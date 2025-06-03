#include "audioloader.h"

// Constructeur : connecte le décodeur à nos slots de traitement
AudioLoader::AudioLoader(QObject *parent)
    : QObject{parent}
{
    connect(&decoder, &QAudioDecoder::bufferReady, this, &AudioLoader::SiBufferPret);
    connect(&decoder, &QAudioDecoder::finished, this, &AudioLoader::finished);
}

// Prépare et lance le décodage du fichier `path`
void AudioLoader::loadFile(const QString &path)
{
    QAudioFormat targetFormat;
    targetFormat.setSampleRate(8000); // ou récupérer la fréquence du fichier
    targetFormat.setSampleFormat(QAudioFormat::UInt8);
    decoder.setAudioFormat(targetFormat);

    decoder.setSource(QUrl::fromLocalFile(path));
    decoder.start();
}

// Traite un buffer décodé et émet un échantillonnage réduit
void AudioLoader::SiBufferPret()
{
    QAudioBuffer buf = decoder.read();
    auto fmt = buf.format();
    const int channelCount = fmt.channelCount();
    const int frames = buf.frameCount();
    const int Fs_orig = fmt.sampleRate();

    if (!buf.isValid() || frames == 0) {
        qWarning() << "Buffer invalide ou vide";
        return;
    }

    QVector<float> block;
    // On estime une taille réaliste pour éviter les réallocations trop
    block.reserve((frames * channelCount + downFactor - 1) / downFactor);

    // Pointeurs sur les données
    if (fmt.sampleFormat() == QAudioFormat::Int16) {
        const float norm = 1.0f / std::numeric_limits<qint16>::max();
        const auto ptr = buf.constData<qint16>();

        // Lecture et down-sampling en une passe
        for (int i = 0; i < frames; ++i) {
            // Pour chaque canal, on moyennise, puis on teste si on garde
            float sample = 0;
            for (int c = 0; c < channelCount; ++c)
                sample += ptr[i * channelCount + c] * norm;
            sample /= channelCount;

            // NE GARDER QUE 1 échantillon sur downFactor
            if ((sampleCounter++ % downFactor) == 0) {
                block.append(sample);
            }
        }
    } else if (fmt.sampleFormat() == QAudioFormat::Float) {
        const auto ptr = buf.constData<float>();
        for (int i = 0; i < frames; ++i) {
            float sample = 0;
            for (int c = 0; c < channelCount; ++c)
                sample += ptr[i * channelCount + c];
            sample /= channelCount;

            if ((sampleCounter++ % downFactor) == 0) {
                block.append(sample);
            }
        }
    } else {
        qWarning() << "Format non géré :" << fmt.sampleFormat();
        return;
    }

    // La nouvelle fréquence d'échantillonnage est divisée par downFactor
    const int Fs_down = Fs_orig / downFactor;
    qDebug() << "Emet" << block.size() << "échantillons à" << Fs_down << "Hz";

    // Transmission du bloc décodé au reste de l'application
    emit SignalReady(block, Fs_down);
}

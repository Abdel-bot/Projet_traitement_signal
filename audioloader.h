#ifndef AUDIOLOADER_H
#define AUDIOLOADER_H

#include <QAudioBuffer>
#include <QAudioDecoder>
#include <QAudioFormat>
#include <QMetaObject>
#include <QObject>
#include <QThread>
#include <QUrl>
#include <QVector>
#include <QtDebug>

// AudioLoader décode un fichier audio dans un QThread
// et émet régulièrement des échantillons sur un signal.
class AudioLoader : public QObject
{
    Q_OBJECT
public:
    explicit AudioLoader(QObject *parent = nullptr);

    /// Lance le décodage du fichier audio `path`.
    /// Les échantillons seront émis par SignalReady.
    void loadFile(const QString &path);

signals:
    /// Emis pour transmettre un bloc d'échantillons décodés
    /// ainsi que la nouvelle fréquence d'échantillonnage.
    void SignalReady(const QVector<float> &samples, int sampleRate);

    /// Signale la fin du décodage.
    void finished();

private slots:
    /// Traite chaque buffer obtenu du décodeur
    void SiBufferPret();

private:
    QAudioDecoder decoder;  ///< objet décodant l'audio
    qint64 sampleCounter = 0; ///< compteur d'échantillons lus
    const int downFactor = 8; ///< réduction de la fréquence d'échantillonnage
};
/// Crée un QThread et un AudioLoader afin de décoder le fichier
/// `audioFilePath`. Les échantillons sont renvoyés au `receiver`
/// via son slot `Echantillonspret`.
inline void setupAudioThread(const QString &audioFilePath, QObject *receiver)
{
    QThread *thread = new QThread;
    AudioLoader *loader = new AudioLoader;
    loader->moveToThread(thread);

    // Une fois le thread lancé, commencer le décodage
    QObject::connect(thread, &QThread::started,receiver,[loader, audioFilePath](){
        loader->loadFile(audioFilePath);
    });

    // Relayer les échantillons vers le thread principal
    QObject::connect(loader, &AudioLoader::SignalReady,
                     receiver, [receiver](const QVector<float>& samples, int sr){
        QMetaObject::invokeMethod(receiver, "Echantillonspret",
                                 Qt::QueuedConnection,
                                 Q_ARG(QVector<float>, samples),
                                 Q_ARG(int, sr));
        qDebug() << "Envoi des échantillons au receiver (" << samples.size() << "échantillons)";
    });
    // Nettoyage quand le décodage est terminé
    QObject::connect(loader, &AudioLoader::finished, thread, &QThread::quit);
    QObject::connect(thread, &QThread::finished, loader, &QObject::deleteLater);
    QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    // Lancement du thread
    thread->start();
}
#endif // AUDIOLOADER_H

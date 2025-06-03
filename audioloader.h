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

class AudioLoader : public QObject
{
    Q_OBJECT
public:
    explicit AudioLoader(QObject *parent = nullptr);
    void loadFile(const QString &path);

signals:
    void SignalReady(const QVector<float> &samples, int sampleRate);
    void finished();

private slots:
    void SiBufferPret();

private:
    QAudioDecoder decoder;
    qint64 sampleCounter = 0;
    const int downFactor = 8;
};
inline void setupAudioThread(const QString &audioFilePath, QObject *receiver)
{
    QThread *thread = new QThread;
    AudioLoader *loader = new AudioLoader;
    loader->moveToThread(thread);

    QObject::connect(thread, &QThread::started,receiver,[loader, audioFilePath](){ loader->loadFile(audioFilePath); });

    QObject::connect(loader, &AudioLoader::SignalReady,
                     receiver, [receiver](const QVector<float>& samples, int sr){
                                    QMetaObject::invokeMethod(receiver, "Echantillonspret",
                                            Qt::QueuedConnection,
                                            Q_ARG(QVector<float>, samples),
                                            Q_ARG(int, sr));
                                            qDebug() << "Envoi des échantillons au receiver (" << samples.size() << "échantillons)";
                                });
    QObject::connect(loader, &AudioLoader::finished, thread, &QThread::quit);
    QObject::connect(thread, &QThread::finished, loader, &QObject::deleteLater);
    QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    thread->start();
}
#endif // AUDIOLOADER_H

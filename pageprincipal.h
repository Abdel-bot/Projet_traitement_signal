#ifndef PAGEPRINCIPAL_H
#define PAGEPRINCIPAL_H

#include <QAudioOutput>
#include <QEvent>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsPathItem>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaRecorder>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainterPath>
#include <QTextStream>
#include <QThread>
#include <QToolTip>
#include "audioloader.h"
#include "fft.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Pageprincipal;
}
QT_END_NAMESPACE

class Pageprincipal : public QMainWindow
{
    Q_OBJECT

public:
    Pageprincipal(QWidget *parent = nullptr);
    ~Pageprincipal();
    void envoyersignal();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void ouvrir_fichier();
    void Echantillonspret(const QVector<float> &samples, int sr);
    void ouvrir_clicker();
    void dessin_signal();
    void enregistrer();
    void Sienregistrementchange(QMediaRecorder::RecorderState etat);
    void essai();
    QStringList separerlignecsv(const QString &line, QChar sep);
    void lire();
    void pause();
    void stop();
    void barrelecture();
    void exporter_csv_cliquer();
    void exporter_wav_cliquer();
    void importer();

private:
    QGraphicsScene *scene_;
    QGraphicsPathItem *waveformItem_ = nullptr;
    Ui::Pageprincipal *ui;
    AudioLoader loader;
    QString fichier;
    QVector<float> Signal_;
    int Fe_ = 0;
    void drawAxes();
    QMediaRecorder *recorder = nullptr;
    fft fft_;
    QMediaPlayer *player = nullptr;
    QAudioOutput *audiooutput = nullptr;
    QList<QAudioDevice> deviceout;
    QGraphicsLineItem *Barredelecture;
    QTimer *playHeadTimer_;
    double facteur_zoom;
};

#endif // PAGEPRINCIPAL_H

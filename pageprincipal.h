#ifndef PAGEPRINCIPAL_H
#define PAGEPRINCIPAL_H

#include <QMainWindow>
#include "audioloader.h"
#include <QThread>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QMediaRecorder>
#include <QTextStream>
#include <QFile>
#include<QEvent>
#include <QMouseEvent>
#include <QToolTip>
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
    void Echantillonspret(const QVector<float>& samples, int sr);
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
    QGraphicsScene* scene_;
    QGraphicsPathItem* waveformItem_ = nullptr;
    Ui::Pageprincipal *ui;
    AudioLoader loader;
    QString fichier;
    QVector<float> Signal_;
    int Fe_ = 0;
    void drawAxes();
    QMediaRecorder* recorder = nullptr;
    fft fft_;
    QMediaPlayer* player = nullptr;
    QAudioOutput* audiooutput=nullptr;
    QList<QAudioDevice> deviceout;
    QGraphicsLineItem*   Barredelecture;
    QTimer* playHeadTimer_;
    double facteur_zoom;
};



#endif // PAGEPRINCIPAL_H

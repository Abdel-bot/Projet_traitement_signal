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
#include <QRubberBand>
#include <QBrush>
#include <QColor>
#include "fft.h"
#include "audioloader.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Pageprincipal;
}
QT_END_NAMESPACE

// Fenêtre principale de l'application d'analyse de signal audio.
class Pageprincipal : public QMainWindow
{
    Q_OBJECT

public:
    Pageprincipal(QWidget *parent = nullptr);
    ~Pageprincipal();

    /// Ouvre la fenêtre FFT et lui transmet le signal complet.
    void envoyersignal();

protected:
    /// Intercepte les événements de la vue pour gérer le zoom et la sélection.
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    /// Boîte de dialogue pour ouvrir un fichier audio.
    void ouvrir_fichier();
    /// Slot appelé par AudioLoader quand des échantillons sont prêts.
    void Echantillonspret(const QVector<float> &samples, int sr);
    /// Slot du menu "Ouvrir"
    void ouvrir_clicker();
    /// Dessine la forme d'onde du signal courant.
    void dessin_signal();
    /// Démarre ou arrête un enregistrement microphone.
    void enregistrer();
    /// Réagit aux changements d'état de l'enregistreur.
    void Sienregistrementchange(QMediaRecorder::RecorderState etat);
    /// Import depuis un fichier CSV.
    void essai();
    /// Outil pour découper une ligne CSV en champs nettoyés.
    QStringList separerlignecsv(const QString &line, QChar sep);
    /// Lance la lecture du fichier ouvert
    void lire();
    /// Met la lecture en pause
    void pause();
    /// Arrête complètement la lecture
    void stop();
    /// Met à jour la barre indiquant la position courante
    void barrelecture();
    /// Exporte tout le signal vers un fichier CSV
    void exporter_csv_cliquer();
    /// Exporter la capture au format WAV (non implémenté)
    void exporter_wav_cliquer();
    /// Import d'un fichier audio ou CSV
    void importer();
    /// Actualise la source du lecteur après ouverture ou import
    void playersource();
    /// Change le périphérique de sortie audio
    void deviceoutchoisi();
    /// Exporte uniquement la sélection courante
    void exporter_selection();
    /// Affiche le spectre de la sélection
    void fft_selection();
    /// Supprime la sélection en cours
    void suppr_selection();
private:
    QGraphicsScene *scene_;            ///< scène utilisée par la vue
    QGraphicsPathItem *waveformItem_ = nullptr; ///< courbe du signal
    Ui::Pageprincipal *ui;
    AudioLoader loader;                ///< décodeur asynchrone
    QString fichier;                  ///< chemin du fichier courant
    QVector<float> Signal_;           ///< données audio chargées
    int Fe_ = 0;                      ///< fréquence d'échantillonnage
    void drawAxes();                  ///< trace les axes de la vue
    QMediaRecorder *recorder = nullptr; ///< enregistreur audio
    fft fft_;                            ///< fenêtre d'analyse FFT
    QMediaPlayer *player = nullptr;      ///< lecteur audio
    QAudioOutput *audiooutput = nullptr; ///< périphérique de sortie courant
    QList<QAudioDevice> deviceout;       ///< liste des sorties disponibles
    QGraphicsLineItem *Barredelecture;   ///< ligne de lecture dans la vue
    QTimer *playHeadTimer_;              ///< timer pour la position
    double facteur_zoom;                 ///< niveau de zoom appliqué
    QRubberBand* rubberBand;             ///< outil de sélection rectangle
    QPoint       origin;                 ///< point initial de la sélection
    QVector<float> Selection;            ///< données sélectionnées
    QGraphicsRectItem *rectItem;         ///< visuel de la sélection
    bool select = false;                 ///< état de sélection actif
    int idxStart;                        ///< premier index sélectionné
};

#endif // PAGEPRINCIPAL_H

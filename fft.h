#ifndef FFT_H
#define FFT_H

#include <QEvent>
#include <QGraphicsPathItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPainterPath>
#include <QToolTip>
#include <QWidget>
#include <cmath>
#include <complex>

using namespace std;
namespace Ui {
class fft;
}

// Widget d'affichage d'un spectre calculé via FFT.
class fft : public QWidget
{
    Q_OBJECT

public:
    explicit fft(QWidget *parent = nullptr);
    ~fft();

public slots:
    /// Réception d'un signal temporel pour calculer la FFT.
    void recupsignal(const QVector<float> &samples, int sr);
private slots:

    /// Lance le calcul de la transformée de Fourier
    void calculedelafft();
    /// Dessine le spectre dans la scène graphique
    void dessin_spectre();

protected:
    /// Gere le zoom et les tooltips dans la vue
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QGraphicsScene *scene_;                   ///< scene d'affichage
    QGraphicsPathItem *waveformItem_ = nullptr; ///< courbe du spectre
    void zeropadding();                      ///< ajoute des zéros pour obtenir une taille puissance de 2
    bool puissancede2();                     ///< teste si la taille est une puissance de 2
    int reverse_bit(int x, unsigned bits);   ///< utilitaire pour la permutation bit-reverse
    void bitReversalPermutation(QVector<std::complex<double>> &a); ///< applique la permutation
    QVector<complex<double>> fft_;           ///< résultat de la FFT
    QVector<double> Signal_;                 ///< signal initial copié
    int Fe_;                                 ///< fréquence d'échantillonnage
    Ui::fft *ui;                             ///< interface générée par Qt
    void drawAxes();                         ///< trace les axes de la vue
    double facteur_zoom;                     ///< niveau de zoom courant
};

#endif // FFT_H

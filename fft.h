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

class fft : public QWidget
{
    Q_OBJECT

public:
    explicit fft(QWidget *parent = nullptr);
    ~fft();

public slots:
    void recupsignal(const QVector<float> &samples, int sr);
private slots:

    void calculedelafft();
    void dessin_spectre();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QGraphicsScene *scene_;
    QGraphicsPathItem *waveformItem_ = nullptr;
    void zeropadding();
    bool puissancede2();
    int reverse_bit(int x, unsigned bits);
    void bitReversalPermutation(QVector<std::complex<double>> &a);
    QVector<complex<double>> fft_;
    QVector<double> Signal_;
    int Fe_;
    Ui::fft *ui;
    void drawAxes();
    double facteur_zoom;
};

#endif // FFT_H

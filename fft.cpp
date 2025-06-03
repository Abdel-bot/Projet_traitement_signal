#include "fft.h"
#include "ui_fft.h"

// Constructeur : initialisation de la vue et de la scène graphique
fft::fft(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::fft)
    , scene_(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene_);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->viewport()->installEventFilter(this);
}

// Destructeur
fft::~fft()
{
    delete ui;
}
// Calcule la FFT du signal courant
void fft::calculedelafft()
{
    // 1) Zero-padding si nécessaire
    if (!puissancede2()) {
        zeropadding();
    }

    // 2) Copie du signal
    QVector<std::complex<double>> a;
    for (int i = 0; i < Signal_.size(); i++) {
        a.append(Signal_[i]);
    }
    int n = a.size();

    // 3) Bit-reversal permutation
    bitReversalPermutation(a);

    // 4) Boucle principale Cooley–Tukey
    int maxStages = static_cast<int>(std::log2(n));
    for (int s = 1; s <= maxStages; ++s) {
        int m = 1 << s;    // m = 2^s
        int half = m >> 1; // m/2
        // Twiddle factor de base W_m
        std::complex<double> Wm = std::exp(std::complex<double>(0, -2.0 * M_PI / m));
        for (int k = 0; k < n; k += m) {
            std::complex<double> w(1, 0);
            for (int j = 0; j < half; ++j) {
                // Butterfly : u + w * t, u - w * t
                std::complex<double> t = w * a[k + j + half];
                std::complex<double> u = a[k + j];
                a[k + j] = u + t;
                a[k + j + half] = u - t;
                w *= Wm;
            }
        }
    }

    // 5) Sauvegarde du résultat
    fft_ = a;
    dessin_spectre();
}
// Vérifie si la taille du signal est une puissance de 2
bool fft::puissancede2()
{
    return Signal_.size() > 0 && (Signal_.size() & (Signal_.size() - 1)) == 0;
}

// Ajoute des zéros pour atteindre la prochaine puissance de 2
void fft::zeropadding()
{
    // Exemples : si taille=6 → puissance=8
    int puissance = 1 << static_cast<int>(std::ceil(std::log2(Signal_.size())));
    for (int i = Signal_.size(); i < puissance; i++) {
        Signal_.append(0.0);
    }
}
// Inversion des bits pour la permutation bit-reverse
int fft::reverse_bit(int x, unsigned bits)
{
    uint32_t ux = static_cast<uint32_t>(x);
    uint32_t y = 0;
    for (unsigned i = 0; i < bits; ++i) {
        y = (y << 1) | (ux & 1u);
        ux >>= 1;
    }
    return static_cast<int>(y);
}

// Applique la permutation bit-reverse à un tableau complexe
void fft::bitReversalPermutation(QVector<std::complex<double>> &a)
{
    int n = a.size();
    unsigned bits = static_cast<unsigned>(std::log2(n));
    for (int i = 0; i < n; ++i) {
        int j = reverse_bit(i, bits);
        if (j > i) {
            std::swap(a[i], a[j]);
        }
    }
}
// Trace le spectre de fréquence dans la vue
void fft::dessin_spectre()
{
    scene_->clear();
    drawAxes();

    const int N = fft_.size();
    if (N < 2) {
        qDebug() << "Signal trop court, rien à dessiner.";
        return;
    }

    // On ne garde que la moitié du spectre (pour un signal réel)
    const int half = N / 2;

    // Dimensions de la vue
    const int w = ui->graphicsView->width();
    const int h = ui->graphicsView->viewport()->height();

    qreal maxFreq = Fe_ / 2.0;
    qreal pxPerHz = w / maxFreq;

    // 1) Trouver le max du signal pour normaliser
    double maxMag = 0.0;
    for (int k = 0; k < half; ++k)
        maxMag = std::max(maxMag, std::abs(fft_[k]));
    if (maxMag == 0.0)
        maxMag = 1.0; // éviter la division par zéro

    // 2) Construire le chemin du spectre
    QPainterPath path;
    // On commence en bas à x=0
    path.moveTo(0, h);

    for (int k = 0; k < half; ++k) {
        // Fréquence en Hz
        double freq = double(k) * Fe_ / N;

        qreal x = qreal(freq) * pxPerHz;

        // Amplitude normalisée [0..1], on l’inverse pour que 1 soit en haut
        double mag = std::abs(fft_[k]) / maxMag;
        qreal y = (1.0 - mag) * h;

        path.lineTo(x, y);
    }

    // 3) Tracé et mise à l’échelle
    scene_->addPath(path, QPen(Qt::blue, 2));
    ui->graphicsView->fitInView(scene_->itemsBoundingRect(), Qt::KeepAspectRatio);

    qDebug() << "Spectre tracé pour" << half << "bins jusqu'à" << (Fe_ / 2) << "Hz";
}
// Stocke le signal fourni puis lance le calcul de FFT
void fft::recupsignal(const QVector<float> &samples, int sr)
{
    Fe_ = sr;
    Signal_.resize(samples.size());
    for (int i = 0; i < samples.size(); ++i)
        Signal_[i] = samples[i]; // ← redimensionne Signal_ à samples.size()
    calculedelafft();
}
// Trace les axes de référence dans la scène
void fft::drawAxes()
{
    const int w = ui->graphicsView->viewport()->width();
    const int h = ui->graphicsView->viewport()->height();
    QPen axisPen(Qt::black);
    axisPen.setWidth(1);

    // Axe horizontal (temps)
    scene_->addLine(0, h / 2, w, h / 2, axisPen);
    // Axe vertical (amplitude)
    scene_->addLine(0, 0, 0, h, axisPen);
}
// Gestion du zoom et de l'affichage d'informations sous la souris
bool fft::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->graphicsView->viewport() && event->type() == QEvent::Wheel) {
        // Cast correct pour Qt6 : QEvent* vers QWheelEvent*
        const QWheelEvent *roue = static_cast<QWheelEvent *>(event);
        const qreal angle = roue->angleDelta().y();
        const qreal facteur = qPow(1.0015, angle);
        facteur_zoom *= facteur;
        ui->graphicsView->scale(facteur, facteur);
        return true;
    }
    if (watched == ui->graphicsView->viewport() && event->type() == QEvent::MouseMove) {
        int w = ui->graphicsView->viewport()->width();
        int h = ui->graphicsView->viewport()->height();

        qreal maxFreq = Fe_ / 2.0;
        qreal pxPerHz = w / maxFreq; // pixels par seconde
        auto *mouseEv = static_cast<QMouseEvent *>(event);
        QPoint ptVue = mouseEv->pos();
        QPointF ptScene = ui->graphicsView->mapToScene(ptVue);
        float frequence = ptScene.x() / pxPerHz;
        float amp   = -ptScene.y() / h;
        if (fft_.size() > 0) {
            int N = fft_.size();
            int idx = qBound(0, int(frequence * N / Fe_), N - 1);
            amp = std::abs(fft_[idx]);
        }
        QString txt = tr("frequence : %1 Hz\nAmplitude : %2").
                      arg(frequence, 0, 'f', 1).
                      arg(amp,   0, 'f', 2);
        QToolTip::showText(
            ui->graphicsView->viewport()->mapToGlobal(ptVue),
            txt,
            ui->graphicsView->viewport()
            );
        return false;
    }
    return QWidget::eventFilter(watched, event);
}

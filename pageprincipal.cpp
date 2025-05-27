#include "pageprincipal.h"
#include "./ui_pageprincipal.h"
#include <QPainterPath>
#include <QPen>
#include <QMediaCaptureSession>
#include <QMediaRecorder>
#include <QAudioInput>
#include <QMediaDevices>
#include <QAudioDevice>
#include <QTimer>



Pageprincipal::Pageprincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Pageprincipal),scene_(new QGraphicsScene(this)),recorder(new QMediaRecorder(this)),player(new QMediaPlayer(this)),audiooutput(new QAudioOutput(this)),Barredelecture(nullptr),
    facteur_zoom(1)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(scene_);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->viewport()->installEventFilter(this);


    QList<QString> listdevices;
    const auto device = QMediaDevices::audioInputs();
    for (const QAudioDevice &device : device){

        listdevices.append(device.description());
    }
    ui->Devices->addItems(QStringList (listdevices));

    QList<QString> listdevicesout;
    deviceout = QMediaDevices::audioOutputs();
    for (const QAudioDevice &deviceo : deviceout){
        listdevicesout.append(deviceo.description());
    }
    ui->Devicesout->addItems(QStringList (listdevicesout));


    connect(ui->actionOuvrir,&QAction::triggered,this,&Pageprincipal::ouvrir_clicker);



    connect(player, &QMediaPlayer::positionChanged,this,&Pageprincipal::barrelecture);
    connect(ui->BouttonLire,&QPushButton::clicked,this,&Pageprincipal::lire);
    connect(ui->BouttonPause,&QPushButton::clicked,this,&Pageprincipal::pause);
    connect(ui->BoutonArreter,&QPushButton::clicked,this,&Pageprincipal::stop);
    connect(ui->actionImporter,&QAction::triggered,this,&Pageprincipal::importer);
    connect(recorder, &QMediaRecorder::recorderStateChanged,this, &Pageprincipal::Sienregistrementchange);
    connect(ui->BonttonEnregistrer,&QPushButton::clicked,this,&Pageprincipal::enregistrer);
    connect(ui->actionTracer_le_spectre,&QAction::triggered,this,&Pageprincipal::envoyersignal);
    connect(ui->actionExporter_csv,&QAction::triggered,this,&Pageprincipal::exporter_csv_cliquer);

}

Pageprincipal::~Pageprincipal()
{
    delete ui;
}
void Pageprincipal::ouvrir_fichier(){
    fichier = QFileDialog::getOpenFileName(
        this,
        tr("Ouvrir Audio"),
        {},
        tr("Audio (*.wav *.mp3 *.aac *.flac *.mp4)")
        );
    if (fichier.isEmpty()) return;
    Signal_.clear();
    setupAudioThread(fichier, this);
}
void Pageprincipal::Echantillonspret(const QVector<float>& samples, int sr)
{
    if (Signal_.isEmpty()) {
        Fe_ = sr;
    }
    Signal_ += samples;
    qDebug() << "Signal_ total : " << Signal_.size();
    // Dès que des échantillons arrivent, dessiner
    dessin_signal();

}
void Pageprincipal::drawAxes()
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
void Pageprincipal::ouvrir_clicker(){
    ouvrir_fichier();
    if(ui->actionExporter_csv->isEnabled()){
        ui->actionExporter_csv->setEnabled(true);
    }
    ui->actionExporter_wav->setEnabled(false);
}
void Pageprincipal::dessin_signal(){
    // Nettoyage de l'ancien tracé
    scene_->clear();
    drawAxes();

    int N = Signal_.size();
    if (N < 2){
        qDebug() << "Signal vide, rien à dessiner.";
        return;}

    int w = ui->graphicsView->viewport()->width();
    int h = ui->graphicsView->viewport()->height();

    // Construire la forme d'onde
    QPainterPath path;
    path.moveTo(0, h / 2);

    double dureeSec = double(N) / Fe_;              // durée totale en secondes
    double kx = w/ dureeSec;                        // pixels par seconde
    double ky = h;                                  // si y est déjà dans [0..1]

    for (int i = 0; i < N; ++i) {
        double t = double(i) / Fe_;                 // temps en secondes
        qreal x = t * kx;                           // position en pixels
        double amp = Signal_[i];                    // supposé dans [-1..1] ou [0..1]
        qreal y = (0.5 - amp*0.5) * ky;             // conversion en pixels
        path.lineTo(x, y);
    }
    qDebug() << "Tracé de" << N << "points";

    //Ajouter le tracé
    waveformItem_ = scene_->addPath(path, QPen(Qt::red));
    ui->graphicsView->fitInView(scene_->itemsBoundingRect(), Qt::KeepAspectRatioByExpanding);
}

void Pageprincipal::enregistrer(){
    // Ces objets statiques persistent entre les appels
    static QMediaCaptureSession *session    = nullptr;
    static QAudioInput          *audioInput = nullptr;

    // Initialisation (seulement au premier appel)
    if (!session) {
        session  = new QMediaCaptureSession(this);
        session->setRecorder(recorder);
    }

    // Si on enregistre déjà, on stoppe et on remet le bouton
    if (recorder->recorderState() == QMediaRecorder::RecordingState) {
        recorder->stop();
        ui->BonttonEnregistrer->setText(tr("Enregistrer"));
        return;

    }

    // 3) Choix du chemin
    fichier = QFileDialog::getSaveFileName(
        this,
        tr("Enregistrer audio"),
        {},
        tr("WAV (*.wav);;MP3 (*.mp3)")
        );
    if (fichier.isEmpty())
        return;

    int idx = ui->Devices->currentIndex();
    QAudioDevice chosenDevice = QMediaDevices::audioInputs().value(idx);

    // (Re)création de l’input audio
    delete audioInput;
    audioInput = new QAudioInput(chosenDevice, this);
    session->setAudioInput(audioInput);

    // Mettre la qualité au plus haut que possible (on a pas besoin de se soucier car déjà pris en charge dans la lecture)
    recorder->setQuality(QMediaRecorder::HighQuality);

    // Lancer l’enregistrement
    recorder->setOutputLocation(QUrl::fromLocalFile(fichier));
    recorder->record();

    // Mise à jour de l’UI
    ui->BonttonEnregistrer->setText(tr("Arrêter"));

}
void Pageprincipal::Sienregistrementchange(QMediaRecorder::RecorderState etat)
{
    if (etat == QMediaRecorder::StoppedState) {
        // À l’arrêt : le fichier est complet, on peut décoder et afficher
        Signal_.clear();
        setupAudioThread(fichier, this);
    }
}
void Pageprincipal::essai()
{
    // 1) Boîte de dialogue pour choisir le fichier CSV à importer
    QString chemin = QFileDialog::getOpenFileName(
        this,
        tr("Importer le signal"),
        QString(),
        tr("CSV (*.csv)")
        );
    if (chemin.isEmpty())
        return;

    // 2) Ouvrir le fichier en lecture texte
    QFile fichier(chemin);
    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(
            this,
            tr("Erreur d'import"),
            tr("Impossible d'ouvrir le fichier en lecture :\n%1").arg(chemin)
            );
        return;
    }

    QTextStream in(&fichier);
    in.setEncoding(QStringConverter::Utf8);

    // 3) Lire et recuperer les different entête de la ligne d'en-tête
    if (in.atEnd()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Le fichier est vide."));
        return;
    }
    QString headerLine = in.readLine();
    QStringList headers = separerlignecsv(headerLine, ';');

    // 4) Trouver les indices des colonnes recherchées
    int idxFs = -1, idxAmp = -1;
    for (int i = 0; i < headers.size(); ++i) {
        QString h = headers.at(i).trimmed().toLower();
        if (h == QString("fréquence d'échantillonnage") || h == QString("frequence d'echantillonnage"))
        {
            idxFs = i;
        }
        else if (h == QString("amplitude")) {
            idxAmp = i;
        }
    }

    if (idxFs < 0 || idxAmp < 0) {
        QMessageBox::critical(
            this,
            tr("Erreur"),
            tr("Colonnes 'fréquence d’échantillonnage' et/ou 'amplitude' introuvables.")
            );
        return;
    }

    // 5) Parcourir toutes les lignes et extraire Fs et amplitude
    //    On remet à zéro vos conteneurs
    Signal_.clear();
    Fe_=0;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        QStringList champs = separerlignecsv(line, ';');
        // Vérifier qu'on a suffisamment de champs
        if (champs.size() <= qMax(idxFs, idxAmp))
            continue;

        bool okFs = false, okAmp = false;
        int     fs  = champs.at(idxFs).toInt(&okFs);
        double  amp = champs.at(idxAmp).toDouble(&okAmp);

        if (okFs && okAmp) {
            if(Fe_==0)Fe_=fs;
            Signal_.append(static_cast<float>(amp));
        }
        else {
            // Ligne mal formée, on l'ignore
            qWarning() << "Ligne CSV invalide :" << line;
        }
    }

    fichier.close();

    QMessageBox::information(
        this,
        tr("Import terminé"),
        tr("Le signal a été importé avec %1 points.").arg(Signal_.size())
        );
    dessin_signal();
}

// Utilitaire de découpage et trim
QStringList Pageprincipal::separerlignecsv(const QString &line, QChar sep)
{
    QStringList parts = line.split(sep);
    for (QString &p : parts)
        p = p.trimmed();
    return parts;
}
void Pageprincipal::envoyersignal(){
    fft *fft = &fft_ ;
    fft_.show();
    if (!fft) {
        qWarning() << "Pas de Processor configuré";
        return;
    }

    bool ok = QMetaObject::invokeMethod(
        fft,
        "recupsignal",                       // nom du slot
        Qt::QueuedConnection,                 // ou Qt::DirectConnection
        Q_ARG(QVector<float>, Signal_),         // premier argument
        Q_ARG(int, Fe_)                   // second argument
        );

    if (!ok) {
        qWarning() << "Échec de l'invocation du slot onAudioReady";
    }
}
void Pageprincipal::lire(){
    if(player->source()!=QUrl::fromLocalFile(fichier) || !player){
        audiooutput = new QAudioOutput(deviceout[ui->Devicesout->currentIndex()]);
        player->setSource(QUrl::fromLocalFile(fichier));
        player->setAudioOutput(audiooutput);
        audiooutput->setVolume(50);
    }

    player->play();
}
void Pageprincipal::barrelecture(){
    const int h = ui->graphicsView->viewport()->height();
    double posMs = player->position();
    double Ttot = player->duration();   // durée totale en ms
    double k = ui->graphicsView->width() / Ttot;
    double x_px = posMs * k;

    if (!Barredelecture) {
        // Création de la ligne la première fois
        QPen pen(Qt::blue);
        pen.setWidth(2);
        Barredelecture = scene_->addLine(x_px, 0, x_px, h, pen);
    } else {
        // Mise à jour de la ligne existante
        Barredelecture->setLine(x_px, 0, x_px, h);
    }
    ui->graphicsView->centerOn(Barredelecture);
}
void Pageprincipal::pause(){
    player->pause();
}
void Pageprincipal::stop(){
    player->stop();
}
bool Pageprincipal::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->graphicsView->viewport() && event->type() == QEvent::Wheel) {
        // Cast correct pour Qt6 : QEvent* vers QWheelEvent*
        const QWheelEvent *roue = static_cast<QWheelEvent*>(event);
        const qreal angle = roue->angleDelta().y();
        const qreal facteur = qPow(1.0015, angle);
        facteur_zoom *= facteur;
        waveformItem_->setPen(QPen(Qt::red,(1/facteur_zoom)));
        ui->graphicsView->scale(facteur, facteur);
        return true;
    }
    if(watched==ui->graphicsView->viewport() && event->type() == QEvent::MouseMove){
        int w = ui->graphicsView->viewport()->width();
        int h = ui->graphicsView->viewport()->height();
        int N = Signal_.size();
        double dureeSec = double(N) / Fe_;              // durée totale en secondes
        double kx = w / dureeSec;                       // pixels par seconde
        double ky = h;                                  // pixels par seconde
        auto *mouseEv = static_cast<QMouseEvent*>(event);
        QPoint ptVue = mouseEv->pos();
        QPointF ptScene = ui->graphicsView->mapToScene(ptVue);
        float temps = ptScene.x() / kx;
        float amp=-ptScene.y()/ky;
        if(Signal_.size()>2) amp   = (Signal_[ptScene.x()/kx*Fe_]);
        QString txt = tr("Temps : %1 ms\nAmplitude : %2").
                      arg(temps, 0, 'f', 1).
                      arg(amp,   0, 'f', 2);
        QToolTip::showText(
            ui->graphicsView->viewport()->mapToGlobal(ptVue),
            txt,
            ui->graphicsView->viewport()
            );
        return false;
    }
    return QMainWindow::eventFilter(watched, event);
}
void Pageprincipal::importer(){
    essai();
    if(ui->actionExporter_wav->isEnabled()){
        ui->actionExporter_wav->setEnabled(true);
    }
    ui->actionExporter_csv->setEnabled(false);
}
void Pageprincipal::exporter_csv_cliquer(){
    QString chemin = QFileDialog::getSaveFileName(
        this,
        tr("Importer le signal"),
        QString(),
        tr("CSV (*.csv)")
        );
    if (chemin.isEmpty())
        return;

    // 2) Ouvrir le fichier en lecture texte
    QFile fichier(chemin);
    if (!fichier.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(
            this,
            tr("Erreur d'import"),
            tr("Impossible d'ouvrir le fichier en ecriture :\n%1").arg(chemin)
            );
        return;
    }

    QTextStream out(&fichier);
    out<<"fréquence d'echantillonnage "<<','<<"temps"<<','<<"amplitude\n";
    out<<Fe_<<','<<0<<','<<Signal_[0]<<"\n";
    for(int i =1;i<Signal_.size();i++){
        double t = double(i) / Fe_;                 // temps en secondes
        out<<0<<';'<<t<<';'<<Signal_[i]<<"\n";
    }
    QMessageBox::information(
        this,
        tr("Import terminé"),
        tr("Le signal a été exporter avec %1 points.").arg(Signal_.size())
        );
    fichier.close();
}
void Pageprincipal::exporter_wav_cliquer(){
    return;
}

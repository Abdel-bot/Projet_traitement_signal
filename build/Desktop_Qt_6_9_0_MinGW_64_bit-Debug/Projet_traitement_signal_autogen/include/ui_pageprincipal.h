/********************************************************************************
** Form generated from reading UI file 'pageprincipal.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEPRINCIPAL_H
#define UI_PAGEPRINCIPAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Pageprincipal
{
public:
    QAction *actionOuvrir;
    QAction *actionImporter;
    QAction *actionTracer_le_spectre;
    QAction *actionExporter_csv;
    QAction *actionExporter_wav;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *gridWidget_2;
    QGridLayout *gridLayout_2;
    QGraphicsView *graphicsView;
    QGridLayout *gridLayout;
    QPushButton *BonttonEnregistrer;
    QLabel *Enregistrer;
    QHBoxLayout *horizontalLayout;
    QPushButton *BouttonLire;
    QPushButton *BouttonPause;
    QPushButton *BoutonArreter;
    QComboBox *Devices;
    QLabel *label;
    QComboBox *Devicesout;
    QLabel *label_3;
    QLabel *Lire;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QMenu *menuAnalyse;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Pageprincipal)
    {
        if (Pageprincipal->objectName().isEmpty())
            Pageprincipal->setObjectName("Pageprincipal");
        Pageprincipal->resize(916, 573);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Pageprincipal->sizePolicy().hasHeightForWidth());
        Pageprincipal->setSizePolicy(sizePolicy);
        actionOuvrir = new QAction(Pageprincipal);
        actionOuvrir->setObjectName("actionOuvrir");
        actionImporter = new QAction(Pageprincipal);
        actionImporter->setObjectName("actionImporter");
        actionTracer_le_spectre = new QAction(Pageprincipal);
        actionTracer_le_spectre->setObjectName("actionTracer_le_spectre");
        actionExporter_csv = new QAction(Pageprincipal);
        actionExporter_csv->setObjectName("actionExporter_csv");
        actionExporter_wav = new QAction(Pageprincipal);
        actionExporter_wav->setObjectName("actionExporter_wav");
        centralwidget = new QWidget(Pageprincipal);
        centralwidget->setObjectName("centralwidget");
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        gridWidget_2 = new QWidget(centralwidget);
        gridWidget_2->setObjectName("gridWidget_2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gridWidget_2->sizePolicy().hasHeightForWidth());
        gridWidget_2->setSizePolicy(sizePolicy1);
        gridWidget_2->setMaximumSize(QSize(1920, 1080));
        gridWidget_2->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        gridWidget_2->setAutoFillBackground(false);
        gridLayout_2 = new QGridLayout(gridWidget_2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
        graphicsView = new QGraphicsView(gridWidget_2);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setEnabled(true);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMaximumSize(QSize(16777215, 16777212));
        graphicsView->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        graphicsView->setAutoFillBackground(false);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);

        gridLayout_2->addWidget(graphicsView, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        BonttonEnregistrer = new QPushButton(gridWidget_2);
        BonttonEnregistrer->setObjectName("BonttonEnregistrer");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(BonttonEnregistrer->sizePolicy().hasHeightForWidth());
        BonttonEnregistrer->setSizePolicy(sizePolicy2);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::MediaRecord));
        BonttonEnregistrer->setIcon(icon);

        gridLayout->addWidget(BonttonEnregistrer, 1, 0, 1, 1);

        Enregistrer = new QLabel(gridWidget_2);
        Enregistrer->setObjectName("Enregistrer");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(Enregistrer->sizePolicy().hasHeightForWidth());
        Enregistrer->setSizePolicy(sizePolicy3);
        Enregistrer->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(Enregistrer, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        BouttonLire = new QPushButton(gridWidget_2);
        BouttonLire->setObjectName("BouttonLire");
        sizePolicy2.setHeightForWidth(BouttonLire->sizePolicy().hasHeightForWidth());
        BouttonLire->setSizePolicy(sizePolicy2);
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
        BouttonLire->setIcon(icon1);

        horizontalLayout->addWidget(BouttonLire);

        BouttonPause = new QPushButton(gridWidget_2);
        BouttonPause->setObjectName("BouttonPause");
        sizePolicy2.setHeightForWidth(BouttonPause->sizePolicy().hasHeightForWidth());
        BouttonPause->setSizePolicy(sizePolicy2);
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause));
        BouttonPause->setIcon(icon2);

        horizontalLayout->addWidget(BouttonPause);

        BoutonArreter = new QPushButton(gridWidget_2);
        BoutonArreter->setObjectName("BoutonArreter");
        sizePolicy2.setHeightForWidth(BoutonArreter->sizePolicy().hasHeightForWidth());
        BoutonArreter->setSizePolicy(sizePolicy2);
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStop));
        BoutonArreter->setIcon(icon3);

        horizontalLayout->addWidget(BoutonArreter);


        gridLayout->addLayout(horizontalLayout, 1, 2, 1, 1);

        Devices = new QComboBox(gridWidget_2);
        Devices->setObjectName("Devices");
        sizePolicy2.setHeightForWidth(Devices->sizePolicy().hasHeightForWidth());
        Devices->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(Devices, 1, 3, 1, 1);

        label = new QLabel(gridWidget_2);
        label->setObjectName("label");
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        label->setTextFormat(Qt::TextFormat::RichText);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label->setWordWrap(true);

        gridLayout->addWidget(label, 0, 3, 1, 1);

        Devicesout = new QComboBox(gridWidget_2);
        Devicesout->setObjectName("Devicesout");
        sizePolicy3.setHeightForWidth(Devicesout->sizePolicy().hasHeightForWidth());
        Devicesout->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(Devicesout, 1, 4, 1, 1);

        label_3 = new QLabel(gridWidget_2);
        label_3->setObjectName("label_3");
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);
        label_3->setTextFormat(Qt::TextFormat::RichText);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_3->setWordWrap(true);

        gridLayout->addWidget(label_3, 0, 4, 1, 1);

        Lire = new QLabel(gridWidget_2);
        Lire->setObjectName("Lire");
        sizePolicy3.setHeightForWidth(Lire->sizePolicy().hasHeightForWidth());
        Lire->setSizePolicy(sizePolicy3);
        Lire->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        Lire->setTextFormat(Qt::TextFormat::PlainText);
        Lire->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(Lire, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        verticalLayout->addWidget(gridWidget_2);

        Pageprincipal->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Pageprincipal);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 916, 21));
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(menubar->sizePolicy().hasHeightForWidth());
        menubar->setSizePolicy(sizePolicy4);
        menuFichier = new QMenu(menubar);
        menuFichier->setObjectName("menuFichier");
        menuAnalyse = new QMenu(menubar);
        menuAnalyse->setObjectName("menuAnalyse");
        Pageprincipal->setMenuBar(menubar);
        statusbar = new QStatusBar(Pageprincipal);
        statusbar->setObjectName("statusbar");
        Pageprincipal->setStatusBar(statusbar);

        menubar->addAction(menuFichier->menuAction());
        menubar->addAction(menuAnalyse->menuAction());
        menuFichier->addAction(actionOuvrir);
        menuFichier->addAction(actionImporter);
        menuFichier->addAction(actionExporter_csv);
        menuFichier->addAction(actionExporter_wav);
        menuAnalyse->addAction(actionTracer_le_spectre);

        retranslateUi(Pageprincipal);

        QMetaObject::connectSlotsByName(Pageprincipal);
    } // setupUi

    void retranslateUi(QMainWindow *Pageprincipal)
    {
        Pageprincipal->setWindowTitle(QCoreApplication::translate("Pageprincipal", "Pageprincipal", nullptr));
        actionOuvrir->setText(QCoreApplication::translate("Pageprincipal", "Ouvrir", nullptr));
        actionImporter->setText(QCoreApplication::translate("Pageprincipal", "Importer", nullptr));
        actionTracer_le_spectre->setText(QCoreApplication::translate("Pageprincipal", "Tracer le spectre", nullptr));
        actionExporter_csv->setText(QCoreApplication::translate("Pageprincipal", "Exporter (.csv)", nullptr));
        actionExporter_wav->setText(QCoreApplication::translate("Pageprincipal", "Exporter(.wav)", nullptr));
        BonttonEnregistrer->setText(QCoreApplication::translate("Pageprincipal", "Enregistrer", nullptr));
        Enregistrer->setText(QCoreApplication::translate("Pageprincipal", "Enregistrer un nouveau Signal", nullptr));
        BouttonLire->setText(QCoreApplication::translate("Pageprincipal", "Lire", nullptr));
        BouttonPause->setText(QCoreApplication::translate("Pageprincipal", "Pause", nullptr));
        BoutonArreter->setText(QCoreApplication::translate("Pageprincipal", "Arreter", nullptr));
        label->setText(QCoreApplication::translate("Pageprincipal", "Entrez votre p\303\251riph\303\251rique d'entr\303\251e", nullptr));
        label_3->setText(QCoreApplication::translate("Pageprincipal", "Entrez votre p\303\251riph\303\251rique de sortie", nullptr));
        Lire->setText(QCoreApplication::translate("Pageprincipal", "Lire le signal", nullptr));
        menuFichier->setTitle(QCoreApplication::translate("Pageprincipal", "Fichier", nullptr));
        menuAnalyse->setTitle(QCoreApplication::translate("Pageprincipal", "Analyse", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Pageprincipal: public Ui_Pageprincipal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEPRINCIPAL_H

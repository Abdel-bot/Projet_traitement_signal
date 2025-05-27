/********************************************************************************
** Form generated from reading UI file 'fft.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FFT_H
#define UI_FFT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fft
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *fft)
    {
        if (fft->objectName().isEmpty())
            fft->setObjectName("fft");
        fft->resize(1025, 546);
        verticalLayout_2 = new QVBoxLayout(fft);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(fft);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setTextFormat(Qt::TextFormat::AutoText);
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label->setWordWrap(false);

        verticalLayout->addWidget(label);

        graphicsView = new QGraphicsView(fft);
        graphicsView->setObjectName("graphicsView");

        verticalLayout->addWidget(graphicsView);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(fft);

        QMetaObject::connectSlotsByName(fft);
    } // setupUi

    void retranslateUi(QWidget *fft)
    {
        fft->setWindowTitle(QCoreApplication::translate("fft", "Form", nullptr));
        label->setText(QCoreApplication::translate("fft", "Spectre du Signal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class fft: public Ui_fft {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FFT_H

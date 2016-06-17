/********************************************************************************
** Form generated from reading UI file 'trackbars.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKBARS_H
#define UI_TRACKBARS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Trackbars
{
public:
    QWidget *centralWidget;
    QLabel *label_4;
    QLabel *label_8;
    QSlider *horizontalSlider_5;
    QLabel *label_6;
    QLabel *label_2;
    QLabel *label_3;
    QSlider *horizontalSlider_3;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSlider *horizontalSlider_4;
    QLabel *label;
    QLabel *label_7;
    QSlider *horizontalSlider;
    QLabel *label_5;
    QSlider *horizontalSlider_2;
    QSlider *horizontalSlider_6;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *frame3;
    QLabel *label_14;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Trackbars)
    {
        if (Trackbars->objectName().isEmpty())
            Trackbars->setObjectName(QString::fromUtf8("Trackbars"));
        Trackbars->resize(832, 365);
        centralWidget = new QWidget(Trackbars);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(460, 150, 55, 17));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 70, 61, 17));
        horizontalSlider_5 = new QSlider(centralWidget);
        horizontalSlider_5->setObjectName(QString::fromUtf8("horizontalSlider_5"));
        horizontalSlider_5->setGeometry(QRect(110, 30, 351, 30));
        horizontalSlider_5->setMaximum(255);
        horizontalSlider_5->setOrientation(Qt::Horizontal);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 30, 55, 17));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(460, 70, 55, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(460, 110, 55, 17));
        horizontalSlider_3 = new QSlider(centralWidget);
        horizontalSlider_3->setObjectName(QString::fromUtf8("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(110, 110, 351, 30));
        horizontalSlider_3->setMaximum(255);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(260, 270, 269, 29));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSlider_4 = new QSlider(centralWidget);
        horizontalSlider_4->setObjectName(QString::fromUtf8("horizontalSlider_4"));
        horizontalSlider_4->setGeometry(QRect(110, 70, 351, 30));
        horizontalSlider_4->setMaximum(255);
        horizontalSlider_4->setOrientation(Qt::Horizontal);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(460, 30, 55, 17));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 150, 55, 17));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(110, 150, 351, 30));
        horizontalSlider->setMaximum(255);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 110, 55, 17));
        horizontalSlider_2 = new QSlider(centralWidget);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(110, 190, 351, 30));
        horizontalSlider_2->setMaximum(255);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        horizontalSlider_6 = new QSlider(centralWidget);
        horizontalSlider_6->setObjectName(QString::fromUtf8("horizontalSlider_6"));
        horizontalSlider_6->setGeometry(QRect(110, 230, 351, 30));
        horizontalSlider_6->setMaximum(255);
        horizontalSlider_6->setOrientation(Qt::Horizontal);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 190, 55, 17));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(30, 230, 55, 17));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(460, 190, 55, 17));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(460, 230, 55, 17));
        frame3 = new QLabel(centralWidget);
        frame3->setObjectName(QString::fromUtf8("frame3"));
        frame3->setGeometry(QRect(550, 40, 241, 201));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(640, 240, 55, 17));
        Trackbars->setCentralWidget(centralWidget);
        label_4->raise();
        label_8->raise();
        horizontalSlider_5->raise();
        label_6->raise();
        label_2->raise();
        label_3->raise();
        horizontalSlider_3->raise();
        layoutWidget->raise();
        horizontalSlider_4->raise();
        label->raise();
        label_7->raise();
        horizontalSlider->raise();
        label_5->raise();
        horizontalSlider_2->raise();
        pushButton_3->raise();
        horizontalSlider_6->raise();
        label_9->raise();
        label_10->raise();
        label_11->raise();
        label_12->raise();
        frame3->raise();
        label_14->raise();
        menuBar = new QMenuBar(Trackbars);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 832, 25));
        Trackbars->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Trackbars);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Trackbars->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Trackbars);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Trackbars->setStatusBar(statusBar);

        retranslateUi(Trackbars);

        QMetaObject::connectSlotsByName(Trackbars);
    } // setupUi

    void retranslateUi(QMainWindow *Trackbars)
    {
        Trackbars->setWindowTitle(QApplication::translate("Trackbars", "Trackbars", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Trackbars", "0", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Trackbars", "highh", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Trackbars", "lowh", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Trackbars", "0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Trackbars", "0", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("Trackbars", "LOAD", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Trackbars", "SAVE", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Trackbars", "EXIT", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Trackbars", "0", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Trackbars", "highs", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Trackbars", "lows", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Trackbars", "lowv", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Trackbars", "highv", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Trackbars", "0", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("Trackbars", "0", 0, QApplication::UnicodeUTF8));
        frame3->setText(QString());
        label_14->setText(QApplication::translate("Trackbars", "Output", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Trackbars: public Ui_Trackbars {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKBARS_H

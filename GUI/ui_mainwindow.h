/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLabel *frame2;
    QLabel *frame1;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_5;
    QRadioButton *radioButton_2;
    QComboBox *comboBox_3;
    QRadioButton *radioButton;
    QLabel *label_4;
    QLabel *label_6;
    QRadioButton *radioButton_3;
    QLabel *label_7;
    QCheckBox *checkBox;
    QLabel *label_8;
    QLabel *label_9;
    QRadioButton *radioButton_4;
    QLabel *label_3;
    QLabel *label_10;
    QLabel *label_11;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1132, 632);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1000, 530, 121, 41));
        frame2 = new QLabel(centralWidget);
        frame2->setObjectName(QStringLiteral("frame2"));
        frame2->setGeometry(QRect(440, 10, 371, 291));
        frame1 = new QLabel(centralWidget);
        frame1->setObjectName(QStringLiteral("frame1"));
        frame1->setGeometry(QRect(10, 10, 371, 291));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(80, 350, 221, 35));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 410, 71, 17));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(140, 310, 121, 17));
        QFont font;
        font.setFamily(QStringLiteral("Droid Sans Fallback"));
        label_2->setFont(font);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(580, 310, 191, 17));
        radioButton_2 = new QRadioButton(centralWidget);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(radioButton_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(230, 440, 121, 22));
        comboBox_3 = new QComboBox(centralWidget);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(300, 520, 131, 31));
        radioButton = new QRadioButton(centralWidget);
        buttonGroup->addButton(radioButton);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(230, 480, 121, 22));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 540, 55, 17));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(60, 540, 55, 17));
        radioButton_3 = new QRadioButton(centralWidget);
        buttonGroup->addButton(radioButton_3);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(100, 440, 103, 22));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(230, 410, 55, 17));
        checkBox = new QCheckBox(centralWidget);
        buttonGroup->addButton(checkBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(360, 360, 101, 22));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(920, 440, 151, 61));
        QFont font1;
        font1.setFamily(QStringLiteral("High Jinks"));
        font1.setPointSize(34);
        label_8->setFont(font1);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(960, 500, 151, 17));
        QFont font2;
        font2.setFamily(QStringLiteral("Slant"));
        font2.setPointSize(15);
        label_9->setFont(font2);
        radioButton_4 = new QRadioButton(centralWidget);
        buttonGroup->addButton(radioButton_4);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(230, 520, 103, 22));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(470, 450, 55, 17));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(550, 450, 55, 17));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(630, 450, 55, 17));
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(500, 440, 46, 27));
        spinBox_2 = new QSpinBox(centralWidget);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(580, 440, 46, 27));
        spinBox_3 = new QSpinBox(centralWidget);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setGeometry(QRect(660, 440, 46, 27));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(470, 490, 55, 17));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(550, 490, 55, 17));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(630, 490, 55, 17));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(500, 490, 16, 17));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(590, 490, 16, 17));
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(660, 490, 16, 17));
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(500, 520, 55, 17));
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(590, 520, 61, 17));
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(550, 520, 16, 17));
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(650, 520, 16, 17));
        label_22 = new QLabel(centralWidget);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(900, 70, 151, 17));
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(930, 140, 71, 141));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1132, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Exit", 0));
        frame2->setText(QString());
        frame1->setText(QString());
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Load from Camera 1", 0)
         << QApplication::translate("MainWindow", "Load from Camera 2", 0)
         << QApplication::translate("MainWindow", "Load from file", 0)
        );
        label->setText(QApplication::translate("MainWindow", "Threshold", 0));
        label_2->setText(QApplication::translate("MainWindow", "Feed footage", 0));
        label_5->setText(QApplication::translate("MainWindow", "Processed Image", 0));
        radioButton_2->setText(QApplication::translate("MainWindow", " Path detection", 0));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Red", 0)
         << QApplication::translate("MainWindow", "Orange", 0)
         << QApplication::translate("MainWindow", "Blue", 0)
         << QApplication::translate("MainWindow", "Green", 0)
         << QApplication::translate("MainWindow", "Yellow", 0)
        );
        radioButton->setText(QApplication::translate("MainWindow", "Line detection", 0));
        label_4->setText(QApplication::translate("MainWindow", "FPS : ", 0));
        label_6->setText(QApplication::translate("MainWindow", "0", 0));
        radioButton_3->setText(QApplication::translate("MainWindow", "HSV ", 0));
        label_7->setText(QApplication::translate("MainWindow", "Detection", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Save stream", 0));
        label_8->setText(QApplication::translate("MainWindow", "SAMUDRA", 0));
        label_9->setText(QApplication::translate("MainWindow", "Deigned by Shivam", 0));
        radioButton_4->setText(QApplication::translate("MainWindow", "Buoy", 0));
        label_3->setText(QApplication::translate("MainWindow", "Kp", 0));
        label_10->setText(QApplication::translate("MainWindow", "Ki", 0));
        label_11->setText(QApplication::translate("MainWindow", "Kd", 0));
        label_12->setText(QApplication::translate("MainWindow", "Roll :", 0));
        label_13->setText(QApplication::translate("MainWindow", "Pitch :", 0));
        label_14->setText(QApplication::translate("MainWindow", "Yaw :", 0));
        label_15->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">13</span></p><p><br/></p></body></html>", 0));
        label_16->setText(QApplication::translate("MainWindow", "<html><head/><body><p>2</p><p><br/></p></body></html>", 0));
        label_17->setText(QApplication::translate("MainWindow", "<html><head/><body><p>6</p><p><br/></p></body></html>", 0));
        label_18->setText(QApplication::translate("MainWindow", "Height :", 0));
        label_19->setText(QApplication::translate("MainWindow", "Pressure :", 0));
        label_20->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">15</span></p></body></html>", 0));
        label_21->setText(QApplication::translate("MainWindow", "<html><head/><body><p>98</p><p><br/></p></body></html>", 0));
        label_22->setText(QApplication::translate("MainWindow", "Current Command  :", 0));
        label_23->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:72pt;\">S</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

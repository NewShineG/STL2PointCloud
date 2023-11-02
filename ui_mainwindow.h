/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLabel *label;
    QDoubleSpinBox *stepXSpinBox;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QDoubleSpinBox *stepYSpinBox;
    QLabel *label_5;
    QLabel *label_6;
    QDoubleSpinBox *stepZSpinBox;
    QLabel *label_7;
    QLabel *layerNumLabel;
    QGroupBox *groupBox_2;
    QLabel *label_8;
    QDoubleSpinBox *pitchXSpinBox;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QDoubleSpinBox *pitchYSpinBox;
    QPushButton *readSTLButton;
    QPushButton *toPointCloudButton;
    QPushButton *toTXTButton;
    QPushButton *toBMPButton;
    QCheckBox *initStartCheckBox;
    QCheckBox *rasterCheckBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(517, 470);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(50, 40, 231, 201));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 50, 60, 30));
        stepXSpinBox = new QDoubleSpinBox(groupBox);
        stepXSpinBox->setObjectName(QString::fromUtf8("stepXSpinBox"));
        stepXSpinBox->setGeometry(QRect(90, 50, 70, 30));
        stepXSpinBox->setDecimals(3);
        stepXSpinBox->setSingleStep(0.100000000000000);
        stepXSpinBox->setValue(0.200000000000000);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(160, 50, 30, 30));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(160, 80, 30, 30));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 80, 60, 30));
        stepYSpinBox = new QDoubleSpinBox(groupBox);
        stepYSpinBox->setObjectName(QString::fromUtf8("stepYSpinBox"));
        stepYSpinBox->setGeometry(QRect(90, 80, 70, 30));
        stepYSpinBox->setDecimals(3);
        stepYSpinBox->setSingleStep(0.100000000000000);
        stepYSpinBox->setValue(0.200000000000000);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(160, 110, 30, 30));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 110, 60, 30));
        stepZSpinBox = new QDoubleSpinBox(groupBox);
        stepZSpinBox->setObjectName(QString::fromUtf8("stepZSpinBox"));
        stepZSpinBox->setGeometry(QRect(90, 110, 70, 30));
        stepZSpinBox->setDecimals(3);
        stepZSpinBox->setSingleStep(0.100000000000000);
        stepZSpinBox->setValue(0.200000000000000);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 150, 90, 30));
        layerNumLabel = new QLabel(groupBox);
        layerNumLabel->setObjectName(QString::fromUtf8("layerNumLabel"));
        layerNumLabel->setGeometry(QRect(120, 150, 60, 30));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(50, 260, 231, 141));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 50, 60, 30));
        pitchXSpinBox = new QDoubleSpinBox(groupBox_2);
        pitchXSpinBox->setObjectName(QString::fromUtf8("pitchXSpinBox"));
        pitchXSpinBox->setGeometry(QRect(90, 50, 70, 30));
        pitchXSpinBox->setDecimals(3);
        pitchXSpinBox->setSingleStep(0.001000000000000);
        pitchXSpinBox->setValue(0.114000000000000);
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(160, 50, 30, 30));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(160, 80, 30, 30));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(30, 80, 60, 30));
        pitchYSpinBox = new QDoubleSpinBox(groupBox_2);
        pitchYSpinBox->setObjectName(QString::fromUtf8("pitchYSpinBox"));
        pitchYSpinBox->setGeometry(QRect(90, 80, 70, 30));
        pitchYSpinBox->setDecimals(3);
        pitchYSpinBox->setSingleStep(0.001000000000000);
        pitchYSpinBox->setValue(0.114000000000000);
        readSTLButton = new QPushButton(centralwidget);
        readSTLButton->setObjectName(QString::fromUtf8("readSTLButton"));
        readSTLButton->setGeometry(QRect(320, 80, 90, 30));
        toPointCloudButton = new QPushButton(centralwidget);
        toPointCloudButton->setObjectName(QString::fromUtf8("toPointCloudButton"));
        toPointCloudButton->setGeometry(QRect(320, 120, 90, 30));
        toTXTButton = new QPushButton(centralwidget);
        toTXTButton->setObjectName(QString::fromUtf8("toTXTButton"));
        toTXTButton->setGeometry(QRect(320, 210, 90, 30));
        toBMPButton = new QPushButton(centralwidget);
        toBMPButton->setObjectName(QString::fromUtf8("toBMPButton"));
        toBMPButton->setGeometry(QRect(320, 290, 90, 30));
        initStartCheckBox = new QCheckBox(centralwidget);
        initStartCheckBox->setObjectName(QString::fromUtf8("initStartCheckBox"));
        initStartCheckBox->setGeometry(QRect(320, 180, 90, 30));
        rasterCheckBox = new QCheckBox(centralwidget);
        rasterCheckBox->setObjectName(QString::fromUtf8("rasterCheckBox"));
        rasterCheckBox->setGeometry(QRect(320, 260, 90, 30));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 517, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "STL\347\224\237\346\210\220\347\202\271\344\272\221", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\351\207\207\346\240\267\351\227\264\350\267\235", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "X\346\226\271\345\220\221\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "um", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "um", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Y\346\226\271\345\220\221\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "um", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Z\346\226\271\345\220\221\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\345\210\207\347\211\207\345\261\202\346\225\260\357\274\232", nullptr));
        layerNumLabel->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "BMP\345\203\217\347\264\240", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "X\346\226\271\345\220\221\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "um", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "um", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Y\346\226\271\345\220\221\357\274\232", nullptr));
        readSTLButton->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226STL", nullptr));
        toPointCloudButton->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\347\202\271\344\272\221", nullptr));
        toTXTButton->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\207\272TXT", nullptr));
        toBMPButton->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\207\272BMP", nullptr));
        initStartCheckBox->setText(QCoreApplication::translate("MainWindow", "\347\224\251\347\202\271", nullptr));
        rasterCheckBox->setText(QCoreApplication::translate("MainWindow", "\346\240\205\346\240\274\345\214\226", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

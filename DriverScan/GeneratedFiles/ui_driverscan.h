/********************************************************************************
** Form generated from reading UI file 'driverscan.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRIVERSCAN_H
#define UI_DRIVERSCAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DriverScanClass
{
public:
    QWidget *centralWidget;
    QTextEdit *txtMsg;
    QPushButton *btScan;
    QComboBox *cbxItem;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DriverScanClass)
    {
        if (DriverScanClass->objectName().isEmpty())
            DriverScanClass->setObjectName(QStringLiteral("DriverScanClass"));
        DriverScanClass->resize(600, 502);
        centralWidget = new QWidget(DriverScanClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        txtMsg = new QTextEdit(centralWidget);
        txtMsg->setObjectName(QStringLiteral("txtMsg"));
        txtMsg->setGeometry(QRect(0, 40, 581, 411));
        btScan = new QPushButton(centralWidget);
        btScan->setObjectName(QStringLiteral("btScan"));
        btScan->setGeometry(QRect(10, 10, 75, 23));
        cbxItem = new QComboBox(centralWidget);
        cbxItem->setObjectName(QStringLiteral("cbxItem"));
        cbxItem->setGeometry(QRect(160, 10, 321, 22));
        DriverScanClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DriverScanClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        DriverScanClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DriverScanClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DriverScanClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DriverScanClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DriverScanClass->setStatusBar(statusBar);

        retranslateUi(DriverScanClass);

        QMetaObject::connectSlotsByName(DriverScanClass);
    } // setupUi

    void retranslateUi(QMainWindow *DriverScanClass)
    {
        DriverScanClass->setWindowTitle(QApplication::translate("DriverScanClass", "DriverScan", Q_NULLPTR));
#ifndef QT_NO_ACCESSIBILITY
        btScan->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        btScan->setText(QApplication::translate("DriverScanClass", "\346\211\253\346\217\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DriverScanClass: public Ui_DriverScanClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRIVERSCAN_H

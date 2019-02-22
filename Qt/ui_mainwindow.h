/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *mainVerticalLayout;
    QLabel *regionLabel;
    QHBoxLayout *mainHorizontalLayout;
    QVBoxLayout *regionVerticalLayout;
    QComboBox *regionComboBox;
    QTableWidget *dataTable;
    QVBoxLayout *chartVerticalLayout;
    QLabel *chartInfoLabel;
    QHBoxLayout *chartHorizontalLayout;
    QPushButton *quitPushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1334, 747);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayoutWidget_3 = new QWidget(centralWidget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 10, 1321, 681));
        mainVerticalLayout = new QVBoxLayout(verticalLayoutWidget_3);
        mainVerticalLayout->setSpacing(6);
        mainVerticalLayout->setContentsMargins(11, 11, 11, 11);
        mainVerticalLayout->setObjectName(QString::fromUtf8("mainVerticalLayout"));
        mainVerticalLayout->setContentsMargins(0, 0, 0, 0);
        regionLabel = new QLabel(verticalLayoutWidget_3);
        regionLabel->setObjectName(QString::fromUtf8("regionLabel"));
        QFont font;
        font.setPointSize(20);
        font.setBold(false);
        font.setUnderline(true);
        font.setWeight(50);
        regionLabel->setFont(font);

        mainVerticalLayout->addWidget(regionLabel);

        mainHorizontalLayout = new QHBoxLayout();
        mainHorizontalLayout->setSpacing(6);
        mainHorizontalLayout->setObjectName(QString::fromUtf8("mainHorizontalLayout"));
        regionVerticalLayout = new QVBoxLayout();
        regionVerticalLayout->setSpacing(6);
        regionVerticalLayout->setObjectName(QString::fromUtf8("regionVerticalLayout"));
        regionComboBox = new QComboBox(verticalLayoutWidget_3);
        regionComboBox->setObjectName(QString::fromUtf8("regionComboBox"));

        regionVerticalLayout->addWidget(regionComboBox);

        dataTable = new QTableWidget(verticalLayoutWidget_3);
        if (dataTable->columnCount() < 3)
            dataTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        dataTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        dataTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        dataTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        dataTable->setObjectName(QString::fromUtf8("dataTable"));
        dataTable->setShowGrid(true);
        dataTable->verticalHeader()->setVisible(false);

        regionVerticalLayout->addWidget(dataTable);


        mainHorizontalLayout->addLayout(regionVerticalLayout);

        chartVerticalLayout = new QVBoxLayout();
        chartVerticalLayout->setSpacing(6);
        chartVerticalLayout->setObjectName(QString::fromUtf8("chartVerticalLayout"));
        chartInfoLabel = new QLabel(verticalLayoutWidget_3);
        chartInfoLabel->setObjectName(QString::fromUtf8("chartInfoLabel"));
        QFont font1;
        font1.setPointSize(14);
        chartInfoLabel->setFont(font1);
        chartInfoLabel->setAlignment(Qt::AlignCenter);

        chartVerticalLayout->addWidget(chartInfoLabel);

        chartHorizontalLayout = new QHBoxLayout();
        chartHorizontalLayout->setSpacing(6);
        chartHorizontalLayout->setObjectName(QString::fromUtf8("chartHorizontalLayout"));

        chartVerticalLayout->addLayout(chartHorizontalLayout);


        mainHorizontalLayout->addLayout(chartVerticalLayout);


        mainVerticalLayout->addLayout(mainHorizontalLayout);

        quitPushButton = new QPushButton(verticalLayoutWidget_3);
        quitPushButton->setObjectName(QString::fromUtf8("quitPushButton"));

        mainVerticalLayout->addWidget(quitPushButton);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1334, 17));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        regionLabel->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = dataTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Age", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = dataTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Men", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = dataTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Women", nullptr));
        chartInfoLabel->setText(QString());
        quitPushButton->setText(QApplication::translate("MainWindow", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

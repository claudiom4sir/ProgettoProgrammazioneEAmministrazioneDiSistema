#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QString>
#include <QStringList>
#include <QtCharts>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), menChart(nullptr), womenChart(nullptr) {
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->mainVerticalLayout);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->dataTable->setSelectionMode(QAbstractItemView::NoSelection);
    fillData();
    setConnects();
    fillRegionComboBox();
    createCharts();
    //setRegionLabel(ui->regionComboBox->currentText().toUpper());
    fillCharts(ui->regionComboBox->currentText());
}

void MainWindow::setConnects() {
    connect(ui->regionComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(setRegionLabel(QString)));
    connect(ui->quitPushButton, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
    connect(ui->regionComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(fillTableWithDataOfRegion(QString)));
    connect(ui->regionComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(fillCharts(QString)));
}

void MainWindow::fillRegionComboBox() {
    ui->regionComboBox->addItems(extractRegionListFromData());
}

void MainWindow::setRegionLabel(const QString& region) {
    ui->regionLabel->setAlignment(Qt::AlignCenter);
    ui->regionLabel->setText(region.toUpper());
}

void MainWindow::createCharts() {
    menChart = new QChart;
    menChart->setTitle("Men");
    menChart->legend()->setAlignment(Qt::AlignRight);
    menChart->setToolTip("Click on the pie's slices to show the percentage");

    womenChart = new QChart;
    womenChart->setTitle("Women");
    womenChart->legend()->setAlignment(Qt::AlignRight);
    womenChart->setToolTip("Click on the pie's slices to show the percentage");

    QChartView* menChartView = new QChartView(menChart);
    QChartView* womenChartView = new QChartView(womenChart);

    ui->chartHorizontalLayout->layout()->addWidget(menChartView);
    ui->chartHorizontalLayout->layout()->addWidget(womenChartView);
}

void MainWindow::fillCharts(const QString& region) {
    if(menChart != nullptr && womenChart != nullptr) {
        QPieSeries* menSeries = new QPieSeries;
        QPieSeries* womenSeries = new QPieSeries;
        int numberOfMen = 0;
        int numberOfWomen = 0;

        for(int i = 0; i < data.length(); ++i) {
            QStringList row = data[i].split(" ");
            if(row[regionIndex] == region) {
                numberOfMen += row[menIndex].toInt();
                numberOfWomen += row[womenIndex].toInt();
            }
        }

        for(int i = 0, j = 0; i < data.length(); ++i) {
            QStringList row = data[i].split(" ");
            if(row[regionIndex] == region) {
                menSeries->append(QString::number(i + 1), row[menIndex].toDouble() / numberOfMen);
                womenSeries->append(QString::number(i + 1), row[womenIndex].toDouble() / numberOfWomen);

                QPieSlice *sliceMen = menSeries->slices().at(j);
                QPieSlice *sliceWomen = womenSeries->slices().at(j);

                sliceMen->setLabel("[" + row[ageIndex] + "]");
                sliceWomen->setLabel("[" + row[ageIndex] + "]");

                ++j;
            }
        }

        menSeries->setLabelsPosition(QPieSlice::LabelOutside);
        womenSeries->setLabelsPosition(QPieSlice::LabelOutside);

        connect(menSeries, SIGNAL(pressed(QPieSlice*)), this, SLOT(showSliceInfo(QPieSlice*)));
        connect(menSeries, SIGNAL(released(QPieSlice*)), this, SLOT(hideSliceInfo(QPieSlice*)));
        connect(womenSeries, SIGNAL(pressed(QPieSlice*)), this, SLOT(showSliceInfo(QPieSlice*)));
        connect(womenSeries, SIGNAL(released(QPieSlice*)), this, SLOT(hideSliceInfo(QPieSlice*)));

        disconnectSeriesSlots();

        menChart->removeAllSeries();
        womenChart->removeAllSeries();
        menChart->addSeries(menSeries);
        womenChart->addSeries(womenSeries);
    }
}

void MainWindow::disconnectSeriesSlots() {
    for(int i = 0; i < menChart->series().size(); ++i) {
        disconnect(menChart->series().at(i), SIGNAL(pressed(QPieSlice*)), this, SLOT(showSliceInfo(QPieSlice*)));
        disconnect(menChart->series().at(i), SIGNAL(released(QPieSlice*)), this, SLOT(hideSliceInfo(QPieSlice*)));
    }

    for(int i = 0; i < womenChart->series().size(); ++i) {
        disconnect(womenChart->series().at(i), SIGNAL(pressed(QPieSlice*)), this, SLOT(showSliceInfo(QPieSlice*)));
        disconnect(womenChart->series().at(i), SIGNAL(released(QPieSlice*)), this, SLOT(hideSliceInfo(QPieSlice*)));
    }
}

void MainWindow::showSliceInfo(QPieSlice* slice) {
    slice->setExploded(true);
    ui->chartInfoLabel->setText(QString::number(slice->percentage() * 100, 'f', 3) + "%");
}

void MainWindow::hideSliceInfo(QPieSlice* slice) {
    slice->setExploded(false);
    ui->chartInfoLabel->setText("");
}

void MainWindow::fillTableWithDataOfRegion(const QString& region) {

    while(ui->dataTable->rowCount() > 0)
        ui->dataTable->removeRow(0);

    int numberOfRow = 0;
    int numberOfMen = 0;
    int numberOfWomen = 0;

    for(int i = 0; i < data.length(); ++i) {
        QStringList row = data[i].split(" ");
        if(row[regionIndex] == region) {
            ui->dataTable->insertRow(numberOfRow);
            ui->dataTable->setItem(numberOfRow, 0, new QTableWidgetItem(row[ageIndex]));
            ui->dataTable->setItem(numberOfRow, 1, new QTableWidgetItem(row[menIndex]));
            ui->dataTable->setItem(numberOfRow, 2, new QTableWidgetItem(row[womenIndex]));

            numberOfMen += row[menIndex].toInt();
            numberOfWomen += row[womenIndex].toInt();
            ++numberOfRow;
        }
    }
    ui->dataTable->insertRow(numberOfRow);
    ui->dataTable->setItem(numberOfRow, 0, new QTableWidgetItem("TOTAL"));
    ui->dataTable->setItem(numberOfRow, 1, new QTableWidgetItem(QString::number(numberOfMen)));
    ui->dataTable->setItem(numberOfRow, 2, new QTableWidgetItem(QString::number(numberOfWomen)));
    ui->dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers); // this make the rows not editable
}

QStringList MainWindow::extractRegionListFromData() {
    QStringList regionList;
    for(int i = 0; i < data.length(); ++i) {
        QStringList row = data[i].split(" ");
        if(!regionList.contains(row[regionIndex]))
            regionList.append(row[regionIndex]);
    }
    return  regionList;
}

void MainWindow::fillData() {
    data = readFile();
}

QStringList MainWindow::readFile() {
    QStringList result;
    QFile file("data.txt");
    file.open(QIODevice::ReadOnly);
    if(file.isOpen()) {
        QTextStream stream(&file);
        while(!stream.atEnd()) {
            QString str = stream.readLine();
            if(str != "<END>")
                result.append(str);
        }
    }
    file.close();
    return result;
}

MainWindow::~MainWindow() {
    delete ui;
}

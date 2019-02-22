#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QtCharts>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    QtCharts::QChart* menChart;
    QtCharts::QChart* womenChart;
    const int regionIndex = 0;
    const int ageIndex = 1;
    const int menIndex = 2;
    const int womenIndex = 3;
    QStringList data;
    void fillData();
    void fillRegionComboBox();
    void setConnects();
    QStringList readFile();
    QStringList extractRegionListFromData();
    void createCharts();
    void disconnectSeriesSlots();

private slots:
    void setRegionLabel(const QString& region);
    void fillTableWithDataOfRegion(const QString& region);
    void fillCharts(const QString& region);
    void showSliceInfo(QPieSlice* slice);
    void hideSliceInfo(QPieSlice* slice);
};

#endif // MAINWINDOW_H

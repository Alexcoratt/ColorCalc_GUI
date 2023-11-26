#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <IConfigManager.hpp>

#include <PaintConsumptionDataManager.hpp>
#include <PaintDataManager.hpp>
#include <LacquerDataManager.hpp>
#include <FoilDataManager.hpp>
#include <FoilRollsDataManager.hpp>

#include "PaintCalculationTab.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_pcCalculateButton_clicked();
    void paintCalculationDataChanged();

private:
    Ui::MainWindow *ui;

    IConfigManager * _configManager;

    PaintConsumptionDataManager * _paintConsumptionDataManager;
    PaintDataManager * _paintDataManager;
    LacquerDataManager * _lacquerDataManager;
    FoilDataManager * _foilDataManager;
    FoilRollsDataManager * _foilRollsDataManager;

    PaintCalculationTab * _paintCalculationTab;
};
#endif // MAINWINDOW_H

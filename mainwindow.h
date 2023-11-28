#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <IConfigManager.hpp>

#include <PaintConsumptionDataManager.hpp>
#include <PaintDataManager.hpp>
#include <LacquerDataManager.hpp>
#include <FoilDataManager.hpp>
#include <FoilRollsDataManager.hpp>

#include "paintcalculationtab.h"
#include "lacquercalculationtab.h"
#include "foilcalculationtab.h"
#include "foilrollstab.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(IConfigManager * configManager, QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;

    IConfigManager * _configManager;

    PaintConsumptionDataManager * _paintConsumptionDataManager;
    PaintDataManager * _paintDataManager;
    LacquerDataManager * _lacquerDataManager;
    FoilDataManager * _foilDataManager;
    FoilRollsDataManager * _foilRollsDataManager;

    PaintCalculationTab * _paintCalculationTab;
    LacquerCalculationTab * _lacquerCalculationTab;
    FoilCalculationTab * _foilCalculationTab;
    FoilRollsTab * _foilRollsTab;
};
#endif // MAINWINDOW_H

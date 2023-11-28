#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>

#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>

#include "presetcreationpopup.h"
#include "presetupdatepopup.h"
#include "presetremovalpopup.h"

#include <JSONConfigManager.hpp>

void exceptionHandler(std::exception const & err, std::string const & text) {
    std::cerr << err.what() << std::endl;
    QMessageBox messageBox;
    messageBox.setText(QString::fromStdString(text));
    messageBox.setWindowTitle("Ошибка");
    messageBox.exec();
}

void openPresetCreationPopUp(ITab * tab) {
    PresetCreationPopUp popUp(tab, exceptionHandler);
    popUp.exec();
}

void openPresetUpdatePopUp(ITab * tab) {
    PresetUpdatePopUp popUp(tab, exceptionHandler);
    popUp.exec();
}

void openPresetRemovalPopUp(ITab * tab) {
    PresetRemovalPopUp popUp(tab, exceptionHandler);
    popUp.exec();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _configManager = new JSONConfigManager{ "/home/alexsm/LinuxFiles/Workshop/projects/ColorCalc/data/config.json", false };
    auto connections = _configManager->getConnections();

    _paintConsumptionDataManager = new PaintConsumptionDataManager{connections.at("paint_consumption")};
    _paintDataManager = new PaintDataManager{connections.at("paint_calculation"), _paintConsumptionDataManager};
    _lacquerDataManager = new LacquerDataManager{connections.at("lacquer_calculation")};
    _foilRollsDataManager = new FoilRollsDataManager{connections.at("foil_rolls")};
    _foilDataManager = new FoilDataManager{connections.at("foil_calculation"), _foilRollsDataManager};

    // setting up paint calculation tab
    _paintCalculationTab = new PaintCalculationTab(_paintDataManager);

    ui->paintPresetField->set(_paintCalculationTab->getPresetName(), "Имя пресета");
    ui->paintTypeField->set(_paintCalculationTab->getPaintType(), "Тип краски");
    ui->materialTypeField->set(_paintCalculationTab->getMaterialType(), "Тип материала");

    ui->pcConsumptionField->set(_paintCalculationTab->getPaintConsumption(), "Расход краски", "г/м2");
    ui->pcDividerField->set(_paintCalculationTab->getDivider(), "Делитель");
    ui->pcPercentageField->set(_paintCalculationTab->getPercent(), "Процент запечатки", "%");
    ui->pcSheetWidthField->set(_paintCalculationTab->getSheetWidth(), "Ширина печатного листа", "мм");
    ui->pcSheetLengthField->set(_paintCalculationTab->getSheetLength(), "Длина печатного листа", "мм");
    ui->pcCirculationField->set(_paintCalculationTab->getCirculation(), "Тираж");
    ui->pcPaintReserveField->set(_paintCalculationTab->getPaintReserve(), "Запас краски", "кг");
    ui->pcResultField->set(_paintCalculationTab->getResult(), "Объем краски", "кг");

    connect(ui->pcCalculateButton, &QPushButton::clicked, _paintCalculationTab, &PaintCalculationTab::calculate);
    connect(ui->pcClearFieldsButton, &QPushButton::clicked, _paintCalculationTab, &PaintCalculationTab::clear);

    connect(ui->pcCreatePresetButton, &QPushButton::clicked, [&]() { openPresetCreationPopUp(_paintCalculationTab); });
    connect(ui->pcUpdatePresetButton, &QPushButton::clicked, [&]() { openPresetUpdatePopUp(_paintCalculationTab); });
    connect(ui->pcRemovePresetButton, &QPushButton::clicked, [&]() { openPresetRemovalPopUp(_paintCalculationTab); });

    // setting up lacquer calculation tab
    _lacquerCalculationTab = new LacquerCalculationTab(_lacquerDataManager);

    ui->lacquerPresetField->set(_lacquerCalculationTab->getPresetName(), "Имя пресета");

    ui->lcConsumptionField->set(_lacquerCalculationTab->getLacquerConsumption(), "Расход краски", "г/м2");
    ui->lcPercentageField->set(_lacquerCalculationTab->getPercentage(), "Процент заливки", "%");
    ui->lcSheetWidthField->set(_lacquerCalculationTab->getSheetWidth(), "Ширина печатного листа", "мм");
    ui->lcSheetLengthField->set(_lacquerCalculationTab->getSheetLength(), "Длина печатного листа", "мм");
    ui->lcCirculationField->set(_lacquerCalculationTab->getCirculation(), "Тираж");
    ui->lcResultField->set(_lacquerCalculationTab->getResult(), "Объем лака", "кг");

    connect(ui->lcCalculateButton, &QPushButton::clicked, _lacquerCalculationTab, &LacquerCalculationTab::calculate);
    connect(ui->lcClearFieldsButton, &QPushButton::clicked, _lacquerCalculationTab, &LacquerCalculationTab::clear);

    connect(ui->lcCreatePresetButton, &QPushButton::clicked, [&]() { openPresetCreationPopUp(_lacquerCalculationTab); });
    connect(ui->lcUpdatePresetButton, &QPushButton::clicked, [&]() { openPresetUpdatePopUp(_lacquerCalculationTab); });
    connect(ui->lcRemovePresetButton, &QPushButton::clicked, [&]() { openPresetRemovalPopUp(_lacquerCalculationTab); });

    // setting up foil calculation tab
    _foilCalculationTab = new FoilCalculationTab(_foilDataManager);

    ui->foilPresetField->set(_foilCalculationTab->getPresetName(), "Имя пресета");

    ui->fcLengthField->set(_foilCalculationTab->getLength(), "Длина клише", "мм");
    ui->fcLengthReserveField->set(_foilCalculationTab->getLengthReserve(), "Запас по длине", "мм");
    ui->fcWidthField->set(_foilCalculationTab->getWidth(), "Ширина клише", "мм");
    ui->fcWidthReserveField->set(_foilCalculationTab->getWidthReserve(), "Запас по ширине", "мм");
    ui->fcSheetNumberField->set(_foilCalculationTab->getSheetNumber(), "Число печатных листов");
    ui->fcCirculationField->set(_foilCalculationTab->getCirculation(), "Тираж");
    ui->fcResultField->set(_foilCalculationTab->getResult(), "Погонные метры", "м");

    connect(ui->fcCalculateButton, &QPushButton::clicked, _foilCalculationTab, &FoilCalculationTab::calculate);
    connect(ui->fcClearFieldsButton, &QPushButton::clicked, _foilCalculationTab, &FoilCalculationTab::clear);

    connect(ui->fcCreatePresetButton, &QPushButton::clicked, [&]() { openPresetCreationPopUp(_foilCalculationTab); });
    connect(ui->fcUpdatePresetButton, &QPushButton::clicked, [&]() { openPresetUpdatePopUp(_foilCalculationTab); });
    connect(ui->fcRemovePresetButton, &QPushButton::clicked, [&]() { openPresetRemovalPopUp(_foilCalculationTab); });
}

MainWindow::~MainWindow()
{
    delete ui;

    delete _configManager;

    delete _paintConsumptionDataManager;
    delete _paintDataManager;
    delete _lacquerDataManager;
    delete _foilDataManager;
    delete _foilRollsDataManager;

    delete _paintCalculationTab;
}


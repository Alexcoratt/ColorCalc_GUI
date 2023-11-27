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

    _paintCalculationTab = new PaintCalculationTab(_paintDataManager);

    // setting up paint calculation tab
    ui->paintPresetField->set(_paintCalculationTab->getPresetName(), "Имя пресета");

    //connect(paintCalculationPresetComboBox.get(), &QComboBox::currentTextChanged, this, &MainWindow::on_pcCalculateButton_clicked);
    ui->paintTypeField->set(_paintCalculationTab->getPaintType(), "Тип краски");
    ui->materialTypeField->set(_paintCalculationTab->getMaterialType(), "Тип материала");

    ui->paintConsumptionField->set(_paintCalculationTab->getPaintConsumption(), "Расход краски", "г/м2");
    ui->dividerField->set(_paintCalculationTab->getDivider(), "Делитель");
    ui->percentageField->set(_paintCalculationTab->getPercent(), "Процент запечатки", "%");
    ui->sheetWidthField->set(_paintCalculationTab->getSheetWidth(), "Ширина печатного листа", "мм");
    ui->sheetLengthField->set(_paintCalculationTab->getSheetLength(), "Длина печатного листа", "мм");
    ui->circulationField->set(_paintCalculationTab->getCirculation(), "Тираж");
    ui->paintReserveField->set(_paintCalculationTab->getPaintReserve(), "Запас краски", "кг");
    ui->pcResultField->set(_paintCalculationTab->getResult(), "Результат вычислений", "кг");

    connect(ui->pcCalculateButton, &QPushButton::clicked, _paintCalculationTab, &PaintCalculationTab::calculate);
    connect(ui->pcClearFieldsButton, &QPushButton::clicked, _paintCalculationTab, &PaintCalculationTab::clear);

    connect(ui->pcCreatePresetButton, &QPushButton::clicked, [&]() { openPresetCreationPopUp(_paintCalculationTab); });
    connect(ui->pcUpdatePresetButton, &QPushButton::clicked, [&]() { openPresetUpdatePopUp(_paintCalculationTab); });
    connect(ui->pcRemovePresetButton, &QPushButton::clicked, [&]() { openPresetRemovalPopUp(_paintCalculationTab); });
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


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

void setNamedField(NamedField * nf, QWidget * widget, QString const & name, QString const & units = "", bool helpButtonVisible = false, QString const & helpText = "") {
    nf->setWidget(widget);
    nf->setName(name);
    nf->setUnits(units);
    nf->setHelpButtonVisible(helpButtonVisible);
    nf->setHelpText(helpText);
}

void setNamedField(NamedField * nf, QWidget * widget, QString const & name, bool helpButtonVisible, QString const & helpText) {
    setNamedField(nf, widget, name, "", helpButtonVisible, helpText);
}

MainWindow::MainWindow(IConfigManager * configManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _configManager = configManager;
    auto connections = _configManager->getConnections();

    _paintConsumptionDataManager = new PaintConsumptionDataManager{connections.at("paint_consumption")};
    _paintDataManager = new PaintDataManager{connections.at("paint_calculation"), _paintConsumptionDataManager};
    _lacquerDataManager = new LacquerDataManager{connections.at("lacquer_calculation")};
    _foilRollsDataManager = new FoilRollsDataManager{connections.at("foil_rolls")};
    _foilDataManager = new FoilDataManager{connections.at("foil_calculation"), _foilRollsDataManager};

    // setting up paint calculation tab
    _paintCalculationTab = new PaintCalculationTab(_paintDataManager);

    setNamedField(ui->paintPresetField, _paintCalculationTab->getPresetName(), "Тип изображения", true, "Тип изображения к запечатке");
    setNamedField(ui->paintTypeField, _paintCalculationTab->getPaintType(), "Тип краски");
    setNamedField(ui->materialTypeField, _paintCalculationTab->getMaterialType(), "Тип материала");

    setNamedField(ui->pcConsumptionField, _paintCalculationTab->getPaintConsumption(), "Расход краски", "г/м2");
    setNamedField(ui->pcDividerField, _paintCalculationTab->getDivider(), "Поправочный коэффициент", true, "Поправочный коэффициент (делитель), присутствующий в формуле");
    setNamedField(ui->pcPercentageField, _paintCalculationTab->getPercent(), "Процент запечатки", "%");
    setNamedField(ui->pcSheetWidthField, _paintCalculationTab->getSheetWidth(), "Ширина печатного листа", "мм");
    setNamedField(ui->pcSheetLengthField, _paintCalculationTab->getSheetLength(), "Длина печатного листа", "мм");
    setNamedField(ui->pcCirculationField, _paintCalculationTab->getCirculation(), "Тираж");
    setNamedField(ui->pcPaintReserveField, _paintCalculationTab->getPaintReserve(), "Запас краски", "кг");
    setNamedField(ui->pcResultField, _paintCalculationTab->getResult(), "Объем краски", "кг");

    connect(ui->pcCalculateButton, &QPushButton::clicked, _paintCalculationTab, &PaintCalculationTab::calculate);
    connect(ui->pcClearFieldsButton, &QPushButton::clicked, _paintCalculationTab, &PaintCalculationTab::clear);

    connect(ui->pcCreatePresetButton, &QPushButton::clicked, [&]() { openPresetCreationPopUp(_paintCalculationTab); });
    connect(ui->pcUpdatePresetButton, &QPushButton::clicked, [&]() { openPresetUpdatePopUp(_paintCalculationTab); });
    connect(ui->pcRemovePresetButton, &QPushButton::clicked, [&]() { openPresetRemovalPopUp(_paintCalculationTab); });

    // setting up lacquer calculation tab
    _lacquerCalculationTab = new LacquerCalculationTab(_lacquerDataManager);

    setNamedField(ui->lacquerPresetField, _lacquerCalculationTab->getPresetName(), "Имя пресета", true, "Пресет - заранее составленный набор значений");

    setNamedField(ui->lcConsumptionField, _lacquerCalculationTab->getLacquerConsumption(), "Расход краски", "г/м2");
    setNamedField(ui->lcPercentageField, _lacquerCalculationTab->getPercentage(), "Процент заливки", "%");
    setNamedField(ui->lcSheetWidthField, _lacquerCalculationTab->getSheetWidth(), "Ширина печатного листа", "мм");
    setNamedField(ui->lcSheetLengthField, _lacquerCalculationTab->getSheetLength(), "Длина печатного листа", "мм");
    setNamedField(ui->lcCirculationField, _lacquerCalculationTab->getCirculation(), "Тираж");
    setNamedField(ui->lcResultField, _lacquerCalculationTab->getResult(), "Объем лака", "кг");

    connect(ui->lcCalculateButton, &QPushButton::clicked, _lacquerCalculationTab, &LacquerCalculationTab::calculate);
    connect(ui->lcClearFieldsButton, &QPushButton::clicked, _lacquerCalculationTab, &LacquerCalculationTab::clear);

    connect(ui->lcCreatePresetButton, &QPushButton::clicked, [&]() { openPresetCreationPopUp(_lacquerCalculationTab); });
    connect(ui->lcUpdatePresetButton, &QPushButton::clicked, [&]() { openPresetUpdatePopUp(_lacquerCalculationTab); });
    connect(ui->lcRemovePresetButton, &QPushButton::clicked, [&]() { openPresetRemovalPopUp(_lacquerCalculationTab); });

    // setting up foil calculation tab
    _foilCalculationTab = new FoilCalculationTab(_foilDataManager);

    setNamedField(ui->foilPresetField, _foilCalculationTab->getPresetName(), "Имя пресета", true, "Пресет - заранее составленный набор значений");

    setNamedField(ui->fcLengthField, _foilCalculationTab->getLength(), "Длина клише", "мм");
    setNamedField(ui->fcLengthReserveField, _foilCalculationTab->getLengthReserve(), "Запас по длине", "мм");
    setNamedField(ui->fcWidthField, _foilCalculationTab->getWidth(), "Ширина клише", "мм");
    setNamedField(ui->fcWidthReserveField, _foilCalculationTab->getWidthReserve(), "Запас по ширине", "мм");
    setNamedField(ui->fcSheetNumberField, _foilCalculationTab->getSheetNumber(), "Число печатных листов");
    setNamedField(ui->fcCirculationField, _foilCalculationTab->getCirculation(), "Тираж");
    setNamedField(ui->fcResultField, _foilCalculationTab->getResult(), "Погонные метры", "м");

    connect(ui->fcCalculateButton, &QPushButton::clicked, _foilCalculationTab, &FoilCalculationTab::calculate);
    connect(ui->fcClearFieldsButton, &QPushButton::clicked, _foilCalculationTab, &FoilCalculationTab::clear);

    connect(ui->fcCreatePresetButton, &QPushButton::clicked, [&]() { openPresetCreationPopUp(_foilCalculationTab); });
    connect(ui->fcUpdatePresetButton, &QPushButton::clicked, [&]() { openPresetUpdatePopUp(_foilCalculationTab); });
    connect(ui->fcRemovePresetButton, &QPushButton::clicked, [&]() { openPresetRemovalPopUp(_foilCalculationTab); });

    // setting up foil rolls tab
    _foilRollsTab = new FoilRollsTab(_foilRollsDataManager, _foilDataManager);

    setNamedField(ui->foilRollsPresetField, _foilRollsTab->getPresetName(), "Название рулона");

    setNamedField(ui->frLengthField, _foilRollsTab->getLength(), "Погонные метры", "м");
    setNamedField(ui->frWidthField, _foilRollsTab->getWidth(), "Ширина", "мм");

    setNamedField(ui->frSuitableRollsField, _foilRollsTab->getSuitableFoilRolls(), "Рулоны, подходящие под заданные параметры клише");

    connect(ui->frFindSuitableRollsButton, &QPushButton::clicked, _foilRollsTab, &FoilRollsTab::findSuitableRolls);
    connect(ui->frClearFieldsButton, &QPushButton::clicked, _foilRollsTab, &FoilRollsTab::clear);

    connect(ui->frCreatePresetButton, &QPushButton::clicked, [&]() { openPresetCreationPopUp(_foilRollsTab); });
    connect(ui->frUpdatePresetButton, &QPushButton::clicked, [&]() { openPresetUpdatePopUp(_foilRollsTab); });
    connect(ui->frRemovePresetButton, &QPushButton::clicked, [&]() { openPresetRemovalPopUp(_foilRollsTab); });
}

MainWindow::~MainWindow()
{
    delete ui;

    delete _paintConsumptionDataManager;
    delete _paintDataManager;
    delete _lacquerDataManager;
    delete _foilDataManager;
    delete _foilRollsDataManager;

    delete _paintCalculationTab;
}


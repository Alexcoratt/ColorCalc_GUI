#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>

#include <QLineEdit>
#include <QComboBox>

#include <JSONConfigManager.hpp>

#define LINE_EDIT_PLACEHOLDER "Введите значение"
#define COMBO_BOX_PLACEHOLDER "Не выбрано"

std::shared_ptr<QLineEdit> getLineEdit(QString const & placeholder = LINE_EDIT_PLACEHOLDER, bool readOnly = false) {
    std::shared_ptr<QLineEdit> lineEdit{ new QLineEdit };
    lineEdit->setPlaceholderText(placeholder);
    lineEdit->setReadOnly(readOnly);
    return lineEdit;
}

std::shared_ptr<QLineEdit> getLineEdit(bool readOnly) {
    return getLineEdit(LINE_EDIT_PLACEHOLDER, readOnly);
}

std::shared_ptr<QComboBox> getComboBox(QString const & placeholder = COMBO_BOX_PLACEHOLDER) {
    std::shared_ptr<QComboBox> comboBox{ new QComboBox };
    comboBox->setPlaceholderText(placeholder);
    return comboBox;
}

void fillComboBox(QComboBox & comboBox, std::vector<std::string> const & options) {
    for (auto const & option : options)
        comboBox.addItem(option.c_str());
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::shared_ptr<JSONConfigManager> jsonConfigManager{ new JSONConfigManager{"/home/alexsm/LinuxFiles/Workshop/projects/ColorCalc/data/config.json", false } };
    auto connections = jsonConfigManager->getConnections();

    _paintConsumptionDataManager = new PaintConsumptionDataManager{connections.at("paint_consumption")};
    _paintDataManager = new PaintDataManager{connections.at("paint_calculation"), _paintConsumptionDataManager};
    _lacquerDataManager = new LacquerDataManager{connections.at("lacquer_calculation")};
    _foilRollsDataManager = new FoilRollsDataManager{connections.at("foil_rolls")};
    _foilDataManager = new FoilDataManager{connections.at("foil_calculation"), _foilRollsDataManager};

    // setting up paint calculation tab
    auto paintCalculationPresetComboBox = getComboBox();
    fillComboBox(*paintCalculationPresetComboBox, _paintDataManager->getConnection()->getPresetNames());
    ui->paintPresetField->set(paintCalculationPresetComboBox, "Имя пресета");

    //connect(paintCalculationPresetComboBox.get(), &QComboBox::currentTextChanged, this, &MainWindow::on_pcCalculateButton_clicked);

    auto paintTypeComboBox = getComboBox();
    fillComboBox(*paintTypeComboBox, _paintDataManager->getPaintTypes());
    ui->paintTypeField->set(paintTypeComboBox, "Тип краски");

    auto materialTypeComboBox = getComboBox();
    fillComboBox(*materialTypeComboBox, _paintDataManager->getMaterialTypes());
    ui->materialTypeField->set(materialTypeComboBox, "Тип материала");

    ui->paintConsumptionField->set(getLineEdit(), "Расход краски", "г/м2");
    ui->dividerField->set(getLineEdit(), "Делитель");
    ui->percentageField->set(getLineEdit(), "Процент запечатки", "%");
    ui->sheetWidthField->set(getLineEdit(), "Ширина печатного листа", "мм");
    ui->sheetLengthField->set(getLineEdit(), "Длина печатного листа", "мм");
    ui->circulationField->set(getLineEdit(), "Тираж");
    ui->paintReserveField->set(getLineEdit(), "Запас краски", "кг");

    ui->pcResultField->set(getLineEdit("", true), "Результат вычислений", "кг");
}

MainWindow::~MainWindow()
{
    delete ui;

    delete _paintConsumptionDataManager;
    delete _paintDataManager;
    delete _lacquerDataManager;
    delete _foilDataManager;
    delete _foilRollsDataManager;
}

void MainWindow::on_pcCalculateButton_clicked()
{
    std::cout << "clicked!\n";
}


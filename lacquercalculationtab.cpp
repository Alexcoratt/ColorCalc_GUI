#include "lacquercalculationtab.h"
#include "common_methods.h"

namespace cm = common_methods;

LacquerCalculationTab::LacquerCalculationTab(LacquerDataManager * manager)
{
    _lacquerDataManager = manager;

    _presetName = cm::getComboBox(_lacquerDataManager->getConnection()->getPresetNames());
    connect(_presetName, &QComboBox::currentTextChanged, this, &LacquerCalculationTab::loadPreset);

    _lacquerConsumption = cm::getLineEdit();
    connect(_lacquerConsumption, &QLineEdit::editingFinished, this, &LacquerCalculationTab::uploadLacquerConsumption);

    _percentage = cm::getLineEdit();
    connect(_percentage, &QLineEdit::editingFinished, this, &LacquerCalculationTab::uploadPercentage);

    _sheetWidth = cm::getLineEdit();
    connect(_sheetWidth, &QLineEdit::editingFinished, this, &LacquerCalculationTab::uploadSheetWidth);

    _sheetLength = cm::getLineEdit();
    connect(_sheetLength, &QLineEdit::editingFinished, this, &LacquerCalculationTab::uploadSheetLength);

    _circulation = cm::getLineEdit();
    connect(_circulation, &QLineEdit::editingFinished, this, &LacquerCalculationTab::uploadCirculation);

    _result = cm::getLineEdit("Расчет не выполнен", true);
}

LacquerCalculationTab::~LacquerCalculationTab() {
    delete _presetName;
    delete _lacquerConsumption;
    delete _percentage;
    delete _sheetWidth;
    delete _sheetLength;
    delete _circulation;
    delete _result;
}

LacquerDataManager const * LacquerCalculationTab::getDataManager() const { return _lacquerDataManager; }
LacquerDataManager * LacquerCalculationTab::getDataManager() { return _lacquerDataManager; }

QComboBox const * LacquerCalculationTab::getPresetName() const { return _presetName; }
QComboBox * LacquerCalculationTab::getPresetName() { return _presetName; }

QLineEdit const * LacquerCalculationTab::getLacquerConsumption() const { return _lacquerConsumption; }
QLineEdit * LacquerCalculationTab::getLacquerConsumption() { return _lacquerConsumption; }

QLineEdit const * LacquerCalculationTab::getPercentage() const { return _percentage; }
QLineEdit * LacquerCalculationTab::getPercentage() { return _percentage; }

QLineEdit const * LacquerCalculationTab::getSheetWidth() const { return _sheetWidth; }
QLineEdit * LacquerCalculationTab::getSheetWidth() { return _sheetWidth; }

QLineEdit const * LacquerCalculationTab::getSheetLength() const { return _sheetLength; }
QLineEdit * LacquerCalculationTab::getSheetLength() { return _sheetLength; }

QLineEdit const * LacquerCalculationTab::getCirculation() const { return _circulation; }
QLineEdit * LacquerCalculationTab::getCirculation() { return _circulation; }

QLineEdit const * LacquerCalculationTab::getResult() const { return _result; }
QLineEdit * LacquerCalculationTab::getResult() { return _result; }

// public slots
void LacquerCalculationTab::update() {
    cm::fillComboBox(_presetName, _lacquerDataManager->getConnection()->getPresetNames());
    cm::setComboBoxIndex(_presetName, [&]() { return _lacquerDataManager->getName(); });

    cm::setLineEditValue<double>(_lacquerConsumption, [&]() { return _lacquerDataManager->getLacquerConsumption(); });
    cm::setLineEditValue<double>(_percentage, [&]() { return _lacquerDataManager->getPercentage(); });
    cm::setLineEditValue<double>(_sheetWidth, [&]() { return _lacquerDataManager->getSheetWidth(); });
    cm::setLineEditValue<double>(_sheetLength, [&]() { return _lacquerDataManager->getSheetLength(); });
    cm::setLineEditValue<std::size_t>(_circulation, [&]() { return _lacquerDataManager->getCirculation(); });

    calculate();

    std::cout << "LacquerCalculationTab: updated" << std::endl;
}

void LacquerCalculationTab::calculate() {
    try {
        _result->setText(QString::fromStdString(cm::toString(_lacquerDataManager->calculate())));
    } catch (std::exception const & err) {
        _result->clear();
        std::cerr << err.what() << std::endl;
    }

    cm::markError(_lacquerConsumption);
    cm::markError(_percentage);
    cm::markError(_sheetWidth);
    cm::markError(_sheetLength);
    cm::markError(_circulation);
}

// private slots
void LacquerCalculationTab::uploadLacquerConsumption() {
    std::cout << "LacquerCalculationTab: uploading lacquer consumption\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _lacquerDataManager->setLacquerConsumption(value); },
        [&]() { _lacquerDataManager->clearLacquerConsumption(); },
        _lacquerConsumption->text(),
        cm::toDouble
    );
    update();
}

void LacquerCalculationTab::uploadPercentage() {
    std::cout << "LacquerCalculationTab: uploading percentage\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _lacquerDataManager->setPercentage(value); },
        [&]() { _lacquerDataManager->clearPercentage(); },
        _percentage->text(),
        cm::toDouble
    );
    update();
}

void LacquerCalculationTab::uploadSheetWidth() {
    std::cout << "LacquerCalculationTab: uploading sheet width\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _lacquerDataManager->setSheetWidth(value); },
        [&]() { _lacquerDataManager->clearSheetWidth(); },
        _sheetWidth->text(),
        cm::toDouble
    );
    update();
}

void LacquerCalculationTab::uploadSheetLength() {
    std::cout << "LacquerCalculationTab: uploading sheet length\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _lacquerDataManager->setSheetLength(value); },
        [&]() { _lacquerDataManager->clearSheetLength(); },
        _sheetLength->text(),
        cm::toDouble
    );
    update();
}

void LacquerCalculationTab::uploadCirculation() {
    std::cout << "LacquerCalculationTab: uploading circulation\t";
    cm::setManagerParam<std::size_t, QString>(
        [&](std::size_t value) { _lacquerDataManager->setCirculation(value); },
        [&]() { _lacquerDataManager->clearCirculation(); },
        _circulation->text(),
        cm::toULong
    );
    update();
}

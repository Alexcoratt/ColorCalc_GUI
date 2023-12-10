#include "foilcalculationtab.h"
#include "common_methods.h"

namespace cm = common_methods;

FoilCalculationTab::FoilCalculationTab(FoilDataManager * manager)
{
    _foilDataManager = manager;

    _presetName = cm::getComboBox(_foilDataManager->getConnection()->getPresetNames());
    connect(_presetName, &QComboBox::currentTextChanged, this, &FoilCalculationTab::loadPreset);

    _length = cm::getLineEdit();
    connect(_length, &QLineEdit::editingFinished, this, &FoilCalculationTab::uploadLength);

    _lengthReserve = cm::getLineEdit();
    connect(_lengthReserve, &QLineEdit::editingFinished, this, &FoilCalculationTab::uploadLengthReserve);

    _width = cm::getLineEdit();
    connect(_width, &QLineEdit::editingFinished, this, &FoilCalculationTab::uploadWidth);

    _widthReserve = cm::getLineEdit();
    connect(_widthReserve, &QLineEdit::editingFinished, this, &FoilCalculationTab::uploadWidthReserve);

    _sheetNumber = cm::getLineEdit();
    connect(_sheetNumber, &QLineEdit::editingFinished, this, &FoilCalculationTab::uploadSheetNumber);

    _circulation = cm::getLineEdit();
    connect(_circulation, &QLineEdit::editingFinished, this, &FoilCalculationTab::uploadCirculation);

    _result = cm::getLineEdit("Расчет не выполнен", true);
}

FoilCalculationTab::~FoilCalculationTab() {
    delete _presetName;
    delete _length;
    delete _lengthReserve;
    delete _width;
    delete _widthReserve;
    delete _sheetNumber;
    delete _circulation;
}

FoilDataManager const * FoilCalculationTab::getDataManager() const { return _foilDataManager; }
FoilDataManager * FoilCalculationTab::getDataManager() { return _foilDataManager; }

QComboBox const * FoilCalculationTab::getPresetName() const { return _presetName; }
QComboBox * FoilCalculationTab::getPresetName() { return _presetName; }

QLineEdit const * FoilCalculationTab::getLength() const { return _length; }
QLineEdit * FoilCalculationTab::getLength() { return _length; }

QLineEdit const * FoilCalculationTab::getLengthReserve() const { return _lengthReserve; }
QLineEdit * FoilCalculationTab::getLengthReserve() { return _lengthReserve; }

QLineEdit const * FoilCalculationTab::getWidth() const { return _width; }
QLineEdit * FoilCalculationTab::getWidth() { return _width; }

QLineEdit const * FoilCalculationTab::getWidthReserve() const { return _widthReserve; }
QLineEdit * FoilCalculationTab::getWidthReserve() { return _widthReserve; }

QLineEdit const * FoilCalculationTab::getSheetNumber() const { return _sheetNumber; }
QLineEdit * FoilCalculationTab::getSheetNumber() { return _sheetNumber; }

QLineEdit const * FoilCalculationTab::getCirculation() const { return _circulation; }
QLineEdit * FoilCalculationTab::getCirculation() { return _circulation; }

QLineEdit const * FoilCalculationTab::getResult() const { return _result; }
QLineEdit * FoilCalculationTab::getResult() { return _result; }

// public slots
void FoilCalculationTab::update() {
    cm::fillComboBox(_presetName, _foilDataManager->getConnection()->getPresetNames());
    cm::setComboBoxIndex(_presetName, [&]() { return _foilDataManager->getName(); });

    cm::setLineEditValue<double>(_length, [&]() { return _foilDataManager->getLength(); });
    cm::setLineEditValue<double>(_lengthReserve, [&]() { return _foilDataManager->getLengthReserve(); });
    cm::setLineEditValue<double>(_width, [&]() { return _foilDataManager->getWidth(); });
    cm::setLineEditValue<double>(_widthReserve, [&]() { return _foilDataManager->getWidthReserve(); });
    cm::setLineEditValue<std::size_t>(_sheetNumber, [&]() { return _foilDataManager->getSheetNumber(); });
    cm::setLineEditValue<std::size_t>(_circulation, [&]() { return _foilDataManager->getCirculation(); });

    calculate();

    std::cout << "FoilCalculationTab: updated" << std::endl;
}

void FoilCalculationTab::calculate() {
    try {
        _result->setText(QString::fromStdString(cm::toString(_foilDataManager->calculate())));
    } catch (std::exception const & err) {
        _result->clear();
        std::cerr << err.what() << std::endl;
    }
    cm::markError(_length);
    cm::markError(_lengthReserve);
    cm::markError(_width);
    cm::markError(_widthReserve);
    cm::markError(_sheetNumber);
    cm::markError(_circulation);
}

// private slots
void FoilCalculationTab::uploadLength() {
    std::cout << "FoilCalculationTab: uploading length\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _foilDataManager->setLength(value); },
        [&]() { _foilDataManager->clearLength(); },
        _length->text(),
        cm::toDouble
    );
    update();
}

void FoilCalculationTab::uploadLengthReserve() {
    std::cout << "FoilCalculationTab: uploading length reserve\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _foilDataManager->setLengthReserve(value); },
        [&]() { _foilDataManager->clearLengthReserve(); },
        _lengthReserve->text(),
        cm::toDouble
    );
    update();
}

void FoilCalculationTab::uploadWidth() {
    std::cout << "FoilCalculationTab: uploading width\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _foilDataManager->setWidth(value); },
        [&]() { _foilDataManager->clearWidth(); },
        _width->text(),
        cm::toDouble
    );
    update();
}

void FoilCalculationTab::uploadWidthReserve() {
    std::cout << "FoilCalculationTab: uploading width reserve\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _foilDataManager->setWidthReserve(value); },
        [&]() { _foilDataManager->clearWidthReserve(); },
        _widthReserve->text(),
        cm::toDouble
    );
    update();
}

void FoilCalculationTab::uploadSheetNumber() {
    std::cout << "FoilCalculationTab: uploading sheet number\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _foilDataManager->setSheetNumber(value); },
        [&]() { _foilDataManager->clearSheetNumber(); },
        _sheetNumber->text(),
        cm::toDouble
    );
    update();
}

void FoilCalculationTab::uploadCirculation() {
    std::cout << "FoilCalculationTab: uploading circulation\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _foilDataManager->setCirculation(value); },
        [&]() { _foilDataManager->clearCirculation(); },
        _circulation->text(),
        cm::toDouble
    );
    update();
}

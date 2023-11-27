#include <iostream>
#include <sstream>

#include "PaintCalculationTab.h"
#include "common_methods.h"

namespace cm = common_methods;

PaintCalculationTab::PaintCalculationTab(PaintDataManager * mgr) {
    _paintDataManager = mgr;

    _presetName = cm::getComboBox();
    cm::fillComboBox(_presetName, _paintDataManager->getConnection()->getPresetNames());
    connect(_presetName, &QComboBox::currentTextChanged, this, &PaintCalculationTab::loadPreset);

    _paintType = cm::getComboBox();
    cm::fillComboBox(_paintType, _paintDataManager->getPaintTypes());
    connect(_paintType, &QComboBox::currentTextChanged, this, &PaintCalculationTab::uploadPaintType);

    _materialType = cm::getComboBox();
    cm::fillComboBox(_materialType, _paintDataManager->getMaterialTypes());
    connect(_materialType, &QComboBox::currentTextChanged, this, &PaintCalculationTab::uploadMaterialType);

    _paintConsumption = cm::getLineEdit();
    connect(_paintConsumption, &QLineEdit::editingFinished, this, &PaintCalculationTab::uploadPaintConsumption);

    _divider = cm::getLineEdit();
    connect(_divider, &QLineEdit::editingFinished, this, &PaintCalculationTab::uploadDivider);

    _percent = cm::getLineEdit();
    connect(_percent, &QLineEdit::editingFinished, this, &PaintCalculationTab::uploadPercent);

    _sheetWidth = cm::getLineEdit();
    connect(_sheetWidth, &QLineEdit::editingFinished, this, &PaintCalculationTab::uploadSheetWidth);

    _sheetLength = cm::getLineEdit();
    connect(_sheetLength, &QLineEdit::editingFinished, this, &PaintCalculationTab::uploadSheetLength);

    _circulation = cm::getLineEdit();
    connect(_circulation, &QLineEdit::editingFinished, this, &PaintCalculationTab::uploadCirculation);

    _paintReserve = cm::getLineEdit();
    connect(_paintReserve, &QLineEdit::editingFinished, this, &PaintCalculationTab::uploadPaintReserve);

    _result = cm::getLineEdit("", true);
}

PaintCalculationTab::~PaintCalculationTab() {
    delete _presetName;
    delete _paintType;
    delete _materialType;
    delete _paintConsumption;
    delete _divider;
    delete _percent;
    delete _sheetWidth;
    delete _sheetLength;
    delete _circulation;
    delete _paintReserve;
}

PaintDataManager const * PaintCalculationTab::getDataManager() const { return _paintDataManager; }
PaintDataManager * PaintCalculationTab::getDataManager() { return _paintDataManager; }

QComboBox const * PaintCalculationTab::getPresetName() const { return _presetName; }
QComboBox * PaintCalculationTab::getPresetName() { return _presetName; }

QComboBox const * PaintCalculationTab::getPaintType() const { return _paintType; }
QComboBox * PaintCalculationTab::getPaintType() { return _paintType; }

QComboBox const * PaintCalculationTab::getMaterialType() const { return _materialType; }
QComboBox * PaintCalculationTab::getMaterialType() { return _materialType; }

QLineEdit const * PaintCalculationTab::getPaintConsumption() const { return _paintConsumption; }
QLineEdit * PaintCalculationTab::getPaintConsumption() { return _paintConsumption; }

QLineEdit const * PaintCalculationTab::getDivider() const { return _divider; }
QLineEdit * PaintCalculationTab::getDivider() { return _divider; }

QLineEdit const * PaintCalculationTab::getPercent() const { return _percent; }
QLineEdit * PaintCalculationTab::getPercent() { return _percent; }

QLineEdit const * PaintCalculationTab::getSheetWidth() const { return _sheetWidth; }
QLineEdit * PaintCalculationTab::getSheetWidth() { return _sheetWidth; }

QLineEdit const * PaintCalculationTab::getSheetLength() const { return _sheetLength; }
QLineEdit * PaintCalculationTab::getSheetLength() { return _sheetLength; }

QLineEdit const * PaintCalculationTab::getCirculation() const { return _circulation; }
QLineEdit * PaintCalculationTab::getCirculation() { return _circulation; }

QLineEdit const * PaintCalculationTab::getPaintReserve() const { return _paintReserve; }
QLineEdit * PaintCalculationTab::getPaintReserve() { return _paintReserve; }

QLineEdit const * PaintCalculationTab::getResult() const { return _result; }
QLineEdit * PaintCalculationTab::getResult() { return _result; }

void PaintCalculationTab::update() {
    cm::fillComboBox(_presetName, _paintDataManager->getConnection()->getPresetNames());
    cm::setComboBoxIndex(_presetName, [&]() { return _paintDataManager->getName(); });

    cm::fillComboBox(_paintType, _paintDataManager->getPaintTypes());
    cm::setComboBoxIndex(_paintType, [&]() { return _paintDataManager->getPaintType(); });

    cm::fillComboBox(_materialType, _paintDataManager->getMaterialTypes());
    cm::setComboBoxIndex(_materialType, [&]() { return _paintDataManager->getMaterialType(); });

    cm::setLineEditValue<double>(_paintConsumption, [&]() { return _paintDataManager->getPaintConsumption(); });
    cm::setLineEditValue<double>(_divider, [&]() { return _paintDataManager->getDivider(); });
    cm::setLineEditValue<double>(_percent, [&]() { return _paintDataManager->getPercentage(); });
    cm::setLineEditValue<double>(_sheetWidth, [&]() { return _paintDataManager->getSheetWidth(); });
    cm::setLineEditValue<double>(_sheetLength, [&]() { return _paintDataManager->getSheetLength(); });
    cm::setLineEditValue<unsigned long>(_circulation, [&]() { return _paintDataManager->getCirculation(); });
    cm::setLineEditValue<double>(_paintReserve, [&]() { return _paintDataManager->getPaintReserve(); });

    std::cout << "PaintCalculationTab: data updated" << std::endl;
}

void PaintCalculationTab::loadPreset(QString const & name) {
    std::string presetName{ name.toStdString() };
    if (presetName.empty())
        return;

    _paintDataManager->loadPreset(presetName);
    std::cout << "PaintCalculationTab: preset named \"" << presetName << "\" selected" << std::endl;
    update();
}

void PaintCalculationTab::uploadPaintType() {
    std::string type = _paintType->currentText().toStdString();
    std::cout << "uploading paint type\t";

    if (type.empty()) {
        std::cout << "Error: field \"paint type\" is empty\n";
        return;
    }

    _paintDataManager->setPaintType(type);
    std::cout << "OK\n";
    update();
}

void PaintCalculationTab::uploadMaterialType() {
    std::string type = _materialType->currentText().toStdString();
    std::cout << "uploading material type\t";

    if (type.empty()) {
        std::cout << "Error: field \"material type\" is empty\n";
        return;
    }

    _paintDataManager->setMaterialType(type);
    std::cout << "OK\n";
    update();
}

void PaintCalculationTab::uploadPaintConsumption() {
    std::cout << "uploading paint consumption\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setPaintConsumption(value); },
        [&]() { _paintDataManager->clearPaintConsumption(); },
        _paintConsumption->text(),
        [&](QString line) { return cm::toDouble(line); }
    );
    update();
}

void PaintCalculationTab::uploadDivider() {
    std::cout << "uploading divider\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setDivider(value); },
        [&]() { _paintDataManager->clearDivider(); },
        _divider->text(),
        [&](QString line) { return cm::toDouble(line); }
    );
    update();
}

void PaintCalculationTab::uploadPercent() {
    std::cout << "uploading divider\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setPercentage(value); },
        [&]() { _paintDataManager->clearPercentage(); },
        _percent->text(),
        [&](QString line) { return cm::toDouble(line); }
    );
    update();
}

void PaintCalculationTab::uploadSheetWidth() {
    std::cout << "uploading sheet width\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setSheetWidth(value); },
        [&]() { _paintDataManager->clearSheetWidth(); },
        _sheetWidth->text(),
        [&](QString line) { return cm::toDouble(line); }
    );
    update();
}

void PaintCalculationTab::uploadSheetLength() {
    std::cout << "uploading sheet length\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setSheetLength(value); },
        [&]() { _paintDataManager->clearSheetLength(); },
        _sheetLength->text(),
        [&](QString line) { return cm::toDouble(line); }
    );
    update();
}

void PaintCalculationTab::uploadCirculation() {
    std::cout << "uploading circulation\t";
    cm::setManagerParam<unsigned long, QString>(
        [&](unsigned long value) { _paintDataManager->setCirculation(value); },
        [&]() { _paintDataManager->clearCirculation(); },
        _circulation->text(),
        [&](QString line) { return cm::toULong(line); }
    );
    update();
}

void PaintCalculationTab::uploadPaintReserve() {
    std::cout << "uploading paint reserve\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setPaintReserve(value); },
        [&]() { _paintDataManager->clearPaintReserve(); },
        _paintReserve->text(),
        [&](QString line) { return cm::toDouble(line); }
    );
    update();
}

void PaintCalculationTab::clear() {
    _paintDataManager->clear();
    std::cout << "PaintCalculationTab: fields cleared" << std::endl;
    update();
}

void PaintCalculationTab::calculate() {
    try {
        _result->setText(QString::fromStdString(cm::toString(_paintDataManager->calculate())));
    } catch (std::exception const & err) {
        std::cerr << err.what() << std::endl;
    }
}

void PaintCalculationTab::createPreset(QString const & name) {
    _paintDataManager->createPreset(name.toStdString());
    update();
}
void PaintCalculationTab::updatePreset(QString const & name) {
    _paintDataManager->updatePreset(name.toStdString());
    update();
}
void PaintCalculationTab::removePreset(QString const & name) {
    _paintDataManager->removePreset(name.toStdString());
    update();
}

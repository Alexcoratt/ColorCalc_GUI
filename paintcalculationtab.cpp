#include <iostream>
#include <sstream>
#include <map>

#include "paintcalculationtab.h"
#include "common_methods.h"

namespace cm = common_methods;

template <typename T>
class BiMap {
private:
    std::map<T, T> _map;

public:
    BiMap(std::map<T, T> const & map = {}) {
        for (auto it = map.begin(); it != map.end(); ++it) {
            _map[it->first] = it->second;
            _map[it->second] = it->first;
        }
    }

    T const & at(T const & key) const {
        return _map.at(key);
    }
    T & at(T const & key) {
        return _map.at(key);
    }
    T & operator[](T const & key) {
        return _map[key];
    }
};

BiMap<std::string> const PAINT_TYPES{{
    {"metallized_paint", "Металлизированная краска"},
    {"folic_paint", "Фолиевая краска"},
    {"uv_curable_paint", "УФ-отверждаемая краска"},
    {"ordinary_paint", "Обычная краска, PANTONE"},
}};

BiMap<std::string> const MATERIAL_TYPES{{
    {"coated_paper", "Мелованная бумага"},
    {"label_paper", "Этикеточная бумага"},
    {"paperboard", "Картон"},
    {"non_absorbent_material", "Невпитывающий материал"}
}};

template <typename T>
std::string translate(std::string const & line, BiMap<T> const & dict) {
    try {
        return dict.at(line);
    } catch (std::out_of_range const & err) {
        std::cerr << err.what() << std::endl;
        return line;
    }
}

void fillComboBoxTranslated(QComboBox * comboBox, std::vector<std::string> const & values, BiMap<std::string> const & dict) {
    comboBox->clear();
    for (auto const & value : values)
        comboBox->addItem(QString::fromStdString(translate(value, dict)));
}

PaintCalculationTab::PaintCalculationTab(PaintDataManager * mgr) {
    _paintDataManager = mgr;

    _presetName = cm::getComboBox();
    cm::fillComboBox(_presetName, _paintDataManager->getConnection()->getPresetNames());
    connect(_presetName, &QComboBox::currentTextChanged, this, &PaintCalculationTab::loadPreset);
    _presetName->setMaximumWidth(256);

    _paintType = cm::getComboBox();
    fillComboBoxTranslated(_paintType, _paintDataManager->getPaintTypes(), PAINT_TYPES);
    connect(_paintType, &QComboBox::currentTextChanged, this, &PaintCalculationTab::uploadPaintType);

    _materialType = cm::getComboBox();
    fillComboBoxTranslated(_materialType, _paintDataManager->getMaterialTypes(), MATERIAL_TYPES);
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

    _result = cm::getLineEdit("Расчет не выполнен", true);
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
    delete _result;
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

    fillComboBoxTranslated(_paintType, _paintDataManager->getPaintTypes(), PAINT_TYPES);
    cm::setComboBoxIndex(_paintType, [&]() { return translate(_paintDataManager->getPaintType(), PAINT_TYPES); });

    fillComboBoxTranslated(_materialType, _paintDataManager->getMaterialTypes(), MATERIAL_TYPES);
    cm::setComboBoxIndex(_materialType, [&]() { return translate(_paintDataManager->getMaterialType(), MATERIAL_TYPES); });

    cm::setLineEditValue<double>(_paintConsumption, [&]() { return _paintDataManager->getPaintConsumption(); });
    cm::setLineEditValue<double>(_divider, [&]() { return _paintDataManager->getDivider(); });
    cm::setLineEditValue<double>(_percent, [&]() { return _paintDataManager->getPercentage(); });
    cm::setLineEditValue<double>(_sheetWidth, [&]() { return _paintDataManager->getSheetWidth(); });
    cm::setLineEditValue<double>(_sheetLength, [&]() { return _paintDataManager->getSheetLength(); });
    cm::setLineEditValue<unsigned long>(_circulation, [&]() { return _paintDataManager->getCirculation(); });
    cm::setLineEditValue<double>(_paintReserve, [&]() { return _paintDataManager->getPaintReserve(); });

    calculate();

    std::cout << "PaintCalculationTab: data updated" << std::endl;
}

void PaintCalculationTab::uploadPaintType() {
    std::string type = _paintType->currentText().toStdString();
    std::cout << "uploading paint type\t";

    if (type.empty()) {
        std::cout << "Error: field \"paint type\" is empty\n";
        return;
    }

    _paintDataManager->setPaintType(translate(type, PAINT_TYPES));

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

    _paintDataManager->setMaterialType(translate(type, MATERIAL_TYPES));

    std::cout << "OK\n";
    update();
}

void PaintCalculationTab::uploadPaintConsumption() {
    std::cout << "uploading paint consumption\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setPaintConsumption(value); },
        [&]() { _paintDataManager->clearPaintConsumption(); },
        _paintConsumption->text(),
        cm::toDouble
    );
    update();
}

void PaintCalculationTab::uploadDivider() {
    std::cout << "uploading divider\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setDivider(value); },
        [&]() { _paintDataManager->clearDivider(); },
        _divider->text(),
        cm::toDouble
    );
    update();
}

void PaintCalculationTab::uploadPercent() {
    std::cout << "uploading divider\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setPercentage(value); },
        [&]() { _paintDataManager->clearPercentage(); },
        _percent->text(),
        cm::toDouble
    );
    update();
}

void PaintCalculationTab::uploadSheetWidth() {
    std::cout << "uploading sheet width\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setSheetWidth(value); },
        [&]() { _paintDataManager->clearSheetWidth(); },
        _sheetWidth->text(),
        cm::toDouble
    );
    update();
}

void PaintCalculationTab::uploadSheetLength() {
    std::cout << "uploading sheet length\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setSheetLength(value); },
        [&]() { _paintDataManager->clearSheetLength(); },
        _sheetLength->text(),
        cm::toDouble
    );
    update();
}

void PaintCalculationTab::uploadCirculation() {
    std::cout << "uploading circulation\t";
    cm::setManagerParam<unsigned long, QString>(
        [&](unsigned long value) { _paintDataManager->setCirculation(value); },
        [&]() { _paintDataManager->clearCirculation(); },
        _circulation->text(),
        cm::toULong
    );
    update();
}

void PaintCalculationTab::uploadPaintReserve() {
    std::cout << "uploading paint reserve\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setPaintReserve(value); },
        [&]() { _paintDataManager->clearPaintReserve(); },
        _paintReserve->text(),
        cm::toDouble
    );
    update();
}

void PaintCalculationTab::calculate() {
    try {
        _result->setText(QString::fromStdString(cm::toString(_paintDataManager->calculate())));
    } catch (std::exception const & err) {
        _result->clear();
        std::cerr << err.what() << std::endl;
    }
    cm::markError(_paintConsumption);
    cm::markError(_divider);
    cm::markError(_percent);
    cm::markError(_sheetWidth);
    cm::markError(_sheetLength);
    cm::markError(_circulation);
    cm::markError(_paintReserve);
}

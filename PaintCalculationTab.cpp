#include <iostream>
#include <sstream>

#include "PaintCalculationTab.h"

#define LINE_EDIT_PLACEHOLDER "Введите значение"
#define COMBO_BOX_PLACEHOLDER "Не выбрано"

QLineEdit * getLineEdit(QString const & placeholder = LINE_EDIT_PLACEHOLDER, bool readOnly = false) {
    QLineEdit * lineEdit = new QLineEdit ;
    lineEdit->setPlaceholderText(placeholder);
    lineEdit->setReadOnly(readOnly);
    return lineEdit;
}

QComboBox * getComboBox(QString const & placeholder = COMBO_BOX_PLACEHOLDER) {
    QComboBox * comboBox = new QComboBox;
    comboBox->setPlaceholderText(placeholder);
    return comboBox;
}

void fillComboBox(QComboBox * comboBox, std::vector<std::string> const & options) {
    comboBox->clear();
    for (auto const & option : options)
        comboBox->addItem(option.c_str());
}

PaintCalculationTab::PaintCalculationTab(PaintDataManager * mgr) {
    _paintDataManager = mgr;

    _presetName = getComboBox();
    fillComboBox(_presetName, _paintDataManager->getConnection()->getPresetNames());
    connect(_presetName, &QComboBox::currentTextChanged, this, &PaintCalculationTab::loadPreset);

    _paintType = getComboBox();
    fillComboBox(_paintType, _paintDataManager->getPaintTypes());
    connect(_paintType, &QComboBox::currentTextChanged, this, &PaintCalculationTab::uploadPaintType);

    _materialType = getComboBox();
    fillComboBox(_materialType, _paintDataManager->getMaterialTypes());
    connect(_materialType, &QComboBox::currentTextChanged, this, &PaintCalculationTab::uploadMaterialType);

    _paintConsumption = getLineEdit();
    connect(_paintConsumption, &QLineEdit::editingFinished, this, &PaintCalculationTab::uploadPaintConsumption);

    _divider = getLineEdit();
    connect(_divider, &QLineEdit::editingFinished, this, &PaintCalculationTab::uploadDivider);

    _percent = getLineEdit();
    connect(_percent, &QLineEdit::editingFinished, this, &PaintCalculationTab::uploadPercent);

    _sheetWidth = getLineEdit();
    connect(_sheetWidth, &QLineEdit::editingFinished, this, &PaintCalculationTab::uploadSheetWidth);

    _sheetLength = getLineEdit();
    connect(_sheetLength, &QLineEdit::editingFinished, this, &PaintCalculationTab::uploadSheetLength);

    _circulation = getLineEdit();
    connect(_circulation, &QLineEdit::editingFinished, this, &PaintCalculationTab::uploadCirculation);

    _paintReserve = getLineEdit();
    connect(_paintReserve, &QLineEdit::editingFinished, this, &PaintCalculationTab::uploadPaintReserve);

    _result = getLineEdit("", true);
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

void setComboBoxIndex(QComboBox * comboBox, QString const & value) {
    QSignalBlocker blocker(comboBox);
    comboBox->setCurrentIndex(comboBox->findText(value));
    blocker.unblock();
}

void setComboBoxIndex(QComboBox * comboBox, std::function<QString()> get) {
    try {
        setComboBoxIndex(comboBox, get());
    } catch (std::exception const & err) {
        comboBox->setCurrentIndex(-1);
        std::cerr << err.what() << std::endl;
    }
}

void setComboBoxIndex(QComboBox * comboBox, std::function<std::string()> get) {
    try {
        setComboBoxIndex(comboBox, QString::fromStdString(get()));
    } catch (std::exception const & err) {
        comboBox->setCurrentIndex(-1);
        std::cerr << err.what() << std::endl;
    }
}

template<typename T>
std::string toString(T const & n) {
    std::ostringstream oss;
    oss << n;
    std::string s =  oss.str();
    int dotpos = s.find_first_of('.');
    if(dotpos!=std::string::npos){
        int ipos = s.size()-1;
        while(s[ipos]=='0' && ipos>dotpos){
            --ipos;
        }
        s.erase ( ipos + 1, std::string::npos );
    }
    return s;
}

template <typename T>
void setLineEditValue(QLineEdit * lineEdit, std::function<T()> const & get) {
    QSignalBlocker blocker(lineEdit);
    try {
        lineEdit->setText(QString::fromStdString(toString(get())));
    } catch (std::exception const & err) {
        lineEdit->clear();
        std::cerr << err.what() << std::endl;
    }
    blocker.unblock();
}

void PaintCalculationTab::update() {
    setComboBoxIndex(_presetName, [&]() { return _paintDataManager->getName(); });
    setComboBoxIndex(_paintType, [&]() { return _paintDataManager->getPaintType(); });
    setComboBoxIndex(_materialType, [&]() { return _paintDataManager->getMaterialType(); });

    setLineEditValue<double>(_paintConsumption, [&]() { return _paintDataManager->getPaintConsumption(); });
    setLineEditValue<double>(_divider, [&]() { return _paintDataManager->getDivider(); });
    setLineEditValue<double>(_percent, [&]() { return _paintDataManager->getPercentage(); });
    setLineEditValue<double>(_sheetWidth, [&]() { return _paintDataManager->getSheetWidth(); });
    setLineEditValue<double>(_sheetLength, [&]() { return _paintDataManager->getSheetLength(); });
    setLineEditValue<unsigned long>(_circulation, [&]() { return _paintDataManager->getCirculation(); });
    setLineEditValue<double>(_paintReserve, [&]() { return _paintDataManager->getPaintReserve(); });

    std::cout << "PaintCalculationTab: data updated" << std::endl;
}

void PaintCalculationTab::loadPreset() {
    std::string presetName{ _presetName->currentText().toStdString() };
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

template <typename T, typename V>
void setManagerParam(std::function<void(T)> const & set, std::function<void()> const & clear, V const & value, std::function<T(V)> const & converter) {
    try {
        set(converter(value));
        std::cout << "OK" << std::endl;
    } catch (std::exception const & err) {
        clear();
        std::cout << err.what() << std::endl;
    }
}

double toDouble(QString const & line) {
    bool isCorrect;
    auto res = line.toDouble(&isCorrect);
    if (isCorrect)
        return res;
    throw std::invalid_argument("toDouble: invalid line \"" + line.toStdString() + "\"");
}

double toULong(QString const & line) {
    bool isCorrect;
    auto res = line.toULong(&isCorrect);
    if (isCorrect)
        return res;
    throw std::invalid_argument("toULong: invalid line \"" + line.toStdString() + "\"");
}

void PaintCalculationTab::uploadPaintConsumption() {
    std::cout << "uploading paint consumption\t";
    setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setPaintConsumption(value); },
        [&]() { _paintDataManager->clearPaintConsumption(); },
        _paintConsumption->text(),
        [&](QString line) { return toDouble(line); }
    );
    update();
}

void PaintCalculationTab::uploadDivider() {
    std::cout << "uploading divider\t";
    setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setDivider(value); },
        [&]() { _paintDataManager->clearDivider(); },
        _divider->text(),
        [&](QString line) { return toDouble(line); }
    );
    update();
}

void PaintCalculationTab::uploadPercent() {
    std::cout << "uploading divider\t";
    setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setPercentage(value); },
        [&]() { _paintDataManager->clearPercentage(); },
        _percent->text(),
        [&](QString line) { return toDouble(line); }
    );
    update();
}

void PaintCalculationTab::uploadSheetWidth() {
    std::cout << "uploading sheet width\t";
    setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setSheetWidth(value); },
        [&]() { _paintDataManager->clearSheetWidth(); },
        _sheetWidth->text(),
        [&](QString line) { return toDouble(line); }
    );
    update();
}

void PaintCalculationTab::uploadSheetLength() {
    std::cout << "uploading sheet length\t";
    setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setSheetLength(value); },
        [&]() { _paintDataManager->clearSheetLength(); },
        _sheetLength->text(),
        [&](QString line) { return toDouble(line); }
    );
    update();
}

void PaintCalculationTab::uploadCirculation() {
    std::cout << "uploading circulation\t";
    setManagerParam<unsigned long, QString>(
        [&](unsigned long value) { _paintDataManager->setCirculation(value); },
        [&]() { _paintDataManager->clearCirculation(); },
        _circulation->text(),
        [&](QString line) { return toULong(line); }
    );
    update();
}

void PaintCalculationTab::uploadPaintReserve() {
    std::cout << "uploading paint reserve\t";
    setManagerParam<double, QString>(
        [&](double value) { _paintDataManager->setPaintReserve(value); },
        [&]() { _paintDataManager->clearPaintReserve(); },
        _paintReserve->text(),
        [&](QString line) { return toDouble(line); }
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
        _result->setText(QString::fromStdString(toString(_paintDataManager->calculate())));
    } catch (std::exception const & err) {
        std::cerr << err.what() << std::endl;
    }
}

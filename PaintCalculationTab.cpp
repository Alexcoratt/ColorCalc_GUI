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

void testSlot(std::string value) {
    std::cout << value << '\n';
}

PaintCalculationTab::PaintCalculationTab(PaintDataManager * mgr) :
    _presetName(getComboBox()),
    _paintType(getComboBox()),
    _materialType(getComboBox()),
    _paintConsumption(getLineEdit()),
    _divider(getLineEdit()),
    _percent(getLineEdit()),
    _sheetWidth(getLineEdit()),
    _sheetLength(getLineEdit()),
    _circulation(getLineEdit()),
    _paintReserve(getLineEdit()),
    _result(getLineEdit("", true)),

    _paintDataManager(mgr)
    {
    fillComboBox(_presetName, _paintDataManager->getConnection()->getPresetNames());
    fillComboBox(_paintType, _paintDataManager->getPaintTypes());
    fillComboBox(_materialType, _paintDataManager->getMaterialTypes());

    connect(_presetName, &QComboBox::currentTextChanged, this, &PaintCalculationTab::loadPreset);
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

QLineEdit const * PaintCalculationTab::getPaintReserve() const { return _paintReserve;}
QLineEdit * PaintCalculationTab::getPaintReserve() { return _paintReserve; }

QLineEdit const * PaintCalculationTab::getResult() const { return _result; }
QLineEdit * PaintCalculationTab::getResult() { return _result; }

void setComboBoxIndex(QComboBox * comboBox, std::string const & value) {
    comboBox->setCurrentIndex(comboBox->findText(QString::fromStdString(value)));
}

void setComboBoxIndex(QComboBox * comboBox, std::function<std::string()> get) {
    try {
        setComboBoxIndex(comboBox, get());
    } catch (std::exception const & err) {
        comboBox->setCurrentIndex(-1);
        std::cerr << err.what() << std::endl;
    }
}

void setLineEditValue(QLineEdit * lineEdit, std::function<std::string()> const & get) {
    try {
        lineEdit->setText(QString::fromStdString(get()));
    } catch (std::exception const & err) {
        lineEdit->clear();
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

void PaintCalculationTab::update() {
    setComboBoxIndex(_presetName, [&]() { return _paintDataManager->getName(); });
    setComboBoxIndex(_paintType, [&]() { return _paintDataManager->getPaintType(); });
    setComboBoxIndex(_materialType, [&]() { return _paintDataManager->getMaterialType(); });

    setLineEditValue(_paintConsumption, [&]() { return toString(_paintDataManager->getPaintConsumption()); });
    setLineEditValue(_divider, [&]() { return toString(_paintDataManager->getDivider()); });
    setLineEditValue(_percent, [&]() { return toString(_paintDataManager->getPercentage()); });
    setLineEditValue(_sheetWidth, [&]() { return toString(_paintDataManager->getSheetWidth()); });
    setLineEditValue(_sheetLength, [&]() { return toString(_paintDataManager->getSheetLength()); });
    setLineEditValue(_circulation, [&]() { return toString(_paintDataManager->getCirculation()); });
    setLineEditValue(_paintReserve, [&]() { return toString(_paintDataManager->getPaintReserve()); });

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

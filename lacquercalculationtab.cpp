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

    _result = cm::getLineEdit("", true);
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

QComboBox const * getPresetName() const;
QComboBox * getPresetName();

QLineEdit const * getLacquerConsumption() const;
QLineEdit * getLacquerConsumption();

QLineEdit const * getPercentage() const;
QLineEdit * getPercentage();

QLineEdit const * getSheetWidth() const;
QLineEdit * getSheetWidth();

QLineEdit const * getSheetLength() const;
QLineEdit * getSheetLength();

QLineEdit const * getCirculation() const;
QLineEdit * getCirculation();

QLineEdit const * getResult() const;
QLineEdit * getResult();

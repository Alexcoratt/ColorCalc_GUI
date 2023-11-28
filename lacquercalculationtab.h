#ifndef LACQUERCALCULATIONTAB_H
#define LACQUERCALCULATIONTAB_H

#include <QComboBox>
#include <QLineEdit>

#include "itab.h"
#include <LacquerDataManager.hpp>

class LacquerCalculationTab : public ITab
{
    Q_OBJECT

public:
    LacquerCalculationTab(LacquerDataManager *);
    ~LacquerCalculationTab();

    LacquerDataManager const * getDataManager() const;
    LacquerDataManager * getDataManager();

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

public slots:
    void update();
    void calculate();

private:
    QComboBox * _presetName;

    QLineEdit * _lacquerConsumption;
    QLineEdit * _percentage;
    QLineEdit * _sheetWidth;
    QLineEdit * _sheetLength;
    QLineEdit * _circulation;

    QLineEdit * _result;

    LacquerDataManager * _lacquerDataManager;

private slots:
    void uploadLacquerConsumption();
    void uploadPercentage();
    void uploadSheetWidth();
    void uploadSheetLength();
    void uploadCirculation();
};

#endif // LACQUERCALCULATIONTAB_H

#ifndef FOILCALCULATIONTAB_H
#define FOILCALCULATIONTAB_H

#include <QComboBox>
#include <QLineEdit>

#include "itab.h"
#include <FoilDataManager.hpp>

class FoilCalculationTab : public ITab
{
    Q_OBJECT

public:
    FoilCalculationTab(FoilDataManager *);
    ~FoilCalculationTab();

    FoilDataManager const * getDataManager() const;
    FoilDataManager * getDataManager();

    QComboBox const * getPresetName() const;
    QComboBox * getPresetName();

    QLineEdit const * getLength() const;
    QLineEdit * getLength();

    QLineEdit const * getLengthReserve() const;
    QLineEdit * getLengthReserve();

    QLineEdit const * getWidth() const;
    QLineEdit * getWidth();

    QLineEdit const * getWidthReserve() const;
    QLineEdit * getWidthReserve();

    QLineEdit const * getSheetNumber() const;
    QLineEdit * getSheetNumber();

    QLineEdit const * getCirculation() const;
    QLineEdit * getCirculation();

    QLineEdit const * getResult() const;
    QLineEdit * getResult();

public slots:
    void update();
    void calculate();

private slots:
    void uploadLength();
    void uploadLengthReserve();
    void uploadWidth();
    void uploadWidthReserve();
    void uploadSheetNumber();
    void uploadCirculation();

private:
    QComboBox * _presetName;

    QLineEdit * _length;
    QLineEdit * _lengthReserve;
    QLineEdit * _width;
    QLineEdit * _widthReserve;
    QLineEdit * _sheetNumber;
    QLineEdit * _circulation;

    QLineEdit * _result;

    FoilDataManager * _foilDataManager;
};

#endif // FOILCALCULATIONTAB_H

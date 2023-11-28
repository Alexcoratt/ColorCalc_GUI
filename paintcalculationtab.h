#ifndef PAINTCALCULATIONTAB_H
#define PAINTCALCULATIONTAB_H

#include <QComboBox>
#include <QLineEdit>
#include "itab.h"

#include <PaintDataManager.hpp>

class PaintCalculationTab : public ITab {
    Q_OBJECT

private:
    QComboBox * _presetName;
    QComboBox * _paintType;
    QComboBox * _materialType;

    QLineEdit * _paintConsumption;
    QLineEdit * _divider;
    QLineEdit * _percent;
    QLineEdit * _sheetWidth;
    QLineEdit * _sheetLength;
    QLineEdit * _circulation;
    QLineEdit * _paintReserve;

    QLineEdit * _result;

    PaintDataManager * _paintDataManager;

private slots:
    void uploadPaintType();
    void uploadMaterialType();
    void uploadPaintConsumption();
    void uploadDivider();
    void uploadPercent();
    void uploadSheetWidth();
    void uploadSheetLength();
    void uploadCirculation();
    void uploadPaintReserve();

public slots:
    void update();
    void calculate();

public:
    PaintCalculationTab(PaintDataManager *);
    ~PaintCalculationTab();

    PaintDataManager const * getDataManager() const;
    PaintDataManager * getDataManager();

    QComboBox const * getPresetName() const;
    QComboBox * getPresetName();

    QComboBox const * getPaintType() const;
    QComboBox * getPaintType();

    QComboBox const * getMaterialType() const;
    QComboBox * getMaterialType();

    QLineEdit const * getPaintConsumption() const;
    QLineEdit * getPaintConsumption();

    QLineEdit const * getDivider() const;
    QLineEdit * getDivider();

    QLineEdit const * getPercent() const;
    QLineEdit * getPercent();

    QLineEdit const * getSheetWidth() const;
    QLineEdit * getSheetWidth();

    QLineEdit const * getSheetLength() const;
    QLineEdit * getSheetLength();

    QLineEdit const * getCirculation() const;
    QLineEdit * getCirculation();

    QLineEdit const * getPaintReserve() const;
    QLineEdit * getPaintReserve();

    QLineEdit const * getResult() const;
    QLineEdit * getResult();
};

#endif // PAINTCALCULATIONTAB_H

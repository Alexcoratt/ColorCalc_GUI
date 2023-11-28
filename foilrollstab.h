#ifndef FOILROLLSTAB_H
#define FOILROLLSTAB_H

#include <QComboBox>
#include <QLineEdit>
#include <QListWidget>
#include "itab.h"

#include <FoilRollsDataManager.hpp>
#include <FoilDataManager.hpp>

class FoilRollsTab : public ITab
{
    Q_OBJECT

public:
    FoilRollsTab(FoilRollsDataManager * foilRollsDataManager, FoilDataManager const * foilDataManager);
    ~FoilRollsTab();

    IDataManager const * getDataManager() const;
    IDataManager * getDataManager();

    QComboBox const * getPresetName() const;
    QComboBox * getPresetName();

    QLineEdit const * getLength() const;
    QLineEdit * getLength();

    QLineEdit const * getWidth() const;
    QLineEdit * getWidth();

    QListWidget const * getSuitableFoilRolls() const;
    QListWidget * getSuitableFoilRolls();

public slots:
    void update();
    void findSuitableRolls();

private slots:
    void uploadLength();
    void uploadWidth();

private:
    QComboBox * _presetName;

    QLineEdit * _length;
    QLineEdit * _width;

    QListWidget * _suitableFoilRolls;

    FoilDataManager const * _foilDataManager;
    FoilRollsDataManager * _foilRollsDataManager;
};

#endif // FOILROLLSTAB_H

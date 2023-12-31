#include "itab.h"
#include <iostream>

void ITab::clear() {
    getDataManager()->clear();
    update();
}

void ITab::createPreset(QString const & name) {
    getDataManager()->createPreset(name.toStdString());
    update();
}
void ITab::createPreset(QString const & name, ITableConnection * targetConnection) {
    targetConnection->createPreset(name.toStdString(), getDataManager()->exportData());
    update();
}

void ITab::updatePreset(QString const & name) {
    getDataManager()->updatePreset(name.toStdString());
    update();
};
void ITab::removePreset(QString const & name) {
    getDataManager()->removePreset(name.toStdString());
    update();
};

void ITab::loadPreset(QString const & name) {
    std::string presetName{ name.toStdString() };
    if (presetName.empty())
        return;

    getDataManager()->loadPreset(presetName);
    update();
}

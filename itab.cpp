#include "itab.h"
#include <iostream>

void ITab::clear() {
    getDataManager()->clear();
    update();
}

void ITab::createPreset(QString const & name) {
    try {
        getDataManager()->createPreset(name.toStdString());
    } catch (std::exception const & err) {
        std::cerr << err.what() << std::endl;
    }

    update();
}
void ITab::updatePreset(QString const & name) {
    try {
        getDataManager()->updatePreset(name.toStdString());
    } catch (std::exception const & err) {
        std::cerr << err.what() << std::endl;
    }

    update();
};
void ITab::removePreset(QString const & name) {
    try {
        getDataManager()->removePreset(name.toStdString());
    } catch (std::exception const & err) {
        std::cerr << err.what() << std::endl;
    }

    update();
};

void ITab::loadPreset(QString const & name) {
    std::string presetName{ name.toStdString() };
    if (presetName.empty())
        return;

    getDataManager()->loadPreset(presetName);
    update();
}

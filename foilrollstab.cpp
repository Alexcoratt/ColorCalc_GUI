#include "foilrollstab.h"
#include "common_methods.h"

namespace cm = common_methods;

FoilRollsTab::FoilRollsTab(FoilRollsDataManager * foilRollsDataManager, FoilDataManager const * foilDataManager)
{
    _foilRollsDataManager = foilRollsDataManager;
    _foilDataManager = foilDataManager;

    _presetName = cm::getComboBox(_foilRollsDataManager->getConnection()->getPresetNames());
    connect(_presetName, &QComboBox::currentTextChanged, this, &FoilRollsTab::loadPreset);

    _length = cm::getLineEdit();
    connect(_length, &QLineEdit::editingFinished, this, &FoilRollsTab::uploadLength);

    _width = cm::getLineEdit();
    connect(_width, &QLineEdit::editingFinished, this, &FoilRollsTab::uploadWidth);

    _suitableFoilRolls = new QListWidget;
    connect(_suitableFoilRolls, &QListWidget::currentTextChanged, this, &FoilRollsTab::loadPreset);
}

FoilRollsTab::~FoilRollsTab() {
    delete _presetName;
    delete _length;
    delete _width;
    delete _suitableFoilRolls;
}

IDataManager const * FoilRollsTab::getDataManager() const { return _foilRollsDataManager; }
IDataManager * FoilRollsTab::getDataManager() { return _foilRollsDataManager; }

QComboBox const * FoilRollsTab::getPresetName() const { return _presetName; }
QComboBox * FoilRollsTab::getPresetName() { return _presetName; }

QLineEdit const * FoilRollsTab::getLength() const { return _length; }
QLineEdit * FoilRollsTab::getLength() { return _length; }

QLineEdit const * FoilRollsTab::getWidth() const { return _width; }
QLineEdit * FoilRollsTab::getWidth() { return _width; }

QListWidget const * FoilRollsTab::getSuitableFoilRolls() const { return _suitableFoilRolls; }
QListWidget * FoilRollsTab::getSuitableFoilRolls() { return _suitableFoilRolls; }

// public slots
void FoilRollsTab::update() {
    cm::fillComboBox(_presetName, _foilRollsDataManager->getConnection()->getPresetNames());
    cm::setComboBoxIndex(_presetName, [&]() { return _foilRollsDataManager->getName(); });

    cm::setLineEditValue<double>(_length, [&]() { return _foilRollsDataManager->getLength(); });
    cm::setLineEditValue<double>(_width, [&]() { return _foilRollsDataManager->getWidth(); });
}

void FoilRollsTab::findSuitableRolls() {
    _suitableFoilRolls->clear();
    auto rolls = _foilDataManager->getSuitableFoilRolls();
    for (auto const & roll : rolls)
        _suitableFoilRolls->addItem(QString::fromStdString(roll));

    if (rolls.empty())
        std::cout << "FoilRollsTab: suitable rolls not found" << std::endl;
    else
        std::cout << "FoilRollsTab: suitable rolls found" << std::endl;
}

// private slots
void FoilRollsTab::uploadLength() {
    std::cout << "FoilRollsTab: uploading length\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _foilRollsDataManager->setLength(value); },
        [&]() { _foilRollsDataManager->clearLength(); },
        _length->text(),
        cm::toDouble
    );
    update();
}

void FoilRollsTab::uploadWidth() {
    std::cout << "FoilRollsTab: uploading width\t";
    cm::setManagerParam<double, QString>(
        [&](double value) { _foilRollsDataManager->setWidth(value); },
        [&]() { _foilRollsDataManager->clearWidth(); },
        _width->text(),
        cm::toDouble
    );
    update();
}

#include "presetremovalpopup.h"
#include "common_methods.h"

#include <PresetDoesNotExistException.hpp>

PresetRemovalPopUp::PresetRemovalPopUp(ITab * tab, std::function<void(std::exception const &, std::string const &)> const & exceptionHandler, QWidget *parent)
    : InputPopUp{parent}
{
    _comboBox = common_methods::getComboBox();
    setInputWidget(_comboBox);
    common_methods::fillComboBox(_comboBox, tab->getDataManager()->getConnection()->getPresetNames());

    _exceptionHandler = exceptionHandler;
    _tab = tab;

    setWindowTitle("Удалить пресет");
    setInfo("Выберите имя пресета, который хотите удалить");
    _comboBox->setPlaceholderText("Не выбрано");
    _comboBox->setCurrentIndex(-1);

    connect(this, &InputPopUp::accepted, this, &PresetRemovalPopUp::accept);
    connect(this, &InputPopUp::rejected, this, &QDialog::close);
}

void PresetRemovalPopUp::accept() {
    try {
        if (!_tab)
            throw std::runtime_error("PresetCreationPopUpManager: DataManager is undefined");

        if (_comboBox->currentIndex() == -1)
            throw std::invalid_argument("PresetCreationPopUpManager: preset name is not selected");

        _tab->removePreset(_comboBox->currentText());
        close();
    } catch(std::runtime_error const & err) {
        _exceptionHandler(err, "Менеджер данных не установлен");
    } catch (std::invalid_argument const & err) {
        _exceptionHandler(err, "Пресет не выбран");
    } catch (PresetDoesNotExistException const & err) {
        _exceptionHandler(err, "Пресета с именем \"" + _comboBox->currentText().toStdString() + "\" не существует");
    }
}

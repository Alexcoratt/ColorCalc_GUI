#include "presetupdatepopup.h"
#include "common_methods.h"

#include <PresetDoesNotExistException.hpp>
#include <ReadOnlyConnectionException.hpp>

PresetUpdatePopUp::PresetUpdatePopUp(ITab * tab, std::function<void(std::exception const &, std::string const &)> const & exceptionHandler, QWidget *parent)
    : InputPopUp{parent}
{
    _comboBox = common_methods::getComboBox();
    setInputWidget(_comboBox);
    common_methods::fillComboBox(_comboBox, tab->getDataManager()->getConnection()->getPresetNames());

    _exceptionHandler = exceptionHandler;
    _tab = tab;

    setWindowTitle("Обновить пресет");
    setInfo("Выберите имя пресета, который хотите обновить");
    _comboBox->setPlaceholderText("Не выбрано");
    _comboBox->setCurrentIndex(-1);

    connect(this, &InputPopUp::accepted, this, &PresetUpdatePopUp::accept);
    connect(this, &InputPopUp::rejected, this, &QDialog::close);
}

void PresetUpdatePopUp::accept() {
    try {
        if (!_tab)
            throw std::runtime_error("PresetCreationPopUpManager: DataManager is undefined");

        if (_comboBox->currentIndex() == -1)
            throw std::invalid_argument("PresetCreationPopUpManager: preset name is not selected");

        _tab->updatePreset(_comboBox->currentText());
        close();

    } catch(std::runtime_error const & err) {
        _exceptionHandler(err, "Менеджер данных не установлен");
    } catch (std::invalid_argument const & err) {
        _exceptionHandler(err, "Пресет не выбран");
    } catch (PresetDoesNotExistException const & err) {
        _exceptionHandler(err, "Пресета с именем \"" + _comboBox->currentText().toStdString() + "\" не существует");
    } catch (ReadOnlyConnectionException const & err) {
        _exceptionHandler(err, "Данный источник открыт только для записи (изменения сохранены до перезапуска приложения)");
        _tab->update();
        close();
    } catch (std::exception const & err) {
        _exceptionHandler(err, "Неизвестная ошибка: " + std::string(err.what()));
    }
}

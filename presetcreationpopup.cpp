#include <iostream>
#include <PresetAlreadyExistsException.hpp>
#include "presetcreationpopup.h"

PresetCreationPopUp::PresetCreationPopUp(ITab * tab, std::function<void(std::exception const &, std::string const &)> const & exceptionHandler, QWidget *parent)
    : InputPopUp{parent}
{
    setInputWidget(&_lineEdit);
    _tab = tab;
    _exceptionHandler = exceptionHandler;

    setWindowTitle("Создать пресет");
    setInfo("Введите имя пресета");
    _lineEdit.setPlaceholderText("Имя пресета");

    connect(this, &InputPopUp::accepted, this, &PresetCreationPopUp::accept);
    connect(this, &InputPopUp::rejected, this, &QDialog::close);
}

void PresetCreationPopUp::accept() {
    try {
        if (!_tab) {
            throw std::runtime_error("PresetCreationPopUpManager: DataManager is undefined");
        }

        QString name = _lineEdit.text();
        if (name.isEmpty())
            throw std::invalid_argument("PresetCreationPopUpManager: LineEdit is empty");

        _tab->createPreset(name);
        close();

    } catch(std::runtime_error const & err) {
        _exceptionHandler(err, "Менеджер данных не установлен");
    } catch (std::invalid_argument const & err) {
        _exceptionHandler(err, "Строка ввода пуста");
    } catch (PresetAlreadyExistsException const & err) {
        _exceptionHandler(err, "Пресет с именем \"" + _lineEdit.text().toStdString() + "\" уже существует");
    }
}

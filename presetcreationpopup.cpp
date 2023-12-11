#include <iostream>
#include <PresetAlreadyExistsException.hpp>
#include <ReadOnlyConnectionException.hpp>
#include <TableConnectionManager.hpp>
#include "presetcreationpopup.h"

#include <QVBoxLayout>

PresetCreationPopUp::PresetCreationPopUp(ITab * tab, std::function<void(std::exception const &, std::string const &)> const & exceptionHandler, QWidget *parent)
    : InputPopUp{parent}
{
    _tab = tab;
    _centralLayout = new QVBoxLayout{};
    _centralLayout->addWidget(&_lineEdit);

    auto mgr = dynamic_cast<TableConnectionManager *>(_tab->getDataManager()->getConnection());
    if (mgr) {
        auto nestedConnections = mgr->getConnections();
        for (auto const * conn : nestedConnections) {
            std::string connName = conn->getName();
            if (conn->isReadOnly())
                connName.append(" (только для чтения)");
            _targetConnection.addItem(QString::fromStdString(connName));
        }
        _centralLayout->addWidget(&_targetConnection);
        _targetConnection.setCurrentIndex(nestedConnections.size() - 1);
    }

    _centralWidget = new QWidget{};
    _centralWidget->setLayout(_centralLayout);
    setInputWidget(_centralWidget);
    _exceptionHandler = exceptionHandler;

    setWindowTitle("Создать пресет");
    setInfo("Введите имя пресета");
    _lineEdit.setPlaceholderText("Имя пресета");

    connect(this, &InputPopUp::accepted, this, &PresetCreationPopUp::accept);
    connect(this, &InputPopUp::rejected, this, &QDialog::close);
}

PresetCreationPopUp::~PresetCreationPopUp() {
    delete _centralLayout;
    //delete _centralWidget; // something's deleting it before I do :(
}

class TabIsUndefinedException : public std::exception {
private:
    std::string _msg;

public:
    TabIsUndefinedException(std::string const & sender) : _msg(sender + ": tab is undefined") {}
    char const * what() const noexcept { return _msg.c_str(); }
};

class LineEditIsEmptyException : public std::exception {
private:
    std::string _msg;

public:
    LineEditIsEmptyException(std::string const & sender) : _msg(sender + ": QLineEdit is empty") {}
    char const * what() const noexcept { return _msg.c_str(); }
};

void PresetCreationPopUp::accept() {
    try {
        if (!_tab) {
            throw TabIsUndefinedException("PresetCreationPopUpManager");
        }

        QString name = _lineEdit.text();
        if (name.isEmpty())
            throw LineEditIsEmptyException("PresetCreationPopUpManager");

        auto mgr = dynamic_cast<TableConnectionManager *>(_tab->getDataManager()->getConnection());
        if (mgr)
            _tab->createPreset(name, mgr->getConnections()[_targetConnection.currentIndex()]);
        else
            _tab->createPreset(name);
        close();

    } catch(TabIsUndefinedException const & err) {
        _exceptionHandler(err, "Менеджер данных не установлен");
    } catch (LineEditIsEmptyException const & err) {
        _exceptionHandler(err, "Строка ввода пуста");
    } catch (PresetAlreadyExistsException const & err) {
        _exceptionHandler(err, "Пресет с именем \"" + _lineEdit.text().toStdString() + "\" уже существует");
    } catch (ReadOnlyConnectionException const & err) {
        _exceptionHandler(err, "Данный источник открыт только для записи (изменения сохранены до перезапуска приложения)");
        _tab->update();
        close();
    } catch (std::exception const & err) {
        _exceptionHandler(err, "Неизвестная ошибка: " + std::string(err.what()));
    }
}

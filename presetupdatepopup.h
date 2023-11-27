#ifndef PRESETUPDATEPOPUP_H
#define PRESETUPDATEPOPUP_H

#include <QWidget>
#include <QComboBox>

#include "inputpopup.h"
#include "itab.h"

class PresetUpdatePopUp : public InputPopUp
{
    Q_OBJECT

public:
    explicit PresetUpdatePopUp(ITab * tab, std::function<void(std::exception const &, std::string const &)> const & exceptionHandler, QWidget *parent = nullptr);

private slots:
    void accept();

private:
    QComboBox _comboBox;
    ITab * _tab;
    std::function<void(std::exception const &, std::string const &)> _exceptionHandler;
};

#endif // PRESETUPDATEPOPUP_H

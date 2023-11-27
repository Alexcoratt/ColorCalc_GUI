#ifndef PRESETREMOVALPOPUP_H
#define PRESETREMOVALPOPUP_H

#include <QWidget>
#include <QComboBox>

#include <inputpopup.h>
#include "itab.h"

class PresetRemovalPopUp : public InputPopUp
{
    Q_OBJECT

public:
    PresetRemovalPopUp(ITab * tab, std::function<void(std::exception const &, std::string const &)> const & exceptionHandler, QWidget *parent = nullptr);

private slots:
    void accept();

private:
    QComboBox * _comboBox;
    ITab * _tab;
    std::function<void(std::exception const &, std::string const &)> _exceptionHandler;
};

#endif // PRESETREMOVALPOPUP_H

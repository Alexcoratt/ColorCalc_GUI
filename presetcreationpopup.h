#ifndef PRESETCREATIONPOPUP_H
#define PRESETCREATIONPOPUP_H

#include <inputpopup.h>
#include <QLineEdit>
#include "itab.h"

class PresetCreationPopUp : public InputPopUp
{
    Q_OBJECT
public:
    explicit PresetCreationPopUp(ITab * tab, std::function<void(std::exception const &, std::string const &)> const & exceptionHandler, QWidget *parent = nullptr);

private slots:
    void accept();

private:
    QLineEdit _lineEdit;
    ITab * _tab;
    std::function<void(std::exception const &, std::string const &)> _exceptionHandler;


signals:

};

#endif // PRESETCREATIONPOPUP_H

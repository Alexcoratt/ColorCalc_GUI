#ifndef PRESETCREATIONPOPUP_H
#define PRESETCREATIONPOPUP_H

#include <inputpopup.h>
#include <QLineEdit>
#include <QComboBox>
#include <QLayout>
#include "itab.h"

class PresetCreationPopUp : public InputPopUp
{
    Q_OBJECT
public:
    explicit PresetCreationPopUp(ITab * tab, std::function<void(std::exception const &, std::string const &)> const & exceptionHandler, QWidget *parent = nullptr);
    ~PresetCreationPopUp();

private slots:
    void accept();

private:
    QLineEdit _lineEdit;
    QComboBox _targetConnection;

    QLayout * _centralLayout;
    QWidget * _centralWidget;

    ITab * _tab;
    std::function<void(std::exception const &, std::string const &)> _exceptionHandler;


signals:

};

#endif // PRESETCREATIONPOPUP_H

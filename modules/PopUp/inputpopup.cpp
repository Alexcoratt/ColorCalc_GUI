#include "inputpopup.h"
#include "./ui_inputpopup.h"

InputPopUp::InputPopUp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InputPopUp)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, [&]() { emit accepted(); });
    connect(ui->buttonBox, &QDialogButtonBox::rejected, [&]() { emit rejected(); });
}

InputPopUp::~InputPopUp()
{
    delete ui;
}

QDialogButtonBox * InputPopUp::getDialogButtonBox() { return ui->buttonBox; }

QWidget const * InputPopUp::getInputWidget() const { return _inputWidget; }
QWidget * InputPopUp::getInputWidget() { return _inputWidget; }
void InputPopUp::setInputWidget(QWidget * widget) {
    if (_inputWidget == widget)
        return;

    if (ui->inputWidgetLayout->isEmpty())
        ui->inputWidgetLayout->addWidget(widget);
    else
        ui->inputWidgetLayout->replaceWidget(_inputWidget, widget);

    _inputWidget = widget;
}

void InputPopUp::setInfo(QString const & info) { ui->infoLabel->setText(info); }


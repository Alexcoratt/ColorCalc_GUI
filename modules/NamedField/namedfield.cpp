#include "namedfield.h"
#include "./ui_namedfield.h"

NamedField::NamedField(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NamedField)
{
    ui->setupUi(this);
    setName("name");
    setUnits("units");
}

NamedField::~NamedField()
{
    delete ui;
}

QWidget const * NamedField::getWidget() const { return _field; }
QWidget * NamedField::getWidget() { return _field; }
void NamedField::setWidget(QWidget * field) {
    if (_field == field)
        return;

    if (ui->fieldLayout->isEmpty())
        ui->fieldLayout->addWidget(field);
    else
        ui->fieldLayout->replaceWidget(_field, field);
    _field = field;
}

QString NamedField::getName() const { return _name; }
void NamedField::setName(QString const & name) {
    ui->nameLabel->setText(name);
    _name = name;
}

QString NamedField::getUnits() const { return _units; }
void NamedField::setUnits(QString const & units) {
    ui->unitsLabel->setText(units);
    _units = units;
}

void NamedField::set(QWidget * widget, QString const & name, QString const & units) {
    setWidget(widget);
    setName(name);
    setUnits(units);
}


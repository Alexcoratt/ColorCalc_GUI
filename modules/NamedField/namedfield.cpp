#include "namedfield.h"
#include "./ui_namedfield.h"
#include "QMessageBox"

NamedField::NamedField(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NamedField)
{
    ui->setupUi(this);
    setName("name");
    setUnits("units");
    setHelpText("help text");

    connect(ui->helpButton, &QPushButton::clicked, this, &NamedField::helpButtonClicked);
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

QString NamedField::getName() const { return ui->nameLabel->text(); }
void NamedField::setName(QString const & name) { ui->nameLabel->setText(name); }
QLabel * NamedField::getNameLabel() { return ui->nameLabel; }

QString NamedField::getHelpText() const { return _helpText; }
void NamedField::setHelpText(QString const & text) { _helpText = text; }

bool NamedField::getHelpButtonVisible() const { return ui->helpButton->isVisible(); }
void NamedField::setHelpButtonVisible(bool isVisible) { ui->helpButton->setVisible(isVisible); }

QString NamedField::getUnits() const { return ui->unitsLabel->text(); }
void NamedField::setUnits(QString const & units) { ui->unitsLabel->setText(units); }
QLabel * NamedField::getUnitsLabel() { return ui->unitsLabel; }

void NamedField::helpButtonClicked() {
    QMessageBox mb;
    mb.setWindowTitle(getName());
    mb.setText(_helpText);
    mb.exec();
}

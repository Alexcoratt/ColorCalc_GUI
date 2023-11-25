#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QLineEdit>
#include <QComboBox>

#define LINE_EDIT_PLACEHOLDER "Введите значение"
#define COMBO_BOX_PLACEHOLDER "Не выбрано"

class MutableQString : public QString {
private:
    std::shared_ptr<QString> _string;

public:
    MutableQString(const char * str) : _string(new QString{str}) {}
    MutableQString(MutableQString const & other) : _string(other._string) {}
};

std::shared_ptr<QLineEdit> getLineEdit(QString const & placeholder = LINE_EDIT_PLACEHOLDER, bool readOnly = false) {
    std::shared_ptr<QLineEdit> lineEdit{ new QLineEdit };
    lineEdit->setPlaceholderText(placeholder);
    lineEdit->setReadOnly(readOnly);
    return lineEdit;
}

std::shared_ptr<QLineEdit> getLineEdit(bool readOnly) {
    return getLineEdit(LINE_EDIT_PLACEHOLDER, readOnly);
}

std::shared_ptr<QComboBox> getComboBox(QString const & placeholder = COMBO_BOX_PLACEHOLDER) {
    std::shared_ptr<QComboBox> comboBox{ new QComboBox };
    comboBox->setPlaceholderText(placeholder);
    return comboBox;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // setting up paint calculation tab
    ui->paintPresetField->set(getComboBox(), "Имя пресета");
    ui->paintTypeField->set(getComboBox(), "Тип краски");
    ui->materialTypeField->set(getComboBox(), "Тип материала");

    ui->paintConsumptionField->set(getLineEdit(), "Расход краски", "г/м2");
    ui->dividerField->set(getLineEdit(), "Делитель");
    ui->percentageField->set(getLineEdit(), "Процент запечатки", "%");
    ui->sheetWidthField->set(getLineEdit(), "Ширина печатного листа", "мм");
    ui->sheetLengthField->set(getLineEdit(), "Длина печатного листа", "мм");
    ui->circulationField->set(getLineEdit(), "Тираж");
    ui->paintReserveField->set(getLineEdit(), "Запас краски", "кг");

    ui->pcResultField->set(getLineEdit(true), "Результат вычислений", "кг");
}

MainWindow::~MainWindow()
{
    delete ui;
}


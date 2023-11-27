#include "common_methods.h"

QLineEdit * common_methods::getLineEdit(QString const & placeholder, bool readOnly) {
    QLineEdit * lineEdit = new QLineEdit ;
    lineEdit->setPlaceholderText(placeholder);
    lineEdit->setReadOnly(readOnly);
    return lineEdit;
}

QComboBox * common_methods::getComboBox(QString const & placeholder) {
    QComboBox * comboBox = new QComboBox;
    comboBox->setPlaceholderText(placeholder);
    return comboBox;
}

QComboBox * getComboBox(std::vector<std::string> const & items, QString const & placeholder) {
    QComboBox * comboBox = common_methods::getComboBox(placeholder);
    common_methods::fillComboBox(comboBox, items);
    return comboBox;
}

void common_methods::fillComboBox(QComboBox * comboBox, std::vector<std::string> const & items) {
    comboBox->clear();
    for (auto const & option : items)
        comboBox->addItem(option.c_str());
}

void common_methods::setComboBoxIndex(QComboBox * comboBox, QString const & value) {
    QSignalBlocker blocker(comboBox);
    comboBox->setCurrentIndex(comboBox->findText(value));
    blocker.unblock();
}

void common_methods::setComboBoxIndex(QComboBox * comboBox, std::function<QString()> get) {
    try {
        setComboBoxIndex(comboBox, get());
    } catch (std::exception const & err) {
        comboBox->setCurrentIndex(-1);
        std::cerr << err.what() << std::endl;
    }
}

void common_methods::setComboBoxIndex(QComboBox * comboBox, std::function<std::string()> get) {
    try {
        setComboBoxIndex(comboBox, QString::fromStdString(get()));
    } catch (std::exception const & err) {
        comboBox->setCurrentIndex(-1);
        std::cerr << err.what() << std::endl;
    }
}

double common_methods::toDouble(QString const & line) {
    bool isCorrect;
    auto res = line.toDouble(&isCorrect);
    if (isCorrect)
        return res;
    throw std::invalid_argument("toDouble: invalid line \"" + line.toStdString() + "\"");
}

double common_methods::toULong(QString const & line) {
    bool isCorrect;
    auto res = line.toULong(&isCorrect);
    if (isCorrect)
        return res;
    throw std::invalid_argument("toULong: invalid line \"" + line.toStdString() + "\"");
}

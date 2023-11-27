#ifndef COMMON_METHODS_H
#define COMMON_METHODS_H

#include <QLineEdit>
#include <QComboBox>
#include <QString>
#include <sstream>
#include <iostream>

namespace common_methods {

constexpr char const * LINE_EDIT_PLACEHOLDER{"Введите значение"};
constexpr char const * COMBO_BOX_PLACEHOLDER{"Не выбрано"};

QLineEdit * getLineEdit(QString const & placeholder = LINE_EDIT_PLACEHOLDER, bool readOnly = false);
QComboBox * getComboBox(QString const & placeholder = COMBO_BOX_PLACEHOLDER);
void fillComboBox(QComboBox * comboBox, std::vector<std::string> const & options);

void setComboBoxIndex(QComboBox * comboBox, QString const & value);
void setComboBoxIndex(QComboBox * comboBox, std::function<QString()> get);
void setComboBoxIndex(QComboBox * comboBox, std::function<std::string()> get);

template<typename T>
std::string toString(T const & n);

template <typename T>
void setLineEditValue(QLineEdit * lineEdit, std::function<T()> const & get);

template <typename T, typename V>
void setManagerParam(std::function<void(T)> const & set, std::function<void()> const & clear, V const & value, std::function<T(V)> const & converter);

double toDouble(QString const & line);
double toULong(QString const & line);

}

template<typename T>
std::string common_methods::toString(T const & n) {
    std::ostringstream oss;
    oss << n;
    std::string s =  oss.str();
    int dotpos = s.find_first_of('.');
    if(dotpos!=std::string::npos){
        int ipos = s.size()-1;
        while(s[ipos]=='0' && ipos>dotpos){
            --ipos;
        }
        s.erase ( ipos + 1, std::string::npos );
    }
    return s;
}

template <typename T>
void common_methods::setLineEditValue(QLineEdit * lineEdit, std::function<T()> const & get) {
    QSignalBlocker blocker(lineEdit);
    try {
        lineEdit->setText(QString::fromStdString(toString(get())));
    } catch (std::exception const & err) {
        lineEdit->clear();
        std::cerr << err.what() << std::endl;
    }
    blocker.unblock();
}

template <typename T, typename V>
void common_methods::setManagerParam(std::function<void(T)> const & set, std::function<void()> const & clear, V const & value, std::function<T(V)> const & converter) {
    try {
        set(converter(value));
        std::cout << "OK" << std::endl;
    } catch (std::exception const & err) {
        clear();
        std::cout << err.what() << std::endl;
    }
}

#endif // COMMON_METHODS_H

#include "inputpopup.h"

#include <QApplication>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InputPopUp w;
    w.show();

    QLineEdit * lineEdit = new QLineEdit;
    w.setInputWidget(lineEdit);

    return a.exec();
}

#include "namedfield.h"

#include <QApplication>
#include <QLineEdit>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NamedField w;
    w.setHelpText("help text");
    w.setHelpButtonVisible(true);
    QWidget * widget = new QLineEdit();
    w.setWidget(widget);
    w.show();
    return a.exec();
}

#ifndef INPUTPOPUP_H
#define INPUTPOPUP_H

#include <QDialog>
#include <QDialogButtonBox>

QT_BEGIN_NAMESPACE
namespace Ui { class InputPopUp; }
QT_END_NAMESPACE

class InputPopUp : public QDialog
{
    Q_OBJECT

public:
    InputPopUp(QWidget *parent = nullptr);
    ~InputPopUp();

    QDialogButtonBox * getDialogButtonBox();

    QWidget const * getInputWidget() const;
    QWidget * getInputWidget();
    void setInputWidget(QWidget *);
    void setInfo(QString const &);

private:
    Ui::InputPopUp *ui;

    QWidget * _inputWidget;
};
#endif // INPUTPOPUP_H

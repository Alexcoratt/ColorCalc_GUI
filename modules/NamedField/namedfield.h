#ifndef NAMEDFIELD_H
#define NAMEDFIELD_H

#include <memory>

#include <QWidget>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class NamedField; }
QT_END_NAMESPACE

class NamedField : public QWidget
{
    Q_OBJECT

public:
    NamedField(QWidget *parent = nullptr);
    ~NamedField();

    QWidget const * getWidget() const;
    QWidget * getWidget();
    void setWidget(QWidget *);

    QString getName() const;
    void setName(QString const &);

    QString getUnits() const;
    void setUnits(QString const &);

    void set(QWidget *, QString const & name, QString const & units = "");

private:
    Ui::NamedField *ui;
    QWidget * _field;
    QString _name;
    QString _units;
};
#endif // NAMEDFIELD_H

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

    QString getHelpText() const;
    void setHelpText(QString const &);

    bool getHelpButtonVisible() const;
    void setHelpButtonVisible(bool isVisible);

    QString getUnits() const;
    void setUnits(QString const &);

public slots:
    void helpButtonClicked();

private:
    Ui::NamedField *ui;
    QWidget * _field;

    QString _helpText;
};
#endif // NAMEDFIELD_H

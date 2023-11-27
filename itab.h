#ifndef ITAB_H
#define ITAB_H

#include <QObject>

class ITab : public QObject
{
    Q_OBJECT
public:
    //explicit ITab(QObject *parent = nullptr);
    virtual ~ITab() {}

    virtual void createPreset(QString const & name) = 0;
    virtual void updatePreset(QString const & name) = 0;
    virtual void removePreset(QString const & name) = 0;

    virtual void loadPreset(QString const & name) = 0;

public slots:
    virtual void clear() = 0;
    virtual void update() = 0;

signals:

};

#endif // ITAB_H

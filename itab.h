#ifndef ITAB_H
#define ITAB_H

#include <QObject>
#include <IDataManager.hpp>

class ITab : public QObject
{
    Q_OBJECT
public:
    virtual ~ITab() {}

    virtual IDataManager const * getDataManager() const = 0;
    virtual IDataManager * getDataManager() = 0;

public slots:
    virtual void clear();

    virtual void update() = 0;

    virtual void createPreset(QString const & name);
    virtual void updatePreset(QString const & name);
    virtual void removePreset(QString const & name);

    virtual void loadPreset(QString const & name);

signals:

};

#endif // ITAB_H

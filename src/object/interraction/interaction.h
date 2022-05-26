#ifndef INTERACTION_H
#define INTERACTION_H
#include <QString>
#include <QGraphicsItem>
#include <src/object/vesselobject.h>

class Interaction : public QGraphicsItem
{
    QString name = "";
    VesselObject * interractableVesselObject;
public:
    Interaction(VesselObject * obj, QString name);

    QString getInterractionName();
    VesselObject * getVesselObject();

    void setNewName(QString newName);
    void setNewVesselObject(VesselObject * obj);

    virtual void Interract();
};

#endif // INTERACTION_H

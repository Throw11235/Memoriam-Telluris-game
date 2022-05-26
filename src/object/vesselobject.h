#ifndef VESSELOBJECT_H
#define VESSELOBJECT_H
#include <QGraphicsItem>
#include <QTimer>
#include <src/object/vessel.h>
#include <src/object/vesselobjecttype.h>

#define OBJECT_TYPE 1001

class Interaction;

class VesselObject : public QGraphicsItem
{
private:
    float mass = 0.0;

    float objectWidth = 0.0;
    float objectHeight = 0.0;

    float coordinateRotation = 0.0;
    float objectRotation = 0.0;

    QString pathToSpriteFile = "";

    QVector2D relativeCoordinates = QVector2D(0,0);

    Vessel * refPoint = nullptr;

    QVector2D speed = QVector2D(0,0);


    float rotationSpeed = 0.0;


    std::list<Interaction*> interractionList = {};

public:
    VesselObject(QString spritePath, std::list<Interaction*> interractions, float width, float heigth, Vessel * refpoint, float x, float y, float mass);
    VesselObject(nlohmann::json & json, Vessel * boundVessel, std::map<std::string ,VesselObjectType*> & objecttypes, std::list<std::string> & exeptions);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void rotateClockwise(float relRotation);

    QVector2D & getRelativeCoordinates();

    float getMass();

    int type() const override;

    float getRotation();

    QString getSpriteFile();

    float getOwnRotation();

    Vessel * getVessel();

    void UpdateObject();


    virtual nlohmann::json loadToJson();

    void loadFromJSON(nlohmann::json & loadedjson, std::map<std::string,VesselObjectType*> & objecttypes, std::list<std::string> & exeptions);

    void loadPropertiesFromType(VesselObjectType * type);


    void advance(int step) override;

    void setVessel(Vessel * newVessel);

    void setCoordinateRotation(float newRotation);

    void setOwnRotation(float newRotation);
};

#endif // VESSELOBJECT_H

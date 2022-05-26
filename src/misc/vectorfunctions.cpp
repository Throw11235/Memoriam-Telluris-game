#include "vectorfunctions.h"

QVector2D RotateVector(QVector2D  toRotate, float angle){
    //Convert vector to a point with same coordinates
    QPointF initialCoords = toRotate.toPointF();

    QTransform rotationAroundCenter = QTransform();

        //rotate system of coordinates and get shifted position
        rotationAroundCenter.rotate(-angle);
        rotationAroundCenter.translate(initialCoords.x(), initialCoords.y());

    //Get coordinates out of QTransform
    QPointF resultVectorCoords = rotationAroundCenter.map(QPointF());

    return QVector2D(resultVectorCoords.x(), resultVectorCoords.y());
}

#include "grid.h"
#include <src/object/vesselobject.h>

Grid::Grid(Vessel * vessel, int gridsize)
{
    connectedVessel = vessel;
    gridSize = gridsize;
}

void Grid::buildGrid(){

}

void Grid::deleteGrid(){

}

void Grid::redrawGrid(){

}

GridSection * Grid::getClosestSection(QPointF position){
    QPointF distanceToAnchor = position - gridAnchorPoint->pos();

    double minDistance = gridSize * gridSize * 16;

    GridSection * selectedGrid = gridLayout[0][0];

    for(unsigned int i = 0; i < gridSize; i++){
        for(unsigned int j = 0; j < gridSize; j++){
            if(QVector2D(distanceToAnchor - gridLayout[i][j]->getRelPosition().toPointF()).lengthSquared() < minDistance){
                selectedGrid = gridLayout[i][j];
                minDistance = QVector2D(distanceToAnchor - gridLayout[i][j]->getRelPosition().toPointF()).lengthSquared();
            }
        }
    }

    return selectedGrid;
}

void Grid::setNewAnchor(VesselObject *anchor){
    gridAnchorPoint = anchor;
}

VesselObject * Grid::getGridAnchor(){
    return gridAnchorPoint;
}

Vessel * Grid::getConnectedVessel(){
    return connectedVessel;
}

void Grid::setGridSize(int newSize){
    gridSize = newSize;
}

int Grid::getGridSize(){
    return gridSize;
}


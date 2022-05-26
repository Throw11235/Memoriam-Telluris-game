#ifndef GRID_H
#define GRID_H
#include <src/graphics/gridsection.h>
#include <src/object/vesselobject.h>

class Grid
{
    //grid pieces sorted by x and y values in ascended order
    std::vector<std::vector<GridSection*>> gridLayout = {};

    unsigned int gridSize = 0;

    Vessel * connectedVessel = nullptr;

    VesselObject * gridAnchorPoint = nullptr;

public:
    Grid(Vessel * vessel, int gridsize);

    ~Grid();

    void buildGrid();

    GridSection * getClosestSection(QPointF position);

    void redrawGrid();

    void deleteGrid();

    void setNewAnchor(VesselObject * anchor);

    void setGridSize(int newSize);

    int getGridSize();

    VesselObject * getGridAnchor();

    Vessel * getConnectedVessel();

};

#endif // GRID_H

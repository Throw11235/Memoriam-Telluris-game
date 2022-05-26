#ifndef MOUSEFOLLOWINGTOOL_H
#define MOUSEFOLLOWINGTOOL_H

#include <QGraphicsItem>

// Abstract class from which all mouse following items are inherited

class MouseFollowingTool : public QGraphicsItem
{
    //Set the keys what are not processed by camera, i.e. q and e keys for placer
    std::list<int> restrictedKeys = {};

public:
    MouseFollowingTool();

    virtual void onClick();

    virtual void onKeyPress();

    std::list<int> & getRestrictedKeys();

    void setRestrictedKeys(std::list<int> & newkeys);
};

#endif // MOUSEFOLLOWINGTOOL_H

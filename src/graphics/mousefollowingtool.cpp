#include "mousefollowingtool.h"

MouseFollowingTool::MouseFollowingTool()
{

}

void MouseFollowingTool::onClick(){
    return;
}

void MouseFollowingTool::onKeyPress(){
    return;
}

std::list<int> & MouseFollowingTool::getRestrictedKeys(){
    return restrictedKeys;
}

void MouseFollowingTool::setRestrictedKeys(std::list<int> &newkeys){
    restrictedKeys = newkeys;
}

#include "decorativeuiwidget.h"
#include <QPixmap>

decorativeUIWidget::decorativeUIWidget(QString spritefile, float x, float y, float width, float height)
{
    this->setPixmap(QPixmap(spritefile));
    this->setGeometry(x,y,width, height);
}

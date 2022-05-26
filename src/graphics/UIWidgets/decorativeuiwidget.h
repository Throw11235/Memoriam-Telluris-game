#ifndef DECORATIVEUIWIDGET_H
#define DECORATIVEUIWIDGET_H
#include <QLabel>

class decorativeUIWidget : public QLabel
{
    QString pathToSpriteFile = "";
public:
    decorativeUIWidget(QString spritefile, float x, float y, float width, float height);
};

#endif // DECORATIVEUIWIDGET_H

#ifndef INTERFACESUBWINDOW_H
#define INTERFACESUBWINDOW_H

#include <QScrollArea>


class InterfaceSubwindow : public QScrollArea
{
    QObject * connectedObject = nullptr;

    int lastKeyPressed = -1;

public:
    InterfaceSubwindow(QWidget * parentWidget,  QRect & windowRect, QObject * toConnect, QString stylesheet = "");

    void addButton(QRect & buttonRect, const QMetaMethod & method , QString spriteOrText, bool isTextButton = false, QString stylesheet = "");

    void addSideWidget(QWidget * widget,  QRect & pos, QWidget * optionalParent = nullptr);


    void keyPressEvent(QKeyEvent *event) override;
    int getLastPressedKey();
};

#endif // INTERFACESUBWINDOW_H

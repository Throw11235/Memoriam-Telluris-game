QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/atmospherics/special_container_types/externalgascontainer.cpp \
    src/atmospherics/special_container_types/pumpgascontainer.cpp \
    src/file_management/modloader.cpp \
    src/game.cpp \
    src/gamesettings.cpp \
    src/graphics/UIWidgets/decorativeuiwidget.cpp \
    src/graphics/UIWidgets/objectplacementfactorybutton.cpp \
    src/graphics/UIWidgets/timespeedbutton.cpp \
    src/graphics/camera.cpp \
    src/graphics/grid.cpp \
    src/graphics/gridsection.cpp \
    src/graphics/interfacesubwindow.cpp \
    src/graphics/masscenterindicator.cpp \
    src/graphics/mousefollowingtool.cpp \
    src/graphics/objectplacementsprite.cpp \
    src/graphics/selectedobjectsprite.cpp \
    src/main.cpp \
    src/gamewindow.cpp \
    src/misc/vectorfunctions.cpp \
    src/nbodysim/celestialbody2d.cpp \
    src/nbodysim/celestialbodysprites.cpp \
    src/nbodysim/nbody2d.cpp \
    src/nbodysim/nbodyphysicssimulation.cpp \
    src/atmospherics/gas.cpp \
    src/atmospherics/gascontainer.cpp \
    src/atmospherics/gasmix.cpp \
    src/nbodysim/nbodysprites.cpp \
    src/object/interraction/interaction.cpp \
    src/object/interraction/specific_interactions/toggleinteraction.cpp \
    src/object/vessel.cpp \
    src/object/vesselobject.cpp \
    src/object/vesselobjectsprite.cpp \
    src/object/vesselobjecttype.cpp \
    src/uimanager.cpp

HEADERS += \
    src/atmospherics/special_container_types/externalgascontainer.h \
    src/atmospherics/special_container_types/pumpgascontainer.h \
    src/file_management/modloader.h \
    src/game.h \
    src/gamesettings.h \
    src/gamewindow.h \
    src/graphics/UIWidgets/decorativeuiwidget.h \
    src/graphics/UIWidgets/objectplacementfactorybutton.h \
    src/graphics/UIWidgets/timespeedbutton.h \
    src/graphics/camera.h \
    src/graphics/grid.h \
    src/graphics/gridsection.h \
    src/graphics/interfacesubwindow.h \
    src/graphics/masscenterindicator.h \
    src/graphics/mousefollowingtool.h \
    src/graphics/objectplacementsprite.h \
    src/graphics/selectedobjectsprite.h \
    src/misc/vectorfunctions.h \
    src/nbodysim/celestialbody2d.h \
    src/nbodysim/celestialbodysprites.h \
    src/nbodysim/nbody2d.h \
    src/nbodysim/nbodyphysicssimulation.h \
    src/atmospherics/gas.h \
    src/atmospherics/gascontainer.h \
    src/atmospherics/gasmix.h \
    src/nbodysim/nbodysprites.h \
    src/object/interraction/interaction.h \
    src/object/interraction/specific_interactions/toggleinteraction.h \
    src/object/vessel.h \
    src/object/vesselobject.h \
    src/object/vesselobjectsprite.h \
    src/object/vesselobjecttype.h \
    src/uimanager.h

FORMS += \
    gamewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Emprunteur.cpp \
    Adresse.cpp \
    Emprunteurs.cpp \
    Vehicules.cpp \
    Moto.cpp \
    Auto.cpp \
    Flotte.cpp \
    Exemplaire.cpp \
    Locations.cpp \
    Location.cpp \
    Date.cpp

HEADERS += \
    Emprunteur.h \
    Adresse.h \
    Emprunteurs.h \
    Vehicules.h \
    Vehicule.h \
    Moto.h \
    Auto.h \
    Flotte.h \
    Exemplaire.h \
    Locations.h \
    Date.h \
    Location.h

QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app
TARGET = DustyParticles
CONFIG += c++11
CONFIG += opengl
INCLUDEPATH += .
OBJECTS_DIR = obj

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    src/Main.cpp \
    src/Vec4.cpp \
    src/Mat4.cpp \
    src/Camera.cpp \
    src/Emitter.cpp \
    src/Particle.cpp

LIBS += -L/usr/local/lib

linux: {
  LIBS+=$$system(sdl2-config --libs)
  LIBS += -lSDL2  -lGLU -lGL -lSDL2_image  -L/usr/local/lib/ #-lglut #-lGLEW
}

macx: {
  DEFINES+=MAC_OS_X_VERSION_MIN_REQUIRED=1060
  QMAKE_LFLAGS += -F/Library/Frameworks
  LIBS += -framework SDL2
  LIBS += -framework SDL2_image
  INCLUDEPATH += /Library/Frameworks/SLD2_image.framework
  INCLUDEPATH += /Library/Frameworks/SDL2.framework/Headers
  INCLUDEPATH += /usr/local/include
  INCLUDEPATH += /usr/local/Cellar

  LIBS+= -framework OpenGL
  LIBS+= -framework GLUT
}

HEADERS += \
    src/Vec4.h \
    src/Mat4.h \
    src/Camera.h \
    src/Emitter.h \
    src/Particle.h

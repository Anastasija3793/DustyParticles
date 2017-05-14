///from Jon Macey (Modified)


#ifndef CAMERA_H
#define CAMERA_H

#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
  #include "GLUT/glut.h"
#include <SDL.h>
#include <SDL_image.h>
#else
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
  #include <GL/gl.h>
  #include <GL/glu.h>
  //#include <GL/glut.h>
#endif

#include "Vec4.h"


class Camera
{
public:
    void lookAt(Vec4 _eye, Vec4 _look, Vec4 _up);
    void perspective(float _fovy,float _aspect, float _zNear, float _zFar);
    float radians(float _deg );
};

#endif // CAMERA_H

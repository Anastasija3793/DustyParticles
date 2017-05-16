/// @file Camera.h
/// @brief camera (to change the view (camera's position and where it looks at))
/// @author Jon Macey

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
#include "Mat4.h"
#include <cmath>

class Camera
{
public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief where camera is looking at
    /// @param[in] _eye camera's position
    /// @param[in] _look where camera looks at (target)
    /// @param[in] _up the up vector
    //----------------------------------------------------------------------------------------------------------------------
    void lookAt(Vec4 _eye, Vec4 _look, Vec4 _up);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the perspective projection
    /// @param[in] _fovy view angle from the bottom-plane to the top-plane
    /// @param[in] _aspect aspect ratio (width/height)
    /// @param[in] _zNear the near of the View Frustum
    /// @param[in] _zFar the far of the View Frustum
    //----------------------------------------------------------------------------------------------------------------------
    void perspective(float _fovy, float _aspect, float _zNear, float _zFar);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the radians
    /// @param[in] _deg degree
    //----------------------------------------------------------------------------------------------------------------------
    float radians(float _deg );
};

#endif // CAMERA_H

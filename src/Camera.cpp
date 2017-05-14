///from Jon Macey


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

#include "Camera.h"
#include "Mat4.h"
#include <cmath>


void Camera::lookAt(Vec4 _eye, Vec4 _look, Vec4 _up)
{
    Vec4 n = _look-_eye;
    Vec4 u = _up;
    Vec4 v = n.cross(u);
    u = v.cross(n);
    n.normalize();
    v.normalize();
    u.normalize();

    Mat4 mv(1.0f);
    mv.m_00= v.m_x;
    mv.m_10= v.m_y;
    mv.m_20= v.m_z;
    mv.m_01= u.m_x;
    mv.m_11= u.m_y;
    mv.m_21= u.m_z;
    mv.m_02=-n.m_x;
    mv.m_12=-n.m_y;
    mv.m_22=-n.m_z;
    mv.m_30=-_eye.dot(v);
    mv.m_31=-_eye.dot(u);
    mv.m_32= _eye.dot(n);
    mv.loadModelView();
}

void Camera::perspective(float _fovy, float _aspect, float _zNear, float _zFar)
{
    float range = tan(radians(_fovy / 2.0)) * _zNear;
    float left = -range * _aspect;
    float right = range * _aspect;
    float bottom = -range;
    float top = range;
    Mat4 result;
    result.m_00 = (2.0f * _zNear) / (right - left);
    result.m_11 = (2.0f * _zNear) / (top - bottom);
    result.m_22 = - (_zFar + _zNear) / (_zFar - _zNear);
    result.m_23 = - 1.0f;
    result.m_32 = - (2.0f* _zFar * _zNear) / (_zFar - _zNear);
    result.loadProjection();
}

float Camera::radians(float _deg)
{
    return (_deg/180.0f) * M_PI;
}

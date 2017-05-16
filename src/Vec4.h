/// @file Vec4.h
/// @brief Enclose Vector object (3D point)
/// @author Jon Macey (Modified by Anastasija Belaka)

#ifndef VEC4_H
#define VEC4_H
#include <array>

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

class Vec4
{

public:

    Vec4()=default;
    Vec4(float _x, float _y, float _z, float _w=1.0) :
        m_x(_x), m_y(_y), m_z(_z), m_w(_w){}
    Vec4 cross(const Vec4 &_r) const;
    void normalize();
    float dot(const Vec4 &_r) const;
    void colourGL() const;
    float length() const;
    float lengthSquared() const;
    void normalGL() const;
    void set(float _x, float _y, float _z, float _w=1.0);
    void vertexGL() const;
    Vec4 operator *(float _rhs)const;
    Vec4 operator -(const Vec4 &_rhs)const;
    //added
    void operator -=(const Vec4 &_rhs);
    //added
    Vec4 operator +(const Vec4 &_rhs) const;
    //added
    void operator +=(const Vec4 &_rhs);

    union
    {
        std::array<float,4> m_openGL={{0.0f,0.0f,0.0f,1.0f}};
        struct
        {
            float m_x;
            float m_y;
            float m_z;
            float m_w;
        };
    };
}; //end class

#endif // VEC4_H

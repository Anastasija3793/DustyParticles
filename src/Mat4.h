/// @file Mat4.h
/// @brief
/// @author Jon Macey

#ifndef MAT4_H
#define MAT4_H
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


//mat4 16 floats
//[1][0][0][0]
//[0][1][0][0]
//[0][0][1][0]
//[0][0][0][1]


 class Mat4
 {

 public:

     Mat4(float _s=1.0f);
     void loadModelView() const;
     void loadProjection() const;
     void identity();
     union
     {
       float m_m[4][4]; // normal 4x4 access
       std::array<float,4> m_openGL; // array access
       struct
       {
         float m_00; //> m_[0][0] m_openGL[0]
         float m_01; //> m_[0][1] m_openGL[1]
         float m_02; //> m_[0][2] m_openGL[2]
         float m_03; //> m_[0][3] m_openGL[3]

         float m_10; //> m_[1][0] m_openGL[4]
         float m_11; //> m_[1][1] m_openGL[5]
         float m_12; //> m_[1][2] m_openGL[6]
         float m_13; //> m_[1][3] m_openGL[7]

         float m_20; //> m_[2][0] m_openGL[8]
         float m_21; //> m_[2][1] m_openGL[9]
         float m_22; //> m_[2][2] m_openGL[10]
         float m_23; //> m_[2][3] m_openGL[11]

         float m_30; //> m_[3][0] m_openGL[12]
         float m_31; //> m_[3][1] m_openGL[13]
         float m_32; //> m_[3][2] m_openGL[14]
         float m_33; //> m_[3][3] m_openGL[15]

       };
     };

 };

#endif // MAT4_H

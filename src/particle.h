#ifndef PARTICLE_H
#define PARTICLE_H

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
#include <cmath>
#include <vector>

#include <algorithm>
#include <cstdlib>


class Particle
{
public:

    Particle(Vec4 _pos, Vec4 _col, Vec4 _vel, bool _notBoom, bool _notFreeze);

    //draw function
    void draw();

    //update function
    void update();

    inline void setCol(Vec4 _col) {m_col = Vec4(_col.m_x,_col.m_y,_col.m_z,m_col.m_w);}

    inline void partExplode(bool _notBoom){m_notBoom = false;}

    inline void freeze(bool _notFreeze){m_notFreeze = false;}

private:
    Vec4 m_col;
    Vec4 m_randCol;

    Vec4 m_velocity; // PUBLIC?

    bool m_notBoom; // PUBLIC?

    bool m_notFreeze; // PUBLIC?
    Vec4 m_pos; //position

    Vec4 m_startPos;
    float m_size;
    float m_randSize;
    //int m_speed;
    int m_lifetime;
    int m_nowLife;
    //int m_isDead;
    //float m_alpha;

};

#endif // PARTICLE_H

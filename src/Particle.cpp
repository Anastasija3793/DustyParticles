#include "Particle.h"
#include "Vec4.h"

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

#include <GL/gl.h>
#include <cmath>
#include <vector>

#include <math.h>

#include <algorithm>
#include <cstdlib>


Particle::Particle(Vec4 _pos, Vec4 _col, Vec4 _vel, bool _notBoom, bool _notFreeze, bool _notGalaxyDust)
{
    m_pos = _pos;
    m_startPos = _pos;
    m_col = _col;
    m_velocity = _vel;
    m_notBoom = _notBoom;
    m_notFreeze = _notFreeze;
    m_notGalaxyDust = _notGalaxyDust;
    m_size = 2.0f;
    m_randSize = (float)rand()/RAND_MAX*0.02-0.001;
    m_lifetime=200;
    m_nowLife=0;
}

void Particle::draw()
{
    //to smooth points
    glEnable(GL_POINT_SMOOTH);

    //for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(m_col.m_x,m_col.m_y,m_col.m_z,m_col.m_w);

    glPointSize(m_size);
    glBegin(GL_POINTS);
    glVertex4f(m_pos.m_x,m_pos.m_y,m_pos.m_z,m_pos.m_w);
    glEnd();
}

void Particle::update()
{
    ++m_nowLife;
    m_size+=m_randSize;
    m_col.m_w-=0.0035f;
    m_pos+=m_velocity;
    m_velocity.set((float)rand()/RAND_MAX*0.02-0.001,(float)rand()/RAND_MAX*0.02+0.001,(float)rand()/RAND_MAX*0.02-0.007,1.0f); //without it particles stop (only emitter is moving)

    if (!m_notBoom)
    {
        m_velocity.set((0.09 * M_PI * (float)rand())/RAND_MAX, (0.09 * M_PI * (float)rand())/RAND_MAX, (0.09 * M_PI * (float)rand())/RAND_MAX, 1.0f);
    }

    //to stop the movement of particles (and emitter)
    if(!m_notFreeze)
    {
        m_velocity.set(0.0f,0.0f,0.0f,1.0f);
        m_randSize = 0.0f;
    }

    if(!m_notGalaxyDust)
    {
        m_pos.set((float)rand()/RAND_MAX*1.5-0.8,(float)rand()/RAND_MAX*1.5-0.8,(float)rand()/RAND_MAX*1.5-0.8,1.0f);
        m_pos.normalize();
        m_col.set(0.5+0.5*(float)rand()/RAND_MAX,0.5+0.5*(float)rand()/RAND_MAX,0.5+0.5*(float)rand()/RAND_MAX,1.0f);
        m_randSize = 0.0f;
        m_size = (float)rand()/RAND_MAX*5.0;
    }


    if(m_nowLife > m_lifetime)
    {
        m_pos=m_startPos;
        m_velocity.set((float)rand()/RAND_MAX*0.02-0.001,(float)rand()/RAND_MAX*0.02+0.001,(float)rand()/RAND_MAX*0.02-0.007,1.0f);
        m_nowLife=0;
        m_size = 2.0f;
        m_randSize = (float)rand()/RAND_MAX*0.02-0.001;
        m_col.m_w=0.7f;
        m_notBoom=true;
        m_notFreeze=true;
        m_notGalaxyDust=true;
    }
}
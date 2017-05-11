///https://github.com/NCCA/ParticleSystem/blob/master/SimpleParticles/src/Emitter.cpp

#include "emitter.h"
//#include "Vec4.h"

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


Emitter::Emitter(Vec4::Vec4 _pos, int _particlesNumber, Vec4 _col, Vec4 _vel, bool _notBoom, bool _notPause)
{
    for(int i=0; i<_particlesNumber; ++i)
    {
        m_particles.push_back(Particle(_pos, _col, _vel, _notBoom, _notPause));
    }
    m_notBoom = _notBoom;
    m_notPause = _notPause;
    m_col = _col;
    m_velocity = _vel;
    m_particlesNumber = _particlesNumber;
}

/*Emitter::~Emitter()
{}*/

void Emitter::resize(int w, int h)
{
    //resize the window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, float(w) / float(h), 0.1, 10.0);

    glViewport(0,0,w,h);

    glMatrixMode(GL_MODELVIEW);
}

/*void Emitter::setColor(float red, float green, float blue, float alpha)
{
    //alpha=m_alpha;
    m_col = Vec4(red,green,blue,m_col.m_w);
}*/

/*void Emitter::setExplode(Vec4 _vel)
{
    m_velocity = Vec4(m_velocity.m_x,m_velocity.m_y,m_velocity.m_z,m_velocity.m_w);
    //m_velocity = Vec4(-0.2f,-0.2f,m_velocity.m_z,m_velocity.m_w);
}*/

/*float Emitter::getAlpha()
{
    return m_col.m_w;
}*/


void Emitter::update()
{
    for(int i=0; i<m_particlesNumber; ++i)
    {
        m_particles[i].update();
    }
}

void Emitter::changeColor(Vec4 _col)

{
    for(int i=0; i<m_particlesNumber; ++i)
    {
        m_particles[i].setCol(_col);
    }
}

void Emitter::explode(Vec4 _vel, bool _notBoom)
{
    //_notBoom=false;
    for(int i=0; i<m_particlesNumber; ++i)
    {
        m_particles[i].partExplode(_vel, _notBoom);
    }
}

void Emitter::pause(Vec4 _vel, bool _notPause)
{
    //_notPause=false;
    for(int i=0; i<m_particlesNumber; ++i)
    {
        m_particles[i].pause(_vel, _notPause);
    }
}

void Emitter::draw()
{
    for(int i=0; i<m_particlesNumber; ++i)
    {
        m_particles[i].draw();
    }
}

///idea from https://github.com/NCCA/ParticleSystem/blob/master/SimpleParticles/src/Emitter.cpp
/// Modified

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

#include "Emitter.h"
//#include "Vec4.h"


Emitter::Emitter(Vec4 _pos, int _particlesNumber, Vec4 _col, Vec4 _vel, bool _notBoom, bool _notFreeze, bool _notGalaxyDust)
{
    for(int i=0; i<_particlesNumber; ++i)
    {
        m_particles.push_back(Particle(_pos, _col, _vel, _notBoom, _notFreeze, _notGalaxyDust));
    }
    m_notBoom = _notBoom;
    m_notFreeze = _notFreeze;
    m_notGalaxyDust = _notGalaxyDust;
    m_col = _col;
    m_velocity = _vel;
    m_particlesNumber = _particlesNumber;
}

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

void Emitter::explode(bool _notBoom)
{
    for(int i=0; i<m_particlesNumber; ++i)
    {
        m_particles[i].partExplode(_notBoom);
    }
}

void Emitter::freeze(bool _notFreeze)
{
    for(int i=0; i<m_particlesNumber; ++i)
    {
        m_particles[i].freeze(_notFreeze);
    }
}
void Emitter::galaxyDust(bool _notGalaxyDust)
{
    for(int i=0; i<m_particlesNumber; ++i)
    {
        m_particles[i].galaxyDust(_notGalaxyDust);
    }
}

void Emitter::draw()
{
    for(int i=0; i<m_particlesNumber; ++i)
    {
        m_particles[i].draw();
    }
}

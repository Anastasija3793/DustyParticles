#ifndef PARTICLE_H
#define PARTICLE_H
/// @file Particle.h
/// @brief Particle class which includes attributes of the particle
/// @author Anastasija Belaka
/// @version 10.0
/// @date 15/05/2017 Updated to NCCA Coding standard
/// Revision History : See https://github.com/Anastasija3793/DustyParticles
/// Initial Version 11/04/2017

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
#include <GL/gl.h>
#include <math.h>
#include <algorithm>
#include <cstdlib>

//----------------------------------------------------------------------------------------------------------------------
/// @class Particle "Particle.h"
/// @brief Particle class (includes its attributes/behaviour)
/// @author Anastasija Belaka
/// @version 10.0
/// @date 15/05/2017 Updated to NCCA Coding standard
/// Revision History : See https://github.com/Anastasija3793/DustyParticles
//----------------------------------------------------------------------------------------------------------------------

class Particle
{
public:

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Enumerators for switching/controlling states of particles
    /// @param[in] normal the normal/default behaviour of particles
    /// @param[in] freeze to freeze particles/emitter in one place (but the 'fading' process continious)
    /// @param[in] explosion to create an explosion
    /// @param[in] galaxy switches to the 'galaxy'/sphere state
    //----------------------------------------------------------------------------------------------------------------------
    typedef enum { normal, freeze, explosion, galaxy } states;
    int state = normal;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Particle with its characteristics
    /// @param[in] _pos the position of the particle
    /// @param[in] _col the colour of the particle
    //----------------------------------------------------------------------------------------------------------------------
    Particle(Vec4 _pos, Vec4 _col);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Draw Method draws particles
    //----------------------------------------------------------------------------------------------------------------------
    void draw();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Update Method updates particles
    //----------------------------------------------------------------------------------------------------------------------
    void update();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Set Colour Method sets the colour of particles
    /// @param[in] _col the colour of the particle
    //----------------------------------------------------------------------------------------------------------------------
    inline void setCol(Vec4 _col) { m_col = Vec4(_col.m_x,_col.m_y,_col.m_z,m_col.m_w); }

private:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the current position of particle
    //----------------------------------------------------------------------------------------------------------------------
    Vec4 m_pos;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the start position of particle
    //----------------------------------------------------------------------------------------------------------------------
    Vec4 m_startPos;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the velocity of particle
    //----------------------------------------------------------------------------------------------------------------------
    Vec4 m_velocity;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the colour of particle
    //----------------------------------------------------------------------------------------------------------------------
    Vec4 m_col;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the size of particles
    //----------------------------------------------------------------------------------------------------------------------
    float m_size;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the random size of particles
    //----------------------------------------------------------------------------------------------------------------------
    float m_randSize;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the life time of particles (how long the particle is going to live)
    //----------------------------------------------------------------------------------------------------------------------
    int m_lifetime;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the current life time of particles
    //----------------------------------------------------------------------------------------------------------------------
    int m_nowLife;
}; //end class

#endif // PARTICLE_H
//----------------------------------------------------------------------------------------------------------------------

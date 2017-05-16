#ifndef EMITTER_H
#define EMITTER_H
/// @file Emitter.h
/// @brief Emitter or 'cloud' which contains particles
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

#include <vector>
#include "Vec4.h"
#include "Particle.h"

//----------------------------------------------------------------------------------------------------------------------
/// @class Emitter "Emitter.h"
/// @brief Emitter class which contains particles (and their behaviour/attributes by passing)
/// @author Anastasija Belaka
/// @version 10.0
/// @date 15/05/2017 Updated to NCCA Coding standard
/// Revision History : See https://github.com/Anastasija3793/DustyParticles
//----------------------------------------------------------------------------------------------------------------------

class Emitter
{
public:

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Emitter or 'cloud' which contains moving particles
    /// @param[in] _pos the position of the emitter
    /// @param[in] _particlesNumber the number of particles
    /// @param[in] _col the colour of particles/emitter (rgba)
    //----------------------------------------------------------------------------------------------------------------------
    Emitter(Vec4 _pos, int _particlesNumber, Vec4 _col);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Update Method updates emitter
    //----------------------------------------------------------------------------------------------------------------------
    void update();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Draw Method draws emitter
    //----------------------------------------------------------------------------------------------------------------------
    void draw();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Change Colour Method changes the colour (need for alpha channel (changing transparency))
    //----------------------------------------------------------------------------------------------------------------------
    void changeColor(Vec4 _col);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Change State Method changes/switches the state ('normal' / 'freeze' / 'explosion' / 'galaxy')
    //----------------------------------------------------------------------------------------------------------------------
    void changeState(int _state);

private:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the position of emitter
    //----------------------------------------------------------------------------------------------------------------------
    Vec4 m_pos;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the colour of emitter/particles
    //----------------------------------------------------------------------------------------------------------------------
    Vec4 m_col;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the number of particles
    //----------------------------------------------------------------------------------------------------------------------
    int m_particlesNumber;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the container where particles are stored
    //----------------------------------------------------------------------------------------------------------------------
    std::vector <Particle> m_particles;
};  //end class

#endif // EMITTER_H

//----------------------------------------------------------------------------------------------------------------------

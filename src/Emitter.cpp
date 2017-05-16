/// @file Emitter.cpp
/// @brief Emitter or 'cloud' for particles
/// @author Anastasija Belaka
/// @version 10.0
/// @date 15/05/2017 Updated to NCCA Coding standard
/// The idea from /modified from : https://github.com/NCCA/ParticleSystem/blob/master/SimpleParticles/src/Emitter.cpp
/// Revision History : See https://github.com/Anastasija3793/DustyParticles
/// Initial Version 11/04/2017

#include "Emitter.h"

Emitter::Emitter(Vec4 _pos, int _particlesNumber, Vec4 _col)
{
    for(int i=0; i<_particlesNumber; ++i)
    {
        m_particles.push_back(Particle(_pos, _col));
    }
    m_col = _col;
    m_particlesNumber = _particlesNumber;
}
//----------------------------------------------------------------------------------------------------------------------
void Emitter::update()
{
    for(int i=0; i<m_particlesNumber; ++i)
    {
        m_particles[i].update();
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Emitter::changeColor(Vec4 _col)

{
    for(int i=0; i<m_particlesNumber; ++i)
    {
        m_particles[i].setCol(_col);
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Emitter::draw()
{
    for(int i=0; i<m_particlesNumber; ++i)
    {
        m_particles[i].draw();
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Emitter::changeState(int _state)
{
    for(int i=0; i<m_particlesNumber; ++i)
    {
        if (m_particles[i].state == _state)
        {
            m_particles[i].state = 0;
        }
        else
        {
            m_particles[i].state=_state;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------

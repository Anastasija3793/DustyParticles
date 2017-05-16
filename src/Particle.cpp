/// @file Particle.cpp
/// @brief Particle class which includes attributes and behaviour of particle
/// @author Anastasija Belaka
/// @version 10.0
/// @date 15/05/2017 Updated to NCCA Coding standard
/// Revision History : See https://github.com/Anastasija3793/DustyParticles
/// Initial Version 11/04/2017

#include "Particle.h"

Particle::Particle(Vec4 _pos, Vec4 _col)
{
    m_pos = _pos;
    m_startPos = _pos;
    m_col = _col;
    m_size = 2.0f;
    m_randSize = (float)rand()/RAND_MAX*0.02-0.001;
    m_lifetime=200;
    m_nowLife=0;
}
//----------------------------------------------------------------------------------------------------------------------
void Particle::draw()
{
    //to smooth points
    glEnable(GL_POINT_SMOOTH);
    //for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //set the colour
    glColor4f(m_col.m_x,m_col.m_y,m_col.m_z,m_col.m_w);
    //drawing a point
    glPointSize(m_size);
    glBegin(GL_POINTS);
    glVertex4f(m_pos.m_x,m_pos.m_y,m_pos.m_z,m_pos.m_w);
    glEnd();
}
//----------------------------------------------------------------------------------------------------------------------
void Particle::update()
{
    //switch states
    switch (state) {
    case explosion:
        m_velocity.set((0.09 * M_PI * (float)rand())/RAND_MAX, (0.09 * M_PI * (float)rand())/RAND_MAX, (0.09 * M_PI * (float)rand())/RAND_MAX, 1.0f);
        break;
    case freeze:
        m_velocity.set(0.0f,0.0f,0.0f,1.0f);
        m_randSize = 0.0f;
        break;
    case galaxy:
        m_pos.set((float)rand()/RAND_MAX*1.5-0.8, (float)rand()/RAND_MAX*1.5-0.8, (float)rand()/RAND_MAX*1.5-0.8, 1.0f);
        m_pos.normalize();
        m_col.set(0.5+0.5*(float)rand()/RAND_MAX, 0.5+0.5*(float)rand()/RAND_MAX, 0.5+0.5*(float)rand()/RAND_MAX, 1.0f);
        m_randSize = 0.0f;
        m_size = (float)rand()/RAND_MAX*5.0;
        break;
    default:
        break;
    }

    //normal state
    ++m_nowLife;
    m_size+=m_randSize;
    m_col.m_w-=0.0035f;
    m_pos+=m_velocity;
    m_velocity.set((float)rand()/RAND_MAX*0.02-0.001,(float)rand()/RAND_MAX*0.02+0.001,(float)rand()/RAND_MAX*0.02-0.007,1.0f);

    //the 'life process' of particle
    //don't delete particles because it's more efficient
    if(m_nowLife > m_lifetime)
    {
        m_pos=m_startPos;
        m_velocity.set((float)rand()/RAND_MAX*0.02-0.001,(float)rand()/RAND_MAX*0.02+0.001,(float)rand()/RAND_MAX*0.02-0.007,1.0f);
        m_nowLife=0;
        m_size = 2.0f;
        m_randSize = (float)rand()/RAND_MAX*0.02-0.001;
        m_col.m_w=0.7f;
        state = normal;
    }
}
//----------------------------------------------------------------------------------------------------------------------

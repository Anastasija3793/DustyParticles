#include "particle.h"
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



Particle::Particle(Vec4::Vec4 _pos, Vec4 _col, Vec4 _vel, bool _notBoom, bool _notPause) //, Emitter *_emitter)
{
    //float random = ((float) rand() / (float) RAND_MAX);
    //float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    m_pos = _pos;
    m_startPos = _pos;
    m_col = _col;
    m_velocity = _vel;
    m_notBoom = _notBoom;
    m_notPause = _notPause;
    //_pos.set(0.0f,0.0f,0.0f,1.0f);
    //\!!!m_velocity.set(0.001f,0.001f,0.0f,1.0f);
    //m_velocity.set(0.001f,0.001f,0.0f,1.0f);
    //m_velocity.set(0.05f,0.05f,0.0f,1.0f);

    //m_lifetime=rand->randomPositiveNumber(200);
    m_lifetime=200;
    m_nowLife=0;

    //m_origin(m_startPos) or m_prevPos !!!
    //m_currentLife(m_nowLife)

    //m_emitter = _emitter;

}

//void Particle::setColor(float red, float green, float blue, float alpha)
//{
//    glColor4f(red,green,blue,m_alpha);
//}

//void Particle::getColor(float red, float green,float blue, float alpha)
//{
//    //
//}

void Particle::draw()
{
    //to smooth points
    //glEnable(GL_POINT_SMOOTH);   //doesn't work

    //for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //draw function
    //glColor3f(0.0f,1.0f,0.0f);
    //glColor4f(0.0f,1.0f,0.5f,m_alpha);

    glColor4f(m_col.m_x,m_col.m_y,m_col.m_z,m_col.m_w);

    glPointSize(2.0f);
    glBegin(GL_POINTS);

    //glVertex3f(0.0f,0.0f,0.0f);
    //glNormal3f();
    glVertex4f(m_pos.m_x,m_pos.m_y,m_pos.m_z,m_pos.m_w);
    //glVertex3f(m_pos.m_x,m_pos.m_y,m_pos.m_z);
    //glVertex4f(m_velocity.m_x,m_velocity.m_y,m_velocity.m_z,m_velocity.m_w);
    glEnd();
}

void Particle::update()
{
    ++m_nowLife;
    //m_lifetime=200;
    //m_alpha-=0.005f;
    m_col.m_w-=0.0035f;
    m_pos+=m_velocity;
    //m_velocity.set(0.0f,0.0f,0.0f,1.0f);
    m_velocity.set((float)rand()/RAND_MAX*0.02-0.001,(float)rand()/RAND_MAX*0.02+0.001,0.0f,1.0f); //without it particles stop (only emitter is moving)

    //m_velocity.set( (0.001*(((2.0+(float)rand())/RAND_MAX)-1)),(0.001*(((2.0+(float)rand())/RAND_MAX)-1)),0.0f,1.0f );




    //m_notBoom=true;
    //m_pos.m_x+=m_velocity.m_x;
    //update drawing/particles/scene (some kind of render?)

    //i somehow effect speed
    /*for (int i=0; i<10; ++i)
    {
        m_pos+=m_velocity;
        //printf("Position x: %4.2f \n", m_pos.m_x);
    }*/

    //this one can stop
    /*if (m_nowLife<m_lifetime)
    {

    m_pos+=m_velocity;
    ++m_nowLife;}
    else
    {
        m_pos=m_startPos;
        m_nowLife=0;
    }*/

//    m_velocity.set((float)rand()/RAND_MAX*0.02-0.001,(float)rand()/RAND_MAX*0.02+0.001,0.0f,1.0f);



    if (!m_notBoom)  //do I need this?
    {
        //m_pos+=m_velocity;
        //m_velocity.set((float)rand()/RAND_MAX*0.02-0.001,(float)rand()/RAND_MAX*0.02+0.001,0.0f,1.0f);
        m_velocity.set((0.09 * M_PI * (float)rand())/RAND_MAX, (0.09 * M_PI * (float)rand())/RAND_MAX,0.0f,1.0f);
        //m_lifetime=100;
    }

    if(!m_notPause)
    {
        m_velocity.set(0.0f,0.0f,0.0f,1.0f);
        //m_nowLife = 0.0f;
        //m_col.m_w = 1.0f;

    }

    //m_alpha-=0.0005f;


//    for (float i=0; i<1; i+=0.5)
//        {
//            m_pos+=m_velocity;
//            //printf("Position x: %4.2f \n", m_pos.m_x);
//        }

    if(m_nowLife > m_lifetime)
    {
        m_pos=m_startPos;
        m_velocity.set((float)rand()/RAND_MAX*0.02-0.001,(float)rand()/RAND_MAX*0.02+0.001,0.0f,1.0f);
        m_nowLife=0;
        //m_alpha=1.0f
        m_col.m_w=0.7f;
        m_notBoom=true;
        m_notPause=true;

        //m_alpha=0.1f;  //if numOfPart=10000;
    }


  //  printf("Position x: %4.2f \n", m_pos.m_x);

    //printf("Position y: %4.2f \n", m_pos.m_y);
}

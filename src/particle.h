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

//class Emitter;

class Particle
{
public:

    //Particle(); //properties?

    //Particle(const Particle &_p) = default;  //used from internet
    Particle(Vec4::Vec4 _pos, Vec4 _col, Vec4 _vel, bool _notBoom, bool _notPause);  //, Emitter *_emitter);
    //Particle(Vec4 _pos = Vec4());

    //    m_pos(_pos),
    //    m_velocity(Vec4(0.1f,0.0f,0.0f,1.0f))
    //{}


    //maybe to initialize a particle or env
    //virtual void init();

    // draw particle?
    void draw();
    //virtual void draw();

    // update moving
    void update();

    inline void setCol(Vec4 _col) {m_col = Vec4(_col.m_x,_col.m_y,_col.m_z,m_col.m_w);}


    inline void partExplode(Vec4 _vel, bool _notBoom){//m_velocity = Vec4(_vel.m_x, _vel.m_y, _vel.m_z, _vel.m_w);
                                       m_notBoom = false;}

    inline void pause(Vec4 _vel, bool _notPause){m_velocity = Vec4(_vel.m_x, _vel.m_y, _vel.m_z, _vel.m_w);
                                       m_notPause = false;}

//    //set colour
//    void setColor(float red, float green, float blue, float alpha);

//    //get colour
//    void getColor(float red, float green, float blue, float alpha);



private:
    Vec4 m_col;

    Vec4 m_velocity; // PUBLIC?

    bool m_notBoom; // PUBLIC?

    bool m_notPause; // PUBLIC?
    Vec4 m_pos; //position

    Vec4 m_startPos;
    //int m_size;
    //int m_colour;
    //int m_speed;
    int m_lifetime;
    int m_nowLife;
    //int m_isDead;
    //float m_alpha;



    //const Emitter *m_emitter;

};

#endif // PARTICLE_H

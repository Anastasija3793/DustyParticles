#ifndef EMITTER_H
#define EMITTER_H

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

#include "particle.h"


class Emitter
{
public:
    Emitter(Vec4::Vec4 _pos, int _particlesNumber, Vec4 _col, Vec4 _vel, bool _notBoom, bool _notPause);
    //~Emitter();

    //resize the window
    void resize(int w, int h);

    void update();

    void changeColor(Vec4 _col);

    void explode(Vec4 _vel, bool _notBoom);

    void draw();

    //set colour
    //void setColor(float red, float green, float blue, float alpha);

    //void setExplode(Vec4 _vel);

    void pause(Vec4 _vel, bool _notPause);

    //float getAlpha();

    //get colour
    //void getColor(float red, float green, float blue, float alpha);



private:
    Vec4 m_pos;
    Vec4 m_col;

    Vec4 m_velocity;

    bool m_notBoom;

    bool m_notPause;

    int m_particlesNumber;
    std::vector <Particle> m_particles; //like array
};


#endif // EMITTER_H

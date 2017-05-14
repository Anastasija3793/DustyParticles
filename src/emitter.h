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
    Emitter(Vec4::Vec4 _pos, int _particlesNumber, Vec4 _col, Vec4 _vel, bool _notBoom, bool _notFreeze);

    //update function
    void update();

    //function for changing alpha (transparency)
    void changeColor(Vec4 _col);

    //explosion function
    void explode(bool _notBoom);

    //draw function
    void draw();

    //function to stop only the movement
    void freeze(bool _notFreeze);

private:
    Vec4 m_pos;
    Vec4 m_col;
    Vec4 m_velocity;
    bool m_notBoom;
    bool m_notFreeze;
    int m_particlesNumber;
    std::vector <Particle> m_particles; //like array
};

#endif // EMITTER_H

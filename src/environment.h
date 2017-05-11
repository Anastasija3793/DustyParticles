#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <SDL.h>
    #include <SDL_image.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include "particle.h"
//need to delete


class Environment
{
public:
    Environment();

    ~Environment();

    virtual void init();

    virtual void draw();

    virtual void update();


    void resizeWin();
    void resizeEnv();

private:
    bool m_Init;
    //smth for time
};


#endif // ENVIRONMENT_H

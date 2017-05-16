/// @file Main.cpp
/// @brief Title of Brief: Programming project 2
///        This is the program which represents a particle system named 'DustyParticles'.
///        The particle system itself represents a 'cloud' of dust particles.
///        The 'cloud' floats diagonally when it is in its normal/default behaviour (state).
///        However, it changes when states are switched (such as 'explosion', 'freeze', 'galaxy')
///        by pressing certain keys (see README.md file).
///        It is also possible to pause/unpause timer and change particles colours (see README.md file).
///        After a certain time particles return to their normal/default state.
///        The main file (Main.cpp) contains the main method - creates window and runs the simulation.
/// @author (start/modified) Richard Southern
/// @author (finish) Anastasija Belaka
/// @version 10.0
/// @date 15/05/2017 Updated to NCCA Coding standard
/// Revision History : See https://github.com/Anastasija3793/DustyParticles
/// Initial Version 11/04/2017

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>

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

// Include header files for our environment

//Particle
#include "Particle.h"

#include "Vec4.h"

//Emitter (contains particles)
#include "Emitter.h"

//Camera
#include "Camera.h"

// The name of the window
#define WINDOW_TITLE "DustyParticles"

// These defines are for the initial window size (it can be changed in the resize function)
int WIDTH = 900;
int HEIGHT = 600;

//Emitter
Emitter *myEmitter = NULL;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

int frame=0;

bool pause = false;


/**
 * @brief initSDL fires up the SDL window and readies it for OpenGL
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int initSDL()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }
    else
    {
        //Use OpenGL 3.1 core
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        //Create window
        gWindow = SDL_CreateWindow( WINDOW_TITLE,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    WIDTH,
                                    HEIGHT,
                                    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * @brief timerCallback an SDL2 callback function which will trigger whenever the timer has hit the elapsed time.
 * @param interval The elapsed time (not used - World uses it's own internal clock)
 * @return the elapsed time.
 */
Uint32 timerCallback(Uint32 interval, void *)
{
    if(!pause)
    {
        myEmitter->update();
    }
    ++frame;
    return interval;
}

/**
 * @brief main The main opengl loop is managed here
 * @param argc Not used
 * @param args Not used
 * @return EXIT_SUCCESS if it went well!
 */

/// This function was originally written by Richard Southern in his Cube workshop
int main( int argc, char* args[] ) {
    //Start up SDL and create window
    if( initSDL() == EXIT_FAILURE ) return EXIT_FAILURE;

    //Create context
    gContext = SDL_GL_CreateContext( gWindow );
    if( gContext == NULL ) return EXIT_FAILURE;

    //Use Vsync
    if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
        fprintf(stderr, "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
    }

    //Setting particles start/default position
    Vec4 particlePosition;
    particlePosition.set(-1.0f,-1.0f,-1.0f,1.0f);
    //Setting particles start/default colour
    Vec4 particleColor;
    particleColor.set(0.0f,1.0f,0.5f,0.7f);
    myEmitter =  new Emitter(particlePosition,1000,particleColor);

    //Camera and its default parameters
    Camera camera;

    float x = -0.15;
    float y = -0.15;
    float z = 2;

    float rX = -0.1;
    float rY = -0.1;
    float rZ = 0;
\
    // Use a timer to update our World. This is the best way to handle updates,
    // as the timer runs in a separate thread and is therefore not affected by the
    // rendering performance.

    SDL_TimerID timerID = SDL_AddTimer(20, //elapsed time in milliseconds*
                                     timerCallback, //callback function*
                                     (void*) NULL //parameters (none)*);
                                     );

    //glutTimerFunc(30, timerCallback, (void *) NULL);


    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    //Enable text input
    SDL_StartTextInput();

    //While application is running
    while( !quit )
    {

        while( SDL_PollEvent( &e ) != 0 )
                {
                    // The window has been resized
                    if ((e.type == SDL_WINDOWEVENT) &&
                            (e.window.event == SDL_WINDOWEVENT_RESIZED))
                    {
                        SDL_GetWindowSize(gWindow, &WIDTH, &HEIGHT);

                        glViewport(0,0,WIDTH,HEIGHT);
                        camera.perspective(45,float((float)WIDTH/(float)HEIGHT),0.01,500);
                    }
                    //User requests quit
                    else if( e.type == SDL_QUIT )
                    {
                      quit = true;
                    }
                    else if (e.type == SDL_KEYDOWN)
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        //changing colours
                        //change to red colour
                        case SDLK_r: { myEmitter->changeColor(Vec4(1.0f,0.0f,0.0f,0.7f));   break; }
                        //change to green colour
                        case SDLK_g: { myEmitter->changeColor(Vec4(0.0f,1.0f,0.0f,0.7f));   break; }
                        //change to blue colour
                        case SDLK_b: { myEmitter->changeColor(Vec4(0.0f,0.0f,1.0f,0.7f));   break; }
                        //change to white colour
                        case SDLK_o: { myEmitter->changeColor(Vec4(1.0f,1.0f,1.0f,0.7f));   break; }
                        //change to yellow colour
                        case SDLK_y: { myEmitter->changeColor(Vec4(1.0f,1.0f,0.5f,0.7f));   break; }
                        //change to random colour
                        case SDLK_RETURN: { myEmitter->changeColor(Vec4((float)rand()/RAND_MAX,(float)rand()/RAND_MAX,(float)rand()/RAND_MAX,0.7f));     break; }
                        //change to default colour
                        case SDLK_z: { myEmitter->changeColor(Vec4(0.0f,1.0f,0.5f,0.7f));   break; }

                        //behaviour of particles (and emitter)
                        //pause particles and then resume it
                        case SDLK_p: { pause = !pause;  break; }
                        //switching to the following cases
                        //explode
                        case SDLK_SPACE: { myEmitter->changeState(2);   break; }
                        //stop only the moving/freeze
                        case SDLK_f: { myEmitter->changeState(1);       break; }
                        //create 'Dust Galaxy'/sphere
                        case SDLK_TAB: { myEmitter->changeState(3);     break; }

                        //changing camera's parameters
                        //moving camera up
                        case SDLK_UP: { y-=0.005;       break; }
                        //moving camera down
                        case SDLK_DOWN: { y+=0.005;     break; }
                        //moving camera right
                        case SDLK_RIGHT: { x-=0.005;    break; }
                        //moving camera left
                        case SDLK_LEFT: { x+=0.005;     break; }
                        //setting camera to the default/start position and 'target'
                        case SDLK_0: {x = -0.15; y = -0.15; z = 2; rX = -0.1; rY = -0.1; rZ = 0; break; }
                        //'zoom in'/move closer
                        case SDLK_1: { z-=0.01;     break; }
                        //'zoom out'/move farther
                        case SDLK_2: { z+=0.01;     break; }
                        //changing where camera look at (target)
                        case SDLK_w: { rY+=0.005;   break; }
                        case SDLK_s: { rY-=0.005;   break; }
                        case SDLK_d: { rX+=0.005;   break; }
                        case SDLK_a: { rX-=0.005;   break; }
                        case SDLK_e: { rZ-=0.01;    break; }
                        case SDLK_q: { rZ+=0.01;    break; }
                        }
                    }
                }

        glViewport(0,0,WIDTH,HEIGHT);
        camera.perspective(45,float(WIDTH/HEIGHT),0.01,500);
        camera.lookAt(Vec4(x,y,z),Vec4(rX,rY,rZ),Vec4(0,1,0));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        myEmitter->draw();

        SDL_GL_SwapWindow( gWindow );
    }

    //Disable text input
    SDL_StopTextInput();

    // Disable our timer
    SDL_RemoveTimer(timerID);

    //delete emitter
    delete myEmitter;

    //Destroy window
    SDL_DestroyWindow( gWindow );

    //Quit SDL subsystems
    SDL_Quit();

    return EXIT_SUCCESS;
}
/// end of function

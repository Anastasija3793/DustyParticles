///
///  @file    Main.cpp
///  @brief   contains the main method - creates window and runs the simulation
///  @author  Richard Southern & Thomas Collingwood

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


// Include the header file for our current World



// Change this if you want something different.
#define WINDOW_TITLE "ParticlePanic"

// These defines are for the initial window size (it can be changed in the resize function)
int WIDTH = 900;
int HEIGHT = 600;


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

bool leftMouseOnWorld = false;
bool leftMouseOnToolbar = false;
bool leftMouseOnWorldPrevious=false;
bool rightMouseButton = false;
bool pookd = false;
bool updateinprogress = false;
bool drawInTimer=false;

int frame=0;
int previousframe=0;
int framedrawn=0;



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
Uint32 timerCallback(Uint32 interval, void *) {
\
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

\
    // Use a timer to update our World. This is the best way to handle updates,
    // as the timer runs in a separate thread and is therefore not affected by the
    // rendering performance.

    SDL_TimerID timerID = SDL_AddTimer(30, /*elapsed time in milliseconds*/
                                     timerCallback, /*callback function*/
                                     (void*) NULL /*parameters (none)*/);

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
                        SDL_SetWindowSize(gWindow, e.window.data1, e.window.data2);

                        WIDTH=e.window.data1;
                        HEIGHT=e.window.data2;
                    }
                    //User requests quit
                    else if( e.type == SDL_QUIT )
                    {
                      quit = true;
        }
        }

            glBegin(GL_TRIANGLES);
            glColor3f(1.0f,1.0f,1.0f);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(1.0f,1.0f,0.0f);
            glVertex3f(2.0f,0.2f,1.0f);
            glEnd();

            glBegin(GL_POINTS);
 glVertex3f(0.0f,0.0f,0.0f);
            glEnd();



        SDL_GL_SwapWindow( gWindow );
    }

    //Disable text input
    SDL_StopTextInput();

    // Disable our timer
    SDL_RemoveTimer(timerID);




    //Destroy window
    SDL_DestroyWindow( gWindow );

    //Quit SDL subsystems
    SDL_Quit();

    return EXIT_SUCCESS;
}
/// end of function

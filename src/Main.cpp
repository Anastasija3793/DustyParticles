///
///  @file    Main.cpp
///  @brief   contains the main method - creates window and runs the simulation
///  @author (start/modified - main.cpp file)  Richard Southern & Thomas Collingwood
///  @author (finish) Anastasija Belaka

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
#include "particle.h"

#include "Vec4.h"

//emitter
#include "emitter.h"


// The name of the window
#define WINDOW_TITLE "DustyParticles"

// These defines are for the initial window size (it can be changed in the resize function)
int WIDTH = 900;
int HEIGHT = 600;

Emitter *myEmitter = NULL;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

/*bool leftMouseOnWorld = false;
bool leftMouseOnToolbar = false;
bool leftMouseOnWorldPrevious=false;
bool rightMouseButton = false;
bool pookd = false;
bool updateinprogress = false;
bool drawInTimer=false;*/

int frame=0;

bool freeze = false;
//int previousframe=0;
//int framedrawn=0;



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

    if(!freeze) myEmitter->update();

     return interval;

    //myEMitter stuff

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


    //particle = new Particle();
    //Particle particle();
    Vec4 particlePosition;
    particlePosition.set(-1.0f,-1.0f,0.0f,1.0f);
    Vec4 particleColor;
    //particleColor.set(0.0f,1.0f,0.5f,particle.m_col.m_w);
    particleColor.set(0.0f,1.0f,0.5f,0.7f);
    Vec4 explosion;
    //explosion.set(0.0f,0.0f,0.0f,1.0f);
    //Vec4 pause;
    //pause.set(0.0f,0.0f,0.0f,1.0f);
    bool notPause = true;
    myEmitter =  new Emitter(particlePosition,1000,particleColor,explosion,true,notPause);
    //Vec4 m_velocity;
    //int key=0;
    //int boom = 0;


    //resize window
    myEmitter->resize(WIDTH,HEIGHT);
    //particle.setColor(particleColor.m_x,particleColor.m_y,particleColor.m_z,particleColor.m_w);

    //particle.setColor(0.0f,1.0f,0.0f,m_alpha);
    //particle.setColor(0.0f,1.0f,0.0f,1.0f);



\
    // Use a timer to update our World. This is the best way to handle updates,
    // as the timer runs in a separate thread and is therefore not affected by the
    // rendering performance.
    //int t = 20;

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
                        SDL_SetWindowSize(gWindow, e.window.data1, e.window.data2);

                        //WIDTH=e.window.data1;
                        //HEIGHT=e.window.data2;

                        myEmitter->resize(e.window.data1,e.window.data2);
                    }
                    //User requests quit
                    else if( e.type == SDL_QUIT )
                    {
                      quit = true;
                    }
                    /*else if(e.type == SDL_TEXTINPUT)
                    {
                        int x = 0, y = 0;
                        SDL_GetMouseState(&x,&y);
                    }*/

                    else if (e.type == SDL_KEYDOWN)
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_r:
                            //change to red colour
                            //particle.setColor(1.0f,0.0f,0.0f,1.0f);
                            myEmitter->changeColor(Vec4(1.0f,0.0f,0.0f,0.7f));
                            break;
                        case SDLK_g:
                            //change to green colour
                            myEmitter->changeColor(Vec4(0.0f,1.0f,0.0f,0.7f));
                            break;
                        case SDLK_b:
                            //change to blue colour
                            myEmitter->changeColor(Vec4(0.0f,0.0f,1.0f,0.7f));
                            break;
                        case SDLK_w:
                            //change to white colour
                            myEmitter->changeColor(Vec4(1.0f,1.0f,1.0f,0.7f));
                            break;
                        case SDLK_y:
                            //change to yellow colour
                            myEmitter->changeColor(Vec4(1.0f,1.0f,0.5f,0.7f));
                            break;
                        case SDLK_d:
                            //change to default colour
                            myEmitter->changeColor(Vec4(0.0f,1.0f,0.5f,0.7f));
                            break;
                        case SDLK_SPACE:
                            //if (boom < 20000)
                            //{
                                //myEmitter->explode(Vec4((float)rand()/RAND_MAX*0.02-0.009,(float)rand()/RAND_MAX*0.02+0.009,0.0f,1.0f),false);
                            //myEmitter->explode(Vec4(0.02 * M_PI * (float)rand()/RAND_MAX, 0.02 * M_PI * (float)rand()/RAND_MAX,0.0f,1.0f),false);
                            myEmitter->explode(Vec4(),false);


                            //myEmitter->explode(Vec4( (0.001*(((2.0+(float)rand())/RAND_MAX)-1)),(0.001*(((2.0+(float)rand())/RAND_MAX)-1)),0.0f,1.0f ),false);
                                //myEmitter->explode(Vec4(-0.02,-0.02,0.0f,1.0f),false);
                                //++boom;
                            //}
                            //boom = 0;
                            break;
                        case SDLK_p:
                            if(freeze) freeze=false;
                            else freeze = true;

//                        if (notPause){
//                            myEmitter->pause(Vec4(),false);}
//                        if (!notPause){
//                            myEmitter->explode(Vec4((float)rand()/RAND_MAX*0.02-0.009,(float)rand()/RAND_MAX*0.02+0.001,0.0f,1.0f),true);}

                            //timerID=0;


                            /*SDL_TimerID timerID = SDL_AddTimer(2, //elapsed time in milliseconds*
                                                             timerCallback, //callback function*
                                                             (void*) NULL //parameters (none)*);
                                                             );*/

                            break;

//                        case SDLK_LEFT:
//                            //key=1;
//                            //glColor4f(1.0f,1.0f,0.5f,1.0f);
//                            particle.setColor(1.0f,1.0f,1.0f,1.0f);
//                            //particleColor.set(1.0f,1.0f,1.0f,1.0f);
//                            break;
                        }
                    }
                }


        //particle-> init();

            /*glBegin(GL_TRIANGLES);
            glColor3f(1.0f,1.0f,1.0f);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(1.0f,1.0f,0.0f);
            glVertex3f(2.0f,0.2f,1.0f);
            glEnd();*/


            /*glPointSize(10.0f);
            glBegin(GL_POINTS);
            glVertex3f(0.0f,0.0f,0.0f);
            glEnd();*/


//        if (key == 1)
//        {
//            m_velocity.set((float)rand()/RAND_MAX*-0.02-0.001,(float)rand()/RAND_MAX*0.02+0.001,0.0f,1.0f);

//        }

//        if (key == 1)
//        {
//            glColor4f(1.0f,1.0f,0.5f,1.0f);
//        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        myEmitter->draw();

        //scaling
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glScalef(0.7f,0.7f,0.7f);
        glMatrixMode(GL_MODELVIEW);

        SDL_GL_SwapWindow( gWindow );
    }

    //Disable text input
    SDL_StopTextInput();

    // Disable our timer
    SDL_RemoveTimer(timerID);


    delete myEmitter;

    //Destroy window
    SDL_DestroyWindow( gWindow );

    //Quit SDL subsystems
    SDL_Quit();

    return EXIT_SUCCESS;
}
/// end of function

#include "environment.h"

Environment::Environment():
//some parameters for our world

    //timer?
    m_Init(false)
{}

Environment::~Environment()
{}

void Environment::init()
{
    //lights
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHT0);
    glEnable (GL_BLEND);

    //background colour
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void Environment::draw()
{
    //there we can translate/rotate (?)
}

void Environment::update()
{
    //maybe timer?
}

void Environment::resizeWin()
{
    //resize window
}

void Environment::resizeEnv()
{
    //resize our environment
}

//glMatrixMode(GL_MODELVIEW);  //to make it bigger?
//glRotate or glTranslate;
//glViewPort(x,y,z)? - changing the camera

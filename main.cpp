
#include <GL/glut.h>
#include "nebula.h"
#include "birthStar.h"
#include<iostream>

int count = 0;
int birthTime = 100;

void timer(int)
{
    nebulaTimer();
    count++;
    if(count >= birthTime)
        birthStarTimer();

    // causes the main loop to call display func asap
    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}

void init(){

    // glPointSize(1.0f);
    // Views the object in the world co-ordinate frame
    glMatrixMode(GL_PROJECTION);
    // resets the transformed matrix to it's original state
    glLoadIdentity();
    const double w = glutGet( GLUT_WINDOW_WIDTH );
    const double h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 70.0, w / h, 5, 4000 );

    // Defines how objects are transformed
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // creates viewing matrix derived from eye point
    gluLookAt( 70, 70, 70, // eye
                0, 0, 0,   // center
                0, 0, 1 ); // up co-ordinates

    nebulaInit();


}

void display(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    nebulaRender();
    if(count == birthTime) birthStarInit();
    if(count >= birthTime)
        birthRender();
    glFlush();
    glutSwapBuffers();
}

static void ResizeWindow(int w, int h)
{

    glMatrixMode(GL_PROJECTION);
    // resets the transformed matrix to it's original state
    glLoadIdentity();
    gluPerspective( 70.0, w / h, 5, 4000 );

    // Defines how objects are transformed
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // // creates viewing matrix derived from eye point
    gluLookAt( 70, 70, 70, // eye
                10, 10, 0,   // center
                0, 0, 1 ); // up co-ordinates

}

int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE ); //double for double buffer window
    glutInitWindowSize( 1000,900 );
    glutInitWindowPosition(500,0);
    glutCreateWindow( "Star-life" );

    init();

    // gets called only on trigger eg. refresh
    glutDisplayFunc( display );

    // without this we get a still image
    glutTimerFunc( 0, timer, 0 );

    glutReshapeFunc(ResizeWindow);
    //function to enable various capabilites
    glEnable( GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); // (scale source color, destination color)

    glutMainLoop();
    return 0;
}
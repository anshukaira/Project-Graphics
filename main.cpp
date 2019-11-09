
#include <GL/glut.h>
#include <vector>
#include <stdio.h>
#include <SOIL.h>
#include "nebula.h"

void timer(int)
{
    nebulaTimer();

    // causes the main loop to call display func asap
    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}

void init(){

    glPointSize(1.0f);
    // Views the object in the world co-ordinate frame
    glMatrixMode(GL_PROJECTION);
    // resets the transformed matrix to it's original state
    glLoadIdentity();
    const double w = glutGet( GLUT_WINDOW_WIDTH );
    const double h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 60.0, w / h, 0.0, 1000000 );

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
    glFlush();
    glutSwapBuffers();
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

    //function to enable various capabilites
    glEnable( GL_BLEND);
    //blends the incoming rgba values with rgba values already in the frame buffer
    //glBlendFunci is for blending with specified buffer
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); // (scale source color, destination color)

    glutMainLoop();
    return 0;
}
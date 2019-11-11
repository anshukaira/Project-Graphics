#include "window1.h"
#include "window2.h"

int main(int argc, char **argv) {

    // Window 2 - 3d Extrapulated output
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100,150);
    glutInitWindowSize(600, 600);
    glutCreateWindow("3D Viewer");
    glutKeyboardFunc(mykeyboardW2);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutIdleFunc(rotation);
    gluOrtho2D(0, 400, 0, 500);
    glutDisplayFunc(displayW2);
    glutMouseFunc(mouseW2);
    glEnable(GL_DEPTH_TEST);
    
    // Window 1 drawing window
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(800,150);
    glutInitWindowSize(width, height);
    glutCreateWindow("Draw Here");
    glutKeyboardFunc(mykeyboardW1);
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 400, 0, 500);
    glutDisplayFunc(displayW1);
    glutMouseFunc(mouseW1);
    
    glutMainLoop();          
    
    return 0;
}


// Input Window to Draw
#include "globals.h"

void displayW1(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawLines();
    projectAllDots();
    glFlush();
}

void mykeyboardW1(unsigned char key, int x, int y) {
    int k = (int) key - '0';
    std::cout << "key code " << k << " " ;
    if (!Cline.empty() && k == 74)
        Cline.pop_back();
    
    glutPostRedisplay();
}

void mouseW1(int button, int state, int x, int y) {
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
        point CP(x, (500 - y), 1.0);
        CP = pointSimplifier(CP, Cline);
       
        if (checkIsFirst(CP, Cline)) {
            //loop formed..
            std::cout << "loop formed.. ";
            
            lines.push_back(Cline);
            
            Cline.clear();
        } else {
            Cline.push_back(CP);
        }
    }
    glutPostRedisplay();
}


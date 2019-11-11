// Input Window to Draw
#include "globals.h"

void displayW1(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawLines();
    projectAllDots();
    glFlush();
}

// to undo the created point on any keyUP
void mykeyboardW1(unsigned char key, int x, int y) {
    int k = (int) key - '0';
    std::cout << "key code " << k << " " ;
    if (!Cline.empty()) 
        Cline.pop_back();
    
    glutPostRedisplay();
}


void mouseW1(int button, int state, int x, int y) {
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
        point CP(x, (height - y), 1.0);
        
        CP = pointSimplifier(CP, Cline);
       
        // if a loop is formed
        if (checkIsFirst(CP, Cline)) {
            std::cout << "loop formed.. ";
            
            lines.push_back(Cline);
            
            // to know a loop is formed
            Cline.clear();
        } else {
            Cline.push_back(CP);
        }
    }
    glutPostRedisplay();
}


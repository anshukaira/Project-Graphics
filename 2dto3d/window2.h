// Output Window to display 3d Extrapolated image
#include "globals.h"

void displayW2(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    
    glLoadIdentity();
    if(lines.size()>0){
        
        
        for(Line l: lines){
            l=convertToIdentityForm(l);
            glRotatef(theta[1], 1.0, 0.0, 0.0);
            glRotatef(theta[2], 0.0, 1.0, 0.0);
            glRotatef(theta[3], 0.0, 0.0, 1.0);
            glPushMatrix();
            
            drawLineLoop(l);
            fillSides(l);
            glTranslatef(0.0, 0.0, size);
            drawLineLoop(l);
            
            glPopMatrix();
            glEnd();
        }
        
    }
    glFlush();
}

void mykeyboardW2(unsigned char key, int x, int y) {
    std::cout << key << " ";
    switch (key) {
        case 'w':
            color=3;
            break;
        case 'r':
            //red
            color=0;
            break;
        case 'g':
            color=1;
            break;
        case 'b':
            color=2;
            break;
        case 'i':
            size-=0.01;
            break;
        case 'd':
            size+=0.01;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void mouseW2(int button, int state, int x, int y) {
    if(axis==2){
        axis=0;
        
    }else        axis++;
    glutPostRedisplay();
}


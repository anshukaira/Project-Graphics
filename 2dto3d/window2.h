// Output Window to display 3d Extrapolated image
#include "globals.h"

void displayW2(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    
    if(lines.size()>0){
        
        
        for(Line l: lines){
            
            l=convertToIdentityForm(l);
            // to create rotating effect in rotation fuct
            glRotatef(theta[1], 1.0, 0.0, 0.0);
            glRotatef(theta[2], 0.0, 1.0, 0.0);
            glRotatef(theta[3], 0.0, 0.0, 1.0);
            glPushMatrix();
            
            drawLineLoop(l);
            createSides(l);
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
            color=0;
            break;
        case 'g':
            color=1;
            break;
        case 'b':
            color=2;
            break;
        // increase width
        case 'i':
            size-=0.01;
            break;
        // decrease width
        case 'd':
            size+=0.01;
            break;
        // toggle btw drawing modes 
        case 's':
        {
            if(drawingMode == drawMode[0]) 
                drawingMode = drawMode[1];
            else
                drawingMode = drawMode[0];
        }
            break;
        case 'x':
        {
            Cline.clear();
            lines.clear();
        }
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


void mouseW2(int button, int state, int x, int y) {
    if(axis==2){
        axis=0;
        
    }else   axis += 1;
    glutPostRedisplay();
}




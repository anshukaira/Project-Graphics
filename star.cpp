#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL.h>

GLuint texEarth;
GLUquadricObj *pSphere = NULL;

void OpenGLInit(void);
void draw_sun();
static void display(void );
static void ResizeWindow(int w, int h);

float size;

GLuint loadTex(const char* filename)
{
    GLuint tex_ID = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,(SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT));
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, tex_ID );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        return tex_ID;
}

void timer(int)
{
    size += 0.005;
	glutPostRedisplay(); // post for display func
    if(size >= 2) size = 2;
	glutTimerFunc(100, timer, 0); // limit frame drawing to 100fps
}


void OpenGLInit(void)
{
    // adds shading glsmooth, glFlat
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST);
    pSphere = gluNewQuadric();
    gluQuadricDrawStyle(pSphere, GLU_FILL);
    gluQuadricNormals(pSphere, GLU_SMOOTH);
    gluQuadricTexture(pSphere, GLU_TRUE);
    timer(0);
}


static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texEarth);
    GLfloat pos[] = { -1.0, -1.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glColor3f(1.0,1.0,1.0);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -10.0f);
    glRotatef( -90.0, 1.0, 0.0, 0.0 );
    gluSphere(pSphere, size, 25, 25);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();

}

void initTex()
{
    texEarth = loadTex("pink-star.jpg");  
}

void draw_sun()
{


    glPushMatrix();
    glRotatef( -90.0, 1.0, 0.0, 0.0 );
    glColor3f(1.0, 1.0, 0.0);
    glutSolidSphere(1.0, 15, 15);
    glPopMatrix();
}

static void ResizeWindow(int w, int h)
{
    float aspectRatio;
    h = (h == 0) ? 1 : h;
    w = (w == 0) ? 1 : w;
    glViewport( 0, 0, w, h );
    aspectRatio = (float)w/(float)h;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60.0, aspectRatio, 5.0, 40.0 );
    glMatrixMode( GL_MODELVIEW );
}


int main( int argc, char** argv )
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( 1200, 900);
    glutCreateWindow( "Solar System" );
    OpenGLInit();
    initTex();
    glutReshapeFunc(ResizeWindow);
    glutDisplayFunc(display);
    glutTimerFunc(0,timer,0);
    glutMainLoop();
    return(0);
}

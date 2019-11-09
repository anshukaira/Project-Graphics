#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

GLuint texEarth;
GLUquadricObj *pSphere = NULL;

void OpenGLInit(void);
void draw_sun();
static void display(void );
static void ResizeWindow(int w, int h);

GLuint loadTex(const char* filename)
{
    GLuint tex_ID = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,(SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT));
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, tex_ID );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        return tex_ID;
    }

void OpenGLInit(void)
{
    glShadeModel( GL_FLAT );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST);
    pSphere = gluNewQuadric();
    gluQuadricDrawStyle(pSphere, GLU_FILL);
    gluQuadricNormals(pSphere, GLU_SMOOTH);
    gluQuadricTexture(pSphere, GLU_TRUE);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texEarth);
    GLfloat pos[] = { 0.0, 0.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glColor3f(1.0,1.0,1.0);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -10.0f);
    glRotatef( -90.0, 1.0, 0.0, 0.0 );
    gluSphere(pSphere, 1.0, 25, 25);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();

}

void initTex()
{
    texEarth = loadTex("something.jpeg");  
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( 1200, 900);
    glutCreateWindow( "Solar System" );
    OpenGLInit();
    initTex();
    glutReshapeFunc(ResizeWindow);
    glutDisplayFunc(display);
    glutMainLoop();
    return(0);
}

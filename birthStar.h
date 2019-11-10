
#include <stdio.h>
#include <GL/glut.h>
#include <SOIL.h>

GLuint texEarth;
GLUquadricObj *pSphere = NULL;


static float size = 0;

GLuint loadTex(const char* filename)
{
    GLuint tex_ID = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,(SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT));
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, tex_ID );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        return tex_ID;
}

void birthStarTimer()
{
    size += 0.05;
    if(size >= 20) size = 20;
}


void birthStarInit(void)
{
    // adds shading glsmooth, glFlat
    glShadeModel( GL_SMOOTH );
    // glClearColor( 0.0, 0.0, 0.0, 0.0 );
    // glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST);
    pSphere = gluNewQuadric();
    gluQuadricDrawStyle(pSphere, GLU_FILL);
    gluQuadricNormals(pSphere, GLU_SMOOTH);
    gluQuadricTexture(pSphere, GLU_TRUE);

    texEarth = loadTex("pink-star.jpg");  
}


void birthRender(void)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texEarth);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -10.0f);
    glRotatef( 0.0, 0.0, 0.0, 50.0 );
    gluSphere(pSphere, size, 25, 25);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}


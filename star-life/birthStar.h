
#include <stdio.h>
#include <GL/glut.h>
#include <SOIL.h>

GLuint pinkTex;
GLuint blueTex;
GLUquadricObj *pSphere = NULL;


static float size = 0, rotAngle = 2;

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
    size += 0.5;
    rotAngle += 1;
    if(size >= 20) size = 20;
}


void birthStarInit(void)
{
    // adds shading glsmooth, glFlat
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST);
    pSphere = gluNewQuadric();
    gluQuadricDrawStyle(pSphere, GLU_FILL);
    gluQuadricNormals(pSphere, GLU_SMOOTH);
    gluQuadricTexture(pSphere, GLU_TRUE);

    pinkTex = loadTex("pics/pink-star.jpg");  
    // blueTex = loadTex("blue-star.jpeg");
}


void birthRender(void)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,pinkTex);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glPushMatrix();
    glTranslatef(-50.0f, -60.0f, 0.0f);
    glRotatef( rotAngle, 0.0, 1.0, 50.0 );
    gluSphere(pSphere, size, 25, 25);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void blueRender(void)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,blueTex);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, -10.0f);
    glRotatef( 0.0, 0.0, 0.0, 50.0 );
    gluSphere(pSphere, size, 25, 25);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}


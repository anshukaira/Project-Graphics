#pragma once
#include <GL/glut.h>
#include <string.h>
#include <iostream>
#include "math.h"
#include <vector>

typedef struct Point {
    GLfloat x, y, z;
    Point(GLfloat px, GLfloat py, GLfloat pz) { x = px;y = py;z = pz;   }
    bool operator== (const Point &c1) { return (x == c1.x && y == c1.y);    }
    
} point;
typedef std::vector<point> Line;



static std::vector<point> Cline;
static std::vector<Line> lines;
static GLfloat size = -0.3;
static GLfloat vision [3]={0.0,45.0,1.0};
static GLdouble theta[3] = {0.0, 0.0, 0.0};
static GLfloat colors [] [3]={  {1.0,0.0,0.0},
                                {0.0,1.0,0.0},
                                {0.0,0.0,1.0},
                                {1.0,1.0,1.0}}; // rgbw color array
static GLint color=3;
static float height=500,width=400,hMid=250,wMid=200;
static GLint axis = 2;
static GLenum drawMode[2] = {GL_LINE_LOOP, GL_TRIANGLES};
static GLenum drawingMode = drawMode[0];




// to chk if the point matches the first point drawn (pushed in the array)

bool checkIsFirst(Point p1, std::vector<point> line) {
    if (line.size() == 0) return 0;
    else {
        point t = line.front();
        if(t==p1){
            return true;
        } else
            return false;
    }
}


// plotting dots on screen using spheres

void drawDot(point p1){
    glPushMatrix();
    // doesn't display points with glvertex3f 
    glTranslatef(p1.x , p1.y, p1.z);
    glutSolidSphere(1.0, 100, 100);
    glPopMatrix();
}

// drawing points pushed in the array

void projectAllDots(){
    for(point p: Cline){
        drawDot(p);
    }
}

// plotting the line using 2 points

void makeLine(point p1, point p2) {
    GLfloat pf1[3]={p1.x, p1.y, p1.z};
    GLfloat pf2[3]={p2.x, p2.y, p2.z};
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(colors[color][0],colors[color][1],colors[color][2]);
    glLineWidth(3);
    glVertex3fv(pf1);
    glVertex3fv(pf2);
    glEnd();
    glPopMatrix();
}

// creating 3d view by lines in z direction 

void createSides( std::vector<point> line){
    for(point p:line){
        point p1(p.x,p.y,0.0);
        point p2(p.x,p.y,size);
        makeLine(p1, p2);
    }
}

// Draw the line in 3d view
// colors can be changed here

void drawLineLoop( std::vector<point> line){
    glPushMatrix();
    glBegin(drawingMode);
    glLineWidth(10);
    for (point p2 : line) {
        const GLfloat v[3]={p2.x, p2.y, p2.z};
        glColor3f(colors[color][0],colors[color][1],colors[color][2]);
        glVertex2fv(v);
    }
    glPopMatrix();
    glEnd();
}

// drawing lines from consective pairs from the array of points (Cline) in 2d

void drawLines() {
    
    point pre(0,0,0);
    int size = Cline.size();
    // if more than 1 point then a line can be drawn
    if (size > 1) {
        pre = Cline.front(); // first val in the vector
        for (point p : Cline) {
            makeLine(pre, p);
            pre.x = p.x;
            pre.y = p.y;
            pre.z = p.z;
        }
    }else{
        pre=Point(0,0,0);
    }
}

// calculating the points because of the dumb graphics co-ordinate system according to the initial window size

point pointSimplifier(point p1, std::vector<point> line) {
    point pres = p1;
    long double mag = 100;
    for (point p2 : line) {
        mag = sqrt(pow(p1.x - p2.x, 2.0) + pow(p1.y - p2.y, 2.0) + pow(p1.z - p2.z, 2.0));
        if (mag < 7) {
            pres = p2;
            break;
        }
    }
    return pres;
}

// converting the points to be plotted on window2

point converter(point val){
    point t(0.0,0.0,0.0);
    t.x=(val.x-wMid)/200;
    t.y=(val.y-hMid)/200;
    t.z=(val.z)/2;
    return t;
}

// creating a line from the converted points

Line convertToIdentityForm(Line l){
    Line t;
    for(point p:l){
        p=converter(p);
        t.push_back(p);
    }
    return t;
}

// rotating effect for the idle funct

void axisTimer(int){

    glutPostRedisplay();
    glutTimerFunc(5,axisTimer, 0);
}

void rotation(){
    theta[axis] +=1.0;
    if(theta[axis]>360) theta[axis]-=360;
    glutPostRedisplay();
    glutTimerFunc(0,axisTimer, 5);
}

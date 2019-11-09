
#include <GL/glut.h>
#include <cmath>

// The moon is a sphere of radius 1 centered at the origin, built from 25
// slices and 25 stacks, lit with GL_LIGHT0 as a directional light pointing
// along <1,1,1>.
class Moon {
  int displayListId;
public:
  void create() {
    displayListId = glGenLists(1);//glgenlist generates a contiguous set of empty display list
    glNewList(displayListId, GL_COMPILE);//creates or replaces a display list
    GLfloat direction[] = {-1.0, -1.0, -1.0, 0.0};//for directions
    glLightfv(GL_LIGHT0, GL_POSITION, direction);//changes the lightning maybe the source of lightining
    glColor3f(1,1,1);
    glutSolidSphere(1.0, 25, 25);//radius, slices(no of subdivisions around z axis, longitude), stacks(..,similar to lattitude)
    glEndList();//endsthe list. as it might remove the id that is created during the glnewlist
  }
  void draw() {
    glCallList(displayListId);//calling the list display id
  }
};

// The one and only moon.
static Moon moon;

// An orbiter is an object that flies on a circle of a certain radius on the
// xz plane.  You supply the radius at construction time.
class Orbiter {
  double radius;
  double u;
public:
  Orbiter(double radius): radius(radius), u(0.0) {}//constructor class(a): a(x), r(7){}
  void advance(double delta)
   {u += delta;}//u--variable of class
  void getPosition(double& x, double& y, double& z) {
    x = radius * cos(u);//
    y = 0;
    z = radius * sin(u);
  }
};

// The one and only orbiter.
static Orbiter orbiter(5.0);

// Clears the window (and the depth buffer) and draws the moon as viewed from
// the current position of the orbiter.
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();//
  glLoadIdentity();//identity matrix
  double x, y, z;
  orbiter.getPosition(x, y, z);
  gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//defining a viewing transformation, eye xyz--specifies the position of eye point, centre xyz--specifies the position of reference point, up xyz-- dirn of up
  moon.draw();
  glPopMatrix();
  glutSwapBuffers();
}

// Advances the orbiter and requests to draw the next frame.
void timer(int v) {
  orbiter.advance(0.01);
  glutPostRedisplay();
  glutTimerFunc(1000/60, timer, v);
}

// reshape() fixes up the projection matrix so that we always see a sphere
// instead of an ellipsoid.
void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 10.0);
}

// Enables depth testing, enables lighting for a bright pinkish diffuse
// light, and creates a moon.
void init() {
  glEnable(GL_DEPTH_TEST);
  GLfloat pink[] = {0.8, 0, 0.4, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, pink);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  moon.create();
}

// The usual application code.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(500, 500);
  glutCreateWindow("The Moon");
  glutDisplayFunc(display);
  glutTimerFunc(100, timer, 0);
  glutReshapeFunc(reshape);
  init();
  glutMainLoop();
}

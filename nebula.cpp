// 3-D hyperbola
#include <GL/glut.h>
#include <vector>

struct Vertex
{
    float x, y, z, w;
    float r, g, b, a;
};
std::vector< Vertex > verts;

void fillVerts()
{
    
    double h = 0.01;
    double a = 10.0;
    double b = 28.0;
    double c = 8.0 / 3.0;

    Vertex cur;
    cur.a = 0.03;
	cur.r = 1;
    cur.g = 1;
	cur.b = 1;

    double x0 = 0.1;
    double y0 = 0;
    double z0 = 0;
    for( unsigned int i = 0; i < 10000; i++ ) 
    {
        // changing rgb values for different loops
        // till 20000 inner circles are black

        // most outer
        if(i == 5000)
        {
            cur.r = 0.41;
            cur.g = 0.004;
            cur.b = 0.39;
        }


        // innermost and one outer
        if(i == 1000)
        {
            cur.r = 0;
            cur.g = 0;
            cur.b = 0.4;
        }

        // major color
        if(i == 9000)
        {
            cur.r = 1.0f;
            cur.g = 0.753f;
            cur.b = 0.796f;
        }

        // formula for the curve
        const double x1 = x0 + h * a * (y0 - x0);
        const double y1 = y0 + h * (x0 * (b - z0) - y0);
        const double z1 = z0 + h * (x0 * y0 - c * z0);
        x0 = -x1;
        y0 = -y1;
        z0 = z1;

        if( i > 100 )
        {
            cur.x = x0;
            cur.y = y0;
            cur.z = z0;
            verts.push_back( cur );
        }
    }
}

float angle = 0;
void timer( int extra )
{
    // spin
    angle += 0.5;


    // causes the main loop to call display func asap
    glutPostRedisplay();
    glutTimerFunc( 10, timer, 0 );
}

void display(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Views the object in the world co-ordinate frame
    glMatrixMode(GL_PROJECTION);
    // resets the transformed matrix to it's original state
    glLoadIdentity();
    const double w = glutGet( GLUT_WINDOW_WIDTH );
    const double h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 60.0, w / h, 0.0, 1000000 );

    // Defines how objects are transformed
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // creates viewing matrix derived from eye point
    gluLookAt( 70, 70, 70, // eye
                0, 0, 0,   // center
                0, 0, 1 ); // up co-ordinates

    glRotatef( angle, 0, 0, 1 ); // rotation of angle deg abt x,y,z

    // DRAWING CURVE

    // arrays are neabled for witing and using during rendering
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
    // Specifies location and data format of array of vertex coordinates
    glVertexPointer( 3, GL_FLOAT, sizeof( Vertex ), &verts[0].x ); // pointer specifies the first coordinate of the vertex in the array
    glColorPointer( 4, GL_FLOAT, sizeof( Vertex ), &verts[0].r );
    // gltrianglefan, glLineStrip look cool
    // Gl points gives dotted structure
    glDrawArrays( GL_TRIANGLE_FAN, 0, verts.size() );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );

    // promotes contents of the back buffer of the layer to the current window to become contents of front buffer. The contents of the back buffer become undefined
    glutSwapBuffers();
}

int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE ); //double for double buffer window
    glutInitWindowSize( 800,600 );
    glutCreateWindow( "3-d cool" );

    // gets called only on trigger eg. refresh
    glutDisplayFunc( display );

    // without this we get a still image
    glutTimerFunc( 0, timer, 0 );

    fillVerts();

    //function to enable various capabilites
    glEnable( GL_BLEND);
    //blends the incoming rgba values with rgba values already in the frame buffer
    //glBlendFunci is for blending with specified buffer
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); // (scale source color, destination color)

    glPointSize(1.0f);

    // calls display on trigger like resizing, uncovering
    glutMainLoop();
    return 0;
}

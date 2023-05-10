#include <windows.h>
#include <GL/glut.h>
#include <math.h>

#define M_PI 3.1415926
float angle1 = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.5,1.5,1.5,0,0,0,0,1,0);
    
    float c = M_PI / 180;
    float phir, phi20r, theta, thetar;
    float x,y,z;
    float angle = 10;
    glRotatef(angle1,0,1,0);
    
    for (float phi = -90 + angle; phi <= 90 - angle; phi += angle) {
        phir = c * phi;
        phi20r = c * (phi + angle);
        glBegin(GL_QUAD_STRIP);
        for (float theta = -180; theta <= 180; theta += angle) {
            thetar = c * theta;
            x = sin(thetar) * cos(phir);
            z = cos(thetar) * cos(phir);
            y = sin(phir);
            glVertex3d(x,y,z); 
            x = sin(thetar) * cos(phi20r);
            z = cos(thetar) * cos(phi20r);
            y = sin(phi20r);
            glVertex3d(x,y,z); 
        }
        glEnd();
    }
    
    float c80;
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(0,1,0);
    c80 = c * (90 - angle);
    y = sin(c80);
    
    for (float theta = 180; theta >= -180; theta -= angle) {
        thetar = c * theta;
        x = sin(thetar) * cos(c80);
        z = cos(thetar) * cos(c80);
        glVertex3d(x,y,z);
    }
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(0,-1,0);
    c80 = c * (90 - angle);
    y = -sin(c80);
    
    for (float theta = -180; theta <= 180; theta += angle) {
        thetar = c * theta;
        x = sin(thetar) * cos(c80);
        z = cos(thetar) * cos(c80);
        glVertex3d(x,y,z);
    }
    
    // for (float theta = 180; theta >= -180; theta -= angle) {
    //     thetar = c * theta;
    //     x = sin(thetar) * cos(c80);
    //     z = cos(thetar) * cos(c80);
    //     glVertex3d(x,y,z);
    // }
    glEnd();
    
    glFlush();
}

void myReshape(int w, int h) {
    float factor = 2;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) glOrtho(-factor,factor,-factor*h/w,factor*h/w,-10,10);
    else glOrtho(-factor*w/h,factor*w/h,-factor,factor,-10,10);
}

void mySpecialFunc(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) 
        angle1 += 5;
    else if (key == GLUT_KEY_RIGHT) 
        angle1 -= 5;
    glutPostRedisplay();
} 

void myIdle() {
    angle1 += 0.5;
    glutPostRedisplay();
}

void init() {
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,0.0);
    
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float factor = 2;
    glOrtho(-factor,factor,-factor,factor,-10,10);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Sphere1");
    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);
    glutSpecialFunc(mySpecialFunc); 
    glutIdleFunc(myIdle);
    init();
    glutMainLoop();
}
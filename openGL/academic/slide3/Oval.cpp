#include <windows.h>
#include <GL/glut.h>
#include <math.h>

#define M_PI 3.1415926

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.5,1.5,1.5,0,0,0,0,1,0);
    
    float c = M_PI / 180;
    float phir, phi20r, theta, thetar;
    float x,y,z;
    float angle = 20;
    
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

void init() {
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,0.0);
    
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.2,1.2,-1.2,1.2,-10,10);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Sphere1");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
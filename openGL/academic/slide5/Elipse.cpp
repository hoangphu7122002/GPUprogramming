#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

#define PI 3.1415962
int W = 500;
int H = 500;

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);    
    
    double W_e = 1.5;
    double H_e = 1.2;
    int N = 50;
    double C = 2*PI/N;
    
    // glColor3f(0,0,0);
    // glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    for (double i = 0; i <= 2*PI + C; i += C) {
        glVertex2f(W_e*cos(i),H_e*sin(i));
        // std::cout << (W*cos(i)) << (H*sin(i)) << std::endl;
    }
    glEnd();
    glFlush();
}

void init() {
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4,4,-4,4,-1,1);
}

int main(int argc, char* argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(W,H);
    glutInitWindowPosition(0,0);
    glutCreateWindow("elipse");
    glutDisplayFunc(myDisplay);
    
    init();
    
    glutMainLoop();   
}
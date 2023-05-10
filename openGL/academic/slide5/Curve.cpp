#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

#define PI 3.1415962
float angle = 0;
double minXVal, maxXVal;
double minYVal, maxYVal;

void findMinMaxVal() {
    minXVal = cos(0) - cos(80 * 0) * sin(0);
    maxXVal = minXVal;
    for (double t = 0; t < 2 * PI; t += 0.001) {
        if (cos(t) - cos(80 * t) * sin(t) > maxXVal) 
            maxXVal = cos(t) - cos(80 * t) * sin(t);
        if (cos(t) - cos(80 * t) * sin(t) < minXVal) 
            minXVal = cos(t) - cos(80 * t) * sin(t);
    }
    minYVal = 2*sin(0) - sin(80 * 0);
    maxYVal = minYVal;
    for (double t = 0; t < 2 * PI; t += 0.001) {
        if (2*sin(t) - sin(80 * t) > maxYVal) 
            maxYVal = 2*sin(t) - sin(80 * t);
        if (2*sin(t) - sin(80 * t) < minYVal) 
            minYVal = 2*sin(t) - sin(80 * t);
    }
}

void drawText(float xPos, float yPos, float zPos, string str) {
    glRasterPos3f(xPos, yPos, zPos);
    void* font = GLUT_BITMAP_9_BY_15;
    for (int i = 0; i < str.length(); ++i)
        glutBitmapCharacter(font,str[i]);
}

void drawAxis() {
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(2,0,0);
        
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,2,0);
        
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,2);
    glEnd();
    glColor3f(0,0,0);
    drawText(1.9,0,0,"X");
    drawText(0,1.7,0,"Y");
    drawText(0,0,1.9,"Z");
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
    // gluLookAt(0.7,0.5,0.3,0,0,0,0,1,0);
    
    // glRotatef(angle,0,1,0);
    
    // drawAxis();
    
    glBegin(GL_LINE_STRIP);
    for (double t = 0; t <= 3*PI; t += 0.001) 
        glVertex2f(cos(t) - cos(80 * t) * sin(t),2*sin(t) - sin(80 * t));
    glEnd();
    glFlush();
}

void mySpecialFunc(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) 
        angle += 5;
    else if (key == GLUT_KEY_RIGHT) 
        angle -= 5;
    glutPostRedisplay();
} 

void init() {
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,0.0);
    
    findMinMaxVal();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(minXVal,maxXVal,minYVal,maxYVal,-10,10);
}

int main(int argc,char* argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Curve");
    glutDisplayFunc(myDisplay);
    // glutSpecialFunc(mySpecialFunc);
    
    init();
    
    glutMainLoop();
}
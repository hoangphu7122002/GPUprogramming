#include <windows.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

int Width = 500;
int Height = 500;
int l = -2;
int r = 4;
int b = -4;
int t = 2;
int len = 20;

void drawSquare(int x, int y) {
    //y = Height - y;
    
    glColor3ub((char)rand() % 256,(char)rand() % 256,(char)rand() % 256);
    glBegin(GL_POLYGON);
        glVertex2f(x + len,y + len);
        glVertex2f(x - len,y + len);
        glVertex2f(x - len,y - len);
        glVertex2f(x + len,y - len);
    glEnd();
    
    // float x1 = ((r - l)/Width) * x + l;
    // float y1 = ((b - t)/Height) * y + t;
    // float len1 = (float(r - l) / Width) * len;
    // glBegin(GL_POLYGON);
    //     glVertex2f(x1 + len1,y1 + len1);
    //     glVertex2f(x1 - len1,y1 + len1);
    //     glVertex2f(x1 - len1,y1 - len1);
    //     glVertex2f(x1 + len1,y1 - len1);
    // glEnd();
    
    glFlush();
}

void myMouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP) 
        drawSquare(x,y);
}

void myDisplay() {
    // glClear(GL_COLOR_BUFFER_BIT);
    
    glFlush();
}

void myKeyboard(unsigned char key, int x, int y) {
    if (key == 'A' || key == 'a') cout << "a: " << endl;
    if (key == 66 || key == 98) cout << "b: " << endl;
    if (key == 127) cout << "Delete" << endl;
}

void init() {
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,Width,Height,0,-1,1);
    // glOrtho(0,Width,0,Height,-1,1);
    // glOrtho(l,r,b,t,-1,1);
}

int main(int argc, char* argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(Width,Height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Mouse Click");
    glutDisplayFunc(myDisplay);
    // glutMouseFunc(myMouse);
    // glutKeyboardFunc(myKeyboard);
    glutPassiveMotionFunc(drawSquare);
    
    init(); 
    
    glutMainLoop();
}
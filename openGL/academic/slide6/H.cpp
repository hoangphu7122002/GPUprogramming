#include <windows.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1415962

float v0[12][2] = {
    {0,0}, {0,2} , {0.6,2},
    {0.6,1.2}, {1.4,1.2} , {1.4,2},
    {2,2}, {2,0} , {1.4,0},
    {1.4,0.8}, {0.6,0.8} , {0.6,0}
};

float m[16] = {
    cos(PI/3), sin(PI/3), 0, 0,
    -sin(PI/3), cos(PI/3), 0, 0,
    0,0,1,0,
    1,2,0,1
};

float ShearTranslate[16] = {
    1,0,0,0,
    0.3,1,0,0,
    0,0,1,0,
    1,2,0,1
};

float Shear[16] = {
    1,0,0,0,
    0.3,1,0,0,
    0,0,1,0,
    0,0,0,1
};

void drawFigure0() {
    // glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 12; ++i) 
        glVertex2fv(v0[i]);
    glEnd();
}

void drawFigure1() {
    float v1[12][2];
    glColor3f(0,0,1);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 12; ++i) {
        v1[i][0] = v0[i][0] * cos(PI/3) - v0[i][1] * sin(PI/3) + 1;
        v1[i][1] = v0[i][0] * sin(PI/3) + v0[i][1] * cos(PI/3) + 2;
        glVertex2fv(v1[i]);
    }
    glEnd();
}


void drawAxis() {
    glColor3f(0.5,0.5,0.5);
    glLineWidth(2);
    glBegin(GL_LINES);
    for (int x = -5; x <= 5; x += 1) {
        glVertex2f(x,-5);
        glVertex2f(x,5);
    }
    for (int y = -5; y <= 5; y += 1) {
        glVertex2f(-5,y); 
        glVertex2f(5,y);
    }
    glEnd();
    
    glColor3f(0,0,0);
    glLineWidth(4);
    glBegin(GL_LINES);
        glVertex2f(0,5);
        glVertex2f(0,-5);
        
        glVertex2f(5,0);
        glVertex2f(-5,0);
    glEnd();
}

void init() {
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,0.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5,5,-5,5,-10,10);   
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawAxis();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // drawFigure1();
    glPushMatrix();
    glColor3f(0,0,1);
    glTranslated(1,2,0);
    glRotatef(60,0,0,1);
    drawFigure0();
    glPopMatrix();
    
    glPushMatrix();
    // glLoadMatrixf(m);
    glTranslated(1,2,0);
    glMultMatrixf(Shear);
    glColor3f(0,1,0);
    drawFigure0();
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1,0,11);
    glRotatef(60,0,0,1);
    glTranslated(1,2,0);
    glScalef(1.4,1.4,1);
    drawFigure0();
    glPopMatrix();
    
    glColor3f(1,0,0);
    drawFigure0();
    
    glFlush();
}

int main(int argc,char* argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("H");
    glutDisplayFunc(display);
    
    init();
    
    glutMainLoop();
}
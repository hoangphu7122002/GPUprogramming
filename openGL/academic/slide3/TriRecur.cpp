#include <windows.h>
#include <GL/glut.h>

int n;

GLfloat v[3][2] = {
    {-1.0,-0.58},
    {1.0,-0.58},
    {0.0,1.15}
};

void triangle(GLfloat* a, GLfloat* b, GLfloat* c) {
    glVertex2fv(a);
    glVertex2fv(b);
    glVertex2fv(c);
}

void recur_triangle(GLfloat* a, GLfloat* b, GLfloat* c, int m) {
    GLfloat v0[2];
    GLfloat v1[2];
    GLfloat v2[2];
    if (m > 0) {
        for (int j = 0; j < 2; ++j) v0[j] = (a[j] + b[j]) / 2;
        for (int j = 0; j < 2; ++j) v1[j] = (a[j] + c[j]) / 2;
        for (int j = 0; j < 2; ++j) v2[j] = (c[j] + b[j]) / 2;
        recur_triangle(a,v0,v1,m-1);
        recur_triangle(c,v1,v2,m-1);
        recur_triangle(b,v2,v0,m-1);
    }
    else triangle(a,b,c);
} 

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
        recur_triangle(v[0],v[1],v[2],n);
    glEnd();
    glFlush();
}

void myinit() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0,2.0,-2.0,2.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,0.0);
}

int main(int argc, char* argv[]) {
    n = 4;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("TriRecur");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}
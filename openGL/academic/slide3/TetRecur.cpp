#include <windows.h>
#include <GL/glut.h>

int n;

GLfloat v[4][3] = {
    {0.0,0.0,0.0},
    {1.0,0.0,0.0},
    {0.0,1.0,0.0},
    {0.0,0.0,1.0},
};

GLfloat colors[4][3] = {
    {1.0,1.0,0.0},
    {0.0,1.0,0.0},
    {0.0,0.0,1.0},
    {1.0,0.0,0.0}
};

void triangle(GLfloat* a, GLfloat* b, GLfloat* c) {
    glVertex2fv(a);
    glVertex2fv(b);
    glVertex2fv(c);
}

void tetra(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d) {
    glColor3fv(colors[0]);
    triangle(b,d,c);
    glColor3fv(colors[1]);
    triangle(a,b,c);
    glColor3fv(colors[2]);
    triangle(a,c,d);
    glColor3fv(colors[3]);
    triangle(a,d,b);
}

void recur_tetra(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d, int m) {
    GLfloat mid[6][3];
    if (m > 0) {
        for (int j = 0; j < 3; ++j) mid[0][j] = (a[j] + b[j]) / 2;
        for (int j = 0; j < 3; ++j) mid[1][j] = (c[j] + b[j]) / 2;
        for (int j = 0; j < 3; ++j) mid[2][j] = (c[j] + a[j]) / 2;
        for (int j = 0; j < 3; ++j) mid[3][j] = (a[j] + d[j]) / 2;
        for (int j = 0; j < 3; ++j) mid[4][j] = (b[j] + d[j]) / 2;
        for (int j = 0; j < 3; ++j) mid[5][j] = (c[j] + d[j]) / 2;
        
        recur_tetra(a,mid[0],mid[2],mid[3],m - 1);
        recur_tetra(b,mid[0],mid[1],mid[4],m - 1);
        recur_tetra(c,mid[1],mid[2],mid[5],m - 1);
        recur_tetra(d,mid[3],mid[4],mid[5],m - 1);
    }
    else tetra(a,b,c,d);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-1,-1,-1,0,0,0,0,1,0);
    
    glBegin(GL_TRIANGLES);
        recur_tetra(v[0],v[1],v[2],v[4],n);
    glEnd();
    glFlush();
}

void myinit() {
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0,1.0,-1.0,1.0,0,10);
}

int main(int argc, char* argv[]) {
    n = 4;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("TriRecur 3d");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}
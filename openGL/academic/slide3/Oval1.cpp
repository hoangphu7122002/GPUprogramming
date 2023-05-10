#include <windows.h>
#include <GL/glut.h>
#include <math.h>

typedef float point[3];

point v[] = {
    {0,1,0},
    {0,-0.33333,0.942809},
    {0.816497,-0.33333,-0.471405},
    {-0.816497,-0.33333,-0.471405},
};
int n;
void triangle(point a, point b, point c) {
    glBegin(GL_POLYGON);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
    glEnd();
}

void normal(point p) {
    float d = 0.0;
    int i;
    for (i = 0; i < 3; ++i) d += p[i] * p[i];
    d = sqrt(d);
    if (d > 0.0) for (i = 0; i < 3; ++i) p[i] /= d;
}

void divideTriangle(point a, point b, point c, int m) {
    point v1, v2, v3;
    int j;
    if (m > 0) {
        for (j = 0; j < 3; j++) v1[j] = (a[j] + b[j])/2;
        normal(v1);
        for (j = 0; j < 3; j++) v2[j] = (a[j] + c[j])/2;
        normal(v2);
        for (j = 0; j < 3; j++) v3[j] = (c[j] + b[j])/2;
        normal(v3);
        divideTriangle(a,v1,v2,m - 1);
        divideTriangle(c,v2,v3,m - 1);
        divideTriangle(b,v3,v1,m - 1);
        divideTriangle(v1,v3,v2,m - 1);
    }
    else triangle(a,b,c);
}

void tet(int m) {
    divideTriangle(v[0],v[1],v[2],m);
    divideTriangle(v[3],v[2],v[1],m);
    divideTriangle(v[0],v[3],v[1],m);
    divideTriangle(v[0],v[2],v[3],m);
}

void display(void) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.5,-0.5,1.5,0,0,0,0,1,0);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    tet(n);
    
    glFlush();
}

void init() {
    glClearColor(1,1,1,1);
    
    glEnable(GL_DEPTH_TEST);
    glColor3f(0,0,0);
    
    glFrontFace(GL_CCW);
    glFrontFace(GL_CULL_FACE);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.2,1.2,-1.2,1.2,-10,10);   
}

int main(int argc, char** argv) {
    n = 7;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Sphere - 2");
    init();
    
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


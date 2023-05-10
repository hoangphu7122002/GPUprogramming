#include <windows.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

GLfloat colors[6][3] = {
    {1,1,0}, {0,1,0}, {0,0,1},
    {1,0,0}, {1,0,1}, {0,1,1}
};

struct Point3d {
    float x, y, z;
    Point3d(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Point3d() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
};

Point3d p0(0,0,0), p1(0,0,1), p2(1,0,1), p3(1,0,0);
Point3d p4(0,1,0), p5(0,1,1), p6(1,1,1), p7(1,1,0);

Point3d a(0,0,0), b(1,0,0), c(0,1,0), d(0,0,1);

float angle = 0;

void drawText(float xPos, float yPos, float zPos, string str) {
    glRasterPos3f(xPos, yPos, zPos);
    void* font = GLUT_BITMAP_9_BY_15;
    for (int i = 0; i < str.length(); ++i)
        glutBitmapCharacter(font,str[i]);
}

void drawSquare(Point3d a, Point3d b, Point3d c, GLfloat color[3]) {
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    glLineWidth(2);
    glColor3fv(color);
    glBegin(GL_POLYGON);
        glVertex3f(a.x,a.y,a.z);
        glVertex3f(b.x,b.y,b.z);
        glVertex3f(c.x,c.y,c.z);
        // glVertex3f(d.x,d.y,d.z);
    glEnd();
    // cout << "here" << endl;
}

void drawVertexsName() {
    glColor3f(0,0,0);
    
    drawText(a.x,a.y,a.z,"a");
    drawText(b.x,b.y,b.z,"b");
    drawText(c.x,c.y,c.z,"c");
    drawText(d.x,d.y,d.z,"d");
}

void drawAxis() {
    glLineWidth(3);
    glBegin(GL_LINES);
        // glVertex3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(2,0,0);
        
        // glVertex3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,2,0);
        
        // glVertex3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,2);
    glEnd();
    glColor3f(0,0,0);
    drawText(1.9,0,0,"X");
    drawText(0,1.7,0,"Y");
    drawText(0,0,1.9,"Z");
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.7,0.5,0.3,0,0,0,0,1,0);
    
    glRotatef(angle,0,1,0);
    
    drawVertexsName();
    drawAxis();
    
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    drawSquare(a,c,b,colors[0]);
    drawSquare(a,d,b,colors[1]);
    drawSquare(a,d,c,colors[2]);
    drawSquare(b,c,d,colors[3]);
    
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
    
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5,1.5,-1.5,1.5,-10,10);
}

int main(int argc,char* argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Tet");
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(mySpecialFunc);
    
    init();
    
    glutMainLoop();
}
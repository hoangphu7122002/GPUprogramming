#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

const int screenWidth = 640 * 2;
const int screenHeight = 480;

#define PI 3.1415962

void drawText(float xPos, float yPos, float zPos, string str) {
    glRasterPos3f(xPos,yPos,zPos);
    void* font = GLUT_BITMAP_TIMES_ROMAN_24;
    for (int i = 0; i < str.length(); ++i) {
        glutBitmapCharacter(font,str[i]);
    }
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
    cout  << "here" << endl;
    glColor3f(0,0,0);
    drawText(1.9,0,0,"X");
    drawText(0,1.3,0,"Y");
    drawText(0,0,1.9,"Z");
}

void setupLight() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);
    
    GLfloat lightIntensity[] = {0.7,0.7,0.7,1};
    GLfloat light_position[] = {10,9,8,0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
    
    GLfloat lightIntensity1[] = {0.7,0.7,0.7,1};
    GLfloat light_position1[] = {10,-9,8,0};
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity1);
}

void normalize(float &x, float &y, float &z) {
    float d = sqrt(x * x + y * y + z * z);
    x = x / d;
    y = y / d;
    z = z / d;
}

void calculateViewMatrix(float eyeX, float eyeY, float eyeZ, float lookX, float lookY, float lookZ, float upX, float upY, float upZ, float matrix[16]) {
    float nX, nY, nZ;
    float uX, uY, uZ;
    float vX, vY, vZ;
    
    nX = eyeX - lookX;
    nY = eyeY - lookY;
    nZ = eyeZ - lookZ;
    
    uX = upY * nZ - upZ * nY;
    uY = -(upX*nZ - upZ * nX);
    uZ = upX * nY - upY * nX;
    
    vX = nY * uZ - nZ * uY;
    vY = -(nX * uZ - nZ * uX);
    vZ = nX * uY - nY * uX;
    
    normalize(nX,nY,nZ);
    normalize(uX,uY,uZ);
    normalize(vX,vY,vZ);
    
    float dX, dY, dZ;
    dX = -(eyeX * uX + eyeY * uY + eyeZ * uZ);
    dY = -(eyeX * vX + eyeY * vY + eyeZ * vZ);
    dZ = -(eyeX * nX + eyeY * nY + eyeZ * nZ);
    
    matrix[0] = uX;
    matrix[1] = vX;
    matrix[2] = nX;
    matrix[3] = 0;
    
    matrix[4] = uY;
    matrix[5] = vY;
    matrix[6] = nY;
    matrix[7] = 0;
    
    matrix[8] = uZ;
    matrix[9] = vZ;
    matrix[10] = nZ;
    matrix[11] = 0;
    
    matrix[12] = dX;
    matrix[13] = dY;
    matrix[14] = dZ;
    matrix[15] = 1;
}

float Scale[16] = {
    1.5, 0, 0, 0,
    0, 1.5, 0, 0,
    0, 0, 1.5, 0,
    0, 0, 0, 1
};

float Rotate[16] = {
    cos(45 * PI/180), 0, -sin(45 * PI/180), 0,
    0, 1, 0, 0,
    sin(45 * PI/180), 0, cos(45*PI/180), 0,
    0, 0, 0, 1
};

void drawTeapot() {
    glColor3d(1,0,0);
    GLfloat mat_diffuse1[] = {1,0,0,1};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glPushMatrix();
    glutSolidTeapot(0.5);
    glPopMatrix();
}

void display() {
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //setup camera volume
    float aspect = 640/480;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.2 * aspect, 1.2 * aspect, -1.2 , 1.2, 0.1, 100);
    
    //setup camera position
    glViewport(0,0,screenWidth/2,screenHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(6,7,8,0,0,0,0,1,0);
    glDisable(GL_LIGHTING);
    drawAxis();
    
    setupLight();
    
    drawTeapot();
    
    glViewport(screenWidth/2,0,screenWidth/2,screenHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float matrix[16];
    calculateViewMatrix(6,7,8,0,0,0,0,1,0,matrix);
    glLoadMatrixf(matrix);
    glDisable(GL_LIGHTING);
    drawAxis();
    
    setupLight();
    // glColor3d(1,0,0);
    glColor3d(1,0,0);
    GLfloat mat_diffuse1[] = {1,0,0,1};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glPushMatrix();
    // glMultMatrixf(Rotate);
    // glMultMatrixf(Scale);
    glutSolidTeapot(0.5);
    glPopMatrix();
    
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100,100);
    glutCreateWindow("glut func");
    
    glutDisplayFunc(display);
    
    // init();
    glEnable(GL_DEPTH_TEST);
    
    glutMainLoop();
}
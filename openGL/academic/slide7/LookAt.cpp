#include <windows.h>
#include <GL/glut.h>

const int screenWidth = 640;
const int screenHeight = 480;

void init() {
    glClearColor(1,1,1,1);
    
    //set up light
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

void drawTeapot() {
    glColor3d(1,0,0);
    GLfloat mat_diffuse1[] = {1,0,0,1};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glPushMatrix();
    glutSolidTeapot(0.5);
    glPopMatrix();
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //setup camera volume
    float aspect = 640 / 480;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.2 * aspect, 1.2 * aspect, -1.2, 1.2, 0.1, 10);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // gluLookAt(0,0,10,0.0,0.0,0.0,0,1,0);
    // gluLookAt(0,0,10,0.0,1,0.0,0,1,0);
    // gluLookAt(0,0,10,0.0,0.0,0.0,2,1,0);
    // gluLookAt(0,0,10,0.0,0.0,0.0,-2,1,0);
    // gluLookAt(0,0,10,0.0,0.0,0.0,1,0,0);
    
    // gluLookAt(0,10,0,0.0,0.0,0.0,1,0,0);
    // gluLookAt(6,7,8,0.0,0.0,0.0,0,1,0);
    
    // gluLookAt(-6,-7,8,0.0,0.0,0.0,0,1,0);
    // gluLookAt(-6,-7,-8,0.0,0.0,0.0,0,1,0);
    // gluLookAt(-6,7,-8,0.0,0.0,0.0,0,1,0);
    // gluLookAt(6,-7,-8,0.0,0.0,0.0,0,1,0);
    
    drawTeapot();
    
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100,100);
    glutCreateWindow("glut func");
    
    glutDisplayFunc(Display);
    
    init();
    glEnable(GL_DEPTH_TEST);
    
    glutMainLoop();
}
#include <windows.h>
#include <GL/glut.h>

const int screenWidth = 640;
const int screenHeight = 480;

void init() {
    glClearColor(1.0,1.0,1.0,0.0);
    
    glEnable(GL_DEPTH_TEST);
    
    //setup camera
    float aspect = 6.4 / 4.8;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.2 * aspect, 1.2 * aspect, -1.2, 1.2, 0.1,100);
    
    //Set up light
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);
    
    GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat light_position[] = {10, 9, 8.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
    
    GLfloat lightIntensity1[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat light_position1[] = {10, 9, -8.0f, 0.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity1);   
}

void drawTeapot() {
    glColor3d(1,0,0);
    GLfloat mat_diffuse1[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse1);
    glPushMatrix();
    glTranslated(0,0,-1); //teapot at (0,0,-1)
    glutSolidTeapot(0.5);
    glPopMatrix();
}

void drawCube() {
    glColor3d(0,0,1);
    GLfloat mat_diffuse3[] = {0.0f, 0.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse3);
    glPushMatrix();
    glTranslated(0,0,-10); //teapot at (0,0,-10)
    glutSolidCube(1);
    glPopMatrix();
}

void drawSphere() {
    glColor3d(0,1,0);
    GLfloat mat_diffuse2[] = {0.0f, 1.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse2);
    glPushMatrix();
    glTranslated(0,0,1.0); //teapot at (0,0,1.0)
    glutSolidSphere(0.3,50,50);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,20,0.0,0.0,0.0,0.0,1.0,0.0);
    
    drawSphere();
    drawTeapot();
    drawCube();
    
    //correct order
    // drawCube();
    // drawTeapot();
    // drawSphere();
    
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH) ;
    glutInitWindowSize(screenWidth,screenHeight);
    glutInitWindowPosition(100,100);
    glutCreateWindow("depth1");
    
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
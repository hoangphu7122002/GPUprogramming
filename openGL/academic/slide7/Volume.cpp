#include <windows.h>
#include <GL/glut.h>

float screenWidth = 1200;
float screenHeight = 400;

void drawGrid(float inc = 0.1) {
    float start = -20;
    float end = -start;
    
    glLineWidth(1);
    glColor3f(0,0,0);
    float current = start;
    glBegin(GL_LINES);
    while(current <= end) {
        glVertex3f(-200,0,current);
        glVertex3f(200,0,current);
        current += inc;
    }
    
    current = start;
    while(current <= end) {
        glVertex3f(current,0,200);
        glVertex3f(current,0,-200);
        current += inc;
    }
    
    glEnd();
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

void display() {    
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    
    GLfloat mat_diffuse1[] = {1,1,1,1};
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.2,1.2,-1.2,1.2,0.1,100);
    // float near1 =0 0.1;
    // float far1 = 100;
    // float m[16] = {
    //     2 / 2.4, 0, 0, 0,
    //     0, 2 / 2.4, 0, 0,
    //     0, 0, 2 / (0.1 - 100), 0,
    //     0, 0, -(far1 + near1) / (far1 - near1), 1
    // };
    // glLoadMatrixf(m);
    
    glViewport(0,0, screenWidth/ 3, screenHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(6,7,8,0,0,0,0,1,0);
    
    glDisable(GL_LIGHTING);
    drawGrid();
    
    setupLight();
    glColor3d(1,0,0);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse1);
    glPushMatrix();
    glutSolidCube(0.5);
    glPopMatrix();
    
    //Perpestive
    float pos = 0.3;
    glLoadIdentity();
    glFrustum(-pos, pos, -pos, pos, 1, 1000);
    // float left = -pos, right = pos, bottom = -pos, top = pos;
    // float near1 = 1;
    // float far1 = 1000;
    // float m1[16] = {
    //     2 * near1 / (right - left), 0, 0, 0,
    //     0, 2 * near1 / (top - bottom), 0, 0,
    //     (right + left) / (right - left), (top + bottom) / (top - bottom), -(far1 + near1) / (far1 - near1),
    //     0, -0, -2*far1*near1 / (far1 - near1), 0
    // };
    // glLoadMatrixf(m1);
    
    glViewport(2*screenWidth/3,0, screenWidth / 3, screenHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(6,7,8,0,0,0,0,1,0);
    
    glDisable(GL_LIGHTING);
    drawGrid(0.25);
    
    setupLight();
    glColor3d(1,0,0);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse1);
    glPushMatrix();
    glutSolidCube(0.5);
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
    
    return 0;
}
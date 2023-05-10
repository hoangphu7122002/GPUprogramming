#include <windows.h>
#include <GL/glut.h>
#include <math.h>

#define DEG2RAD (3.14159f/180.f)

GLfloat angle = 0.0;

void processTimer(int value) {
    angle += (GLfloat)value;
    if (angle > 360) angle = angle - 360.0f;
    glutTimerFunc(100,processTimer,10);
    glutPostRedisplay();
}

void drawPoint(float x, float y){
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
}

void drawWing(float R, float angleinc, int i){
    angle += angleinc * i;
    if (i == 0) glColor3f(1,0,0);
    else if (i == 12) glColor3f(0,1,0);
    else glColor3f(0,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(0,0);
        for (int j = 0; j <= 1; ++j) {
              angle += angleinc * j;
            float x = R * cos(DEG2RAD * angle);
            float y = R * sin(DEG2RAD * angle);
            // drawPoint(x,y);
            glVertex2f(x,y);
        }
    glEnd();
}

void drawFan(float R) {
    float x,y;
    float angleinc = 10;
    
    glPointSize(3);
    drawPoint(0,0);
    // x = R * cos(angle);
    // y = R * sin(angle);
    // glPointSize(3);
    // drawPoint(x,y);
    drawWing(R,angleinc,0);
    angle -= angleinc * 1;
    drawWing(R,angleinc,12);
    angle -= angleinc * 13;
    drawWing(R,angleinc,24);
    angle -= angleinc * 25;
}

void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    // drawCirle(2.5);
    drawFan(2.5);
    glFlush();
}

void init()
{
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4.5,4.5,-4.5,4.5,-1,1);
}

int main(int argc, char* argv[])
{
    angle = 0.0f;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Example");
    glutDisplayFunc(mydisplay);
    glutTimerFunc(100,processTimer,10);
    init();

    glutMainLoop();
}

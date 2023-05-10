#include <windows.h>
#include <GL/glut.h>
#include <math.h>

#define DEG2RAD (3.14159f/180.f)

void drawPoint(float x, float y){
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
}

void drawCirle(float R){
    float x,y;
    float angleinc = 10;
    float angle;
    glBegin(GL_LINE_LOOP);
            angle = 0;
            x = R * cos(angle);
            y = R * sin(angle);
            glVertex2f(x,y);
            for (int i = 1; i <= 36; ++i){
                    angle += angleinc;
                    x = R * cos(DEG2RAD * angle);
                    y = R * sin(DEG2RAD * angle);
                    glVertex2f(x,y);
            }
    glEnd();
}

void drawPoint1(float R){
    float x,y;
    float angleinc = 10;
    float angle;
    angle = 0;
    glPointSize(3);
    drawPoint(0,0);
    x = R * cos(angle);
    y = R * sin(angle);
    glPointSize(3);
    drawPoint(x,y);
    for (int i = 1; i <= 36; ++i){
            angle += angleinc;
            x = R * cos(DEG2RAD * angle);
            y = R * sin(DEG2RAD * angle);
            drawPoint(x,y);
    }
    
    glBegin(GL_LINE_LOOP);
        // angle = 0;
        // x = R * cos(angle);
        // y = R * sin(angle);
        // glVertex2f(x,y);
        for (int i = 0; i <= 35; ++i){
            angle = i * angleinc;
            x = R * cos(DEG2RAD * angle);
            y = R * sin(DEG2RAD * angle);
            glVertex2f(0,0);
            glVertex2f(x,y);
        }
    glEnd();
}

void drawWing(float R, float angleinc, int i){
    for (int j = 0; j <= 1; ++j) {
        float angle = angleinc * (i + j);
        float x = R * cos(DEG2RAD * angle);
        float y = R * sin(DEG2RAD * angle);
        drawPoint(x,y);
    }
    if (i == 0) glColor3f(1,0,0);
    else if (i == 12) glColor3f(0,1,0);
    else glColor3f(0,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(0,0);
        for (int j = 0; j <= 1; ++j) {
            float angle = angleinc * (i + j);
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
    float angle;
    angle = 0;
    
    glPointSize(3);
    drawPoint(0,0);
    // x = R * cos(angle);
    // y = R * sin(angle);
    // glPointSize(3);
    // drawPoint(x,y);
    drawWing(R,angleinc,0);
    drawWing(R,angleinc,12);
    drawWing(R,angleinc,24);
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
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Example");
    glutDisplayFunc(mydisplay);
    
    init();

    glutMainLoop();
}

#include <windows.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926

float RSaokim = 2.5;
float RTraiDat = RSaokim * 149600 / 108200;

void drawCirle(float R, int n = 40){
        float x,y;
        float angleinc = 2 * PI / n;
        float angle;
        glBegin(GL_LINE_LOOP);
                angle = 0;
                x = R * cos(angle);
                y = R * sin(angle);
                glVertex2f(x,y);
                for (int i = 1; i < n; ++i){
                        angle += angleinc;
                        x = R * cos(angle);
                        y = R * sin(angle);
                        glVertex2f(x,y);
                }
        glEnd();
}

void drawDistance(){
        float angleTraidatInc = 4;
        float factor = 365.25636 / 224.7008;
        float angleSaokimInc = factor * angleTraidatInc;
        float xTraidat, yTraidat;
        float xSaokim, ySaokim;
        float angleTraidat = 90, angleSaokim = 90;
        glBegin(GL_LINES);
        for (int i = 0; i <= (360/ angleTraidatInc) * 16; ++i){
                angleTraidat -= angleTraidatInc;
                angleSaokim -= angleSaokimInc;
                xTraidat = RTraiDat*cos(angleTraidat*PI / 180);
                yTraidat = RTraiDat*sin(angleTraidat*PI / 180);
                xSaokim = RTraiDat*cos(angleSaokim*PI / 180);
                ySaokim = RTraiDat*sin(angleSaokim*PI / 180);
                glVertex2f(xTraidat,yTraidat);
                glVertex2f(xSaokim,ySaokim);
        }
        glEnd();
}

void mydisplay(){
        glClear(GL_COLOR_BUFFER_BIT);

        drawCirle(RSaokim);
        drawCirle(RTraiDat);
        drawDistance();
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
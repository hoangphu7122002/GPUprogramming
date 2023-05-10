// #include <GL/freeglut.h>
#include <windows.h>
#include <GL/glut.h>
void drawBlueBlock(float x, float y){
     glColor3f(0,0,1);
     glBegin(GL_TRIANGLES);
       glVertex2f(x,y);
       glVertex2f(x + 5,y);
       glVertex2f(x + 5,y + 2);
     glEnd();
}

void drawGreenBlock(float x, float y){
     glColor3f(0,1,0);
     glBegin(GL_QUADS);
       glVertex2f(x,y);
       glVertex2f(x + 2,y);
       glVertex2f(x + 2,y + 1);
                         glVertex2f(x, y + 1);

                         glVertex2f(x,y + 1);
                         glVertex2f(x,y + 2);
                         glVertex2f(x + 5,y + 2);
                         glVertex2f(x + 5,y + 1);
     glEnd();
}

void drawCycleBlock(float x, float y){
     glColor3f(0,1,1);
     glBegin(GL_QUADS);
       glVertex2f(x,y);
       glVertex2f(x + 5,y);
       glVertex2f(x + 5,y + 1);
                         glVertex2f(x, y + 1);

                         glVertex2f(x + 2,y + 1);
                         glVertex2f(x + 5,y + 1);
                         glVertex2f(x + 5,y + 2);
                         glVertex2f(x + 2,y + 2);
     glEnd();
}

void drawRedBlock(float x, float y){
        glColor3f(1,0,0);
        glBegin(GL_TRIANGLES);
                glVertex2f(x,y);
                glVertex2f(x + 8,y);
                glVertex2f(x + 8,y + 3);
        glEnd();
}

void drawGrid(){
        glColor3f(0,0,0);
        glBegin(GL_LINES);

        for (int i = 0; i < 15; ++i){
                glVertex2f(i,0);
                glVertex2f(i,15);
        }

        for (int i = 0; i < 15; ++i){
                glVertex2f(0,i);
                glVertex2f(15,i);
        }
        glEnd();
}

void mydisplay(){
        glClear(GL_COLOR_BUFFER_BIT);

        drawRedBlock(6,3);
        drawRedBlock(1,9);

        drawBlueBlock(1,1);
        drawBlueBlock(9,12);

        drawGreenBlock(6,1);
        drawGreenBlock(9,10);

        drawCycleBlock(9,9);
        drawCycleBlock(9,1);

        drawGrid();

        glFlush();
}

void init()
{
        glClearColor(1,1,1,1);
        glColor3f(0,0,0);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,15,0,15,-1,1);
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
        return 0;
}
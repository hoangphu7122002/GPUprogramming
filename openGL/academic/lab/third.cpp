#include <windows.h>
#include <GL/glut.h>
#include <time.h>

void init(){
        glClearColor(1.0,1.0,1.0,1.0); //white color
        glColor3f(1.0,0,0); //draw in red

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0,50.0,0.0,50.0);
        glMatrixMode(GL_MODELVIEW);
}

void display(){
        GLfloat ver[3][2] = {{0,0},{25,50},{50,0}};
        srand(time(NULL));
        GLfloat p[2] = {7.5,5.0};
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POINTS);
        for (int k = 0; k < 500000; ++k){
                int j = rand() % 3;
                p[0] = (p[0] + ver[j][0])/2.0;
                p[1] = (p[1] + ver[j][1])/2.0;
                glVertex2fv(p);
        }
        glEnd();
        glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("simple");
    glutDisplayFunc(display);

    init();

    glutMainLoop();
}
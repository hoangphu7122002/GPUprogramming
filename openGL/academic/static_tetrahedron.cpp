#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float tetra_vertices[][3] = {
    {0.0f,0.0f,1.0f},
    {0.0, 0.942809, -0.33333},
    {-0.816497, -0.471405, -0.33333},
    {0.816497, -0.471405, -0.33333}
};

void myDisplay() {
    //setup viewer camera (param)
    //direction (from eye to the ref point)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        1.5,
        1.5,
        1.5,
        0.0,
        0.0,
        0.0,
        1.0,
        0.0,
        0.0
    );
    
    //clear screen
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f,0.0f,0.0f);
        //0,2,1
        glVertex3fv(tetra_vertices[0]);
        glVertex3fv(tetra_vertices[2]);
        glVertex3fv(tetra_vertices[1]);
        
        glColor3f(0.0f,1.0f,0.0f);
        //0,1,3
        glVertex3fv(tetra_vertices[0]);
        glVertex3fv(tetra_vertices[1]);
        glVertex3fv(tetra_vertices[3]);
        
        glColor3f(0.0f,0.0f,1.0f);
        //0,3,2
        glVertex3fv(tetra_vertices[0]);
        glVertex3fv(tetra_vertices[3]);
        glVertex3fv(tetra_vertices[2]);
        
        glColor3f(1.0f,0.0f,0.0f);
        //3,1,2
        glVertex3fv(tetra_vertices[3]);
        glVertex3fv(tetra_vertices[1]);
        glVertex3fv(tetra_vertices[2]);
    glEnd();
    
    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    int size;
    if (width < height)
        size = width;
    else size = height;
    glViewport(0, 0, size, size);
}

void initOpenGL(){
//setup projection type
//glFrustrum: define viewing volume
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -1.0, //left
        1.0, //right
        -1.0, //bottom
        1.0, //top
        2.0, //near
        10.0 //far
    );
    //Default MatrixMode is MODELVIEW
    glMatrixMode(GL_MODELVIEW);
    //setup background color, or clear color
    glClearColor(0.1f, 0.7f, 0.7f, 1.0f);
}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Drawing a Tetrahedron");
    initOpenGL();
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(reshape);
    glutMainLoop();
}

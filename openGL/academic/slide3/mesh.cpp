#include <windows.h>
#include <GL/glut.h>
// #include <iostream>

// using namespace std;

GLfloat colors[4][3] = {
    {1,1,0}, {0,1,0}, {0,0,1}, {1,0,0}
};

struct Point3D {
    float x, y, z;
    Point3D(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Point3D() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
};

struct Face {
    int numVerts;
    Point3D* pointArr;
};

class Mesh {
public:
    int numFaces;
    Face* faceArr;
    void drawWireFrame() {
        for (int i = 0; i < numFaces; ++i) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glBegin(GL_POLYGON);
                for (int j = 0; j < faceArr[i].numVerts; ++j) {
                    glVertex3f(faceArr[i].pointArr[j].x, faceArr[i].pointArr[j].y, faceArr[i].pointArr[j].z);
                }
            glEnd();
        }
    }  
    
    void drawColor() {
        for (int i = 0; i < numFaces; ++i) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_POLYGON);
                for (int j = 0; j < faceArr[i].numVerts; ++j) {
                    glColor3fv(colors[i % 4]);
                    glVertex3f(faceArr[i].pointArr[j].x, faceArr[i].pointArr[j].y, faceArr[i].pointArr[j].z);
                }
            glEnd();
        }
    }  
};

Mesh myMesh;
Point3D a(0,0,0), b(1,0,0), c(0,1,0), d(0,0,1);
float angle = 0;

void createTet() {
    myMesh.numFaces = 4;
    myMesh.faceArr = new Face[myMesh.numFaces];
    myMesh.faceArr[0].numVerts = 3;
    myMesh.faceArr[0].pointArr = new Point3D[3];
    myMesh.faceArr[0].pointArr[0] = a;
    myMesh.faceArr[0].pointArr[1] = b;
    myMesh.faceArr[0].pointArr[2] = c;
    
    myMesh.faceArr[1].numVerts = 3;
    myMesh.faceArr[1].pointArr = new Point3D[3];
    myMesh.faceArr[1].pointArr[0] = a;
    myMesh.faceArr[1].pointArr[1] = b;
    myMesh.faceArr[1].pointArr[2] = d;
    
    myMesh.faceArr[2].numVerts = 3;
    myMesh.faceArr[2].pointArr = new Point3D[3];
    myMesh.faceArr[2].pointArr[0] = a;
    myMesh.faceArr[2].pointArr[1] = c;
    myMesh.faceArr[2].pointArr[2] = d;
    
    myMesh.faceArr[3].numVerts = 3;
    myMesh.faceArr[3].pointArr = new Point3D[3];
    myMesh.faceArr[3].pointArr[0] = b;
    myMesh.faceArr[3].pointArr[1] = c;
    myMesh.faceArr[3].pointArr[2] = d;   
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.7,0.5,0.3,0,0,0,0,1,0);
    
    glRotatef(angle,0,1,0);
    
    glViewport(0,0,500,500);
    myMesh.drawWireFrame();
    
    glViewport(500,0,500,500);
    myMesh.drawColor();
    glFlush();
}

void mySpecialFunc(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) 
        angle += 5;
    else if (key == GLUT_KEY_RIGHT) 
        angle -= 5;
    glutPostRedisplay();
} 

void init() {
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,0.0);
    
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5,1.5,-1.5,1.5,-10,10);
    
    createTet();
}

int main(int argc,char* argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("tet Mesh");
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(mySpecialFunc);
    
    init();
    
    glutMainLoop();
}
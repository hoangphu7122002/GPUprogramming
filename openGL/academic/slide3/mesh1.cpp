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

class VertexID{
public:
    int vertIndex;
    // int normIndex; //phap tuyen
};

class Face {
public:
    int nVerts;
    VertexID* vert;
    Face() {nVerts = 0; vert = NULL;}
    ~Face() {
        if (vert != NULL) delete[] vert; 
        nVerts = 0;}
};

class Mesh {
private:
    int numVerts;
    Point3D* pt;
    // int numNormals;
    // Vector3* norm;
    int numFaces;
    Face* face;
public:
    Mesh(){
        numVerts = 0;
        pt = NULL;
        numFaces = 0;
        face = NULL;
    };
    ~Mesh() {
        if (pt != NULL) delete[] pt;
        if (face != NULL) delete[] face;
        numVerts = 0;
        numFaces = 0;
    };
    void DrawWireframe() {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        for (int f = 0; f < numFaces; ++f) {
            glBegin(GL_POLYGON);
            for (int v = 0; v < face[f].nVerts; ++v) {
                int iv = face[f].vert[v].vertIndex;
                glVertex3f(pt[iv].x,pt[iv].y,pt[iv].z);
            }
            glEnd();
        }
    }
    
    void DrawColor() {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        for (int f = 0; f < numFaces; ++f) {
            glBegin(GL_POLYGON);
            for (int v = 0; v < face[f].nVerts; ++v) {
                int iv = face[f].vert[v].vertIndex;
                int ic = f % 4;
                glColor3fv(colors[ic]);
                glVertex3f(pt[iv].x,pt[iv].y,pt[iv].z);
            }
            glEnd();
        }
    }
    
    void createTet(Point3D a, Point3D b, Point3D c, Point3D d) {
        numVerts = 4;
        pt = new Point3D[numVerts];
        pt[0] = a;
        pt[1] = b;
        pt[2] = c;
        pt[3] = d;
        
        numFaces = 4;
        face = new Face[numFaces];
        face[0].nVerts = 3;
        face[0].vert = new VertexID[face[0].nVerts];
        face[0].vert[0].vertIndex = 1;
        face[0].vert[1].vertIndex = 2;
        face[0].vert[2].vertIndex = 3;
        
        face[1].nVerts = 3;
        face[1].vert = new VertexID[face[1].nVerts];
        face[1].vert[0].vertIndex = 0;
        face[1].vert[1].vertIndex = 2;
        face[1].vert[2].vertIndex = 1;
        
        face[2].nVerts = 3;
        face[2].vert = new VertexID[face[2].nVerts];
        face[2].vert[0].vertIndex = 0;
        face[2].vert[1].vertIndex = 3;
        face[2].vert[2].vertIndex = 2;
        
        face[3].nVerts = 3;
        face[3].vert = new VertexID[face[3].nVerts];
        face[3].vert[0].vertIndex = 1;
        face[3].vert[1].vertIndex = 3;
        face[3].vert[2].vertIndex = 0;
    }
    
};

Mesh myMesh;
Point3D a(0,0,0), b(1,0,0), c(0,1,0), d(0,0,1);
float angle = 0;

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.7,0.5,0.3,0,0,0,0,1,0);
    
    glRotatef(angle,0,1,0);
    
    glViewport(0,0,500,500);
    myMesh.DrawWireframe();
    
    glViewport(500,0,500,500);
    myMesh.DrawColor();
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
    
}

int main(int argc,char* argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("tet Mesh");
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(mySpecialFunc);
    
    myMesh.createTet(a,b,c,d);
    
    init();
    
    glutMainLoop();
}
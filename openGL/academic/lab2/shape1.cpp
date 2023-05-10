#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

// using namespace std;

#define PI 3.1415962

GLfloat colors[6][3] = {
    {1,1,0}, {0,1,0}, {0,0,1}, {1,0,0} , {1,0,1}, {0,1,1}
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
    
    void operator=(const Point3D &D) {
        this->x = D.x;
        this->y = D.y;
        this->z = D.z;
    }
    
    void set(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
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
    int nSegment;
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
                int ic = 0;
                glColor3fv(colors[ic]);
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
                int ic = 0;
                glColor3fv(colors[ic]);
                glVertex3f(pt[iv].x,pt[iv].y,pt[iv].z);
            }
            glEnd();
        }
    }
    void vien() {
        glLineWidth(4);
        glColor3f(0,0,0);
        glBegin(GL_LINES);
            for (int i = 5 * nSegment; i < 6*nSegment - 1; ++i) {
                glVertex3f(pt[i + 1].x,pt[i + 1].y,pt[i + 1].z);
                glVertex3f(pt[i + 2].x,pt[i + 2].y,pt[i + 2].z);
            }
        glEnd();
        
        glLineWidth(4);
        glColor3f(0,0,0);
        glBegin(GL_LINES);
            for (int i = 4 * nSegment; i < 5*nSegment - 1; ++i) {
                glVertex3f(pt[i + 1].x,pt[i + 1].y,pt[i + 1].z);
                glVertex3f(pt[i + 2].x,pt[i + 2].y,pt[i + 2].z);
            }
        glEnd();
        
        glLineWidth(4);
        glColor3f(0,0,0);
        glBegin(GL_LINES);
            for (int i = 3 * nSegment; i < 4*nSegment - 1; ++i) {
                glVertex3f(pt[i + 1].x,pt[i + 1].y,pt[i + 1].z);
                glVertex3f(pt[i + 2].x,pt[i + 2].y,pt[i + 2].z);
            }
        glEnd();
        
        glLineWidth(4);
        glColor3f(0,0,0);
        glBegin(GL_LINES);
            for (int i = 0 * nSegment; i < 1*nSegment - 1; ++i) {
                glVertex3f(pt[i + 1].x,pt[i + 1].y,pt[i + 1].z);
                glVertex3f(pt[i + 2].x,pt[i + 2].y,pt[i + 2].z);
            }
        glEnd();
        
        glLineWidth(4);
        glColor3f(0,0,0);
        glBegin(GL_LINES);
            for (int i = 1 * nSegment; i < 2*nSegment - 1; ++i) {
                glVertex3f(pt[i + 1].x,pt[i + 1].y,pt[i + 1].z);
                glVertex3f(pt[i + 2].x,pt[i + 2].y,pt[i + 2].z);
            }
        glEnd();
        
        glLineWidth(4);
        glColor3f(0,0,0);
        glBegin(GL_LINES);
            //
            glVertex3f(pt[1].x,pt[1].y,pt[1].z);
            glVertex3f(pt[1+nSegment].x,pt[1 + nSegment].y,pt[1 + nSegment].z);
            
            glVertex3f(pt[nSegment].x,pt[nSegment].y,pt[nSegment].z);
            glVertex3f(pt[2*nSegment].x,pt[2*nSegment].y,pt[2*nSegment].z);
            //
            
            //
            glVertex3f(pt[1+3*nSegment].x,pt[1+3*nSegment].y,pt[1+3*nSegment].z);
            glVertex3f(pt[1+nSegment].x,pt[1 + nSegment].y,pt[1 + nSegment].z);
            
            glVertex3f(pt[4*nSegment].x,pt[4*nSegment].y,pt[4*nSegment].z);
            glVertex3f(pt[2*nSegment].x,pt[2*nSegment].y,pt[2*nSegment].z);
            //
            
            //
            glVertex3f(pt[1].x,pt[1].y,pt[1].z);
            glVertex3f(pt[1+4*nSegment].x,pt[1 + 4*nSegment].y,pt[1 + 4*nSegment].z);
            
            glVertex3f(pt[nSegment].x,pt[nSegment].y,pt[nSegment].z);
            glVertex3f(pt[5*nSegment].x,pt[5*nSegment].y,pt[5*nSegment].z);
            //
            
            //
            glVertex3f(pt[1+5*nSegment].x,pt[1+5*nSegment].y,pt[1+5*nSegment].z);
            glVertex3f(pt[1+4*nSegment].x,pt[1 + 4*nSegment].y,pt[1 + 4*nSegment].z);
            
            glVertex3f(pt[6*nSegment].x,pt[6*nSegment].y,pt[6*nSegment].z);
            glVertex3f(pt[5*nSegment].x,pt[5*nSegment].y,pt[5*nSegment].z);
            //
            
            //
            glVertex3f(pt[1+2*nSegment].x,pt[1+2*nSegment].y,pt[1+2*nSegment].z);
            glVertex3f(pt[1+3*nSegment].x,pt[1 + 3*nSegment].y,pt[1 + 3*nSegment].z);
            
            glVertex3f(pt[3*nSegment].x,pt[3*nSegment].y,pt[3*nSegment].z);
            glVertex3f(pt[4*nSegment].x,pt[4*nSegment].y,pt[4*nSegment].z);
            //
            
            //
            glVertex3f(pt[1+2*nSegment].x,pt[1+2*nSegment].y,pt[1+2*nSegment].z);
            glVertex3f(pt[1+5*nSegment].x,pt[1 + 5*nSegment].y,pt[1 + 5*nSegment].z);
            
            glVertex3f(pt[3*nSegment].x,pt[3*nSegment].y,pt[3*nSegment].z);
            glVertex3f(pt[6*nSegment].x,pt[6*nSegment].y,pt[6*nSegment].z);
            //
        glEnd();
    }
    
    void createShape2(int nSegment, float lHeight, float hHeight, float fIRadius, float fORadius, float fAngle, float smallRadius) {
        this->nSegment = nSegment;
        numVerts = nSegment * 6 + 2;
        pt = new Point3D[numVerts];
        
        int i;
        int idx;
        fAngle = fAngle/nSegment;
        float x,y,z;
        
        //far
        pt[0].set(0,0,0);
        for (i = 0; i < nSegment; ++i) {
            x =  fORadius * cos(fAngle * i);
            z =  fORadius * sin(fAngle * i);
            pt[i + 1].set(x,0,z);
            pt[i + nSegment + 1].set(x,hHeight,z);
        }
        
        //near
        pt[numVerts-1].set(0,lHeight,0);
        for (i = 0; i < nSegment; ++i) {
            x =  fIRadius * cos(fAngle * i);
            z =  fIRadius * sin(fAngle * i);
            pt[i + 2*nSegment + 1].set(x,lHeight,z);
            pt[i + 3*nSegment + 1].set(x,hHeight,z);
        }
        
        for (i = 0; i < nSegment; ++i) {
            x =  smallRadius * cos(fAngle * i);
            z =  smallRadius * sin(fAngle * i);
            pt[i + 4*nSegment + 1].set(x,0,z);
            pt[i + 5*nSegment + 1].set(x,lHeight,z);
        }
        
        numFaces = nSegment * 8; 
        face = new Face[numFaces];
        
        idx = 0;
        
        //tu giac tren
        for (i = 5*nSegment; i < 6*nSegment - 1; ++i) {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];
            face[idx].vert[0].vertIndex = i + 1;
            face[idx].vert[1].vertIndex = i + 2;
            face[idx].vert[2].vertIndex = i + 2 - 3*nSegment;
            face[idx].vert[3].vertIndex = i + 1 - 3*nSegment;
            idx++;
        }
        
        //tu giac duoi
        for (i = 4*nSegment; i < 5*nSegment - 1; ++i) {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];
            face[idx].vert[0].vertIndex = i + 1;
    		face[idx].vert[1].vertIndex = i + 2;
            
            face[idx].vert[2].vertIndex = i + 2 - 4 * nSegment;   
            face[idx].vert[3].vertIndex = i + 1 - 4 * nSegment;
            idx++;
        }
        
        //mat tu giac ngoai
        for (i = 0; i < nSegment; ++i) {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];
            face[idx].vert[0].vertIndex = i + 1 + 4*nSegment;
            face[idx].vert[1].vertIndex = i + 1 + 5*nSegment;
            face[idx].vert[2].vertIndex = i + 1 + 2*nSegment;
            face[idx].vert[3].vertIndex = i + 1;
            
            idx++;
        }
        
        //mat tu giac truoc nho
        for (i = 4*nSegment; i < 5 * nSegment - 1; ++i) {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];
            face[idx].vert[0].vertIndex = i + 1;
            face[idx].vert[1].vertIndex = i + 2;
            face[idx].vert[2].vertIndex = i + 2 + nSegment;
            face[idx].vert[3].vertIndex = i + 1 + nSegment;
            
            idx++;
        }
        
        //mat chu nhat nho phia truoc
        for (i = 2*nSegment; i < 3*nSegment - 1; ++i) {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];
            face[idx].vert[0].vertIndex = i + 1;
            face[idx].vert[1].vertIndex = i + 2;
            face[idx].vert[2].vertIndex = i + 2 + nSegment;
            face[idx].vert[3].vertIndex = i + 1 + nSegment;
            idx++;
        }
        
        //mat ben chu nhat nho
        for (i = 2*nSegment; i < 3*nSegment - 1; ++i) {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];
            face[idx].vert[0].vertIndex = i + 1;
            face[idx].vert[1].vertIndex = i + nSegment + 1;
            face[idx].vert[2].vertIndex = i - nSegment + 1;
            face[idx].vert[3].vertIndex = i - 2 * nSegment + 1;
            idx++;
        }
        
        //mat hinh chu nhat ngoai nho
        for (i = 0; i < nSegment - 1; ++i) {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];
            face[idx].vert[0].vertIndex = i + 1;
            face[idx].vert[1].vertIndex = i + 1 + nSegment;
            face[idx].vert[2].vertIndex = i + 2  + nSegment;
            face[idx].vert[3].vertIndex = i + 2;
            idx++;
        }
        
        //mat hinh chu nhat tren
        for (i = 3*nSegment; i < 4*nSegment - 1; ++i) {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];
            face[idx].vert[0].vertIndex = i + 1;
            face[idx].vert[1].vertIndex = i + 2;
            face[idx].vert[2].vertIndex = i + 2  - 2 * nSegment;
            face[idx].vert[3].vertIndex = i + 1 - 2 * nSegment;
            idx++;
        }
    }
};

void drawText(float xPos, float yPos, float zPos, char str[]) {
    glRasterPos3f(xPos, yPos, zPos);
    void* font = GLUT_BITMAP_9_BY_15;
    for (int i = 0; i < strlen(str); ++i)
        glutBitmapCharacter(font,str[i]);
}

void drawAxis() {
    glLineWidth(3);
    glBegin(GL_LINES);
        // glVertex3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(2,0,0);
        
        // glVertex3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,2,0);
        
        // glVertex3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,2);
    glEnd();
    glColor3f(0,0,0);
    drawText(1.9,0,0,"X");
    drawText(0,1.7,0,"Y");
    drawText(0,0,1.9,"Z");
}

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
    drawAxis();
    
    glViewport(500,0,500,500);
    myMesh.DrawColor();
    myMesh.vien();
    
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
    glOrtho(-4,4,-4,4,-10,10);
}

int main(int argc,char* argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("tet Mesh");
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(mySpecialFunc);
    
    myMesh.createShape2(32,1,2,2,3,PI/2,1);
    
    init();
    
    glutMainLoop();
}
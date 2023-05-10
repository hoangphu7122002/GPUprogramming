#include <windows.h>
#include <GL/glut.h>
#include <math.h>
// #include <iostream>

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
                int ic = f % 6;
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
                int ic = f % 6;
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
    
    void createCuboid(float fsizeX, float fsizeY, float fsizeZ) {
        numVerts = 8;
        float x = fsizeX / 2;
        float y = fsizeY / 2;
        float z = fsizeZ / 2;
        pt = new Point3D[numVerts];
        pt[0] = Point3D(x,-y,z);
        pt[1] = Point3D(x,-y,-z);
        pt[2] = Point3D(x,y,-z);
        pt[3] = Point3D(x,y,z);
        pt[4] = Point3D(-x,y,-z);
        pt[5] = Point3D(-x,y,z);
        pt[6] = Point3D(-x,-y,z);
        pt[7] = Point3D(-x,-y,-z);
        
        numFaces = 6;
        face = new Face[numFaces];
        
        face[0].nVerts = 4;
        face[0].vert = new VertexID[face[0].nVerts];
        face[0].vert[0].vertIndex = 0;
        face[0].vert[1].vertIndex = 1;
        face[0].vert[2].vertIndex = 2;
        face[0].vert[3].vertIndex = 3;
        
        face[1].nVerts = 4;
        face[1].vert = new VertexID[face[1].nVerts];
        face[1].vert[0].vertIndex = 2;
        face[1].vert[1].vertIndex = 4;
        face[1].vert[2].vertIndex = 5;
        face[1].vert[3].vertIndex = 3;
        
        face[2].nVerts = 4;
        face[2].vert = new VertexID[face[2].nVerts];
        face[2].vert[0].vertIndex = 4;
        face[2].vert[1].vertIndex = 5;
        face[2].vert[2].vertIndex = 6;
        face[2].vert[3].vertIndex = 7;
        
        face[3].nVerts = 4;
        face[3].vert = new VertexID[face[3].nVerts];
        face[3].vert[0].vertIndex = 0;
        face[3].vert[1].vertIndex = 1;
        face[3].vert[2].vertIndex = 7;
        face[3].vert[3].vertIndex = 6;
        
        face[4].nVerts = 4;
        face[4].vert = new VertexID[face[4].nVerts];
        face[4].vert[0].vertIndex = 5;
        face[4].vert[1].vertIndex = 6;
        face[4].vert[2].vertIndex = 0;
        face[4].vert[3].vertIndex = 3;
        
        face[5].nVerts = 4;
        face[5].vert = new VertexID[face[5].nVerts];
        face[5].vert[0].vertIndex = 4;
        face[5].vert[1].vertIndex = 7;
        face[5].vert[2].vertIndex = 1;
        face[5].vert[3].vertIndex = 2;
    }
      
    void createCylinder(int nSegment, float fHeight, float fRadius) {
        numVerts = nSegment*2 + 2;
        pt = new Point3D[numVerts];
        
        int i;
        int idx;
        float fAngle = 2*PI/nSegment;
        float x,y,z;
        
        pt[0].set(0,fHeight/2,0);
        for (i = 0; i < nSegment; ++i) {
            x =  fRadius * cos(fAngle * i);
            z =  fRadius * sin(fAngle * i);
            y = fHeight/2;
            pt[i + 1].set(x,y,z);
            y = -fHeight/2;
            pt[i + 1 + nSegment].set(x,y,z);
        }
        
        pt[numVerts - 1].set(0,-fHeight/2,0);
        
        numFaces = nSegment * 3;
        face = new Face[numFaces];
        
        idx = 0;
        for (i = 0; i < nSegment; ++i) {
            face[idx].nVerts = 3;
            face[idx].vert = new VertexID[face[idx].nVerts];
            face[idx].vert[0].vertIndex = 0;
            if (i < nSegment - 1) {
    			face[idx].vert[1].vertIndex = i + 2;
            }
            else face[idx].vert[1].vertIndex = 1;
            face[idx].vert[2].vertIndex = i + 1;
            idx++;
        }
        
        for(i = 0; i<nSegment; i++){
    		face[idx].nVerts = 4;
    		face[idx].vert = new VertexID[face[idx].nVerts];
    		
    		face[idx].vert[0].vertIndex = i+1;
    		if(i <nSegment - 1)
    			face[idx].vert[1].vertIndex = i+2;
    		else
    			face[idx].vert[1].vertIndex = 1;
    		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
    		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;
    
    		idx++;
    	}
        
        for(i = 0; i<nSegment; i++){
    		face[idx].nVerts = 3;
    		face[idx].vert = new VertexID[face[idx].nVerts];
    		face[idx].vert[0].vertIndex = numVerts - 1;
    		if(i < nSegment -1)
    			face[idx].vert[2].vertIndex = i + 2 + nSegment;
    		else
    			face[idx].vert[2].vertIndex = 1 + nSegment;
    		face[idx].vert[1].vertIndex = i + 1 + nSegment;
    		idx++;
    	}
    }
    
    void createCylinderHole(int nSegment, float fHeight, float fORadius, float fIRadius) {
        numVerts = nSegment*4;
        pt = new Point3D[numVerts];
        
        int i;
        int idx;
        float fAngle = 2*PI/nSegment;
        float x,y,z;
        
        //outside
        for (i = 0; i < nSegment; ++i) {
            x =  fORadius * cos(fAngle * i);
            z =  fORadius * sin(fAngle * i);
            y = fHeight/2;
            pt[i].set(x,y,z);
            y = -fHeight/2;
            pt[i + nSegment].set(x,y,z);
        }
        
        //inside
        for (i = 0; i < nSegment; ++i) {
            x =  fIRadius * cos(fAngle * i);
            z =  fIRadius * sin(fAngle * i);
            y = fHeight/2;
            pt[i + 2 * nSegment].set(x,y,z);
            y = -fHeight/2;
            pt[i + 3 * nSegment].set(x,y,z);
        }
        
        numFaces = nSegment * 4;
        face = new Face[numFaces];
        
        idx = 0;
        //Outside
        for (i = 0; i < nSegment; ++i) {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];
            face[idx].vert[0].vertIndex = i;
            if (i < nSegment - 1) {
    			face[idx].vert[1].vertIndex = i + 1;
            }
            else face[idx].vert[1].vertIndex = 0;
            face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
            face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;            
            
            idx++;
        }
        
        //inside
        for (i = 2*nSegment; i < 3*nSegment; ++i) {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];
            face[idx].vert[0].vertIndex = i;
            if (i < 3*nSegment - 1) {
    			face[idx].vert[1].vertIndex = i + 1;
            }
            else face[idx].vert[1].vertIndex = 2*nSegment;
            face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
            face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;            
            
            idx++;
        }
        
        //top
        for (i = 0; i < nSegment; ++i) {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];
            face[idx].vert[0].vertIndex = i;
            if (i < nSegment - 1) {
    			face[idx].vert[1].vertIndex = i + 1;
            }
            else face[idx].vert[1].vertIndex = 0;
            face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2*nSegment;
            face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2*nSegment;            
            
            idx++;
        }        
        
        //bottom
        for (i = 0; i < nSegment; ++i) {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];
            face[idx].vert[0].vertIndex = i + nSegment;
            if (i < nSegment - 1) {
    			face[idx].vert[1].vertIndex = i + 1 + nSegment;
            }
            else face[idx].vert[1].vertIndex = nSegment;
            face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2*nSegment;
            face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2*nSegment;            
            
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
    
    myMesh.createCylinderHole(32,3,4,3);
    
    init();
    
    glutMainLoop();
}
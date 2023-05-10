#include "supportClass.hpp"

class VertexID
{
public:
	int	vertIndex;
	int	colorIndex;
};

class Face
{
public:
	int	nVerts;
	VertexID* vert;
	
	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if(vert !=NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int	numVerts;
	Point3*	pt;
	
	int	numFaces;
	Face* face;
public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void reset() {
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();
};

class Cylinder : public Mesh {
private:
	int nSegments;
	float height, radius;
public:     
	Cylinder(int nSegments, float height, float radius){
		this->nSegments = nSegments;
		this->height = height;
		this->radius = radius;
	}
	int getNSegments() {return this->nSegments;}
	float getHeight() {return this->height;}
	float getRadius() {return this->radius;}
	void createShape();
};

class Cuboid : public Mesh {
private:
	float fsizeX;
	float fsizeY;
	float fsizeZ;
public:
	Cuboid(float x, float y, float z) {
		this->fsizeX = x;
		this->fsizeY = y;
		this->fsizeZ = z;
	}
	
	float getX() {return this->fsizeX;}
	float getY() {return this->fsizeY;}
	float getZ() {return this->fsizeZ;}
	void createShape();
};

class Shape1 : public Mesh {
private:
	int nSegment;
	float lHeight;
	float hHeight; 
	float fIRadius; 
	float fORadius; 
	float fAngle;
	float smallRadius;
public:
	Shape1(int nSegment, float lHeight, float hHeight, float fIRadius, float fORadius, float fAngle, float smallRadius){
		this->nSegment = nSegment;
		this->lHeight = lHeight;
		this->hHeight = hHeight;
		this->fIRadius = fIRadius;
		this->fORadius = fORadius;
		this->fAngle = fAngle;	
		this->smallRadius = smallRadius;
	}
	void creatShape();
};

class Shape2 : public Mesh {
private:
	int nSegment;
	float lHeight;
	float hHeight;
	float fIRadius;
	float fORadius;
	float fAngle;
public:
	Shape2(int nSegment, float lHeight, float hHeight, float fIRadius, float fORadius, float fAngle){
		this->nSegment = nSegment;
		this->lHeight = lHeight;
		this->hHeight = hHeight;
		this->fIRadius = fIRadius;
		this->fORadius = fORadius;
		this->fAngle = fAngle;	
	}
	void creatShape();
};
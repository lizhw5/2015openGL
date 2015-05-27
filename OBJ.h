/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#ifndef OBJ_H
#define OBJ_H
#include <vector>
#include "Vertex.h"
#include "Material.h"
using namespace std;
/*点类*/
class cPoint
{
friend class cOBJ;
public:
	void render(const cOBJ &Obj);
private:
	int VIndex;									//顶点坐标
};

/*线类*/
class cLine
{
friend class cOBJ;
public:
	void render(const cOBJ &Obj);
private:
	vector<int> Vindexs;						//顶点坐标
};

/*面类*/
class cFace
{
friend class cOBJ;
public:
	cFace();
	void render(cOBJ &Obj);
private:
	vector<sVertexData> Vindexs;				//顶点索引
	int Mindex;									//材质索引
};
/*OBJ 类*/
class cOBJ
{
friend class cPoint;
friend class cLine;
friend class cFace;
public:
	cOBJ();
	cOBJ(const char* FilePath);
	bool loadObjFromFile(const char* FilePath);	//load *.obj
	bool loadMaterialFromFile(const char* FilePath);//load *.mtl
	void render();
	void print_vetor();
private:
	vector<sVertex> Vertexs;					//顶点坐标集合
	vector<sTextureVertex> TVertex;				//顶点纹理坐标集合
	vector<sNormalVertex> NVertex;				//顶点法线集合
	vector<cPoint> Points;						//点集合
	vector<cLine> Lines;						//线集合
	vector<cFace> Faces;						//面集合
	vector<cMaterial> Materials;				//材质库
};
#endif
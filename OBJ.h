/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#ifndef OBJ_H
#define OBJ_H
#include <vector>
#include "Vertex.h"
#include "Material.h"
using namespace std;
/*����*/
class cPoint
{
friend class cOBJ;
public:
	void render(const cOBJ &Obj);
private:
	int VIndex;									//��������
};

/*����*/
class cLine
{
friend class cOBJ;
public:
	void render(const cOBJ &Obj);
private:
	vector<int> Vindexs;						//��������
};

/*����*/
class cFace
{
friend class cOBJ;
public:
	cFace();
	void render(cOBJ &Obj);
private:
	vector<sVertexData> Vindexs;				//��������
	int Mindex;									//��������
};
/*OBJ ��*/
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
	vector<sVertex> Vertexs;					//�������꼯��
	vector<sTextureVertex> TVertex;				//�����������꼯��
	vector<sNormalVertex> NVertex;				//���㷨�߼���
	vector<cPoint> Points;						//�㼯��
	vector<cLine> Lines;						//�߼���
	vector<cFace> Faces;						//�漯��
	vector<cMaterial> Materials;				//���ʿ�
};
#endif
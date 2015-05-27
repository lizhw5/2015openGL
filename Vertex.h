/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#ifndef VERTEX_H
#define VERTEX_H

/*顶点坐标*/
struct sVertex
{
	double fX;
	double fY;
	double fZ;
};

/*顶点纹理坐标*/
struct sTextureVertex
{
	double fS;
	double fT;
	double fP;
};

/*顶点法线坐标*/
struct sNormalVertex
{
	double fX;
	double fY;
	double fZ;
};

/*顶点*/
struct sVertexData
{
	int m_nVI;					//顶点坐标索引
	bool m_bVt;
	int m_nVtI;					//对应纹理坐标索引
	bool m_bVn;
	int m_nVnI;					//对应法线坐标索引
};

#endif
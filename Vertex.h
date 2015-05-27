/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#ifndef VERTEX_H
#define VERTEX_H

/*��������*/
struct sVertex
{
	double fX;
	double fY;
	double fZ;
};

/*������������*/
struct sTextureVertex
{
	double fS;
	double fT;
	double fP;
};

/*���㷨������*/
struct sNormalVertex
{
	double fX;
	double fY;
	double fZ;
};

/*����*/
struct sVertexData
{
	int m_nVI;					//������������
	bool m_bVt;
	int m_nVtI;					//��Ӧ������������
	bool m_bVn;
	int m_nVnI;					//��Ӧ������������
};

#endif
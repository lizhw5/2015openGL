/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#ifndef MATERIAL_H
#define MATERIAL_H
#include <array>
#include "Texture.h"
#include "util.h"
class cOBJ;
//���� glMaterial{if}(GLenum face, GLenum pname, TYPE param);
//array<float,4> for array[0]->R array[1]->G array[2]->B array[3]->A
class cMaterial
{
friend class cOBJ;
public:
	cMaterial();
	cMaterial(array<float,4> _ambient,array<float,4> _diffuse,array<float,4> _specular,array<float,4> _emission,float _fShiness,float _fTrans);
	~cMaterial();
	bool initTexture();				//load texture from texturePath[];
	void setMaterial();
	void setTexturePath(const char* FilePath);
	//!TODO: ���Ӹ����ʲ�����Set��Get����

private:
	array<float, 4> ambient;		//���ʵĻ�����ɫ
	array<float, 4> diffuse;		//��������γɵĹ���ǿ��
	array<float, 4> specular;		//���淴����γɵĹ���ǿ��
	array<float, 4> emission;		//�ò��ʱ����΢΢�����ⷢ����ߵ���ɫ
	float fShiness;					//����ָ��
	float fTrans;					//͸����
	char MaterialName[PATH_SIZE];	//��������
	cTexture tex;					//����
	char texturePath[PATH_SIZE];	//����·�� *.png *.jpg *.tga etc.
};
#endif
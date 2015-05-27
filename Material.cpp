#define _CRT_SECURE_NO_WARNINGS
#include "Material.h"
cMaterial::cMaterial(){
	for(int i=0;i<4;++i){
		ambient[i]=1.0;
		diffuse[i]=1.0;
		specular[i]=1.0;
	}
	for(int i=0;i<4;++i){
		emission[i]=0;
	}
	fShiness=50.0;
	fTrans=1.0;
}
cMaterial::cMaterial(array<float,4> _ambient,array<float,4> _diffuse,array<float,4> _specular,array<float,4> _emission,float _fShiness,float _fTrans){
	ambient=_ambient;
	diffuse=_diffuse;
	specular=_specular;
	emission=_emission;
	fShiness=_fShiness;
	fTrans=_fTrans;
}
cMaterial::~cMaterial(){
	//do nothing
}
bool cMaterial::initTexture(){
	return tex.loadTexture(texturePath);
}
void cMaterial::setTexturePath(const char* FilePath){
	if(strlen(FilePath)>=PATH_SIZE)
		printf("texture path too long!\n");
	strcpy(texturePath,FilePath);
}
void cMaterial::setMaterial(){
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_ADD);*/
	//设置材质
	glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient[0]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &specular[0]);
	glMaterialfv(GL_FRONT, GL_EMISSION, &emission[0]);
	//glMaterialf(GL_FRONT, GL_SHININESS, fShiness);   //暂时不用
	//设置纹理

	tex.bindTexutre();
}
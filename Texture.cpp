/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#define _CRT_SECURE_NO_WARNINGS
#include "Texture.h"
cTexture::cTexture(){
	pic=0;
	fif=FIF_UNKNOWN;
	width=height=0;
	bits=0;
	texureId=0;
}
cTexture::cTexture(const char*FilePath){
	loadTexture(FilePath);
}
cTexture::~cTexture(){
	unloadTexture();
}
bool cTexture::loadTexture(const char* FilePath){
	//防止重复加载同一张图片
	if(strcmp(FilePath,_FilePath)==0){
		return true;
	}
	//获取图片
	fif=FreeImage_GetFileType(FilePath,0);									
	//识别图片格式
	if(fif == FIF_UNKNOWN){
		fif=FreeImage_GetFIFFromFilename(FilePath);
	}
	if(fif==FIF_UNKNOWN || !FreeImage_FIFSupportsReading(fif)){
		printf("FIError: not support type");
		return false;
	}
	//加载图片
	pic=FreeImage_Load(fif,FilePath);
	if(!pic){
		printf("Texture Error: cant not load!\n");
		return false;
	}
	//获取像素格式
	bits = FreeImage_GetBits(pic);
	width = FreeImage_GetWidth(pic);
	height = FreeImage_GetHeight(pic);
	show(width);show(height);
	if(bits==0 || width ==0 || height==0)
		return false;
	strcpy(_FilePath,FilePath);
	//加载texture 到显存
	glGenTextures(1, &texureId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D,texureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Min Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Mag Filter
	if(fif==FIF_PNG||fif==FIF_TARGA||fif==FIF_GIF)
		glTexImage2D(GL_TEXTURE_2D,0,3,width,height,0,GL_BGRA_EXT,GL_UNSIGNED_BYTE,bits);//支持透明的图片格式 需要设置格式为BGRA
	else
		glTexImage2D(GL_TEXTURE_2D,0,3,width,height,0,GL_BGR_EXT,GL_UNSIGNED_BYTE,bits);//不支持透明的图片格式 
	return true;
}
void cTexture::unloadTexture(){
	if(!pic)
		FreeImage_Unload(pic);
}
void cTexture::bindTexutre(){
	glBindTexture(GL_TEXTURE_2D,texureId);

}
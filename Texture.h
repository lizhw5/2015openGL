/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#ifndef TEXTURE_H
#define TEXTURE_H
#include <gl/glut.h>
#include <FreeImage.h>
#include "util.h"
#pragma comment(lib, "FreeImage.lib")
class cTexture
{
public:
	cTexture();
	cTexture(const char* FilePath);
	~cTexture();
	bool loadTexture(const char* FilePath);	//只调用一次
	void unloadTexture();
	void bindTexutre();						// 每次render调用
private:
	FIBITMAP *pic;
	FREE_IMAGE_FORMAT fif;
	unsigned int width,height;
	BYTE *bits;
	GLuint texureId;
	char _FilePath[PATH_SIZE];
};

#endif
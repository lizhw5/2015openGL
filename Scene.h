#ifndef SCENE_H
#define SCENE_H
#include "OBJ.h"
#include "Camera.h"
#include "Player.h"
class cScene
{
public:
	cScene();
	~cScene();
	void render();
private:
	cOBJ SkyBox;
	cOBJ LandForm;
	//cCamera *Camera;
	cPlayer Player;
}

#endif
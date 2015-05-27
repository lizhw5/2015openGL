#ifndef PLAYER_H
#define PLAYER_H
#include "OBJ.h"
#include "Camera.h"

#define PLAY_STATE_IDLE 0
#define PLAY_STATE_WALKING 1
#define PLAY_STATE_JUMPING 2

struct sBox
{

};

class cPlayer{
public:
	bool collisionCheck();
	void moveForward();
	void moveBack();
	void moveLeft();
	void moveRight();
	void jump();
private:
	cOBJ PlayerOBJ;
	sBox BoundingBox;			//最小包围盒
	cCamera Camera;				//摄像机
	array<double,3> Positon;	//位置
	array<float, 3> Face;		//朝向
	unsigned int state;			//状态
};
#endif
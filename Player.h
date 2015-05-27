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
	sBox BoundingBox;			//��С��Χ��
	cCamera Camera;				//�����
	array<double,3> Positon;	//λ��
	array<float, 3> Face;		//����
	unsigned int state;			//״̬
};
#endif
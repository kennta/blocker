#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Character.h"

class SceneBase;

class Block : public Character
{
public:
	Block(SceneBase& scene);
	virtual ~Block();

	virtual void onTick();
	virtual void onDraw(Graphics& g);
	virtual double getWidth();
	virtual double getHeight();
	virtual void addDamage(int damage);

private:
	SceneBase& _scene;
	double _width;
	double _height;
	int _hp;
};

#endif // _BALL_H_

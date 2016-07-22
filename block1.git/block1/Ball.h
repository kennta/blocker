#ifndef _BALL_H_
#define _BALL_H_

#include "Character.h"

class SceneBase;

class Ball : public Character
{
public:
	Ball(SceneBase& scene);
	virtual ~Ball();

    virtual void onTick();
    virtual void onDraw(Graphics& g);
	int hit_flag = 0;
	double vx;
	double vy;
	int _isShot = 0;

private:
    SceneBase& _scene;


};

#endif // _BALL_H_

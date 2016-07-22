#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_

#include "SceneBase.h"
#include "Player.h"
#include "Ball.h"
#include "Block.h"
#include <list>

class SceneGame : public SceneBase
{
public:
    SceneGame();
    virtual ~SceneGame();
    virtual bool onInit();
    virtual void onRelease();
    virtual void onTick();
    virtual void onDraw(Graphics& g);

    virtual Player& getPlayer();
	virtual Ball& getBall();

	virtual int isHit(Character& c);
	virtual int _isHit(Vector2Df upleft, Vector2Df upright, Vector2Df downleft, Vector2Df downright);

private:
    Player _player;
    Ball   _ball;
	std::list<Block> _block;
	int _hitCount;

};

#endif // _SCENE_GAME_H_

#include "GameDefine.h"
#include "SceneGame.h"
#include "debug.h"

#include <windows.h>
#include <math.h>

#include "GameMain.h"
#include "TaskManager.h"
#include "SceneTitle.h"
#include <list>
#include <iostream>


using namespace std;

SceneGame::SceneGame()
    : _player(*this)
    , _ball(*this)
{
	for (int i = 1; i <= CLEAR_COUNT; i++) {
		_block.push_back(Block(*this));
	}
}

SceneGame::~SceneGame()
{
}

bool SceneGame::onInit()
{

	std::list<Block>::iterator itr;
	int count = 1;
	for (auto itr = _block.begin(); itr != _block.end(); ++itr) {
		(*itr).setPos(Vector2Df( 2 * BLOCK_WIDTH * count, 100));
		if (count > 5 && count <= 10) {
			(*itr).setPos(Vector2Df((2 * BLOCK_WIDTH * count) - (BLOCK_WIDTH * 10), 100 + 2 * BLOCK_HEIGHT));
		}
		else if (count > 10) {
			(*itr).setPos(Vector2Df((2 * BLOCK_WIDTH * count) - (BLOCK_WIDTH * 20), 100 + 4 * BLOCK_HEIGHT));
		}
		count++;
	}

    _player.setPos(Vector2Df(DWIDTH / 2, DHEIGHT - 100));
	_ball.setPos(Vector2Df(_player.getPos().x, _player.getPos().y - 2.5 * BALL_SIZE));

    TaskManager::getInstance().addDrawTask(this, TASK_PRIORITY_SCENE);
	
    return true;
}

void SceneGame::onRelease()
{
    GameMain::getInstance().changeScene(new SceneTitle()); // SCENE_GAME 再開
}

void SceneGame::onTick()
{
    _player.onTick();
	_ball.onTick();

	std::list<Block>::iterator itr;
	int count = 1;
	for (auto itr = _block.begin(); itr != _block.end(); ++itr) {
		(*itr).onTick();
		if (isHit((*itr))) {
			(*itr).addDamage(1);
			(*itr).setPos(Vector2Df(DWIDTH + BLOCK_WIDTH * 2, DHEIGHT + BLOCK_HEIGHT));
		}
		count++;
	}

	if (_ball.getPos().y > DHEIGHT - 2 * BALL_SIZE) {
		kill();
	}

	if (_hitCount >= 1) {
		kill();
	}

	isHit(_player);
}

void SceneGame::onDraw(Graphics& g)
{
    _player.onDraw(g);
	_ball.onDraw(g);
	std::list<Block>::iterator itr;
	int count = 1;
	for (auto itr = _block.begin(); itr != _block.end(); ++itr) {
		(*itr).onDraw(g);
		count++;
	}
}

Player&SceneGame::getPlayer()
{
    return _player;
}

Ball&SceneGame::getBall()
{
	return _ball;
}


int SceneGame::isHit(Character& c)
{
	Vector2Df ul = Vector2Df(c.getPos().x - c.getWidth(), c.getPos().y - c.getHeight());
	Vector2Df ur = Vector2Df(c.getPos().x + c.getWidth(), c.getPos().y - c.getHeight());
	Vector2Df dl = Vector2Df(c.getPos().x - c.getWidth(), c.getPos().y + c.getHeight());
	Vector2Df dr = Vector2Df(c.getPos().x + c.getWidth(), c.getPos().y + c.getHeight());

	return SceneGame::_isHit(ul, ur, dl, dr);
}

int SceneGame::_isHit(Vector2Df upleft, Vector2Df upright, Vector2Df downleft, Vector2Df downright)
{
	int isHit = 0;

	// 上側の判定
	// ベクトル
	Vector2Df ulur = upright - upleft;
	Vector2Df ulb = _ball.getPos() - upleft;

	// 内積
	int inner = ulur * ulb;

	// なす角
	double nas1 = acos((inner) / (ulur.length() * ulb.length()));

	if (((ulb.length() * sin(nas1)) < BALL_SIZE))
	{
		if (_ball.getPos().x >= upleft.x && _ball.getPos().x <= upright.x) {
			_ball.vy *= -1;
			isHit = 1;
		}
	}

	// 左側の判定
	// ベクトル
	Vector2Df dlul = upleft - downleft;
	Vector2Df dlb = _ball.getPos() - downleft;

	// 内積
	int inner2 = dlul * dlb;

	// なす角
	double nas2 = acos((inner2) / (dlul.length() * dlb.length()));

	if (((dlb.length() * sin(nas2)) < BALL_SIZE))
	{
		if (_ball.getPos().x <= downleft.x + (BALL_SIZE / 2 + 5) && _ball.getPos().y >= upleft.y && _ball.getPos().y <= downleft.y) {
			_ball.vx *= -1;
			isHit = 1;
		}
	}

	// 右側の判定
	// ベクトル
	Vector2Df drur = upright - downright;
	Vector2Df drb  = _ball.getPos() - downright;

	// 内積
	int inner3 = drur * drb;

	// なす角
	double nas3 = acos((inner3) / (drur.length() * drb.length()));

	if (((drb.length() * sin(nas3)) < BALL_SIZE))
	{
		if (_ball.getPos().x <= downright.x + (BALL_SIZE / 2 + 5) && _ball.getPos().y >= upright.y && _ball.getPos().y <= downright.y) {
			_ball.vx *= -1;
			isHit = 1;
		}
	}

	// 下側の判定
	// ベクトル
	Vector2Df pdlpdr = downright - downleft;

	// 内積
	int inner4 = pdlpdr * dlb;

	// なす角
	double nas4 = acos((inner4) / (pdlpdr.length() * dlb.length()));

	if (((dlb.length() * sin(nas4)) < BALL_SIZE))
	{
		if (_ball.getPos().x >= downleft.x && _ball.getPos().x <= downright.x) {
			_ball.vy *= -1;
			isHit = 1;
		}
	}

	// 角のあたり判定
	if ((_ball.getPos() - upleft).length() < BALL_SIZE) {
		_ball.vy *= -1;
		isHit = 1;
	}
	if ((_ball.getPos() - upright).length() < BALL_SIZE) {
		_ball.vy *= -1;
		isHit = 1;
	}
	if ((_ball.getPos() - downleft).length() < BALL_SIZE) {
		_ball.vy *= -1;
		isHit = 1;
	}
	if ((_ball.getPos() - downright).length() < BALL_SIZE) {
		_ball.vy *= -1;
		isHit = 1;
	}

	return isHit;
}
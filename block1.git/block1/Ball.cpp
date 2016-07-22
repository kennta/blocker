#include "Ball.h"

#include "SceneGame.h"

#include <math.h>
#include "GameDefine.h"
#include "GameMain.h"

Ball::Ball(SceneBase& scene)
    : Character()
    , _scene(scene)
{
	vy = -3.0;
	vx = 3.0;
}

Ball::~Ball()
{
}

void Ball::onTick()
{
	Input& in = GameMain::getInstance().getInput();
	if (in.isDown(Input::KEY_UP)) _isShot++;

	if (_isShot > 0) {
		if (_pos.x - BALL_SIZE <= 0 || _pos.x + BALL_SIZE >= DWIDTH) {
			vx *= -1;
		}
		if (_pos.y - BALL_SIZE <= 0 || _pos.y + BALL_SIZE >= DHEIGHT) {
			vy *= -1;
		}
		_pos.x += vx;
		_pos.y += vy;
	}
	else {
		if (in.isDown(Input::KEY_LEFT)) _pos.x = (_pos.x - PLAYER_VELOCITY > BALL_SIZE) ? _pos.x - PLAYER_VELOCITY : BALL_SIZE + 1;
		if (in.isDown(Input::KEY_RIGHT)) _pos.x = (_pos.x + PLAYER_VELOCITY < DWIDTH - BALL_SIZE) ? _pos.x + PLAYER_VELOCITY : DWIDTH - BALL_SIZE - 1;
	}
}

void Ball::onDraw(Graphics& g)
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255,0,0));
    g.setPen(pen);
	g.drawEllipse(_pos.x - BALL_SIZE, _pos.y - BALL_SIZE, _pos.x + BALL_SIZE, _pos.y + BALL_SIZE);
    g.setPen(NULL);
    DeleteObject(pen);

}

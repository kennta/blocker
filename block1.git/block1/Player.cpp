#include "Player.h"

#include "GameDefine.h"
#include "GameMain.h"

Player::Player(SceneBase& scene)
    : Character()
    , _scene(scene)
{
	_width  = PLAYER_WIDTH;
	_height = PLAYER_HEIGHT;
}

Player::~Player()
{
}

void Player::onTick()
{
    // Ž©ƒLƒƒƒ‰ˆÚ“®
    Input& in = GameMain::getInstance().getInput();
	if (in.isDown(Input::KEY_LEFT)) _pos.x = (_pos.x - PLAYER_VELOCITY > _width) ? _pos.x - PLAYER_VELOCITY : _width + 1;
	if (in.isDown(Input::KEY_RIGHT)) _pos.x = (_pos.x + PLAYER_VELOCITY < DWIDTH - _width) ? _pos.x + PLAYER_VELOCITY : DWIDTH - _width - 1;
	//if (in.isDown(Input::KEY_UP)) _pos.y = (_pos.y - PLAYER_VELOCITY > _height) ? _pos.y - PLAYER_VELOCITY : _height + 1;
	//if (in.isDown(Input::KEY_DOWN)) _pos.y = (_pos.y + PLAYER_VELOCITY < DHEIGHT - _height) ? _pos.y + PLAYER_VELOCITY : DHEIGHT - _height - 1;
}

void Player::onDraw(Graphics& g)
{
    HPEN pen  = CreatePen(PS_SOLID, 2, RGB(0,255,0));
    g.setPen(pen);
	g.drawRectangle(_pos.x - _width, _pos.y - _height, _pos.x + _width, _pos.y + _height);
    g.setPen(NULL);
    DeleteObject(pen);
}

double Player::getWidth()
{
	return _width;
}

double Player::getHeight()
{
	return _height;
}
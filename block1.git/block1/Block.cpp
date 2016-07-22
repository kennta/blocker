#include "Block.h"

#include "SceneGame.h"

#include <math.h>
#include "GameDefine.h"

Block::Block(SceneBase& scene)
	: Character()
	, _scene(scene)
{
	_width = BLOCK_WIDTH;
	_height = BLOCK_HEIGHT;
	_hp = 1;
}

Block::~Block()
{
}

void Block::onTick()
{
}

void Block::onDraw(Graphics& g)
{
	int red = 255;
	int green = 255;
	int blue = 255;

		HPEN pen = CreatePen(PS_SOLID, 2, RGB(red, green, blue));
		g.setPen(pen);
		g.drawRectangle(_pos.x - _width, _pos.y - _height, _pos.x + _width, _pos.y + _height);
		g.setPen(NULL);
		DeleteObject(pen);	
}

double Block::getWidth()
{
	return _width;
}

double Block::getHeight()
{
	return _height;
}

void Block::addDamage(int damage)
{
	_hp -= 1;
	if (_hp <= 0) {
	}
}

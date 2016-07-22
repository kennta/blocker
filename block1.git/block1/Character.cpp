#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::setPos(const Vector2Df& pos)
{
    _pos = pos;
}

Vector2Df Character::getPos() const
{
    return _pos;
}

double Character::getWidth()
{
	return _width;
}

double Character::getHeight()
{
	return _height;
}
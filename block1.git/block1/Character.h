#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Graphics.h"
#include "Vector2D.h"

class Character
{
public:
    Character();
    virtual ~Character();
    virtual void onTick() = 0;
    virtual void onDraw(Graphics& g) = 0;

    virtual void setPos(const Vector2Df& pos);
    virtual Vector2Df getPos() const;
	virtual double getWidth();
	virtual double getHeight();

protected:
    Vector2Df _pos;

private:
	double _width;
	double _height;
};

#endif // _CHARACTER_H_

#include "Input.h"

#include <windows.h>
#include <string.h>

Input::Input()
{
    memset(_flags, 0, sizeof(_flags));
}

Input::~Input()
{
}

void Input::reset()
{
    _flags[TYPE_DOWN] = _flags[TYPE_UP] = 0;
}

void Input::reflectKeyUp()
{
    _flags[TYPE_DOWN] &= ~_flags[TYPE_UP];
    _flags[TYPE_REP] = _flags[TYPE_UP] = 0;
}

void Input::keyDown(const unsigned int dependencyKey)
{
    int key = _dependencyKey2key(dependencyKey);
    if (key) _flags[TYPE_DOWN] |= key;
}

void Input::keyRepeat(const unsigned int dependencyKey)
{
    int key = _dependencyKey2key(dependencyKey);
    if (key) _flags[TYPE_REP] |= key;
}

void Input::keyUp(const unsigned int dependencyKey)
{
    int key = _dependencyKey2key(dependencyKey);
    if (key) _flags[TYPE_UP] |= key;
}

bool Input::isDown(const unsigned int key) const
{
    return _flags[TYPE_DOWN] & key;
}

bool Input::isRepeat(const unsigned int key) const
{
    return _flags[TYPE_REP] & key;
}

bool Input::isUp(const unsigned int key) const
{
    return _flags[TYPE_UP] & key;
}

unsigned int Input::_dependencyKey2key(unsigned int dependencyKey)
{
    switch (dependencyKey) {
    case VK_LEFT : return KEY_LEFT;
    case VK_UP   : return KEY_UP;
    case VK_RIGHT: return KEY_RIGHT;
    case VK_DOWN : return KEY_DOWN;
    default: return 0;
    }
}

#include "Task.h"

Task::Task()
    : _state(STATE_CREATED)
    , _priority(PRIORITY_BOTTOM)
    , _draw_priority(PRIORITY_BOTTOM)
{
}

Task::~Task()
{
}

void Task::onResume()
{
}

void Task::onDraw(Graphics& g)
{
}

void Task::markOffInit()
{
    _state = (_state == STATE_CREATED) ? STATE_INITIALIZED : _state;
}

void Task::kill()
{
    _state = STATE_KILLED;
}

void Task::suspend()
{
    if (_state == STATE_INITIALIZED) _state = STATE_SUSPENDED;
}

void Task::resume()
{
    if (_state == STATE_SUSPENDED) _state = STATE_INITIALIZED;
}

void Task::Priority(int priority)
{
    _priority = priority;
}

int Task::Priority() const
{
    return _priority;
}

void Task::DrawPriority(int priority)
{
    _draw_priority = priority;
}

int Task::DrawPriority() const
{
    return _draw_priority;
}

bool Task::isRunning() const
{
    return (_state == STATE_INITIALIZED);
}

bool Task::isInitialized() const
{
    return (_state >= STATE_INITIALIZED);
}

bool Task::isDead() const
{
    return (_state == STATE_KILLED);
}

bool Task::operator==(Task& rhs) const
{
    return this == &rhs;
}

#ifndef _TASK_H_
#define _TASK_H_

#include "Graphics.h"

class TaskManager;

class Task
{
public:
    enum _STATE_ : unsigned int
    {
        STATE_CREATED     = 0,
        STATE_INITIALIZED    ,
        STATE_SUSPENDED      ,
        STATE_KILLED
    };

    enum _PRIORITY_ : int
    {
        PRIORITY_TOP        = 0,
        PRIORITY_BOTTOM     = 0x7fffffff,
        PRIORITY_APP_TOP    = 0x00000fff,
        PRIORITY_APP_BOTTOM = 0x00ffffff,
    };

    Task();
    virtual ~Task();

    virtual bool onInit() = 0;
    virtual void onRelease() = 0;
    virtual void onResume();
    virtual void onTick() = 0;
    virtual void onDraw(Graphics& g);
    virtual void markOffInit();
    virtual void kill();
    virtual void suspend();
    virtual void resume();

    virtual void Priority(int priority);
    virtual int  Priority() const;
    virtual void DrawPriority(int priority);
    virtual int  DrawPriority() const;
    virtual bool isRunning() const;
    virtual bool isInitialized() const;
    virtual bool isDead() const;

    virtual bool operator==(Task& rhs) const;

private:
    unsigned int _state;         // èÛë‘
    int          _priority;      // èàóùóDêÊìx
    int          _draw_priority; // ï`âÊÇÃóDêÊìx

};

#endif // _TASK_H_

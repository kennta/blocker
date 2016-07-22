#ifndef _TASKMANAGER_H_
#define _TASKMANAGER_H_

#include <map>
#include "Task.h"

class TaskManager
{
public:
    static TaskManager& getInstance();
    virtual bool addTask(Task* task, int priority);
    virtual bool addDrawTask(Task* task, int priority);
    virtual bool isTerminated() const;
    virtual void killAll(int begin, int end);
    virtual void killAll(int priority);
    virtual void onTick();
    virtual void drawCancel(Task* task);
    virtual void onDraw(Graphics& g);
    virtual void onResume();

private:
    typedef std::multimap<int, Task*> TaskList;

    TaskManager();
    virtual ~TaskManager();
    virtual void kill();

    TaskList proc_tasks_;
    TaskList draw_tasks_;
    bool     terminated_;

};

#endif // _TASKMANAGER_H_

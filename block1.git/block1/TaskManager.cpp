#include "TaskManager.h"

TaskManager::TaskManager()
    : terminated_(false)
{
}

TaskManager::~TaskManager()
{
}

TaskManager& TaskManager::getInstance()
{
    static TaskManager this_;
    return this_;
}

bool TaskManager::addTask(Task* task, int priority)
{
    if (!task) return false;

    // I—¹ˆ—’†
    if (isTerminated())
    {
        task->kill();
        task->onRelease();
        return false;
    }

    // ƒ^ƒXƒN‚Ì‰Šú‰»
    if (!task->isInitialized())
    {
        if (!task->onInit())
        {
            task->kill();
            task->onRelease();
            return false;
        }
        task->markOffInit();
    }

    // —Dæ“x‚ðÝ’è‚·‚é
    task->Priority(priority);

    // —Dæ“x‚ðŽQÆ‚µ‚ÄƒŠƒXƒg‚É‘}“ü‚·‚é
    proc_tasks_.insert(TaskList::value_type(priority, task));

    return true;
}

bool TaskManager::addDrawTask(Task* task, int priority)
{
    if (!task) return false;

    // I—¹ˆ—’†
    if (isTerminated()) return false;

    // —Dæ“x‚ðÝ’è‚·‚é
    task->DrawPriority(priority);

    // —Dæ“x‚ðŽQÆ‚µ‚ÄƒŠƒXƒg‚É‘}“ü‚·‚é
    for (auto it : proc_tasks_)
    {
        // “ñd“o˜^‚ð–hŽ~‚·‚é
        if (it.second == task)
        {
            return true;
        }
    }
    draw_tasks_.insert(TaskList::value_type(priority, task));
    return true;
}

bool TaskManager::isTerminated() const
{
    return terminated_;
}

void TaskManager::killAll(int begin, int end)
{
    for (TaskList::iterator it = proc_tasks_.lower_bound(begin); it != proc_tasks_.upper_bound(end); ++it)
    {
        (it->second)->kill();
    }
}

void TaskManager::killAll(int priority)
{
    killAll(priority, priority);
}

void TaskManager::onTick()
{
    for (auto it : proc_tasks_)
    {
        Task* task = it.second;
        if (task->isRunning()) task->onTick();
    }

    kill();
}

void TaskManager::kill()
{
    for (TaskList::iterator it = proc_tasks_.begin(); it != proc_tasks_.end();)
    {
        Task* task = it->second;
        if (task->isDead())
        {
            task->onRelease();
            drawCancel(task);
            proc_tasks_.erase(it++);
            delete task;
        }
        else
        {
            ++it;
        }
    }
}

void TaskManager::drawCancel(Task* task)
{
    for (TaskList::iterator it = draw_tasks_.begin(); it != draw_tasks_.end(); ++it)
    {
        if (it->second == task)
        {
            draw_tasks_.erase(it);
            return;
        }
    }
}

void TaskManager::onDraw(Graphics& g)
{
    for (auto it : draw_tasks_)
    {
        if ((it.second)->isRunning()) (it.second)->onDraw(g);
    }
    //draw_tasks_.clear();
}

void TaskManager::onResume()
{
    for (auto it : proc_tasks_)
    {
        (it.second)->onResume();
    }
}

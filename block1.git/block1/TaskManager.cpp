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

    // 終了処理中
    if (isTerminated())
    {
        task->kill();
        task->onRelease();
        return false;
    }

    // タスクの初期化
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

    // 優先度を設定する
    task->Priority(priority);

    // 優先度を参照してリストに挿入する
    proc_tasks_.insert(TaskList::value_type(priority, task));

    return true;
}

bool TaskManager::addDrawTask(Task* task, int priority)
{
    if (!task) return false;

    // 終了処理中
    if (isTerminated()) return false;

    // 優先度を設定する
    task->DrawPriority(priority);

    // 優先度を参照してリストに挿入する
    for (auto it : proc_tasks_)
    {
        // 二重登録を防止する
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

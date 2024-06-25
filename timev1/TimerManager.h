#ifndef _TIMER_MANAGER_H_
#define _TIMER_MANAGER_H_

#include "Timer.h"
#include <stdint.h>
#include <list>

struct TimerCompare
{
    bool operator()(const Timer* lhs, const Timer* rhs) const
    {
        return lhs->getExpiredTime() < rhs->getExpiredTime();
    }
};

void defaultTimerCallback()
{

}

class TimerManager
{
public:
    TimerManager() = default;
    ~TimerManager() = default;

    //重复次数 触发间隔 回调函数
    int64_t addTimer(int32_t repeatCount, int64_t interval, const TimerCallback& callback);
    //移除定时器
    bool removeTimer(int64_t timerId);
    //检测定时器是否到期，到期触发回调函数
    void checkAndHandleTimers();


private:
    std::list<Timer*> m_listTimers;
};


#endif // !_TIMER_MANAGER_H_
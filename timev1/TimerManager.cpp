#include "TimerManager.h"

int64_t TimerManager::addTimer(int32_t repeatCount, int64_t interval, const TimerCallback& callback)
{
    Timer* pTimer = new Timer(repeatCount, interval, callback);
    m_listTimers.push_back(pTimer);
    
    //按照过期时间从小到大排序
    m_listTimers.sort(TimerCompare());
    
    return pTimer->getId();
}

bool TimerManager::removeTimer(int64_t timerId)
{
    for (auto iter = m_listTimers.begin(); iter != m_listTimers.end(); ++iter)
    {
        if ((*iter)->getId() == timerId)
        {
            m_listTimers.erase(iter);
            return true;
        }
    }
    
    return false;
}

void TimerManager::checkAndHandleTimers()
{
    //遍历过程中是否调整了部分定时器的过期时间
    bool adjusted = false;
    Timer* deleteTimer;
    for(auto iter = m_listTimers.begin(); iter != m_listTimers.end();)
    {
        if ((*iter)->IsExpired())
        {
            (*iter)->run();

            if ((*iter)->getRepeatedTimes() == 0)
            {
                //定时机器不需要再触发，从集合中移除该对象
                deleteTimer = *iter;
                iter = m_listTimers.erase(iter);
                delete deleteTimer;
                continue;
            }
            else
            {
                ++iter;
                //标记下集合中有定时器调整了过期时间
                adjusted = true;
            }
            
        }
        else
        {
            //找到大于当前系统时间的定时器对象就不需要继续往下检查了，退出循环
            break;
        }
    }

    //如果集合中有定时器调整了过期时间，则需要重新调整集合中定时器的过期时间
    if (adjusted)
    {
        m_listTimers.sort(TimerCompare());
    }
}
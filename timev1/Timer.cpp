#include "Timer.h"
#include <time.h>

std::atomic<int> Timer::s_initialId = 0;

Timer::Timer(int32_t repeatedTimes, int64_t interval, const TimerCallback& timerCallback)
{
    m_repeatedTimes = repeatedTimes;
    m_interval = interval;
    m_callback = timerCallback;
    //当前时间 + 间隔时间 = 下一次到期时间
    m_expiredTime = (int64_t)time(nullptr) + interval;
    //生成唯一id
    m_id = ++s_initialId;
}

const bool Timer::IsExpired()
{
    int64_t now = (int64_t)time(nullptr);
    return now >= m_expiredTime;
}

void Timer::run()
{
    m_callback();

    if (m_repeatedTimes >= 1)
    {
        m_repeatedTimes --;
    }

    m_expiredTime += m_interval;
}
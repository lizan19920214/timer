#ifndef _TIME_H_
#define _TIME_H_

#include <functional>
#include <atomic>

typedef std::function<void()> TimerCallback;

class Timer
{
public:
    /**
     * repeatedTimes 定时器重复次数 -1表示一直重复
     * interval 定时器触发时间间隔 单位毫秒
     * timerCallback 定时器触发后的回调函数
    */
    Timer(int32_t repeatedTimes, int64_t interval, const TimerCallback& timerCallback);
    ~Timer();

public:
    int64_t getId() const {return m_id;}
    int64_t getExpiredTime() const {return m_expiredTime;}
    int32_t getRepeatedTimes() const {return m_repeatedTimes;}

    void run();
    const bool IsExpired();

private:
    //定时器id，唯一标识一个定时器
    int64_t     m_id;
    //定时器下一次到期时间
    time_t      m_expiredTime;
    //定时器重复触发的次数
    int32_t     m_repeatedTimes;
    //定时器触发后的回调函数
    TimerCallback m_callback;
    //触发时间间隔
    int64_t     m_interval;
    //定时器id基准值
    static std::atomic<int> s_initialId;

};



#endif //!_TIME_H_
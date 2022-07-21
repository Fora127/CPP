#pragma once

#include <unistd.h>
#include <iostream>
#include <mutex>
#include <thread>

#include "Timer.h"

struct InitParams
{
    double m_dBA;
    double m_dRMV;
    double m_dRDV;
};

class Controller
{
private:
    InitParams m_params;
    Timer m_timer;
    Timer m_timerInterval;
    Timer m_timerShiftBA;

    double m_curBA;
    std::mutex m_mtxBA;

    bool m_bAlarm;
    std::mutex m_mtxAlarm;

    bool m_bStop;
    std::mutex m_mtxStop;

    double m_curY;
    std::mutex m_mtxCurY;

    std::thread* m_pThread;

public:
    Controller();
    ~Controller();
    double getCurrentY();
    bool getAlarmStatus();
    double getCurrentBA();

    void detectAlarm();

    void SetControlParams( const InitParams params );
    void SetCurrentValue( const double curY );

    void startThread();
    void stopThread( );

    bool isStopped();
};

///
inline void Controller::SetControlParams( const InitParams params )
{
    m_params = params;
}

inline void Controller::SetCurrentValue( const double curY)
{
    std::lock_guard<std::mutex> l( m_mtxCurY );
    m_curY = curY;
}

inline bool Controller::isStopped()
{
    std::lock_guard<std::mutex> l( m_mtxStop );
    return m_bStop;
}

inline double Controller::getCurrentY()
{
    std::lock_guard<std::mutex> l( m_mtxCurY );
    return m_curY;
}

inline bool Controller::getAlarmStatus()
{
    std::lock_guard<std::mutex> l( m_mtxAlarm);
    return m_bAlarm;
}

inline double Controller::getCurrentBA()
{
    std::lock_guard<std::mutex> l(m_mtxBA);
    return m_curBA;
}



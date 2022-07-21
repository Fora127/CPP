#include "Controller.h"

Controller::Controller( )
{
    m_bStop = false;
    m_bAlarm = false;
    m_pThread = nullptr;
}

Controller::~Controller()
{
    m_timer.stop();
    m_timerInterval.stop();
    m_timerShiftBA.stop();
    stopThread();
}

void Controller::startThread()
{
    if( m_pThread )
        return;

    {
        std::lock_guard<std::mutex> l( m_mtxStop );
        m_bStop = false;
    }

    m_pThread = new std::thread( &Controller::detectAlarm, this );
}

void Controller::stopThread(  )
{
    if (!m_pThread)
        return;

    m_mtxStop.lock();
    m_bStop = true;
    m_mtxStop.unlock();

    m_pThread->join();

    delete m_pThread;
    m_pThread = nullptr;
}

void Controller::detectAlarm()
{
    double m_dY = 0;
    bool bTimerStarted = false;
    bool bExtraTimerStarted  = false;
    m_curBA = m_params.m_dBA;

    m_timerInterval.start();

    while( !isStopped() )
    {
        m_mtxAlarm.lock();

        m_dY = getCurrentY();

        // start timer alarm
        if ( !m_bAlarm &&
             m_dY >= m_params.m_dBA && !bTimerStarted )
        {
            m_timer.start();
            bTimerStarted = 1;
        }

        // alarm conditions
        if( !m_bAlarm &&
             bTimerStarted &&
             m_dY >= m_params.m_dBA &&
             ( m_timer.elapsedSeconds()) > m_params.m_dRDV )
        {
            m_bAlarm = true;
            std::cout << "ALARM STATUS: " << m_bAlarm << std::endl;
            m_timerInterval.stop();
            m_timerInterval.start();
        }

        // moove BA condidtions
        // if Y more than BA start timer + RMV move alarm border
        if( !bExtraTimerStarted &&
             m_dY > (m_params.m_dBA + m_params.m_dRMV) )
        {
            bExtraTimerStarted = true;
            m_timerShiftBA.start();
        }

        // if Y more than BA during RMV moove alarm border
        if( bExtraTimerStarted &&
            m_dY > (m_params.m_dBA + m_params.m_dRMV) &&
            ( m_timer.elapsedSeconds()) > m_params.m_dRDV )
        {
           bExtraTimerStarted = false;
           m_curBA = m_params.m_dBA + m_params.m_dRMV;
           m_timerShiftBA.stop();
           m_timer.stop();
        }

        // reset timer alarm
        if( !m_bAlarm &&
             bTimerStarted &&
             m_dY < m_params.m_dBA )
        {
            m_timer.stop();
            m_timerShiftBA.stop();
            bTimerStarted = false;
            bExtraTimerStarted = false;
        }

        //start timer for reset alarm
        if( m_bAlarm &&
            !bTimerStarted &&
             m_dY < (m_curBA - m_params.m_dRMV) )
        {
            m_timer.start();
            bTimerStarted = 1;
        }

        // reset alarm conditions
        if( m_bAlarm &&
            bTimerStarted &&
            m_dY < (m_curBA - m_params.m_dRMV) &&
            ( m_timer.elapsedSeconds()) > m_params.m_dRDV )
        {
            m_bAlarm = false;
            m_curBA = m_params.m_dBA;
            std::cout << "ALARM STATUS: " << m_bAlarm << std::endl;
            m_timerInterval.stop();
            m_timerInterval.start();
        }

        // reset timer alarm
        if( m_bAlarm &&
            bTimerStarted &&
            m_dY >= (m_curBA - m_params.m_dRMV) )
        {
            m_timer.stop();
            bTimerStarted = 0;
        }

        m_mtxAlarm.unlock();

        usleep(50);
    }
}


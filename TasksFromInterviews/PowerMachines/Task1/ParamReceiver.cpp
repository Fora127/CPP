#include "ParamReceiver.h"

#include <iostream>

ParamReceiver::ParamReceiver()
{    
    m_pController = nullptr;
}

ParamReceiver::ParamReceiver(Controller* controller)
{
    Init();
    m_pController = controller;
    m_pController->SetControlParams(m_params);

//    double d = 12.0;
//    setCurrentY(d);

    m_pController->startThread();

}

ParamReceiver::~ParamReceiver()
{
    m_pController = nullptr;
}

void ParamReceiver::Init1()
{
    m_params.m_dBA = 10;
    m_params.m_dRDV = 5; //sec
    m_params.m_dRMV = 1;
}

void ParamReceiver::Init()
{
    std::cout << "DATA ANALIZER " << std::endl;
    std::cout << "/  First input control params" << std::endl;
    std::cout << "/  Then input current value" << std::endl;
    std::cout << "/  Alarm signal will be printed every 30 seconds or if changed" << std::endl<< std::endl;

    std::cout << "Input control params" << std::endl;
    std::cout << "BA - Alarm Border: " ;
    m_params.m_dBA = checkInputValue( "" );

    bool isRMV = 1;
    while( isRMV )
    {
        std::cout << "RMV - Hysteresis value: " ;
        m_params.m_dRMV = checkInputValue( "" );
        if(m_params.m_dRMV > m_params.m_dBA)
        {
            std::cout << "RMV could't be more than BA. Please try again " << std::endl<< std::endl;
        }
        else
          isRMV = 0;
    }

    bool isRDV = 1;
    while( isRDV )
    {
        std::cout << "RDV - Control period of time, sec: " ;
        m_params.m_dRDV = checkInputValue( "" );

        if(m_params.m_dRDV < 0)
        {
            std::cout << "RDV could't be less than 0. Please try again " << std::endl<< std::endl;
        }
        else
          isRDV = 0;
    }

    std::cout << std::endl<< std::endl;
    std::cout << "Hereinafter input Y: " << std::endl;
}

double ParamReceiver::checkInputValue( const std::string str )
{
    double num;
    if( !str.empty() )
        std::cout << "" <<str <<" " ;

    while ( !(std::cin >> num) ) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' ); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    return num;
}

InitParams ParamReceiver::getSettings()
{
    return m_params;
}

void ParamReceiver::setCurrentY( double &y )
{
    if( m_pController )
        m_pController->SetCurrentValue( y );

}

double ParamReceiver::getCurrentY()
{
    return m_pController ? m_pController->getCurrentY() : 0;
}


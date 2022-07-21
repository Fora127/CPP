#pragma once

#include <mutex>

#include "Controller.h"

class ParamReceiver
{
private:
    InitParams m_params;
    bool m_bAlarmExtraY;
    Controller* m_pController;

public:
    ParamReceiver();
    ParamReceiver(Controller* contr);
    ~ParamReceiver();

private:
    void Init();
    void Init1();

public:
    InitParams getSettings();
    double checkInputValue( const std::string str );
    double getCurrentY();
    void setCurrentY( double& );
};


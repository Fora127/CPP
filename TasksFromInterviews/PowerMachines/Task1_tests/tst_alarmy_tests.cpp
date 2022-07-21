#include <QtTest>
#include <QThread>


// add necessary includes here

#include "../Task1/Controller.h"

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(5);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

class AlarmY_Tests : public QObject
{
    Q_OBJECT

private:
    Controller* m_pController;
    InitParams m_InitParams;

    double t_moreThanTarg;
    double t_lessThanTarg;

public:
    AlarmY_Tests();
    ~AlarmY_Tests();

private slots:
    void test_case1();
    void test_case2();
    void test_case3();
    void test_case4();
    void test_case5();
    void test_case6();
    void test_case7();
    void test_case8();
    void test_case9();
    void test_case10();
    virtual void initTestCase();
    virtual void init();
    virtual void cleanup();
};

AlarmY_Tests::AlarmY_Tests()
{

}

AlarmY_Tests::~AlarmY_Tests()
{

}

void AlarmY_Tests::initTestCase()
{
    m_InitParams.m_dBA = 10.0;
    m_InitParams.m_dRDV = 1.0;          // time_tagr
    m_InitParams.m_dRMV = 1.0;          // H

    t_moreThanTarg = m_InitParams.m_dRDV + 0.1;
    t_lessThanTarg = m_InitParams.m_dRDV - 0.1;
}

void AlarmY_Tests::init()
{
    m_pController = new Controller();
    m_pController->SetControlParams(m_InitParams);
    m_pController->startThread();
}

void AlarmY_Tests::cleanup()
{
    m_pController->stopThread( );
    delete m_pController;
    m_pController = nullptr;
}

void AlarmY_Tests::test_case1()
{
    /*
     * текущее значение Y < BA
     */
    m_pController->SetCurrentValue(m_InitParams.m_dBA - 1);
    QThread::msleep(t_moreThanTarg*1000);
    QVERIFY( m_pController->getAlarmStatus() == 0 );


}

void AlarmY_Tests::test_case2()
{
    /*
     * текущее значение Y > BA ( t > RDV )
     */

    m_pController->SetCurrentValue(m_InitParams.m_dBA + 2);
    QThread::msleep(t_moreThanTarg*1000);
    QVERIFY( m_pController->getAlarmStatus() == 1 );
}

void AlarmY_Tests::test_case3()
{
    /*
     * текущее значение Y > BA ( t < RDV )
     */
    m_pController->SetCurrentValue(m_InitParams.m_dBA + 1);
    QThread::msleep(t_lessThanTarg*1000);
    QVERIFY( m_pController->getAlarmStatus() == 0 );

}

void AlarmY_Tests::test_case4()
{
    /*
     * текущее значение Y > BA ( t > RDV ), затем Y < BA-RMV ( t < RDV )
     */
    m_pController->SetCurrentValue(m_InitParams.m_dBA + 1);
    QThread::msleep(t_moreThanTarg*1000);
    m_pController->SetCurrentValue(m_InitParams.m_dBA - m_InitParams.m_dRMV - 1);
    QThread::msleep(t_lessThanTarg*1000);
    QVERIFY( m_pController->getAlarmStatus() == 1 );
}

void AlarmY_Tests::test_case5()
{
    /*
     * текущее значение Y > BA ( t > RDV ), затем Y < BA-RMV ( t > RDV )
     */
    m_pController->SetCurrentValue(m_InitParams.m_dBA + 1);
    QThread::msleep(t_moreThanTarg*1000);
    m_pController->SetCurrentValue(m_InitParams.m_dBA - m_InitParams.m_dRMV - 1);
    QThread::msleep(t_moreThanTarg*1000);
    QVERIFY( m_pController->getAlarmStatus() == 0 );
}

void AlarmY_Tests::test_case6()
{
    /*
     * текущее значение Y > BA+RMV  ( t > RDV)
     */
    m_pController->SetCurrentValue(m_InitParams.m_dBA + m_InitParams.m_dRMV + 1);
    QThread::msleep(t_moreThanTarg*1000);
    QVERIFY( m_pController->getAlarmStatus() == 1 &&
             m_pController->getCurrentBA() == (m_InitParams.m_dBA + m_InitParams.m_dRMV) );
}

void AlarmY_Tests::test_case7()
{
    /*
     * текущее значение Y > BA+RMV ( t > RDV ), затем  BA < Y < BA+RMV ( t > RDV )
     */
    m_pController->SetCurrentValue(m_InitParams.m_dBA + m_InitParams.m_dRMV + 1);
    QThread::msleep(t_moreThanTarg*1000);
    m_pController->SetCurrentValue(m_InitParams.m_dBA + 1);
    QThread::msleep(t_moreThanTarg*1000);
    QVERIFY( m_pController->getAlarmStatus() == 1 &&
             m_pController->getCurrentBA() > (m_InitParams.m_dBA + m_InitParams.m_dRMV - 0.1) );
}

void AlarmY_Tests::test_case8()
{
    /*
     * текущее значение Y > BA+RMV ( t < RDV )
     */
    m_pController->SetCurrentValue(m_InitParams.m_dBA + m_InitParams.m_dRMV + 1);
    QThread::msleep(t_lessThanTarg*1000);
    QVERIFY( m_pController->getAlarmStatus() == 0 &&
             m_pController->getCurrentBA() == m_InitParams.m_dBA );
}

void AlarmY_Tests::test_case9()
{
    /*
     * текущее значение Y > BA+RMV ( t < RDV ), затем BA < Y < BA+RMV  ( t > RDV )
     */
    m_pController->SetCurrentValue(m_InitParams.m_dBA + m_InitParams.m_dRMV + 1);
    QThread::msleep(t_lessThanTarg*1000);
    m_pController->SetCurrentValue(m_InitParams.m_dBA + m_InitParams.m_dRMV - 1);
    QThread::msleep(t_moreThanTarg*1000);
    QVERIFY( m_pController->getAlarmStatus() == 1 &&
             m_pController->getCurrentBA() < m_InitParams.m_dBA + 0.01);
}

void AlarmY_Tests::test_case10()
{
    /*
     * текущее значение Y > BA+RMV ( t > RDV ), затем BA-RMV < Y < BA  ( t > RDV )
     */
    m_pController->SetCurrentValue(m_InitParams.m_dBA + m_InitParams.m_dRMV + 1);
    QThread::msleep(t_moreThanTarg*1000);
    m_pController->SetCurrentValue(m_InitParams.m_dBA  - 1);
    QThread::msleep(t_moreThanTarg*1000);
    QVERIFY( m_pController->getAlarmStatus() == 0 );
}

QTEST_APPLESS_MAIN(AlarmY_Tests)

#include "tst_alarmy_tests.moc"





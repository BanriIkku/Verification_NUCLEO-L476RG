
#include "_PLATFORM_main.h"
#define TRACE_GROUP   "plat"


/* ///////////////////////////////////////////////////// */
/*! @brief 要約説明.
 *         要約説明の続き.
 *
 *  詳細説明がここから始まる.
 */
/* ///////////////////////////////////////////////////// */
MBED_WEAK int _USR_Repetition(void)
{
    tr_info("%s_%s_%s : %s",__FILE__,__FUNCTION__, __LINE__, "Repetition" );
    return 0;
}

/* ///////////////////////////////////////////////////// */
/*! @brief 要約説明.
 *         要約説明の続き.
 *
 *  詳細説明がここから始まる.
 */
/* ///////////////////////////////////////////////////// */
MBED_WEAK int _USR_Initialize(void)
{
    tr_info("%s_%s_%s : %s",__FILE__,__FUNCTION__, __LINE__, "Initialize" );
    return 0;
}

/* ///////////////////////////////////////////////////// */
/*! @brief 要約説明.
 *         要約説明の続き.
 *
 *  詳細説明がここから始まる.
 */
/* ///////////////////////////////////////////////////// */
MBED_WEAK int _USR_Terminate(void)
{
    tr_info("%s_%s_%s : %s",__FILE__,__FUNCTION__, __LINE__, "Terminate" );
    return 0;
}

/* ///////////////////////////////////////////////////// */
/*! @brief 要約説明.
 *         要約説明の続き.
 *
 *  詳細説明がここから始まる.
 */
/* ///////////////////////////////////////////////////// */
int _PLATFORM_Repetition(void)
{
    tr_info("%s_%s_%s : %s",__FILE__,__FUNCTION__, __LINE__, "Repetition" );
    return _USR_Repetition();
}

/* ///////////////////////////////////////////////////// */
/*! @brief 要約説明.
 *         要約説明の続き.
 *
 *  詳細説明がここから始まる.
 */
/* ///////////////////////////////////////////////////// */
int _PLATFORM_Initialize(void)
{
    tr_info("%s_%s_%s : %s",__FILE__,__FUNCTION__, __LINE__, "Initialize" );
    return _USR_Initialize();
}


/* ///////////////////////////////////////////////////// */
/*! @brief 要約説明.
 *         要約説明の続き.
 *
 *  詳細説明がここから始まる.
 */
/* ///////////////////////////////////////////////////// */
int _PLATFORM_Terminate(void)
{
    tr_info("%s_%s_%s : %s",__FILE__,__FUNCTION__, __LINE__, "Terminate" );

    return _USR_Terminate();
}

DigitalOut usr_led(LED1);
InterruptIn user_interruptin(USER_BUTTON);
volatile bool flag_continued=true;

void _func_continued() {
    flag_continued=false;
}

/* ///////////////////////////////////////////////////// */
/*! @brief 要約説明.
 *         要約説明の続き.
 *
 *  詳細説明がここから始まる.
 */
/* ///////////////////////////////////////////////////// */
int _PLATFORM_main(void)
{
    int ret_value=0;
    usr_led=1;
    ret_value += _PLATFORM_Initialize();

    user_interruptin.rise(&_func_continued);  // attach the address of the flip function to the rising edge
    LowPowerTimer lpt;
    lpt.start();
    do
    {
        if(1<= lpt.read())
        {
            usr_led=!usr_led;
            lpt.reset();
        }
        _PLATFORM_Repetition();
        ThisThread::sleep_for(MBED_CONF_MYPLATFORM_INTERVAL_MILLISECOND);
    } while(true==flag_continued);
    lpt.stop();

    usr_led=1;
    ret_value += _PLATFORM_Terminate();
    usr_led=0;
    return ret_value;
}


#undef TRACE_GROUP

#include "_PLATFORM_main.h"
#include "_PLATFORM_Logger.h"
#include "mbed_trace.h"

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
    tr_info("%s[%d] %s: %s", __FILE__, __LINE__, __FUNCTION__, "Initialize" );
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
    tr_info("%s[%d] %s: %s", __FILE__, __LINE__, __FUNCTION__, "Terminate" );
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
    // tr_info("%s_%s_%d: %s",__FILE__,__FUNCTION__, __LINE__, "Repetition" );
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
    tr_info("%s[%d] %s: %s", __FILE__, __LINE__, __FUNCTION__, "Initialize" );
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
    tr_info("%s[%d] %s: %s", __FILE__, __LINE__, __FUNCTION__, "Terminate" );

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

    mbed_trace_print_function_set(_Logger_output);
    mbed_trace_mutex_wait_function_set(_Logger_mutex_wait_function);
    mbed_trace_mutex_release_function_set(_Logger_mutex_release_function);


    mbed_trace_init();

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
            lpt.reset();
        }
        _PLATFORM_Repetition();
        ThisThread::sleep_for(MBED_CONF_MYPLATFORM_INTERVAL_MILLISECOND);
    } while(true==flag_continued);
    lpt.stop();

    usr_led=1;
    ret_value += _PLATFORM_Terminate();
    usr_led=0;

    mbed_trace_free();

    return ret_value;
}


#undef TRACE_GROUP
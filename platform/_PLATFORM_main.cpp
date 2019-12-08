
#include "_PLATFORM_main.h"
#include "mbed_trace.h"

#define TRACE_GROUP   "plat"

Mutex forPC_mutex;

UARTSerial forPC_serial(STDIO_UART_TX, STDIO_UART_RX,MBED_CONF_PLATFORM_STDIO_BAUD_RATE);


/* ///////////////////////////////////////////////////// */
/*! @brief 要約説明.
 *         要約説明の続き.
 *
 *  詳細説明がここから始まる.
 */
/* ///////////////////////////////////////////////////// */
static void  _Logger_Output(const char* value)
{
    int len=strlen(value);
    forPC_serial.write(value, len);
}

/* ///////////////////////////////////////////////////// */
/*! @brief 要約説明.
 *         要約説明の続き.
 *
 *  詳細説明がここから始まる.
 */
/* ///////////////////////////////////////////////////// */
static void  _Logger_mutex_wait_function(void)
{
    forPC_mutex.lock();
}

/* ///////////////////////////////////////////////////// */
/*! @brief 要約説明.
 *         要約説明の続き.
 *
 *  詳細説明がここから始まる.
 */
/* ///////////////////////////////////////////////////// */
static void  _Logger_mutex_release_function(void)
{
    forPC_mutex.unlock();
}

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

    mbed_trace_init();
    mbed_trace_print_function_set(_Logger_Output);
    mbed_trace_mutex_wait_function_set(_Logger_mutex_wait_function);
    mbed_trace_mutex_release_function_set(_Logger_mutex_release_function);

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
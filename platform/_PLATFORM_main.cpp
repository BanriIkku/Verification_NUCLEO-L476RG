
#include "_PLATFORM_main.h"
#include "mbed_trace.h"

#define TRACE_GROUP   "plat"

#define PLATFORM_STRING_MAX 255

Mutex forPC_mutex;

UARTSerial forPC_serial(STDIO_UART_TX, STDIO_UART_RX, MBED_CONF_PLATFORM_STDIO_BAUD_RATE);


/* ///////////////////////////////////////////////////// */
/*! @brief 要約説明.
 *         要約説明の続き.
 *
 *  詳細説明がここから始まる.
 */
/* ///////////////////////////////////////////////////// */
static void  _Logger_Output(const char *value)
{
    int len = strlen(value);
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
MBED_WEAK int _USR_Repetition(const char *agrs_split, const int len)
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
    tr_info("%s[%d] %s: %s", __FILE__, __LINE__, __FUNCTION__, "Initialize");
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
    tr_info("%s[%d] %s: %s", __FILE__, __LINE__, __FUNCTION__, "Terminate");
    return 0;
}

/* ///////////////////////////////////////////////////// */
/*! @brief 要約説明.
 *         要約説明の続き.
 *
 *  詳細説明がここから始まる.
 */
/* ///////////////////////////////////////////////////// */
int _PLATFORM_Repetition(const char *agrs_split, const int len)
{
    // tr_info("%s_%s_%d: %s",__FILE__,__FUNCTION__, __LINE__, "Repetition" );
    return _USR_Repetition(agrs_split, len);
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
    tr_info("%s[%d] %s: %s", __FILE__, __LINE__, __FUNCTION__, "Initialize");
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
    tr_info("%s[%d] %s: %s", __FILE__, __LINE__, __FUNCTION__, "Terminate");

    return _USR_Terminate();
}

DigitalOut usr_led(LED1);
InterruptIn user_interruptin(USER_BUTTON);
volatile bool flag_continued = true;

void _func_continued()
{
    flag_continued = false;
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
    char agrs_char[PLATFORM_STRING_MAX] = {0};
    char agrs_split[PLATFORM_STRING_MAX] = {0};
    ssize_t args_len = 0;
    int args_len_split = 0;
    bool flag_get_args = false;
    mbed_trace_init();
    mbed_trace_print_function_set(_Logger_Output);
    mbed_trace_mutex_wait_function_set(_Logger_mutex_wait_function);
    mbed_trace_mutex_release_function_set(_Logger_mutex_release_function);

    int ret_value = 0;

    usr_led = 1;
    ret_value += _PLATFORM_Initialize();

    user_interruptin.rise(&_func_continued);  // attach the address of the flip function to the rising edge
    LowPowerTimer lpt;
    lpt.start();

    do {

        args_len = forPC_serial.read(agrs_char, PLATFORM_STRING_MAX);

        for (int i = 0; i < args_len; i++) {
            if (PLATFORM_STRING_MAX <= args_len_split) {
                args_len_split = 0;
            }
            if ('\r' == agrs_char[i]) {

            } else if ('\n' == agrs_char[i]) {
                flag_get_args = true;
                agrs_split[args_len_split] = '\0';
            } else {
                agrs_split[args_len_split++] = agrs_char[i];
            }
        }

        if (1 <= lpt.read()) {
            usr_led = !usr_led;
            lpt.reset();
        }
        _PLATFORM_Repetition(agrs_split, ((true == flag_get_args) ? args_len_split : 0));

        if (true == flag_get_args) {
            args_len_split = 0;
            flag_get_args = false;
        }


        ThisThread::sleep_for(MBED_CONF_MYPLATFORM_INTERVAL_MILLISECOND);
    } while (true == flag_continued);
    lpt.stop();

    usr_led = 1;
    ret_value += _PLATFORM_Terminate();
    usr_led = 0;

    mbed_trace_free();

    return ret_value;
}


#undef TRACE_GROUP
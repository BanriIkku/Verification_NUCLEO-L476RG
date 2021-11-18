/**
 * @file _PLATFORM_main.cpp
 * @brief
 * @date 2021-09-11
 *
 * @copyright Copyright (c) MaSiRo Project. 2021-.
 *
 */
#include "_PLATFORM_main.h"

#include "SystemReport.h"
#include "mbed_trace.h"

#define TRACE_GROUP "plat"

#define PLATFORM_STRING_MAX 255

/* ///////////////////////////////////////////////////// */
#if MBED_CONF_MYPLATFORM_OUTPUT_LED_ENABLE
/**
 * @brief 動作ランプの定義
 *
 * @return DigitalOut
 */
DigitalOut running_lamp(MBED_CONF_MYPLATFORM_OUTPUT_LED_PIN);
#endif
/* ///////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////// */
#if MBED_CONF_MYPLATFORM_SYSTEMREPORT_ENABLE
SystemReport system_report;
#endif
/* ///////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////// */
/**
 * @brief 停止処理判定フラグ
 *
 */
volatile bool flag_continued = true;
/**
 * @brief 停止処理をリクエストする
 * ユーザー側で宣言しなおすことで、上書きする。
 *
 * @return trueならば、停止処理を実行する。
 */
MBED_WEAK bool _USR_Request_Suspension()
{
    return true;
}
/**
 * @brief ユーザーリクエストを確認し、OKならば停止する。
 *
 */
void _PLATFORM_Request_Suspension()
{
    if (true == _USR_Request_Suspension()) {
        flag_continued = false;
    }
}

/* ///////////////////////////////////////////////////// */
#if MBED_CONF_MYPLATFORM_SUSPENSION_ENABLE
/**
 * @brief ボード搭載のユーザーボタンで停止処理をする
 *
 * @return InterruptIn
 */
InterruptIn suspension_interrupt_in(MBED_CONF_MYPLATFORM_SUSPENSION_BUTTON);
#endif

#if MBED_CONF_MYPLATFORM_OUTPUT_UART_ENABLE
/**
 * @brief
 *
 * @return BufferedSerial
 */
BufferedSerial forPC_serial(CONSOLE_TX, CONSOLE_RX, MBED_CONF_PLATFORM_STDIO_BAUD_RATE);

/**
 * @brief
 *
 */
Mutex forPC_mutex;

/**
 * @brief UART経由で動作ログを出力するの関数
 *
 * @param value
 */
static void _Logger_Output(const char *value)
{
    int len = strlen(value);
    forPC_serial.write(value, len);
}

/**
 * @brief UART経由で動作ログを出力する際のロック処理
 *
 */
static void _Logger_mutex_wait_function(void)
{
    forPC_mutex.lock();
}

/**
 * @brief UART経由で動作ログを出力する際のロック解除処理
 *
 */
static void _Logger_mutex_release_function(void)
{
    forPC_mutex.unlock();
}
#endif

/**
 * @brief ユーザー用の繰り返し処理
 * ユーザー側で宣言しなおすことで、上書きする。
 *
 * @param args_split
 * @param len
 * @return MBED_WEAK
 */
MBED_WEAK int _USR_Repetition(USER_DATA *commondata, const char *args_split, const int len)
{
    if (0 < len) {
        tr_info("%s[%d] : %s[%d]", __FILE__, __LINE__, args_split, len);
    }
    return 0;
}

/**
 * @brief ユーザー用の初期化処理
 *
 * ユーザー側で宣言しなおすことで、上書きする。
 *
 * @return int
 */
MBED_WEAK int _USR_Initialize(USER_DATA *commondata)
{
    tr_info("%s[%d] %s: %s", __FILE__, __LINE__, __FUNCTION__, "Initialize");
    return 0;
}

/**
 * @brief ユーザー用の終了処理
 *
 * ユーザー側で宣言しなおすことで、上書きする。
 *
 * @return int
 */
MBED_WEAK int _USR_Terminate(USER_DATA *commondata)
{
    tr_info("%s[%d] %s: %s", __FILE__, __LINE__, __FUNCTION__, "Terminate");
    return 0;
}

/**
 * @brief
 *
 * @param args_split
 * @param len
 * @return int
 */
inline int _PLATFORM_Repetition(USER_DATA *commondata, const char *args_split, const int len)
{
    // tr_info("%s_%s_%d: %s",__FILE__,__FUNCTION__, __LINE__, "Repetition" );
    return _USR_Repetition(commondata, args_split, len);
}
/**
 * @brief
 *
 * @return int
 */
inline int _PLATFORM_Initialize(USER_DATA *commondata)
{
#if MBED_CONF_MYPLATFORM_SYSTEMREPORT_ENABLE
    system_report.report_system_information();
#endif
    tr_info("%s[%d] %s: %s", __FILE__, __LINE__, __FUNCTION__, "Initialize");
    return _USR_Initialize(commondata);
}

/**
 * @brief
 *
 * @return int
 */
inline int _PLATFORM_Terminate(USER_DATA *commondata)
{
    tr_info("%s[%d] %s: %s", __FILE__, __LINE__, __FUNCTION__, "Terminate");

    int result = _USR_Terminate(commondata);

    return result;
}
/**
 * @brief
 *
 * @return int
 */
int _PLATFORM_main(void)
{
    USER_DATA *commondata = new USER_DATA();
#if MBED_CONF_MYPLATFORM_OUTPUT_UART_ENABLE
    char    args_char[PLATFORM_STRING_MAX] = { '\0' };
    ssize_t args_len                       = 0;
#endif
    char                                  args_split[PLATFORM_STRING_MAX] = { '\0' };
    int                                   args_len_split                  = 0;
    bool                                  flag_get_args                   = false;
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    double                                elapsed = 0;
#if MBED_CONF_MYPLATFORM_OUTPUT_LED_ENABLE
    std::chrono::system_clock::time_point led_start;
    double                                led_span = 1000;
#endif
#if MBED_CONF_MYPLATFORM_SYSTEMREPORT_ENABLE
    std::chrono::system_clock::time_point report_start;
    double                                report_span = MBED_CONF_MYPLATFORM_SYSTEMREPORT_INTERVAL_MILLISECOND;
#endif
    std::chrono::milliseconds interval_sleep(MBED_CONF_MYPLATFORM_INTERVAL_MILLISECOND);
    double                    interval_sleep_min = 10;
    int                       ret_value          = 0;

    mbed_trace_init();
#if MBED_CONF_MYPLATFORM_OUTPUT_UART_ENABLE
    mbed_trace_print_function_set(_Logger_Output);
    mbed_trace_mutex_wait_function_set(_Logger_mutex_wait_function);
    mbed_trace_mutex_release_function_set(_Logger_mutex_release_function);
#endif

#if MBED_CONF_MYPLATFORM_OUTPUT_LED_ENABLE
    running_lamp = 1;
#endif
    ret_value += _PLATFORM_Initialize(commondata);

#if MBED_CONF_MYPLATFORM_SUSPENSION_ENABLE
    // attach the address of the flip function to the rising edge
    suspension_interrupt_in.rise(&_PLATFORM_Request_Suspension);
    led_start = std::chrono::system_clock::now();
#endif

    do {
#if MBED_CONF_MYPLATFORM_OUTPUT_UART_ENABLE
        if (true == forPC_serial.readable()) {
            args_len = forPC_serial.read(args_char, sizeof(args_char));

            for (int i = 0; i < args_len; i++) {
                if (PLATFORM_STRING_MAX <= args_len_split) {
                    args_len_split = 0;
                }
                if ('\r' == args_char[i]) {
                } else if ('\n' == args_char[i]) {
                    flag_get_args              = true;
                    args_split[args_len_split] = '\0';
                } else {
                    args_split[args_len_split++] = args_char[i];
                }
            }
        }
#endif

#if MBED_CONF_MYPLATFORM_OUTPUT_LED_ENABLE
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - led_start).count();
        if (led_span <= elapsed) {
            running_lamp = !running_lamp;
            led_start    = std::chrono::system_clock::now();
        }
#endif
        start = std::chrono::system_clock::now(); // 計測開始時間
        _PLATFORM_Repetition(commondata, args_split,
                             ((true == flag_get_args) ? args_len_split : 0)); // 処理

        if (true == flag_get_args) {
            args_len_split = 0;
            flag_get_args  = false;
        }
#if MBED_CONF_MYPLATFORM_SYSTEMREPORT_ENABLE
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - report_start).count();
        if (report_span <= elapsed) {
            system_report.report_state();
            report_start = std::chrono::system_clock::now();
        }
#endif
        end     = std::chrono::system_clock::now();                                                              // 計測終了時間
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>((interval_sleep + start) - end).count(); //処理に要した時間をミリ秒に変換

        if (0 >= elapsed) {
            elapsed = interval_sleep_min;
        }

        ThisThread::sleep_for(std::chrono::milliseconds((int)elapsed));
    } while (true == flag_continued);

#if MBED_CONF_MYPLATFORM_OUTPUT_LED_ENABLE
    running_lamp = 1;
#endif
    ret_value += _PLATFORM_Terminate(commondata);
#if MBED_CONF_MYPLATFORM_OUTPUT_LED_ENABLE
    running_lamp = 0;
#endif

    mbed_trace_free();

    return ret_value;
}
#undef TRACE_GROUP


#include "mbed.h"
#include "mbed_trace.h"

Mutex forPC_mutex;

UARTSerial forPC_serial(STDIO_UART_TX, STDIO_UART_RX,MBED_CONF_PLATFORM_STDIO_BAUD_RATE);


/* ///////////////////////////////////////////////////// */
/*! @brief 要約説明.
 *         要約説明の続き.
 *
 *  詳細説明がここから始まる.
 */
/* ///////////////////////////////////////////////////// */
static void _Logger_output(const char* value)
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
static void _Logger_mutex_wait_function(void)
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
static void _Logger_mutex_release_function(void)
{
    forPC_mutex.unlock();
}

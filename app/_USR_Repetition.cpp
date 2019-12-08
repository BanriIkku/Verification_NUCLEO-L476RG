#include "../platform/_PLATFORM_main.h"
#include "mbed_trace.h"
#include "EPD/E-INK/Target/13454/EPD_Device.h"

#define TRACE_GROUP   "_USR"
#if 1
E_INK::EPD_Device epd;
#endif
#define EPD_SIZE ((400/8)*300)
/* ///////////////////////////////////////////////////// */
/*! @brief 要約説明.
 *         要約説明の続き.
 *
 *  詳細説明がここから始まる.
 */
/* ///////////////////////////////////////////////////// */
int _USR_Repetition(const char *agrs_split, const int len)
{
#if 1
    static  char bw_value[EPD_SIZE];
    int bw_length=EPD_SIZE;

    static   char red_value[EPD_SIZE];
    int red_length=EPD_SIZE;

    for (int i = 0; i < EPD_SIZE; i++)
    {
        bw_value[i] = 0x0f;
    }
    for (int i = 0; i < EPD_SIZE; i++)
    {
        red_value[i] = 0xAA;
    }


    if (0 < len)
    {
        tr_info("/////");
        tr_info(agrs_split);
        for (int i = 0; i < len; i++) {
            switch (agrs_split[i])
            {

            case '1':
                tr_info("Init 01");
                if (false == epd.Create())
                {
                    tr_info("ERR");
                }

                break;
            case '0':
                tr_info("End");
                epd.Destroy();
                /* code */
                break;
            case 'a':
                break;
            case 'b':
                break;
            case 'c':
                tr_info("%s", epd.busy()?"YES":"NO");
                break;
            case 'r':
                if (true == epd.Continued())
                {
                    tr_info("Refresh");
                    epd.Refresh(bw_value, bw_length, red_value, red_length);
                }
                else
                {
                    tr_info("BUSY");
                }

                /* code */
                break;

            default:
                break;
            }
        }


        tr_info("*******");
    }
#else
    if (0 < len)
    {
        tr_info(agrs_split);
    }
#endif
    return 0;
}

#undef TRACE_GROUP
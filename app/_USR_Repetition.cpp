#include "../platform/_PLATFORM_main.h"
#include "mbed_trace.h"
#include "EPD/E-INK/Target/13454/EPD_Device.h"

#define TRACE_GROUP   "_USR"
#if 1
E_INK::EPD_Device epd;
#endif
#define EPD_SIZE ((400/8)*300)

static char images_data[EPD_SIZE] = {
#include "data.txt"
};
static char images_HertB[EPD_SIZE] = {
#include "HertF.txt"
};
static char images_HertF[EPD_SIZE] = {
#include "HertB.txt"
};

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
    int bw_length=EPD_SIZE;
#if 0
    static  char bw_value[EPD_SIZE];


    for (int i = 0; i < EPD_SIZE; i++)
    {
        bw_value[i] = 0x0f;
    }
#endif
    int red_length=EPD_SIZE;
#if 1
    static   char red_value[EPD_SIZE];
    for (int i = 0; i < EPD_SIZE; i++)
    {
        red_value[i] = 0x00;
    }
#endif


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
            case 'h':
                if (true == epd.Continued())
                {
                    tr_info("Refresh");
                    epd.Refresh(images_HertF, bw_length, images_HertB, red_length);
                }
                else
                {
                    tr_info("BUSY");
                }

                /* code */
                break;
            case 'r':
                if (true == epd.Continued())
                {
                    tr_info("Refresh");
                    epd.Refresh(images_data, bw_length, red_value, red_length);
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
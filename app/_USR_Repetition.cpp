#include "../platform/_PLATFORM_main.h"
#include "mbed_trace.h"

#define TRACE_GROUP "_USR"

/* ///////////////////////////////////////////////////// */
/*! @brief 要約説明.
 *         要約説明の続き.
 *
 *  詳細説明がここから始まる.
 */
/* ///////////////////////////////////////////////////// */
int _USR_Repetition(USER_DATA *commondata, const char *args_split, const int len)
{
    if (0 < len) {
        tr_info("%s", args_split);
    }
    return 0;
}

#undef TRACE_GROUP
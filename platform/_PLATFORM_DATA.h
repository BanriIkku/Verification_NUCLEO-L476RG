/**
 * @file _PLATFORM_DATA.h
 * @brief
 * @date 2021-09-11
 *
 * @copyright Copyright (c) MaSiRo Project. 2021-.
 *               MaSiRo Project.
 *
 */
#ifndef _PLATFORM_DATA
#define _PLATFORM_DATA

#include "mbed.h"

/**
 * @brief プラットフォーム用のデータクラス
 */
class PLATFORM_DATA {
public:
    PLATFORM_DATA() {}
    void Request_Suspension()
    {
        this->_Request_Suspension = true;
    }

private:
    bool _Request_Suspension = false;
};

#endif

#include "EPD_Device.h"

namespace E_INK {
////////////////////////////////////////////////
////////////////////////////////////////////////
// Create()
bool EPD_Device::Create()
{
    spi_initialize();

    toggle_reset(false);
    ThisThread::sleep_for(100);
    toggle_reset(true);
    ThisThread::sleep_for(100);
    toggle_reset(false);
    ThisThread::sleep_for(100);

    CMD_06();
    CMD_04();
    if(true == check_busy(false))
    {
        CMD_00();
        CMD_61();
        CMD_50();

        return true;
    }
    return false;
}

// Destroy()
bool EPD_Device::Destroy()
{
    CMD_50();
    CMD_02();
    CMD_07();
    return true;
}

bool EPD_Device::Refresh(char *bw_value, int bw_length,char *red_value, int red_length)
{
    // BWdata
    CMD_10(bw_value,bw_length);

    // readdata
    CMD_13(red_value,red_length);

    CMD_12();
    return true;
}
bool EPD_Device::Continued()
{
    return check_busy(false);
}

////////////////////////////////////////////////
////////////////////////////////////////////////
}

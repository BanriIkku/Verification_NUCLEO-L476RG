#include "EPD_Device.h"

namespace E_INK {
/* ==================================== */

#define EPD_DEVICE_BUSY_TIMEOUT       15000
#define EPD_DEVICE_BUSY_WAITTIME      1
/////////////////////////////////////////
#define EPD_DEVICE_SPIMODE  (MBED_CONF_E_INK_MODE_POLARITY << 1) & MBED_CONF_E_INK_MODE_PHASE
/* ==================================== */

SPI EPD_Device_spi(MBED_CONF_E_INK_MOSI, MBED_CONF_E_INK_MISO, MBED_CONF_E_INK_SCLK);  // mosi, miso, sclk
DigitalOut EPD_Device_cs(MBED_CONF_E_INK_CS);
DigitalOut EPD_Device_dc(MBED_CONF_E_INK_DC);
DigitalOut EPD_Device_reset(MBED_CONF_E_INK_RST);
DigitalIn EPD_Device_busy(MBED_CONF_E_INK_BUSY);


void EPD_Device::spi_initialize(void)
{
    EPD_Device_spi.format(MBED_CONF_E_INK_BITS, EPD_DEVICE_SPIMODE);
    EPD_Device_spi.frequency(MBED_CONF_E_INK_FREQUENCY);
}
void EPD_Device::spi_write(int data)
{
    EPD_Device_spi.write(data);
}
int EPD_Device::spi_read(void)
{
    return EPD_Device_spi.write(0x00);
}
/**
 * @brief
 */
void EPD_Device::toggle_cs(bool toggle)
{
    EPD_Device_cs.write(toggle ? 1 : 0);
}
/**
 * @brief
 */
void EPD_Device::toggle_dc(bool toggle)
{
    EPD_Device_dc.write(toggle ? 1 : 0);
}
/**
 * @brief
 */
void EPD_Device::toggle_reset(bool toggle)
{
    EPD_Device_reset.write(toggle ? 1 : 0);
}
/**
 * @brief
 */
bool EPD_Device::check_busy(bool toggle)
{
    bool retValue = true;
    Timer ts;
    ts.start();
    ts.reset();
    while ((toggle ? 1 : 0) == EPD_Device_busy.read()) {
        if (EPD_DEVICE_BUSY_TIMEOUT < ts.read_ms()) {
            retValue = false;
            break;
        }
        ThisThread :: sleep_for(EPD_DEVICE_BUSY_WAITTIME);
    }
    ts.stop();

    return retValue;
}




// 唯一のインスタンスをNULLで初期化
EPD_Device *EPD_Device::s_pInstance = NULL;

// Create()
void EPD_Device::Create()
{
    if (!s_pInstance) {
        s_pInstance = new EPD_Device;
    }
}

// Destroy()
void EPD_Device::Destroy()
{
    delete s_pInstance;
    s_pInstance = NULL;
}

/* ==================================== */
} // namespace E_INK

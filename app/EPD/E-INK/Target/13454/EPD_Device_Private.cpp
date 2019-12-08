#include "EPD_Device.h"

namespace E_INK {
/**
 * @brief Panel Setting (PSR) (Register: R00H)
 */
void EPD_Device::CMD_00(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x00);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x0F);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief Power Setting (PWR) (R01H)
 */
void EPD_Device::CMD_01(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x01);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x03);
        spi_write(0x00);
        spi_write(0x26);
        spi_write(0x26);
        spi_write(0x03);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief Power OFF (PWR) (R02H)
 */
void EPD_Device::CMD_02(void)
{
// Power off
// SPI (0x02)
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x02);
    }
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_03(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x03);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x00);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_04(void)
{
// Power on
// SPI (0x04)
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x04);
    }
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_05(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x05);
    }
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_06(void)
{
// Booster soft start
// SPI (0x06,0x17,0x17,0x17)
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x06);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x17);
        spi_write(0x17);
        spi_write(0x17);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_07(void)
{
// Deep sleep
// SPI (0x07,0xa5)
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x07);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0xA5);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_10(char *value, int length)
{
// Data start transmission 1
// SPI (0x10)
// Transport B/W data
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x10);
    }
    toggle_dc(true);
    {
        // send data
        for (int i = 0; i < length; i++) {
            spi_write(value[i]);
        }
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
bool EPD_Device::CMD_11(void)
{
    int value = 0x00;
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x11);
    }
    toggle_dc(true);
    {
        // send data
        value = spi_read();
    }
    toggle_dc(false);
    toggle_cs(false);

    return (((value >> 7) & 0x01) == 0x01) ? true : false;
}
/**
 * @brief
 */
void EPD_Device::CMD_12(void)
{
// Display refresh
// SPI (0x12)
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x12);
    }
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_13(char *value, int length)
{
// Data start transmission 2
// SPI (0x13)
// Transport red data
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x13);
    }
    toggle_dc(true);
    {
        // send data
        for (int i = 0; i < length; i++) {
            spi_write(value[i]);
        }
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_20(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x20);
    }
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_21(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x21);
    }
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_22(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x22);
    }
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_23(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x23);
    }
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_24(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x24);
    }
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_30(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x30);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x3C);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_40(int *lm, int *tsr)
{
    int value_1 = 0x00;
    int value_2 = 0x00;
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x40);
    }
    toggle_dc(true);
    {
        // send data
        value_1 = spi_read();
        value_2 = spi_read();
    }
    toggle_dc(false);
    toggle_cs(false);
    *lm = value_1 << 0x03 & ((value_2 >> 0x05) & 0x07);
    *tsr = value_1;
}
/**
 * @brief
 */
void EPD_Device::CMD_41(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x41);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x00);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_42(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x42);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x00);
        spi_write(0x00);
        spi_write(0x00);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_43(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x43);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x00);
        spi_write(0x00);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_50(void)
{
// Vcom and data interval setting
// SPI (0x50,value)Note1
// Vcom and data interval setting
// SPI (0x50,0x87)
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x50);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x87);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
bool EPD_Device::CMD_51(void)
{
    int value = 0x00;
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x51);
    }
    toggle_dc(true);
    {
        // send data
        value = spi_read();
    }
    toggle_dc(false);
    toggle_cs(false);

    return (((value) & 0x01) == 0x01) ? true : false;
}
/**
 * @brief
 */
void EPD_Device::CMD_60(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x60);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x22);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_61(void)
{
// Resolution setting
// SPI (0x61,0x01,0x90,0x01,0x2c)
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x61);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x01);
        spi_write(0x90);
        spi_write(0x01);
        spi_write(0x2C);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_65(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x65);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x00);
        spi_write(0x00);
        spi_write(0x00);
        spi_write(0x00);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
int EPD_Device::CMD_71(void)
{
    int value = 0x00;
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x71);
    }
    toggle_dc(true);
    {
        // send data
        value = spi_read();
    }
    toggle_dc(false);
    toggle_cs(false);

    return (value) & 0x7F;
}
/**
 * @brief
 */
void EPD_Device::CMD_80(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x80);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x00);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_81(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x81);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x00);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_82(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x82);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x00);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_90(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x90);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x00);
        spi_write(0x00);

        spi_write(0x00);
        spi_write(0x07);

        spi_write(0x00);
        spi_write(0x00);

        spi_write(0x00);
        spi_write(0x00);

        spi_write(0x01);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_91(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x91);
    }
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_92(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0x92);
    }
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_A0(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0xA0);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0xA5);
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_A1(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0xA1);
    }
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_A2(int *value, int length)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0xA2);
    }
    toggle_dc(true);
    {
        // send data
        spi_read();
        for (int i = 0; i < length; i++) {
            value[i] = spi_read();
        }
    }
    toggle_dc(false);
    toggle_cs(false);
}
/**
 * @brief
 */
void EPD_Device::CMD_E3(void)
{
    toggle_cs(true);
    toggle_dc(false);
    {
        // send command
        spi_write(0xE3);
    }
    toggle_dc(true);
    {
        // send data
        spi_write(0x00);
    }
    toggle_dc(false);
    toggle_cs(false);
}
}

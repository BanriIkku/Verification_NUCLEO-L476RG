
# Verification_NUCLEO-L476RG

NUCLEO-L476RGを使って何ができるか確認するためのrepositoryです。



## Configuration parameters

https://os.mbed.com/docs/mbed-os/v5.14/reference/configuration.html


## Pin配置

    // STDIO for console print
#ifdef MBED_CONF_TARGET_STDIO_UART_TX
    STDIO_UART_TX = MBED_CONF_TARGET_STDIO_UART_TX,
#else
    STDIO_UART_TX = PA_2,
#endif
#ifdef MBED_CONF_TARGET_STDIO_UART_RX
    STDIO_UART_RX = MBED_CONF_TARGET_STDIO_UART_RX,
#else
    STDIO_UART_RX = PA_3,
#endif


    // Generic signals namings
    LED1        = PA_5,
    LED2        = PA_5,
    LED3        = PA_5,
    LED4        = PA_5,
    USER_BUTTON = PC_13,
    // Standardized button names
    BUTTON1 = USER_BUTTON,
    SERIAL_TX   = STDIO_UART_TX,
    SERIAL_RX   = STDIO_UART_RX,
    USBTX       = STDIO_UART_TX,
    USBRX       = STDIO_UART_RX,
    I2C_SCL     = PB_8,
    I2C_SDA     = PB_9,
    SPI_MOSI    = PA_7,
    SPI_MISO    = PA_6,
    SPI_SCK     = PA_5,
    SPI_CS      = PB_6,
    PWM_OUT     = PB_3,

    /**** USB pins ****/
    USB_OTG_FS_DM = PA_11,
    USB_OTG_FS_DP = PA_12,
    USB_OTG_FS_ID = PA_10,
    USB_OTG_FS_NOE = PC_9,
    USB_OTG_FS_NOE_ALT0 = PA_13,
    USB_OTG_FS_SOF = PA_8,
    USB_OTG_FS_VBUS = PA_9,

    /**** OSCILLATOR pins ****/
    RCC_OSC32_IN = PC_14,
    RCC_OSC32_OUT = PC_15,
    RCC_OSC_IN = PH_0,
    RCC_OSC_OUT = PH_1,

    /**** DEBUG pins ****/
    SYS_JTCK_SWCLK = PA_14,
    SYS_JTDI = PA_15,
    SYS_JTDO_SWO = PB_3,
    SYS_JTMS_SWDIO = PA_13,
    SYS_JTRST = PB_4,
    SYS_PVD_IN = PB_7,
    SYS_WKUP1 = PA_0,
    SYS_WKUP2 = PC_13,
    SYS_WKUP4 = PA_2,
    SYS_WKUP5 = PC_5,

## 参考資料

https://os.mbed.com/questions/84388/Nucleo-F401RE-as-USB-Mass-Storage-Device/
http://www.doxygen.jp/

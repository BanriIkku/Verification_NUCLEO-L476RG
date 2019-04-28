
#ifndef _EPD_DEVICE_H_
#define _EPD_DEVICE_H_
/* ==================================== */
#include "mbed.h"

namespace E_INK {
/* ==================================== */
class EPD_Device {
public:
    static EPD_Device *GetInstance()
    {
        return s_pInstance;
    }

    static void Create();
    static void Destroy();

protected:
    static EPD_Device *s_pInstance;
    EPD_Device();     // 隠しコンストラクタ

private:
////////////////////////////////
    void spi_initialize(void);
    void spi_write(int data);
    int spi_read(void);

    void toggle_cs(bool toggle);
    void toggle_dc(bool toggle);
    void toggle_reset(bool toggle);
    bool check_busy(bool toggle);

////////////////////////////////
    void CMD_00(void);
    void CMD_01(void);
    void CMD_02(void);
    void CMD_03(void);
    void CMD_04(void);
    void CMD_05(void);
    void CMD_06(void);
    void CMD_07(void);
    void CMD_10(int *value, int length);
    bool CMD_11(void);
    void CMD_12(void);
    void CMD_13(int *value, int length);
    void CMD_20(void);
    void CMD_21(void);
    void CMD_22(void);
    void CMD_23(void);
    void CMD_24(void);
    void CMD_30(void);
    void CMD_40(int *lm, int *tsr);
    void CMD_41(void);
    void CMD_42(void);
    void CMD_43(void);
    void CMD_50(void);
    bool CMD_51(void);
    void CMD_60(void);
    void CMD_61(void);
    void CMD_65(void);
    int CMD_71(void);
    void CMD_80(void);
    void CMD_81(void);
    void CMD_82(void);
    void CMD_90(void);
    void CMD_91(void);
    void CMD_92(void);
    void CMD_A0(void);
    void CMD_A1(void);
    void CMD_A2(int *value, int length);
    void CMD_E3(void);

////////////////////////////////
};

/* ==================================== */
} // namespace E_INK
#endif

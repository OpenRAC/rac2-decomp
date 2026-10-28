/* func_L05_00442880 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G8 -ffunction-sections.
 * Measured in src/levels/shared/L05_00442880-g8.c: 472/472 bytes.
 * US: 0/4 local places; PAL: 0/4 local places; US2: 0/4 local places.
 * No strict linked build was run because no local placement matched.
 * The initial model pointer uses v0 instead of a0 and later preload/store stages differ in FPR allocation/order. Preload groups follow measured memory reads. Reopen with alias/field grouping evidence.
 */

#include "common.h"

extern char *D_L05_001B1EC4 MACRO_ADDR;
extern char *D_L05_001B251C MACRO_ADDR;
extern int D_L05_001A79F0 __attribute__((sda));
extern int func_L05_00379F38(void);extern float D_L05_001B1AB4 __attribute__((sda));
extern float D_L05_001B1AB8 __attribute__((sda));
extern float D_L05_001B1ABC __attribute__((sda));
extern float D_L05_001B1A8C __attribute__((sda));
extern float D_L05_001B1A90 __attribute__((sda));
extern float D_L05_001B1A88 __attribute__((sda));
extern float D_L05_001B1A94 __attribute__((sda));
extern float D_L05_001B1A98 __attribute__((sda));
extern float D_L05_001B1A28 __attribute__((sda));
extern float D_L05_001B1A34 __attribute__((sda));
extern float D_L05_001B1A38 __attribute__((sda));
extern float D_L05_001B1A3C __attribute__((sda));
extern float D_L05_001B1A2C __attribute__((sda));
extern float D_L05_001B1A30 __attribute__((sda));
extern float D_L05_001B1A1C __attribute__((sda));
extern float D_L05_001B1A20 __attribute__((sda));
extern float D_L05_001B1A24 __attribute__((sda));
extern float D_L05_001B1A78 __attribute__((sda));
extern float D_L05_001B1A74 __attribute__((sda));
extern float D_L05_001B1A58 __attribute__((sda));
extern float D_L05_001B1B88 __attribute__((sda));
extern float D_L05_001B1B84 __attribute__((sda));
extern float D_L05_001B1B8C __attribute__((sda));
extern float D_L05_001B1B90 __attribute__((sda));
extern float D_L05_001B1B94 __attribute__((sda));
extern float D_L05_001B1B98 __attribute__((sda));
extern float D_L05_001B1B9C __attribute__((sda));
extern float D_L05_001B1BA0 __attribute__((sda));
extern float D_L05_001B1BA4 __attribute__((sda));
extern float D_L05_001B1BA8 __attribute__((sda));
extern float D_L05_001B1BAC __attribute__((sda));
extern float D_L05_001B1BB0 __attribute__((sda));
extern float D_L05_001B1BB4 __attribute__((sda));
extern float D_L05_001B1BB8 __attribute__((sda));
extern float D_L05_001B1BC0 __attribute__((sda));
extern float D_L05_001B1A5C __attribute__((sda));
extern float D_L05_001B1A64 __attribute__((sda));
extern float D_L05_001B1A4C __attribute__((sda));
extern float D_L05_001B1A50 __attribute__((sda));
extern float D_L05_001B1A54 __attribute__((sda));
extern float D_L05_001B1A70 __attribute__((sda));
extern float D_L05_001B1A6C __attribute__((sda));

void func_L05_00442880(char *object)
{
    char *record = *(char **)(object + 0x70);
    char *settings = record + 0x50;
    char *entry = *(char **)(D_L05_001B1EC4 + *(short *)(object + 0x84) * 32 + 0x1C);
    char *render = *(char **)(*(int *)(entry + 0x20) * 256 + D_L05_001B251C + 0x68);
    {
        float value0 = D_L05_001B1AB4;
        float value1 = D_L05_001B1AB8;
        float value2 = D_L05_001B1ABC;
        float value3 = D_L05_001B1A8C;
        float value4 = D_L05_001B1A90;
        float value5 = D_L05_001B1A88;
        float value6 = D_L05_001B1A94;
        float value7 = D_L05_001B1A98;
        *(float *)(render + 0x240) = value0;
        *(float *)(render + 0x244) = value1;
        *(float *)(render + 0x248) = value2;
        *(float *)(render + 0x250) = value3;
        *(float *)(render + 0x254) = value4;
        *(float *)(render + 0x24C) = value5;
        *(float *)(render + 0x258) = value6;
        *(float *)(render + 0x25C) = value7;
    }
    if (func_L05_00379F38()) {
        if (D_L05_001A79F0 == 15) {
            {
                float value8 = D_L05_001B1A34;
                float value9 = D_L05_001B1A38;
                float value10 = D_L05_001B1A3C;
                *(float *)(settings + 0xC) = value8;
                *(float *)(settings + 0x10) = value9;
                *(float *)(settings + 0x14) = value10;
            }
        } else {
            {
                float value11 = D_L05_001B1A28;
                float value12 = D_L05_001B1A2C;
                float value13 = D_L05_001B1A30;
                *(float *)(settings + 0xC) = value11;
                *(float *)(settings + 0x10) = value12;
                *(float *)(settings + 0x14) = value13;
            }
        }
        {
            float value14 = D_L05_001B1A1C;
            float value16 = D_L05_001B1A20;
            float value17 = D_L05_001B1A24;
            float value18 = D_L05_001B1A78;
            float value15 = D_L05_001B1A74;
            *(float *)(settings + 0x0) = value14;
            *(float *)(settings + 0x78) = value15;
            *(float *)(settings + 0x4) = value16;
            *(float *)(settings + 0x8) = value17;
            *(float *)(settings + 0x74) = value18;
        }
    } else if (D_L05_001A79F0 == 15) {
        {
            float value19 = D_L05_001B1B88;
            float value20 = D_L05_001B1B84;
            float value21 = D_L05_001B1B8C;
            float value22 = D_L05_001B1B90;
            *(float *)(settings + 0x10) = value19;
            {
                float value24 = D_L05_001B1B94;
                float value25 = D_L05_001B1B98;
                float value26 = D_L05_001B1B9C;
                float value23 = D_L05_001B1BA0;
                *(float *)(settings + 0xC) = value20;
                *(float *)(settings + 0x14) = value21;
                *(float *)(record + 0x50) = value22;
                {
                    float value28 = D_L05_001B1BA4;
                    float value29 = D_L05_001B1BA8;
                    float value30 = D_L05_001B1BAC;
                    float value31 = D_L05_001B1BB0;
                    float value32 = D_L05_001B1BB4;
                    float value33 = D_L05_001B1BB8;
                    float value34 = D_L05_001B1A94;
                    float value27 = D_L05_001B1BC0;
                    *(float *)(settings + 0x78) = value23;
                    *(float *)(settings + 0x4) = value24;
                    *(float *)(settings + 0x8) = value25;
                    *(float *)(settings + 0x74) = value26;
                    *(float *)(render + 0x25C) = value27;
                    *(float *)(render + 0x240) = value28;
                    *(float *)(render + 0x244) = value29;
                    *(float *)(render + 0x248) = value30;
                    *(float *)(render + 0x250) = value31;
                    *(float *)(render + 0x254) = value32;
                    *(float *)(render + 0x24C) = value33;
                    *(float *)(render + 0x258) = value34;
                }
            }
        }
    } else {
        {
            float value35 = D_L05_001B1A58;
            float value36 = D_L05_001B1A5C;
            float value37 = D_L05_001B1A64;
            float value38 = D_L05_001B1A4C;
            float value40 = D_L05_001B1A50;
            float value41 = D_L05_001B1A54;
            float value42 = D_L05_001B1A70;
            float value39 = D_L05_001B1A6C;
            *(float *)(settings + 0xC) = value35;
            *(float *)(settings + 0x10) = value36;
            *(float *)(settings + 0x14) = value37;
            *(float *)(record + 0x50) = value38;
            *(float *)(settings + 0x78) = value39;
            *(float *)(settings + 0x4) = value40;
            *(float *)(settings + 0x8) = value41;
            *(float *)(settings + 0x74) = value42;
        }
    }
}
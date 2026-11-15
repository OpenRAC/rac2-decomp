#include "common.h"

extern float D_L09_001B13F4 __attribute__((sda));
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern void func_002A7750(char *, int, int);
extern void func_002A7470(char *, int, int, int);

typedef struct DobboEmitter {
    u8 pad_0[0x28];
    u8 f_28;
    u8 pad_29[0x1];
    u8 f_2A;
    u8 pad_2B[0x5];
    float f_30;
    u8 pad_34[0x14];
    u8 f_48;
    u8 pad_49[0x1];
    u8 f_4A;
    u8 pad_4B[0x15];
    u8 f_60;
    u8 pad_61[0x1F];
    float f_80;
    float f_84;
    u8 pad_88[0x4];
    float f_8C;
    u8 pad_90[0x8];
    s32 f_98;
    u8 pad_9C[0x64];
    float f_100;
    float f_104;
    float f_108;
    float f_10C;
    float f_110;
    u8 pad_114[0x1C];
    float f_130;
    float f_134;
    s32 f_138;
    s32 f_13C;
    u8 pad_140[0x90];
    float f_1D0;
    float f_1D4;
    u8 pad_1D8[0x4];
    float f_1DC;
    u8 pad_1E0[0x2];
    short f_1E2;
    short f_1E4;
    u8 pad_1E6[0x2];
    u8 f_1E8;
    u8 f_1E9;
    u8 pad_1EA[0x4A];
    s32 f_234;
    u8 pad_238[0x10C];
    float f_344;
    float f_348;
} DobboEmitter;

/* Runs on the object's first update: copies its position into the record, rolls its size and
   timings and fills in the record's defaults. */
void func_L09_00404C50(char *obj)
{
    DobboEmitter *rec = *(DobboEmitter **)(obj + 0x68);
    float size, spin;
    int count;

    qcopy((char *)rec + 0x300, obj + 0x10);
    size = func_002A7878(1.0f, 1.333f);
    rec->f_344 = size;
    *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * size;
    rec->f_48 = FloatToInt(15.0f);
    rec->f_4A = FloatToInt(4.0f);
    count = 3;
    rec->f_98 = count;
    rec->f_8C = 0.4f;
    rec->f_60 = 0xB;
    rec->f_30 = 0.333f;
    rec->f_2A = 2;
    rec->f_84 = rec->f_80 = 0.2f;
    rec->f_28 = count;
    rec->f_134 = 0.05f;
    rec->f_104 = rec->f_344 * 0.1f;
    rec->f_110 = 0.17453295f;
    rec->f_130 = 0.52359885f;
    rec->f_100 = rec->f_344 * 0.3f;
    rec->f_10C = rec->f_108 = 0.1f;
    rec->f_138 |= 0x80;
    spin = func_002A78D8(18.0f, 22.0f);
    rec->f_1E8 = 7;
    rec->f_1E9 = 6;
    rec->f_1DC = spin * 0.017453294f;
    rec->f_1E2 = 0x78;
    rec->f_1E4 = 0xB4;
    rec->f_13C = rec->f_234;
    rec->f_1D4 = 1.75f;
    rec->f_1D0 = D_L09_001B13F4 * 0.016666668f;
    rec->f_348 = func_002A7940();
    func_002A7750(obj, 1, 0);
    if (*(u8 *)(obj + 0x43) != 0)
        func_002A7470(obj, 0, 0, 0);
    *(s32 *)(obj + 0x9C) = 0xC;
    *(unsigned short *)(obj + 0x34) |= 0x1000;
}

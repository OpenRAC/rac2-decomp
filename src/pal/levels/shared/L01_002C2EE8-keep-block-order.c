#include "include_asm.h"

extern unsigned int D_00138320[];
extern void func_L00_002B39F0(int, float);
extern void func_PAL_L00_002D2668(int, int, float);
extern void func_L00_002D2470(int, int);
extern void func_002AC9F8(void *, float);
extern int D_L00_001A7DDC __attribute__((sda));
typedef struct {
    unsigned char pad0[0x160]; float velocity[4];
    float field_170, elapsed_174, speed_178;
    unsigned char pad1[0x1B4 - 0x17C]; float animation_time; int count_1b8;
    unsigned char pad2[4]; int count_1c0;
    unsigned char pad3[0x1E0 - 0x1C4]; short flag_1e0;
    unsigned char pad4[2]; short flag_1e4;
    unsigned char pad5[0x278 - 0x1E6]; float distance_278;
    unsigned char pad6[4]; float angle_280; unsigned char flag_284;
    unsigned char pad7[0x40E - 0x285]; unsigned char flag_40e;
    unsigned char pad8[0x49C - 0x40F]; unsigned char level_49c;
    unsigned char pad9[0xC20 - 0x49D]; float animation_scale;
    unsigned char pad10[4]; int flags_c28;
    unsigned char pad11[0x1454 - 0xC2C]; short flag_1454; unsigned char flag_1456;
    unsigned char pad12[0x1492 - 0x1457]; unsigned char flag_1492;
    unsigned char pad13[0x2290 - 0x1493]; void *object; int mode, frame;
    unsigned char pad14[0x22B4 - 0x229C]; unsigned char mode_22b4;
    unsigned char pad15[4]; unsigned char flag_22b9;
    unsigned char pad16[0x24A0 - 0x22BA]; int reset_24a0;
    unsigned char pad17[0x24B8 - 0x24A4]; float timer;
    unsigned char pad18[0x24FC - 0x24BC]; short flag_24fc;
} HeroActionState;
extern HeroActionState D_00189E20;

/* Hand-adapted from func_L00_002CA898. */
void func_PAL_L01_002C2EE8(void)
{
    D_00189E20.reset_24a0 = 0;
    func_L00_002B39F0(0, 1.0f);
    if (D_00138320[0] & 8) {
        ref_L01_002C2CF0_00(4, 0);
        func_PAL_L00_002D2668(0xD, 2, -2.0f);
        func_L00_002D2470(3, 0x12);
        return;
    }
    if (0.3f < D_00189E20.timer && D_00189E20.flag_1e0 == 0) {
        if (D_00189E20.flag_1492 != 0 || D_00189E20.flag_22b9 != 0) {
            ref_L01_002C2CF0_00(2, 1);
        } else {
            int amount;
            if (!ref_L01_002C2CF0_00(2, 0)) return;
            amount = 7;
            if (D_00189E20.level_49c > 4) amount = 12;
            D_00189E20.frame = 1;
            func_PAL_L00_002D2668(4, D_L00_001A7DDC, (float)amount);
            D_00189E20.flag_40e = 1;
        }
        return;
    }
    if ((0.060000002f < D_00189E20.speed_178 && D_00189E20.level_49c > 2) ||
        D_00189E20.mode == 0x10) {
        if (ref_L01_002C2CF0_00(3, 0)) {
            func_PAL_L00_002D2668(5, 0, -1.0f);
            func_002AC9F8(D_00189E20.velocity, 0.10000001f);
        }
        return;
    }
    if (D_00189E20.level_49c < 11 && (D_00189E20.flags_c28 & 2) == 0) return;
    if (!ref_L01_002C2CF0_00(0, 0)) return;
    if (ref_L01_002C2CF0_01(0) == 0x51) {
        func_PAL_L00_002D2668(ref_L01_002C2CF0_01(0), 0, 12.0f);
    } else if (D_00189E20.flags_c28 & 2) {
        func_PAL_L00_002D2668(ref_L01_002C2CF0_01(0), 0, -2.0f);
    }
}

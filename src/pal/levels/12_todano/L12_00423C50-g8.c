#include "include_asm.h"

#include "common.h"
extern f32 D_L12_001B1F50[] SDATA(D_L12_001B1F50);
extern f32 D_L12_001B1F58[] SDATA(D_L12_001B1F58);
extern f32 D_L12_001B1F60[] SDATA(D_L12_001B1F60);
extern s32 D_L12_001B1FA0 __attribute__((sda));
extern f32 D_L12_001B1FB0 __attribute__((sda));
extern f32 D_L12_001B1FB4 __attribute__((nosda));
extern f32 D_L12_001B1FB8 __attribute__((nosda));
extern void moby_set_state(void *, int, int);
extern s32 PlayMobySound(s32, s32, s32);
extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern s32 D_L12_001B29C8 __attribute__((sda));
extern u8 *D_L12_001B090C __attribute__((nosda));
extern u8 *D_L12_001B1360 __attribute__((nosda));
extern float IntToFloat(int);
extern int PulseColor(int, int, float);
extern int IsPointInCuboid(void *, int);
extern void moby_set_flag_bit(u8 *, s32);
extern int second_tracked_object_is_open(void);
extern s32 D_L12_001B22D0 __attribute__((sda));
extern f32 D_L12_001B2280[] SDATA(D_L12_001B2280);
extern f32 D_L12_001B2288[] SDATA(D_L12_001B2288);
extern f32 D_L12_001B22B0[] SDATA(D_L12_001B22B0);
extern u8 *CreateMoby(int);

void func_PAL_L12_00425A08(u8 *a0)
{
    s32 *s = *(s32 **)(a0 + 0x68);
    u8 *rec;
    u8 *obj;
    f32 phase, d;

    switch (a0[0x20]) {
    case 0:
        moby_set_state(a0, 1, -1);
        break;
    case 1:
        rec = D_L12_001B2E9C + (s[1] << 8);
        if (rec[0x31] != 0) {
            phase = IntToFloat(D_L12_001B29C8 % 50);
            d = IntToFloat(50);
            phase *= 6.2831855f;
            phase /= d;
            *(s32 *)(rec + 0x78) = PulseColor(0x802020A0, 0x80202050, phase - 3.1415927f);
        }
        if (s[0] == -1)
            break;
        obj = D_L12_001B090C;
        if (obj != 0) {
            if (IsPointInCuboid(obj + 0x10, s[0])) {
                *(s32 *)(rec + 0x78) = 0x80A02020;
                moby_set_state(a0, 2, -1);
                if (s[2] != -1)
                    moby_set_flag_bit(D_L12_001B2E9C + (s[2] << 8), 1);
            }
        } else if (second_tracked_object_is_open()) {
            if (IsPointInCuboid(D_L12_001B1360 + 0x10, s[0])) {
                *(s32 *)(rec + 0x78) = 0x80A02020;
                moby_set_state(a0, 2, -1);
                if (s[2] != -1)
                    moby_set_flag_bit(D_L12_001B2E9C + (s[2] << 8), 1);
            }
        }
        break;
    }
}

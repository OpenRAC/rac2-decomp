#include "include_asm.h"

typedef unsigned char u8;
typedef float f32;
typedef int s32;

/* func_PAL_L22_003CD550, the PAL copy of func_L22_003C9880: the same C, where the rate
 * becomes 1/50, the phase step 0.0003490659f, the 1080 window 900, and every read of the
 * clock D_001A7390 is scaled to 50 Hz.  The window test reads history[31].time after the
 * scaling (retail's load follows the division's zero check), not through a local. */
extern float D_L22_001AFF08[] __attribute__((sda));
extern float D_L22_001AFF10[] __attribute__((sda));
extern int D_L22_001AFF18[] __attribute__((sda));
extern int D_L22_001AFF18_gp[] __asm__("D_L22_001AFF18__gp") __attribute__((section(".sdata")));
extern float D_L22_001AFF20[] __attribute__((sda));
extern float D_L22_001A7CD8[] __attribute__((sda));
extern unsigned int D_001A7390[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));

/* The per-subtitle history src/game/00289178.c updates (12-byte rows). */
typedef struct {
    unsigned short count, pad;
    unsigned int time, levels;
} SubtitleHistory;
extern SubtitleHistory D_0018C958[];

extern void func_002A7750(void *, int, int);
extern f32 func_002A7878(f32 low, f32 high);
extern int func_002E5CF8(int index, int a1, char *a2);
extern void func_00288E18(int, int);
extern f32 func_00282DB0(void *, void *);
extern void func_PAL_L22_003CD898(char *);
extern void func_L22_003C9D48(u8 *);
extern void func_L00_002E6CF0(void (*)(u8 *), void *);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283198(f32);
extern int func_00283D38(int, int, f32);
extern u8 D_00189E20[];
extern f32 func_00282E48(void *a0, void *a1);

void func_PAL_L22_003CD550(u8 *obj)
{
    u8 *ctl = *(u8 **)(obj + 0x68);
    int state = obj[0x20];
    int i;

    switch (state) {
    case 0:
        func_002A7750(obj, 1, -1);
        *(short *)(obj + 0x32) = 255;
        {
            float *offset, *rate, *radius;
            i = 0;
            radius = (float *)(ctl + 0x10);
            rate = (float *)(ctl + 0x30);
            offset = (float *)(ctl + 0x20);
            for (; i < 4; i++) {
                *offset++ = (float)i * 0.25f;
                *rate++ = func_002A7878(D_L22_001AFF08[0], D_L22_001AFF08[1]) * 0.020000001f;
                *radius++ = func_002A7878(D_L22_001AFF10[0], D_L22_001AFF10[1]);
            }
        }
        break;
    case 1: {
        u8 *player;
        SubtitleHistory *history;

        if (func_00282E48(D_00189E20 + 0x80, obj + 0x10) < 3.0f)
            D_L22_001A7CD8[0] = *(float *)ctl;
        player = D_00189E20;
        if (*(int *)(player + 0x2294) == 0x81 && *(int *)(player + 0x1B8) == state)
            func_002E5CF8(0, 0, (char *)obj);
        history = D_0018C958;
        {
            /* unsigned int snapshot: retail tests the u16 with an andi and
             * increments the unmasked value */
            unsigned int count = history[31].count;
            if ((unsigned short)count <= 65534) {
                u8 *player2 = D_00189E20;
                if (*(int *)(player2 + 0x2294) == 0x81)
                    history[31].count = 65535;
                else if (*(u8 **)(player2 + 0x33C) == obj) {
                    /* each arm reads the clock itself: reorg merges the two
                     * reads into the branch's delay slot */
                    if ((unsigned short)count != 0) {
                        if (((s32)D_001A7390[0] * 5 + 2) / 6 - history[31].time > 900 || history[31].time == 0)
                            func_00288E18(2504, 31);
                        else if (history[31].time < ((s32)D_001A7390[0] * 5 + 2) / 6)
                            history[31].time = ((s32)D_001A7390[0] * 5 + 2) / 6;
                    } else {
                        history[31].count = count + 1;
                        if (history[31].time < ((s32)D_001A7390[0] * 5 + 2) / 6)
                            history[31].time = ((s32)D_001A7390[0] * 5 + 2) / 6;
                        history[31].levels =
                            (history[31].levels | (1 << D_001A79F0[0])) | 0x80000000;
                    }
                }
            }
        }
        if (func_00282DB0(obj + 0xE0, D_00189E20 + 0x2C0) < -0.6f) {
            func_PAL_L22_003CD898((char *)obj);
            func_L00_002E6CF0(func_L22_003C9D48, obj);
        }
        break;
    }
    }
    if (obj[0x31]) {
        float f;
        *(float *)(ctl + 4) = func_00283B98(*(float *)(ctl + 4),
                                            D_L22_001AFF20[0] * 0.0003490659f);
        f = func_00283198(*(float *)(ctl + 4));
        f = f * f;
        f = f * f;
        *(int *)(obj + 0x78) = func_00283D38(D_L22_001AFF18_gp[0], D_L22_001AFF18[1], f * f);
    }
}


#include "common.h"

extern u8 *D_L12_001B2E9C __attribute__((sda));

/* The subtitle history (src/game/00289178.c): per record, its play count, the time it was last
   played and the levels it was played in (bit 31: played at all). */
typedef struct {
    unsigned short count, pad;
    unsigned int time, levels;
} SubtitleHistory;

extern void func_002A7750(void *, int, int);
extern int func_PAL_00289730(int, int);

extern u8 D_00189EA0[];
extern SubtitleHistory D_0018C958[];
extern u8 D_001A7AF8[] __attribute__((sda));
extern u32 D_001A7390;
extern int D_001A79F0[] __attribute__((sda));
extern int D_0018C0B4 NOT_SDA;
extern int func_002ACBC8(void *, int);
extern void func_00282948(void *);

/* func_PAL_L12_003EF838, the PAL copy of func_L12_003EB470: the same C, where func_00288E18
   becomes func_PAL_00289730, the 0x438 and 0x2A30 frame counts become 0x384 and 0x2328, and
   D_001A7390 is scaled to 50 Hz wherever it is read. Plays subtitle lines, each gated on its
   record in the subtitle history (the record index is the second argument of the call). */
void func_PAL_L12_003EF838(u8 *o) {
    u8 *d = *(u8 **)(o + 0x68);

    switch (o[0x20]) {
    case 0:
        o[0x30] = 255;
        *(int *)(d + 0x10) = -1;
        func_002A7750(o, 1, -1);
        break;
    case 1:
        if (func_002ACBC8(D_00189EA0, *(int *)d) && *(int *)(D_00189EA0 + 0x540)
            && !D_0018C958[121].count)
            func_PAL_00289730(0xA22, 121);
        if (func_002ACBC8(D_00189EA0, *(int *)(d + 4)) && !D_001A7AF8[0x33]) {
            if (D_0018C958[92].count) {
                if (((s32)D_001A7390 * 5 + 2) / 6 - D_0018C958[92].time > 0x384
                    || D_0018C958[92].time == 0)
                    func_PAL_00289730(0xA05, 92);
                else if (D_0018C958[92].time < ((s32)D_001A7390 * 5 + 2) / 6)
                    D_0018C958[92].time = ((s32)D_001A7390 * 5 + 2) / 6;
            } else {
                if (D_0018C958[92].count < 65535)
                    D_0018C958[92].count++;
                if (D_0018C958[92].time < ((s32)D_001A7390 * 5 + 2) / 6)
                    D_0018C958[92].time = ((s32)D_001A7390 * 5 + 2) / 6;
                D_0018C958[92].levels = (D_0018C958[92].levels | (1u << D_001A79F0[0])) | 0x80000000u;
            }
        }
        if (func_002ACBC8(D_00189EA0, *(int *)(d + 8))) {
            u8 *p = D_L12_001B2E9C + (*(int *)(d + 0xC) << 8);

            if (p && *(s16 *)(p + 0xAA) == 0xFB8 && p[0x20] != 254 && p[0x20] != 253) {
                if (*(int *)(d + 0x10) < 0)
                    *(int *)(d + 0x10) = 0x2328;
                else if (!*(int *)(d + 0x10)) {
                    u32 seen = D_0018C958[93].levels & (1 << D_001A79F0[0]);

                    if (!seen)
                        func_PAL_00289730(0xA06, 93);
                }
            }
        }
        if (D_001A7AF8[7] && D_0018C0B4 != 0x6F) {
            u32 seen = D_0018C958[127].levels & (1 << D_001A79F0[0]);

            if (!seen)
                func_PAL_00289730(0xA28, 127);
        }
        if (*(int *)(d + 0x10) >= 0)
            func_00282948(d + 0x10);
        break;
    }
}

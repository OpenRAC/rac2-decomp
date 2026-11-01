#include "include_asm.h"

#include "common.h"
typedef struct Task28E458 {
    u8 pad00[0x18];
    void (*update)(struct Task28E458 *);
    u8 pad1C[0x90 - 0x1C];
} Task28E458;
extern s32 D_001B18A4[] __attribute__((sda));
extern s32 D_001B15A8[] __attribute__((sda));
extern s32 D_001B187C[] __attribute__((sda));
extern s32 D_001B17B0[] __attribute__((sda));
extern s32 D_001B17B4[] __attribute__((sda));
extern s32 D_001B17B8[] __attribute__((sda));
extern s32 D_001A8BB0[] __attribute__((sda));
extern Task28E458 D_00255330[];

void func_PAL_0028ECD8(void) {
    Task28E458 *t;
    s32 i;

    if (D_001B18A4[1] != 0 || D_001B15A8[0] != 0) {
        D_001B18A4[1] = 0;
        return;
    }
    t = D_00255330;
    D_001B187C[0] = 0xFFFFF0;
    for (i = 12; i >= 0; i--) {
        if (t->update != 0) {
            t->update(t);
        }
        t++;
    }
    if ((D_001B17B0[0] != 0 || D_001B17B4[0] != 0) && D_001A8BB0[0] == 0) {
        if (D_001B17B0[0] != 0) {
            D_001B17B4[0] += 0x12;
            if (D_001B17B4[0] > 0x80) {
                D_001B17B4[0] = 0x80;
            }
        } else {
            D_001B17B4[0] -= 0x12;
            if (D_001B17B4[0] < 0) {
                D_001B17B4[0] = 0;
            }
        }
        if (D_001B17B0[0] != 0) {
            D_001B17B0[0]--;
        }
        if (D_001B17B0[0] == 1000) {
            D_001B17B0[0] = 0;
        }
    } else {
        D_001B17B8[0] = 100;
    }
}

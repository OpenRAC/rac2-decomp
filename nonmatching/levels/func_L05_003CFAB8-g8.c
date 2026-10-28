/* Complete C near miss; NOT linked and no exact-C credit.
 * Measured source unit: src/levels/shared/L05_003CFAB8-g8.c
 * Game profile: -O2 -G8 -ffunction-sections
 * Compiled/retail bytes: 216/212. US: 0/2; US2: 0/2; PAL: ABSENT.
 * Residual and reopening condition: The truthful incomplete reach-table array adds one address instruction; the old scalar declaration understated the table. The sound call now has its real integer return. Tail state-pointer/counter allocation and three-store ordering remain open. Reopen with measured complete table extent and a documented per-file threshold.
 * Field views describe only measured prefixes, not complete game-object extents.
 */

#include "common.h"
extern int func_L05_003CFC28(int);
extern void func_L05_003CFB90(char *, char *);
extern float func_00282E48(char *, char *);
extern int func_002E5DA0(int, int, char *, int);

extern float D_L05_001AFB68[] __attribute__((sda));
extern char D_L05_001B96C0[];

struct S_L05_003CFAB8 {
    char pad0[0x160];
    float f160;
    int f164;
    int f168;
    int f16C;
};

void func_L05_003CFAB8(char *a0)
{
    char *s0 = a0;
    char *s1;
    struct S_L05_003CFAB8 *t;
    float f20;
    float f0;
    int v1;
    int idx;

    idx = func_L05_003CFC28(*(short *)(s0 + 0xAA));
    f20 = *(float *)((char *)D_L05_001AFB68 + 4 * idx);
    s1 = D_L05_001B96C0;
    if (func_00282E48(s0 + 0x10, s1) <= f20) {
        if (*(short *)(s0 + 0xAA) != 0x956) {
            func_L05_003CFB90(s0, s1);
            func_002E5DA0(7, 0, s0, 0xFBF);
            t = (struct S_L05_003CFAB8 *)(s1 - 0x140);
            if (*(short *)(s0 + 0xAA) == 0x955) {
                f0 = 0.05f;
                v1 = 0x1E;
            } else {
                f0 = 0.15f;
                v1 = 0x3C;
            }
            t->f16C = 0;
            t->f160 = f0;
            t->f168 = v1;
        }
    }
}

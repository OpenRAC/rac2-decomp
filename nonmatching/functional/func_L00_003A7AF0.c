/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high, 29 October 2026; retained near miss.
 * USA v1.01: 324/320 bytes, 0/27 places; ten checker runs in this task.
 * Profile: -O2 -G8 -ffunction-sections -mno-split-addresses -fno-gcse.
 * Splitting the final config paths with a real early return reduces the prior
 * 328-byte draft to 324 bytes. The table-fill loop remains exact in the diff.
 * Remaining: the state +36 sentinel store moves ahead of the zero stores;
 * final scalar config stores use different FP lifetimes, ordering and branches.
 * The first raw instruction difference is +0x38. Equal behavior is not a match.
 * Typed state fields, swapping sentinel source order, preloading the final tag,
 * reversed/duplicated config arms, ordinary split addresses, keep-block-order
 * and disabling the first scheduler did not close these differences.
 * Next: independently evidenced state/config layout and final CFG lifetimes.
 * All required declarations are below; the ref symbol is the GP config view.
 */
#include "include_asm.h"
extern float D_L00_001B2868 __attribute__((section(".data")));
extern float D_L00_001B286C __attribute__((section(".data")));
extern float D_L00_001B2870 __attribute__((section(".data")));
extern float D_L00_001B286C __attribute__((sda));
extern int D_L00_001AF6C4 __attribute__((sda));
extern int D_L00_001AF6CC __attribute__((sda));
extern int func_L00_00329E90(char *, int, void *);
extern char *func_L00_0032A088(int, int);
extern int func_L00_00329FF0(int);

void func_L00_003A7AF0(char *object)
{
    char *state = *(char **)(object + 0x68);
    int local[4];
    int value, i;
    int index;
    int *table;
    *(short *)(state + 4) = -1;
    *(float *)(state + 12) = 0.1f;
    *(int *)(state + 60) = -1;
    *(int *)(state + 0) = 0;
    *(short *)(state + 6) = 0;
    *(short *)(state + 16) = 0;
    *(int *)(state + 8) = 0;
    *(int *)(state + 36) = -1;
    *(int *)(state + 40) = 0;
    *(int *)(state + 44) = 0;
    *(int *)(state + 48) = 0;
    if (*(short *)(object + 0xAA) == 1490)
        *(int *)(state + 52) = D_L00_001AF6C4;
    else
        *(int *)(state + 52) = D_L00_001AF6CC;
    *(unsigned int *)(object + 0x78) = 0xFF0020FF;
    index = func_L00_00329E90(object, 0, local);
    *(short *)(state + 18) = index;
    if (local[0] == 0) {
        table = (int *)func_L00_0032A088(*(short *)(object + 0xAA), (short)index);
        value = func_L00_00329FF0((int)(table + 16));
        for (i = 15; i >= 0; --i) {
            *table = value;
            value += 640;
            table++;
        }
    }
    D_L00_001B2868 = 0.104719766f;
    if (*(short *)(object + 0xAA) == 1490) {
        D_L00_001B286C = 20.0f;
        D_L00_001B2870 = 0.104719766f;
        return;
    }
    D_L00_001B286C = 30.0f;
    D_L00_001B2870 = 0.104719766f;
}

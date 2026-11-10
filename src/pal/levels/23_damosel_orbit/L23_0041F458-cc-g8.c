/* func_PAL_L23_0041F458, the PAL copy of func_L23_0041A3B8: the same C, where rename func_L23_00422540 becomes func_PAL_L23_00427920; rename func_L23_0041BF18 becomes func_PAL_L23_00420FF8; rename func_L23_004280D8 becomes func_PAL_L23_0042D620; rename func_0032C700 becomes func_PAL_L00_003FB330. */
/* func_PAL_L23_0041F458: Damosel effect trigger. Kind 0xF objects spawn the burst at
   D_L23_001B3850 along the object's state direction and play sound 0x21; kinds 0x10 and
   0xC, once the timer threshold is reached and the blink mask is full, aim it at arg1 and
   play sound 0x1A (with the explosion) or 0x21. Returns 1 when the object was handled.

   The kind 0xF arm groups its effect in a nonempty one-pass statement, as current RAC1 game
   C does (docs/build/compiler-notes.md, source methods shared with RAC1): its loop notes keep the
   `la` of D_L23_001B3850 ahead of the two frame-address arguments. func_L00_0035F5A0 returns
   int, as its matched definition does. -mno-split-addresses keeps retail's adjacent
   lui/addiu pairs; D_L23_001B3850 is MACRO_ADDR so each use rematerializes its address. */

#include "common.h"

extern float D_L23_001B3728 __attribute__((sda));

extern float D_L23_001B1454 __attribute__((sda));

extern int D_L23_001B3784;

extern char D_L23_001B3850[] MACRO_ADDR;

extern char D_L23_001B3870[];

extern void func_00282F20(char *, char *, float);

extern void func_00282CF0(char *, char *, char *);

extern char *func_PAL_L23_00427920(char *, char *, float *);

extern unsigned char *func_PAL_L23_0042D620(char *, char *, char *, int, float);

extern int func_L00_0035F5A0(int, int, int);

extern char *func_PAL_L00_003FB330(char *, int, int, int, int, int, int, int, float, float, int, int, int, char *);

extern void func_PAL_L23_00420FF8(char *, float, float);

int func_PAL_L23_0041F458(char *arg0, char *arg1) {
    char *state = *(char **)(arg0 + 0x68);
    float tmp;
    float vec[4];
    int kind = *(unsigned char *)(arg0 + 0x20);

    if (kind != 0xF) {
        if (kind == 0x10 || kind == 0xC) {
            if (D_L23_001B3784 == 0)
                return 0;
        } else
            return 0;
    } else {
        if ((*(unsigned short *)(arg0 + 0x96) & 3) != 2)
            return 1;
        do {
            func_00282F20((char *)vec, D_L23_001B3870, *(short *)(state + 0x33A) * 0.020000001f);
            tmp = *(float *)(state + 0x300) * 1.5f;
            func_PAL_L23_00427920(D_L23_001B3850, (char *)vec, &tmp);
        } while (0);
        func_L00_0035F5A0(0x21, 0, 0);
        return 1;
    }
    if (!(D_L23_001B3728 >= D_L23_001B1454))
        return 1;
    func_PAL_L23_00420FF8(arg0, 2.0f, 2.0f);
    if (*(unsigned char *)(arg0 + 0x20) == 0x10) {
        int m = *(short *)(state + 0x336);
        if ((*(unsigned short *)(arg0 + 0x96) & ((1 << (9 - m)) - 1)) != ((1 << (9 - m)) - 1))
            return 1;
        func_00282CF0((char *)vec, arg1, D_L23_001B3850);
        func_00282F20((char *)vec, (char *)vec, *(short *)(state + 0x33C) * 0.020000001f);
        func_PAL_L23_0042D620(arg0, (char *)vec, D_L23_001B3850, 0, *(float *)(state + 0x304));
        func_PAL_L00_003FB330(D_L23_001B3850, 0, 2, 3, 2, 2, 0xA, 0, 0.5f, 20.0f, 1, 1, 0, 0);
        func_L00_0035F5A0(0x1A, 0, 0);
    } else {
        int m = *(short *)(state + 0x334);
        if ((*(unsigned short *)(arg0 + 0x96) & ((1 << (9 - m)) - 1)) != ((1 << (9 - m)) - 1))
            return 1;
        func_00282CF0((char *)vec, arg1, D_L23_001B3870);
        func_00282F20((char *)vec, (char *)vec, *(short *)(state + 0x33A) * 0.020000001f);
        func_PAL_L23_00427920(D_L23_001B3850, (char *)vec, (float *)(state + 0x300));
        func_L00_0035F5A0(0x21, 0, 0);
    }
    return 1;
}

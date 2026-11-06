/* func_PAL_L11_0044B820, the PAL copy of func_L11_00445DF8: the same C, where scale ref_L11_00445DF8_04 + func_002A77E0(ref_L11_00445DF8_04). */
#include "common.h"

extern const float ref_L11_00445DF8_00 __attribute__((sda));
extern const s32 ref_L11_00445DF8_01 __attribute__((sda));
extern float ref_L11_00445DF8_02 __attribute__((sda));
extern float ref_L11_00445DF8_03 __attribute__((sda));
extern s32 ref_L11_00445DF8_04 __attribute__((sda));
extern s32 D_001A7A00;
extern char D_001A63A8[];
extern char D_00189E20[];
extern s32 func_00282948(void *);
extern s32 func_002A77E0(s32);
extern int func_L11_00445D28(char *, int);

void func_PAL_L11_0044B820(char *a0, s32 a1, float a2, float a3) {
    char *state = *(char **)(a0 + 0x68);
    char *g = D_001A63A8;
    char *hero;
    char *hero2;
    s32 id23;
    s32 id24;
    s32 off;
    s32 list[12];
    s32 *lp;
    s32 n;
    s32 j;
    s32 k;
    s32 count;
    float acc;

    if (*(s32 *)(g + 0x68) != 0)
        return;
    if (*(s32 *)(g + 0x24) != -1)
        return;
    if (*(s32 *)(state + 0x190) != 0)
        return;
    n = 0;
    acc = *(float *)(state + 0x194) + a2;
    count = *(s32 *)(state + 0x198) + a1;
    *(s32 *)(state + 0x198) = count;
    *(float *)(state + 0x194) = acc;
    if (ref_L11_00445DF8_00 < acc || ref_L11_00445DF8_01 < count) {
        lp = list;
        for (j = 0; j < 4; j++) {
            s32 id;

            id = j + 0x14;
            if (*(s16 *)(state + 0x2A0 + id * 2) == 0)
                lp[n++] = id;
        }
        *(s32 *)(state + 0x198) = 0;
        *(s32 *)(state + 0x194) = 0;
    }
    if (func_00282948(state + 0x1B0) != 0) {
        *(s32 *)(state + 0x198) = 0;
        *(s32 *)(state + 0x1B0) = 250;
        *(s32 *)(state + 0x194) = 0;
    }
    if (ref_L11_00445DF8_02 < a3) {
        lp = list;
        for (k = 0; k < 2; k++) {
            s32 id = k + 0x12;

            if (*(s16 *)(state + 0x2A0 + id * 2) == 0)
                lp[n++] = id;
        }
    }
    hero = D_00189E20;
    if ((float)*(s32 *)(hero + 0x24CC) < (float)D_001A7A00 * ref_L11_00445DF8_03) {
        id23 = 0x18;
        if (*(s16 *)(state + 0x2D0) == 0)
            list[n++] = id23;
    }
    hero2 = D_00189E20;
    if (*(s32 *)(hero2 + 0x24CC) <= 0) {
        id24 = func_002A77E0(2) + 0x19;
        off = id24 * 2;
        if (*(s16 *)(state + off + 0x2A0) == 0)
            list[n++] = id24;
    }
    if (n != 0) {
        func_L11_00445D28(a0, list[func_002A77E0(n)]);
        *(s32 *)(state + 0x190) = (((int)(ref_L11_00445DF8_04 + func_002A77E0(ref_L11_00445DF8_04)) * 5 + 2) / 6);
    }
}

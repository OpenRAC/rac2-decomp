#include "common.h"

/* func_L23_0041CD58 is a unit of its own: it reads $gp data and needs the opt-in quadword-copy
   profile and its scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt).
   The one MACRO_ADDR count gives retail's absolute reads and its $gp write in a branch's delay
   slot. The row pointer is a local so its address lives long enough for loop.c to move it out
   of the first, 83-instruction loop; taken inline, only its %hi is hoisted. */

typedef int TI128 __attribute__((mode(TI)));

extern char *D_L23_001B1484 __attribute__((sda));
extern char D_00189E20[];
extern s32 D_L23_00259050[3][60];
extern s32 D_L23_001B3738[3] __attribute__((sda));
extern s32 D_L23_001B3744 MACRO_ADDR;
extern float D_L23_001B1414 __attribute__((sda));
extern TI128 D_L23_001C0AA0;
extern float func_00282E48(char *, char *);
extern int func_L23_0041D1F0(char *, int, int, int);
extern void func_002A7750(unsigned char *, unsigned char, int);
extern float func_L23_0041E220(char *);
extern int func_002A77E0(int);
extern int func_L23_0041D0A0(char *, int, float);
extern void func_00282D30(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern void func_L23_00418650(char *, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_L23_0041C7D8(void *, int);

/* Refresh the active effect pools, then choose a new free spawn position. */
void func_L23_0041CD58(char *object) {
    TI128 loc[2];
    TI128 *offset;
    char *state = *(char **)(D_L23_001B1484 + 0x68);
    int group = 0;
    int remaining;
    int next;
    int oldCount;
    int oldTotal;
    int spawnGroup;
    char **slot;
    char **spawnSlot;
    s32 *count;
    float alpha;
    char *axis;
    float scale;
    do {
        s32 (*rows)[60] = D_L23_00259050;

        count = &D_L23_001B3738[group];
        slot = (char **)rows[group];
        next = group + 1;
        remaining = 49;
        do {
            if (*slot && *(float *)(state + 0x20) > 0.0f) {
                char *hero = D_00189E20;

                if ((*(unsigned char **)(hero + 0x2290))[0x43] != 6 && fast_vec_dist(*slot + 0x10, hero + 0x80) < 12.0f) {
                    if (func_L23_0041D1F0(object, (int)*slot, group, 1)) {
                        if (((unsigned char *)*slot)[0x20] == 0) {
                            func_002A7750((unsigned char *)*slot, 16, 0);
                            (*slot)[0x23] = 127;
                        }
                        oldCount = *count;
                        oldTotal = D_L23_001B3744;
                        *slot = 0;
                        *count = oldCount - 1;
                        D_L23_001B3744 = oldTotal - 1;
                    } else {
                        alpha = func_L23_0041E220(*slot) * 0.083333336f;
                        if (alpha > 1.0f) alpha = 1.0f;
                        else if (alpha < 0.1f) alpha = 0.1f;
                        (*slot)[0x23] = (int)(alpha * 127.0f);
                    }
                }
            }
            remaining--;
            slot++;
        } while (remaining >= 0);
        group = next;
    } while (group < 3);
    if (!func_002A77E0(30) && D_L23_001B3744 < 12) {
        func_L23_0041D0A0((char *)&loc[0], 1, 0.0f);
        offset = &loc[1];
        spawnGroup = 0;
        do {
            spawnSlot = (char **)D_L23_00259050[spawnGroup];
            next = spawnGroup + 1;
            remaining = 49;
            do {
                if (*spawnSlot && fast_vec_dist(*spawnSlot + 16, (char *)&loc[0]) < 4.0f) {
                    axis = *spawnSlot + (func_002A77E0(2) * 16 + 0xC0);
                    if (func_002A77E0(2)) scale = D_L23_001B1414;
                    else scale = -D_L23_001B1414;
                    FastVecScale((char *)offset, axis, scale);
                    FastVecAdd((char *)&loc[0], (char *)&loc[0], (char *)offset);
                    func_L23_00418650((char *)&loc[0], 0.0f);
                }
                remaining--;
                spawnSlot++;
            } while (remaining >= 0);
            spawnGroup = next;
        } while (spawnGroup < 3);
        *offset = loc[0];
        func_L23_00418650((char *)offset, 3.0f);
        if (CollLine(offset, &loc[0], 18, 0, 0))
            loc[0] = D_L23_001C0AA0;
        func_L23_0041C7D8(&loc[0], 0);
    }
}

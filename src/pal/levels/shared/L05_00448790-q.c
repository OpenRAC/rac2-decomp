#include "include_asm.h"

#include "common.h"
extern char *D_L05_001B1EC4 MACRO_ADDR;
extern char *D_L05_001B251C MACRO_ADDR;
extern char *D_L05_001B260C MACRO_ADDR;
extern char D_L05_001B3600[] MACRO_ADDR;
extern float func_00282E48(char *, char *);
extern void func_00282F20(char *, char *, float);
extern s32 func_002A77E0(s32);
extern void func_PAL_L05_00449A28(char *);
extern void func_L05_004427A8(void);

/* Picks the best-scoring of the entity's nine slots (or the runner-up on a random draw), copies
   its transform to the object and to the entity, and resets the object. */
void func_PAL_L05_00448790(char *obj)
{
    char *entry = *(char **)(D_L05_001B1EC4 + *(short *)(obj + 0x84) * 32 + 0x1C);
    char *self = D_L05_001B251C + (*(s32 *)(entry + 0x20) << 8);
    char *state = *(char **)(self + 0x68);
    s32 best = -1;
    s32 second = -1;
    float next = 0.0f;
    float top = 0.0f;
    s32 i;
    s32 pick;
    char *rec;

    for (i = 0; i < 9; i++) {
        s32 *slot = (s32 *)(state + 0x21C) + i;
        if (*slot >= 0) {
            float score = func_00282E48(self + 0x10, D_L05_001B260C + (*slot << 7) + 0x30);
            if (top < score) {
                next = top;
                second = best;
                top = score;
                best = *slot;
            } else if (next < score) {
                second = *slot;
                next = score;
            }
        }
    }
    pick = best;
    if (func_002A77E0(2) != 0)
        pick = second >= 0 ? second : pick;
    rec = D_L05_001B260C + (pick << 7);
    qcopy(obj + 0x30, rec + 0x30);
    qcopy(D_L05_001B3600, obj + 0x30);
    qcopy(self + 0x10, obj + 0x30);
    func_00282F20(obj, rec, 1.0f);
    func_00282F20(obj + 0x10, rec + 0x10, 1.0f);
    func_00282F20(obj + 0x20, rec + 0x20, 1.0f);
    qzero(*(char **)(obj + 0x70) + 0xB0);
    func_PAL_L05_00449A28(obj);
    func_L05_004427A8();
}

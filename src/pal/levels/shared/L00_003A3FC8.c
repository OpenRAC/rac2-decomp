#include "include_asm.h"

/* func_PAL_L00_003A3FC8 is defined in L00_003A3FC8-tile.c. */

extern int D_0018C0B4;
extern char *D_L00_001B1EA8[] __attribute__((sda));
extern char *D_001FDA80[];
extern int D_001A8A44 __attribute__((sda));
extern char D_L00_003A09F8[];
extern int func_002A8AF0(char *a, char *b, int c);
extern int func_002ACBC8(char *a, int b);
extern void ref_L00_003A0C00_00(char *a, char *b);
extern void func_L00_00391310(char *a, char *b);

/* Marks the object not drawable, finds the first object of the global list with id 0xAC and
   counts one more frame in the object's state; checks the sixteen-byte regions of the state
   against the target's position and releases the count as soon as one holds. */
void func_PAL_L00_003A41D0(char *object)
{
    char *state;
    char *target = 0;
    char *p;
    char *e;
    char *pos;
    int none;

    *(unsigned char *)(object + 0x30) = 0xFF;
    state = *(char **)(object + 0x68);
    if (D_0018C0B4 != 0x1C)
        goto reset;
    for (p = D_L00_001B1EA8[0]; p != 0; p = *(char **)(p + 0x28)) {
        if (*(short *)(p + 0xAA) == 0xAC) {
            target = p;
            break;
        }
    }
    if (target == 0 || *(short *)(target + 0xAA) != 0xAC) {
reset:
        *(int *)(state + 0x140) = 0;
        return;
    }
    pos = target + 0x10;
    none = -1;
    *(int *)(state + 0x140) = *(int *)(state + 0x140) + 1;
    e = state;
    do {
        if (*(int *)e != none && *(float *)(target + 0x18) > *(float *)(e + 4) &&
            *(float *)(target + 0x18) < *(float *)(e + 8)) {
            char *t = D_001FDA80[*(int *)e];
            if (func_002A8AF0(pos, t + 0x10, *(int *)t) != 0) {
                *(int *)(state + 0x140) = 0;
                break;
            }
        }
        if (func_002ACBC8(pos, *(int *)(e + 0xC)) != 0) {
            *(int *)(state + 0x140) = 0;
            break;
        }
        e += 0x10;
    } while ((int)e < (int)state + 0x140);
    if (*(int *)(state + 0x140) > 0) {
        if (D_001A8A44 != 0)
            ref_L00_003A0C00_00(D_L00_003A09F8, object);
        if (*(int *)(state + 0x140) >= 0x4C)
            func_L00_00391310(target, *(char **)(target + 0x68));
    }
}


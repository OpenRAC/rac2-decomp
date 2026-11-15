#include "include_asm.h"
#include "common.h"

/* -G8 unit for func_00325DA0, which reads D_001B1688 and D_001B1B5C absolutely and
   D_001B1B78 through $gp (0031F210-g8.c declares D_001B1B5C sda). func_00325D30, its
   neighbour in retail, must stay in front of it: this cc1's combine does not reset
   mem_last_set before its nonzero-bits scan, so the previous function's last store or
   call leaves the group byte's first load unproven, and the loop test keeps retail's
   `andi $v1,$a3,0xFF`. Compiled alone, the mask folds away and the body is 4 bytes short. */

extern void func_0029F338(void *);

/* Removes the two attached part objects of the given entries. */
void func_00325D30(char *object, char *entries)
{
    int count = 1;
    do {
        char *child = *(char **)entries;
        count--;
        entries += 4;
        if (child != 0 && *(short *)(child + 0xAA) == 0xAA2 /* moby class 2722 */)
            MarkMobySpawned(child);
    } while (count >= 0);
}

extern int D_001B1688;
extern char *D_001B1B5C;
extern int D_001B1B78 MACRO_ADDR;
extern unsigned short *D_001EE5A0[];
extern void func_00325EC0(char *);
extern void func_0027CFD0(void (*)(char *), char *);

/* Copies a shared counter value to every member of the object's group that has the same kind. It then schedules the group's glow effects. */
void func_00325DA0(unsigned char *object, int *field)
{
    unsigned short *p;
    unsigned char *e;
    int offset;

    if (*field != gGameTime) {
        if (object[0x21] == 0xFF) {
            *field = gGameTime;
        } else {
            offset = (char *)field - *(char **)(object + 0x68);
            for (p = D_001EE5A0[object[0x21]];
                 object[0x21] != 0xFF && object[0x21] <= D_001B1B78 && p != 0 &&
                 ((p != 0 && (short)p[-1] >= 0) || p == D_001EE5A0[object[0x21]]);
                 p++) {
                e = (unsigned char *)D_001B1B5C + ((*p & 0x7FFF) << 8);
                if (e == 0)
                    break;
                if (*(short *)(e + 0xAA) == *(short *)(object + 0xAA))
                    *(int *)(*(char **)(e + 0x68) + ((offset >> 2) << 2)) = gGameTime;
            }
        }
        RegisterOverlayDrawCallback(DrawGroupJointGlows, (char *)object);
    }
}

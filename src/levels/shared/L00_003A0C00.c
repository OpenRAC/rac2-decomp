#include "include_asm.h"
#include "names.h"

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
void func_L00_003A0C00(char *object)
{
    char *state;
    char *target = 0;
    char *node;
    char *slot;
    char *pos;
    int none;

    *(unsigned char *)(object + 0x30) = 0xFF;
    state = *(char **)(object + 0x68);
    if (D_0018C0B4 != 0x1C)
        goto reset;
    for (node = D_L00_001B1EA8[0]; node != 0; node = *(char **)(node + 0x28)) {
        if (*(short *)(node + 0xAA) == 0xAC /* Visibomb Missile */) {
            target = node;
            break;
        }
    }
    if (target == 0 || *(short *)(target + 0xAA) != 0xAC /* Visibomb Missile */) {
reset:
        *(int *)(state + 0x140) = 0;
        return;
    }
    pos = target + 0x10;
    none = -1;
    *(int *)(state + 0x140) = *(int *)(state + 0x140) + 1;
    slot = state;
    do {
        if (*(int *)slot != none && *(float *)(target + 0x18) > *(float *)(slot + 4) &&
            *(float *)(target + 0x18) < *(float *)(slot + 8)) {
            char *other = D_001FDA80[*(int *)slot];
            if (point_in_path_xy(pos, other + 0x10, *(int *)other) != 0) {
                *(int *)(state + 0x140) = 0;
                break;
            }
        }
        if (IsPointInCuboid(pos, *(int *)(slot + 0xC)) != 0) {
            *(int *)(state + 0x140) = 0;
            break;
        }
        slot += 0x10;
    } while ((int)slot < (int)state + 0x140);
    if (*(int *)(state + 0x140) > 0) {
        if (D_001A8A44 != 0)
            ref_L00_003A0C00_00(D_L00_003A09F8, object);
        if (*(int *)(state + 0x140) >= 0x5B)
            ReleaseTether(target, *(char **)(target + 0x68));
    }
}

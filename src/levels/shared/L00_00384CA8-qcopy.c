#include "include_asm.h"
#include "names.h"

/* func_L00_00384CA8 is a unit of its own: the two sixteen-byte blocks the level
   copies need the opt-in grouped quadword-copy profile (-frac2-qcopy
   -frac2-qcopy-barrier, config/cflags.txt), which gives retail's grouped
   `lq $v0,0($s3) ; sq $v0,0($a0)` and `lq $v0,0($s4) ; sq $v0,0($v1)` with both
   addresses in registers, and holds the copies in front of the call's argument
   moves. */

typedef int L00_00384CA8_TI128 __attribute__((mode(TI)));

extern void *func_0029EFD0(int id);
extern void func_002A7750(void *object, unsigned char mode, int value);

/* Creates the object the level names, fills its fields and its two sixteen-byte
   blocks, then hands it to the shared setup. */
void *func_L00_00384CA8(void *owner, void *position, void *velocity, unsigned int index)
{
    char *object = (char *)CreateMoby(0x1335 /* moby class 4917 */);
    char *child;

    if (object != 0) {
        child = *(char **)(object + 0x68);
        *(void **)(object + 0xB8) = owner;
        *(unsigned char *)(object + 0x30) = 0xFF;
        *(unsigned char *)(object + 0xBC) = index;
        *(L00_00384CA8_TI128 *)(object + 0x10) = *(L00_00384CA8_TI128 *)position;
        *(L00_00384CA8_TI128 *)child = *(L00_00384CA8_TI128 *)velocity;
        SetMobyState(object, 2, -1);
    }
    return object;
}

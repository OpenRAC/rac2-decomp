#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef int TI128 __attribute__((mode(TI)));
extern u8 *func_0029EFD0(int);

/* The func_L02_003A8770 spawn for a live owner: the child is bound to the owner and
   starts at its position. */
u8 *func_00312E20(u8 *owner, int type) {
    u8 *object;
    u8 *data;
    if ((signed char)owner[0x20] < 0)
        return 0;
    object = CreateMoby(0x326 /* moby class 806 */);
    if (object) {
        data = *(u8 **)(object + 0x68);
        object[0x30] = 0x40;
        object[0x20] = 0;
        *(u8 **)(object + 0xB8) = owner;
        data[0x57] = type;
        *(int *)(object + 0x98) = 0;
        *(u16 *)(object + 0x34) |= 0x41;
        *(TI128 *)(object + 0x10) = *(TI128 *)(owner + 0x10);
    }
    return object;
}

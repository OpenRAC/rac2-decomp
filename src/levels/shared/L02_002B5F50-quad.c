#include "names.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef int TI128 __attribute__((mode(TI)));
extern u8 *func_0029EFD0(int);
extern void func_00282C88(TI128 *);
extern void func_002833F0(void *, void *);

/* Creates a new effect moby at a position and sets its type. */
u8 *func_L02_003A8770(TI128 *position, int type) {
    u8 *object = CreateMoby(0x326 /* moby class 806 */);
    u8 *data;
    if (object) {
        data = *(u8 **)(object + 0x68);
        object[0x30] = 0x40;
        object[0x20] = 0;
        *(u8 **)(object + 0xB8) = object;
        data[0x57] = type;
        *(int *)(object + 0x98) = 0;
        *(u16 *)(object + 0x34) |= 0x41;
        *(TI128 *)(object + 0x10) = *position;
        ClearVector128((TI128 *)(object + 0xF0));
        euler_rotation_basis(object + 0xC0, object + 0xF0);
    }
    return object;
}

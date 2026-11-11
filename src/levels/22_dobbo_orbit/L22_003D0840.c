#include "common.h"

extern void func_002A7750(void *object, int state, int arg2);

void func_L22_003D0840(u8 *object) {
    if (object[0x20] == 0) {
        u16 flags = *(u16 *)(object + 0x34) | 0x41;
        *(u16 *)(object + 0x34) = flags;
        func_002A7750(object, 1, -1);
    }
}

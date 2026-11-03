#include "common.h"

extern void func_002A0F48(u8 *p);

void func_L08_003CDB38(u8 *p) {
    u8 *s = *(u8 **)(p + 0x68);
    qcopy(p + 0x10, s);
    qcopy(p + 0xF0, s + 0x10);
    func_002A0F48(p);
}

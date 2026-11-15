#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char *func_0029EFD0(int);
extern void func_00283360(void *);
extern int D_L22_001AF37C;

char *func_L22_003FD1E8(char *obj, TI128 *pos, int arg3, f32 f) {
    char *o = CreateMoby(0xE3D);
    if (o != 0) {
        u8 *ctl = *(u8 **)(o + 0x68);
        *(short *)(ctl + 0x2A) = arg3;
        if ((short)arg3 != 0) {
            int c = D_L22_001AF37C;
            D_L22_001AF37C = c + 1;
            *(u16 *)(o + 0x96) = (c + 2) % 31;
        }
        *(u16 *)(o + 0x34) |= 0x108;
        *(u8 *)(o + 0x30) = 0xFF;
        *(u16 *)(o + 0x32) = 0x50;
        *(u8 *)(o + 0x31) = 1;
        *(u8 *)(o + 0x20) = 0;
        *(f32 *)(o + 0x2C) = *(f32 *)(*(u32 *)(o + 0x24) + 0x24) * f;
        *(u32 *)(ctl + 0x20) = (u32)obj;
        qcopy(o + 0x10, pos);
        set_identity_rotation_rows(o + 0xC0);
    }
    return o;
}

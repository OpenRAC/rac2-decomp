#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char *func_0029EFD0(int);
extern void func_00283360(void *);
extern int D_L22_001AF37C;

/* Creates a moby of class 3643 linked to the owner at the given position, with a size scale; a nonzero flag gives it a staggered timer. */
char *func_L22_003FC780(char *owner, TI128 *pos, int staggered, f32 scale) {
    char *created = CreateMoby(0xE3B /* moby class 3643 */);
    if (created != 0) {
        u8 *ctl = *(u8 **)(created + 0x68);
        *(short *)(ctl + 0x2A) = staggered;
        if ((short)staggered != 0) {
            int counter = D_L22_001AF37C;
            D_L22_001AF37C = counter + 1;
            *(u16 *)(created + 0x96) = (counter + 2) % 31;
        }
        *(u16 *)(created + 0x34) |= 0x108;
        *(u8 *)(created + 0x30) = 0xFF;
        *(u16 *)(created + 0x32) = 0x50;
        *(u8 *)(created + 0x31) = 1;
        *(u8 *)(created + 0x20) = 0;
        *(f32 *)(created + 0x2C) = *(f32 *)(*(u32 *)(created + 0x24) + 0x24) * scale;
        *(u32 *)(ctl + 0x20) = (u32)owner;
        qcopy(created + 0x10, pos);
        set_identity_rotation_rows(created + 0xC0);
    }
    return created;
}

#include "include_asm.h"

#include "common.h"
extern s32  func_32AB10(char *a0);
extern s32  func_360A80(s32 a0, s32 a1, char *a2);
extern f32  func_31BAE8(f32 a0, f32 a1);
extern f32  func_2F0000(f32 a0, f32 a1);
extern s32  func_312898(s32 a0, s32 a1, void *a2);
extern u8  *D_L03_001B2A1C;
extern f32  D_00189E20_19;
extern u8   D_001395BF;
extern u8   D_001395C0;
extern u8   D_001A7AFA;
extern u8   D_001A7B32;
extern u8   D_001A7AFB;
extern u8   D_001A7B33;
extern u8   D_001A7AFC;
extern u8   D_001A7B34;
extern u8 *D_L03_001B2A1C_tbl[] __asm__("D_L03_001B2A1C") __attribute__((sda));
extern void *func_0029EFD0(int);
extern void func_002A0F48(void *);

/* Spawns a kind-0xB1B object owned by OWNER at POSITION: opaque, a 0.015 rate, its state
   taking the two vectors, the three floats (in reverse order), a 0x10E word and the
   three bytes (the last twice). Returns the object, or 0. */
u8 *func_PAL_L03_003E5DE8(char *owner, void *position, void *first, void *second,
                        u8 a, u8 b, u8 c, f32 x, f32 y, f32 z)
{
    u8 *object;
    u8 *state;

    object = func_0029EFD0(0xB1B);
    if (object != 0) {
        qcopy(object + 0x10, position);
        object[0x30] = *(u16 *)(object + 0x32) = 0xFF;
        *(f32 *)(object + 0x2C) = 0.015f;
        *(char **)(object + 0xB8) = owner;
        object[0x20] = 0;
        state = *(u8 **)(object + 0x68);
        qcopy(state, first);
        qcopy(state + 0x10, second);
        *(f32 *)(state + 0x64) = z;
        state[0x75] = a;
        state[0x76] = b;
        state[0x77] = c;
        state[0x78] = c;
        *(f32 *)(state + 0x68) = y;
        *(f32 *)(state + 0x6C) = x;
        *(s32 *)(state + 0x70) = 0xE1;
        func_002A0F48(object);
    }
    return object;
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L03_003E61B0);

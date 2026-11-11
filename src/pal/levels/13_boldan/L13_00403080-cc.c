/* func_PAL_L13_00403080, the PAL copy of func_L13_003FE970: the same C, where template sibling func_PAL_L13_00402E14. */

typedef float f32;
typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef short s16;
extern s32 func_2AF870(u8 *);
extern u8 D_L13_001B1E60[];
extern s32 D_001A79F0 __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));
extern f32 func_00282E80(void *, void *);
extern f32 func_00282E48(void *, void *);
extern void func_002AAA00(void *, void *, f32, f32, f32, f32, s32);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern u8 D_00189EA0[];
extern s32 func_002ACBC8(u8 *, s32);
extern s32 func_002ACBC8(u8 *, s32);
extern s32 func_2AF870(u8 *);
extern u8 D_L13_001B1E60[];

void func_PAL_L13_00403080(u8 *a0) {
    u8 *ptr = *(u8 **)(a0 + 0x68);
    f32 vec[4];

    if (*(s32 *)ptr != 0) {
        if (func_00282E80(a0 + 0x10, D_00189EA0) < 8.0f) {
            if (a0[0x20] == 0) {
                a0[0x20] = 1;
            }
        }
    } else if (*(s32 *)(ptr + 8) != 0) {
        if (func_00282E48(a0 + 0x10, D_00189EA0) < 8.0f) {
            if (a0[0x20] == 0) {
                if (*(s16 *)(D_00189EA0 + 0x2C8) == 1) {
                    a0[0x20] = 2;
                }
            }
        }
    } else {
        if (a0[0x20] == 0) {
            *(u32 *)(a0 + 0x98) = 0;
            a0[0x20] = 3;
        }
    }

    if (a0[0x20] == 1) {
        func_002AAA00(a0 + 0xF8, ptr + 4, 2.3561947f, 0.0025132746f, 0.0025132746f, 0.04188791f, 0);
    }
    if (a0[0x20] == 2) {
        func_002AAA00(a0 + 0xF8, ptr + 4, 1.5707965f, 0.0025132746f, 0.0025132746f, 0.04188791f, 0);
    }
    if (a0[0x20] == 4) {
        *(u16 *)(a0 + 0x96) = *(u16 *)(a0 + 0x96) + 1;
        func_00282F20(vec, a0 + 0xD0, 0.20000002f);
        func_00282CC0(a0 + 0x10, a0 + 0x10, vec);
        if (*(u16 *)(a0 + 0x96) >= 11) {
            *(u16 *)(a0 + 0x96) = 0;
            a0[0x20] = 5;
        }
    }
    if (a0[0x20] == 5) {
        u32 c = *(u16 *)(a0 + 0x96) + 1;

        *(u16 *)(a0 + 0x96) = c;
        if ((u16)c >= 31) {
            *(u16 *)(a0 + 0x96) = 0;
            a0[0x20] = 6;
        }
    }
    if (a0[0x20] == 6) {
        *(u16 *)(a0 + 0x96) = *(u16 *)(a0 + 0x96) + 1;
        func_00282F20(vec, a0 + 0xD0, -0.20000002f);
        func_00282CC0(a0 + 0x10, a0 + 0x10, vec);
        if (*(u16 *)(a0 + 0x96) >= 11) {
            a0[0x20] = 0;
        }
    }
}


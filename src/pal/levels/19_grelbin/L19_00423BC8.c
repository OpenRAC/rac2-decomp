#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L19_00423BC8);


INCLUDE_ASM("asm/pal/levels", func_PAL_L19_00425AE0);

#include "common.h"
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A7750(void *, int, int);
extern s32 D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[];
extern u8 *D_L19_001B2A1C[] __attribute__((sda));
extern char D_00188660[];
extern float D_L19_001A8F20[] MACRO_ADDR;
extern void func_002AA458(void *, void *, void *, float, float, float);
extern int func_002E5CF8(int, int, void *);
extern float func_00282E48(void *, void *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L19_00420B48(void *);
extern void func_002A8C00(float, void *, void *, int, void *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern u16 *D_L19_001FB5A0[];
extern u8 *D_L19_001B2A1C[] __attribute__((sda));
extern s32 D_L19_001B2A38[] __attribute__((sda));
extern s32 D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[];
extern s32 func_002B38B8(u8 *);
extern float D_L19_001B1ECC[] SDATA(D_L19_001B1ECC);
extern float D_L19_001B1ED0[] SDATA(D_L19_001B1ED0);
extern float D_L19_001B1ED4[] SDATA(D_L19_001B1ED4);
extern float D_L19_001B1ED8[] SDATA(D_L19_001B1ED8);
extern u8 D_L19_001B1EDC[] SDATA(D_L19_001B1EDC);
extern int D_L19_001B1EE0[] SDATA(D_L19_001B1EE0);
extern int D_L19_001B1EE4[] SDATA(D_L19_001B1EE4);
extern float D_L19_001B1EE8[] SDATA(D_L19_001B1EE8);
extern float D_L19_001B1EEC[] SDATA(D_L19_001B1EEC);
extern u32 D_L19_001B1EF0[] SDATA(D_L19_001B1EF0);
extern u32 D_L19_001B1EF4[] SDATA(D_L19_001B1EF4);
extern int D_L19_001B1EFC[] SDATA(D_L19_001B1EFC);
extern int D_L19_001B1F00[] SDATA(D_L19_001B1F00);

/* Moves the object between two points. State 0 records its home position and builds the far
   point (along the axis at 0xC0, raised by the first state word); state 1 waits for its trigger
   flag or for its linked entity to leave state 0; states 2 and 3 move it out and back, keeping
   its looping sound alive, and then cast a collision line along the axis at 0xE0. */
void func_PAL_L19_00425F08(char *obj)
{
    char *data = *(char **)(obj + 0x68);
    float offset[4] __attribute__((aligned(16)));
    char query[0x30] __attribute__((aligned(16)));
    char *sound;

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        func_00282F20(offset, obj + 0xC0, *(float *)(data + 4));
        func_00282CC0(data + 0x30, offset, obj + 0x10);
        *(float *)(data + 0x38) += *(float *)data;
        qcopy(data + 0x20, obj + 0x10);
        *(int *)(data + 0x40) = -1;
    case 1:
        if ((*(u8 *)(obj + 0xB0) != 0xFF && (D_0019B2E8[*(u8 *)(obj + 0xB0) + (D_001A79F0 << 4)] & 0x80)) ||
            (*(int *)(data + 0x1C) != -1 &&
             *(u8 *)((char *)((*(int *)(data + 0x1C) << 8) + (int)D_L19_001B2A1C[0]) + 0x20) != 0))
            func_002A7750(obj, 2, -1);
        break;
    case 2:
        func_002AA458(obj + 0x10, data + 0x30, data + 0x14, *(float *)(data + 8) * 0.00040000002f,
                      *(float *)(data + 8) * 0.00040000002f, *(float *)(data + 8) * 0.020000001f);
        sound = D_00188660 + *(int *)(data + 0x40) * 0x70;
        if (*(char **)(sound + 0x88) != obj || !*(u8 *)(sound + 0x74))
            *(int *)(data + 0x40) = func_002E5CF8(0, 4, obj);
        if (func_00282E48(obj + 0x10, data + 0x30) < *(float *)(data + 8) * 0.020000001f)
            func_002A7750(obj, 3, -1);
        break;
    case 3:
        sound = D_00188660 + *(int *)(data + 0x40) * 0x70;
        if (*(char **)(sound + 0x88) != obj || !*(u8 *)(sound + 0x74))
            *(int *)(data + 0x40) = func_002E5CF8(0, 4, obj);
        func_002AA458(obj + 0x10, data + 0x20, data + 0x14, *(float *)(data + 8) * 0.00040000002f,
                      *(float *)(data + 8) * 0.00040000002f, *(float *)(data + 8) * 0.020000001f);
        if (func_00282E48(obj + 0x10, data + 0x20) < *(float *)(data + 8) * 0.020000001f)
            func_002A7750(obj, 2, -1);
        break;
    }
    if (*(u8 *)(obj + 0x20) >= 2) {
        func_L00_002E6CF0(func_L19_00420B48, obj);
        func_002A8C00(4.0f, query, obj, 1, D_L19_001A8F20);
        *(u16 *)(query + 0x1A) = *(u16 *)(obj + 0xAA);
        func_00282F20(offset, obj + 0xE0, *(float *)(data + 0xC));
        func_00282CC0(offset, obj + 0x10, offset);
        func_002761F8(obj + 0x10, offset, 0, obj, query);
    }
}


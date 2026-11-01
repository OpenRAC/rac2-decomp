#include "include_asm.h"

typedef int Rac2TI128 __attribute__((mode(TI)));
extern void *func_0029EFD0(int id);
extern int func_002FED90(void *a0, void *a1, float f12, float f13, float f14);
extern int func_L00_002FCF18(void *a0, float f12, float f13, float f14, float f15, float f16);
extern float func_002A7940(void);
extern void func_002833F0(void *a0, void *a1);
extern unsigned int D_L00_001AFDA0 __attribute__((sda));

/* Creates the level's own object, fills the header the object carries, copies the two
   16-byte records it is given into it, and lets the shared helpers set the rest up.
   The object is returned; a null one is returned unchanged. */
void *func_PAL_L00_003BECF0(char *a0, char *a1, char *a2, char *a3)
{
    char *node;
    char *sub;
    char *p1;
    unsigned short v0;

    node = (char *)func_0029EFD0(0x9A9);
    if (node != 0) {
        v0 = *(unsigned short *)(node + 0x34);
        *(unsigned char *)(node + 0x30) = 0xFF;
        *(unsigned short *)(node + 0x32) = 0x1FF;
        *(unsigned short *)(node + 0x34) = v0 | 0x100;

        sub = *(char **)(node + 0x68);
        p1 = node + 0x10;
        *(int *)(sub + 0x44) = *(short *)(a0 + 0xAA);
        *(int *)(sub + 0x34) = 0x64;
        *(float *)(sub + 0x4C) = 0.01f;
        *(int *)(sub + 0x40) = (int)a1;

        *(Rac2TI128 *)p1 = *(Rac2TI128 *)a2;
        *(Rac2TI128 *)sub = *(Rac2TI128 *)a3;
        *(Rac2TI128 *)(sub + 0x20) = *(Rac2TI128 *)a3;

        *(int *)(sub + 0x50) = func_002FED90(node, 0, 1.0f, 1.0f, 1.0f);
        *(int *)(sub + 0x54) = 0;
        *(int *)(sub + 0x58) = 0;
        *(unsigned char *)(node + 0x20) = 0;
        D_L00_001AFDA0 = D_L00_001AFDA0 + 1;
        *(int *)(sub + 0x5C) = func_L00_002FCF18(p1, 0.0f, 0.0f, 0.25f, 0.14f, 1.0f);
        *(float *)(node + 0xF0) = func_002A7940();
        *(float *)(node + 0xF4) = func_002A7940();
        *(float *)(node + 0xF8) = func_002A7940();
        *(float *)(node + 0xFC) = 0.0f;
        func_002833F0(node + 0xC0, node + 0xF0);
    }
    return node;
}

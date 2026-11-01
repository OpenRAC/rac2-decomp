#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00423418);

extern int func_L00_0032A088(int id, int index);
extern void func_002FEE50(int index);
extern void func_0029F338(void *object);
extern int *func_L00_0032A0B8(int id, int index);
extern float func_002A7878(float a, float b);
extern int func_00283CF0(float value);
extern void func_L00_002EBE88(int a0, int a1, int a2, int a3, int a4, int a5,
                              float f12, float f13, float f14);
extern void func_L00_0041E648(void *self, int flags, int mode);
extern unsigned char D_00139568[];
extern unsigned char D_L00_00262570[];
typedef struct {
    unsigned char pad000[4];
    unsigned char flag;
} Entry262570;
extern float func_002A7878(float a, float b);
extern int func_00283CF0(float a);

/* Looks the object's record up in the level's table (the resident byte at D_00139568 + 0x16
   is the record's number), asks the level's builder for a matrix with the flags the object's
   own word selects, then reads the record's two colour bytes and hands the level's renderer
   the object's record. */
void func_PAL_L00_00423778(void *arg0)
{
    unsigned char *self = arg0;
    unsigned char *rec;
    int handle;
    int flags;
    int mode;
    int base;
    float scale;
    unsigned int c1;
    unsigned int c2;

    rec = *(unsigned char **)(self + 0x68);
    handle = func_L00_0032A088(*(int *)(rec + 0x50), *(int *)(rec + 0x3C));
    if (handle == 0) {
        func_002FEE50(*(int *)(rec + 0x6C));
        func_0029F338(self);
    } else {
        if (((Entry262570 *)(D_L00_00262570 + D_00139568[0x16] * 224))->flag != 0) {
            flags = 0x802080;
            if (*(int *)(rec + 0x68) != 0)
                flags = 0x802020;
            mode = 0x7F;
        } else {
            flags = 0x202080;
            mode = 0x50;
        }
        func_L00_0041E648(self, flags, mode);
        if (((Entry262570 *)(D_L00_00262570 + D_00139568[0x16] * 224))->flag == 0)
            return;
        base = handle + func_L00_0032A0B8(*(int *)(rec + 0x50), *(int *)(rec + 0x3C))[2];
        scale = func_002A7878(0.5f, 1.0f);
        c1 = (unsigned int)func_00283CF0(scale * 127.0f) << 24;
        c2 = (unsigned int)func_00283CF0(scale * 48.0f) << 24;
        func_L00_002EBE88(*(int *)((char *)base + *(int *)(rec + 0x30) * 4),
                          0x17, 0xE, 0x7,
                          0xFF5050 | c1, 0xFF1010 | c2,
                          0.0f, 3.0f, 0.0f);
    }
}


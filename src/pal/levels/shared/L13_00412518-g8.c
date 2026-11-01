#include "include_asm.h"

#include "common.h"
typedef int L13_TI128 __attribute__((mode(TI)));
extern char *func_0029EFD0(int);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00282E20(char *);
extern float func_002A7940(void);
extern void func_002ACEC0(char *, char *, char *, float);
extern void func_002833F0(char *, char *);
extern float func_002A7878(float, float);
extern void func_002C2210(void *, int, int, float, int, int, int, float, float, int);
extern void func_002E5CF8(int, int, char *);
extern float D_L13_001B1360 __attribute__((sda));
extern int D_L13_001B1308 __attribute__((sda));
extern int D_L13_001B130C __attribute__((sda));
extern char D_L13_001A8F20[] __attribute__((sda));
typedef struct {
    unsigned char pad00[0x20];
    unsigned char active;
    unsigned char pad21[2];
    unsigned char opacity;
    unsigned char pad24[8];
    float scale;
    unsigned char alpha, enabled;
    unsigned short color, flags;
} DCObject;

char *func_PAL_L13_00412518(char *a0, char *a1, char *a2, int a3, float f12)
{
    float angle, scale;
    char *p = a2;
    char *q = a0;
    char *entity = func_0029EFD0(0xEA7);

    if (entity != 0) {
        *(unsigned char *)(entity + 0x30) = 0xFF;
        *(unsigned short *)(entity + 0x32) = 0xFF;
        *(unsigned char *)(entity + 0x31) = 1;
        *(unsigned char *)(entity + 0x20) = 0;
        *(long long *)(entity + 0x38) = *(long long *)(q + 0x38);
        *(L13_TI128 *)(entity + 0x10) = *(L13_TI128 *)p;
        p = *(char **)(entity + 0x68);
        *(L13_TI128 *)p = *(L13_TI128 *)a1;
        *(char **)(p + 0x10) = q;
        *(float *)(p + 0x14) = f12;
        *(float *)(p + 0x20) = 0.1500000059604645f;
        ((DCObject *)entity)->flags |= 0x208;

        *(float *)(entity + 0xF8) =
            func_00283B98(func_00283248(*(float *)(a1 + 0), *(float *)(a1 + 4)), 1.5707964906692505f);
        *(float *)(entity + 0xF0) = -func_00283248(func_00282E20(a1), *(float *)(a1 + 8));
        angle = func_002A7940();

        q = entity + 0xC0;
        func_002ACEC0(entity + 0xE0, entity + 0xE0, entity + 0xD0, angle);
        func_002ACEC0(q, q, entity + 0xD0, angle);
        func_002833F0(q, entity + 0xF0);

        ((DCObject *)entity)->opacity = 0x80;
        ((DCObject *)entity)->flags |= 0x100;
        ((DCObject *)entity)->scale = D_L13_001B1360;
        *(int *)(p + 0x24) = 0;
        scale = func_002A7878(8.0f, 10.0f);
        func_002C2210(entity + 0x10, 0xC, D_L13_001B1308, scale * 0.30000001192092896f, 0, 0xA,
                    (int)D_L13_001A8F20, scale, 0.0f, 0);
        func_002C2210(entity + 0x10, 0xC, D_L13_001B130C, scale * 0.03999999910593033f, 1, -0xA,
                    (int)D_L13_001A8F20, scale * 0.4000000059604645f, 0.0f, 0);
        func_002E5CF8(0, 0, entity);
    }
    return entity;
}

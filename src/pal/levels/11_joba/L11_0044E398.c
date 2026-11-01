#include "include_asm.h"

#include "common.h"
extern void func_32C9E0();
extern void func_32C700();
extern s32 func_441868(s32 a0, s32 a1);
extern s32 func_33C800(char *a0, s32 a1, s32 a2, s32 a3, float f12, float f13);

void func_PAL_L11_0044E398(char *a0)
{
    if (*(s32 *)(*(char **)(a0 + 0x68) + 0x354) != 0) {
        func_32C9E0(a0, 4, 2);
        if (*(u8 *)(a0 + 0x43) != 0)
            func_32C700(a0, 0, 0, 0x8);
    } else {
        func_32C9E0(a0, 5, 2);
        if (*(u8 *)(a0 + 0x43) != 1)
            func_32C700(a0, 1, 0, 0x8);
    }
}

typedef int Rac2TI128 __attribute__((mode(TI)));
extern int func_L11_00448D28(char *object);
extern void func_00282CF0(void *, void *, void *);
extern float func_002B04E0(char *object, float *src, char *third);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00282E48(void *, void *);
extern int func_002A77E0(int);
extern void func_002A7750(char *, int, int);
extern void func_PAL_002A7E68(char *, int, int, int);
extern char D_00189EA0[];

/* Picks the attack variant the actor plays against its target: the aim vector comes from the
   state's target record, or the shared default, and a close and well aimed target starts one
   of three attacks. */
int func_PAL_L11_0044E538(char *object)
{
    char *state = *(char **)(object + 0x68);
    float v[4];
    float tmp[4];
    float ang;
    char *p;

    if (func_L11_00448D28(object) != 0)
        return 0;
    p = *(char **)(state + 0x350);
    if (p != 0)
        *(Rac2TI128 *)v = *(Rac2TI128 *)(p + 0x10);
    else
        *(Rac2TI128 *)v = *(Rac2TI128 *)D_00189EA0;
    if (*(short *)(state + 0x36E) != 0) {
        func_00282CF0(tmp, v, object + 0x10);
        ang = func_002B04E0(object, tmp, state + 0x2F0);
    } else {
        ang = func_00283C80(func_00283248(v[0] - *(float *)(object + 0x10), v[1] - *(float *)(object + 0x14)),
                            *(float *)(object + 0xF8));
    }
    if (func_00282E48(object + 0x10, v) < 4.0f) {
        if (ang < 0.26179942f) {
            if (func_002A77E0(4) == 0) {
                func_002A7750(object, 0xC, 5);
                if (*(unsigned char *)(object + 0x43) != 7)
                    func_PAL_002A7E68(object, 7, 0, 0x8);
            } else if (*(int *)(state + 0x354) != 0) {
                func_002A7750(object, 0xE, 6);
                if (*(unsigned char *)(object + 0x43) != 9)
                    func_PAL_002A7E68(object, 9, 8, 0xC);
            } else {
                func_002A7750(object, 0xD, 6);
                if (*(unsigned char *)(object + 0x43) != 8)
                    func_PAL_002A7E68(object, 8, 8, 0xC);
            }
            return 1;
        }
    }
    return 0;
}


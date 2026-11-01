#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
extern int func_L00_00367720(void);
extern void func_L05_00417448(void *);
extern void func_L05_00379E60(int, int, int, int);
extern void func_L05_00417730(void *);
extern int func_002ED688(void *);
extern void func_002EE678(void *, unsigned int);
extern void func_002EE920(void *, void *);
extern int func_002EEB00(void *);
extern void func_L05_0037C160(void *);
extern void func_L05_0037B948(void *, int, float);
extern float func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern int func_00282948(void *);
extern int func_002E5DA0(int, int, void *, int);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_L05_00417550(void *);
extern int D_L05_001B0F50 __attribute__((sda));
extern int D_L05_00221D48 NOT_SDA;
extern char *D_L05_001FE380[];
extern char *D_L05_001B251C MACRO_ADDR;
extern u8 D_00188660[];

typedef struct { u8 pad[0x11C]; int mode; } Movement;
void func_L05_004170C8(u8 *actor)
{
    Vector direction, facing;
    u8 *state = *(u8 **)(actor + 0x68);
    u8 *movement;
    char *path;
    int one, mode;
    if (actor[0x20] == 0) {
        actor[0x30] = 0xFF;
        if (func_L00_00367720() == 0)
            return;
        func_L05_00417448(actor);
        if (*(int *)(state + 0x1B4) != 0)
            func_L05_00379E60((int)actor, (int)func_L05_00417730, 0, 0);
        D_L05_001B0F50 = 0;
        return;
    }
    movement = (u8 *)func_002ED688(actor);
    if (*(int *)(movement + 0x110) == 0)
        return;
    path = D_L05_001FE380[D_L05_00221D48];
    one = 1;
    func_002EE678(actor, 11);
    if (*(int *)(state + 0x1B8) == 0) {
        *(int *)(state + 0x1B8) = one;
        *(int *)(state + 0x1BC) = one;
        qcopy(actor + 0x10, path + 0x10);
        *(int *)(state + 0x1BC) = 2;
        func_002EE920(actor, path + 0x20);
        func_00282CF0(movement + 0x90, movement + 0x60, actor + 0x10);
        func_00282F20(movement + 0x90, movement + 0x90, 1.0f);
        *(int *)(movement + 0x130) = 2000000;
    } else if (func_002EEB00(actor) != 0) {
        int next = *(int *)(state + 0x1BC);
        if (next >= *(int *)path)
            D_L05_001B0F50 = one;
        else {
            *(int *)(state + 0x1BC) = next + 1;
            func_002EE920(actor, path + (next * 16 + 16));
            *(int *)(movement + 0x130) = 2000000;
        }
    }
    if (D_L05_001B0F50 == 0) {
        func_L05_0037C160(actor);
        func_L05_0037B948(actor, 1, 32.0f);
    }
    mode = *(int *)(movement + 0x110);
    if (mode == 1) {
        if (*(int *)(state + 0x1B0) != -1) {
            u8 *other;
            ((Movement *)movement)->mode = mode;
            other = (u8 *)D_L05_001B251C + (*(int *)(state + 0x1B0) << 8);
            *(u8 **)(movement + 0x120) = other;
            if (func_00282E48(other + 0x10, actor + 0x10) < 15.0f) {
                float alignment;
                func_00282CF0(&direction, actor + 0x10, *(u8 **)(movement + 0x120) + 0x10);
                func_00282F20(&direction, &direction, 1.0f);
                func_00282F20(&facing, *(u8 **)(movement + 0x120) + 0xC0, 1.0f);
                alignment = func_00282DB0(&facing, &direction);
                if (alignment > 0.4f) {
                    if (func_00282948(state + 0x1C8) != 0) {
                        *(int *)(state + 0x1C4) = func_002E5DA0(14, 0, actor, 0xFBF);
                        *(int *)(state + 0x1C8) = func_00283CF0(func_002A7878(180.0f, 240.0f));
                    }
                } else if (alignment < -0.4f && func_00282948(state + 0x1C8) != 0) {
                    func_002E5DA0(11, 0, actor, 0xFBF);
                    *(int *)(state + 0x1C8) = func_00283CF0(func_002A7878(180.0f, 240.0f));
                }
            }
        }
        func_L05_00417550(actor);
    }
    {
        u8 *sound = D_00188660 + *(int *)(state + 0x1C0) * 0x70;
        if (*(u8 **)(sound + 0x88) != actor || sound[0x74] == 0)
            *(int *)(state + 0x1C0) = func_002E5DA0(0, 6, actor, 0xF82);
    }
}

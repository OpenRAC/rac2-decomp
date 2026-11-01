#include "include_asm.h"

typedef unsigned char u8;
typedef int s32;
typedef int Quadword __attribute__((mode(TI)));
extern char *func_0029EFD0(short);
extern void func_002B37E8(char *, char *);
extern float func_00283BE0(float, float);
extern void func_002A7750(char *, s32, s32);
extern int func_002B38B8(u8 *);
extern int func_002B3868(u8 *);
extern void func_002E5CF8(s32, s32, char *);
extern void func_0029F338(char *);
extern float func_002AA548(float *, float *, float, float, float, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
typedef struct { char *child; float velocity; } ChildMotion;

void func_PAL_L16_003F97B0(char *object)
{
    ChildMotion *vars = *(ChildMotion **)(object + 0x68);
    union { Quadword q; float f[4]; } offset;
    if (vars == 0) {
        func_002B37E8(func_0029EFD0(0xe7f), object);
        func_0029F338(object);
        return;
    }
    switch (*(u8 *)(object + 0x20)) {
    case 0: {
        float size;
        *(float *)(object + 0xF0) = func_00283BE0(*(float *)(object + 0xf8), 1.5707964897155762f);
        func_002B37E8((vars->child = func_0029EFD0(0x99d)), object);
        size = *(float *)(*(char **)(vars->child + 0x24) + 0x24);
        *(float *)(vars->child + 0x2c) = size + size;
        func_002A7750(object, 1, -1);
        break;
    }
    case 1:
        if (func_002B38B8((u8 *)vars->child)) {
            func_002E5CF8(0, 0, object);
            func_002A7750(object, 2, -1);
        }
        break;
    case 2:
        if (func_002B3868((u8 *)object)) func_002E5CF8(0, 0, object);
        func_002AA548((float *)(object + 0xF0), &vars->velocity, 0.0f, 0.000767945f, 251.32744f, 349.06592f);
        if (*(float *)(object + 0xF0) <= 0.0f) {
            *&vars->velocity = 0.0f;
            func_002E5CF8(1, 0, object);
            func_002A7750(object, 7, -1);
        }
        break;
    case 3:
        if (func_002B3868((u8 *)object)) func_002E5CF8(1, 0, object);
        func_002AA548((float *)(object + 0xF0), &vars->velocity, 0.43633235f, 0.025132746f, 0.00062831864f, 1.0471977f);
        if (0.4363323450088501f <= *(float *)(object + 0xF0)) {
            *&vars->velocity = 0.0f;
            func_002A7750(object, 4, -1);
        }
        break;
    case 4:
        func_002AA548((float *)(object + 0xF0), &vars->velocity, 0.0f, 0.00062831864f, 0.25132746f, 3.4906592f);
        if (*(float *)(object + 0xF0) <= 0.0f) {
            *&vars->velocity = 0.0f;
            func_002E5CF8(1, 0, object);
            func_002A7750(object, 5, -1);
        }
        break;
    case 5:
        if (func_002B3868((u8 *)object)) func_002E5CF8(1, 0, object);
        func_002AA548((float *)(object + 0xF0), &vars->velocity, 0.26179942f, 0.025132746f, 0.00062831864f, 1.0471977f);
        if (0.2617994248867035f <= *(float *)(object + 0xF0)) {
            *&vars->velocity = 0.0f;
            func_002A7750(object, 6, -1);
        }
        break;
    case 6:
        func_002AA548((float *)(object + 0xF0), &vars->velocity, 0.0f, 0.00062831864f, 0.25132746f, 3.4906592f);
        if (*(float *)(object + 0xF0) <= 0.0f) {
            *&vars->velocity = 0.0f;
            func_002E5CF8(1, 0, object);
            func_002A7750(object, 7, -1);
        }
        break;
    case 7:
        if (func_002B3868((u8 *)object)) func_002E5CF8(1, 0, object);
        func_002AA548((float *)(object + 0xF0), &vars->velocity, 0.087266475f, 0.025132746f, 0.00062831864f, 1.0471977f);
        if (0.0872664749622345f <= *(float *)(object + 0xF0)) {
            *&vars->velocity = 0.0f;
            func_002A7750(object, 8, -1);
        }
        break;
    case 8:
        func_002AA548((float *)(object + 0xF0), &vars->velocity, 0.0f, 0.00062831864f, 0.25132746f, 3.4906592f);
        if (*(float *)(object + 0xF0) <= 0.0f) {
            *&vars->velocity = 0.0f;
            func_002E5CF8(1, 0, object);
            func_002A7750(object, 9, -1);
        }
        break;
    case 9:
        if (func_002B3868((u8 *)object)) func_002E5CF8(1, 0, object);
        func_002AA548((float *)(object + 0xF0), &vars->velocity, 0.03490659f, 0.025132746f, 0.00062831864f, 1.0471977f);
        if (0.03490658849477768f <= *(float *)(object + 0xF0)) {
            *&vars->velocity = 0.0f;
            func_002A7750(object, 10, -1);
        }
        break;
    case 10:
        func_002AA548((float *)(object + 0xF0), &vars->velocity, 0.0f, 0.00062831864f, 0.25132746f, 3.4906592f);
        break;
    }
    *(Quadword *)(vars->child + 0x10) = *(Quadword *)(object + 0x10);
    offset.q = 0;
    offset.f[1] = 8.0f;
    offset.f[2] = -0.5f;
    func_00283098(&offset, &offset, object + 0xC0);
    func_00282CC0(vars->child + 0x10, vars->child + 0x10, &offset);
}

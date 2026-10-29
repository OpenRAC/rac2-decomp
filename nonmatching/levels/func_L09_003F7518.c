/* Retained animation parameter reconstruction, 2026-10-28.
 * Retail620B, best616B, 0/2 US placements after4 bounded trials.
 * A per-branch helper call produces700B. Narrow no-schedule-insns ties616;
 * no store-order volatile, dependency, assembly alias or register workaround.
 * Retail keeps object/animation in different saved registers, emits an extra
 * branch-local A0 move and a different ordinary byte/float store schedule.
 * Actual002B60B0 returns its allocated float-parameter record pointer; format
 * logger0026FEB8 is variadic. This source includes each canonical symbol once.
 * Private state minimum42CB; optional child needs44B to read animation byte43.
 */
#include "common.h"
extern void func_0026FEB8(const char *, ...);
extern void *func_002B60B0(u8 *, float, float, float, float);
extern void func_002A7470(void *, int, int, int);
extern const char D_L09_001B10A8[];
extern float D_L09_001B0F0C_gp SDATA(D_L09_001B0F0C);
extern float D_L09_001B0F10_gp SDATA(D_L09_001B0F10);
extern float D_L09_001B0F14_gp SDATA(D_L09_001B0F14);
extern float D_L09_001B0F18_gp SDATA(D_L09_001B0F18);
extern float D_L09_001B0F1C_gp SDATA(D_L09_001B0F1C);
extern float D_L09_001B0F20_gp SDATA(D_L09_001B0F20);

/* Private fields extend through the 32-bit state at +0x428. The child at
 * +0x2F8 is optional; its animation byte is read only after the null check. */
void func_L09_003F7518(u8 *object, int animation, int first, int second)
{
    u8 *vars = *(u8 **)(object + 0x68);
    u8 *child;
    float x, y, z, w;
    func_0026FEB8(D_L09_001B10A8, *(s16 *)(object + 0xB2), animation);
    if (animation == 12) {
        x = D_L09_001B0F0C_gp;
        y = D_L09_001B0F10_gp;
    } else {
        x = D_L09_001B0F14_gp;
        y = D_L09_001B0F18_gp;
    }
    z = D_L09_001B0F1C_gp;
    w = D_L09_001B0F20_gp;
    func_002B60B0(object, x * 0.00027777778450399637f, y * 0.01666666753590107f, z * 4.848137450608192e-06f, w * 0.0002908882452175021f);
    *(float *)(vars + 0x118) += *(float *)(vars + 0x118);
    if ((unsigned)(animation - 13) < 3) {
        vars[0x66] = 15; vars[0xC2] = 7; vars[0xC3] = 19; vars[0xC6] = 1;
        *(int *)(vars + 0x6C) = 0; *(int *)(vars + 0x70) = 0;
        *(int *)(vars + 0x74) = 0; *(int *)(vars + 0x78) = 0; *(int *)(vars + 0x7C) = 0;
        vars[0x61] = 15; vars[0x62] = 15;
        vars[0xBC] = 7; vars[0xBD] = 19; vars[0xBE] = 7; vars[0xBF] = 19;
    } else if (animation == 16) {
        *(float *)(vars + 0x6C) = 0.36666667461395264f; *(float *)(vars + 0x70) = 0.11666667461395264f;
        *(float *)(vars + 0x78) = 0.008333333767950535f; *(float *)(vars + 0x7C) = 0.004166666883975267f;
        vars[0x61] = 18; vars[0x66] = 20;
        vars[0xBC] = 5; vars[0xBD] = 9; vars[0xBE] = 4; vars[0xBF] = 7;
        vars[0xC2] = 10; vars[0xC3] = 17;
        *(float *)(vars + 0x74) = 0.004166666883975267f;
        vars[0x62] = 17; vars[0xC6] = 0;
    }
    if ((*(int *)(vars + 0x428) != 0 || (*(int *)(vars + 0x2DC) != -1 && *(int *)(vars + 0x2DC) == *(int *)(vars + 0x2B0))) && animation != 15) {
        if (object[0x43] != 14)
            func_002A7470(object, 14, first, second);
    } else if (object[0x43] != animation)
        func_002A7470(object, animation, first, second);
    child = *(u8 **)(vars + 0x2F8);
    if (child != 0 && child[0x43] != animation)
        func_002A7470(child, animation, first, second);
}

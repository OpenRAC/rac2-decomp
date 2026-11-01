#include "include_asm.h"

#include "common.h"
extern int func_002A77E0(int);
extern void func_002A7750(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int func_L02_003D18D8(char *);
extern u8 *D_L02_001B359C[] __attribute__((sda));
extern int func_002A77E0(int);
extern float func_00282E80(char *, char *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern int func_002A77E0(int);

/* Picks the idle variant the actor should play, from its distance and heading. */
int func_PAL_L02_003D56E8(char *object) {
    char *state = *(char **)(object + 0x68);
    float dist;
    float ang;

    if (func_L02_003D18D8(object) != 0)
        return 0;
    dist = 100.0f;
    ang = 1.0f;
    if (*(char **)(state + 0x2E0) != 0) {
        dist = func_00282E80(object + 0x10, *(char **)(state + 0x2E0) + 0x10);
        ang = func_00283248(*(float *)(*(char **)(state + 0x2E0) + 0x10) - *(float *)(object + 0x10),
                            *(float *)(*(char **)(state + 0x2E0) + 0x14) - *(float *)(object + 0x14));
    }
    if (dist < 4.0f) {
        if (func_00283C80(ang, *(float *)(object + 0xF8)) < 0.26179942f) {
            if (func_002A77E0(5) == 0) {
                func_002A7750(object, 0xC, 5);
                if (*(u8 *)(object + 0x43) != 7)
                    func_PAL_002A7E68(object, 7, 0, 0x8);
            } else if (*(int *)(state + 0x2E4) != 0) {
                func_002A7750(object, 0x12, 6);
                if (*(u8 *)(object + 0x43) != 0xD)
                    func_PAL_002A7E68(object, 0xD, 8, 0xC);
            } else {
                func_002A7750(object, 0xF, 6);
                if (*(u8 *)(object + 0x43) != 0xA)
                    func_PAL_002A7E68(object, 0xA, 8, 0xC);
            }
            return 1;
        }
    }
    return 0;
}


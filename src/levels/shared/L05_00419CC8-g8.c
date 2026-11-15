#include "common.h"


extern char *func_0029EFD0(int);
extern int func_00283CF0(float);
extern float func_002A7940(void);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_L00_002E6EF8(void (*)(char *), char *);
extern void func_L05_0041A228(char *);
extern float D_L05_001B1030 __attribute__((sda));
extern float D_L05_001B1034 __attribute__((sda));
extern float D_L05_001B1038 __attribute__((sda));
extern float D_L05_001B1054 __attribute__((sda));
extern float D_L05_001B1058 __attribute__((sda));
typedef int EffectVector __attribute__((mode(TI)));

/* Creates a shot-like effect object that starts at a position and flies along a direction. It copies the owner's turn or builds its own, and gets its draw function set up. */
char *func_L05_00419CC8(char *owner, void *pos, void *dir, int color1, int color2, int orient, int kind, int value, float scale)
{
    char *effect = CreateMoby(0xFFA /* moby class 4090 */);
    float up[4];
    char *vars;
    float speed;
    *(EffectVector *)up = 0;
    up[2] = 1.0f;
    if (effect) {
        float baseSpeed = D_L05_001B1030;
        int life;
        float start, end;
        vars = *(char **)(effect + 0x68);
        *(int *)(vars+0x30) = kind;
        speed = baseSpeed * (1.0f / 60.0f);
        if (kind) speed = D_L05_001B1034 * (1.0f / 60.0f);
        effect[0x20] = 0;
        *(unsigned char *)(effect+0x30) = 0xFF;
        life = FloatToInt(D_L05_001B1038 / speed);
        end = D_L05_001B1058;
        start = D_L05_001B1054;
        *(char **)(vars+4) = owner;
        *(int *)vars = life;
        *(float *)(vars+0x3c) = start;
        *(float *)(vars+0x40) = (end-start)/(float)life;
        *(float *)(vars+8) = RandomAngle();
        *(float *)(vars+0xc) = scale;
        *(int *)(vars+0x38) = value;
        if (*(int *)(vars+0x30)) {
            *(int *)(vars+0x20)=0x00FF2020;
            *(int *)(vars+0x24)=0x7FEF2020;
            *(int *)(vars+0x34)=0;
        } else {
            *(int *)(vars+0x20)=color1;
            *(int *)(vars+0x24)=color2 | 0x7F000000;
        }
        if (!orient) {
            qcopy(effect+0xc0,owner+0xc0);
            qcopy(effect+0xd0,owner+0xd0);
            qcopy(effect+0xe0,owner+0xe0);
            vec_scale_to_length(vars+0x10,dir,speed);
        } else {
            vec_scale_to_length(effect+0xc0,dir,1.0f);
            FastVecCross(effect+0xd0,effect+0xc0,up);
            vec_scale_to_length(effect+0xd0,effect+0xd0,1.0f);
            FastVecCross(effect+0xe0,effect+0xd0,effect+0xc0);
            qcopy(vars+0x10,dir);
        }
        qcopy(effect+0x10,pos);
        AddDrawCallbackToList3(DrawEnergyBlastEffect,effect);
    }
    return effect;
}

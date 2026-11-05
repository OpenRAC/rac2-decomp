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

char *func_L05_00419CC8(char *owner, void *pos, void *dir, int color1, int color2, int orient, int kind, int value, float scale)
{
    char *obj = func_0029EFD0(0xFFA);
    float up[4];
    char *st;
    float speed;
    *(EffectVector *)up = 0;
    up[2] = 1.0f;
    if (obj) {
        float initial = D_L05_001B1030;
        int life;
        float start, end;
        st = *(char **)(obj + 0x68);
        *(int *)(st+0x30) = kind;
        speed = initial * (1.0f / 60.0f);
        if (kind) speed = D_L05_001B1034 * (1.0f / 60.0f);
        obj[0x20] = 0;
        *(unsigned char *)(obj+0x30) = 0xFF;
        life = func_00283CF0(D_L05_001B1038 / speed);
        end = D_L05_001B1058;
        start = D_L05_001B1054;
        *(char **)(st+4) = owner;
        *(int *)st = life;
        *(float *)(st+0x3c) = start;
        *(float *)(st+0x40) = (end-start)/(float)life;
        *(float *)(st+8) = func_002A7940();
        *(float *)(st+0xc) = scale;
        *(int *)(st+0x38) = value;
        if (*(int *)(st+0x30)) {
            *(int *)(st+0x20)=0x00FF2020;
            *(int *)(st+0x24)=0x7FEF2020;
            *(int *)(st+0x34)=0;
        } else {
            *(int *)(st+0x20)=color1;
            *(int *)(st+0x24)=color2 | 0x7F000000;
        }
        if (!orient) {
            qcopy(obj+0xc0,owner+0xc0);
            qcopy(obj+0xd0,owner+0xd0);
            qcopy(obj+0xe0,owner+0xe0);
            func_00282F20(st+0x10,dir,speed);
        } else {
            func_00282F20(obj+0xc0,dir,1.0f);
            func_00282DD8(obj+0xd0,obj+0xc0,up);
            func_00282F20(obj+0xd0,obj+0xd0,1.0f);
            func_00282DD8(obj+0xe0,obj+0xd0,obj+0xc0);
            qcopy(st+0x10,dir);
        }
        qcopy(obj+0x10,pos);
        func_L00_002E6EF8(func_L05_0041A228,obj);
    }
    return obj;
}

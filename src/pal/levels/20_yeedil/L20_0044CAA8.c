#include "include_asm.h"

#include "common.h"
extern void func_002A7750(int, int, int);
typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vec4;
extern void func_00282CF0(void *, void *, void *);
extern int func_002B3868(char *);
extern int func_002B38B8(char *);
extern void func_002AA548(char *, char *, float, float, float, float);
extern int func_002E5CF8(int, int, char *);
extern int func_002B3868(char *);
extern int func_002B38B8(char *);
extern void func_002AA548(char *, char *, float, float, float, float);
extern int func_L00_00324120(char *);
extern float func_00282C48(float);
extern int func_002E59B0(char *, int);
extern int func_002E5CF8(int, int, char *);
extern void func_002E59F8(int);
extern int func_L14_003DE908(char *);
extern void func_002AD6F0(void *, void *, void *, void *);
typedef struct { char pad[0x74]; unsigned char active; char pad2[0x13]; char *owner; } SoundSlot;
extern SoundSlot D_00188660[];
extern float D_00189EA4;

void func_PAL_L20_0044CAA8(char *arg0) {
    Vec4 pos, rot, delta;
    char *state = *(char **)(arg0 + 0x68);
    qcopy(&pos, arg0+0x10);
    qcopy(&rot, arg0+0xF0);
    switch (*(unsigned char *)(arg0 + 0x20)) {
    case 0:
        *(int *)(state+0x5C) |= 1;
        {
            float target=*(float *)(state+0x60);
            float start=*(float *)(arg0+0x14);
            *(float *)(state+0x6C) = 0.0014000001f;
            *(float *)(state+0x64) = start;
            *(float *)(state+0x70) = (start+target)*0.5f;
        }
        if (*(int *)(state+0x78) == 0) *(int *)(state+0x74)=0;
        else *(int *)(state+0x74)=1;
        func_002A7750(arg0,1,-1);
        break;
    case 1:
        if (func_002B38B8(arg0)) {
            if (func_L00_00324120(arg0) || (*(float *)(arg0+0x14)-*(float *)(state+0x70))*(D_00189EA4-*(float *)(state+0x70)) < 0.0f) {
                if (*(int *)(state+0x74)==0) func_002A7750(arg0,2,-1);
                else func_002A7750(arg0,3,-1);
                if (!func_002E59B0(arg0,*(int *)(state+0x7C))) *(int *)(state+0x7C)=func_002E5CF8(0,4,arg0);
            }
        }
        break;
    case 2:
        if (func_002B3868(arg0)) *(int *)(state+0x68)=0;
        if (func_00282C48(*(float *)(state+0x60)-*(float *)(arg0+0x14)) < 0.03f) {
            int i=*(int *)(state+0x7C);
            if (i != -1) {
                SoundSlot *slot=(SoundSlot *)((char *)D_00188660+i*0x70);
                if (slot->owner==arg0 && slot->active) func_002E59F8(i);
            }
            *(int *)(state+0x7C)=-1;
            if (!func_L14_003DE908(arg0)) {
                *(int *)(state+0x74)=1;
                *(float *)(arg0+0x14)=*(float *)(state+0x60);
                func_002A7750(arg0,1,-1);
            }
        } else func_002AA548(arg0+0x14,state+0x68,*(float *)(state+0x60),*(float *)(state+0x6C),*(float *)(state+0x6C),0.24000001f);
        break;
    case 3:
        if (func_002B3868(arg0)) *(int *)(state+0x68)=0;
        if (func_00282C48(*(float *)(arg0+0x14)-*(float *)(state+0x64)) < 0.03f) {
            int i=*(int *)(state+0x7C);
            if (i != -1) {
                SoundSlot *slot=(SoundSlot *)((char *)D_00188660+i*0x70);
                if (slot->owner==arg0 && slot->active) func_002E59F8(i);
            }
            *(int *)(state+0x7C)=-1;
            if (!func_L14_003DE908(arg0)) {
                *(int *)(state+0x74)=0;
                *(float *)(arg0+0x14)=*(float *)(state+0x64);
                func_002A7750(arg0,1,-1);
            }
        } else func_002AA548(arg0+0x14,state+0x68,*(float *)(state+0x64),*(float *)(state+0x6C),*(float *)(state+0x6C),0.24000001f);
        break;
    }
    func_00282CF0(&delta,arg0+0x10,&pos);
    func_002AD6F0(state+0x20,&delta,&rot,arg0+0xF0);
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L20_0044CEB0);



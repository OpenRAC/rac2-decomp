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


extern int func_00282948(void *);
extern void func_L00_003294F0(char *, int);
extern void func_PAL_L20_0044D1C8(char *);

/* func_PAL_L20_0044CEB0, the PAL copy of func_L20_004473B0: the same C, with the four timers at
   0x74-0x80 scaled to 50 Hz when the object starts (case 0). */
void func_PAL_L20_0044CEB0(char *arg0) {
    char *state;
    TI128 pos, rot, delta;
    float accel;

    state = *(char **)(arg0 + 0x68);
    qcopy(&pos, arg0 + 0x10);
    qcopy(&rot, arg0 + 0xF0);
    switch (*(unsigned char *)(arg0 + 0x20)) {
    case 0:
        qcopy(state + 0x60, arg0 + 0x10);
        *(int *)(state + 0x5C) |= 1;
        *(int *)(state + 0x74) = (*(int *)(state + 0x74) * 5 + 2) / 6;
        *(int *)(state + 0x78) = (*(int *)(state + 0x78) * 5 + 2) / 6;
        *(int *)(state + 0x7C) = (*(int *)(state + 0x7C) * 5 + 2) / 6;
        *(int *)(state + 0x80) = (*(int *)(state + 0x80) * 5 + 2) / 6;
        func_L00_003294F0(arg0, 1);
        func_002A7750((int)arg0, 4, -1);
        break;
    case 1:
        if (func_002B3868(arg0) != 0) {
            *(int *)(state + 0x88) = 0;
            *(int *)(state + 0x84) = *(int *)(state + 0x74);
        }
        if (func_00282948(state + 0x84) != 0) {
            func_002A7750((int)arg0, 2, -1);
        }
        {
            int duration = *(int *)(state + 0x74);
            float speed = *(float *)(state + 0x70);
            float start = *(float *)(state + 0x68) + speed;
            accel = (speed * 4.0f) / (float)(duration * duration);
            func_002AA548(arg0 + 0x18, state + 0x88, start, accel,
                          accel, accel * (float)duration);
        }
        break;
    case 2:
        if (func_002B3868(arg0) != 0) {
            *(int *)(state + 0x84) = *(int *)(state + 0x78);
        }
        if (func_00282948(state + 0x84) != 0) {
            func_002A7750((int)arg0, 3, -1);
        }
        break;
    case 3:
        if (func_002B3868(arg0) != 0) {
            *(int *)(state + 0x88) = 0;
            *(int *)(state + 0x84) = *(int *)(state + 0x7C);
        }
        if (func_00282948(state + 0x84) != 0) {
            func_002A7750((int)arg0, 4, -1);
        }
        {
            int duration = *(int *)(state + 0x74);
            float speed = *(float *)(state + 0x70);
            float start = *(float *)(state + 0x68);
            accel = (speed * 4.0f) / (float)(duration * duration);
            func_002AA548(arg0 + 0x18, state + 0x88, start, accel,
                          accel, accel * (float)duration);
        }
        break;
    case 4:
        if (func_002B3868(arg0) != 0) {
            *(int *)(state + 0x84) = *(int *)(state + 0x80);
        }
        if (func_00282948(state + 0x84) != 0) {
            func_002A7750((int)arg0, 1, -1);
        }
        break;
    }
    if (func_002B38B8(arg0) == 0) {
        if (0.0f < *(float *)(state + 0x8C)) {
            func_PAL_L20_0044D1C8(arg0);
            *(float *)(state + 0x8C) = -1000.0f;
        }
    }
    func_00282CF0(&delta, arg0 + 0x10, &pos);
    func_002AD6F0(state + 0x20, &delta, &rot, arg0 + 0xF0);
}



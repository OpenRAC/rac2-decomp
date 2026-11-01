#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern void func_00282CF0(void *dst, void *a, void *b);
typedef struct { char pad[0x74]; unsigned char active; char pad2[0x13]; char *owner; } PrisonLiftVoice;
typedef struct {
    char pad0000[0x80];
    Vec position;                
    char pad0090[0x22B4 - 0x90];
    unsigned char mode;          
} PrisonLiftHero;
extern PrisonLiftHero D_00189E20;
extern char D_00188660[];
extern int func_002B3868(char *self);
extern int func_L00_00324120(char *);
extern int func_002ACBC8(void *, int);
extern int func_002E59B0(char *, int);
extern int func_002E5CF8(int, int, char *);
extern void func_002E59F8(int);
extern int func_L14_003DE908(char *);
extern void func_002A7750(void *, int, int);
extern float func_002AA548(void *, void *, float, float, float, float);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_00282CF0(void *dst, void *a, void *b);
extern char D_00188660[];
extern int func_002B3868(char *self);
extern void func_L00_002E6EF8(void (*f)(char *), char *arg);

/* A lift that travels between its start height (0x68) and its target (0x64): state 0 sets it
   up, state 1 waits for the hero (or a trigger) and starts it with its travel sound, states 2
   and 3 ease it up and down and stop the sound on arrival. Riders follow its movement. */
void func_PAL_L14_003E25F8(char *arg0)
{
    Vec pos, rot, delta;
    char *state = *(char **)(arg0 + 0x68);
    int sound;

    qcopy(&pos, arg0 + 0x10);
    qcopy(&rot, arg0 + 0xF0);
    switch (*(unsigned char *)(arg0 + 0x20)) {
    case 0:
        *(int *)(state + 0x5C) |= 1;
        {
            float target = *(float *)(state + 0x64);
            float start = *(float *)(arg0 + 0x18);
            *(int *)(state + 0x74) = -1;
            *(float *)(state + 0x7C) = 0.0014000001f;
            *(float *)(state + 0x68) = start;
            *(int *)(state + 0x70) = 0;
            *(float *)(state + 0x80) = (start + target) * 0.5f;
        }
        if (*(int *)(state + 0x60) == 0) *(int *)(state + 0x6C) = 0;
        else *(int *)(state + 0x6C) = 1;
        *(unsigned char *)(arg0 + 0x20) = 1;
        break;
    case 1:
        if (D_00189E20.mode == 1 && *(int *)(state + 0x84)) {
            if (*(int *)(state + 0x6C) == 1) {
                func_002A7750(arg0, 2, -1);
                *(int *)(state + 0x74) = func_002E5CF8(0, 4, arg0);
            }
        } else if (func_L00_00324120(arg0)
                   || ((*(float *)(arg0 + 0x18) - *(float *)(state + 0x80)) * (D_00189E20.position.f[2] - *(float *)(state + 0x80)) < 0.0f
                       && *(int *)(state + 0x70))) {
            if (*(int *)(state + 0x6C) == 0) {
                func_002A7750(arg0, 3, -1);
                if (!func_002E59B0(arg0, *(int *)(state + 0x74)))
                    *(int *)(state + 0x74) = func_002E5CF8(0, 4, arg0);
            } else {
                func_002A7750(arg0, 2, -1);
                if (!func_002E59B0(arg0, *(int *)(state + 0x74)))
                    *(int *)(state + 0x74) = func_002E5CF8(0, 4, arg0);
            }
        }
        break;
    case 2:
        if (func_002B3868(arg0)) {
            *(float *)(state + 0x78) = 0.0f;
            (*(int *)(state + 0x70))++;
        }
        if (*(float *)(state + 0x64) - *(float *)(arg0 + 0x18) < 0.03f) {
            sound = *(int *)(state + 0x74);
            if (sound != -1) {
                PrisonLiftVoice *voice = (PrisonLiftVoice *)(D_00188660 + sound * 0x70);
                if (voice->owner == arg0 && voice->active) func_002E59F8(sound);
            }
            *(int *)(state + 0x74) = -1;
            if (!func_L14_003DE908(arg0)) {
                *(int *)(state + 0x6C) = 0;
                *(float *)(arg0 + 0x18) = *(float *)(state + 0x64);
                func_002A7750(arg0, 1, -1);
            }
        } else func_002AA548(arg0 + 0x18, state + 0x78, *(float *)(state + 0x64), *(float *)(state + 0x7C), *(float *)(state + 0x7C), 0.120000005f);
        break;
    case 3:
        if (func_002B3868(arg0)) {
            *(float *)(state + 0x78) = 0.0f;
            (*(int *)(state + 0x70))++;
        }
        if (*(float *)(arg0 + 0x18) - *(float *)(state + 0x68) < 0.03f) {
            sound = *(int *)(state + 0x74);
            if (sound != -1) {
                PrisonLiftVoice *voice = (PrisonLiftVoice *)(D_00188660 + sound * 0x70);
                if (voice->owner == arg0 && voice->active) func_002E59F8(sound);
            }
            *(int *)(state + 0x74) = -1;
            if (!func_L14_003DE908(arg0)) {
                *(int *)(state + 0x6C) = 1;
                *(float *)(arg0 + 0x18) = *(float *)(state + 0x68);
                func_002A7750(arg0, 1, -1);
            }
        } else {
            int ridden = func_L00_00324120(arg0) != 0;
            int away = func_002ACBC8(&D_00189E20.position, *(int *)(state + 0x88)) == 0;
            if (ridden || away)
                func_002AA548(arg0 + 0x18, state + 0x78, *(float *)(state + 0x68), *(float *)(state + 0x7C), *(float *)(state + 0x7C), 0.120000005f);
        }
        break;
    }
    func_00282CF0(&delta, arg0 + 0x10, &pos);
    func_002AD6F0(state + 0x20, &delta, &rot, arg0 + 0xF0);
}


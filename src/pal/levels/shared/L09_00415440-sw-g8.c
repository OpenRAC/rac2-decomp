#include "include_asm.h"

#include "common.h"
extern char D_00188660[];
typedef struct { char pad[0x33c]; char *object; int active; } Player10608;
extern Player10608 D_00189E20;
extern char D_L09_001B17F8[];
extern char *D_L09_001B294C;
extern int D_L09_001BFE58 NOT_SDA;
extern float D_L09_001B17F4 __attribute__((sda));
extern void func_0026FEB8(void *, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern float func_00282E48(const void *, const void *);
extern int func_00277258(void *, int, void *, float);
extern void func_PAL_L09_00415DA0(void *);
extern void func_PAL_L09_00415E28(void *);
extern void func_002AD6F0(void *, void *, void *, void *);
#define WORD(p,o) (*(int *)((char *)(p)+(o)))
#define FLOAT(p,o) (*(float *)((char *)(p)+(o)))
#define BYTE(p,o) (*(u8 *)((char *)(p)+(o)))
#define HALF(p,o) (*(short *)((char *)(p)+(o)))
typedef int Quad __attribute__((mode(TI)));
typedef struct { char pad[0x74]; u8 active; char gap[0x13]; char *owner; } SoundSlot;
#define SLOT(i) (D_00188660 + (i)*0x70)
#define SOUND_SLOT(i) ((SoundSlot *)SLOT(i))

/* Moves to the selected waypoint while ridden, then returns to its starting position. */
void func_PAL_L09_00415868(char *object)
{
    float old_position[4] __attribute__((aligned(16)));
    float old_rotation[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    char *slot;
    char *state = *(char **)(object + 0x68);
    qcopy(old_position, object + 0x10);
    qcopy(old_rotation, object + 0xf0);
    switch (BYTE(object,0x20)) {
    case 0:
        *(Quad *)(state+0x80) = *(Quad *)(object+0x10);
        FLOAT(state,0x64) *= 0.020000001f;
        FLOAT(object,0x2c) *= 1.75f;
        if (WORD(state,0x60) == -1)
            func_0026FEB8(D_L09_001B17F8, HALF(object,0xaa), HALF(object,0xb2));
        WORD(state,0x6c) = -1;
        func_002A7750(object,1,-1);
        break;
    case 1:
        if (func_002B3868(object)) {
            if (WORD(state,0x6c) != -1) {
                slot = SLOT(WORD(state,0x6c));
                if (*(char **)(slot+0x88) == object && BYTE(slot,0x74))
                    func_002E59F8(WORD(state,0x6c));
            }
            WORD(state,0x6c) = -1;
        }
        slot = SLOT(WORD(state,0x6c));
        if (*(char **)(slot+0x88) != object || !BYTE(slot,0x74))
            WORD(state,0x6c) = func_002E5CF8(1,4,object);
        if (WORD(state,0x60) != -1 && D_00189E20.object==object && D_00189E20.active)
            func_002A7750(object,2,-1);
        break;
    case 2:
        if (func_002B3868(object)) {
            if (WORD(state,0x6c) != -1) {
                slot = SLOT(WORD(state,0x6c));
                if (*(char **)(slot+0x88) == object && BYTE(slot,0x74))
                    func_002E59F8(WORD(state,0x6c));
            }
            WORD(state,0x6c) = -1;
        }
        slot = SLOT(WORD(state,0x6c));
        if (*(char **)(slot+0x88) != object || !BYTE(slot,0x74))
            WORD(state,0x6c) = func_002E5CF8(0,4,object);
        func_00282CF0(delta,D_L09_001B294C+WORD(state,0x60)*0x80+0x30,object+0x10);
        func_00282F20(delta,delta,FLOAT(state,0x64));
        func_00282CC0(object+0x10,object+0x10,delta);
        if (func_00282E48(object+0x10,D_L09_001B294C+WORD(state,0x60)*0x80+0x30)<=0.88f)
            func_002A7750(object,3,-1);
        break;
    case 3:
        if (func_002B3868(object)) {
            if (WORD(state,0x6c) != -1) {
                slot = SLOT(WORD(state,0x6c));
                if (*(char **)(slot+0x88) == object && BYTE(slot,0x74))
                    func_002E59F8(WORD(state,0x6c));
            }
            WORD(state,0x6c) = -1;
        }
        slot = SLOT(WORD(state,0x6c));
        if (*(char **)(slot+0x88) != object || !BYTE(slot,0x74))
            WORD(state,0x6c) = func_002E5CF8(1,4,object);
        if (D_00189E20.object!=object)
            func_002A7750(object,4,-1);
        break;
    case 4: {
        if (func_002B3868(object)) {
            if (WORD(state,0x6c) != -1) {
                if (SOUND_SLOT(WORD(state,0x6c))->owner == object && SOUND_SLOT(WORD(state,0x6c))->active)
                    func_002E59F8(WORD(state,0x6c));
            }
            WORD(state,0x6c) = -1;
        }
        if (func_00277258(object+0x10,0x10,object,D_L09_001B17F4) && D_L09_001BFE58)
            break;
        if (SOUND_SLOT(WORD(state,0x6c))->owner != object || !SOUND_SLOT(WORD(state,0x6c))->active)
            WORD(state,0x6c) = func_002E5CF8(0,4,object);
        func_00282CF0(delta,state+0x80,object+0x10);
        func_00282F20(delta,delta,FLOAT(state,0x64));
        func_00282CC0(object+0x10,object+0x10,delta);
        if (func_00282E48(object+0x10,state+0x80)<=0.88f)
            func_002A7750(object,1,-1);
        break;
    }
    }
    func_PAL_L09_00415DA0(object);
    func_PAL_L09_00415E28(object);
    func_00282CF0(delta,object+0x10,old_position);
    func_002AD6F0(state+0x20,delta,old_rotation,object+0xf0);
}

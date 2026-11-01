#include "include_asm.h"

#include "common.h"
extern void func_002A7750(void *, int, int);
extern int func_002A7820(int, int);
extern int func_002B3868(void *);
extern void func_002E59F8(int);
extern char D_00188660[];
extern void func_L14_00432450(void *);
extern int prisonStartSound(int, int, void *) __asm__("func_002E5CF8");
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; void *owner; } PrisonSoundAnchor;
extern int func_00282948(void *);
extern int func_002B3868(void *);
extern void func_002A7750(void *, int, int);
extern int func_00282948(void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_002A7750(void *, int, int);
extern int func_002A7820(int, int);
extern int func_002B3868(void *);
extern void func_002E59F8(int);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern char D_00188660[];
extern void func_L14_00432450(void *);

void func_PAL_L14_00437BB8(char *object)
{
    int *state = *(int **)(object + 0x68);
    switch ((unsigned char)object[0x20]) {
    case 0:
        state[10] += 63;
        state[11] += 63;
        state[12] += 63;
        state[13] += 63;
        state[14] += 63;
        state[15] = 10;
        state[16] = -1;
        func_002A7750(object, 1, -1);
        break;
    case 1:
        func_002A7750(object, func_002A7820(2, 3), -1);
        break;
    case 2:
        if (func_002B3868(object)) {
            if (state[16] != -1 && ((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->owner == object && ((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->active)
                func_002E59F8(state[16]);
            state[16] = -1;
            state[3] = ((s32)(func_002A7820(state[0], state[1])) * 5 + 2) / 6;
        }
        if (((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->owner != object || !((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->active)
            state[16] = prisonStartSound(0, 4, object);
        if (func_00282948(state + 3))
            func_002A7750(object, 1, -1);
        break;
    case 3:
        if (func_002B3868(object)) {
            if (state[16] != -1 && ((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->owner == object && ((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->active)
                func_002E59F8(state[16]);
            state[16] = -1;
            state[3] = ((s32)(func_002A7820(state[0], state[1])) * 5 + 2) / 6;
        }
        if (((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->owner != object || !((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->active)
            state[16] = prisonStartSound(1, 4, object);
        if (func_00282948(state + 3))
            func_002A7750(object, 1, -1);
        break;
    }
    func_L00_002E6EF8(func_L14_00432450, object);
}


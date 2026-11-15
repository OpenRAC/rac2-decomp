#include "include_asm.h"
#include "names.h"

extern int func_002A9640(char *a0, int a1, int a2);

typedef int TI128 __attribute__((mode(TI)));
extern char D_L14_001B1870[8] __attribute__((sda));
extern char D_L14_001B1878[8] __attribute__((sda));
extern int D_L14_001B18A0 __attribute__((sda));
extern void func_002A7750_3(char *a0, int a1, int a2);
extern void func_00282F20(void *out, void *in, float scale);
extern void func_00282CF0(void *out, void *in1, void *in2);
extern void func_00282CC0(void *out, void *in1, void *in2);
extern void func_L00_0032A258(char *, void *, void *, void *, int, int, int, int, int, int, int);
extern void func_002E5CF8(int, int, char *);
extern void func_0029F338(char *a0);

/* Finds a nearby object, fires a beam toward it with a sound, then removes itself. */
void func_L14_00427458(char *self) {
    float beamPoints[2][4] __attribute__((aligned(16)));
    char *state = *(char **)(self + 0x68);
    char *target;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        func_002A7750_3(self, 1, -1);
        break;
    case 1:
        target = (char *)FindOwnedEffectSlot(self, 0x4010000, 0);
        if (target != 0 && *(int *)state == 0) {
            float beamOffset[4] __attribute__((aligned(16)));
            *(TI128 *)beamOffset = 0;
            beamOffset[0] = 3.0f;
            beamOffset[1] = 3.0f;
            vec_scale_to_length(beamPoints[0], target + 0x10, 8.0f);
            vec_scale_to_length(beamPoints[1], target + 0x10, 18.0f);
            FastVecSub(beamPoints[0], beamPoints[0], beamOffset);
            FastVecAdd(beamPoints[1], beamPoints[1], beamOffset);
            ExplodeObjectIntoPieces(self, beamPoints, D_L14_001B1878, D_L14_001B1870, 0xFFFF, 0, D_L14_001B18A0, 8, 0xFFFF, 0xFF, 0);
            PlayMobySound(0, 0, self);
            func_002A7750_3(self, 2, -1);
        }
        *(unsigned char *)(self + 0xA8) = 0xFF;
        break;
    case 2:
        MarkMobySpawned(self);
        break;
    }
}

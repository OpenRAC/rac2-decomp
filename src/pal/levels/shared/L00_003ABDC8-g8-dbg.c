/* func_PAL_L00_003ABDC8, the PAL copy of func_L00_003A8670 (flags in config/cflags.txt: -O2 -G8 -ffunction-sections -g). */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct { char pad[0x2294]; int level; } Context;
extern char D_00189E20[];
extern float D_L00_001AF718 __attribute__((sda));
extern float D_L00_001AF71C __attribute__((sda));
extern float D_L00_001AF724 __attribute__((sda));
extern float D_L00_001AF728 __attribute__((sda));
extern float D_L00_001AF72C __attribute__((sda));
extern float D_L00_001AF730 __attribute__((sda));
extern int D_L00_001AF734 __attribute__((sda));
extern int D_L00_001AF738 __attribute__((sda));
extern float D_L00_001AF73C __attribute__((sda));
extern float D_L00_001AF740 __attribute__((sda));
extern float D_L00_001AF744 __attribute__((sda));
extern char *func_L00_0032A088(int, int);
extern float func_002A7940(void);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern float func_00283CE0(int);

/* The pool's measured stride is 112 bytes, including both nine-float arrays. */
typedef struct {
    TI128 position;
    short duration, active;
    float angle, spin, scale, reciprocal, drift;
    float phase[9], speed[9];
} BeamParticle;

void func_PAL_L00_003ABDC8(TI128 *position, int index)
{
    char *base = func_L00_0032A088(1483, index);
    BeamParticle *entry;
    int i, j;
    Context *context = (Context *)D_00189E20;
    for (i = 0, entry = (BeamParticle *)base; i < 80; ++i, ++entry) {
        if (entry->active == 0) {
            float high;
            entry->active = 1;
            qcopy(&entry->position, position);
            entry->angle = func_002A7940();
            entry->spin = func_002A78D8(D_L00_001AF718, D_L00_001AF71C) * 0.017453294f;
            entry->scale = func_002A7878(D_L00_001AF728, D_L00_001AF724);
            entry->duration = ((s32)func_002A7820(D_L00_001AF734, D_L00_001AF738) * 5 + 2) / 6;
            entry->reciprocal = 1.0f / func_00283CE0(entry->duration);
            if (context->level == 29)
                high = D_L00_001AF744;
            else
                high = D_L00_001AF740;
            entry->drift = func_002A7878(D_L00_001AF73C, high) * 0.020000001f;
            for (j = 0; j < 9; j++) {
                ((BeamParticle *)base)[i].phase[j] = 0.0f;
                ((BeamParticle *)base)[i].speed[j] = func_002A7878(D_L00_001AF72C, D_L00_001AF730);
            }
            return;
        }
    }
}

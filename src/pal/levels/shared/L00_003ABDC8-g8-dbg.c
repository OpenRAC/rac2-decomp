/* func_PAL_L00_003ABDC8, the PAL copy of func_L00_003A8670 (flags in config/cflags.txt: -O2 -G8 -ffunction-sections -g). */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct { char pad[0x2294]; int level; } Context;
extern char g_hero_state[];
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
extern char *level_get_slot_body(int, int);
extern float math_random_angle(void);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern float IntToFloat(int);

/* The pool's measured stride is 112 bytes, including both nine-float arrays. */
typedef struct {
    TI128 position;
    short duration, active;
    float angle, spin, scale, reciprocal, drift;
    float phase[9], speed[9];
} BeamParticle;

void func_PAL_L00_003ABDC8(TI128 *position, int index)
{
    char *base = level_get_slot_body(1483, index);
    BeamParticle *entry;
    int i, j;
    Context *context = (Context *)g_hero_state;
    for (i = 0, entry = (BeamParticle *)base; i < 80; ++i, ++entry) {
        if (entry->active == 0) {
            float high;
            entry->active = 1;
            qcopy(&entry->position, position);
            entry->angle = math_random_angle();
            entry->spin = math_random_signed_float_range(D_L00_001AF718, D_L00_001AF71C) * 0.017453294f;
            entry->scale = math_random_float_range(D_L00_001AF728, D_L00_001AF724);
            entry->duration = ((s32)math_random_int_range(D_L00_001AF734, D_L00_001AF738) * 5 + 2) / 6;
            entry->reciprocal = 1.0f / IntToFloat(entry->duration);
            if (context->level == 29)
                high = D_L00_001AF744;
            else
                high = D_L00_001AF740;
            entry->drift = math_random_float_range(D_L00_001AF73C, high) * 0.020000001f;
            for (j = 0; j < 9; j++) {
                ((BeamParticle *)base)[i].phase[j] = 0.0f;
                ((BeamParticle *)base)[i].speed[j] = math_random_float_range(D_L00_001AF72C, D_L00_001AF730);
            }
            return;
        }
    }
}

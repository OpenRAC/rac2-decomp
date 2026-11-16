#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union EffectVector { Quadword bits; float value[4]; } EffectVector;
extern float IntToFloat(int moby);
extern int math_fast_helper_a(float *moby, float f12);
extern float math_random_float_range(float lo, float hi);
extern void moby_transform_joint_to_world(char *moby, int a1, float *a2);
extern char *part_spawn_scaling(float *moby, float *a1, int a2, int a3, int t0, int t1, int t2, int t3);
extern int FloatToInt(float pos);

/* func_L09_003FEA48 is defined in L09_003FEA48-g8.velocity (this unit has no $gp access for it). */

/* func_L09_003FEAE8 is defined in L09_003FEAE8-g8.velocity. */

/* Spawns red and white sparkle particles that float up from two joints of the object (PAL: 50 Hz speed). */
void part_spawn_joint_sparkles_pal(char *moby) {
    EffectVector pos;
    EffectVector joint_pos;
    EffectVector velocity;
    EffectVector spawn_vel;
    int i;
    int j;
    char *part;

    qcopy(pos.value, moby + 0x10);
    pos.value[3] = 6.0f;
    if (math_fast_helper_a(pos.value, IntToFloat(*(s16 *)(moby + 0x32))) == -1)
        return;
    for (i = 12; i < 14; i++) {
        spawn_vel.bits = 0;
        spawn_vel.value[2] = -(math_random_float_range(3.5f, 4.5f) * 0.020000001f);
        velocity.bits = spawn_vel.bits;
        for (j = 0; j < 2; j++) {
            moby_transform_joint_to_world(moby, i, joint_pos.value);
            joint_pos.value[2] += IntToFloat(j) * 0.015f + 0.5f;
            if (j & 1)
                part = part_spawn_scaling(joint_pos.value, velocity.value, 0x77FF0000, 0x00FF0060, 0x10, 200, -100, 1);
            else
                part = part_spawn_scaling(joint_pos.value, velocity.value, 0x77FF0060, 0x00FF0000, 0x11, 300, -100, 1);
            if (part)
                part[9] = ((*(s16 *)(moby + 0x32) >> 5) << 4) + FloatToInt(0.0f);
            part = part_spawn_scaling(joint_pos.value, velocity.value, 0x77FFFFFF, 0x00FF0000, 0xA, 100, -100, 1);
            if (part)
                part[9] = ((*(s16 *)(moby + 0x32) >> 5) << 4) + FloatToInt(0.0f);
        }
    }
}




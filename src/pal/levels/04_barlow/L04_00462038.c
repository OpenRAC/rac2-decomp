#include "include_asm.h"

#include "common.h"
extern int part_find_owned_effect_slot(unsigned char *obj, int a1, int a2);
extern void PlayMobySound(int a0, int a1, unsigned char *obj);
extern void vec_random_direction(float *vec, float f12, float f13);
extern float math_fabs(float value);
extern void func_PAL_L00_00328480(unsigned char *obj, float *pos, int a2, int a3, float *vel, float f12, float f13, float f14, float f15, int color, int t2);
extern void moby_mark_spawned(unsigned char *obj);

/* Throws two puffs of the effect at the object's position, lifted by 0.75, then flags the object and updates it twice. */
void func_PAL_L04_00462038(unsigned char *obj)
{
    float vel[4];
    float pos[4];

    if (part_find_owned_effect_slot(obj, 0x10000, 0) != 0) {
        PlayMobySound(0, 0, obj);
        qcopy(pos, obj + 0x10);
        pos[2] += 0.75f;
        vec_random_direction(vel, 0.080000006f, 0.120000005f);
        vel[2] = math_fabs(vel[2]) * 1.5f;
        func_PAL_L00_00328480(obj, pos, 15, 1, vel, 0.5f, 3.0f, 0.75f, 1.25f, 0x50404040, 0);
        vec_random_direction(vel, 0.080000006f, 0.120000005f);
        vel[2] = math_fabs(vel[2]) * 1.5f;
        func_PAL_L00_00328480(obj, pos, 15, 1, vel, 0.5f, 3.0f, 0.75f, 1.25f, 0x50404040, 0);
        obj[0xA8] = 0xFF;
        moby_mark_spawned(obj);
        moby_mark_spawned(obj);
    }
}


#include "names.h"
/* func_L01_003B4480 in its own unit: it copies 128 bits, and the retail's copy keeps
   both addresses in registers, which is the compiler's opt-in grouped copy
   (-frac2-qcopy, config/cflags.txt). The flag changes every TImode copy in a unit,
   so the unit holds this function alone. */

#include "common.h"

/* The 128-bit integer mode is what reaches retail's lq/sq copies. */
typedef int V4 __attribute__((mode(TI)));

extern float coll_probe_ground_height_below(void *a0, int a1, float f12);
extern int GetCollHitMaterial(void);
extern void vec_add_random_offset(float *v, float f);
extern float level_get_water_height(void);
extern float math_random_float_range(float a, float b);
extern int math_random_int_below(int a);
extern void *part_spawn_drifting(char *a0, int a1, int a2, float f12, float f13);
extern float FastVecLength(void *a0);
extern void part_spawn_water_splash_effects(void *a0, int a1, int a2, int a3);

/* The float the second argument of func_002C19D8 points at. */
extern f32 g_water_l01_height[];

/* Makes bubbles rise from the object when the game is in the right mode, and a splash when the object is moving fast. */
void swamp_beast_spawn_bubbles(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    float bubble_pos[4];
    float value;
    int i;

    coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
    if (GetCollHitMaterial() != 3)
        return;
    {
        u8 *src_pos = object + 0x10;
        u8 *speed_vec = state + 0xE0;
        i = 0;
        while (i >= 0) {
            *(V4 *)bubble_pos = *(V4 *)src_pos;
            vec_add_random_offset(bubble_pos, 0.15f);
            bubble_pos[2] = level_get_water_height();
            value = math_random_float_range(0.3f, 2.5f);
            part_spawn_drifting((char *)bubble_pos, (int)g_water_l01_height,
                          (int)((((u32)math_random_int_below(6) + 0x14) << 24) | 0x5060), value, 11000.0f);
            i--;
        }
        value = 0.0333333333f;
        if (value < FastVecLength(speed_vec) || value < FastVecLength(state + 0x2F0))
            part_spawn_water_splash_effects(object, 3, 10, 1);
    }
}

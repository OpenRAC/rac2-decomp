#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float g_breakable_corner_table[16] __attribute__((sda));
extern int g_breakable_piece_lifetime __attribute__((sda));
extern float g_breakable_piece_spread_range[2] __attribute__((sda));
extern float g_breakable_piece_speed_range[2] __attribute__((sda));
extern float g_breakable_piece_offset[4] __attribute__((sda));
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_local_offset_to_world(void *, void *, float, float, float);
extern void vec_local_to_world(void *, void *, float, float, float);
extern void *part_spawn_object_following_effect(void *, void *, int, int, int, int, int, int, float, float);
extern void part_explode_object_into_pieces_pal(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern float math_random_float_range(float, float);
extern void moby_mark_spawned(void *);

/* Breakable object: lights up its corners, breaks into pieces when its effect slot is hit, then explodes (PAL: 50 Hz speeds). */
void breakable_l18_object_update_pal(u8 *obj) {
    float offset[4] __attribute__((aligned(16)));
    float corner_a[4] __attribute__((aligned(16)));
    float corner_b[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68), *effect;
    int i, x, y;
    float *corner, *corner_a_ptr, *corner_b_ptr;

    switch (obj[0x20]) {
    case 0:
        i = 0;
        corner_b_ptr = corner_b;
        corner_a_ptr = corner_a;
        y = 20;
        x = 4;
        corner = g_breakable_corner_table;
        for (; i < 4; i++, y -= 8, x -= 8, corner += 4) {
            FastVecScale(offset, corner, *(float *)(obj + 0x2C));
            part_spawn_object_following_effect(offset, obj, 0x28808080, -1, 0, -1, 0, 0x60,
                             *(float *)(obj + 0x2C) * 1050000.f, .15f);
            vec_local_offset_to_world(obj, corner_a_ptr, corner[0], corner[1], corner[2]);
            qcopy(corner_b_ptr, corner_a_ptr);
            if (i < 2) {
                vec_local_to_world(obj, corner_b_ptr, (float)x, 0, -4.f);
            } else {
                vec_local_to_world(obj, corner_b_ptr, 0, (float)y, -4.f);
            }
            corner_a[3] = .2f;
            corner_b[3] = 1.f;
        }
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        effect = part_find_owned_effect_slot(obj, 0x4010000, 0);
        if (effect && !*(int *)state) {
            *(TI128 *)corner_b = 0;
            corner_b[0] = 3.f;
            corner_b[1] = 3.f;
            *(float *)(effect + 0x18) = .75f;
            FastVecScale(offset, effect + 0x10, math_random_float_range(6.f, 8.f));
            qcopy(corner_a, offset);
            FastVecSub(offset, offset, corner_b);
            FastVecAdd(corner_a, corner_a, corner_b);
            part_explode_object_into_pieces_pal(obj, offset, g_breakable_piece_spread_range, g_breakable_piece_speed_range,
                             0xFFFF, -1, g_breakable_piece_lifetime, 9, -128, 255, 0);
            moby_set_state(obj, 2, -1);
        }
        obj[0xA8] = 255;
        break;
    case 2:
        part_explode_object_into_pieces_pal(obj, g_breakable_piece_offset, g_breakable_piece_spread_range, g_breakable_piece_speed_range,
                         0xFFFF, 0, g_breakable_piece_lifetime, 6, 0xFA7F, 255, 0);
        vec_local_offset_to_world(obj, offset, 0, 0, 20.f);
        SpawnExplosion_pal(offset, 0, 5, 5, 5, 5, 5, 0, 1, 0, 1, 0,
                      *(float *)(obj + 0x2C) * 2.f, 20.f);
        moby_mark_spawned(obj);
        break;
    }
}

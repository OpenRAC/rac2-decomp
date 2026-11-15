#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L18_001B1B40[16] __attribute__((sda));
extern int D_L18_001B1B30 __attribute__((sda));
extern float D_L18_001B1B08[2] __attribute__((sda));
extern float D_L18_001B1B00[2] __attribute__((sda));
extern float D_L18_001B1B10[4] __attribute__((sda));

extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_local_offset_to_world(void *, void *, float, float, float);
extern void vec_local_to_world(void *, void *, float, float, float);
extern void part_spawn_object_following_effect(void *, void *, int, int, int, int, int, int, float, float);
extern void part_explode_object_into_pieces(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern void SpawnExplosion(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern int moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern float math_random_float_range(float, float);
extern void moby_mark_spawned(void *);

/* Updates a breakable object (moby class 4484): it sets up its glow, waits to be hit, then releases a burst and an explosion and disappears. */
void breakable_l18_object_update(u8 *obj) {
    float offset[4] __attribute__((aligned(16)));
    float pos_a[4] __attribute__((aligned(16)));
    float pos_b[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68), *hit;
    int i, x_offset, y_offset;
    float *corner, *pos_a_cursor, *pos_b_cursor;

    switch (obj[0x20]) {
    case 0:
        i = 0;
        pos_b_cursor = pos_b;
        pos_a_cursor = pos_a;
        y_offset = 20;
        x_offset = 4;
        corner = D_L18_001B1B40;
        for (; i < 4; i++, y_offset -= 8, x_offset -= 8, corner += 4) {
            FastVecScale(offset, corner, *(float *)(obj + 0x2C));
            part_spawn_object_following_effect(offset, obj, 0x28808080, -1, 0, -1, 0, 0x60,
                             *(float *)(obj + 0x2C) * 1050000.f, .15f);
            vec_local_offset_to_world(obj, pos_a_cursor, corner[0], corner[1], corner[2]);
            qcopy(pos_b_cursor, pos_a_cursor);
            if (i < 2) {
                vec_local_to_world(obj, pos_b_cursor, (float)x_offset, 0, -4.f);
            } else {
                vec_local_to_world(obj, pos_b_cursor, 0, (float)y_offset, -4.f);
            }
            pos_a[3] = .2f;
            pos_b[3] = 1.f;
        }
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        hit = part_find_owned_effect_slot(obj, 0x4010000, 0);
        if (hit && !*(int *)state) {
            *(TI128 *)pos_b = 0;
            pos_b[0] = 3.f;
            pos_b[1] = 3.f;
            *(float *)(hit + 0x18) = .75f;
            FastVecScale(offset, hit + 0x10, math_random_float_range(6.f, 8.f));
            qcopy(pos_a, offset);
            FastVecSub(offset, offset, pos_b);
            FastVecAdd(pos_a, pos_a, pos_b);
            part_explode_object_into_pieces(obj, offset, D_L18_001B1B08, D_L18_001B1B00,
                             0xFFFF, -1, D_L18_001B1B30, 9, -128, 255, 0);
            moby_set_state(obj, 2, -1);
        }
        obj[0xA8] = 255;
        break;
    case 2:
        part_explode_object_into_pieces(obj, D_L18_001B1B10, D_L18_001B1B08, D_L18_001B1B00,
                         0xFFFF, 0, D_L18_001B1B30, 6, 0xFA7F, 255, 0);
        vec_local_offset_to_world(obj, offset, 0, 0, 20.f);
        SpawnExplosion(offset, 0, 5, 5, 5, 5, 5, 0, 1, 0, 1, 0,
                      *(float *)(obj + 0x2C) * 2.f, 20.f);
        moby_mark_spawned(obj);
        break;
    }
}

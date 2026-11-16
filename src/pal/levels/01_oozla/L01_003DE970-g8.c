#include "include_asm.h"

#include "common.h"
extern f32 g_falling_object_target_scale __attribute__((sda));
extern f32 g_falling_object_scale_blend __attribute__((sda));
extern f32 g_falling_object_spin_rate __attribute__((sda));
extern f32 g_falling_object_collision_radius __attribute__((sda));
extern u8 *g_hit_l01_result __attribute__((nosda));
typedef struct { u8 pad[0x2290]; s32 collision; } CameraAB;
extern CameraAB g_hero_state;
extern void FastVecAdd(void *, void *, void *);
extern void func_PAL_L01_003DED38(void *);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern f32 func_PAL_L01_003BEB40(void);
extern s32 coll_test_point(void *, s32, f32, s32);
extern void func_PAL_L01_003DE970(void *, void *);
extern int coll_cast_object_line(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern void vec_scale_to_length(void *, void *, f32);
extern void moby_mark_spawned(void *);
extern void part_queue_ground_shadow(void *, f32);

void func_PAL_L01_003DF218(u8 *obj) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 bottom[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    f32 height;
    *(f32 *)(obj + 0x2C) += (*(f32 *)(*(u8 **)(obj + 0x24) + 0x24) * g_falling_object_target_scale - *(f32 *)(obj + 0x2C)) * g_falling_object_scale_blend;
    qcopy(pos, obj + 0x10);
    FastVecAdd(obj + 0x10, obj + 0x10, state);
    func_PAL_L01_003DED38(obj);
    if ((obj[0x60] & 2) && obj[0x43] != 1) func_PAL_002A7E68(obj, 1, 0, 10);
    height = func_PAL_L01_003BEB40();
    if ((coll_test_point(obj + 0x10, 0, g_falling_object_collision_radius, *(s32 *)(state + 0x10)) &&
          (!g_hit_l01_result || *(s16 *)(g_hit_l01_result + 0xAA) != 0x660)) || *(f32 *)(obj + 0x18) < height) {
        func_PAL_L01_003DE970(obj, state);
        qcopy(bottom, obj + 0x10);
        bottom[2] -= 6.0f;
        coll_cast_object_line(g_hero_state.collision, obj + 0x10, bottom, 0.0001f, 1.0f, 1, 0, 1, 0);
        vec_scale_to_length(state, state, g_falling_object_collision_radius);
        *(s32 *)(state + 8) = 0;
        FastVecAdd(obj + 0x10, obj + 0x10, state);
        FastVecAdd(bottom, bottom, state);
        coll_cast_object_line(g_hero_state.collision, obj + 0x10, bottom, 0.0001f, 1.0f, 1, 0, 1, 0);
        moby_mark_spawned(obj);
    } else {
        *(f32 *)(state + 8) -= g_falling_object_spin_rate * 0.00040000002f;
        if (*(f32 *)(obj + 0x10) < 2.0f || *(f32 *)(obj + 0x10) > 1021.0f ||
            *(f32 *)(obj + 0x14) < 2.0f || *(f32 *)(obj + 0x14) > 1021.0f ||
            *(f32 *)(obj + 0x18) < 2.0f || *(f32 *)(obj + 0x18) > 1021.0f) { moby_mark_spawned(obj); return; }
        part_queue_ground_shadow(obj, *(f32 *)(obj + 0x2C) / *(f32 *)(*(u8 **)(obj + 0x24) + 0x24));
    }
}

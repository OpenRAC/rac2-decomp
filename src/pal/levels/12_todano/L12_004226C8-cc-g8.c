#include "names.h"
/* func_PAL_L12_004226C8, the PAL copy of func_L12_0041D3B0: the same C, where rename func_0032C700 becomes func_PAL_L00_003FB330; rename func_002B0A68 becomes func_PAL_002B15D8; rename func_L12_0041E8F8 becomes func_PAL_L12_00423C50; scale D_L12_001B1DC0 / 2; wrap D_L12_001B1DC0 (((int)({e}) * 5 + 2) / 6). */
#include "common.h"

extern struct { u8 pad[0x464]; u8 flags[0]; } g_object_flags;
extern u8 g_moby_nibble_table[];
extern s32 g_current_map_index __attribute__((sda));
extern u8 *g_moby_list_start MACRO_ADDR;
extern u8 *D_L12_001B2E9C_gp SDATA(D_L12_001B2E9C);
extern s32 g_break_child_duration __attribute__((sda));
/* The burst helper reads a vector at this GP-relative address. */
extern f32 g_explosion_position_offset[] SDATA(D_L12_001B1DD0);
extern u8 g_hero_position[];

extern void moby_mark_spawned(void *);
extern s32 linked_moby_is_finished(void *);
extern void linked_moby_trigger_burst_pal(void *);
extern void moby_set_state(void *, s32, s32);
extern s32 math_fast_float_d(void *);
/* Eight GPR inputs, four stack inputs and two FP inputs, in their EE ABI order. */
extern void *SpawnExplosion_pal(void *, s32, s32, s32, s32, s32, s32, s32,
                         s32, s32, s32, s32, f32, f32);
extern void FastVecSub(void *, void *, void *);
extern void vec_transform_and_set_height(void *, void *, void *, void *, f32);
extern void vec_scale_to_length(void *, void *, f32);
extern void part_spawn_masked_debris_pal(void *, s32, void *, u8, f32, f32, f32, f32);

/* Waits for three linked mobys to be ready, lifts them, then blows up and leaves a burst of effects (PAL: 50 Hz timings). */
void UpdateThreeChildRiseController_pal(u8 *self)
{
    u8 *vars = *(u8 **)(self + 0x68);
    s32 ready;
    f32 push_vec[4] __attribute__((aligned(16)));

    switch (self[0x20]) {
    case 0: {
        u16 object_id;
        s32 packed;

        self[0x20] = 1;
        *(f32 *)(vars + 0x10) = *(f32 *)(self + 0x18);
        object_id = *(u16 *)(self + 0xB2);
        if (g_object_flags.flags[(s16)object_id])
            goto Destroy0;
        packed = g_moby_nibble_table[((s16)object_id >> 1) + (g_current_map_index << 10)];
        if (object_id & 1) {
            if ((packed >> 4) & 7)
                goto Destroy0;
            return;
        } else {
            if (!(packed & 7))
                return;
        }
Destroy0:
        moby_mark_spawned(self);
        break;
    }
    case 1: {
        s32 *links;
        s32 i;

        ready = 1;
        links = (s32 *)vars;
        for (i = 0; i < 3; i++) {
            if (links[i] != -1) {
                if (!linked_moby_is_finished(D_L12_001B2E9C_gp + (links[i] << 8)))
                    ready = 0;
            }
        }
        if (ready)
            self[0x20] = 2;
        break;
    }
    case 4: {
        u8 *list_base = g_moby_list_start;
        s32 *links;
        s32 i;

        *(f32 *)(vars + 0xC) += 0.002f;
        *(f32 *)(self + 0x18) += *(f32 *)(vars + 0xC);
        links = (s32 *)vars;
        for (i = 0; i < 3; i++) {
            if (links[i] != -1)
                *(f32 *)((links[i] << 8) + (u32)list_base + 0x18) += *(f32 *)(vars + 0xC);
        }
        if (*(f32 *)(vars + 0x10) + 8.0f < *(f32 *)(self + 0x18))
            self[0x20] = 5;
        break;
    }
    case 2:
        moby_set_state(self, 3, -1);
        *(s32 *)(vars + 0x14) = (((int)(g_break_child_duration) * 5 + 2) / 6);
        break;

    case 3: {
        s32 *links;
        s32 i;
        s32 *links2;
        s32 j;

        if (math_fast_float_d(vars + 0x14)) {
            SpawnExplosion_pal(g_explosion_position_offset, 1, 14, 10, 15, 10, 20, 1,
                          1, 1, 0, 0, 2.0f, 20.0f);
            *(s32 *)(self + 0x98) = 0;
            *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) | 0x41) & 0xEFFF;
            FastVecSub(push_vec, self + 0x10, g_hero_position);
            vec_transform_and_set_height(self, push_vec, push_vec, 0, 0.0f);
            vec_scale_to_length(push_vec, push_vec, 0.120000005f);
            part_spawn_masked_debris_pal(self, 0xFFF, push_vec, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
            moby_set_state(self, 5, -1);
            links = (s32 *)vars;
            for (i = 0; i < 3; i++) {
                if (links[i] != -1) {
                    D_L12_001B2E9C_gp[(links[i] << 8) + 0x20] = 4;
                    linked_moby_trigger_burst_pal(g_moby_list_start + (links[i] << 8));
                }
            }
        }
        if (*(s32 *)(vars + 0x14) == (((int)(g_break_child_duration / 2) * 5 + 2) / 6)) {
            links2 = (s32 *)vars;
            for (j = 0; j < 3; j++) {
                if (links2[j] != -1)
                    D_L12_001B2E9C_gp[(links2[j] << 8) + 0x20] = 4;
            }
        }
        break;
    }
    case 5: {
        u8 *list_base, *child, *counter;
        u16 object_id;
        s32 *links;
        s32 i;

        links = (s32 *)vars;
        for (i = 0; i < 3; i++) {
            if (links[i] != -1) {
                list_base = D_L12_001B2E9C_gp;
                child = (u8 *)((links[i] << 8) + (u32)list_base);
                *(u16 *)(child + 0x34) &= 0xEFFF;
                moby_mark_spawned(list_base + (links[i] << 8));
            }
        }
        object_id = *(u16 *)(self + 0xB2);
        if (object_id & 1) {
            counter = &g_moby_nibble_table[((s16)object_id >> 1) + (g_current_map_index << 10)];
            if (((*counter >> 4) & 7) != 7)
                *counter += 16;
        } else {
            counter = &g_moby_nibble_table[((s16)object_id >> 1) + (g_current_map_index << 10)];
            if ((*counter & 7) != 7)
                *counter += 1;
        }
        moby_mark_spawned(self);
        break;
    }
    }
}

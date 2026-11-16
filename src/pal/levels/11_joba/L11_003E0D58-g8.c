#include "names.h"
/* func_PAL_L11_003E0D58, the PAL copy of func_L11_003DCEB0: the same C, where 0x79 becomes 0x65;
   func_002ABBB8 becomes func_PAL_002AC718. */
#include "common.h"

extern f32 g_bomb_fall_rate __attribute__((sda));
extern f32 g_bomb_velocity_scale __attribute__((sda));
extern f32 g_bomb_explosion_size __attribute__((sda));
extern u8 g_aim_position[];
extern u8 g_identity_l11_matrix[] __attribute__((sda));
extern s32 CollLine(void *, void *, s32, void *, s32);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int PlayMobySound(s32, s32, u8 *);
extern void moby_mark_spawned(u8 *);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void moby_set_state(void *, int, int);

void func_PAL_L11_003E0D58(u8 *a0) {
    u8 vec[16] __attribute__((aligned(16)));
    u8 *s0 = *(u8 **)(a0 + 0x68);
    s32 flag = 0;
    u8 state = a0[0x20];

    switch (state) {
    case 0:
        FastVecAdd(vec, a0 + 0x10, s0);
        *(f32 *)(s0 + 8) = *(f32 *)(s0 + 8) - *(f32 *)(s0 + 0xC);
        if (CollLine(a0 + 0x10, vec, 2, 0, 0) != 0) {
            qcopy(a0 + 0x10, g_aim_position);
            *(f32 *)(a0 + 0x18) = *(f32 *)(a0 + 0x18) + g_bomb_fall_rate * g_bomb_velocity_scale;
            moby_set_state(a0, 1, -1);
        } else {
            qcopy(a0 + 0x10, vec);
        }
        break;
    case 1:
        *(u16 *)(a0 + 0x96) += 1;
        if (*(u16 *)(a0 + 0x96) >= 0x65) flag = state;
        break;
    }
    if (part_find_owned_effect_slot(a0, -1, 0) != 0 || flag != 0) {
        SpawnExplosionEffects_pal(a0, g_identity_l11_matrix, a0 + 0x10, g_bomb_explosion_size, 1.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
        PlayMobySound(0, 0, a0);
        moby_mark_spawned(a0);
    }
}

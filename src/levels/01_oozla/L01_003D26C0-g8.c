#include "common.h"

extern u8 g_sound_state[];
extern u8 *g_moby_l01_table MACRO_ADDR;
extern u8 *D_L01_001FE180[];
extern f32 D_L01_001B0540 __attribute__((sda));

extern s32 AdvancePointAlongPolyline(u8 *object, u8 *entry, void *out, s32 current, s32 direction, f32 step);
extern s32 PlayMobySound(s32 a0, s32 a1, void *a2);
extern void moby_mark_spawned(void *a0);
extern void FastVecSub(void *a0, void *a1, void *a2);
extern void mat_combine_and_store(void *a0, void *a1, void *a2, void *a3);

/* Moves a launched object along its path and removes it at the end. */
void launched_projectile_update(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *launcher_vars = *(u8 **)(*(u8 **)(vars + 0x70) + 0x68);
    u8 *path_table;
    u8 *sound_handle;
    f32 move_delta[4];

    *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24) * D_L01_001B0540;
    qcopy(vars + 0x60, moby + 0x10);
    path_table = D_L01_001FE180[*(s32 *)(vars + 0x74)];
    *(s32 *)(vars + 0x78) =
        AdvancePointAlongPolyline(moby, path_table, moby + 0x10, *(s32 *)(vars + 0x78), 1,
                          *(f32 *)(launcher_vars + 0x20) * 0.016666668f);
    if (*(f32 *)(moby + 0x18) < *(f32 *)(vars + 0x68)) {
        if (!(*(u16 *)(vars + 0x7C) & 0x80)) {
            PlayMobySound(1, 0, moby);
            *(u16 *)(vars + 0x7C) = *(u16 *)(vars + 0x7C) | 0x80;
        }
        g_moby_l01_table[(*(s32 *)(*(u8 **)(*(u8 **)(vars + 0x70) + 0x68) + 0xC) << 8) + 0xBC] = 1;
    }
    sound_handle = g_sound_state + *(s16 *)(vars + 0x7E) * 0x70;
    if (*(u8 **)(sound_handle + 0x88) != moby || sound_handle[0x74] == 0)
        *(s16 *)(vars + 0x7E) = PlayMobySound(0, 4, moby);
    if (*(s32 *)(vars + 0x78) == *(s32 *)path_table - 1) {
        g_moby_l01_table[(*(s32 *)(*(u8 **)(*(u8 **)(vars + 0x70) + 0x68) + 0xC) << 8) + 0xBC] = 0;
        moby_mark_spawned(moby);
    } else {
        FastVecSub(move_delta, moby + 0x10, vars + 0x60);
        mat_combine_and_store(vars + 0x20, move_delta, moby + 0xF0, moby + 0xF0);
        qcopy(vars + 0x60, moby + 0x10);
    }
}

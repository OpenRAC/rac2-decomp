#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int s32;
typedef float f32;

/* The current level: read through $gp only from a branch delay slot, absolute elsewhere. */
extern s32 g_current_map_index __attribute__((section(".sdata")));

/* One done flag per slot. `sda` on an unsized array makes cc1 emit the `la` macro, so the
   `lui`/`addiu` pair stays together, as in retail. */
extern u8 g_collection_progress_flags[] __attribute__((sda));

extern char g_hero_position[];

extern u8 g_nanotech_upgrade_flag __attribute__((nosda));

extern unsigned short g_nanotech_upgrade_flag_2 __attribute__((nosda));

extern u8 *g_nanotech_upgrade_moby __attribute__((sda));

extern u8 *g_nanotech_scan_list __attribute__((sda));

/* Four offsets of 16 bytes, addressed from $gp: declared as one float so cc1 keeps it small. */
extern f32 g_nanotech_offset_matrix __attribute__((sda));

extern f32 g_nanotech_pos_length __attribute__((sda));

extern f32 g_nanotech_drift_speed __attribute__((sda));

extern s32 g_nanotech_particle_size __attribute__((sda));

extern f32 g_nanotech_spin_rate __attribute__((sda));

extern f32 g_nanotech_spin_rates[3] __attribute__((sda));

extern f32 g_nanotech_bob_scale __attribute__((sda));

extern f32 FastAddRotations(f32, f32);
extern void moby_mark_spawned(u8 *);
extern void vec_scale_to_length(u8 *, u8 *, f32);
extern void FastVecAdd(u8 *, u8 *, u8 *);
extern void FastVecSub(float *, u8 *, u8 *);
extern float fast_vec_dist(void *, void *);
extern void euler_rotation_basis(void *, void *);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_random_float_range(float, float);
extern u8 *part_spawn_fading_drift(void *, void *, int, int, int, int, int, float, float, float, int);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void hud_queue_hint_message(int, int);
extern void moby_init_random_colors_pal(u8 *);
extern void gfx_draw_glow_ring_sprites_pal(u8 *);

/* Updates a nanotech upgrade pickup (PAL: 50 Hz timings).
   func_PAL_L06_004695FC, the PAL copy of func_L03_00424C40: the same C with the spin and speed
   constants scaled to 50 Hz, the particle lifetime as well, and its callees the PAL copies.
   The loop counts up over the table: reversed by loop.c, its counter and pointer are compiler
   pseudos, not user variables that lose their equivalence, so the hoisted divisor is the one
   left without a saved register and is rematerialised in the loop. */
/* A three-state object: state 0 arms it (and on level 5 finds the entity of class 0xFBF),
   state 1 spins its four angles and throws four particles each frame until the player (or that
   entity on level 5) comes near, state 2 marks its slot done and removes it. */
void nanotech_l06_upgrade_update_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 rot_matrix[12];
    f32 drift_dir[4];
    f32 pos[4];
    f32 (*offset_rows)[4];
    u8 *center;
    u8 *moby_pos;
    u8 *moby_pos_copy;
    u8 *scan_moby;
    u8 *found_moby;
    s32 lifetime;
    s32 i;
    f32 hero_dist;

    switch (moby[0x20]) {
    case 0:
        moby[0x20] = 1;
        moby[0xBC] = 0;
        *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24) * 1.1f;
        if (g_collection_progress_flags[*(s32 *)vars] == 1) {
            moby_mark_spawned(moby);
            return;
        }
        if (g_current_map_index == 5 && g_nanotech_upgrade_moby == 0 && (scan_moby = g_nanotech_scan_list) != 0) {
            s32 class_id = 0xFBF;     /* in a register: retail compares with `xor`, not `xori` */
            found_moby = 0;
            do {
                if (*(short *)(scan_moby + 0xAA) == class_id)
                    found_moby = scan_moby;
                scan_moby = *(u8 **)(scan_moby + 0x28);
            } while (scan_moby != 0);
            g_nanotech_upgrade_moby = found_moby;
        }
        moby_init_random_colors_pal(moby);
        return;
    case 1:
        /* Retail keeps the position in two registers (the first test's and a copy for the
           rest); with this unit's -fno-gcse the copy after the first call gives both. */
        moby_pos = moby + 0x10;
        *(f32 *)(moby + 0xF8) = FastAddRotations(*(f32 *)(moby + 0xF8), 0.03f);
        hero_dist = fast_vec_dist(g_hero_position, moby_pos);
        moby_pos_copy = moby_pos;
        if (hero_dist < 1.5f)
            moby[0x20] = 2;
        if (g_current_map_index == 5 && g_nanotech_upgrade_moby != 0) {
            if (fast_vec_dist(g_nanotech_upgrade_moby + 0x10, moby_pos_copy) < 3.0f)
                moby[0x20] = 2;
        }
        center = moby_pos_copy;
        *(f32 *)(vars + 0x50) = FastAddRotations(*(f32 *)(vars + 0x50), g_nanotech_spin_rate * 0.0003490659f);
        *(f32 *)(vars + 0x54) = FastAddRotations(*(f32 *)(vars + 0x54), g_nanotech_spin_rates[0] * 0.0003490659f);
        *(f32 *)(vars + 0x58) = FastAddRotations(*(f32 *)(vars + 0x58), g_nanotech_spin_rates[1] * 0.0003490659f);
        *(f32 *)(vars + 0x5C) = FastAddRotations(*(f32 *)(vars + 0x5C), g_nanotech_spin_rates[2] * 0.0003490659f);
        euler_rotation_basis(rot_matrix, vars + 0x50);
        offset_rows = (f32 (*)[4])&g_nanotech_offset_matrix;
        for (i = 0; i < 4; i++) {
            lifetime = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            matrix_mul_vec3(pos, offset_rows[i], rot_matrix);
            vec_scale_to_length((u8 *)pos, (u8 *)pos, g_nanotech_pos_length);
            FastVecAdd((u8 *)pos, (u8 *)pos, center);
            FastVecSub(drift_dir, center, (u8 *)pos);
            vec_scale_to_length((u8 *)drift_dir, (u8 *)drift_dir, g_nanotech_drift_speed * 0.020000001f);
            part_spawn_fading_drift(pos, drift_dir, ((s32)(g_nanotech_particle_size) * 5 + 2) / 6, 0x804020, lifetime, 0, 0x6F,
                          math_random_float_range(0.07f, 0.12f) * 210000.0f, 42000.0f, 0.0f, 6);
        }
        *(f32 *)(moby + 0xF0) = math_fast_sin_or_cos_a(*(f32 *)(vars + 0x5C)) * g_nanotech_bob_scale;
        *(f32 *)(moby + 0xF4) = math_fast_sin_or_cos_b(*(f32 *)(vars + 0x5C)) * g_nanotech_bob_scale;
        gfx_draw_glow_ring_sprites_pal(moby);
        return;
    case 2:
        g_collection_progress_flags[*(s32 *)vars] = 1;
        if (*(s32 *)vars == 0)
            g_nanotech_upgrade_flag = 1;
        if (g_nanotech_upgrade_flag_2 == 0)
            hud_queue_hint_message(0xA31, 0x88);
        moby_mark_spawned(moby);
        return;
    }
}

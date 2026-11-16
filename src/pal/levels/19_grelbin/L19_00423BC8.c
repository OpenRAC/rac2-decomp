#include "include_asm.h"




#include "common.h"
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void moby_set_state(void *, int, int);
extern s32 g_current_map_index __attribute__((sda));
extern u8 g_moby_group_flags[];
extern u8 *g_moby_l19_array[] __attribute__((sda));
extern char g_sound_state[];
extern float g_particle_effect_template[] MACRO_ADDR;
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern int PlayMobySound(int, int, void *);
extern float fast_vec_dist(void *, void *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void gfx_draw_beam_along_heading(void *);
extern void make_hit_descriptor(float, void *, void *, int, void *);
extern int CollLine(void *, void *, int, void *, void *);
extern u16 *g_group_ptr_table[];
extern u8 *g_moby_l19_array[] __attribute__((sda));
extern s32 g_max_l19_group_index[] __attribute__((sda));
extern s32 g_current_map_index __attribute__((sda));
extern u8 g_moby_group_flags[];
extern s32 flag_is_third_pending_set(u8 *);
extern float g_group_release_speed_min_a[] SDATA(D_L19_001B1ECC);
extern float g_group_release_speed_max_a[] SDATA(D_L19_001B1ED0);
extern float g_group_release_speed_min_b[] SDATA(D_L19_001B1ED4);
extern float g_group_release_speed_max_b[] SDATA(D_L19_001B1ED8);
extern u8 g_group_release_glow_alpha[] SDATA(D_L19_001B1EDC);
extern int g_group_release_particle_type_a[] SDATA(D_L19_001B1EE0);
extern int g_group_release_particle_type_b[] SDATA(D_L19_001B1EE4);
extern float g_group_release_particle_scale_a[] SDATA(D_L19_001B1EE8);
extern float g_group_release_particle_scale_b[] SDATA(D_L19_001B1EEC);
extern u32 g_group_release_color_start[] SDATA(D_L19_001B1EF0);
extern u32 g_group_release_color_end[] SDATA(D_L19_001B1EF4);
extern int g_group_release_fade_param_a[] SDATA(D_L19_001B1EFC);
extern int g_group_release_fade_param_b[] SDATA(D_L19_001B1F00);

/* Moves the object between two points. State 0 records its home position and builds the far
   point (along the axis at 0xC0, raised by the first state word); state 1 waits for its trigger
   flag or for its linked entity to leave state 0; states 2 and 3 move it out and back, keeping
   its looping sound alive, and then cast a collision line along the axis at 0xE0. */
void UpdateGrelbinTriggeredShuttle_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float offset[4] __attribute__((aligned(16)));
    char query[0x30] __attribute__((aligned(16)));
    char *sound;

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        vec_scale_to_length(offset, moby + 0xC0, *(float *)(vars + 4));
        FastVecAdd(vars + 0x30, offset, moby + 0x10);
        *(float *)(vars + 0x38) += *(float *)vars;
        qcopy(vars + 0x20, moby + 0x10);
        *(int *)(vars + 0x40) = -1;
    case 1:
        if ((*(u8 *)(moby + 0xB0) != 0xFF && (g_moby_group_flags[*(u8 *)(moby + 0xB0) + (g_current_map_index << 4)] & 0x80)) ||
            (*(int *)(vars + 0x1C) != -1 &&
             *(u8 *)((char *)((*(int *)(vars + 0x1C) << 8) + (int)g_moby_l19_array[0]) + 0x20) != 0))
            moby_set_state(moby, 2, -1);
        break;
    case 2:
        vec_spring_to_target(moby + 0x10, vars + 0x30, vars + 0x14, *(float *)(vars + 8) * 0.00040000002f,
                      *(float *)(vars + 8) * 0.00040000002f, *(float *)(vars + 8) * 0.020000001f);
        sound = g_sound_state + *(int *)(vars + 0x40) * 0x70;
        if (*(char **)(sound + 0x88) != moby || !*(u8 *)(sound + 0x74))
            *(int *)(vars + 0x40) = PlayMobySound(0, 4, moby);
        if (fast_vec_dist(moby + 0x10, vars + 0x30) < *(float *)(vars + 8) * 0.020000001f)
            moby_set_state(moby, 3, -1);
        break;
    case 3:
        sound = g_sound_state + *(int *)(vars + 0x40) * 0x70;
        if (*(char **)(sound + 0x88) != moby || !*(u8 *)(sound + 0x74))
            *(int *)(vars + 0x40) = PlayMobySound(0, 4, moby);
        vec_spring_to_target(moby + 0x10, vars + 0x20, vars + 0x14, *(float *)(vars + 8) * 0.00040000002f,
                      *(float *)(vars + 8) * 0.00040000002f, *(float *)(vars + 8) * 0.020000001f);
        if (fast_vec_dist(moby + 0x10, vars + 0x20) < *(float *)(vars + 8) * 0.020000001f)
            moby_set_state(moby, 2, -1);
        break;
    }
    if (*(u8 *)(moby + 0x20) >= 2) {
        gfx_add_draw_callback_first(gfx_draw_beam_along_heading, moby);
        make_hit_descriptor(4.0f, query, moby, 1, g_particle_effect_template);
        *(u16 *)(query + 0x1A) = *(u16 *)(moby + 0xAA);
        vec_scale_to_length(offset, moby + 0xE0, *(float *)(vars + 0xC));
        FastVecAdd(offset, moby + 0x10, offset);
        CollLine(moby + 0x10, offset, 0, moby, query);
    }
}


#include "names.h"
/* func_US2_L15_00432488, the v2.00 copy of func_L15_004307E0: the same C, where the first pass
   also stops the owner's sound and clears its slot id, then deletes D_L15_001B1584 and
   D_L15_001B1588 when their field 0x34 is set. The last stage drops the D_L15_001B1520 count,
   func_L15_00432008 and func_0029B3E0, and calls func_002AD7B8 first instead of last. */

#include "common.h"

typedef float Vector[4] __attribute__((aligned(16)));
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; u8 *target; char pad1C[4]; Vector pos; } Hit;

extern int g_cutscene_l15_started_flag __attribute__((sda));
extern int g_gorn_cutscene_started_flag __attribute__((sda));
extern int g_gorn_cutscene_active_flag __attribute__((sda));
extern int g_gorn_message_counter __attribute__((sda));
extern float g_cutscene_l15_camera_rotation[4] SDATA(D_L15_001B1540);
/* Retail takes the camera position's address $gp-relative and reaches its z absolutely. */
extern float g_cutscene_camera_pos[4] MACRO_ADDR;
extern float camera_pos[4] SDATA(D_L15_001B1550);
extern int g_gorn_cutscene_basis_flag NOT_SDA;
extern u8 *g_gorn_path_first_node __attribute__((sda));
extern u8 *g_gorn_path_next_node __attribute__((sda));
extern u8 g_sound_state[];
extern int g_gorn_challenge_count;
extern u8 *g_moby_base;
extern Hit g_hit_l15_result;

extern void music_Unpause(void);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_a(s32 a0);
extern u8 **level_get_object_list(void);
extern s32 level_get_saved_value(void);
extern void entry_spawn_list_objects_with_flag(u8 *a0, s32 a1);
extern void *level_find_object_by_class_id(int);
extern int group_count_alive(void *);
extern int math_fast_float_d(void *);
extern void effect_remove_family_mobys(void);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, void *);
extern float fast_vec_dist(void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void mat_get_euler_angles(void *, void *);
extern void ship_start_transition(void *, void *, int);
extern void snd_stop_voice(int);
extern void moby_mark_spawned(void *);
extern void moby_set_flag_bit(void *, int);
extern void hero_set_state_value_c(int);
extern void moby_mark_flag_and_append_to_list(int);
extern void gorn_finish_challenge_stage_us2(void *, int);

/* Gorn challenge stage 1 setup and check (USA v2.00): on the first pass starts the scene, then
   once all ships are gone it runs the camera cutscene and finishes the stage. */
void gorn_cutscene_update_us2(u8 *moby)
{
    Vector step;
    Vector ahead;
    Vec up;
    Vector basis[3];
    u8 *vars = *(u8 **)(moby + 0x68);

    if (g_cutscene_l15_started_flag == 0) {
        u8 **list;
        int i, count;
        u8 *owner_moby = g_moby_base + (*(int *)(vars + 0x20) << 8);
        u8 *owner_data = *(u8 **)(owner_moby + 0x68);
        int voice_id = *(int *)(owner_data + 0x270);

        if (voice_id != -1) {
            u8 *entry = g_sound_state + voice_id * 0x70;

            if (*(u8 **)(entry + 0x88) == owner_moby && entry[0x74] != 0)
                snd_stop_voice(voice_id);
        }
        *(int *)(owner_data + 0x270) = -1;
        *(int *)(owner_data + 0x14) = 0;
        g_gorn_cutscene_basis_flag = 0;
        g_cutscene_l15_started_flag = 1;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        *(int *)(vars + 0x6C) = 30;
        list = level_get_object_list();
        count = level_get_saved_value();
        for (i = 0; i < count; i++) {
            if (*(short *)(list[i] + 0xAA) == 0x1211)
                entry_spawn_list_objects_with_flag(list[i], 1);
        }
        if (g_gorn_path_first_node != 0 && *(unsigned short *)(g_gorn_path_first_node + 0x34) != 0) {
            moby_mark_spawned(g_gorn_path_first_node);
            g_gorn_path_first_node = 0;
        }
        if (g_gorn_path_next_node != 0 && *(unsigned short *)(g_gorn_path_next_node + 0x34) != 0) {
            moby_mark_spawned(g_gorn_path_next_node);
            g_gorn_path_next_node = 0;
        }
    }
    if (group_count_alive(level_find_object_by_class_id(0x1211)) != 0)
        return;
    if (g_gorn_challenge_count < 6)
        return;
    if (g_gorn_cutscene_started_flag == 0) {
        u8 *stage_moby;
        u8 *pos;
        float dist;

        if (math_fast_float_d(vars + 0x6C) == 0)
            return;
        *(int *)(vars + 0x6C) = 60;
        effect_remove_family_mobys();
        stage_moby = g_moby_base + (*(int *)(vars + 0x20) << 8);
        pos = stage_moby + 0x10;
        qcopy(camera_pos, pos);
        vec_scale_to_length(step, stage_moby + 0xC0, 196.0f);
        dist = 25.0f;
        FastVecAdd(ahead, pos, step);
        if (CollLine(pos, ahead, 0, stage_moby, 0) != 0) {
            Hit *hit = &g_hit_l15_result;

            if (hit->target != 0 && *(short *)(hit->target + 0xAA) == 0x1211)
                dist = fast_vec_dist(hit->pos, pos);
        }
        if (dist < 16.0f)
            dist = -32.0f;
        else
            dist = dist * 0.5f;
        vec_scale_to_length(step, stage_moby + 0xC0, dist);
        FastVecAdd(camera_pos, camera_pos, step);
        g_cutscene_camera_pos[2] -= 16.0f;
        up.q = 0;
        up.f[2] = 1.0f;
        qcopy(basis[0], stage_moby + 0xC0);
        qcopy(basis[2], up.f);
        FastVecCross(basis[1], basis[0], basis[2]);
        basis[0][3] = basis[1][3] = basis[2][3] = 0.0f;
        mat_get_euler_angles(basis, g_cutscene_l15_camera_rotation);
        ship_start_transition(camera_pos, g_cutscene_l15_camera_rotation, 300);
        moby[0x20] = 3;
        g_gorn_cutscene_started_flag = 1;
    } else if (g_gorn_cutscene_active_flag != 0) {
        if (math_fast_float_d(vars + 0x6C) == 0)
            return;
        *(int *)(vars + 0x6C) = 10;
        moby_mark_flag_and_append_to_list(0x10);
        moby_set_flag_bit(g_moby_base + (*(int *)(vars + 0x28) << 8), 1);
        g_gorn_message_counter = 0;
        g_gorn_cutscene_active_flag = 0;
        hero_set_state_value_c(1);
    } else if (math_fast_float_d(vars + 0x6C) != 0) {
        entry_init_all_registered();
        gorn_finish_challenge_stage_us2(moby, 0);
    }
}

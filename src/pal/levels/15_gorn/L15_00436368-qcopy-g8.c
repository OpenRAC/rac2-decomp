#include "names.h"
/* func_PAL_L15_00436368, the PAL copy of func_L15_004307E0: the same C, where the timers scale
   to 50 Hz (30 to 25, 60 to 50, 10 to 8), the first frame also frees the two objects in
   D_L15_001B1584 and D_L15_001B1588, the distance step runs along +0xC0 rather than +0xA0, and
   the hand-back makes one more func_002AD7B8(0x10) call.

   Gorn's cutscene controller. On the first frame it starts the scene and
   wakes every 0x1211 object, then, once the timer runs out, it builds the camera from the
   object D_L15_001B261C points at (a ray towards it, the distance halved or pulled to -32, a
   basis from the facing and the up vector) and later hands control back.

   The camera position is taken $gp-relative (an SDATA view) but its z is read and written
   absolutely (MACRO_ADDR), D_L15_00221E3C is NOT_SDA, and the basis w components are one
   chained `= 0.0f` in the order 0, 1, 2 (retail stores a float zero with swc1).

   func_0029B3E0 returns int, as its definition in src/game/0029AE78-save-g8.c does and as
   L00_002FC7A8-launch.c tests. With the value-returning call, local-alloc gives the counter
   decrement after it retail's registers (the table pointer in $v0, the counter in $v1); a
   void declaration swaps them. */

#include "common.h"

typedef float Vector[4] __attribute__((aligned(16)));
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; u8 *target; char pad1C[4]; Vector pos; } Hit;

extern int g_cutscene_l15_started_flag __attribute__((sda));
extern int g_challenge_completed_a __attribute__((sda));
extern int g_gorn_cutscene_started_flag __attribute__((sda));
extern int g_gorn_cutscene_active_flag __attribute__((sda));
extern int g_gorn_message_counter __attribute__((sda));
extern char *g_gorn_path_first_node __attribute__((sda));
extern char *g_gorn_path_next_node __attribute__((sda));
extern float g_cutscene_l15_camera_rotation[4] SDATA(D_L15_001B1540);
/* Retail takes the camera position's address $gp-relative and reaches its z absolutely. */
extern float g_cutscene_camera_pos[4] MACRO_ADDR;
extern float camera_pos[4] SDATA(D_L15_001B1550);
extern int g_gorn_cutscene_basis_flag NOT_SDA;
extern int g_gorn_challenge_count;
extern u8 *g_moby_base;
extern Hit g_hit_l15_result;

extern void music_Unpause(void);
extern void moby_mark_spawned(void *);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_a(s32 a0);
extern u8 **level_get_object_list(void);
extern s32 level_get_saved_value(void);
extern void entry_spawn_list_objects_with_flag_pal(u8 *a0, s32 a1);
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
extern void func_PAL_L05_00448A58(void *, void *, int);
extern void snd_clamp_copy_volumes(void);
extern int MemcardSave(int, int);
extern void moby_set_flag_bit(void *, int);
extern void hero_set_state_value_c(int);
extern void moby_mark_flag_and_append_to_list(int);
extern void func_PAL_L15_00436118(void *, int);

void func_PAL_L15_00436368(u8 *self)
{
    Vector step;
    Vector ahead;
    Vec up;
    Vector basis[3];
    u8 *vars = *(u8 **)(self + 0x68);

    if (g_cutscene_l15_started_flag == 0) {
        u8 **list;
        int i, count;

        g_gorn_cutscene_basis_flag = 0;
        g_cutscene_l15_started_flag = 1;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        *(int *)(vars + 0x6C) = 25;
        list = level_get_object_list();
        count = level_get_saved_value();
        for (i = 0; i < count; i++) {
            if (*(short *)(list[i] + 0xAA) == 0x1211)
                entry_spawn_list_objects_with_flag_pal(list[i], 1);
        }
        if (g_gorn_path_first_node != 0) {
            moby_mark_spawned(g_gorn_path_first_node);
            g_gorn_path_first_node = 0;
        }
        if (g_gorn_path_next_node != 0) {
            moby_mark_spawned(g_gorn_path_next_node);
            g_gorn_path_next_node = 0;
        }
    }
    if (group_count_alive(level_find_object_by_class_id(0x1211)) != 0)
        return;
    if (g_gorn_challenge_count < 6)
        return;
    if (g_gorn_cutscene_started_flag == 0) {
        u8 *obj;
        u8 *pos;
        float dist;

        if (math_fast_float_d(vars + 0x6C) == 0)
            return;
        *(int *)(vars + 0x6C) = 50;
        effect_remove_family_mobys();
        obj = g_moby_base + (*(int *)(vars + 0x20) << 8);
        pos = obj + 0x10;
        qcopy(camera_pos, pos);
        vec_scale_to_length(step, obj + 0xC0, 196.0f);
        dist = 25.0f;
        FastVecAdd(ahead, pos, step);
        if (CollLine(pos, ahead, 0, obj, 0) != 0) {
            Hit *hit = &g_hit_l15_result;

            if (hit->target != 0 && *(short *)(hit->target + 0xAA) == 0x1211)
                dist = fast_vec_dist(hit->pos, pos);
        }
        if (dist < 16.0f)
            dist = -32.0f;
        else
            dist = dist * 0.5f;
        vec_scale_to_length(step, obj + 0xC0, dist);
        FastVecAdd(camera_pos, camera_pos, step);
        g_cutscene_camera_pos[2] -= 16.0f;
        up.q = 0;
        up.f[2] = 1.0f;
        qcopy(basis[0], obj + 0xC0);
        qcopy(basis[2], up.f);
        FastVecCross(basis[1], basis[0], basis[2]);
        basis[0][3] = basis[1][3] = basis[2][3] = 0.0f;
        mat_get_euler_angles(basis, g_cutscene_l15_camera_rotation);
        func_PAL_L05_00448A58(camera_pos, g_cutscene_l15_camera_rotation, 300);
        self[0x20] = 3;
        g_gorn_cutscene_started_flag = 1;
    } else if (g_gorn_cutscene_active_flag != 0) {
        if (math_fast_float_d(vars + 0x6C) == 0)
            return;
        *(int *)(vars + 0x6C) = 8;
        moby_mark_flag_and_append_to_list(0x10);
        g_challenge_completed_a++;
        snd_clamp_copy_volumes();
        MemcardSave(0, -1);
        g_challenge_completed_a--;
        moby_set_flag_bit(g_moby_base + (*(int *)(vars + 0x28) << 8), 1);
        g_gorn_message_counter = 0;
        g_gorn_cutscene_active_flag = 0;
        hero_set_state_value_c(1);
        moby_mark_flag_and_append_to_list(0x10);
    } else if (math_fast_float_d(vars + 0x6C) != 0) {
        entry_init_all_registered();
        func_PAL_L15_00436118(self, 0);
    }
}

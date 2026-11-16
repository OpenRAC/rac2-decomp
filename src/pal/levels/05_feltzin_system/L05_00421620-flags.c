#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern void vec_clear_128(char *block);
extern float math_random_float_range(float a, float b);
extern char *moby_get_motion_data(char *object);
extern void *state_get_stored_pointer_value(char *object);
extern void level_append_object(char *object, int a1, int a2, int a3);
extern void func_PAL_002A7E68(char *object, int a1, int a2, int a3);
extern void func_PAL_L05_0037E8E0(char *object);
extern int moby_process_collision_hit(char *object, int a1, int a2, int a3);
extern void moby_check_player_in_view_and_range(char *object, int a1, float a2);
extern int moby_can_take_next_step(char *object);
extern void func_PAL_L05_0037DE20(char *object);
extern int math_fast_float_d(char *block);
extern int math_fast_helper_a(char *buf, float value);
extern void gfx_add_draw_callback_third(void *fn, char *object);
extern void blast_call_helper_no_args(void);
extern char g_beam_owned_records[];
extern char *g_feltzin_target_mobys __attribute__((sda));
extern void beam_fire_burst_pal(char *object);
typedef struct {
    char pad0[0x104];
    int x104, x108, pad10C, mode, pad114, pad118;
    int has_target;
    char *target;
} Target05;
extern void tail_trail_spawn_burst_pal(char *object);
extern void feltzin_enemy_init_position_fast_pal(char *obj);

/* Per-frame update. On the first frame it initializes the object and, if state+0x264 is set, clears
   the owners of the 128 interpolation records; afterwards it points the record at moby state+0x260
   and runs func_PAL_L05_00421BC0 unless func_00283DB8 returns -1 for the object's position. */
void feltzin_enemy_c_update_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    Target05 *r;
    Vec buf;

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        if (state_get_stored_pointer_value(object) == 0)
            return;
        feltzin_enemy_init_position_fast_pal(object);
        func_PAL_002A7E68(object, 1, 0, 0);
        vec_clear_128((char *)&buf);
        *(float *)(object + 0x48) = math_random_float_range(0.9f, 1.1f);
        if (*(int *)(state + 0x264) != 0) {
            char *base;
            int *p;
            int i;

            level_append_object(object, 0, 0, 0);
            base = g_beam_owned_records;
            p = (int *)(base + 0x27F0);
            i = 0x7F;
            do {
                *p = 0;
                p -= 0x14;
                i--;
            } while (i >= 0);
        }
        return;
    }
    r = (Target05 *)moby_get_motion_data(object);
    if (r->mode == 0)
        return;
    {
        int one = 1;

        func_PAL_L05_0037E8E0(object);
        moby_process_collision_hit(object, 0, 0, 0);
        moby_check_player_in_view_and_range(object, one, 64.0f);
        if (r->mode == one) {
            if (*(int *)(state + 0x260) != -1) {
                r->has_target = 1;
                r->target = g_feltzin_target_mobys + *(int *)(state + 0x260) * 256;
            }
            if (r->x108 != 0 && r->x104 != 0)
                beam_fire_burst_pal(object);
            if (moby_can_take_next_step(object) != 0)
                func_PAL_L05_0037DE20(object);
            math_fast_float_d(state + 0x268);
            qcopy(&buf, object + 0x10);
            buf.f[3] = *(float *)(object + 0xC) * 0.00097656f;
            if (math_fast_helper_a((char *)&buf, 100.0f) != -1)
                tail_trail_spawn_burst_pal(object);
        }
    }
    gfx_add_draw_callback_third(blast_call_helper_no_args, object);
}

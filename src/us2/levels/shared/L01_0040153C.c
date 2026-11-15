#include "names.h"
/* func_US2_L01_0040153C, the USA v2.00 copy of func_L01_003FFFE8: the same C, where the
   func_L00_002B9D60 argument 0x6F becomes -1, case 4 tests before func_0029B3E0, and
   func_002AF0A8 and func_L01_002BEB90 become func_US2_002AFF10 and ref_US2_L01_0040153C_00
   (func_US2_L01_002BEEA8 in level 1, func_US2_L08_002D31F8 in level 8). */
#include "include_asm.h"
#include "common.h"

extern int g_current_map_index __attribute__((sda));

extern void moby_set_state(char *, int, int);
extern void STUB_printf(void *, int);
extern void moby_mark_spawned(void *);
extern int coll_point_inside_region(void *, int);
extern void FadeToBlack(int);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void load_scene_chunk(int, int);
extern int req_push_queue(void *, int);
extern s32 req_launch_queued(void *);
extern void game_set_slowdown_factor(void);
extern int game_is_either_mode_two(void);
extern void moby_mark_flag_and_append_to_list(int);
extern void func_US2_002AFF10(int);
extern void moby_mark_table_entry_flagged(int);
extern void level_capture_checkpoint_state(void *, void *);
extern void hero_start_move_state_walk_or_run(int);
extern void ref_US2_L01_0040153C_00(int, int);
extern void script_queue_keyed_request(int, int);
extern int MemcardSave(int, int);
extern unsigned char D_0019B2E8[];
extern char g_hero_position[];

/* Level data, at another address in each level that has this function. The trigger flag is
   read at an offset from its owner: retail never moves it into a delay slot. */
extern int ref_L01_003FFFE8_00[] __attribute__((sda));
extern char ref_L01_003FFFE8_01[];
extern char ref_L01_003FFFE8_02[];
extern char ref_L01_003FFFE8_03[];
extern char ref_L01_003FFFE8_04[];
extern char *ref_L01_003FFFE8_05 __attribute__((sda));
extern char ref_L01_003FFFE8_06[];
extern int ref_L01_003FFFE8_07 __attribute__((sda));

/* a trigger moby: reports bad setup, waits to be activated, plays its effects and removes itself */
void func_US2_L01_0040153C(char *m)
{
    char *d = *(char **)(m + 0x68);
    int active;

    switch (*(unsigned char *)(m + 0x20)) {
    case 0:
        if (*(int *)d == -1)
            STUB_printf(ref_L01_003FFFE8_01, *(short *)(m + 0xB2));
        if (*(short *)(d + 4) == -1)
            STUB_printf(ref_L01_003FFFE8_02, *(short *)(m + 0xB2));
        if (*(int *)(d + 8) == -1)
            STUB_printf(ref_L01_003FFFE8_03, *(short *)(m + 0xB2));
        if (*(unsigned char *)(m + 0xB0) != 255) {
            if (D_0019B2E8[*(unsigned char *)(m + 0xB0) + (g_current_map_index << 4)] & 128) {
                moby_mark_spawned(m);
                break;
            }
        } else
            STUB_printf(ref_L01_003FFFE8_04, *(short *)(m + 0xB2));
        moby_set_state(m, 1, -1);
        break;
    case 1:
        active = 0;
        if (*(unsigned char *)(m + 0xBC) ||
            (*(int *)d != -1 && coll_point_inside_region(g_hero_position, *(int *)d) &&
             (*(int *)(d + 0x18) || *(int *)(g_hero_position + 0x2C0))))
            active = 1;
        if (active) {
            int ready;

            *(unsigned char *)(m + 0x30) = 255;
            FadeToBlack(20);
            if (*(int *)(d + 0xC) != -1) {
                char *p = ref_L01_003FFFE8_05 + (*(int *)(d + 0xC) << 7);

                hero_reset_position_and_direction(p + 0x30, p + 0x70, -1, 1);
            }
            if (*(int *)(d + 8) != -1)
                load_scene_chunk(*(int *)(d + 8), 0);
            ready = 1;
            if (g_current_map_index == 8 && *(short *)(d + 4) == 0) {
                if (req_push_queue(ref_L01_003FFFE8_06, 0x57)) {
                    req_push_queue(ref_L01_003FFFE8_06, 9);
                    req_push_queue(ref_L01_003FFFE8_06, 0x58);
                    req_launch_queued(ref_L01_003FFFE8_06);
                    game_set_slowdown_factor();
                    ref_L01_003FFFE8_07 = 1;
                } else
                    ready = 0;
            }
            if (ready)
                moby_set_state(m, 3, -1);
        }
        break;
    case 3:
        ref_L01_003FFFE8_00[1] = 1;
        if (!game_is_either_mode_two()) {
            ref_L01_003FFFE8_00[1] = 0;
            if (*(short *)(d + 6) != -1) {
                moby_mark_flag_and_append_to_list(*(short *)(d + 6));
                func_US2_002AFF10(*(short *)(d + 6));
            }
            moby_set_state(m, 4, -1);
        }
        break;
    case 4:
        if (*(unsigned char *)(m + 0xB0) != 255) {
            int n = *(unsigned char *)(m + 0xB0);

            if (!(D_0019B2E8[n + (g_current_map_index << 4)] & 128)) {
                moby_mark_table_entry_flagged(n);
                level_capture_checkpoint_state(m + 0x10, m + 0xF0);
            }
        }
        hero_start_move_state_walk_or_run(0);
        ref_US2_L01_0040153C_00(0, 1);
        script_queue_keyed_request(*(int *)(d + 0x14), *(int *)(d + 0x10));
        if (*(unsigned char *)(m + 0xB0) != 255 || *(short *)(d + 6) != -1)
            MemcardSave(0, -1);
        moby_mark_spawned(m);
        break;
    }
}

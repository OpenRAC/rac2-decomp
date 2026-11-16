#include "names.h"
/* func_PAL_L04_003F16D8, the PAL copy of func_L04_003ED740: the same C, where func_L00_002B9D60
   becomes func_PAL_L00_002B9CD8. */
#include "common.h"

typedef struct {
    char pad[0x284];
    char *target;
    int timer;
} HeroD740;

extern char *g_moby_l04_pool __attribute__((sda));
extern char *g_linked_record_table[] __attribute__((sda));
extern char g_hero_position[], g_sound_state[];
extern HeroD740 g_hero_l04_state;
extern u8 g_moby_group_flags[];
extern char *g_hero_moby;
extern int g_current_map_index __attribute__((sda));
extern int moby_count_group_not_in_state(int, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern int IsPointInCuboid(void *, int);
extern void cam_lock_entry(int);
extern int cam_is_trigger_ready(int);
extern void moby_mark_table_entry_flagged(unsigned int);
extern void level_capture_checkpoint_state(void *, void *);
extern int snd_start_in_slot(int, int, void *);
extern void moby_set_flag_bit(void *, int);
extern void hero_reset_position_and_direction_pal(void *, void *, int, int);
extern void snd_stop_voice(int);

/* Controls obj_a sequence of linked objects: waits for them to finish, plays obj_a camera move, then puts the player at obj_a saved spot (PAL build). */
void linked_sequence_controller_update_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(u8 *)(moby + 0x20) = 1;
        break;
    case 1: {
        int i, busy;

        busy = 0;
        for (i = 0; i < 4; i++)
            if (moby_count_group_not_in_state(*(int *)(vars + 4 * i), -1))
                busy = 1;
        if (!busy) {
            if (*(int *)(vars + 0x18) == 0) {
                char *obj_a, *obj_b;

                obj_a = g_moby_l04_pool + (*(int *)(vars + 0x74) << 8);
                obj_b = g_moby_l04_pool + (*(int *)(vars + 0x78) << 8);
                if (*(u8 *)(obj_a + 0x20) == 1)
                    snd_play_from_class_bank(0, 0, obj_a, 0xCE6);
                *(u8 *)(obj_a + 0x20) = 2;
                *(u8 *)(obj_b + 0x20) = 2;
                if (IsPointInCuboid(g_hero_position, *(int *)(vars + 0x70)) &&
                    !(g_moby_group_flags[*(u8 *)(moby + 0xB0) + g_current_map_index * 16] & 128)) {
                    cam_lock_entry(*(int *)(vars + 0x10));
                    *(u8 *)(moby + 0x20) = 2;
                    *(u8 *)(obj_a + 0x20) = 3;
                    *(u8 *)(obj_b + 0x20) = 3;
                }
            } else if (*(int *)(vars + 0x18) == 1) {
                char *obj_a, *obj_b;

                if (!(g_moby_group_flags[*(u8 *)(moby + 0xB0) + g_current_map_index * 16] & 128)) {
                    cam_lock_entry(*(int *)(vars + 0x10));
                    *(u8 *)(moby + 0x20) = 4;
                    obj_a = g_moby_l04_pool + (*(int *)(vars + 0x74) << 8);
                    obj_b = g_moby_l04_pool + (*(int *)(vars + 0x78) << 8);
                    snd_play_from_class_bank(0, 0, obj_a, 0xCE6);
                    *(u8 *)(obj_a + 0x20) = 2;
                    *(u8 *)(obj_b + 0x20) = 2;
                    if (!(g_moby_group_flags[*(u8 *)(moby + 0xB0) + g_current_map_index * 16] & 128)) {
                        moby_mark_table_entry_flagged(*(u8 *)(moby + 0xB0));
                        level_capture_checkpoint_state(moby + 0x10, moby + 0xF0);
                    }
                }
            }
        } else if (*(int *)(vars + 0x18) == 0 &&
                   IsPointInCuboid(g_hero_position, *(int *)(vars + 0x70)) &&
                   !(g_moby_group_flags[*(u8 *)(moby + 0xB0) + g_current_map_index * 16] & 128)) {
            cam_lock_entry(*(int *)(vars + 0x10));
            *(u8 *)(moby + 0x20) = 2;
        }
        break;
    }
    case 2: {
        if (cam_is_trigger_ready(*(int *)(vars + 0x10))) {
            *(signed char *)(moby + 0x95) = snd_start_in_slot(23, 4, g_hero_moby);
            {
                char *base = g_moby_l04_pool;
                int i;

                for (i = 0; i < 14; i++) {
                    char *obj_a, *obj_vars;
                    int id = *(int *)(vars + 0x20 + i * 4);

                    if (id != -1) {
                        obj_a = base + (id << 8);
                        if (obj_a) {
                            obj_vars = *(char **)(obj_a + 0x68);
                            *(int *)(obj_vars + 0x260) = *(int *)(obj_vars + 0x264);
                            *(int *)(obj_vars + 0x250) = *(int *)(obj_vars + 0x254);
                            *(int *)(obj_a + 0x98) = *(int *)(*(char **)(obj_a + 0x24) + 0x10);
                            *(u16 *)(obj_a + 0x34) &= 0xFFBE;
                        }
                    }
                }
            }
            {
                char *obj_a = g_linked_record_table[0] + (*(int *)(vars + 0x14) << 7);

                qcopy(g_hero_position, obj_a + 0x30);
                qcopy(g_hero_position + 0x10, obj_a + 0x70);
                moby_set_flag_bit(moby, 1);
                *(u16 *)(moby + 0x96) = 0;
                *(u8 *)(moby + 0x20) = 5;
            }
        }
        break;
    }
    case 3: {
        char *obj_a, *obj_b;

        if (cam_is_trigger_ready(*(int *)(vars + 0x10))) {
            {
                char *record = g_linked_record_table[0] + (*(int *)(vars + 0x14) << 7);

                qcopy(g_hero_position, record + 0x30);
                record += 0x70;
                qcopy(g_hero_position + 0x10, record);
            }
            obj_a = g_moby_l04_pool + (*(int *)(vars + 0x20) << 8);
            obj_b = g_moby_l04_pool + (*(int *)(vars + 0x24) << 8);
            *(u8 *)(obj_a + 0x95) = 4;
            *(u8 *)(obj_a + 0x20) = 17;
            if (!g_hero_l04_state.target) {
                g_hero_l04_state.target = obj_b;
                g_hero_l04_state.timer = 0;
            }
            *(int *)(obj_a + 0x98) = *(int *)(*(char **)(obj_a + 0x24) + 0x10);
            {
                char *b_vars = *(char **)(obj_b + 0x68);
                *(int *)(b_vars + 0x270) = *(int *)(b_vars + 0x274);
            }
            {
                char *a_vars = *(char **)(obj_a + 0x68);
                *(int *)(a_vars + 0x270) = *(int *)(a_vars + 0x274);
            }
            *(u8 *)(moby + 0x20) = 5;
        }
        break;
    }
    case 4: {
        char *obj_a;

        if (cam_is_trigger_ready(*(int *)(vars + 0x10))) {
            obj_a = g_linked_record_table[0] + (*(int *)(vars + 0x14) << 7);
            hero_reset_position_and_direction_pal(obj_a + 0x30, obj_a + 0x70, 111, 1);
            *(u8 *)(moby + 0x20) = 5;
            moby_set_flag_bit(moby, 1);
        }
        break;
    }
    case 5: {
        if (*(u16 *)(moby + 0x96) < 60)
            ++*(u16 *)(moby + 0x96);
        else if (cam_is_trigger_ready(*(int *)(vars + 0x10))) {
            int i = *(signed char *)(moby + 0x95);

            if (i != -1) {
                char *obj_a = (char *)g_sound_state + i * 0x70;
                if (*(char **)(obj_a + 0x88) == g_hero_moby && *(u8 *)(obj_a + 0x74))
                    snd_stop_voice(i);
            }
            i = -1;
            *(signed char *)(moby + 0x95) = i;
        }
        break;
    }
    }
}

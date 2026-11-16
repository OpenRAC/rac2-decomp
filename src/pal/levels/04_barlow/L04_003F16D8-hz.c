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

void linked_sequence_controller_update_pal(char *o)
{
    char *p = *(char **)(o + 0x68);

    switch (*(u8 *)(o + 0x20)) {
    case 0:
        *(u8 *)(o + 0x20) = 1;
        break;
    case 1: {
        int i, busy;

        busy = 0;
        for (i = 0; i < 4; i++)
            if (moby_count_group_not_in_state(*(int *)(p + 4 * i), -1))
                busy = 1;
        if (!busy) {
            if (*(int *)(p + 0x18) == 0) {
                char *a, *b;

                a = g_moby_l04_pool + (*(int *)(p + 0x74) << 8);
                b = g_moby_l04_pool + (*(int *)(p + 0x78) << 8);
                if (*(u8 *)(a + 0x20) == 1)
                    snd_play_from_class_bank(0, 0, a, 0xCE6);
                *(u8 *)(a + 0x20) = 2;
                *(u8 *)(b + 0x20) = 2;
                if (IsPointInCuboid(g_hero_position, *(int *)(p + 0x70)) &&
                    !(g_moby_group_flags[*(u8 *)(o + 0xB0) + g_current_map_index * 16] & 128)) {
                    cam_lock_entry(*(int *)(p + 0x10));
                    *(u8 *)(o + 0x20) = 2;
                    *(u8 *)(a + 0x20) = 3;
                    *(u8 *)(b + 0x20) = 3;
                }
            } else if (*(int *)(p + 0x18) == 1) {
                char *a, *b;

                if (!(g_moby_group_flags[*(u8 *)(o + 0xB0) + g_current_map_index * 16] & 128)) {
                    cam_lock_entry(*(int *)(p + 0x10));
                    *(u8 *)(o + 0x20) = 4;
                    a = g_moby_l04_pool + (*(int *)(p + 0x74) << 8);
                    b = g_moby_l04_pool + (*(int *)(p + 0x78) << 8);
                    snd_play_from_class_bank(0, 0, a, 0xCE6);
                    *(u8 *)(a + 0x20) = 2;
                    *(u8 *)(b + 0x20) = 2;
                    if (!(g_moby_group_flags[*(u8 *)(o + 0xB0) + g_current_map_index * 16] & 128)) {
                        moby_mark_table_entry_flagged(*(u8 *)(o + 0xB0));
                        level_capture_checkpoint_state(o + 0x10, o + 0xF0);
                    }
                }
            }
        } else if (*(int *)(p + 0x18) == 0 &&
                   IsPointInCuboid(g_hero_position, *(int *)(p + 0x70)) &&
                   !(g_moby_group_flags[*(u8 *)(o + 0xB0) + g_current_map_index * 16] & 128)) {
            cam_lock_entry(*(int *)(p + 0x10));
            *(u8 *)(o + 0x20) = 2;
        }
        break;
    }
    case 2: {
        if (cam_is_trigger_ready(*(int *)(p + 0x10))) {
            *(signed char *)(o + 0x95) = snd_start_in_slot(23, 4, g_hero_moby);
            {
                char *base = g_moby_l04_pool;
                int i;

                for (i = 0; i < 14; i++) {
                    char *a, *q;
                    int id = *(int *)(p + 0x20 + i * 4);

                    if (id != -1) {
                        a = base + (id << 8);
                        if (a) {
                            q = *(char **)(a + 0x68);
                            *(int *)(q + 0x260) = *(int *)(q + 0x264);
                            *(int *)(q + 0x250) = *(int *)(q + 0x254);
                            *(int *)(a + 0x98) = *(int *)(*(char **)(a + 0x24) + 0x10);
                            *(u16 *)(a + 0x34) &= 0xFFBE;
                        }
                    }
                }
            }
            {
                char *a = g_linked_record_table[0] + (*(int *)(p + 0x14) << 7);

                qcopy(g_hero_position, a + 0x30);
                qcopy(g_hero_position + 0x10, a + 0x70);
                moby_set_flag_bit(o, 1);
                *(u16 *)(o + 0x96) = 0;
                *(u8 *)(o + 0x20) = 5;
            }
        }
        break;
    }
    case 3: {
        char *a, *b;

        if (cam_is_trigger_ready(*(int *)(p + 0x10))) {
            {
                char *record = g_linked_record_table[0] + (*(int *)(p + 0x14) << 7);

                qcopy(g_hero_position, record + 0x30);
                record += 0x70;
                qcopy(g_hero_position + 0x10, record);
            }
            a = g_moby_l04_pool + (*(int *)(p + 0x20) << 8);
            b = g_moby_l04_pool + (*(int *)(p + 0x24) << 8);
            *(u8 *)(a + 0x95) = 4;
            *(u8 *)(a + 0x20) = 17;
            if (!g_hero_l04_state.target) {
                g_hero_l04_state.target = b;
                g_hero_l04_state.timer = 0;
            }
            *(int *)(a + 0x98) = *(int *)(*(char **)(a + 0x24) + 0x10);
            {
                char *bd = *(char **)(b + 0x68);
                *(int *)(bd + 0x270) = *(int *)(bd + 0x274);
            }
            {
                char *ad = *(char **)(a + 0x68);
                *(int *)(ad + 0x270) = *(int *)(ad + 0x274);
            }
            *(u8 *)(o + 0x20) = 5;
        }
        break;
    }
    case 4: {
        char *a;

        if (cam_is_trigger_ready(*(int *)(p + 0x10))) {
            a = g_linked_record_table[0] + (*(int *)(p + 0x14) << 7);
            hero_reset_position_and_direction_pal(a + 0x30, a + 0x70, 111, 1);
            *(u8 *)(o + 0x20) = 5;
            moby_set_flag_bit(o, 1);
        }
        break;
    }
    case 5: {
        if (*(u16 *)(o + 0x96) < 60)
            ++*(u16 *)(o + 0x96);
        else if (cam_is_trigger_ready(*(int *)(p + 0x10))) {
            int i = *(signed char *)(o + 0x95);

            if (i != -1) {
                char *a = (char *)g_sound_state + i * 0x70;
                if (*(char **)(a + 0x88) == g_hero_moby && *(u8 *)(a + 0x74))
                    snd_stop_voice(i);
            }
            i = -1;
            *(signed char *)(o + 0x95) = i;
        }
        break;
    }
    }
}

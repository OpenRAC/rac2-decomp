#include "common.h"

typedef struct {
    char pad[0x284];
    char *target;
    int timer;
} HeroD740;

extern char *g_moby_l04_pool __attribute__((sda));
extern char *D_L04_001B25CC[] __attribute__((sda));
extern char g_hero_position[], g_sound_state[];
extern HeroD740 D_L04_001B9540;
extern u8 D_0019B2E8[];
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
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void snd_stop_voice(int);

/* Controls a sequence of linked objects: waits for them to finish, plays a camera move, then puts the player at a saved spot. */
void linked_sequence_controller_update(char *moby)
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
                char *partA, *partB;

                partA = g_moby_l04_pool + (*(int *)(vars + 0x74) << 8);
                partB = g_moby_l04_pool + (*(int *)(vars + 0x78) << 8);
                if (*(u8 *)(partA + 0x20) == 1)
                    snd_play_from_class_bank(0, 0, partA, 0xCE6);
                *(u8 *)(partA + 0x20) = 2;
                *(u8 *)(partB + 0x20) = 2;
                if (IsPointInCuboid(g_hero_position, *(int *)(vars + 0x70)) &&
                    !(D_0019B2E8[*(u8 *)(moby + 0xB0) + g_current_map_index * 16] & 128)) {
                    cam_lock_entry(*(int *)(vars + 0x10));
                    *(u8 *)(moby + 0x20) = 2;
                    *(u8 *)(partA + 0x20) = 3;
                    *(u8 *)(partB + 0x20) = 3;
                }
            } else if (*(int *)(vars + 0x18) == 1) {
                char *partA, *partB;

                if (!(D_0019B2E8[*(u8 *)(moby + 0xB0) + g_current_map_index * 16] & 128)) {
                    cam_lock_entry(*(int *)(vars + 0x10));
                    *(u8 *)(moby + 0x20) = 4;
                    partA = g_moby_l04_pool + (*(int *)(vars + 0x74) << 8);
                    partB = g_moby_l04_pool + (*(int *)(vars + 0x78) << 8);
                    snd_play_from_class_bank(0, 0, partA, 0xCE6);
                    *(u8 *)(partA + 0x20) = 2;
                    *(u8 *)(partB + 0x20) = 2;
                    if (!(D_0019B2E8[*(u8 *)(moby + 0xB0) + g_current_map_index * 16] & 128)) {
                        moby_mark_table_entry_flagged(*(u8 *)(moby + 0xB0));
                        level_capture_checkpoint_state(moby + 0x10, moby + 0xF0);
                    }
                }
            }
        } else if (*(int *)(vars + 0x18) == 0 &&
                   IsPointInCuboid(g_hero_position, *(int *)(vars + 0x70)) &&
                   !(D_0019B2E8[*(u8 *)(moby + 0xB0) + g_current_map_index * 16] & 128)) {
            cam_lock_entry(*(int *)(vars + 0x10));
            *(u8 *)(moby + 0x20) = 2;
        }
        break;
    }
    case 2: {
        if (cam_is_trigger_ready(*(int *)(vars + 0x10))) {
            *(signed char *)(moby + 0x95) = snd_start_in_slot(23, 4, g_hero_moby);
            {
                char *mobyTable = g_moby_l04_pool;
                int i;

                for (i = 0; i < 14; i++) {
                    char *partA, *partVars;
                    int partId = *(int *)(vars + 0x20 + i * 4);

                    if (partId != -1) {
                        partA = mobyTable + (partId << 8);
                        if (partA) {
                            partVars = *(char **)(partA + 0x68);
                            *(int *)(partVars + 0x260) = *(int *)(partVars + 0x264);
                            *(int *)(partVars + 0x250) = *(int *)(partVars + 0x254);
                            *(int *)(partA + 0x98) = *(int *)(*(char **)(partA + 0x24) + 0x10);
                            *(u16 *)(partA + 0x34) &= 0xFFBE;
                        }
                    }
                }
            }
            {
                char *partA = D_L04_001B25CC[0] + (*(int *)(vars + 0x14) << 7);

                qcopy(g_hero_position, partA + 0x30);
                qcopy(g_hero_position + 0x10, partA + 0x70);
                moby_set_flag_bit(moby, 1);
                *(u16 *)(moby + 0x96) = 0;
                *(u8 *)(moby + 0x20) = 5;
            }
        }
        break;
    }
    case 3: {
        char *partA, *partB;

        if (cam_is_trigger_ready(*(int *)(vars + 0x10))) {
            {
                char *spot = D_L04_001B25CC[0] + (*(int *)(vars + 0x14) << 7);

                qcopy(g_hero_position, spot + 0x30);
                spot += 0x70;
                qcopy(g_hero_position + 0x10, spot);
            }
            partA = g_moby_l04_pool + (*(int *)(vars + 0x20) << 8);
            partB = g_moby_l04_pool + (*(int *)(vars + 0x24) << 8);
            *(u8 *)(partA + 0x95) = 4;
            *(u8 *)(partA + 0x20) = 17;
            if (!D_L04_001B9540.target) {
                D_L04_001B9540.target = partB;
                D_L04_001B9540.timer = 0;
            }
            *(int *)(partA + 0x98) = *(int *)(*(char **)(partA + 0x24) + 0x10);
            {
                char *partBVars = *(char **)(partB + 0x68);
                *(int *)(partBVars + 0x270) = *(int *)(partBVars + 0x274);
            }
            {
                char *partAVars = *(char **)(partA + 0x68);
                *(int *)(partAVars + 0x270) = *(int *)(partAVars + 0x274);
            }
            *(u8 *)(moby + 0x20) = 5;
        }
        break;
    }
    case 4: {
        char *partA;

        if (cam_is_trigger_ready(*(int *)(vars + 0x10))) {
            partA = D_L04_001B25CC[0] + (*(int *)(vars + 0x14) << 7);
            hero_reset_position_and_direction(partA + 0x30, partA + 0x70, 111, 1);
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
                char *partA = (char *)g_sound_state + i * 0x70;
                if (*(char **)(partA + 0x88) == g_hero_moby && *(u8 *)(partA + 0x74))
                    snd_stop_voice(i);
            }
            i = -1;
            *(signed char *)(moby + 0x95) = i;
        }
        break;
    }
    }
}

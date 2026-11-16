#include "include_asm.h"

#include "common.h"
extern int g_trooper_anim_period __attribute__((sda));
extern void trooper_fire_arm_shot_pal(char *);
extern int path_is_entry_reachable_pal(void *, int);
extern int enemy_select_path(void *, int, int);
extern void enemy_set_animation_state_pal(void *, int, int, int);
extern int path_toggle_handle_cache(char *);
extern void moby_set_state(void *, int, int);
extern int math_random_int_range(int, int);
extern int func_001163B0(void);
extern void anim_start_blended_pal(void *, int, int, int);

/* Picks the enemy's next action from its current command and whether its trigger is ready (PAL). */
void enemy_choose_next_action_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *parent;
    int ready = 1;
    if (*(int *)(vars + 0x2DC) != -1) {
        ready = path_is_entry_reachable_pal(moby, *(int *)(vars + 0x2DC)) != 0;
        if (*(int *)(vars + 0x180) >= 0x33) ready = 1;
    }
    if (ready) {
        switch (*(u8 *)(moby + 0x95)) {
        case 3: {
            int alternate;
            *(int *)(vars + 0x138) &= ~4;
            if (*(u8 *)(vars + 0x302) & 2) *(u8 *)(vars + 0x302) = 0;
            enemy_select_path(moby, *(int *)(vars + 0x2BC), -1);
            alternate = *(u8 *)(vars + 0x30E);
            if (alternate) {
                enemy_set_animation_state_pal(moby, 4, 0, math_random_int_range(7, 12));
                moby_set_state(moby, 4, 5);
            } else {
                enemy_set_animation_state_pal(moby, 12, 0, math_random_int_range(7, 12));
                moby_set_state(moby, 8, 5);
            }
            return;
        }
        case 4:
            enemy_select_path(moby, *(int *)(vars + 0x2B4), -1);
            moby_set_state(moby, 5, 1);
            return;
        case 5: {
            int result = path_toggle_handle_cache(moby);
            if (!*(u8 *)(vars + 0x303) || result) {
                enemy_set_animation_state_pal(moby, 12, 0, math_random_int_range(7, 12));
                moby_set_state(moby, 8, 5);
                *(short *)(vars + 0x2E4) = ((s32)(g_trooper_anim_period) * 5 + 2) / 6;
            }
            return;
        }
        case 1:
        case 6: {
            int result;
            path_toggle_handle_cache(moby);
            if (*(u8 *)(moby + 0x60) & 2) {
                result = func_001163B0() & 1;
                enemy_set_animation_state_pal(moby, result, 0, math_random_int_range(10, 20));
                moby_set_state(moby, 5, -1);
            }
            return;
        }
        }
    } else if ((*(u8 *)(vars + 0x303) && *(u8 *)(moby + 0x95) == 5) || (*(int *)(vars + 0x4C0) && *(u8 *)(moby + 0x95) == 3)) {
        parent = *(char **)(vars + 0x2F8);
        if (parent && *(short *)(parent + 0xAA) == 0xD0E && *(u8 *)(parent + 0x20) != 0xFE && *(u8 *)(parent + 0x20) != 0xFD) {
            *(u8 *)(vars + 0x30C) = 0;
            *(u8 *)(vars + 0x30D) = 1;
            if (*(u8 *)(parent + 0x42) == 10) trooper_fire_arm_shot_pal(moby);
            else if (*(u8 *)(parent + 0x43) != 10) anim_start_blended_pal(parent, 10, 0, 10);
        }
    }
}

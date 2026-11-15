#include "names.h"
/* Selects the object action from its command, trigger readiness and linked parent state. */
#include "common.h"
extern int D_L09_001B0F40 __attribute__((sda));
extern void trooper_fire_arm_shot(char *);
extern int path_is_entry_reachable(void *, int);
extern int enemy_select_path(void *, int, int);
extern void enemy_set_animation_state(void *, int, int, int);
extern int path_toggle_handle_cache(char *);
extern void moby_set_state(void *, int, int);
extern int math_random_int_range(int, int);
extern int func_001163B0(void);
extern void anim_start_blended(void *, int, int, int);
/* Picks the enemy's next action from its current command and whether its trigger is ready. */
void enemy_choose_next_action(char *obj)
{
    char *vars = *(char **)(obj + 0x68);
    char *parent;
    int ready = 1;
    if (*(int *)(vars + 0x2DC) != -1) {
        ready = path_is_entry_reachable(obj, *(int *)(vars + 0x2DC)) != 0;
        if (*(int *)(vars + 0x180) >= 0x33) ready = 1;
    }
    if (ready) {
        switch (*(u8 *)(obj + 0x95)) {
        case 3: {
            int alternate;
            *(int *)(vars + 0x138) &= ~4;
            if (*(u8 *)(vars + 0x302) & 2) *(u8 *)(vars + 0x302) = 0;
            enemy_select_path(obj, *(int *)(vars + 0x2BC), -1);
            alternate = *(u8 *)(vars + 0x30E);
            if (alternate) {
                enemy_set_animation_state(obj, 4, 0, math_random_int_range(7, 12));
                moby_set_state(obj, 4, 5);
            } else {
                enemy_set_animation_state(obj, 12, 0, math_random_int_range(7, 12));
                moby_set_state(obj, 8, 5);
            }
            return;
        }
        case 4:
            enemy_select_path(obj, *(int *)(vars + 0x2B4), -1);
            moby_set_state(obj, 5, 1);
            return;
        case 5: {
            int result = path_toggle_handle_cache(obj);
            if (!*(u8 *)(vars + 0x303) || result) {
                enemy_set_animation_state(obj, 12, 0, math_random_int_range(7, 12));
                moby_set_state(obj, 8, 5);
                *(short *)(vars + 0x2E4) = D_L09_001B0F40;
            }
            return;
        }
        case 1:
        case 6: {
            int result;
            path_toggle_handle_cache(obj);
            if (*(u8 *)(obj + 0x60) & 2) {
                result = func_001163B0() & 1;
                enemy_set_animation_state(obj, result, 0, math_random_int_range(10, 20));
                moby_set_state(obj, 5, -1);
            }
            return;
        }
        }
    } else if ((*(u8 *)(vars + 0x303) && *(u8 *)(obj + 0x95) == 5) || (*(int *)(vars + 0x4C0) && *(u8 *)(obj + 0x95) == 3)) {
        parent = *(char **)(vars + 0x2F8);
        if (parent && *(short *)(parent + 0xAA) == MOBY_CLASS_MEGACORP_TROOPER_TORSO && *(u8 *)(parent + 0x20) != 0xFE && *(u8 *)(parent + 0x20) != 0xFD) {
            *(u8 *)(vars + 0x30C) = 0;
            *(u8 *)(vars + 0x30D) = 1;
            if (*(u8 *)(parent + 0x42) == 10) trooper_fire_arm_shot(obj);
            else if (*(u8 *)(parent + 0x43) != 10) anim_start_blended(parent, 10, 0, 10);
        }
    }
}

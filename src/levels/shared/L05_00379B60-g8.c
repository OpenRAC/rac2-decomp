#include "common.h"
extern int g_feltzin_mission_index[] __attribute__((sda));
extern int g_feltzin_challenge_state[];
extern void *g_level_object_list[];
extern int g_level_object_count __attribute__((sda));
extern int g_level_random_object_index __attribute__((sda));
extern void InitSlotFlagsFromEquipment(void);
extern int math_random_int_range(int,int);
extern int list_count_ready_objects(void *);
extern void UpdateSpaceProjectilePool(void *);
extern void gfx_add_draw_callback_third(void (*)(void *),void *);
/* Picks a random live object that can be chosen and sets up its follow-up update. */
void level_select_random_object(void)
{
    /* The initial state pointer and subsequent search flag have disjoint lifetimes. */
    union { int *state; int found; } phase;
    int *state;
    int *selection;
    if (g_feltzin_mission_index[0] < 10) InitSlotFlagsFromEquipment();
    phase.state = g_feltzin_challenge_state;
    if (phase.state[0x84/4] != 0) return;
    {
        if (g_level_object_count >= 2) {
            g_level_random_object_index = math_random_int_range(0,g_level_object_count-1);
            selection = phase.state;
            phase.found = 0;
            while (!phase.found) {
                if (selection[4] == 0) phase.found = 1;
                if (list_count_ready_objects(g_level_object_list[g_level_random_object_index])) phase.found = 1;
                if (!phase.found) {
                    g_level_random_object_index++;
                    if (g_level_random_object_index >= g_level_object_count) g_level_random_object_index = 0;
                }
            }
        } else g_level_random_object_index = 0;
    }
    state = g_feltzin_challenge_state;
    *(unsigned short *)((char *)state+0x40) = 0;
    *(unsigned short *)((char *)state+0x42) = 0;
    if (state[0x78/4]) gfx_add_draw_callback_third(UpdateSpaceProjectilePool,(void *)state[0x78/4]);
}

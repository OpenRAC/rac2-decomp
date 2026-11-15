#include "common.h"

/* A unit of its own (with the old unit's flags) so that the call to func_L02_003FD770 goes through its symbol: PAL has has
   that function as assembly at an address of its own, and a call within one object can only
   reach the object's own copy. */

extern char D_L02_001B11D0[8] __attribute__((sda));
extern char D_L02_001B11E0[8] __attribute__((sda));
extern float fast_vec_dist(void *, void *);
extern char g_camera_l02_position[];
extern int D_L02_001B32E8;
extern void moby_set_state(char *, int, int);
extern void cutscene_setup_camera(char *);

/* Raises the flag at 0x1B32E8. When the point at D_L02_001BA500 is within 0.0001 of the one at
   D_L02_001B11D0 the actor changes state by its kind (4 to 7, 5 to 6) and the two widgets are
   updated; otherwise func_L02_003FD770 runs unless the object's state half-word is 5. */
/* Checks whether the hero has reached the arena's control spot and, if so, opens the challenge menu. */
void arena_check_hero_at_console(char *actor) {
    D_L02_001B32E8 = 1;
    if (fast_vec_dist(g_camera_l02_position, D_L02_001B11D0) < 0.0001f) {
        if (*(unsigned char *)(actor + 0x20) == 4)
            moby_set_state(actor, 7, -1);
        else if (*(unsigned char *)(actor + 0x20) == 5)
            moby_set_state(actor, 6, -1);
        SetCamera5Mode(1, 0);
        object_copy_vector_to_selected(D_L02_001B11D0);
        cam_set_state_rotation(D_L02_001B11E0);
    } else if (*(short *)(*(char **)(g_camera_l02_position + 0x50) + 0x86) != 5) {
        cutscene_setup_camera(actor);
    }
}

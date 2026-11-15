#include "common.h"

extern void moby_step_at_own_position_factor(void *,float);
extern void moby_step_at_own_position(void *);
extern int ComputeRegionRouteHeading(void *,void *,void *,void *,int,void *,void *,float,float);
extern int moby_step_controller(void *,void *,float);
extern int moby_turn_toward_target_and_step(void *,void *,float);
extern void moby_set_state(void *,int,int);
extern void vec_add_random_offset(void *,float);
/* Moves an enemy each frame: walks it along its path or toward its target, and
   drops it into state 3 when it takes a hit. */
void enemy_update_movement(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    int mode = obj[0x42];
    if (mode<0) return;
    if (mode<6) goto low;
    if (mode>=8) return;
    goto high;
low:
        if (*(s16 *)(state+0x766)) moby_step_at_own_position_factor(obj,*(float *)(state+0x724));
        else moby_step_at_own_position(obj);
    return;
high:
        if (*(int *)(state+0x71C)!=-1 && *(s16 *)(state+0x76A)) {
            u8 *p=state+0x700;
            ComputeRegionRouteHeading(obj+0x10,p,state+0x748,state+0x200,*(int *)(state+0x730),state+0x73C,state+0x740,0.0f,0.4f);
            moby_step_controller(obj,p,*(float *)(state+0x748));
        } else moby_turn_toward_target_and_step(obj,state+0x700,*(float *)(state+0x720));
        if (obj[0x20]!=9 && obj[0x20]!=4 && obj[0x20]!=3) {
            if (*(int *)(state+0x190)>=6) moby_set_state(obj,3,-1);
            if (*(int *)(state+0x1A4)&3) {
                vec_add_random_offset(obj+0x10,0.01f);
                moby_set_state(obj,3,-1);
            }
        }

}


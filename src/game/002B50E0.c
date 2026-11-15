#include "include_asm.h"
#include "names.h"

/* func_002B50E0 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt). Its two returns
   keep the final status load in the block of the calls: with one shared return the block would
   end in the calls, add_branch_dependences would tie the argument moves of func_002B5828 and
   $a3 would be set last. func_002B52A0 is passed the two scratch slots retail really sets. */

extern int g_game_time __attribute__((sda));
extern char *moby_get_controller(void *);
extern void coll_check_ground_object_touch(void *, void *);
extern void coll_find_ground_below_object(void *, void *, float);
extern void vec_clear_128(void *);
extern void moby_update_controller_velocity(void *, void *, void *, void *, void *, float);
extern void coll_apply_velocity_and_resolve(void *, void *, void *, void *);
extern void moby_update_ground_contact(void *, void *, void *, void *);
extern void anim_update_foot_tilt_angles(void *, void *, float);
extern void thread_accumulate_timer_ticks(void);

typedef int PoseVector128 __attribute__((mode(TI)));

/* Runs one movement step for an object that has a movement controller: finds the ground, moves it toward the target, resolves collisions and returns the controller status. */
int moby_step_controller(void *self, void *target, float amount)
{
    char *data = moby_get_controller(self);
    PoseVector128 work[3];

    if (data == 0)
        return 8;
    if (g_game_time == *(int *)(data + 0xBC))
        return *(int *)(data + 0x94);
    *(int *)(data + 0x98) = *(int *)(data + 0x94);
    *(int *)(data + 0x94) = 0;
    if (!(*(int *)(data + 0x38) & 0x100))
        coll_check_ground_object_touch(self, data);
    {
        PoseVector128 *src = (PoseVector128 *)((char *)self + 0x10);
        work[0] = *src;
    }
    if (g_game_time - *(int *)(data + 0xBC) >= 2 || *(int *)(data + 0xBC) == 0) {
        coll_find_ground_below_object(self, data, 0.0f);
        *(unsigned char *)(data + 0xEA) = 0xFF;
        *(int *)(data + 0x9C) &= ~2;
        *(float *)(data + 0xB4) = 0.0f;
        *(int *)(data + 0x80) = 0;
        vec_clear_128(data + 0xA0);
    }
    *(int *)(data + 0xBC) = g_game_time;
    moby_update_controller_velocity(self, data, target, &work[1], &work[2], amount);
    coll_apply_velocity_and_resolve(self, data, &work[0], &work[2]);
    moby_update_ground_contact(self, data, target, &work[0]);
    anim_update_foot_tilt_angles(self, data, amount);
    thread_accumulate_timer_ticks();
    return *(int *)(data + 0x94);
}

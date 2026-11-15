#include "include_asm.h"
#include "names.h"
typedef int Q128 __attribute__((mode(TI)));

extern void moby_transform_joint_to_world(void *entity, int a, void *out);
extern void vec_scale_to_length(void *, void *, float);
extern void level_build_spawn_record(void *, void *, void *, void *, void *, void *, int, int, int);
extern void turret_start_swinging(char *);
extern char *group_pick_random_active_entity(int);

/* Launches every member of the object's group away from it at a fixed speed. */
void group_launch_members(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float start[4];
    float velocity[4];
    float offset[4];
    char *member;

    moby_transform_joint_to_world(moby, 0, start);
    *(Q128 *)offset = 0;
    offset[2] = 5.0f;
    vec_scale_to_length(velocity, moby + 0xC0, 2.0f);
    for (;;) {
        member = group_pick_random_active_entity(*(int *)(vars + 0x180));
        if (member == 0) break;
        turret_start_swinging(member);
        level_build_spawn_record(member, start, velocity, member + 0x10, offset, member + 0xF0, 0x5A, 0, 0);
    }
}

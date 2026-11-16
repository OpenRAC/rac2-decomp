#include "names.h"
/* func_PAL_L20_00449750, the PAL copy of func_L20_00443CF0: the same C with the callees are PAL's
   func_PAL_L20_004495C0 and func_PAL_L20_00445B90. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void yeedil_boss_compute_shot_launch_pal(char *, char *, char *, float *);
extern u8 *ActivateGroupMemberAt_pal(int, const float *, const float *, float);

/* Finds the group member to activate along the enemy aim and returns it. (PAL) */
u8 *group_activate_member_along_aim_pal(char *moby) {
    char *state = *(char **)(moby + 0x68);
    TI128 origin;
    TI128 direction;
    float spread;

    spread = 1.0471977f;
    yeedil_boss_compute_shot_launch_pal(moby, (char *)&origin, (char *)&direction, &spread);
    return ActivateGroupMemberAt_pal(*(int *)(state + 0x21C), (float *)&origin, (float *)&direction, spread);
}

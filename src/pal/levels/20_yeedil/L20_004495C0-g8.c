#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern void yeedil_boss_compute_shot_launch_pal(char *, char *, char *, float *);
extern char *turret_spawn_from_group_pal(char *, int, TI128 *, TI128 *);

char *yeedil_boss_launch_group_shot_pal(char *arg0) {
    TI128 v0;
    TI128 v1;
    TI128 *pa = &v0;
    TI128 *pb = &v1;
    char *state;
    float f;

    f = 0.78539824f;
    state = *(char **)(arg0 + 0x68);
    yeedil_boss_compute_shot_launch_pal(arg0, (char *)pa, (char *)pb, &f);
    return turret_spawn_from_group_pal(arg0, *(int *)(state + 0x240), pa, pb);
}

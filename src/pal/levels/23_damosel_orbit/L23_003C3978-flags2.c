#include "include_asm.h"
#include "names.h"

typedef int TI16 __attribute__((mode(TI)));
extern float g_enemy_snap_anim_blend __attribute__((sda));
extern TI16 g_coll_line_hit_point_2;
extern void moby_play_anim_and_link_pal(char *arg0, int arg1, int arg2, int arg3, int arg4, float arg5);
extern void mothership_project_point_onto_surface(TI16 *, float);
extern int CollLine(TI16 *, TI16 *, int, int, int);

/* Starts the snap animation and, if asked, moves the moby down to the ground below it (moby is reused as the pointer to b, as retail does). (PAL) */
void enemy_snap_to_ground_pal(char *moby, int snap) {
    TI16 ray_end;
    TI16 ray_start;
    TI16 *ray_end_ptr;

    if ((unsigned char)(*(unsigned char *)(moby + 0x43) - 5) >= 2 && *(unsigned char *)(moby + 0x20) != 2)
        moby_play_anim_and_link_pal(moby, 5, 0, 5, 1, g_enemy_snap_anim_blend);
    if (snap != 0) {
        TI16 *pos = (TI16 *)(moby + 0x10);

        /* ray_start's address is formed between the two copies, where retail has it. */
        ray_end_ptr = &ray_end;
        ray_end = *pos;
        moby = (char *)&ray_start;
        ray_start = *pos;
        mothership_project_point_onto_surface((TI16 *)moby, -2.0f);
        mothership_project_point_onto_surface(ray_end_ptr, 0.1f);
        if (CollLine((TI16 *)moby, ray_end_ptr, 0x12, 0, 0) != 0)
            *pos = g_coll_line_hit_point_2;
    }
}

#include "include_asm.h"
#include "names.h"

typedef int TI16 __attribute__((mode(TI)));
extern float g_enemy_snap_anim_blend __attribute__((sda));
extern TI16 g_coll_line_hit_point_2;
extern void moby_play_anim_and_link_pal(char *arg0, int arg1, int arg2, int arg3, int arg4, float arg5);
extern void mothership_project_point_onto_surface(TI16 *, float);
extern int CollLine(TI16 *, TI16 *, int, int, int);

void func_PAL_L23_003C3AA0(char *arg0, int arg1) {
    TI16 a;
    TI16 b;
    TI16 *p;

    if ((unsigned char)(*(unsigned char *)(arg0 + 0x43) - 5) >= 2 && *(unsigned char *)(arg0 + 0x20) != 2)
        moby_play_anim_and_link_pal(arg0, 5, 0, 5, 1, g_enemy_snap_anim_blend);
    if (arg1 != 0) {
        TI16 *pos = (TI16 *)(arg0 + 0x10);

        /* b's address is formed between the two copies, where retail has it. */
        p = &a;
        a = *pos;
        arg0 = (char *)&b;
        b = *pos;
        mothership_project_point_onto_surface((TI16 *)arg0, -2.0f);
        mothership_project_point_onto_surface(p, 0.1f);
        if (CollLine((TI16 *)arg0, p, 0x12, 0, 0) != 0)
            *pos = g_coll_line_hit_point_2;
    }
}

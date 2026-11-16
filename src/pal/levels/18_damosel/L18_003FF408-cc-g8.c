#include "names.h"
/* func_PAL_L18_003FF408, the PAL copy of func_L18_003FB308: the same C, where rename func_L18_003FB620 becomes func_PAL_L18_003FF768; scale D_L18_001B0580; scale D_L18_001B0580. */
#include "common.h"

extern int g_platform_move_frames __attribute__((sda));
extern float g_platform_move_distance __attribute__((sda));
extern int g_platform_wait_frames __attribute__((sda));
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void moby_set_state(u8 *, int, int);
extern int flag_set_first_pending(u8 *);
extern int snd_play_from_class_bank(int, int, u8 *, int);
extern void part_spawn_trail_particles_pal(u8 *);

/* Slides the object out and back by a fixed step each frame, moving a linked object with it, and sprays particles while it moves out. (PAL: 50 Hz timings) */
void sliding_l18_platform_update_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    switch (moby[0x20]) {
    case 0:
        qcopy_nc(vars, moby + 0x10);
        vec_scale_to_length(vars + 0x10, moby + 0xC0, g_platform_move_distance / (((int)(g_platform_move_frames) * 5 + 2) / 6));
        moby_set_state(moby, 1, -1);
        *(int *)(vars + 0x20) = 0;
        break;
    case 1: {
        if (*(int *)(vars + 0x20) >= 2) {
            FastVecSub(moby + 0x10, moby + 0x10, vars + 0x10);
            FastVecAdd(g_moby_l18_table[0] + (*(int *)(vars + 0x24) << 8) + 0x10,
                         g_moby_l18_table[0] + (*(int *)(vars + 0x24) << 8) + 0x10,
                         vars + 0x10);
            --*(int *)(vars + 0x20);
        } else if (*(int *)(vars + 0x20) > 0) {
            qcopy_nc(moby + 0x10, vars);
            qcopy_nc((u8 *)((*(int *)(vars + 0x24) << 8) +
                           (int)g_moby_l18_table[0] + 0x10), vars);
            --*(int *)(vars + 0x20);
        }
        break;
    }
    case 2:
        if (flag_set_first_pending(moby))
            snd_play_from_class_bank(0, 0, moby, 0x1152);
        if (*(int *)(vars + 0x20) < (((int)(g_platform_move_frames) * 5 + 2) / 6)) {
            FastVecAdd(moby + 0x10, moby + 0x10, vars + 0x10);
            FastVecSub(g_moby_l18_table[0] + (*(int *)(vars + 0x24) << 8) + 0x10,
                         g_moby_l18_table[0] + (*(int *)(vars + 0x24) << 8) + 0x10,
                         vars + 0x10);
            ++*(int *)(vars + 0x20);
        }
        if (*(int *)(vars + 0x28))
            part_spawn_trail_particles_pal(moby);
        if (g_platform_wait_frames < *(u16 *)(moby + 0x96))
            moby_set_state(moby, 1, -1);
        break;
    }
    if (*(u16 *)(moby + 0x96) <= 0xFFFEu)
        ++*(u16 *)(moby + 0x96);
}

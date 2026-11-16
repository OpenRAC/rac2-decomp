#include "include_asm.h"

#include "common.h"
extern void part_update_scrolling_effect(char *object);
extern void FastVecAdd(char *out, char *first, char *second);
extern void projectile_check_hit_explode_pal(char *a0, char *a1);
extern int math_fast_float_d(char *a0);
extern void moby_mark_spawned(char *a0);
extern void gfx_add_draw_callback_third(void (*callback)(char *), char *object);

/* Three-state gate on the record's byte 0x20. State 0 stamps itself state 1 and falls into the
 * state-1 body (a 16-byte copy of the record's vector, the pair update and the shared sub-object
 * test that promotes the record to state 2); state 2 destroys the record and returns; every other
 * state, and the end of the state-1 body, re-arms the record through the level callback. */
void timed_record_update_pal(char *moby)
{
    char *handle = *(char **)(moby + 0x68);
    char local[16];

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned char *)(moby + 0x20) = 1;
    case 1: {
        char *p = moby + 0x10;

        qcopy(local, p);
        FastVecAdd(p, handle, p);
        projectile_check_hit_explode_pal(moby, local);
        if (math_fast_float_d(handle + 0x10) != 0)
            *(unsigned char *)(moby + 0x20) = 2;
        break;
    }
    case 2:
        moby_mark_spawned(moby);
        return;
    default:
        break;
    }
    gfx_add_draw_callback_third(part_update_scrolling_effect, moby);
}

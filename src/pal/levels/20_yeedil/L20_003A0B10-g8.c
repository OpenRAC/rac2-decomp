#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct YeedilObject {
    char reserved00[0x20];
    unsigned char state;
    char reserved21[0xB8 - 0x21];
    struct YeedilObject *parent;
    char reservedBC[0x100 - 0xBC];
} YeedilObject;
extern unsigned short *g_group_l20_id_lists[];
extern int g_group_count;
extern YeedilObject *g_group_l20_member_table;
extern struct {
    char reserved00[0x80];
    float position[4];
} D_00189E20;
extern int trooper_init_spawned_pal(void *, const void *, void *);
extern float mat_fast_helper_a(float, float);

/* Finds the first object of the group whose state is 6, makes parent its parent and
   sets it up at pos; returns it, or 0 if there is none or the setup fails. */
YeedilObject *trooper_spawn_from_free_slot_pal(void *parent, int group, const float *pos) {
    YeedilObject *found = 0;
    unsigned short *p = g_group_l20_id_lists[group];
    YeedilObject *obj;

    if ((group & 0xFF) == 0xFF) {
        goto end;
    }
    if (g_group_count < group) {
        goto end;
    }
    if (p == 0) {
        goto end;
    }
    for (;;) {
        obj = &g_group_l20_member_table[*p & 0x7FFF];

        if (obj == 0) {
            goto end;
        }
        if (obj->state == 6) {
            found = obj;
            found->parent = parent;
            goto end;
        }
        p++;
        if ((group & 0xFF) == 0xFF) {
            goto end;
        }
        if (g_group_count < group) {
            goto end;
        }
        if (p == 0) {
            goto end;
        }
        if ((short)p[-1] >= 0) {
            continue;
        }
        if (p == g_group_l20_id_lists[group]) {
            continue;
        }
        break;
    }
end:
    if (found != 0) {
        TI128 buf;

        qzero(&buf);

        ((float *)&buf)[2] = mat_fast_helper_a(g_hero_state.position[0] - pos[0],
                                           g_hero_state.position[1] - pos[1]);
        if (trooper_init_spawned_pal(found, pos, &buf) == 0) {
            found = 0;
        }
    }
    return found;
}

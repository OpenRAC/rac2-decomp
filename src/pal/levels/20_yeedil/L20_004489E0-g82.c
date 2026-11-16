#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float component[4]; } Vector431E0;
extern u16 *g_group_l20_id_lists[];
extern char *g_group_l20_member_table;
extern int g_group_count __attribute__((sda));
extern int moby_is_state_six(char *);
extern void nanotech_crate_init(char *);
extern int moby_fuse_linked_objects(char *, char *, char *, char **, int);
extern char *glow_effect_create(char *, char *, int, int);

char *yeedil_boss_place_group_member_pal(char *arg0, TI128 *arg1) {
    char *state = *(char **)(arg0 + 0x68);
    u16 *rec;
    char *found = 0;
    Vector431E0 buf;

    for (rec = g_group_l20_id_lists[*(int *)(state + 0x218)];
         (*(int *)(state + 0x218) & 0xFF) != 0xFF && *(int *)(state + 0x218) <= g_group_count && rec != 0 &&
         ((rec != 0 && (s16)rec[-1] >= 0) || rec == g_group_l20_id_lists[*(int *)(state + 0x218)]);
         rec++) {
        char *e = g_group_l20_member_table + ((*rec & 0x7FFF) << 8);

        if (e != 0 && moby_is_state_six(e) != 0)
            found = e;
        break;
    }
    if (found != 0) {
        char *p = found + 0x10;
        char *s2;

        qcopy(p, arg1);
        nanotech_crate_init(found);
        moby_fuse_linked_objects(found, p, found + 0xF0, 0, 0);
        s2 = *(char **)(found + 0x68);
        *(int *)(s2 + 0xAC) |= 8;
        qcopy(&buf, p);
        buf.component[2] -= 0.5f;
        glow_effect_create(found, (char *)&buf, 0x12C, 0);
    }
    return found;
}

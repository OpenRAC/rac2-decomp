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

/* Takes the first usable object of the enemy group, moves it to the given place and starts it with a small effect. Returns that object. (PAL) */
char *yeedil_boss_place_group_member_pal(char *moby, TI128 *position) {
    char *state = *(char **)(moby + 0x68);
    u16 *rec;
    char *found = 0;
    Vector431E0 buf;

    for (rec = g_group_l20_id_lists[*(int *)(state + 0x218)];
         (*(int *)(state + 0x218) & 0xFF) != 0xFF && *(int *)(state + 0x218) <= g_group_count && rec != 0 &&
         ((rec != 0 && (s16)rec[-1] >= 0) || rec == g_group_l20_id_lists[*(int *)(state + 0x218)]);
         rec++) {
        char *member = g_group_l20_member_table + ((*rec & 0x7FFF) << 8);

        if (member != 0 && moby_is_state_six(member) != 0)
            found = member;
        break;
    }
    if (found != 0) {
        char *member_pos = found + 0x10;
        char *member_vars;

        qcopy(member_pos, position);
        nanotech_crate_init(found);
        moby_fuse_linked_objects(found, member_pos, found + 0xF0, 0, 0);
        member_vars = *(char **)(found + 0x68);
        *(int *)(member_vars + 0xAC) |= 8;
        qcopy(&buf, member_pos);
        buf.component[2] -= 0.5f;
        glow_effect_create(found, (char *)&buf, 0x12C, 0);
    }
    return found;
}

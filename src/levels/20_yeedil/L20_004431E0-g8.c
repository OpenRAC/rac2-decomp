#include "names.h"
/* Finds the first entity of the group state+0x218 (if func_00312B58 accepts it), moves it to
   arg1, and spawns func_L20_0039BDF0 0.5 below it.  The group walk is the usual macro shape
   (see src/game/0031F210-group-g8.c); its redundant inner `rec != 0` keeps jump1 from
   duplicating the exit test, and -frac2-keep-block-order keeps the rotated test after the body. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float component[4]; } Vector431E0;

extern u16 *D_L20_001FBB20[];
extern char *D_L20_001B2F9C;
extern int D_L20_001B2FB8 __attribute__((sda));
extern int moby_is_state_six(char *);
extern void nanotech_crate_init(char *);
extern int moby_fuse_linked_objects(char *, char *, char *, char **, int);
extern char *glow_effect_create(char *, char *, int, int);

/* Takes the first usable object of the enemy group, moves it to the given place and starts it with a small effect. Returns that object. */
char *yeedil_boss_place_group_member(char *moby, TI128 *position) {
    char *state = *(char **)(moby + 0x68);
    u16 *rec;
    char *found = 0;
    Vector431E0 buf;

    for (rec = D_L20_001FBB20[*(int *)(state + 0x218)];
         (*(int *)(state + 0x218) & 0xFF) != 0xFF && *(int *)(state + 0x218) <= D_L20_001B2FB8 && rec != 0 &&
         ((rec != 0 && (s16)rec[-1] >= 0) || rec == D_L20_001FBB20[*(int *)(state + 0x218)]);
         rec++) {
        char *e = D_L20_001B2F9C + ((*rec & 0x7FFF) << 8);

        if (e != 0 && moby_is_state_six(e) != 0)
            found = e;
        break;
    }
    if (found != 0) {
        char *p = found + 0x10;
        char *found_vars;

        qcopy(p, position);
        nanotech_crate_init(found);
        moby_fuse_linked_objects(found, p, found + 0xF0, 0, 0);
        found_vars = *(char **)(found + 0x68);
        *(int *)(found_vars + 0xAC) |= 8;
        qcopy(&buf, p);
        buf.component[2] -= 0.5f;
        glow_effect_create(found, (char *)&buf, 0x168, 0);
    }
    return found;
}

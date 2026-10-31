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
extern int func_00312B58(char *);
extern void func_L02_003A6FE8(char *);
extern int func_L02_002EF388(char *, char *, char *, char **, int);
extern char *func_L20_0039BDF0(char *, char *, int, int);

char *func_L20_004431E0(char *arg0, TI128 *arg1) {
    char *state = *(char **)(arg0 + 0x68);
    u16 *rec;
    char *found = 0;
    Vector431E0 buf;

    for (rec = D_L20_001FBB20[*(int *)(state + 0x218)];
         (*(int *)(state + 0x218) & 0xFF) != 0xFF && *(int *)(state + 0x218) <= D_L20_001B2FB8 && rec != 0 &&
         ((rec != 0 && (s16)rec[-1] >= 0) || rec == D_L20_001FBB20[*(int *)(state + 0x218)]);
         rec++) {
        char *e = D_L20_001B2F9C + ((*rec & 0x7FFF) << 8);

        if (e != 0 && func_00312B58(e) != 0)
            found = e;
        break;
    }
    if (found != 0) {
        char *p = found + 0x10;
        char *s2;

        qcopy(p, arg1);
        func_L02_003A6FE8(found);
        func_L02_002EF388(found, p, found + 0xF0, 0, 0);
        s2 = *(char **)(found + 0x68);
        *(int *)(s2 + 0xAC) |= 8;
        qcopy(&buf, p);
        buf.component[2] -= 0.5f;
        func_L20_0039BDF0(found, (char *)&buf, 0x168, 0);
    }
    return found;
}

#include "common.h"

/* This unit is built with -G8: func_L20_0039DBC8 needs the -G8 profile. In a -G0 unit
   the loop's copies of the group index and the entry address are allocated to other
   registers (as in func_L20_00409480). It does not share L20_0039C448-g8.c, which
   declares D_L20_001FBB20 and D_L20_001B2F9C as char tables.

   The objects are typed as a struct, so the store to found->parent cannot alias the
   scalar globals: loop.c hoists the table-base load and the in-loop re-test of
   D_L20_001B2FB8, and cse2 folds the hoisted re-test into the retail's
   `daddu $t1,$zero,$zero` + `bnez $t1`. The clear of the 16-byte buffer is qzero, which
   puts the `sq $zero` first after the found test, as in the retail. */

typedef int TI128 __attribute__((mode(TI)));

/* The level's object table: 0x100 bytes per object. */
typedef struct YeedilObject {
    char reserved00[0x20];
    unsigned char state;
    char reserved21[0xB8 - 0x21];
    struct YeedilObject *parent;
    char reservedBC[0x100 - 0xBC];
} YeedilObject;

extern unsigned short *D_L20_001FBB20[];

extern int D_L20_001B2FB8;

extern YeedilObject *D_L20_001B2F9C;

extern struct {
    char reserved00[0x80];
    float position[4];
} D_00189E20;

extern int func_L20_0039DCF8(void *, const void *, void *);

extern float func_00283248(float, float);

/* Finds the first object of the group whose state is 6, makes parent its parent and
   sets it up at pos; returns it, or 0 if there is none or the setup fails. */
YeedilObject *func_L20_0039DBC8(void *parent, int group, const float *pos) {
    YeedilObject *found = 0;
    unsigned short *p = D_L20_001FBB20[group];
    YeedilObject *obj;

    if ((group & 0xFF) == 0xFF) {
        goto end;
    }
    if (D_L20_001B2FB8 < group) {
        goto end;
    }
    if (p == 0) {
        goto end;
    }
    for (;;) {
        obj = &D_L20_001B2F9C[*p & 0x7FFF];

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
        if (D_L20_001B2FB8 < group) {
            goto end;
        }
        if (p == 0) {
            goto end;
        }
        if ((short)p[-1] >= 0) {
            continue;
        }
        if (p == D_L20_001FBB20[group]) {
            continue;
        }
        break;
    }
end:
    if (found != 0) {
        TI128 buf;

        qzero(&buf);

        ((float *)&buf)[2] = func_00283248(D_00189E20.position[0] - pos[0],
                                           D_00189E20.position[1] - pos[1]);
        if (func_L20_0039DCF8(found, pos, &buf) == 0) {
            found = 0;
        }
    }
    return found;
}

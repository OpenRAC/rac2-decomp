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
extern unsigned short *D_L20_001FBB20[];
extern int D_L20_001B2FB8;
extern YeedilObject *D_L20_001B2F9C;
extern struct {
    char reserved00[0x80];
    float position[4];
} D_00189E20;
extern int func_PAL_L20_003A0C40(void *, const void *, void *);
extern float func_00283248(float, float);

/* Finds the first object of the group whose state is 6, makes parent its parent and
   sets it up at pos; returns it, or 0 if there is none or the setup fails. */
YeedilObject *func_PAL_L20_003A0B10(void *parent, int group, const float *pos) {
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
        if (func_PAL_L20_003A0C40(found, pos, &buf) == 0) {
            found = 0;
        }
    }
    return found;
}

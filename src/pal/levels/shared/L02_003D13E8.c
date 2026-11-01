#include "include_asm.h"

#include "common.h"
extern char *D_L02_001B359C __attribute__((sda));
extern char *D_L02_001FC060[];
extern int D_L02_001B35B8 __attribute__((sda));
typedef int L02Word;
extern L02Word D_L02_001B35B8 __attribute__((sda));
extern int func_002A7820(int, int);
struct L02GroupObject {
    char pad[0x21];
    unsigned char group;
};
struct L02GroupEntityObj {
    char pad[0x378];
    short f378;
};
struct L02GroupEntity {
    char pad[0x68];
    struct L02GroupEntityObj *obj;
};
extern int D_L02_001B35B8 __attribute__((sda));

/* Gives every entity of the object's group a random timer between 0x1E and 0x5A at +0x378
   of its private block. */
void func_PAL_L02_003D13E8(struct L02GroupObject *arg0)
{
    unsigned short *q;
    unsigned short *p;
    struct L02GroupEntity *e;

    if (arg0->group == 0xFF)
        return;
    q = (unsigned short *)D_L02_001FC060[arg0->group];
    if (q != 0) {
        p = q;
        while (arg0->group != 0xFF && arg0->group <= D_L02_001B35B8 && p != 0 &&
               ((p != 0 && (short)p[-1] >= 0) ||
                p == (unsigned short *)D_L02_001FC060[arg0->group])) {
            struct L02GroupEntityObj *o;

            e = (struct L02GroupEntity *)(D_L02_001B359C + ((*p & 0x7FFF) << 8));
            if (e == 0)
                break;
            o = e->obj;
            p++;
            o->f378 = ((s32)(func_002A7820(0x1E, 0x5A)) * 5 + 2) / 6;
        }
    }
}


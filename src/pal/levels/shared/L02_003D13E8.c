#include "include_asm.h"

#include "common.h"
extern char *g_moby_l02_pool __attribute__((sda));
extern char *g_entity_group_lists[];
extern int g_group_max_index __attribute__((sda));
typedef int L02Word;
extern L02Word g_group_max_index __attribute__((sda));
extern int math_random_int_range(int, int);
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
extern int g_group_max_index __attribute__((sda));

/* Gives every entity of the object's group a random timer between 0x1E and 0x5A at +0x378
   of its private block. */
void func_PAL_L02_003D13E8(struct L02GroupObject *arg0)
{
    unsigned short *q;
    unsigned short *p;
    struct L02GroupEntity *e;

    if (arg0->group == 0xFF)
        return;
    q = (unsigned short *)g_entity_group_lists[arg0->group];
    if (q != 0) {
        p = q;
        while (arg0->group != 0xFF && arg0->group <= g_group_max_index && p != 0 &&
               ((p != 0 && (short)p[-1] >= 0) ||
                p == (unsigned short *)g_entity_group_lists[arg0->group])) {
            struct L02GroupEntityObj *o;

            e = (struct L02GroupEntity *)(g_moby_l02_pool + ((*p & 0x7FFF) << 8));
            if (e == 0)
                break;
            o = e->obj;
            p++;
            o->f378 = ((s32)(math_random_int_range(0x1E, 0x5A)) * 5 + 2) / 6;
        }
    }
}


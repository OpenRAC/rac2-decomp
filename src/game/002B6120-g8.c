#include "ps2_hw.h"
#include "common.h"
#include "include_asm.h"

/* Both accumulator words live in small data, so this file is built with -G8.
   They differ from program to program, so they carry no level. */
extern int ref_L00_002B62A0_00 __attribute__((sda));
extern float ref_L00_002B62A0_01 __attribute__((sda));

/* Counts one tick and folds the hardware timer, converted from unsigned, into
   the small-data float accumulator. */
void func_002B62A0(void)
{
    unsigned int ticks = T0_COUNT;

    ref_L00_002B62A0_00 = ref_L00_002B62A0_00 + 1;
    ref_L00_002B62A0_01 = ref_L00_002B62A0_01 + (float)ticks;
}

typedef struct Node Node;

struct Node {
    unsigned char pad0[0x20];
    signed char flag20;
    unsigned char pad21[7];
    Node *next;
    unsigned char pad2c[8];
    unsigned short flags;
    unsigned char pad36[0x2E];
    void (*vfunc)(Node *);
};

extern Node *func_002A08A0(void);
extern void func_002A05A8(Node *);
extern void func_002A0F48(Node *);
extern Node *ref_002B6658_00 __attribute__((sda));

/* Builds the visible object list (its head kept in small data), then for each
   live object: advances its animation unless flag 0x40 is set, calls its update
   hook (call_hook, as RAC1's update_visible_resident_objects does) and refreshes
   its bounds unless flag 4 is set. */
void func_002B6658(void)
{
    Node *t;

    ref_002B6658_00 = func_002A08A0();
    t = ref_002B6658_00;
    for (; t != 0; t = t->next) {
        if (t->flag20 >= 0) {
            if ((t->flags & 0x40) == 0)
                func_002A05A8(t);
            call_hook(t->vfunc, t);
            if ((t->flags & 4) == 0)
                func_002A0F48(t);
        }
    }
}

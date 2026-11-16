#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    TI128 a;
    TI128 b;
    float life;
    void *owner;
    int pad28, pad2C;
} Slot00305438;
extern void moby_transform_joint_to_world(void *a, int b, void *c);
extern Slot00305438 ref_00305438_00[];

/* Takes the first free entry of the table for the object and counts it. */
void part_add_trail_entry_pal(void *obj, void *other)
{
    char *vars = *(char **)((char *)obj + 0x68);
    TI128 joint_pos;
    int i;

    moby_transform_joint_to_world(obj, 1, &joint_pos);
    for (i = 0; i < 100; i++) {
        if (ref_00305438_00[i].owner == 0) {
            Slot00305438 *e = &ref_00305438_00[i];

            *(int *)(vars + 0x64) += 1;
            e->owner = obj;
            e->life = 1e+02f;
            qcopy(&e->b, other);
            qcopy(e, &joint_pos);
            break;
        }
    }
}

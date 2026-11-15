#include "names.h"
/* Copies the quad at +0x10 of the object to the stack with the approved qcopy helper and
   stores func_L08_003D8290(&copy, v + 3, v - 20), v the float at +0x3E8 of its state, at
   +0x434 of the state. */
#include "common.h"
typedef unsigned int ti_word __attribute__((mode(TI)));
extern float coll_find_ground_height_between(void *, float, float);

/* Finds the ground height below the object and stores it in its private data. */
void moby_store_ground_height(char *moby) {
    ti_word position;
    char *vars = *(char **)(moby + 0x68);
    float baseHeight;
    qcopy(&position, moby + 0x10);
    baseHeight = *(float *)(vars + 0x3E8);
    *(float *)(vars + 0x434) = coll_find_ground_height_between(&position, baseHeight + 3.0f, baseHeight - 20.0f);
}

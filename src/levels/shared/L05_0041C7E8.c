#include "names.h"
/* Copies the quad at +0x10 and the three quads at +0xC0 of a into b with the approved
   qcopy helper, then, when the word at +4 of b's state is set, hands b's +0xD0 vector (as
   both arguments) and -1.0f to func_00282D30. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void FastVecScale(char *, char *, float);

/* Copies the owner's position and turn onto a part object, and flips one axis if the part is the mirrored one. */
void equipment_copy_owner_transform(char *owner, char *part)
{
    char *partVars = *(char **)(part + 0x68);
    int i;

    qcopy(part + 0x10, owner + 0x10);
    for (i = 0; i < 3; i++)
        qcopy(part + 0xC0 + i * 16, owner + 0xC0 + i * 16);
    if (*(int *)(partVars + 4) != 0)
        FastVecScale(part + 0xD0, part + 0xD0, -1.0f);
}

#include "common.h"

extern void FastVecScale(char *dst, char *src, float value);

/* Copies the donor record into the object: the header quadword, then the two transform rows that its mode selects, then the last row. */
void donor_transform_copy(char *object)
{
    char *sub = *(char **)(object + 0x68);
    char *src = *(char **)(sub + 0x50);

    qcopy(object + 0x10, src + 0x10);
    switch (*(int *)(sub + 0x54)) {
    case 0:
        qcopy(object + 0xC0, src + 0xC0);
        qcopy(object + 0xD0, src + 0xD0);
        break;
    case 1:
        qcopy(object + 0xC0, src + 0xC0);
        FastVecScale(object + 0xD0, src + 0xD0, -1.0f);
        break;
    default:
        return;
    }
    qcopy(object + 0xE0, src + 0xE0);
}

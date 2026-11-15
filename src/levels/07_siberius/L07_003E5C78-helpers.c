#include "common.h"

extern void moby_set_state(unsigned char *, int, int);

extern void FastVecSub(void *, void *, void *);

extern void vec_transform_by_object_or_given(char *, char *, char *, char *);

extern void vec_scale_to_length(void *, void *, float);

/* Sends an idle entity to a new spot and shrinks it to a tenth of its size, ready to be
   launched. */
void entity_send_and_shrink(char *entity, char *newPos, char *homePos, char *platform)
{
    char *ptr;
    unsigned short flags;
    int rowsLeft;

    if (*(unsigned char *)(entity + 0x20) != 8)
        return;

    ptr = *(char **)(entity + 0x68);
    *(unsigned short *)(entity + 0x34) = (*(unsigned short *)(entity + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(entity + 0x98) = 0;
    moby_set_state((unsigned char *)entity, 9, 4);

    qcopy(entity + 0x10, newPos);
    qcopy(ptr + 0x230, homePos);
    *(int *)(ptr + 0x260) = (int)platform;
    *(unsigned char *)(entity + 0x7F) = 0;

    if (platform != 0) {
        FastVecSub(ptr + 0x220, homePos, platform + 0x10);
        vec_transform_by_object_or_given(platform, ptr + 0x220, ptr + 0x220, 0);
    }
    flags = *(unsigned short *)(entity + 0x34);
    ptr = entity + 0xC0;
    rowsLeft = 2;
    *(unsigned short *)(entity + 0x34) = flags | 0x100;
    do {
        vec_scale_to_length(ptr, ptr, 0.1f);
        ptr += 0x10;
        rowsLeft--;
    } while (rowsLeft >= 0);
}

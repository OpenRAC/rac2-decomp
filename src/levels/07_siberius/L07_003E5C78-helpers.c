#include "common.h"

extern void func_002A7750(unsigned char *, int, int);

extern void func_00282CF0(void *, void *, void *);

extern void func_002AFDD8(char *, char *, char *, char *);

extern void func_00282F20(void *, void *, float);

/* Sends an idle entity to a new spot and shrinks it to a tenth of its size, ready to be
   launched. */
void func_L07_003E5C78(char *entity, char *newPos, char *homePos, char *platform)
{
    char *ptr;
    unsigned short flags;
    int rowsLeft;

    if (*(unsigned char *)(entity + 0x20) != 8)
        return;

    ptr = *(char **)(entity + 0x68);
    *(unsigned short *)(entity + 0x34) = (*(unsigned short *)(entity + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(entity + 0x98) = 0;
    SetMobyState((unsigned char *)entity, 9, 4);

    qcopy(entity + 0x10, newPos);
    qcopy(ptr + 0x230, homePos);
    *(int *)(ptr + 0x260) = (int)platform;
    *(unsigned char *)(entity + 0x7F) = 0;

    if (platform != 0) {
        FastVecSub(ptr + 0x220, homePos, platform + 0x10);
        TransformVectorByObjectOrGiven(platform, ptr + 0x220, ptr + 0x220, 0);
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

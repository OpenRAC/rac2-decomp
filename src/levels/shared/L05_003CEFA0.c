#include "common.h"
extern char *func_0029EFD0(int);
extern void func_L05_003CF9C8(char *);
extern int func_L05_003CFC28(int);
extern float D_L05_001AFB68[] SDATA(D_L05_001AFB68);

/* Spawns one flying piece of a given kind at a position, sized to match its owner. */
char *func_L05_003CEFA0(char *owner,void *position,int kind)
{
    char *object=CreateMoby(kind);
    if (object) {
        char *state=*(char **)(object+0x68);
        int index;
        qcopy(object+0x10,position);
        qzero(state+0x10);
        object[0x31]=1;
        RandomizeObjectReachAndAngles(object);
        object[0x20]=1;
        *(u64 *)(object+0x38)=*(u64 *)(owner+0x38);
        index=ClassIdToTableIndex(*(short *)(object+0xAA));
        *(float *)(object+0x2C) *= D_L05_001AFB68[index];
    }
    return object;
}

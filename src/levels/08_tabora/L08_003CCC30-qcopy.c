#include "common.h"

extern void *func_0029EFD0(int id);
extern float func_00283CE0(int value);
extern void func_002A0F48(void *moby);

/* Creates one waterfall piece of the given class at the parent waterfall's position and copies the parent's settings into it. */
void *func_L08_003CCC30(void *parent, int classId, short rotationSpeed, int isOpen, int linkIndex, unsigned char minAlpha,
                        unsigned char rotates) {
    unsigned char *parentBytes = (unsigned char *)parent;
    unsigned char *child = (unsigned char *)CreateMoby(classId);
    unsigned char *childVars;

    if (child) {
        child[0x30] = parentBytes[0x30];
        *(unsigned short *)(child + 0x32) = *(unsigned short *)(parentBytes + 0x32);
        child[0x31] = 1;
        qcopy(child + 0x10, parentBytes + 0x10);
        qcopy(child + 0xF0, parentBytes + 0xF0);
        *(float *)(child + 0xF8) = *(float *)(parentBytes + 0xF8);
        *(int *)(child + 0xF0) = 0;
        *(int *)(child + 0xF4) = 0;
        childVars = (unsigned char *)*(unsigned int *)(child + 0x68);
        *(unsigned short *)(childVars + 0x4) = rotationSpeed;
        childVars[0x1C] = isOpen;
        *(float *)(childVars + 0x8) = IntToFloat(isOpen);
        childVars[0x1D] = rotates;
        *(int *)childVars = linkIndex;
        childVars[0x1E] = minAlpha;
        *(unsigned short *)(childVars + 0x6) = 0;
        func_002A0F48(child);
        child[0x20] = 0;
    }
    return child;
}

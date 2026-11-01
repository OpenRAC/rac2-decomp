#include "include_asm.h"

#include "common.h"
extern unsigned char D_00189E20[];
struct SetupOwnerView {
    unsigned char prefix[0x194];
    unsigned char *matrix;
    unsigned char gap198[0x290-0x198];
    short value290;
    unsigned char value292;
    unsigned char value293;
    unsigned char gap294[0x314-0x294];
    int value314;
};
extern struct SetupOwnerView D_L00_001B8C80;
struct SetupBlendView {
    unsigned int word0;
    float value4;
    float value8;
    unsigned int wordC;
};
extern void func_00282C88(void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern float func_00283248(float,float);

void func_PAL_L00_0042DA78(unsigned char *object)
{
    unsigned char *data=*(unsigned char **)(object+0x70);
    unsigned char *part=data+0x40;
    unsigned char *hero=D_00189E20;
    unsigned char *updated;
    unsigned char *tracking;
    unsigned char *translation;
    unsigned char *matrix;
    *(float *)(part+0x4C)=1.5f;
    *(float *)(part+0x48)=0.20943953096866608f;
    *(float *)(part+0x58)=0.0017453294713050127f;
    *(float *)(part+0x5C)=-0.00436332356184721f;
    *(int *)(part+0x40)=0;
    *(void **)(part+0x44)=*(void **)(hero+0x2290);
    {
        unsigned char *settings=*(unsigned char **)(object+0x70)+0xA0;
        *(float *)settings=4.639999866485596f;
        *(float *)(settings+4)=0.5f;
        *(float *)(settings+0x10)=2.0f;
        *(float *)(settings+0x14)=0.05f;
    }
    {
        unsigned char *settings=*(unsigned char **)(object+0x70);
        *(float *)(settings+0x10)=0.01f;
        *(float *)(settings+0x14)=0.3f;
        *(short *)(settings+0x1E)=100;
        *(int *)(settings+0x18)=0;
        *(short *)(settings+0x1C)=0;
        func_00282C88(settings);
    }
    {
        unsigned char *settings=*(unsigned char **)(object+0x70);
        struct SetupBlendView *blend=(struct SetupBlendView *)(settings+0x30);
        blend->value4=0.02f;
        blend->value8=0.2f;
        blend->wordC=0;
        *(unsigned int *)(settings+0x30)=0;
    }
    updated=*(unsigned char **)(object+0x70);
    tracking=updated+0xB8;
    *(int *)(tracking+4)=0;
    matrix=D_L00_001B8C80.matrix;
    translation=object+0x30;
    qcopy(translation,matrix+0x30);
    qcopy(object,matrix);
    qcopy(object+0x10,matrix+0x10);
    qcopy(object+0x20,matrix+0x20);
    qcopy(object+0x40,object);
    *(short *)(object+0x7E)=0;
    if((unsigned int)(*(int *)(hero+0x2294)-0x2B)<2) {
        *(float *)(part+0x30)=func_00283180(*(float *)(hero+0xAEC));
        *(float *)(part+0x34)=func_00283198(*(float *)(hero+0xAEC));
        *(int *)(part+0x38)=0;
        *(float *)(updated+0xB8)=*(float *)(hero+0xAEC);
        *(void **)(tracking+8)=*(void **)(hero+0xAD4);
    } else {
        unsigned char *direction=data+0x70;
        func_00282CF0(direction,*(unsigned char **)(hero+0xAA4)+0x10,translation);
        *(int *)(part+0x38)=0;
        *(int *)(part+0x3C)=0;
        func_00282F20(direction,direction,1.0f);
        *(float *)(updated+0xB8)=func_00283248(*(float *)(part+0x30),*(float *)(part+0x34));
        *(void **)(tracking+8)=*(void **)(hero+0xAA4);
    }
    D_L00_001B8C80.value293=2;
    D_L00_001B8C80.value290=1;
    D_L00_001B8C80.value314=50;
}



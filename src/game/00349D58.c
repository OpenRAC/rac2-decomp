#include "names.h"
/* func_00349D58: initialises the HUD widget's text, sprites and fade keys. A unit of its own for
 * -frac2-keep-float-pun-source (config/cflags.txt): a colour read twice keeps its word in $v0, set
 * after the previous call, with one mtc1 into a saved FPR; a colour read once folds to li.s
 * (docs/build/compiler-notes.md). WriteBits is the one spelling for every colour. Same-file C calls and
 * prototypes differ from 00345358.c, so it cannot live there. */
static __inline__ float WriteBits(unsigned int bits)
{
    float f;
    *(unsigned int *)&f = bits;
    return f;
}

extern void *func_00336E40(void *);
extern void *func_00336DA8(int, void *);
extern void func_003361E0(void *,void *,void *);
extern void func_00336408(void *,int,int,void *,void *);
extern void func_00336390(void *,void *,int);
extern void func_00336498(void *,unsigned int,unsigned int);
extern void func_003364B0(void *,unsigned int,unsigned int);
extern void func_00336CE0(void *,unsigned int);
extern void func_00336B90(void *,int);
extern void func_00336CC8(void *,int);
extern int func_00335E20(void *);
extern int func_00335E18(void *);
extern void func_003494D0(void *,void *);
extern void func_00349628(void *,int);
extern void func_00349590(void *,void *);
extern void func_003495C0(void *,void *);
extern void func_00349678(void *,float);
extern void func_00349670(void *,int);
extern void func_003495D8(void *,int,float,float,float,float,float);
extern void func_00349610(void *,int,float,float);
extern void func_00349630(void *,int);
extern int func_003495C8(void *,int);
extern char D_001AE5F8[],D_001AE608[],D_001AE610[],D_001AE618[];
extern float D_001B23A4 __attribute__((sda));
extern int D_001B23A0 __attribute__((sda));
extern int D_001A7B90 __attribute__((sda));
extern int D_001A7A00 __attribute__((sda));

/* Sets up one HUD gauge: its texts, sprites and the fade animations that show, hide and pulse them. */
void func_00349D58(char *object,char *data,void *context)
{
    int *zeroBlock;
    void *parent;
    char *label;
    char *anim0,*anim1,*anim2,*anim3,*anim4;
    float scaledSize;
    *(void **)(object+0x13c)=context;
    if(context) {
        zeroBlock=ReturnSecondArgument(16,AllocPoolCell(context));
        *(int **)(object+8)=zeroBlock;
        parent=*(void **)(object+0x13c);
        zeroBlock[1]=0;zeroBlock[2]=0;zeroBlock[3]=0;zeroBlock[0]=0;
        zeroBlock=ReturnSecondArgument(16,AllocPoolCell(parent));
        *(int **)(object+0x1c8)=zeroBlock;
        zeroBlock[1]=0;zeroBlock[2]=0;zeroBlock[3]=0;zeroBlock[0]=0;
    }
    InitDerivedArrays(object+0x10,D_001AE5F8,context);
    InitDerivedArrays((object+0x5c),D_001AE608,context);
    InitDerivedArrays((object+0xa8),D_001AE610,context);
    label=object+0xf4;
    InitDerivedObjectB(label,146,0,D_001AE618,context);
    SetFieldAt40((object+0x5c),data+0x8710,17);
    SetFieldAt40((object+0xa8),data+0x8710,18);
    SetFirstPair(label,0x8049c1ff,0x80001eff);
    SetSecondPair(label,0x50f0c070,0x50f0c070);
    SetTextAlignment(label,0x60442d00);
    SetMeterMaximum(label,100);
    scaledSize=3.0f*D_001B23A4+0.5f;
    SetWidgetPositionY(label,D_001B23A0==1?(int)(scaledSize+1.0f):(int)scaledSize);
    *((int *)GetFieldC((object+0x5c)))=0x60442d00;
    *((int *)GetFieldC((object+0xa8)))=0x55f0c070;
    anim0=object+0x140;
    InitFadeEffect(anim0,context);
    SetEffectField0x84(anim0,2);
    SetFadeField0x2C(anim0,*(void **)(object+0x1c8));
    SetFadeField0x80(anim0,object+0x1cc);
    SetFadeSpeed(anim0,0.005f);
    SetEffectField0x20(anim0,2);
    /* 50.0f: a literal or its own local; a local shared with the colours swaps $f20/$f21. */
    SetFadeParameterRow(anim0,0,0.0f,WriteBits(0x80f0c070),50.0f,0.0f,0.0f);
    SetFadeParameterRow(anim0,1,1.0f,WriteBits(0x80f0f0f0),50.0f,0.0f,0.0f);
    SetAnimationKeyRange(anim0,0,0.0f,0.0f);
    StartFadeDirection(anim0,1);
    anim1=object+0x1d4;
    InitFadeEffect(anim1,context);
    SetEffectField0x84(anim1,3);
    SetFadeParameterRow(anim1,0,0.0f,WriteBits(0x442d00),0.0f,0.0f,0.0f);
    SetFadeParameterRow(anim1,1,0.3f,WriteBits(0x60442d00),0.0f,0.0f,0.0f);
    SetFadeParameterRow(anim1,2,1.0f,WriteBits(0x60442d00),0.0f,0.0f,0.0f);
    SetAnimationKeyRange(anim1,1,0.0f,2.0f);
    SetFadeField0x2C(anim1,((int *)GetFieldC((object+0x5c))));
    SetEffectField0x20(anim1,0);
    SetFadeField0x80(anim1,object+0x1cc);
    StartFadeDirection(anim1,-1);
    SetFadeSpeed(anim1,gIsPalVideo?0.14f:0.11666667461395264f);
    anim2=object+0x25c;
    InitFadeEffect(anim2,context);
    SetEffectField0x84(anim2,3);
    SetFadeParameterRow(anim2,0,0.0f,0.0f,0.0f,0.0f,0.0f);
    SetFadeParameterRow(anim2,1,0.3f,1.0f,1.0f,0.0f,0.0f);
    SetFadeParameterRow(anim2,2,1.0f,1.0f,1.0f,0.0f,0.0f);
    SetFadeField0x2C(anim2,((void *)GetSecondField((object+0x5c))));
    SetEffectField0x20(anim2,0);
    SetFadeField0x80(anim2,object+0x1d0);
    StartFadeDirection(anim2,-1);
    SetFadeSpeed(anim2,gIsPalVideo?0.14f:0.11666667461395264f);
    SwapFadeField0x28(anim2,0);
    anim3=object+0x2e4;
    InitFadeEffect(anim3,context);
    SetEffectField0x84(anim3,3);
    SetFadeParameterRow(anim3,0,0.0f,WriteBits(0xf0c070),0.0f,0.0f,0.0f);
    SetFadeParameterRow(anim3,1,0.3f,WriteBits(0x55f0c070),0.0f,0.0f,0.0f);
    SetFadeParameterRow(anim3,2,1.0f,WriteBits(0x55f0c070),0.0f,0.0f,0.0f);
    SetAnimationKeyRange(anim3,1,0.0f,3.0f);
    SetFadeField0x2C(anim3,((int *)GetFieldC((object+0xa8))));
    SetEffectField0x20(anim3,0);
    SetFadeField0x80(anim3,object+0x1cc);
    StartFadeDirection(anim3,-1);
    SetFadeSpeed(anim3,gIsPalVideo?0.14f:0.11666667461395264f);
    anim4=object+0x36c;
    InitFadeEffect(anim4,context);
    SetEffectField0x84(anim4,3);
    SetFadeParameterRow(anim4,0,0.0f,1.2000000476837158f,1.2000000476837158f,0.0f,0.0f);
    SetFadeParameterRow(anim4,1,0.3f,1.0f,1.0f,0.0f,0.0f);
    SetFadeParameterRow(anim4,2,1.0f,1.0f,1.0f,0.0f,0.0f);
    SetFadeField0x2C(anim4,((void *)GetSecondField((object+0xa8))));
    SetEffectField0x20(anim4,0);
    SetFadeField0x80(anim4,object+0x1d0);
    StartFadeDirection(anim4,-1);
    SetFadeSpeed(anim4,gIsPalVideo?0.14f:0.11666667461395264f);
    *(int *)(object+0x3f4)=0;
    *(int *)(object+0x400)=-1;
    *(int *)(object+0x3f8)=0;
    /* +4 before +0xC: swapped, sw $zero,0xC issues before the D_001A7A00 load, retail's after. */
    *(int *)(object+4)=D_001A7A00;
    *(int *)(object+0xc)=0;
}

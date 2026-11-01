#include "include_asm.h"

#include "common.h"
typedef int EffectQuad __attribute__((mode(TI)));
typedef struct { unsigned char b[256]; } EffectSlot;
extern EffectSlot *D_L04_001B24DC;
extern int D_L04_001B2008 __attribute__((section(".data")));
extern void func_PAL_L04_003FA088(unsigned char *);
extern void *func_L04_00400A18(unsigned char *,void *,float);
extern float func_00283B98(float,float);
extern void func_002AEE70(void *,void *,void *,float,float,float);
extern int func_00282948(void *);
extern void func_PAL_L04_003FA170(void *);
#define EFFECT_WORD(p,o) (*(int *)((p)+(o)))
#define EFFECT_PTR(p,o) (*(unsigned char **)((p)+(o)))
#define EFFECT_FLOAT(p,o) (*(float *)((p)+(o)))
#define EFFECT_FLAGS(p,o) (*(unsigned short *)((p)+(o)))
#define EFFECT_QUAD(p,o) (*(EffectQuad *)((p)+(o)))

/* Updates a three-part rotating effect and cycles its highlighted part. */
void func_PAL_L04_003FA368(unsigned char *m) {
    unsigned char *s=EFFECT_PTR(m,0x68);
    float delta=0;
    int mode;
    if(EFFECT_WORD(s,0x10)!=-1) {
        if ((unsigned)(D_L04_001B24DC[EFFECT_WORD(s,0x10)].b[0x20]-2)>=2) return;
    }
    if(m[0x20]==0) {
        EFFECT_FLOAT(m,0x18)+=0.5f; EFFECT_FLOAT(s,0x54)=0; EFFECT_WORD(s,0)=0;
        EFFECT_FLOAT(s,0x58)=EFFECT_FLOAT(m,0x18); m[0x30]=255; EFFECT_FLAGS(m,0x32)=127;
        EFFECT_FLOAT(m,0x2C)=EFFECT_FLOAT(EFFECT_PTR(m,0x24),0x24);
        EFFECT_WORD(s,4)=0; EFFECT_WORD(s,8)=0; EFFECT_WORD(s,12)=0;
        func_PAL_L04_003FA088(m); m[0x20]=1;
    }
    if(!EFFECT_PTR(s,4))EFFECT_PTR(s,4)=func_L04_00400A18(m,(void *)0xB1C,1.0f);
    if(!EFFECT_PTR(s,8))EFFECT_PTR(s,8)=func_L04_00400A18(m,(void *)0xB1D,1.0f);
    if(!EFFECT_PTR(s,12))EFFECT_PTR(s,12)=func_L04_00400A18(m,(void *)0xB1E,1.0f);
    if(!EFFECT_PTR(s,4)||!EFFECT_PTR(s,8)||!EFFECT_PTR(s,12))return;
    EFFECT_FLOAT(m,0xF8)=func_00283B98(EFFECT_FLOAT(m,0xF8),0.062831864f);
    func_002AEE70(m,s+0x54,&delta,0.01f,0.12566373f,EFFECT_FLOAT(s,0x58));
    mode=D_L04_001B2008;
    EFFECT_QUAD(EFFECT_PTR(s,4),0x10)=EFFECT_QUAD(m,0x10);
    EFFECT_QUAD(EFFECT_PTR(s,8),0x10)=EFFECT_QUAD(m,0x10);
    EFFECT_QUAD(EFFECT_PTR(s,12),0x10)=EFFECT_QUAD(m,0x10);
    EFFECT_QUAD(EFFECT_PTR(s,4),0xF0)=EFFECT_QUAD(m,0xF0);
    EFFECT_QUAD(EFFECT_PTR(s,8),0xF0)=EFFECT_QUAD(m,0xF0);
    EFFECT_QUAD(EFFECT_PTR(s,12),0xF0)=EFFECT_QUAD(m,0xF0);
    switch((mode%50)/12) {
    case 0: EFFECT_WORD(EFFECT_PTR(s,4),0x78)=0x804040FF;EFFECT_WORD(EFFECT_PTR(s,8),0x78)=0x80000040;EFFECT_WORD(EFFECT_PTR(s,12),0x78)=0x80000040;break;
    case 1: EFFECT_WORD(EFFECT_PTR(s,4),0x78)=0x80000040;EFFECT_WORD(EFFECT_PTR(s,8),0x78)=0x804040FF;EFFECT_WORD(EFFECT_PTR(s,12),0x78)=0x80000040;break;
    case 2: EFFECT_WORD(EFFECT_PTR(s,4),0x78)=0x80000040;EFFECT_WORD(EFFECT_PTR(s,8),0x78)=0x80000040;EFFECT_WORD(EFFECT_PTR(s,12),0x78)=0x804040FF;break;
    case 3: EFFECT_WORD(EFFECT_PTR(s,4),0x78)=0x80000040;EFFECT_WORD(EFFECT_PTR(s,8),0x78)=0x80000040;EFFECT_WORD(EFFECT_PTR(s,12),0x78)=0x80000040;break;
    }
    if(func_00282948(s)) {
        EFFECT_FLAGS(m,0x34)&=0xFFBE; EFFECT_FLAGS(EFFECT_PTR(s,4),0x34)&=0xFFBE;
        EFFECT_FLAGS(EFFECT_PTR(s,8),0x34)&=0xFFBE; EFFECT_FLAGS(EFFECT_PTR(s,12),0x34)&=0xFFBE;
        func_PAL_L04_003FA170(m);
    }else{
        EFFECT_FLAGS(m,0x34)|=0x41; EFFECT_FLAGS(EFFECT_PTR(s,4),0x34)|=0x41;
        EFFECT_FLAGS(EFFECT_PTR(s,8),0x34)|=0x41; EFFECT_FLAGS(EFFECT_PTR(s,12),0x34)|=0x41;
    }
}

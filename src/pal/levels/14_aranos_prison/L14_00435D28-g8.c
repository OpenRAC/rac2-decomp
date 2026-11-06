#include "common.h"
extern char D_00188660[];
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; void *owner; } PrisonSoundAnchor;
extern int prisonStartSound(int, int, void *) __asm__("func_002E5CF8");
extern void func_002E59F8(int);
extern void func_002A7750(char *,int,int);
extern void func_L00_002E6EF8(void *,void *);
extern float func_L14_00430898(float);
extern void func_PAL_L14_004364B0(char *);
extern float func_002A7878(float, float);
extern int func_002B38B8(void *);
extern int func_002B3868(void *);
extern float func_00283198(float);
extern int D_L14_001B20C8;
extern int D_L14_001B20C8_1 __attribute__((sda));
extern float D_L14_00260270[32], D_L14_002602F0[32];
typedef struct {
    float w00;
    int w04;
    float w08;
    unsigned int w0c;
    int w10;
    float w14;
    float w18;
    int w1c;
    float w20;
    float w24;
    float w28;
    float w2c;
    unsigned int w30;
    unsigned int w34;
    unsigned int w38;
    unsigned int w3c;
    unsigned int w40;
    unsigned int w44;
    unsigned int w48;
    unsigned int w4c;
    int range[2];
    int w58;
    int w5c;
    float w60;
    float w64;
    float w68;
    float w6c;
    float w70;
    float w74;
    float w78;
    float w7c;
    float currentScale;
    float baseScale;
    float pulseScale;
    int w8c;
    int pulseFrames;
    int w94;
    int w98;
    float w9c;
    float wa0;
    float wa4;
    int wa8;
    float wac;
    int wb0;
    float wb4;
    int wb8;
    float wbc;
    unsigned int wc0;
    int sound;
} PrisonEffectState;
/* func_PAL_L14_00435D28, the PAL copy of func_L14_00430410: the same C, with pulseFrames rescaled
 * to 50 Hz on init and func_PAL_L14_004364B0 as the draw callback. */
/* Initializes the pulse effect, maintains its sound and draw callback, and fades its scale. */
void func_PAL_L14_00435D28(char *self)
{
    PrisonEffectState *s = *(PrisonEffectState **)(self+0x68);
    int i;
    switch ((unsigned char)self[0x20]) {
    case 0:
        s->pulseFrames=((s32)(s->pulseFrames) * 5 + 2) / 6;
        s->w00=0;
        s->w04=69; s->w08=1.2f; s->w0c=0x50000080;
        s->w20=2.0f; s->w24=4.2f; s->w28=3.1f; s->w2c=3.7f;
        s->w30=0x80000080; s->w34=0x80000080;
        s->w38=0x80200060; s->w3c=0x80808080; s->w40=0x80200060;
        s->w44=0x80300050; s->w48=0x80202880; s->w4c=0x80606020;
        for (i=1;i>=0;i--) s->range[i]=i*50;
        s->w10=300;
        s->w60=-0.125f; s->w64=0.133f;
        s->w68=0.241f; s->w6c=-0.221f;
        s->w18=1.2f; s->w70=0.6f;
        s->w74=0.5f; s->w78=0.4f;
        s->w7c=0.7f;
        s->w1c=54;
        s->w94=0x28280080; s->w98=0x0a800000;
        s->wa0=0.9f; s->wa4=0.1f;
        s->wa8=20; s->wac=s->w14=0.8f;
        s->wb0=70; s->wb4=s->w9c=2.0f;
        for(i=0;i<32;i++) {
            D_L14_00260270[i]=func_002A7878(-3.1415927f,3.1415927f);
            D_L14_002602F0[i]=(float)i*0.03125f;
        }
        s->wb8=71; s->wbc=1.0f;
        s->wc0=0x80800000;
        self[0x31]=0; *(unsigned short *)(self+0x34)|=1;
        s->sound=-1;
        func_002A7750(self,1,-1);
        break;
    case 1:
        if (((PrisonSoundAnchor *)(D_00188660+s->sound*112))->owner!=self ||
            !((PrisonSoundAnchor *)(D_00188660+s->sound*112))->active)
            s->sound=prisonStartSound(0,4,self);
        func_L00_002E6EF8(func_PAL_L14_004364B0,self);
        if(func_002B38B8(self)) {
            if(D_L14_001B20C8_1<50) s->baseScale=0;
            func_002A7750(self,2,-1);
        }
        break;
    case 2: {
        int sound=s->sound;
        if(sound!=-1 && ((PrisonSoundAnchor *)(D_00188660+sound*112))->owner==self &&
            ((PrisonSoundAnchor *)(D_00188660+sound*112))->active) func_002E59F8(sound);
        s->sound=-1;
        if(func_002B3868(self)) *(int *)(self+0x98)=0;
        if(s->baseScale>0.5f) {
            func_L00_002E6EF8(func_PAL_L14_004364B0,self);
            s->baseScale-=0.05f;
        }
        break;
    }
    }
    s->currentScale=s->baseScale+s->pulseScale*
        func_00283198(func_L14_00430898((float)D_L14_001B20C8*6.2831855f/(float)s->pulseFrames));
}


#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad80[0x80];
    float position[4];
    float rotation[4];
    char pad1fc[0x15c];
    short flag;
    char pad64c[0x44e];
    float heading;
    float pitch;
    char pad6a0[0x4c];
    float heading2;
    char pad6a8[0x4];
    char * target;
    char pad730[0x84];
    float matrix[12];
    float direction[4];
    float angles[4];
    char padc2c[0x4ac];
    int condition;
    char pade98[0x268];
    char * slots[2];
    char * overlay;
    int pending;
    char pad11a0[0x2f8];
    int timer;
    char pad2290[0x10ec];
    int resource;
    char pad229c[0x8];
    int mode;
    char pad22b8[0x18];
    unsigned char enabled;
    char pad22ba[0x1];
    unsigned char active;
    unsigned char dual;
    char pad22c3[0x7];
    unsigned char transformed;
    char pad2490[0x1cc];
    char * object;
    char pad24b0[0x1c];
    int animation;
    int savedMode;
    char pad24cc[0x14];
    int mode2;
    char pad24ec[0x1c];
    short flag2;
    char pad24f4[0x6];
    short selector;
} AnimationState;
extern AnimationState D_00189E20_26;
extern int func_L00_002AEAC0(int);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
extern void *func_002AB1F0(void *);
extern int func_L00_002ADEA0(int);
extern char *ref_L00_002AEB18_0(int,int);
extern void ref_L00_002AEB18_1(int,void *);
extern void ref_L00_002AEB18_2(int,void *,int,int,int,int);
extern void ref_L00_002AEB18_3(int,void *);
extern float func_002AA2E8(float *,float,float);
extern char D_L00_001B5000[];

void func_PAL_L00_002AEA00(void)
{
    int enabled=0,id=0,mode;
    float opacity=1.0f;
    unsigned char *data;
    char *overlay;
    if(D_00189E20_26.object) {
        data=func_002AB1F0(D_00189E20_26.object);
        enabled=1;
        id=0x72;
        if(data[0x2c]) {
            id=func_L00_002AEAC0((unsigned char)data[0x2c]);
            if(D_00189E20_26.mode==1) opacity=0.7f;
        }
    }
    if(D_00189E20_26.flag) {
        enabled=1;
        id=func_L00_002AEAC0(D_00189E20_26.selector);
    }
    if(D_00189E20_26.mode2==1) {
        int anim=((unsigned char *)D_00189E20_26.resource)[0x43];
        enabled=1;
        if((anim==0x51 || anim==0x7b || anim==0x57) && !D_00189E20_26.condition) enabled=0;
        opacity=0.8f; id=0x74;
    }
    mode=func_L00_002ADEA0(0);
    if((mode==30 || mode==28 || mode==29) && D_00189E20_26.enabled) {
        enabled=1; opacity=0.8f; id=0x6f;
    }
    if(enabled) {
        if(!D_00189E20_26.overlay) {
            D_00189E20_26.overlay=ref_L00_002AEB18_0(D_00189E20_26.resource,24);
            I(D_00189E20_26.overlay,8)=0;
        }
    } else {
        if(!D_00189E20_26.overlay) return;
        if(func_002AA2E8((float *)(D_00189E20_26.overlay+8),0.0f,0.060000002f)==0.0f)
            ref_L00_002AEB18_1(D_00189E20_26.resource,&D_00189E20_26.overlay);
    }
    overlay=D_00189E20_26.overlay;
    if(!overlay) return;
    if(!enabled) return;
    {
        func_002AA2E8((float *)(overlay+8),opacity,0.060000002f);
        P(D_00189E20_26.overlay,0x38)=D_L00_001B5000;
        P(D_00189E20_26.overlay,0x3c)=D_L00_001B5000+0x600;
        if((unsigned char)D_00189E20_26.overlay[0x23]!=id)
            ref_L00_002AEB18_2(D_00189E20_26.resource,D_00189E20_26.overlay,id,0,7,1);
        else ref_L00_002AEB18_3(D_00189E20_26.resource,D_00189E20_26.overlay);
    }
}

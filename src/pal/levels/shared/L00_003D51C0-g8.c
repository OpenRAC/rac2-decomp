#include "include_asm.h"

#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define S(p,o) (*(s16 *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern u8 D_00139568[];
extern int D_00139688[];
typedef struct {
    char pad_00[0x38]; s16 multiple_sound; s16 single_sound;
    char pad_3C[2]; s16 moby_class;
    char pad_40[0x4E]; u16 capacity;
    char pad_90[0x50];
} PickupResource;
extern PickupResource D_L00_00262570[];
typedef struct {
    char pad_00[0x20]; float axis[4];
    char pad_30[0x10]; float matrix[16];
    float position[4]; char pad_90[0x50]; float target[4];
    char pad_F0[0x60]; float motion[4];
    char pad_160[0x2162]; u8 override;
    char pad_22C3[0x1E1]; float range; float height;
    char pad_24AC[0x20]; int enabled;
} PickupPlayer;
extern char D_00189E20[];
#define PLAYER ((PickupPlayer *)D_00189E20)
extern int D_L00_001A8FF0[] __attribute__((sda));
extern int D_L00_001B19C8[] __attribute__((sda));
extern int D_L00_001B2ADC[] MACRO_ADDR;
extern void *D_0018C0B0 NOT_SDA;
extern void func_00282C90(void *);
extern void func_PAL_00273A10(void *);
extern float func_00282E48(void *,void *);
extern int func_00282948(void *);
extern float func_00282C48(float);
extern float func_00282E80(void *,void *);
extern float func_002B0360(void *);
extern int func_L00_002D3FB8(int,int);
extern void func_PAL_L00_003282B0(int,int,int);
extern void func_002A7750(void *,int,int);
extern void func_00282C88(void *);
extern int func_00282C30(int);
extern int func_002E5CF8(int,int,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00283098(void *,void *,void *);
extern void func_002AA2E8(void *,float,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_00282DF0(void *);
extern void func_0029F338(void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_002ACE78(void *,void *,float);
extern void func_00283958(void *,void *);
extern void func_00283738(void *,void *,void *);
extern int func_00282ED8(void *,void *);

void func_PAL_L00_003D51C0(char *m)
{
    char *d=*(char **)(m+0x68);
    PickupResource *e;
    int j,i,yes,changed,old,delta,sound;
    float speed,time,target_speed;
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float v[4] __attribute__((aligned(16)));
    float v2[4] __attribute__((aligned(16)));
    float v3[4] __attribute__((aligned(16)));
    float v4[4] __attribute__((aligned(16)));
    float up[4] __attribute__((aligned(16)));
    char matrix[48] __attribute__((aligned(16)));
    switch(B(m,0x20)) {
    case 0:
        B(m,0x20)=1;
        for(j=0;j<56;j++) {
            e=&D_L00_00262570[D_00139568[j]];
            if(e->moby_class==S(m,0xaa))I(d,0x68)=j;
        }
        break;
    case 1:
        if(B(d,0x5c)==3 && (D_L00_001B19C8[0]&15)==(((int)m>>8)&15)) {
            qzero(d);func_00282C90(d+0x10);B(d,0x5c)=0;
        }
        qcopy(a,d);
        func_PAL_00273A10(m);
        changed=0;
        if(func_00282E48(a,d)>F(d,0x48)*2.0f)changed=1;
        yes=1;
        if(B(d,0x5c)||changed) {
            if(func_00282948(d+0x7c)) {
                if(func_00282C48(F(m,0x18)-PLAYER->position[2])>PLAYER->height)yes=0;
                else if(func_00282E80(m+0x10,PLAYER->position)>PLAYER->range)yes=0;
            }
        } else {
            yes=0;
            if(func_00282C48(F(m,0x18)-PLAYER->position[2])<PLAYER->height &&
               func_00282E80(m+0x10,PLAYER->position)<PLAYER->range)I(d,0x7c)=3;
        }
        if(D_00139688[I(d,0x68)] >=
           ((PickupResource *)(D_00139568[I(d,0x68)] * 224 + (unsigned int)D_L00_00262570))->capacity)yes=0;
        if(D_L00_001A8FF0[0]) {
            if(func_002B0360(m+0x10)<F(d,0x78)-2.0f)goto force_pickup;
        } else if(F(m,0x18)<F(d,0x78)-2.0f)goto force_pickup;
        if(!PLAYER->override)goto check_enabled;
force_pickup:
        yes=1;
check_enabled:
        if(!PLAYER->enabled)yes=0;
        if(yes) {
            i=I(d,0x68);old=D_00139688[i];
            func_L00_002D3FB8(i,I(d,0x60));
            if(old<D_00139688[i]) {
                delta=D_00139688[i]-old;
                if(delta==1) {
                    e=&D_L00_00262570[D_00139568[i]];
                    sound=e->single_sound;
                } else {
                    e=&D_L00_00262570[D_00139568[i]];
                    sound=e->multiple_sound;
                }
                func_PAL_L00_003282B0(sound,delta,-1);
            }
            func_002A7750(m,2,-1);
            F(d,0x74)=0.16000001f;
            func_00282C88(d);
            if(func_00282C30(D_L00_001B19C8[0]-D_L00_001B2ADC[0])>8) {
                func_002E5CF8(0,0,m);D_L00_001B2ADC[0]=D_L00_001B19C8[0];
            }
        }
        break;
    case 2:
        func_00282CF0(a,m+0x10,PLAYER->position);
        func_00283098(a,a,PLAYER->matrix);
        target_speed=8.0f;
        if(a[2]>0.0f)target_speed=0.0f;
        func_002AA2E8(d+0x74,target_speed,0.0096f);
        func_00282F20(b,PLAYER->axis,F(d,0x74));
        func_00282CC0(m+0x10,m+0x10,b);
        func_00282CC0(m+0x10,m+0x10,PLAYER->motion);
        speed=func_00282DF0(d);
        func_002AA2E8(&speed,1.2800001f,0.0096f);
        func_00282CF0(c,PLAYER->target,m+0x10);
        time=func_00282DF0(c)/speed;
        if(time<25.0f)func_002AA2E8(m+0x2c,0.0f,F(*(char **)(m+0x24),0x24)*0.04f);
        if(F(m,0x2c)==0.0f) {func_0029F338(m);return;}
        if(time<=1.0f) {func_0029F338(m);return;}
        func_00282F20(d,c,speed);
        func_00282CC0(m+0x10,m+0x10,d);
        func_00282DD8(v,PLAYER->axis,d);
        func_002ACE78(v,v,0.10471977f);
        *(Quadword *)up=0;up[2]=0.3f;
        func_00283098(v2,up,m+0xc0);
        func_00283958(v,matrix);
        func_00283738(m+0xc0,matrix,m+0xc0);
        func_00283098(v3,up,m+0xc0);
        func_00282CF0(v4,v3,v2);
        func_00282CF0(m+0x10,m+0x10,v4);
        break;
    }
    if(B(m,0x20)==1 && func_00282ED8(m,D_0018C0B0)) {
        B(m,0x23)=B(m,0x23)>36?B(m,0x23)-4:36;
    } else {
        B(m,0x23)=B(m,0x23)<124?B(m,0x23)+4:128;
    }
    if(*(s8 *)(m+0x23)>=0)*(u16 *)(m+0x34)|=0x2000;
    else *(u16 *)(m+0x34)&=0xdfff;
}

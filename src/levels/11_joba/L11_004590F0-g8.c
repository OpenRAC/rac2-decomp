#include "common.h"
extern void func_002AFFD8(void *,void *,int);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern int func_002761F8(void *,void *,int,void *,int);
extern void func_L11_00459640(void *,int,int);
extern void func_002A8BD0(void *,void *,int,float);
extern int func_00277F48(void *,float,int,void *,void *);
extern int func_00282948(void *);
extern float func_002A7878(float,float);
extern int func_002A77E0(int);
extern void *func_002C2210(void *,int,float,float,int,int,int,void *,float,int);
extern float func_00283CE0(int);
extern int func_001163B0(void);
extern void func_0029F338(void *);
extern void func_L11_00459D48(void *);
typedef struct { float velocity[4]; char *source; int flags; u8 mode, enabled; u16 type; float amount; int style; char pad[12]; } Damage;
typedef struct { char pad[24]; char *owner; int count; float point[4]; } Collision;
extern Collision D_L11_001C0D00;
extern float D_L11_001B1FF0 __attribute__((sda));
extern float D_L11_001B1FF4 __attribute__((sda));
extern float D_L11_001B1FF8 __attribute__((sda));
extern int D_L11_001B2000 __attribute__((sda));
extern int D_L11_001B2004 __attribute__((sda));
void func_L11_004590F0(char *p) {
    float old[4], ground[4], next[4];
    Damage hit, damage;
    char *q=*(char **)(p+0x68), *other;
    int same;
    qcopy(old,p+0x10);
    func_002AFFD8(p+0x10,ground,1);
    qcopy(next,p+0x10);
    if (*(u8 *)(p+0x20)==0) {
        func_00282CC0(p+0x10,p+0x10,q+0x40);
        hit.source=p;
        hit.flags=0x10001;
        hit.amount=*(float *)(q+0x64);
        hit.style=1;
        qcopy(&hit,q+0x40);
        func_00282F20(&hit,&hit,1.0f);
        hit.velocity[3]=5627.9248046875f;
        hit.mode=1;hit.enabled=1;
        hit.type=*(u16 *)(p+0xAA);
        if(func_002761F8(next,p+0x10,0,p,0)) {
            other=D_L11_001C0D00.owner;
            same=other && *(char **)(q+0x50) && *(s16 *)(other+0xAA)==*(s16 *)(*(char **)(q+0x50)+0xAA);
            if(!same) {
                if(!D_L11_001C0D00.owner) func_L11_00459640(D_L11_001C0D00.point,1,0);
                else if(*(int *)(D_L11_001C0D00.owner+0x98)) func_L11_00459640(D_L11_001C0D00.point,1,1);
                func_002A8BD0(&damage,p,0x810001,*(float *)(q+0x64));
                damage.mode=2;damage.enabled=1;
                damage.type=*(u16 *)(*(char **)(q+0x50)+0xAA);
                func_00277F48(D_L11_001C0D00.point,0.2f,16,p,&damage);
                goto destroy;
            }
        }
    }
    if(func_00282948(q+0x58)) {
        char *position=p+0x10;
        float scale;
        int sign,i;
        scale=func_002A7878(D_L11_001B1FF4,D_L11_001B1FF8);
        sign=func_002A77E0(2);if(!sign) sign--;
        for(i=4;i>=0;i--) {
            hit.velocity[2]=func_002A7878(-1,1);hit.velocity[1]=func_002A7878(-1,1);hit.velocity[0]=func_002A7878(-1,1);
            func_00282F20(&hit,&hit,0.025f);
            hit.velocity[2]=func_002A7878(0,0.1f);
            func_002C2210(position,60,scale*0.35f,scale,D_L11_001B2000,0,sign,&hit,D_L11_001B1FF0,0);
            func_002C2210(position,60,scale*0.245f,scale*0.7f,D_L11_001B2004,1,sign,&hit,D_L11_001B1FF0,0);
            sign=-sign;
        }
        goto destroy;
    } else {
        float scale;
        int sign;
        if(*(int *)(q+0x58)<16) {
            float ratio;
            ratio=func_00283CE0(*(int *)(q+0x58));ratio=ratio/func_00283CE0(15);
            *(float *)(q+0x60)=ratio;
            if(func_001163B0()%3==0) {
                sign=func_002A77E0(2);if(!sign)sign--;
                scale=func_002A7878(D_L11_001B1FF4,D_L11_001B1FF8);
                hit.velocity[2]=func_002A7878(-1,1);hit.velocity[1]=func_002A7878(-1,1);hit.velocity[0]=func_002A7878(-1,1);
                func_00282F20(&hit,&hit,0.025f);
                func_002C2210(p+0x10,60,scale*0.05f,scale,D_L11_001B2000,0,sign,&hit,D_L11_001B1FF0,0);
                func_002C2210(p+0x10,60,scale*0.0035f,scale*0.035f,D_L11_001B2004,1,sign,&hit,D_L11_001B1FF0,0);
            }
        }
        if(*(float *)(p+0x10)<2 || *(float *)(p+0x10)>1021 || *(float *)(p+0x14)<2 || *(float *)(p+0x14)>1021 || *(float *)(p+0x18)<2 || *(float *)(p+0x18)>1021) { destroy: func_0029F338(p); }
        else func_L11_00459D48(p);
    }
}

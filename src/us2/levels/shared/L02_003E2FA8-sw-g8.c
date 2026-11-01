#include "include_asm.h"

#include "common.h"
typedef struct { char pad[0x464]; unsigned char flags[0]; } L02E1A40Progress;
extern L02E1A40Progress D_L02_0021F4F0;
extern unsigned char D_0019B4A8[];
extern int D_001A79F0[] __attribute__((sda));
extern int currentLevel_gp SDATA(D_001A79F0);
typedef struct L02E1A40Object L02E1A40Object;
extern L02E1A40Object *D_L02_001B359C[] __attribute__((sda));
extern L02E1A40Object *entityPool_gp SDATA(D_L02_001B359C);
extern char *D_0018A15C[];
typedef struct {
    char pad0[0x24]; int message; int timer;
    char pad1[0x3c]; int disabled; short f6c; char pad2[4]; short f72;
} L02E1A40Hud;
extern L02E1A40Hud D_001A63A8;
extern float D_L02_001B0760 SDATA(D_L02_001B0760);
extern float D_L02_001B0764 SDATA(D_L02_001B0764);
extern float D_L02_001B0768 SDATA(D_L02_001B0768);
extern float D_L02_001B0768_abs[] __asm__("D_L02_001B0768") __attribute__((sda));
extern int D_L02_001B0770 SDATA(D_L02_001B0770);
extern int D_L02_001B0770_abs[] __asm__("D_L02_001B0770") __attribute__((sda));
extern int D_L02_001B0778 SDATA(D_L02_001B0778);
extern int D_L02_001B0780 SDATA(D_L02_001B0780);
extern int D_L02_001B0780_abs[] __asm__("D_L02_001B0780") __attribute__((sda));
extern int D_L02_001B0788 SDATA(D_L02_001B0788);
extern int D_L02_001B0788_abs[] __asm__("D_L02_001B0788") __attribute__((sda));
extern int D_L02_001B30C8[] __attribute__((sda));
extern void func_L00_003294F0(void *,int);
extern void func_0029F338(void *);
extern void func_002A7750(void *,int,int);
extern float func_00283B98(float,float);
extern void func_L00_002E6CF0(void *,void *);
extern void func_L02_003E2150(void *);
extern float func_002AA2E8(void *,float,float);
extern int func_002A77E0(int);
extern float func_002A7940(void);
extern float func_00283180(float),func_00283198(float);
extern void func_00282CC0(void *,void *,void *);
extern float func_002A7878(float,float);
extern int func_00283D38(int,int,float);
extern int func_002A7820(int,int);
extern void func_00282C88(void *);
extern float func_00283CE0(int);
extern void func_002C3150(void *,void *,int,float,int,int,int);
extern void func_L00_002D40A0(void *,int,float);
extern float func_00282E80(void *,void *),func_00282C48(float);
extern int func_002B3868(void *);
extern int func_002E5CF8(int,int,char *);
extern void func_US2_002B1880(int,int);
extern void func_002B6D28(void);
typedef struct {
    int other, first, second; char pad0[8]; int auxiliary;
    float angle, angle2, fade; char pad1[4]; int color0, color1, alpha;
    char pad2[4]; int f38, f3c, count, message0, message1;
} L02E1A40Data;
struct L02E1A40Object {
    char pad0[0x10]; float position[4]; unsigned char state;
    char pad21[0x10]; unsigned char active; char pad32[0x36]; L02E1A40Data *data;
    char pad6c[0x2a]; unsigned short ticks; char pad98[0x1a]; unsigned short index;
    char padb4[0x44]; float radius; char padfc[4];
};
typedef struct { char pad[0x5c0]; L02E1A40Object *target; } L02E1A40Hero;
extern L02E1A40Hero D_00189E20;
#define I(p,o) (*(int *)((char *)(p)+(o)))

void func_US2_L02_003E2FA8(L02E1A40Object *obj)
{
    float pos[4], vel[4];
    L02E1A40Data *d=obj->data;
    L02E1A40Object *other;
    unsigned short index;
    unsigned short completedIndex;
    int color, duration;
    int initialPacked, message0, message1;
    unsigned int ticks, savedByte;
    unsigned int frame;
    float angle, size, speed;
    unsigned char *save;
    switch(obj->state) {
    case 0:
        d->f38=0; d->f3c=0; d->count=0;
        index=obj->index;
        if(D_L02_0021F4F0.flags[(short)index] ||
           ((initialPacked=D_0019B4A8[((short)index>>1)+(D_001A79F0[0]<<10)]),
            (index&1) ? ((initialPacked>>4)&7) : (initialPacked&7))) {
            func_L00_003294F0((D_L02_001B359C[0]+d->first),1);
            func_L00_003294F0((D_L02_001B359C[0]+d->second),1);
            if(d->auxiliary!=-1) func_0029F338(entityPool_gp+d->auxiliary);
            func_002A7750(obj,5,-1);
        } else func_002A7750(obj,1,-1);
        break;
    case 1:
        d->angle=func_00283B98(d->angle,D_L02_001B0760*0.0002908882452175021f);
        func_L00_002E6CF0(func_L02_003E2150,obj);
        if(d->fade!=0.0f) func_002AA2E8(&d->fade,0.0f,0.033333335f);
        if(obj->active && !func_002A77E0(5)) {
            angle=func_002A7940();
            pos[0]=func_00283180(angle)*1.15f;
            pos[1]=func_00283198(angle)*1.15f;
            pos[2]=0;
            func_00282CC0(pos,pos,obj->position);
            pos[2]+=0.1f;
            size=func_002A7878(D_L02_001B0768,D_L02_001B0768_abs[1]);
            color=func_00283D38(D_L02_001B0770,D_L02_001B0770_abs[1],func_002A7878(0,1));
            speed=func_002A7878(1,2);
            duration=func_002A7820(60,180);
            func_00282C88(vel);
            vel[2]=speed/func_00283CE0(duration);
            func_002C3150(pos,vel,color,size,(unsigned char)duration,(unsigned char)func_002A77E0(255),0);
        }
        if(D_0018A15C[0]==(char *)obj) {
            func_002A7750(obj,2,-1);
            if(!D_L02_001B0778) {
                D_L02_001B0778=1;
                func_L00_002D40A0(obj->position,1,obj->radius);
            }
        } else {
            other=(D_L02_001B359C[0]+d->other);
            if(func_00282E80(obj->position,other->position)<1.5f && func_00282C48(obj->position[2]-other->position[2])<0.5f)
                func_002A7750(obj,3,-1);
        }
        break;
    case 2:
        if(func_002B3868(obj)) {
            func_002E5CF8(1,0,(char *)obj);
            d->color0=D_L02_001B0780;
            d->color1=D_L02_001B0780_abs[1];
            d->fade=0;d->alpha=0;
            func_US2_002B1880(0x131D,180);
            if(!D_001A63A8.disabled && D_001A63A8.message==-1) {
                message0=d->message0;
                D_001A63A8.timer=0;
                D_001A63A8.message=(message0&0x3fff)+2000;
            }
        }
        if(D_0018A15C[0]!=(char *)obj) func_002A7750(obj,1,-1);
        d->angle=func_00283B98(d->angle,D_L02_001B0760*0.0002908882452175021f);
        angle=func_00283B98(d->angle2,D_L02_001B0764*0.0002908882452175021f);
        frame=D_L02_001B30C8[0];
        d->angle2=angle;
        if((frame&1) && d->alpha<255) d->alpha++;
        func_L00_002E6CF0(func_L02_003E2150,obj);
        func_002AA2E8(&d->fade,1,0.033333335f);
        break;
    case 3:
        if(func_002B3868(obj)) {
            I(d,0x40)++;
            d->color0=D_L02_001B0788;
            d->color1=D_L02_001B0788_abs[1];
            d->fade=0;d->alpha=0;
            func_US2_002B1880(0x131E,180);
            message1=d->message1;
            D_001A63A8.timer=0;
            D_001A63A8.message=(message1&0x3fff)+2000;
        }
        ticks = obj->ticks;
        obj->ticks = ticks + 1;
        if(ticks>180) func_002A7750(obj,4,-1);
        else if(obj->ticks>60) {
{ L02E1A40Object *candidate; int i=d->other; candidate=D_L02_001B359C[0]+i; if(D_00189E20.target==candidate) D_00189E20.target=0; }
            func_L00_003294F0((D_L02_001B359C[0]+d->first),1);
            func_L00_003294F0((D_L02_001B359C[0]+d->second),1);
        }
        d->angle=func_00283B98(d->angle,D_L02_001B0760*0.0002908882452175021f);
        angle=func_00283B98(d->angle2,D_L02_001B0764*0.0002908882452175021f);
        frame=D_L02_001B30C8[0];
        d->angle2=angle;
        if((frame&1) && d->alpha<255) d->alpha++;
        func_L00_002E6CF0(func_L02_003E2150,obj);
        func_002AA2E8(&d->fade,1,0.033333335f);
        break;
    case 4:
        func_L00_002E6CF0(func_L02_003E2150,obj);
        func_002AA2E8(&d->fade,0,0.033333335f);
        if(d->fade<=0) {
            completedIndex=obj->index;
            if(completedIndex&1) {
                save=&D_0019B4A8[((short)completedIndex>>1)+(currentLevel_gp<<10)];
                savedByte=*save;
                if(((savedByte>>4)&7)!=7) *save=savedByte+16;
            } else {
                save=&D_0019B4A8[((short)completedIndex>>1)+(currentLevel_gp<<10)];
                savedByte=*save;
                if((savedByte&7)!=7) *save=savedByte+1;
            }
            func_002A7750(obj,5,-1);
        }
        break;
    }
    if(D_001A63A8.f72==3 && D_001A63A8.f6c<6000) func_002B6D28();
}

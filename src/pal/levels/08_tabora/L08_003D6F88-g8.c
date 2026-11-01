#include "include_asm.h"

#include "common.h"
#define F(p,T,o) (*(T *)((char *)(p)+(o)))
extern char D_L08_001B9B00[], D_0019B4A8[];
extern char D_L08_001A8F20[] __attribute__((sda));
extern struct { char pad[0x464]; u8 flags[0]; } D_L08_0021EAF0;
extern int D_001A79F0;
extern int D_L08_001A8F00 __attribute__((sda));
extern float D_L08_001B02F0 __attribute__((sda)), D_L08_001B02F4 __attribute__((sda)), D_L08_001B02F8 __attribute__((sda));
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *), func_0029F338(void *);
extern int func_002ACD38(void *),func_002F5D10(void);
extern float func_002A89A8(void *,int,float),func_002A7878(float,float),func_002A7940(void),func_00283CE0(int);
extern int func_00283CF0(float),func_002A7820(int,int);
extern void func_002A7750(void *,int,int),func_PAL_L08_003D0280(void *);
extern void *func_002A9640(void *,int,int);
extern float func_PAL_002AA108(void *,void *);
extern void func_PAL_002AC290(void *,void *),func_PAL_002AC3C0(void *,void *),func_0029FCC0(void *,int,void *),func_002A7398(void *,int,int);
extern void func_PAL_002AC718(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_L03_003268C0(void *,int,int,int,int,int,int,void *);
extern int func_002E5CF8(int,int,void *);
extern void *func_0029EFD0(int);
extern void func_002A0F48(void *),func_002AB650(void *),func_002AF000(void *,float,float,float);
extern void func_00282CC0(void *,void *,void *),func_PAL_L08_00414850(void *,void *,void *,float,float);

/* Applies damage, updates hit effects, and spawns debris when health reaches zero. */
void func_PAL_L08_003D6F88(char *o) {
    char *p=F(o,char *,0x68), *hit, *spawn, *health, *effect;
    float impact, z, angle, speed, t;
    int n, bits, sound;
    float at[4] __attribute__((aligned(16)));
    float target[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    if(F(o,u8,0x31) && func_00282E48(o+0x10,D_L08_001B9B00)<48.0f) {
        func_002A93B0(o); F(o,u8,0x6F)=45;
    }
    if(F(o,u8,0xB0)!=255) {
        unsigned short index=F(o,u16,0xB2);
        if(D_L08_0021EAF0.flags[(short)index]) {func_0029F338(o);return;}
        bits=F(D_0019B4A8,u8,((short)index>>1)+(D_001A79F0<<10));
        if((index&1) ? ((bits>>4)&7) : (bits&7)) {func_0029F338(o);return;}
    }
    if(!func_002ACD38(o+0x10)) return;
    if(D_L08_001A8F00==2) {F(o,u8,0x31)=0;F(o,u16,0x34)|=1;}
    else {F(o,u8,0x31)=1;F(o,u16,0x34)&=0xFFFE;}
    if(func_002F5D10())return;
    if(!F(o,u8,0x20)) {
        z=func_002A89A8(o+0x10,0,0.5f);
        z-=func_002A7878(0.2f,0.7f);
        F(o,float,0x18)=z;
        func_002A7750(o,1,-1);
    }
    if(!p)return;
    if(F(o,u8,0x31))func_PAL_L08_003D0280(o);
    health=p+0x20;effect=p+0x50;
    hit=func_002A9640(o,0x230000,0);
    impact=func_PAL_002AA108(o,hit);
    if(impact>0) {
        F(health,float,0)-=impact;
        F(effect,u8,7)=255;F(effect,u8,8)=255;F(effect,u8,9)=255;
        func_PAL_002AC290(o,effect);
        func_0029FCC0(o,0,at);
        func_002A7398(o,3,func_00283CF0(func_00283CE0(F(p,s16,0x24))-F(health,float,0))<16 ? func_00283CF0(func_00283CE0(F(p,s16,0x24))-F(health,float,0)) : 15);
        F(o,int,0x48)=0;
        z=F(o,float,0x48);
        func_PAL_002AC718(o,D_L08_001A8F20,at,z,z,4,2,5,2,1,9,1,-1,z,0,0,-1,0,0x810001);
        func_L03_003268C0(o,-1,0,0x96D,1,3,0,D_L08_001A8F20);
        sound=func_002A7820(0,2);
        if(F(health,float,0)>z)func_002E5CF8(sound,0,o);
    }
    F(o,u8,0xA8)=255;
    func_PAL_002AC3C0(o,effect);
    if(F(health,float,0)<=0) {
        qzero(at);at[2]=0.20000002f;
        if(hit)qcopy(target,hit);
        else {qcopy(target,o+0x10);target[2]+=2;}
        spawn=func_0029EFD0(0x8C4);
        if(spawn) {
            F(spawn,u8,0x23)=80;F(spawn,u16,0x34)|=0x800;
            F(spawn,float,0x2C)=F(F(spawn,char *,0x24),float,0x24)*0.65f;
            F(spawn,u8,0x30)=255;F(spawn,u16,0x32)=255;
            F(spawn,u8,0x31)=1;F(spawn,u8,0x20)=0;
            F(spawn,u8,0xBC)=0;
            qcopy(spawn+0x10,o+0x10);
            func_002A0F48(spawn);func_002AB650(spawn);
            F(F(spawn,char *,0x68),char *,4)=o;
            func_PAL_002AC718(o,at,target,0,0,20,6,32,6,4,3,2,-1,20,1,3,-1,0,0x810001);
            func_L03_003268C0(o,0x96D,3,0,0,0,0,D_L08_001A8F20);
            func_002E5CF8(3,0,o);
            angle=func_002A7940();
            n=0;
            do {
                speed=D_L08_001B02F0*0.020000001f;
                t=func_002A7878(D_L08_001B02F4,D_L08_001B02F8);
                --n;
                func_002AF000(velocity,speed,angle,t*0.017453294f);
                angle+=2.0943954f;
                func_00282CC0(position,target,velocity);
                t=func_002A7878(1,10);
                z=func_002A7878(8,12);
                func_PAL_L08_00414850(o,position,velocity,t,z);
            }while(n>=0);
            func_0029F338(o);
        }
    }
}

#include "include_asm.h"

#include "common.h"
#define F(p,T,o) (((struct { char pad[o]; T v; } *)(p))->v)
typedef int B971Quad __attribute__((mode(TI)));
extern char *D_L04_001B25CC[] __attribute__((sda)) NOT_SDA, *D_L04_001B24E8[] __attribute__((sda)) NOT_SDA, *g_moby_l04_pool[] __attribute__((sda)) NOT_SDA;
extern char D_L04_001B9540[] NOT_SDA, g_hero_state[] NOT_SDA;
extern int g_current_lap, g_race_time_ticks;
extern int D_L04_001B0918 __attribute__((sda));
extern char *D_L04_001B08F4 __attribute__((sda));
extern void racer_release_sound_handles(char *,char *),racer_reset_state(char *,int),hoverbike_init_race_course(char *);
extern void hero_reset_position_and_direction(void *,void *,int,int),moby_mark_spawned(char *);
extern void part_refresh_active_records(char *),racer_activate_linked(char *),func_US2_0029C548(int,int);

void func_US2_L04_0040BE48(char *m,int hidden)
{
    float point[4] __attribute__((aligned(16))), rotation[4] __attribute__((aligned(16)));
    char *p=F(m,char *,0x68), *obj;
    *(B971Quad *)point=F((F(p,volatile int,0x198)<<7)+(unsigned int)D_L04_001B25CC[0],B971Quad,0x30);
    *(B971Quad *)rotation=F((F(p,volatile int,0x198)<<7)+(unsigned int)D_L04_001B25CC[0],B971Quad,0x70);
    F(D_L04_001B9540,int,0x16c)=F(D_L04_001B9540,int,0x188)=F(D_L04_001B9540,int,0x180)=F(D_L04_001B9540,int,0x168)=F(D_L04_001B9540,int,0x160)=0;
    racer_release_sound_handles(m,p);
    racer_reset_state(m,0);
    hoverbike_init_race_course(m);
    hero_reset_position_and_direction(point,rotation,0x31,1);
    F(m,unsigned char,0x20)=2;
    F(m,B971Quad,0x10)=*(B971Quad *)point;F(m,B971Quad,0xf0)=*(B971Quad *)rotation;
    F(m,unsigned short,0x34)=(F(m,unsigned short,0x34)&0xffbe)|0x400;
    F(p,int,0x394)=150;
    F(m,unsigned char,0x30)=255;
    F(p,int,0x270)=0;
    g_current_lap=0;g_race_time_ticks=0;D_L04_001B0918=0;
    obj=D_L04_001B24E8[0];
    F(p,int,0x31c)=0;
    for(;obj;obj=F(obj,char *,0x28)) {
        unsigned short type=F(obj,unsigned short,0xaa);
        if ((unsigned int)(type-0xabd)<2 || (short)type==0xb3d || (short)type==0xb3e || (short)type==0xb3f || (short)type==0xb40 || (short)type==0x27f || (short)type==0x70 || (short)type==0x7a) moby_mark_spawned(obj);
    }
    part_refresh_active_records(m);racer_activate_linked(m);
    F(g_hero_state,int,0x24a0)=26;
    F(D_L04_001B9540,int,0x400)=0;
    F(g_hero_state,unsigned char,0x22b7)=1;
    F(g_hero_state,unsigned char,0x22b5)=1;
    F(F(g_hero_state,char *,0x2290),int,0x98)=0;
    F(g_hero_state,unsigned char,0x22c2)=1;
    if (hidden) {
        char *hiddenObj;
        F(m,unsigned char,0xbc)=0;
        F(m,unsigned short,0x34)|=0x41;
        func_US2_0029C548(0,0);
        if (F(p,int,0x1dc)!=-1) {
            char *child;
            hiddenObj=g_moby_l04_pool[0]+(F(p,int,0x1dc)<<8);
            child=D_L04_001B08F4;
            F(hiddenObj,unsigned short,0x34)|=0x41;
            if(child) F(child,unsigned short,0x34)|=0x41;
        }
        { char *base=g_moby_l04_pool[0];
        int noChild=-1;
        int i, *slot;
        for(slot=(int *)(p+0x1e4),i=20;i>=0;i--,slot++) {
            if(*slot!=noChild) {
                char *child;
                hiddenObj=base+(*slot<<8);
                F(hiddenObj,unsigned short,0x34)|=0x41;
                child=F(F(hiddenObj,char *,0x68),char *,0x8c);
                if(child) F(child,unsigned short,0x34)|=0x41;
            }
        }
        }
    } else F(m,unsigned char,0xbc)=2;
}

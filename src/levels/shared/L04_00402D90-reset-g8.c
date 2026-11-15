#include "common.h"
#define F(p,T,o) (((struct { char pad[o]; T v; } *)(p))->v)
typedef int B971Quad __attribute__((mode(TI)));
/* Only the first pointer slot at each absolute symbol is described here. */
extern char *D_L04_001B25CC[] __attribute__((sda)) NOT_SDA, *D_L04_001B24E8[] __attribute__((sda)) NOT_SDA, *g_moby_l04_pool[] __attribute__((sda)) NOT_SDA;
extern char D_L04_001B9540[] NOT_SDA, g_hero_state[] NOT_SDA;
extern int g_current_lap, g_race_time_ticks;
extern int D_L04_001B0918 __attribute__((sda));
extern char *D_L04_001B08F4 __attribute__((sda));
extern void racer_release_sound_handles(char *,char *),racer_reset_state(char *,int),hoverbike_init_race_course(char *);
extern void hero_reset_position_and_direction(void *,void *,int,int),moby_mark_spawned(char *);
extern void part_refresh_active_records(char *),racer_activate_linked(char *),level_store_value_pair(int,int);
/* Puts the race back at the start: moves the controller to its start spot, clears the race counters and hides or shows the racers. */
void race_reset_controller(char *controller,int hidden)
{
    float point[4] __attribute__((aligned(16))), rotation[4] __attribute__((aligned(16)));
    char *vars=F(controller,char *,0x68), *obj;
    *(B971Quad *)point=F((F(vars,volatile int,0x198)<<7)+(unsigned int)D_L04_001B25CC[0],B971Quad,0x30);
    *(B971Quad *)rotation=F((F(vars,volatile int,0x198)<<7)+(unsigned int)D_L04_001B25CC[0],B971Quad,0x70);
    F(D_L04_001B9540,int,0x16c)=F(D_L04_001B9540,int,0x188)=F(D_L04_001B9540,int,0x180)=F(D_L04_001B9540,int,0x168)=F(D_L04_001B9540,int,0x160)=0;
    racer_release_sound_handles(controller,vars);
    racer_reset_state(controller,0);
    hoverbike_init_race_course(controller);
    hero_reset_position_and_direction(point,rotation,0x31,1);
    F(controller,unsigned char,0x20)=2;
    F(controller,B971Quad,0x10)=*(B971Quad *)point;F(controller,B971Quad,0xf0)=*(B971Quad *)rotation;
    F(controller,unsigned short,0x34)=(F(controller,unsigned short,0x34)&0xffbe)|0x400;
    F(vars,int,0x394)=150;
    F(controller,unsigned char,0x30)=255;
    F(vars,int,0x270)=0;
    g_current_lap=0;g_race_time_ticks=0;D_L04_001B0918=0;
    obj=D_L04_001B24E8[0];
    F(vars,int,0x31c)=0;
    for(;obj;obj=F(obj,char *,0x28)) {
        unsigned short type=F(obj,unsigned short,0xaa);
        if ((unsigned int)(type-0xabd /* moby class 2749 */)<2 || (short)type==0xb3d /* moby class 2877 */ || (short)type==0xb3e /* moby class 2878 */ || (short)type==0xb3f /* moby class 2879 */ || (short)type==0xb40 /* moby class 2880 */ || (short)type==0x27f /* moby class 639 */ || (short)type==0x70 /* moby class 112 */ || (short)type==0x7a /* moby class 122 */) moby_mark_spawned(obj);
    }
    part_refresh_active_records(controller);racer_activate_linked(controller);
    F(g_hero_state,int,0x24a0)=26;
    F(D_L04_001B9540,int,0x400)=0;
    F(g_hero_state,unsigned char,0x22b7)=1;
    F(g_hero_state,unsigned char,0x22b5)=1;
    F(F(g_hero_state,char *,0x2290),int,0x98)=0;
    F(g_hero_state,unsigned char,0x22c2)=1;
    if (hidden) {
        char *hiddenObj;
        F(controller,unsigned char,0xbc)=0;
        F(controller,unsigned short,0x34)|=0x41;
        level_store_value_pair(0,0);
        if (F(vars,int,0x1dc)!=-1) {
            char *child;
            hiddenObj=g_moby_l04_pool[0]+(F(vars,int,0x1dc)<<8);
            child=D_L04_001B08F4;
            F(hiddenObj,unsigned short,0x34)|=0x41;
            if(child) F(child,unsigned short,0x34)|=0x41;
        }
        { char *base=g_moby_l04_pool[0];
        int noChild=-1;
        int i, *slot;
        for(slot=(int *)(vars+0x1e4),i=20;i>=0;i--,slot++) {
            if(*slot!=noChild) {
                char *child;
                hiddenObj=base+(*slot<<8);
                F(hiddenObj,unsigned short,0x34)|=0x41;
                child=F(F(hiddenObj,char *,0x68),char *,0x8c);
                if(child) F(child,unsigned short,0x34)|=0x41;
            }
        }
        }
    } else F(controller,unsigned char,0xbc)=2;
}

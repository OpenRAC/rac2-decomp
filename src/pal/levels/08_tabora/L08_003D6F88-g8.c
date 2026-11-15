#include "include_asm.h"

#include "common.h"
#define F(p,T,o) (*(T *)((char *)(p)+(o)))
extern char D_L08_001B9B00[], D_0019B4A8[];
extern char D_L08_001A8F20[] __attribute__((sda));
extern struct { char pad[0x464]; u8 flags[0]; } D_L08_0021EAF0;
extern int g_current_map_index;
extern int D_L08_001A8F00 __attribute__((sda));
extern float D_L08_001B02F0 __attribute__((sda)), D_L08_001B02F4 __attribute__((sda)), D_L08_001B02F8 __attribute__((sda));
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *), moby_mark_spawned(void *);
extern int moby_is_in_selected_zone(void *),game_is_either_mode_two(void);
extern float coll_probe_ground_height_below(void *,int,float),math_random_float_range(float,float),math_random_angle(void),IntToFloat(int);
extern int FloatToInt(float),math_random_int_range(int,int);
extern void moby_set_state(void *,int,int),func_PAL_L08_003D0280(void *);
extern void *part_find_owned_effect_slot(void *,int,int);
extern float func_PAL_002AA108(void *,void *);
extern void func_PAL_002AC290(void *,void *),func_PAL_002AC3C0(void *,void *),moby_transform_joint_to_world(void *,int,void *),anim_start_immediate(void *,int,int);
extern void func_PAL_002AC718(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void part_spawn_effect_burst(void *,int,int,int,int,int,int,void *);
extern int PlayMobySound(int,int,void *);
extern void *CreateMoby(int);
extern void func_002A0F48(void *),hero_copy_field_to_moby(void *),vec_build_spherical_offset(void *,float,float,float);
extern void FastVecAdd(void *,void *,void *),func_PAL_L08_00414850(void *,void *,void *,float,float);

/* Applies damage, updates hit effects, and spawns debris when health reaches zero. */
void func_PAL_L08_003D6F88(char *o) {
    char *p=F(o,char *,0x68), *hit, *spawn, *health, *effect;
    float impact, z, angle, speed, t;
    int n, bits, sound;
    float at[4] __attribute__((aligned(16)));
    float target[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    if(F(o,u8,0x31) && fast_vec_dist(o+0x10,D_L08_001B9B00)<48.0f) {
        moby_update_ground_check(o); F(o,u8,0x6F)=45;
    }
    if(F(o,u8,0xB0)!=255) {
        unsigned short index=F(o,u16,0xB2);
        if(D_L08_0021EAF0.flags[(short)index]) {moby_mark_spawned(o);return;}
        bits=F(D_0019B4A8,u8,((short)index>>1)+(g_current_map_index<<10));
        if((index&1) ? ((bits>>4)&7) : (bits&7)) {moby_mark_spawned(o);return;}
    }
    if(!moby_is_in_selected_zone(o+0x10)) return;
    if(D_L08_001A8F00==2) {F(o,u8,0x31)=0;F(o,u16,0x34)|=1;}
    else {F(o,u8,0x31)=1;F(o,u16,0x34)&=0xFFFE;}
    if(game_is_either_mode_two())return;
    if(!F(o,u8,0x20)) {
        z=coll_probe_ground_height_below(o+0x10,0,0.5f);
        z-=math_random_float_range(0.2f,0.7f);
        F(o,float,0x18)=z;
        moby_set_state(o,1,-1);
    }
    if(!p)return;
    if(F(o,u8,0x31))func_PAL_L08_003D0280(o);
    health=p+0x20;effect=p+0x50;
    hit=part_find_owned_effect_slot(o,0x230000,0);
    impact=func_PAL_002AA108(o,hit);
    if(impact>0) {
        F(health,float,0)-=impact;
        F(effect,u8,7)=255;F(effect,u8,8)=255;F(effect,u8,9)=255;
        func_PAL_002AC290(o,effect);
        moby_transform_joint_to_world(o,0,at);
        anim_start_immediate(o,3,FloatToInt(IntToFloat(F(p,s16,0x24))-F(health,float,0))<16 ? FloatToInt(IntToFloat(F(p,s16,0x24))-F(health,float,0)) : 15);
        F(o,int,0x48)=0;
        z=F(o,float,0x48);
        func_PAL_002AC718(o,D_L08_001A8F20,at,z,z,4,2,5,2,1,9,1,-1,z,0,0,-1,0,0x810001);
        part_spawn_effect_burst(o,-1,0,0x96D,1,3,0,D_L08_001A8F20);
        sound=math_random_int_range(0,2);
        if(F(health,float,0)>z)PlayMobySound(sound,0,o);
    }
    F(o,u8,0xA8)=255;
    func_PAL_002AC3C0(o,effect);
    if(F(health,float,0)<=0) {
        qzero(at);at[2]=0.20000002f;
        if(hit)qcopy(target,hit);
        else {qcopy(target,o+0x10);target[2]+=2;}
        spawn=CreateMoby(0x8C4);
        if(spawn) {
            F(spawn,u8,0x23)=80;F(spawn,u16,0x34)|=0x800;
            F(spawn,float,0x2C)=F(F(spawn,char *,0x24),float,0x24)*0.65f;
            F(spawn,u8,0x30)=255;F(spawn,u16,0x32)=255;
            F(spawn,u8,0x31)=1;F(spawn,u8,0x20)=0;
            F(spawn,u8,0xBC)=0;
            qcopy(spawn+0x10,o+0x10);
            func_002A0F48(spawn);hero_copy_field_to_moby(spawn);
            F(F(spawn,char *,0x68),char *,4)=o;
            func_PAL_002AC718(o,at,target,0,0,20,6,32,6,4,3,2,-1,20,1,3,-1,0,0x810001);
            part_spawn_effect_burst(o,0x96D,3,0,0,0,0,D_L08_001A8F20);
            PlayMobySound(3,0,o);
            angle=math_random_angle();
            n=0;
            do {
                speed=D_L08_001B02F0*0.020000001f;
                t=math_random_float_range(D_L08_001B02F4,D_L08_001B02F8);
                --n;
                vec_build_spherical_offset(velocity,speed,angle,t*0.017453294f);
                angle+=2.0943954f;
                FastVecAdd(position,target,velocity);
                t=math_random_float_range(1,10);
                z=math_random_float_range(8,12);
                func_PAL_L08_00414850(o,position,velocity,t,z);
            }while(n>=0);
            moby_mark_spawned(o);
        }
    }
}

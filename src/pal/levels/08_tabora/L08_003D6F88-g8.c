#include "include_asm.h"

#include "common.h"
#define F(p,T,o) (*(T *)((char *)(p)+(o)))
extern char g_hero_position_vec[], g_moby_nibble_table[];
extern char g_str_effect_name[] __attribute__((sda));
extern struct { char pad[0x464]; u8 flags[0]; } g_moby_spawn_state_flags_b;
extern int g_current_map_index;
extern int g_cutscene_l08_active_flag __attribute__((sda));
extern float g_crystal_shell_speed __attribute__((sda)), g_crystal_shell_random_low __attribute__((sda)), g_crystal_shell_random_high __attribute__((sda));
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *), moby_mark_spawned(void *);
extern int moby_is_in_selected_zone(void *),game_is_either_mode_two(void);
extern float coll_probe_ground_height_below(void *,int,float),math_random_float_range(float,float),math_random_angle(void),IntToFloat(int);
extern int FloatToInt(float),math_random_int_range(int,int);
extern void moby_set_state(void *,int,int),gfx_draw_glowing_spark_rings_pal(void *);
extern void *part_find_owned_effect_slot(void *,int,int);
extern float moby_update_aim_target_strength_pal(void *,void *);
extern void gfx_start_color_fade_pal(void *,void *), gfx_update_color_fade_pal(void *,void *), anim_start_immediate(void *,int,int);
extern void moby_transform_joint_to_world(void *,int,void *);
extern void SpawnExplosionEffects_pal(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void part_spawn_effect_burst(void *,int,int,int,int,int,int,void *);
extern int PlayMobySound(int,int,void *);
extern void *CreateMoby(int);
extern void func_002A0F48(void *),hero_copy_field_to_moby(void *),vec_build_spherical_offset(void *,float,float,float);
extern void FastVecAdd(void *,void *,void *);
extern s32 moby_spawn_spinning_object_pal(void *,void *,void *,float,float);

/* Applies damage, updates hit effects, and spawns debris when health reaches zero. */
void crystal_shell_update_damage_pal(char *o) {
    char *p=F(o,char *,0x68), *hit, *spawn, *health, *effect;
    float impact, z, angle, speed, t;
    int n, bits, sound;
    float at[4] __attribute__((aligned(16)));
    float target[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    if(F(o,u8,0x31) && fast_vec_dist(o+0x10,g_hero_position_vec)<48.0f) {
        moby_update_ground_check(o); F(o,u8,0x6F)=45;
    }
    if(F(o,u8,0xB0)!=255) {
        unsigned short index=F(o,u16,0xB2);
        if(g_moby_spawn_state_flags_b.flags[(short)index]) {moby_mark_spawned(o);return;}
        bits=F(g_moby_nibble_table,u8,((short)index>>1)+(g_current_map_index<<10));
        if((index&1) ? ((bits>>4)&7) : (bits&7)) {moby_mark_spawned(o);return;}
    }
    if(!moby_is_in_selected_zone(o+0x10)) return;
    if(g_cutscene_l08_active_flag==2) {F(o,u8,0x31)=0;F(o,u16,0x34)|=1;}
    else {F(o,u8,0x31)=1;F(o,u16,0x34)&=0xFFFE;}
    if(game_is_either_mode_two())return;
    if(!F(o,u8,0x20)) {
        z=coll_probe_ground_height_below(o+0x10,0,0.5f);
        z-=math_random_float_range(0.2f,0.7f);
        F(o,float,0x18)=z;
        moby_set_state(o,1,-1);
    }
    if(!p)return;
    if(F(o,u8,0x31))gfx_draw_glowing_spark_rings_pal(o);
    health=p+0x20;effect=p+0x50;
    hit=part_find_owned_effect_slot(o,0x230000,0);
    impact=moby_update_aim_target_strength_pal(o,hit);
    if(impact>0) {
        F(health,float,0)-=impact;
        F(effect,u8,7)=255;F(effect,u8,8)=255;F(effect,u8,9)=255;
        gfx_start_color_fade_pal(o,effect);
        moby_transform_joint_to_world(o,0,at);
        anim_start_immediate(o,3,FloatToInt(IntToFloat(F(p,s16,0x24))-F(health,float,0))<16 ? FloatToInt(IntToFloat(F(p,s16,0x24))-F(health,float,0)) : 15);
        F(o,int,0x48)=0;
        z=F(o,float,0x48);
        SpawnExplosionEffects_pal(o,g_str_effect_name,at,z,z,4,2,5,2,1,9,1,-1,z,0,0,-1,0,0x810001);
        part_spawn_effect_burst(o,-1,0,0x96D,1,3,0,g_str_effect_name);
        sound=math_random_int_range(0,2);
        if(F(health,float,0)>z)PlayMobySound(sound,0,o);
    }
    F(o,u8,0xA8)=255;
    gfx_update_color_fade_pal(o,effect);
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
            SpawnExplosionEffects_pal(o,at,target,0,0,20,6,32,6,4,3,2,-1,20,1,3,-1,0,0x810001);
            part_spawn_effect_burst(o,0x96D,3,0,0,0,0,g_str_effect_name);
            PlayMobySound(3,0,o);
            angle=math_random_angle();
            n=0;
            do {
                speed=g_crystal_shell_speed*0.020000001f;
                t=math_random_float_range(g_crystal_shell_random_low,g_crystal_shell_random_high);
                --n;
                vec_build_spherical_offset(velocity,speed,angle,t*0.017453294f);
                angle+=2.0943954f;
                FastVecAdd(position,target,velocity);
                t=math_random_float_range(1,10);
                z=math_random_float_range(8,12);
                moby_spawn_spinning_object_pal(o,position,velocity,t,z);
            }while(n>=0);
            moby_mark_spawned(o);
        }
    }
}

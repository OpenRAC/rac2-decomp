#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define I(p,o) (*(int *)((p)+(o)))
#define P(p,o) (*(u8 **)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
extern u8 *g_moby_l04_pool;
extern u16 *g_moby_l04_group_lists[] NOT_SDA;
struct Resident502D0 { u8 pad[0x2290]; u8 *target; };
extern struct Resident502D0 g_hero_state NOT_SDA;
extern u8 g_str_tribesman_debug_format[] NOT_SDA, g_str_tribesman_update[] NOT_SDA, g_tether_zero_vec[] NOT_SDA;
extern int g_tribesman_group_limit;
extern float coll_probe_ground_height_below(void *, int, float);
extern int path_build_route_nodes(void *, int, void *, int);
extern void STUB_printf(void *, ...);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int), FloatToInt(float), math_random_int_range(int,int);
extern void moby_set_flag_bit(void *, int), moby_set_controller_speed_limits(void *,float,float,float,float);
extern void moby_set_state(void *,int,int), anim_start_blended_pal(void *,int,int,int);
extern u8 *CreateMoby(int);
extern void func_002A0F48(void *), moby_copy_joint_transform_to_object(void *,void *,int,int),moby_mark_spawned(void *);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *),linked_children_free(void *),part_spawn_explosion_with_sparks_pal(void *,void *,int,float,float);
extern int moby_apply_damage_to_object_pal(void *,void *,int);
extern void part_l04_spawn_spinning_pairs_pal(void *,int);
extern void moby_transform_joint_to_world(void *,int,void *);
extern int PlayMobySound(int,int,void *);
extern void gfx_start_color_fade_pal(void *,void *),tribesman_flag_group(void *),SetDeathBits_pal(void *,int,int);
extern int moby_count_group_not_in_state(int,int),hero_check_distance_zones(void *,void *,int,int,int,float,float);
extern int weapon_select_aim_target(void *,void *,float,float,int,int);

/* Shared enemy update for the Tribesman: sets up its stats and linked parts on the first frame, then handles hits, targeting and falling. Returns 1 when the moby should be removed (PAL). */
int tribesman_update_common_pal(u8 *moby) {
    u8 *vars = P(moby,0x68);
    int result;

    u8 position[16] __attribute__((aligned(16)));
    if (moby[0x20] == 0) {
        P(vars,0x18) = vars+0x140;
        F(moby,0x18) = coll_probe_ground_height_below(moby+0x10,0,0.5f);
        if (I(vars,0x560)) { H(moby,0x34) |= 0x41; I(moby,0x98)=0; }
        if (I(vars,0x548)) {
            I(vars,0x540) = path_build_route_nodes(moby,I(vars,0x544),vars+0x340,16);
            STUB_printf(g_str_tribesman_debug_format,I(vars,0x540));
        }
        if (F(vars,0x2A8)==0.0f) F(vars,0x2A8)=0.01745329424738884f*math_random_signed_float_range(15.0f,25.0f);
        else F(vars,0x2A8)*=0.01745329424738884f;
        if (I(vars,0x2B4)) F(vars,0x2A8)=math_random_signed_float_range(5.0f,30.0f)*0.01745329424738884f;
        if (math_random_int_below(2)==1) { H(moby,0x34)|=0x8000; moby_set_flag_bit(moby,1); }
        vars[0x48]=FloatToInt(20.0f);
        vars[0x4A]=FloatToInt(14.0f);
        vars[0x70]=25; I(vars,0xA8)=4;
        vars[0x71]=21; vars[0x72]=16; vars[0x76]=18; vars[0x77]=19;
        F(vars,0x7C)=0.24000001f; F(vars,0x80)=0.15f;
        F(vars,0x84)=0.008f; F(vars,0x88)=0.014f; F(vars,0x8C)=0.006f;
        vars[0xCC]=5; vars[0xCD]=10; vars[0xCE]=8; vars[0xCF]=15; vars[0xD2]=6; vars[0xD3]=11;
        F(vars,0x10C)=1.0f; F(vars,0xB8)=0.18000000715255737f; P(vars,0x188)=vars+0x2C0;
        F(vars,0x90)=0.75f; F(vars,0x94)=0.75f; F(vars,0x9C)=0.4f;
        F(vars,0x140)=0.75f; F(vars,0x144)=0.75f; F(vars,0x148)=0.4f; F(vars,0x14C)=0.4f;
        if (I(vars,0x2B4)) { F(vars,0x148)=0.6f; F(vars,0x14C)=0.6f; }
        if (I(vars,0x2B8)!=-1) I(vars,0x17C)=I(vars,0x2B8);
        F(vars,0x150)=0.9599311947822571f; F(vars,0x170)=1.4835299849510193f;
        F(vars,0x16C)=0.002f; F(vars,0x174)=1.5f;
        moby_set_controller_speed_limits(moby,0.0024f,0.060000002f,0.0016755164f,0.12566373f);
        if (I(vars,0x560)) { F(vars,0x148)=0.7f; F(vars,0x150)=1.3089970350265503f; F(vars,0x14C)=0.7f; }
        vars[0x28]=3; vars[0x29]=1; F(vars,0x30)=0.75f; F(vars,0x2BC)=vars[0x34]; vars[0x2E]=1;
        if (I(vars,0x27C)) {
            moby_set_state(moby,1,5);
            if (I(vars,0x280)!=-1) {
                u8 *other=g_moby_l04_pool+(I(vars,0x280)<<8);
                P(vars,0x284)=other;
                qcopy(moby+0x10,other+0x10); qcopy(moby+0xF0,other+0xF0);
                I(moby,0x98)=0; H(moby,0x34)&=0xAFFF;
                P(P(P(vars,0x284),0x68),0x2AC)=moby;
                P(vars,0x290)=CreateMoby(0x911);
                if (!P(vars,0x290)) return 1;
                P(vars,0x290)[0x30]=moby[0x30]; P(vars,0x290)[0x31]=0;
                func_002A0F48(P(vars,0x290));
                { u8 *child=P(vars,0x290); qcopy(child+0x10,moby+0x10); F(child,0x18)+=0.75f; }
                P(vars,0x288)=CreateMoby(0xFF9);
                if (!P(vars,0x288)) return 1;
                P(vars,0x288)[0x30]=moby[0x30]; H(P(vars,0x288),0x32)=H(moby,0x32);
                P(vars,0x288)[0x31]=1; *(u64 *)(P(vars,0x288)+0x38)=*(u64 *)(moby+0x38);
                func_002A0F48(P(vars,0x288)); moby_copy_joint_transform_to_object(moby,P(vars,0x288),1,0);
                I(vars,0x2A0)=0;
            } else {
                STUB_printf(g_str_tribesman_update); I(vars,0x27C)=0; moby_set_state(moby,4,0); return 1;
            }
        } else {
            moby_set_state(moby,4,0);
            if (moby[0x43]!=10) anim_start_blended_pal(moby,10,0,0);
            if (I(vars,0x564)==1) {
                P(vars,0x56C)=g_moby_l04_pool+(I(vars,0x568)<<8); moby_set_state(moby,5,0);
                if (moby[0x43]!=28) anim_start_blended_pal(moby,28,0,0);
            } else if (I(vars,0x564)==2) {
                P(vars,0x56C)=g_moby_l04_pool+(I(vars,0x568)<<8); moby_set_state(moby,5,0);
                if (moby[0x43]!=30) anim_start_blended_pal(moby,30,5,0);
            } else if (I(vars,0x564)==3) {
                P(vars,0x56C)=g_moby_l04_pool+(I(vars,0x568)<<8); moby_set_state(moby,5,0);
                if (moby[0x43]!=30) anim_start_blended_pal(moby,30,0,0);
            }
            P(vars,0x2AC)=CreateMoby(0x9AC);
            if (!P(vars,0x2AC)) return 1;
            P(vars,0x2AC)[0x30]=moby[0x30]; H(P(vars,0x2AC),0x32)=H(moby,0x32);
            P(vars,0x2AC)[0x31]=1; *(u64 *)(P(vars,0x2AC)+0x38)=*(u64 *)(moby+0x38);
            func_002A0F48(P(vars,0x2AC)); I(P(vars,0x2AC),0x98)=0;
            moby_copy_joint_transform_to_object(moby,P(vars,0x2AC),3,0);
        }
        qcopy(vars+0x110,moby+0x10);
        F(vars,0x120)=1.0f; F(vars,0x12C)=F(vars,0x298); F(vars,0x130)=10.0f;
        I(vars,0x294)=math_random_int_range(100,583);
    }
        if (moby[0x31] && fast_vec_dist(moby+0x10,g_tether_zero_vec)<24.0f) { moby_update_ground_check(moby); moby[0x6F]=22; }
    if (vars[0x2E]==2) { linked_children_free(moby); return 1; }
    if (P(vars,0x2AC)) moby_copy_joint_transform_to_object(moby,P(vars,0x2AC),3,0);
    if (F(vars,0x20)<=1.0f) {
        if (P(vars,0x2AC)) {
            part_spawn_explosion_with_sparks_pal(moby,P(vars,0x2AC)+0x10,-1,0.5f,3.0f);
            moby_mark_spawned(P(vars,0x2AC)); P(vars,0x2AC)=0;
        }
        I(vars,0x2A0)=0;
    }
    if (I(vars,0x1C0)>=16 && moby[0x95]==2) {
        F(vars,0x2A8)=math_random_signed_float_range(15.0f,25.0f)*0.01745329424738884f; I(vars,0x1C0)=0;
        if (moby[0x43]!=11) anim_start_blended_pal(moby,11,0,8);
        moby_set_state(moby,17,-1);
    }
    result=moby_apply_damage_to_object_pal(moby,vars+0x60,I(vars,0x2A0));
    if (result) {

        if (F(moby,0x48)!=1.0f) F(moby,0x48)=1.0f;
        if (I(vars,0x2A0)) { moby_transform_joint_to_world(moby,3,position); part_l04_spawn_spinning_pairs_pal(position,8); }
        if (result==4) PlayMobySound(24,0,moby);
        I(vars,0x2A0)=0; vars[0x57]=210; gfx_start_color_fade_pal(moby,vars+0x50); tribesman_flag_group(moby);
        if ((unsigned)(result-4)<2 && g_tribesman_group_limit>=moby[0x21] && moby_count_group_not_in_state(moby[0x21],-1)>=2) {
            u16 *ids=g_moby_l04_group_lists[moby[0x21]];
            do {
                u8 *other=P(g_moby_l04_pool+((*ids&0x7FFF)<<8),0x68);
                if (!I(other,0x2A4)) { I(other,0x2A4)=1; break; }
            } while ((s16)*ids++>=0);
        }
    }
    { u8 *old_target; u8 *state_timer=vars+0x278;
        H(vars,0x274)=hero_check_distance_zones(moby,state_timer,I(vars,0x260),I(vars,0x264),0,F(vars,0x268),F(vars,0x26C));
        I(vars,0x258)=weapon_select_aim_target(moby,P(vars,0x250),F(vars,0x268),10.0f,0,0);
        old_target=P(vars,0x240);
        I(vars,0x25C)=weapon_select_aim_target(moby,P(vars,0x254),F(vars,0x26C),10.0f,0,0);
        if (old_target!=g_hero_state.target && P(vars,0x240)==g_hero_state.target) {
            P(vars,0x240)=old_target; *(Quad *)(vars+0x230)=*(Quad *)(old_target+0x10);
        }
    }
    if (moby[0x95]!=4) {
        float floor=coll_probe_ground_height_below(moby+0x10,0,0.5f);
        F(moby,0x18)-=0.37600002f;
        if (F(moby,0x18)<floor) F(moby,0x18)=floor;
    }
    if (F(moby,0x18)<40.0f) {
        SetDeathBits_pal(moby,0,3);
        if (P(vars,0x288)) { moby_mark_spawned(P(vars,0x288)); P(vars,0x288)=0; }
        if (P(vars,0x2AC)) {
            part_spawn_explosion_with_sparks_pal(moby,P(vars,0x2AC)+0x10,-1,0.5f,3.0f);
            moby_mark_spawned(P(vars,0x2AC)); P(vars,0x2AC)=0;
        }
        return 1;
    }
    return 0;
}

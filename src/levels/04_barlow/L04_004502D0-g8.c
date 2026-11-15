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
extern u8 D_L04_001B18A0[] NOT_SDA, D_L04_002CA650[] NOT_SDA, D_L04_001B9680[] NOT_SDA;
extern int D_L04_001B24F8;
extern float coll_probe_ground_height_below(void *, int, float);
extern int path_build_route_nodes(void *, int, void *, int);
extern void STUB_printf(void *, ...);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int), FloatToInt(float), math_random_int_range(int,int);
extern void moby_set_flag_bit(void *, int), moby_set_controller_speed_limits(void *,float,float,float,float);
extern void moby_set_state(void *,int,int), anim_start_blended(void *,int,int,int);
extern u8 *CreateMoby(int);
extern void func_002A0F48(void *), moby_copy_joint_transform_to_object(void *,void *,int,int),moby_mark_spawned(void *);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *),linked_children_free(void *),part_spawn_explosion_with_sparks(void *,void *,int,float,float);
extern int moby_apply_damage_to_object(void *,void *,int);
extern void part_l04_spawn_spinning_pairs(void *,int);
extern void moby_transform_joint_to_world(void *,int,void *);
extern int PlayMobySound(int,int,void *);
extern void gfx_start_color_fade(void *,void *),tribesman_flag_group(void *),SetDeathBits(void *,int,int);
extern int moby_count_group_not_in_state(int,int),hero_check_distance_zones(void *,void *,int,int,int,float,float);
extern int weapon_select_aim_target(void *,void *,float,float,int,int);
/* Shared enemy update for the Tribesman: sets up its stats and linked parts on the first frame, then handles hits, targeting and falling. Returns 1 when the object should be removed. */
int tribesman_update_common(u8 *object) {
    u8 *data = P(object,0x68);
    int result;

    u8 position[16] __attribute__((aligned(16)));
    if (object[0x20] == 0) {
        P(data,0x18) = data+0x140;
        F(object,0x18) = coll_probe_ground_height_below(object+0x10,0,0.5f);
        if (I(data,0x560)) { H(object,0x34) |= 0x41; I(object,0x98)=0; }
        if (I(data,0x548)) {
            I(data,0x540) = path_build_route_nodes(object,I(data,0x544),data+0x340,16);
            STUB_printf(D_L04_001B18A0,I(data,0x540));
        }
        if (F(data,0x2A8)==0.0f) F(data,0x2A8)=0.01745329424738884f*math_random_signed_float_range(15.0f,25.0f);
        else F(data,0x2A8)*=0.01745329424738884f;
        if (I(data,0x2B4)) F(data,0x2A8)=math_random_signed_float_range(5.0f,30.0f)*0.01745329424738884f;
        if (math_random_int_below(2)==1) { H(object,0x34)|=0x8000; moby_set_flag_bit(object,1); }
        data[0x48]=FloatToInt(20.0f);
        data[0x4A]=FloatToInt(14.0f);
        data[0x70]=25; I(data,0xA8)=4;
        data[0x71]=21; data[0x72]=16; data[0x76]=18; data[0x77]=19;
        F(data,0x7C)=0.20000001788139343f; F(data,0x80)=0.125f;
        F(data,0x84)=0.0055555556900799274f; F(data,0x88)=0.009722222574055195f; F(data,0x8C)=0.004166666883975267f;
        data[0xCC]=5; data[0xCD]=10; data[0xCE]=8; data[0xCF]=15; data[0xD2]=6; data[0xD3]=11;
        F(data,0x10C)=1.0f; F(data,0xB8)=0.18000000715255737f; P(data,0x188)=data+0x2C0;
        F(data,0x90)=0.75f; F(data,0x94)=0.75f; F(data,0x9C)=0.4f;
        F(data,0x140)=0.75f; F(data,0x144)=0.75f; F(data,0x148)=0.4f; F(data,0x14C)=0.4f;
        if (I(data,0x2B4)) { F(data,0x148)=0.6f; F(data,0x14C)=0.6f; }
        if (I(data,0x2B8)!=-1) I(data,0x17C)=I(data,0x2B8);
        F(data,0x150)=0.9599311947822571f; F(data,0x170)=1.4835299849510193f;
        F(data,0x16C)=0.0013888889225199819f; F(data,0x174)=1.5f;
        moby_set_controller_speed_limits(object,0.0016666667060926557f,0.05000000447034836f,0.0011635529808693528f,0.10471977293491364f);
        if (I(data,0x560)) { F(data,0x148)=0.7f; F(data,0x150)=1.3089970350265503f; F(data,0x14C)=0.7f; }
        data[0x28]=3; data[0x29]=1; F(data,0x30)=0.75f; F(data,0x2BC)=data[0x34]; data[0x2E]=1;
        if (I(data,0x27C)) {
            moby_set_state(object,1,5);
            if (I(data,0x280)!=-1) {
                u8 *other=g_moby_l04_pool+(I(data,0x280)<<8);
                P(data,0x284)=other;
                qcopy(object+0x10,other+0x10); qcopy(object+0xF0,other+0xF0);
                I(object,0x98)=0; H(object,0x34)&=0xAFFF;
                P(P(P(data,0x284),0x68),0x2AC)=object;
                P(data,0x290)=CreateMoby(0x911 /* moby class 2321 */);
                if (!P(data,0x290)) return 1;
                P(data,0x290)[0x30]=object[0x30]; P(data,0x290)[0x31]=0;
                func_002A0F48(P(data,0x290));
                { u8 *child=P(data,0x290); qcopy(child+0x10,object+0x10); F(child,0x18)+=0.75f; }
                P(data,0x288)=CreateMoby(0xFF9 /* moby class 4089 */);
                if (!P(data,0x288)) return 1;
                P(data,0x288)[0x30]=object[0x30]; H(P(data,0x288),0x32)=H(object,0x32);
                P(data,0x288)[0x31]=1; *(u64 *)(P(data,0x288)+0x38)=*(u64 *)(object+0x38);
                func_002A0F48(P(data,0x288)); moby_copy_joint_transform_to_object(object,P(data,0x288),1,0);
                I(data,0x2A0)=0;
            } else {
                STUB_printf(D_L04_002CA650); I(data,0x27C)=0; moby_set_state(object,4,0); return 1;
            }
        } else {
            moby_set_state(object,4,0);
            if (object[0x43]!=10) anim_start_blended(object,10,0,0);
            if (I(data,0x564)==1) {
                P(data,0x56C)=g_moby_l04_pool+(I(data,0x568)<<8); moby_set_state(object,5,0);
                if (object[0x43]!=28) anim_start_blended(object,28,0,0);
            } else if (I(data,0x564)==2) {
                P(data,0x56C)=g_moby_l04_pool+(I(data,0x568)<<8); moby_set_state(object,5,0);
                if (object[0x43]!=30) anim_start_blended(object,30,5,0);
            } else if (I(data,0x564)==3) {
                P(data,0x56C)=g_moby_l04_pool+(I(data,0x568)<<8); moby_set_state(object,5,0);
                if (object[0x43]!=30) anim_start_blended(object,30,0,0);
            }
            P(data,0x2AC)=CreateMoby(0x9AC /* moby class 2476 */);
            if (!P(data,0x2AC)) return 1;
            P(data,0x2AC)[0x30]=object[0x30]; H(P(data,0x2AC),0x32)=H(object,0x32);
            P(data,0x2AC)[0x31]=1; *(u64 *)(P(data,0x2AC)+0x38)=*(u64 *)(object+0x38);
            func_002A0F48(P(data,0x2AC)); I(P(data,0x2AC),0x98)=0;
            moby_copy_joint_transform_to_object(object,P(data,0x2AC),3,0);
        }
        qcopy(data+0x110,object+0x10);
        F(data,0x120)=1.0f; F(data,0x12C)=F(data,0x298); F(data,0x130)=10.0f;
        I(data,0x294)=math_random_int_range(120,700);
    }
        if (object[0x31] && fast_vec_dist(object+0x10,D_L04_001B9680)<24.0f) { moby_update_ground_check(object); object[0x6F]=22; }
    if (data[0x2E]==2) { linked_children_free(object); return 1; }
    if (P(data,0x2AC)) moby_copy_joint_transform_to_object(object,P(data,0x2AC),3,0);
    if (F(data,0x20)<=1.0f) {
        if (P(data,0x2AC)) {
            part_spawn_explosion_with_sparks(object,P(data,0x2AC)+0x10,-1,0.5f,3.0f);
            moby_mark_spawned(P(data,0x2AC)); P(data,0x2AC)=0;
        }
        I(data,0x2A0)=0;
    }
    if (I(data,0x1C0)>=16 && object[0x95]==2) {
        F(data,0x2A8)=math_random_signed_float_range(15.0f,25.0f)*0.01745329424738884f; I(data,0x1C0)=0;
        if (object[0x43]!=11) anim_start_blended(object,11,0,10);
        moby_set_state(object,17,-1);
    }
    result=moby_apply_damage_to_object(object,data+0x60,I(data,0x2A0));
    if (result) {

        if (F(object,0x48)!=1.0f) F(object,0x48)=1.0f;
        if (I(data,0x2A0)) { moby_transform_joint_to_world(object,3,position); part_l04_spawn_spinning_pairs(position,8); }
        if (result==4) PlayMobySound(24,0,object);
        I(data,0x2A0)=0; data[0x57]=210; gfx_start_color_fade(object,data+0x50); tribesman_flag_group(object);
        if ((unsigned)(result-4)<2 && D_L04_001B24F8>=object[0x21] && moby_count_group_not_in_state(object[0x21],-1)>=2) {
            u16 *ids=g_moby_l04_group_lists[object[0x21]];
            do {
                u8 *other=P(g_moby_l04_pool+((*ids&0x7FFF)<<8),0x68);
                if (!I(other,0x2A4)) { I(other,0x2A4)=1; break; }
            } while ((s16)*ids++>=0);
        }
    }
    { u8 *oldTarget; u8 *stateTimer=data+0x278;
        H(data,0x274)=hero_check_distance_zones(object,stateTimer,I(data,0x260),I(data,0x264),0,F(data,0x268),F(data,0x26C));
        I(data,0x258)=weapon_select_aim_target(object,P(data,0x250),F(data,0x268),10.0f,0,0);
        oldTarget=P(data,0x240);
        I(data,0x25C)=weapon_select_aim_target(object,P(data,0x254),F(data,0x26C),10.0f,0,0);
        if (oldTarget!=g_hero_state.target && P(data,0x240)==g_hero_state.target) {
            P(data,0x240)=oldTarget; *(Quad *)(data+0x230)=*(Quad *)(oldTarget+0x10);
        }
    }
    if (object[0x95]!=4) {
        float floor=coll_probe_ground_height_below(object+0x10,0,0.5f);
        F(object,0x18)-=0.31333333253860474f;
        if (F(object,0x18)<floor) F(object,0x18)=floor;
    }
    if (F(object,0x18)<40.0f) {
        SetDeathBits(object,0,3);
        if (P(data,0x288)) { moby_mark_spawned(P(data,0x288)); P(data,0x288)=0; }
        if (P(data,0x2AC)) {
            part_spawn_explosion_with_sparks(object,P(data,0x2AC)+0x10,-1,0.5f,3.0f);
            moby_mark_spawned(P(data,0x2AC)); P(data,0x2AC)=0;
        }
        return 1;
    }
    return 0;
}

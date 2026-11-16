#include "include_asm.h"

/* func_PAL_L19_0041B440, the PAL copy of func_L19_004160A0: the same C at 50 Hz, with the timers, rates and
   velocities scaled and the table index spelled as a shift pair. */
#include "common.h"

#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define H(p,o) (*(u16 *)((char *)(p)+(o)))
#define S(p,o) (*(s16 *)((char *)(p)+(o)))
#define W(p,o) (*(s32 *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
typedef struct {
    char pad0[0x80];
    float position[4];
    char pad90[0x40];
    float saved_position[4];
    char padE0[0x21B0];
    char *target;
    int mode;
} GrelbinContext;
extern char g_hero_state[];
extern char g_particle_effect_template[] MACRO_ADDR;
extern char g_hit_position_vec[], g_hero_l19_state_block[];
extern char g_leviathan_data[];
typedef struct { char pad[0x464]; u8 entries[1]; } ActorFlags;
extern ActorFlags g_trigger_active_table;
extern char *g_group_ptr_table[];
extern char *g_moby_l19_array __attribute__((sda));
extern void moby_fade_out_update(void *);
extern int g_leviathan_particle_param __attribute__((sda));
extern int g_active_yeti_count __attribute__((sda));
extern int g_current_map_index MACRO_ADDR;
extern unsigned char g_moby_nibble_table[];
extern int moby_is_in_selected_zone(void *);
extern int FloatToInt(float);
extern void cam_end_override(void *);
extern int leviathan_update_helper_pal(void *);
extern int moby_count_group_not_in_state(int,int);
extern void moby_set_state(void *,int,int);
extern void anim_start_blended_pal(void *,int,int,int);
extern int FastDecTimer(void *);
extern int math_random_int_range(int,int);
extern float mat_fast_helper_a(float,float);
extern int moby_start_effect_from_entry(void *,float);
extern char *cam_alloc_override_slot_pal(int);
extern float math_step_value_toward_target(void *,void *,float,float,float,float);
extern float vec_distance_xy(void *,void *);
extern void SetDeathBits_pal(void *,int,int);
extern void moby_mark_spawned(void *);
extern int math_is_value_within_step_pal(void *,float);
extern char *CreateMoby(int);
extern void func_002A0F48(void *);
extern void hero_copy_field_to_moby(void *);
extern float moby_get_anim_value(void *);
extern void vec_random_direction(void *,float,float);
extern float math_fabs(float);
extern void FastVecAdd(void *,void *,void *);
extern char *cam_moby_create_pal(void *,int,int,int,void *,void *,void *,int,float,float);
extern void moby_init_child_from_parent(void *,void *);
extern int math_random_int_below(int);
extern int PlayMobySound(int,int,void *);
extern void gfx_add_draw_callback_first(void (*)(void *),void *);
extern void leviathan_draw_charge_flash(void *), part_emit_beam_muzzle_glow(void *), DrawGrelbinBeamEffect(void *);
extern void part_spawn_random_direction_effect(void *,float,float);
extern float math_random_signed_float_range(float,float), math_random_float_range(float,float);
extern char *part_spawn_fading_drift(void *,void *,int,int,int,int,int,float,float,float,int);
extern void make_hit_descriptor(void *,void *,int,void *,float);
extern void moby_transform_joint_point(void *,int,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecSub(void *,void *,void *);
extern int CollLine(void *,void *,int,void *,void *);
extern void moby_tick_timers_age(void *);

/* Updates the Leviathan boss: eyes the hero, charges and fires its beam, takes hits and spawns the yeti it drops (PAL: 50 Hz timings). */
void leviathan_update_pal(char *obj)
{
    float direction[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    char hit_desc[0x30] __attribute__((aligned(16)));
    char joint_matrix[0x40] __attribute__((aligned(16)));
    float scaled[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    char *src_matrix;
    char *vars;
    char *spawned_actor;
    int can_act,i,value;
    float random_scale;
    u16 flags;

    if (((GrelbinContext *)g_hero_state)->mode == 0x6F) return;
    if (!moby_is_in_selected_zone(obj+0x10)) {
        B(obj,0x30)=FloatToInt((float)S(obj,0x32)+15.0f);
        return;
    }
    vars=P(obj,0x68);
    if (H(obj,0x34)&0x80) {
        char *child=P(vars,0x2F0);
        if (child) H(child,0x34)|=0x80;
    } else {
        char *child=P(vars,0x2F0);
        if (child) H(child,0x34)&=0xFF7F;
    }
    if ((unsigned)(B(obj,0x95)-2)>=2 || ((GrelbinContext *)g_hero_state)->mode==0x31 || F(vars,0x20)<=0.0f) {
        if (W(vars,0x310)) { cam_end_override(P(vars,0x314)); W(vars,0x310)=0; }
    }
    if (leviathan_update_helper_pal(obj)) {
        if (W(vars,0x310)) {cam_end_override(P(vars,0x314)); W(vars,0x310)=0;}
        moby_mark_spawned(obj);
        return;
    }
    switch (B(obj,0x95)) {
    case 0:
    {
        char *idle_target;
        can_act=1;
        if (B(obj,0x21)!=0xFF && g_group_ptr_table[B(obj,0x21)]) {
            if (moby_count_group_not_in_state(W(vars,0x308),-1)) can_act=0;
        }
        if (W(vars,0x30C)!=-1) {
            idle_target=g_moby_l19_array+(W(vars,0x30C)<<8);
            if (idle_target && B(idle_target,0x20)!=0xFE && B(idle_target,0x20)!=0xFD) can_act=0;
        }
        if (can_act) {
            if (W(vars,0x2FC)==1) {
                moby_set_state(obj,4,2);
                if (B(obj,0x43)) anim_start_blended_pal(obj,0,0,8);
            } else if (W(vars,0x220) && FastDecTimer(vars+0x21E)) {
                moby_set_state(obj,2,1);
                W(vars,0x220)=0;
                if (W(vars,0x218)<250) W(vars,0x218)=(math_random_int_range(480,600)*5+2)/6;
            }
        }
        idle_target=P(vars,0x200);
        moby_start_effect_from_entry(obj,mat_fast_helper_a(F(idle_target,0x10)-F(obj,0x10),F(idle_target,0x14)-F(obj,0x14)));
        break;
    }
    case 1:
        if ((W(vars,0x2FC)==1 || W(vars,0x2F8)==1) && B(obj,0x20)!=11) {
            moby_set_state(obj,7,2);
            if (B(obj,0x43)!=2) anim_start_blended_pal(obj,2,0,8);
        }
        break;
    case 2:
    {
        char *attack_target;
        if (!W(vars,0x310) && ((GrelbinContext *)g_hero_state)->mode!=0x31) {
            P(vars,0x314)=cam_alloc_override_slot_pal(5);
            F(P(vars,0x314),0)=10.0f;
            F(P(vars,0x314),4)=0.1f;
            W(P(vars,0x314),0xC)=0;
            W(vars,0x310)=1;
        }
        attack_target=P(vars,0x200);
        moby_start_effect_from_entry(obj,mat_fast_helper_a(F(attack_target,0x10)-F(obj,0x10),F(attack_target,0x14)-F(obj,0x14)));
        if (B(obj,0x20)!=4) math_step_value_toward_target(obj+0x18,vars+0x2D4,F(vars,0x2D0),0.0056000003f,0.0056000003f,0.84000003f);
        if (B(obj,0x20)!=4 && B(obj,0x20)!=11) {
            if (vec_distance_xy(obj+0x10,((GrelbinContext *)g_hero_state)->position)<12.0f) F(vars,0x2D0)=F(vars,0x2D8)-10.0f;
            else if (vec_distance_xy(obj+0x10,((GrelbinContext *)g_hero_state)->position)<26.0f) F(vars,0x2D0)=F(vars,0x2D8)-7.0f;
            else F(vars,0x2D0)=F(vars,0x2D8)-4.0f;
        }
        if (W(vars,0x2FC)!=1 && W(vars,0x2F8)!=1 && B(obj,0x20)!=4 && B(obj,0x20)!=7 && B(obj,0x20)!=8 && B(obj,0x20)!=9 && B(obj,0x20)!=11) {
            moby_set_state(obj,2,1);
            if (B(obj,0x43)!=1) anim_start_blended_pal(obj,1,0,8);
        }
        break;
    }
    case 4:
    {
        char *dying_target;
        dying_target=P(vars,0x200);
        moby_start_effect_from_entry(obj,mat_fast_helper_a(F(dying_target,0x10)-F(obj,0x10),F(dying_target,0x14)-F(obj,0x14)));
        if (B(obj,0x20)!=4) math_step_value_toward_target(obj+0x18,vars+0x2D4,F(vars,0x2D0),0.56f,0.56f,0.84000003f);
        /* fall through */
    }
    case 3:
        if (B(obj,0x60)&2) {SetDeathBits_pal(obj,0,3);moby_mark_spawned(obj);return;}
    {
    char *child_state;
    if (F(vars,0x20)<=0.0f && math_is_value_within_step_pal(obj,37.0f) && !(g_trigger_active_table.entries[(s16)(flags=H(obj,0xB2))])) {
        int counts=g_moby_nibble_table[((s32)(flags<<16)>>17)+(g_current_map_index<<10)];
        if (!((flags&1) ? (counts>>4)&7 : counts&7)) {
            spawned_actor=CreateMoby(0x1266);
            if (spawned_actor) {
                u16 id=H(obj,0xB2);
                if (id&1) {
                    u8 *marks=g_moby_nibble_table+(((s32)(id<<16)>>17)+(g_current_map_index<<10));
                    if (((*marks>>4)&7)!=7) *marks+=0x10;
                } else {
                    u8 *marks=g_moby_nibble_table+(((s32)(id<<16)>>17)+(g_current_map_index<<10));
                    if ((*marks&7)!=7) *marks+=1;
                }
                B(spawned_actor,0x23)=0x50;
                H(spawned_actor,0x34)|=0x800;
                B(spawned_actor,0x30)=0xFF; H(spawned_actor,0x32)=0xFF; B(spawned_actor,0x31)=1;
                B(spawned_actor,0x20)=0; B(spawned_actor,0xBC)=0;
                qcopy(spawned_actor+0x10,P(vars,0x2F0)+0x10);
                F(spawned_actor,0x18)+=1.0f;
                func_002A0F48(spawned_actor);hero_copy_field_to_moby(spawned_actor);
                child_state=P(spawned_actor,0x68); F(child_state,0)=0.1f;
                anim_start_blended_pal(spawned_actor,1,0,20);
                F(spawned_actor,0x48)=F(child_state,0)+F(child_state,0);B(spawned_actor,0x20)=2;
            }
        }
    }
    }
        break;
    }
    switch (B(obj,0x20)) {
    case 4:
    {
        char *new_actor;
        if (moby_get_anim_value(obj)>=4.0f && !W(vars,0x304) && !B(obj,0x42)) {
            char *shake=g_hero_l19_state_block;
            int j;
            F(shake,0x160)=0.25f;
            W(shake,0x168)=0x20;W(shake,0x16C)=0;
            H(obj,0x34)=(H(obj,0x34)&0xFFBE)|0x1000;
            W(obj,0x98)=W(P(obj,0x24),0x10);W(vars,0x304)=1;
            for (j=0;j<5;j++) {
                char *effect,*src;
                vec_random_direction(direction,0.34000003f,0.42000002f);
                direction[2]=math_fabs(direction[2])*6.5f;
                if (direction[2]>1.5000001f) direction[2]=1.5000001f;
                FastVecAdd(direction,direction,g_particle_effect_template);
                src=P(vars,0x2F0);
                effect=cam_moby_create_pal(src,1,S(src,0xAA),j,src+0x10,src+0xF0,direction,0xFF,180.0f,45.0f);
                P(effect,0x64)=(char *)moby_fade_out_update;
            }
            new_actor=CreateMoby(0x1208);
            if (new_actor) {
                moby_init_child_from_parent(new_actor,P(vars,0x2F0));
                H(new_actor,0x32)=H(obj,0x32);B(new_actor,0x30)=B(obj,0x30);
                src_matrix=P(vars,0x2F0);
                {
                    int row;
                    for (row=0;row<4;row++) qcopy_nc(new_actor+0xC0+row*16,src_matrix+0xC0+row*16);
                }
                moby_mark_spawned(P(vars,0x2F0));P(vars,0x2F0)=new_actor;
            }
        }
        if (B(obj,0x60)&2) {
            F(vars,0x2D0)=F(vars,0x2D8)-7.0f;
            moby_set_state(obj,7,-1);
            if (B(obj,0x43)!=2) anim_start_blended_pal(obj,2,0,8);
        }
        break;
    }
    case 2:
        if (B(obj,0x60)&2) {
            value=B(obj,0x43);
            if (value!=math_random_int_below(2)+3) anim_start_blended_pal(obj,math_random_int_below(2)+3,0,2);
            moby_set_state(obj,3,-1);
        }
        break;
    case 3:
        if (B(obj,0x60)&2) {
            if (B(obj,0x43)!=1) anim_start_blended_pal(obj,1,0,3);
            moby_set_state(obj,2,-1);
        }
        break;
    case 5:
        if (B(obj,0x60)&2) {
            moby_set_state(obj,7,-1);
            if (B(obj,0x43)!=2) anim_start_blended_pal(obj,2,0,5);
        }
        break;
    case 7:
        if (math_is_value_within_step_pal(obj,13.0f)) PlayMobySound(4,0,obj);
        if (moby_get_anim_value(obj)>17.0f && B(obj,0x42)==2) {
            F(obj,0x48)=0.5f;gfx_add_draw_callback_first(leviathan_draw_charge_flash,obj);
            if (B(obj,0x60)&2) {
                qcopy(vars+0x2E0,vars+0x1F0);
                moby_set_state(obj,8,-1);
                if (B(obj,0x43)!=4) anim_start_blended_pal(obj,4,20,17);
            }
        }
        break;
    case 8:
        gfx_add_draw_callback_first(part_emit_beam_muzzle_glow,obj);
        if (F(vars,0x22C)>=1.0f) {PlayMobySound(3,0,obj);moby_set_state(obj,9,-1);}
        break;
    case 9:
    {
        char *particle;
        gfx_add_draw_callback_first(DrawGrelbinBeamEffect,obj);
        qcopy(direction,g_hit_position_vec);
        for (i=9;i>=0;i--) {
            part_spawn_random_direction_effect(velocity,0.28000003f,0.32000002f);
            if (velocity[2]<0.0f) velocity[2]=-velocity[2];
            value=FloatToInt(math_random_signed_float_range(2.0f,5.0f));
            random_scale=math_random_float_range(0.6f,1.0f);
            part_spawn_fading_drift(vars+0x2C0,velocity,17,0x804020,value,127,127,210000.0f*random_scale,2100.0f,0.00584f,g_leviathan_particle_param);
            value=FloatToInt(math_random_signed_float_range(2.0f,5.0f));
            random_scale=math_random_float_range(0.6f,1.0f);
            particle=part_spawn_fading_drift(vars+0x2C0,velocity,17,0x804040,value,48,48,630000.0f*random_scale,4200.0f,0.00584f,0);
            if (particle) {
                char *g=g_leviathan_data;
                B(particle,2)=B(P(g,0xD4),0);
            }
        }
        make_hit_descriptor(hit_desc,obj,0x10001,g_particle_effect_template,(float)B(vars,0x34));
        moby_transform_joint_point(obj,0,joint_matrix);
        qcopy(velocity,joint_matrix+0x30);
        vec_scale_to_length(scaled,joint_matrix,0.25f);
        FastVecAdd(velocity,velocity,scaled);
        FastVecSub(delta,vars+0x2E0,velocity);
        vec_scale_to_length(delta,delta,F(vars,0x238)*60.0f);
        FastVecAdd(delta,delta,velocity);
        CollLine(velocity,delta,0,obj,hit_desc);
        if (H(obj,0x96)>40) {
            F(vars,0x234)-=0.05f;
            if (F(vars,0x234)<=0.0f) {
                F(vars,0x22C)=0.0f;F(vars,0x230)=1.0f;F(vars,0x228)=0.1f;F(vars,0x234)=0.1f;F(vars,0x238)=0.1f;
                moby_set_state(obj,10,-1);
                if (B(obj,0x43)!=3) anim_start_blended_pal(obj,3,0,8);
            }
        } else {
            F(vars,0x234)+=0.1f;if (F(vars,0x234)>1.0f) F(vars,0x234)=1.0f;
            F(vars,0x238)+=0.2f;if (F(vars,0x238)>1.0f) F(vars,0x238)=1.0f;
        }
        break;
    }
    case 10:
        if (B(obj,0x60)&2) {
            moby_set_state(obj,7,-1);
            if (B(obj,0x43)!=2) anim_start_blended_pal(obj,2,0,8);
        }
        break;
    case 11:
    {
        char *final_target;
        final_target=P(vars,0x200);
        if (final_target && S(final_target,0xAA)==MOBY_CLASS_YETI) moby_start_effect_from_entry(P(vars,0x200),mat_fast_helper_a(F(obj,0x10)-F(final_target,0x10),F(obj,0x14)-F(final_target,0x14)));
        if (B(obj,0x60)&2) {
            F(vars,0x2D0)=F(vars,0x2D8)-4.0f;
            if (W(vars,0x2FC)!=1 && W(vars,0x2F8)!=1) {
                moby_set_state(obj,7,2);
                if (B(obj,0x43)!=2) anim_start_blended_pal(obj,2,0,8);
            } else {
                moby_set_state(obj,2,1);
                if (B(obj,0x43)!=1) anim_start_blended_pal(obj,1,0,8);
            }
        }
        if (math_is_value_within_step_pal(obj,11.0f) && B(obj,0x42)==6) {
            GrelbinContext *ctx;
            char *next;
            char *dead=P(vars,0x200);
            --g_active_yeti_count;
            moby_mark_spawned(dead);
            ctx=(GrelbinContext *)g_hero_state;
            next=ctx->target;
            W(vars,0x204)=1;
            P(vars,0x200)=next;
            qcopy(vars+0x1F0,ctx->saved_position);
        }
        break;
    }
    }
    moby_tick_timers_age(obj);
}

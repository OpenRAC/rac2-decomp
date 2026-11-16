#include "include_asm.h"
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
    float savedPosition[4];
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
extern int leviathan_update_helper(void *);
extern int moby_count_group_not_in_state(int,int);
extern void moby_set_state(void *,int,int);
extern void anim_start_blended(void *,int,int,int);
extern int FastDecTimer(void *);
extern int math_random_int_range(int,int);
extern float mat_fast_helper_a(float,float);
extern int moby_start_effect_from_entry(void *,float);
extern char *cam_alloc_override_slot(int);
extern float math_step_value_toward_target(void *,void *,float,float,float,float);
extern float vec_distance_xy(void *,void *);
extern void SetDeathBits(void *,int,int);
extern void moby_mark_spawned(void *);
extern int math_is_value_within_step(void *,float);
extern char *CreateMoby(int);
extern void func_002A0F48(void *);
extern void hero_copy_field_to_moby(void *);
extern float moby_get_anim_value(void *);
extern void vec_random_direction(void *,float,float);
extern float math_fabs(float);
extern void FastVecAdd(void *,void *,void *);
extern char *cam_moby_create(void *,int,int,int,void *,void *,void *,int,float,float);
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

/* Updates the Arctic Leviathan every frame. It turns toward its target, walks, fires and bursts in turn, and blows apart when it is destroyed. */
void leviathan_update(char *moby)
{
    float burst_vel[4] __attribute__((aligned(16)));
    float particle_vel[4] __attribute__((aligned(16)));
    char hit_matrix[0x30] __attribute__((aligned(16)));
    char body_matrix[0x40] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    char *old_child;
    char *vars;
    char *spawnedActor=0;
    int can_act,i=0,count=0;
    float size_scale=0.0f;
    u16 flags;

    if (((GrelbinContext *)g_hero_state)->mode == 0x6F) return;
    if (!moby_is_in_selected_zone(moby+0x10)) {
        B(moby,0x30)=FloatToInt((float)S(moby,0x32)+15.0f);
        return;
    }
    vars=P(moby,0x68);
    if (H(moby,0x34)&0x80) {
        char *child=P(vars,0x2F0);
        if (child) H(child,0x34)|=0x80;
    } else {
        char *child=P(vars,0x2F0);
        if (child) H(child,0x34)&=0xFF7F;
    }
    if ((unsigned)(B(moby,0x95)-2)>=2 || ((GrelbinContext *)g_hero_state)->mode==0x31 || F(vars,0x20)<=0.0f) {
        if (W(vars,0x310)) { cam_end_override(P(vars,0x314)); W(vars,0x310)=0; }
    }
    if (leviathan_update_helper(moby)) {
        if (W(vars,0x310)) {cam_end_override(P(vars,0x314)); W(vars,0x310)=0;}
        moby_mark_spawned(moby);
        return;
    }
    switch (B(moby,0x95)) {
    case 0:
    {
        char *idleTarget;
        can_act=1;
        if (B(moby,0x21)!=0xFF && g_group_ptr_table[B(moby,0x21)]) {
            if (moby_count_group_not_in_state(W(vars,0x308),-1)) can_act=0;
        }
        if (W(vars,0x30C)!=-1) {
            idleTarget=g_moby_l19_array+(W(vars,0x30C)<<8);
            if (idleTarget && B(idleTarget,0x20)!=0xFE && B(idleTarget,0x20)!=0xFD) can_act=0;
        }
        if (can_act) {
            if (W(vars,0x2FC)==1) {
                moby_set_state(moby,4,2);
                if (B(moby,0x43)) anim_start_blended(moby,0,0,10);
            } else if (W(vars,0x220) && FastDecTimer(vars+0x21E)) {
                moby_set_state(moby,2,1);
                W(vars,0x220)=0;
                if (W(vars,0x218)<300) W(vars,0x218)=math_random_int_range(480,600);
            }
        }
        idleTarget=P(vars,0x200);
        moby_start_effect_from_entry(moby,mat_fast_helper_a(F(idleTarget,0x10)-F(moby,0x10),F(idleTarget,0x14)-F(moby,0x14)));
        break;
    }
    case 1:
        if ((W(vars,0x2FC)==1 || W(vars,0x2F8)==1) && B(moby,0x20)!=11) {
            moby_set_state(moby,7,2);
            if (B(moby,0x43)!=2) anim_start_blended(moby,2,0,10);
        }
        break;
    case 2:
    {
        char *attackTarget;
        if (!W(vars,0x310) && ((GrelbinContext *)g_hero_state)->mode!=0x31) {
            P(vars,0x314)=cam_alloc_override_slot(5);
            F(P(vars,0x314),0)=10.0f;
            F(P(vars,0x314),4)=0.1f;
            W(P(vars,0x314),0xC)=0;
            W(vars,0x310)=1;
        }
        attackTarget=P(vars,0x200);
        moby_start_effect_from_entry(moby,mat_fast_helper_a(F(attackTarget,0x10)-F(moby,0x10),F(attackTarget,0x14)-F(moby,0x14)));
        if (B(moby,0x20)!=4) math_step_value_toward_target(moby+0x18,vars+0x2D4,F(vars,0x2D0),0.003888888983f,0.003888888983f,0.7000000477f);
        if (B(moby,0x20)!=4 && B(moby,0x20)!=11) {
            if (vec_distance_xy(moby+0x10,((GrelbinContext *)g_hero_state)->position)<12.0f) F(vars,0x2D0)=F(vars,0x2D8)-10.0f;
            else if (vec_distance_xy(moby+0x10,((GrelbinContext *)g_hero_state)->position)<26.0f) F(vars,0x2D0)=F(vars,0x2D8)-7.0f;
            else F(vars,0x2D0)=F(vars,0x2D8)-4.0f;
        }
        if (W(vars,0x2FC)!=1 && W(vars,0x2F8)!=1 && B(moby,0x20)!=4 && B(moby,0x20)!=7 && B(moby,0x20)!=8 && B(moby,0x20)!=9 && B(moby,0x20)!=11) {
            moby_set_state(moby,2,1);
            if (B(moby,0x43)!=1) anim_start_blended(moby,1,0,10);
        }
        break;
    }
    case 4:
    {
        char *dyingTarget;
        dyingTarget=P(vars,0x200);
        moby_start_effect_from_entry(moby,mat_fast_helper_a(F(dyingTarget,0x10)-F(moby,0x10),F(dyingTarget,0x14)-F(moby,0x14)));
        if (B(moby,0x20)!=4) math_step_value_toward_target(moby+0x18,vars+0x2D4,F(vars,0x2D0),0.3888888955f,0.3888888955f,0.7000000477f);
        /* fall through */
    }
    case 3:
        if (B(moby,0x60)&2) {SetDeathBits(moby,0,3);moby_mark_spawned(moby);return;}
    {
    char *childState;
    if (F(vars,0x20)<=0.0f && math_is_value_within_step(moby,45.0f) && !(g_trigger_active_table.entries[(s16)(flags=H(moby,0xB2))])) {
        int counts=g_moby_nibble_table[((s16)flags>>1)+(g_current_map_index<<10)];
        if (!((flags&1) ? (counts>>4)&7 : counts&7)) {
            spawnedActor=CreateMoby(0x1266 /* moby class 4710 */);
            if (spawnedActor) {
                u16 id=H(moby,0xB2);
                if (id&1) {
                    u8 *marks=g_moby_nibble_table+(((s16)id>>1)+(g_current_map_index<<10));
                    if (((*marks>>4)&7)!=7) *marks+=0x10;
                } else {
                    u8 *marks=g_moby_nibble_table+(((s16)id>>1)+(g_current_map_index<<10));
                    if ((*marks&7)!=7) *marks+=1;
                }
                B(spawnedActor,0x23)=0x50;
                H(spawnedActor,0x34)|=0x800;
                B(spawnedActor,0x30)=0xFF; H(spawnedActor,0x32)=0xFF; B(spawnedActor,0x31)=1;
                B(spawnedActor,0x20)=0; B(spawnedActor,0xBC)=0;
                qcopy(spawnedActor+0x10,P(vars,0x2F0)+0x10);
                F(spawnedActor,0x18)+=1.0f;
                func_002A0F48(spawnedActor);hero_copy_field_to_moby(spawnedActor);
                childState=P(spawnedActor,0x68); F(childState,0)=0.1f;
                anim_start_blended(spawnedActor,1,0,20);
                F(spawnedActor,0x48)=F(childState,0)+F(childState,0);B(spawnedActor,0x20)=2;
            }
        }
    }
    }
        break;
    }
    switch (B(moby,0x20)) {
    case 4:
    {
        char *newActor;
        if (moby_get_anim_value(moby)>=4.0f && !W(vars,0x304) && !B(moby,0x42)) {
            char *shake=g_hero_l19_state_block;
            int j;
            F(shake,0x160)=0.25f;
            W(shake,0x168)=0x26;W(shake,0x16C)=0;
            H(moby,0x34)=(H(moby,0x34)&0xFFBE)|0x1000;
            W(moby,0x98)=W(P(moby,0x24),0x10);W(vars,0x304)=1;
            for (j=0;j<5;j++) {
                char *effect,*src;
                vec_random_direction(burst_vel,0.2833333611f,0.3500000238f);
                burst_vel[2]=math_fabs(burst_vel[2])*6.5f;
                if (burst_vel[2]>1.2500001192f) burst_vel[2]=1.2500001192f;
                FastVecAdd(burst_vel,burst_vel,g_particle_effect_template);
                src=P(vars,0x2F0);
                effect=cam_moby_create(src,1,S(src,0xAA),j,src+0x10,src+0xF0,burst_vel,0xFF,180.0f,45.0f);
                P(effect,0x64)=(char *)moby_fade_out_update;
            }
            newActor=CreateMoby(0x1208 /* moby class 4616 */);
            if (newActor) {
                moby_init_child_from_parent(newActor,P(vars,0x2F0));
                H(newActor,0x32)=H(moby,0x32);B(newActor,0x30)=B(moby,0x30);
                old_child=P(vars,0x2F0);
                {
                    int row;
                    for (row=0;row<4;row++) qcopy_nc(newActor+0xC0+row*16,old_child+0xC0+row*16);
                }
                moby_mark_spawned(P(vars,0x2F0));P(vars,0x2F0)=newActor;
            }
        }
        if (B(moby,0x60)&2) {
            F(vars,0x2D0)=F(vars,0x2D8)-7.0f;
            moby_set_state(moby,7,-1);
            if (B(moby,0x43)!=2) anim_start_blended(moby,2,0,10);
        }
        break;
    }
    case 2:
        if (B(moby,0x60)&2) {
            count=B(moby,0x43);
            if (count!=math_random_int_below(2)+3) anim_start_blended(moby,math_random_int_below(2)+3,0,2);
            moby_set_state(moby,3,-1);
        }
        break;
    case 3:
        if (B(moby,0x60)&2) {
            if (B(moby,0x43)!=1) anim_start_blended(moby,1,0,4);
            moby_set_state(moby,2,-1);
        }
        break;
    case 5:
        if (B(moby,0x60)&2) {
            moby_set_state(moby,7,-1);
            if (B(moby,0x43)!=2) anim_start_blended(moby,2,0,6);
        }
        break;
    case 7:
        if (math_is_value_within_step(moby,13.0f)) PlayMobySound(4,0,moby);
        if (moby_get_anim_value(moby)>17.0f && B(moby,0x42)==2) {
            F(moby,0x48)=0.5f;gfx_add_draw_callback_first(leviathan_draw_charge_flash,moby);
            if (B(moby,0x60)&2) {
                qcopy(vars+0x2E0,vars+0x1F0);
                moby_set_state(moby,8,-1);
                if (B(moby,0x43)!=4) anim_start_blended(moby,4,20,20);
            }
        }
        break;
    case 8:
        gfx_add_draw_callback_first(part_emit_beam_muzzle_glow,moby);
        if (F(vars,0x22C)>=1.0f) {PlayMobySound(3,0,moby);moby_set_state(moby,9,-1);}
        break;
    case 9:
    {
        char *particle;
        gfx_add_draw_callback_first(DrawGrelbinBeamEffect,moby);
        qcopy(burst_vel,g_hit_position_vec);
        for (i=9;i>=0;i--) {
            part_spawn_random_direction_effect(particle_vel,0.2333333492f,0.2666666806f);
            if (particle_vel[2]<0.0f) particle_vel[2]=-particle_vel[2];
            count=FloatToInt(math_random_signed_float_range(2.0f,5.0f));
            size_scale=math_random_float_range(0.6f,1.0f);
            part_spawn_fading_drift(vars+0x2C0,particle_vel,20,0x804020,count,127,127,210000.0f*size_scale,2100.0f,0.00405555591f,g_leviathan_particle_param);
            count=FloatToInt(math_random_signed_float_range(2.0f,5.0f));
            size_scale=math_random_float_range(0.6f,1.0f);
            particle=part_spawn_fading_drift(vars+0x2C0,particle_vel,20,0x804040,count,48,48,630000.0f*size_scale,4200.0f,0.00405555591f,0);
            if (particle) {
                char *g=g_leviathan_data;
                B(particle,2)=B(P(g,0xD4),0);
            }
        }
        make_hit_descriptor(hit_matrix,moby,0x10001,g_particle_effect_template,(float)B(vars,0x34));
        moby_transform_joint_point(moby,0,body_matrix);
        qcopy(particle_vel,body_matrix+0x30);
        vec_scale_to_length(offset,body_matrix,0.25f);
        FastVecAdd(particle_vel,particle_vel,offset);
        FastVecSub(delta,vars+0x2E0,particle_vel);
        vec_scale_to_length(delta,delta,F(vars,0x238)*60.0f);
        FastVecAdd(delta,delta,particle_vel);
        CollLine(particle_vel,delta,0,moby,hit_matrix);
        if (H(moby,0x96)>40) {
            F(vars,0x234)-=0.05f;
            if (F(vars,0x234)<=0.0f) {
                F(vars,0x22C)=0.0f;F(vars,0x230)=1.0f;F(vars,0x228)=0.1f;F(vars,0x234)=0.1f;F(vars,0x238)=0.1f;
                moby_set_state(moby,10,-1);
                if (B(moby,0x43)!=3) anim_start_blended(moby,3,0,10);
            }
        } else {
            F(vars,0x234)+=0.1f;if (F(vars,0x234)>1.0f) F(vars,0x234)=1.0f;
            F(vars,0x238)+=0.2f;if (F(vars,0x238)>1.0f) F(vars,0x238)=1.0f;
        }
        break;
    }
    case 10:
        if (B(moby,0x60)&2) {
            moby_set_state(moby,7,-1);
            if (B(moby,0x43)!=2) anim_start_blended(moby,2,0,10);
        }
        break;
    case 11:
    {
        char *finalTarget;
        finalTarget=P(vars,0x200);
        if (finalTarget && S(finalTarget,0xAA)==MOBY_CLASS_YETI) moby_start_effect_from_entry(P(vars,0x200),mat_fast_helper_a(F(moby,0x10)-F(finalTarget,0x10),F(moby,0x14)-F(finalTarget,0x14)));
        if (B(moby,0x60)&2) {
            F(vars,0x2D0)=F(vars,0x2D8)-4.0f;
            if (W(vars,0x2FC)!=1 && W(vars,0x2F8)!=1) {
                moby_set_state(moby,7,2);
                if (B(moby,0x43)!=2) anim_start_blended(moby,2,0,10);
            } else {
                moby_set_state(moby,2,1);
                if (B(moby,0x43)!=1) anim_start_blended(moby,1,0,10);
            }
        }
        if (math_is_value_within_step(moby,11.0f) && B(moby,0x42)==6) {
            GrelbinContext *ctx;
            char *next;
            char *dead=P(vars,0x200);
            --g_active_yeti_count;
            moby_mark_spawned(dead);
            ctx=(GrelbinContext *)g_hero_state;
            next=ctx->target;
            W(vars,0x204)=1;
            P(vars,0x200)=next;
            qcopy(vars+0x1F0,ctx->savedPosition);
        }
        break;
    }
    }
    moby_tick_timers_age(moby);
}

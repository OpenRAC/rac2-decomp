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
extern char D_L19_001A8F20[] MACRO_ADDR;
extern char D_L19_001BFEA0[], D_L19_001B9900[];
extern char D_L19_001FF5C0[];
typedef struct { char pad[0x464]; u8 entries[1]; } ActorFlags;
extern ActorFlags D_L19_0021EA30;
extern char *D_L19_001FB5A0[];
extern char *g_moby_l19_array __attribute__((sda));
extern void moby_fade_out_update(void *);
extern int D_L19_001B1BF8 __attribute__((sda));
extern int g_active_yeti_count __attribute__((sda));
extern int g_current_map_index MACRO_ADDR;
extern unsigned char D_0019B4A8[];
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
extern void func_US2_002A7AA8(void *,int,int);
extern void moby_mark_spawned(void *);
extern int func_US2_002AF9C8(void *,float);
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

void func_US2_L19_004173C0(char *obj)
{
    float v[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    char mat[0x30] __attribute__((aligned(16)));
    char mat2[0x40] __attribute__((aligned(16)));
    float tmp[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    char *q;
    char *s;
    char *spawnedActor=0;
    int ok,i=0,n=0;
    float f=0.0f;
    u16 flags;

    if (((GrelbinContext *)g_hero_state)->mode == 0x6F) return;
    if (!moby_is_in_selected_zone(obj+0x10)) {
        B(obj,0x30)=FloatToInt((float)S(obj,0x32)+15.0f);
        return;
    }
    s=P(obj,0x68);
    if (H(obj,0x34)&0x80) {
        char *child=P(s,0x2F0);
        if (child) H(child,0x34)|=0x80;
    } else {
        char *child=P(s,0x2F0);
        if (child) H(child,0x34)&=0xFF7F;
    }
    if ((unsigned)(B(obj,0x95)-2)>=2 || ((GrelbinContext *)g_hero_state)->mode==0x31 || F(s,0x20)<=0.0f) {
        if (W(s,0x310)) { cam_end_override(P(s,0x314)); W(s,0x310)=0; }
    }
    if (leviathan_update_helper(obj)) {
        if (W(s,0x310)) {cam_end_override(P(s,0x314)); W(s,0x310)=0;}
        moby_mark_spawned(obj);
        return;
    }
    switch (B(obj,0x95)) {
    case 0:
    {
        char *idleTarget;
        ok=1;
        if (B(obj,0x21)!=0xFF && D_L19_001FB5A0[B(obj,0x21)]) {
            if (moby_count_group_not_in_state(W(s,0x308),-1)) ok=0;
        }
        if (W(s,0x30C)!=-1) {
            idleTarget=g_moby_l19_array+(W(s,0x30C)<<8);
            if (idleTarget && B(idleTarget,0x20)!=0xFE && B(idleTarget,0x20)!=0xFD) ok=0;
        }
        if (ok) {
            if (W(s,0x2FC)==1) {
                moby_set_state(obj,4,2);
                if (B(obj,0x43)) anim_start_blended(obj,0,0,10);
            } else if (W(s,0x220) && FastDecTimer(s+0x21E)) {
                moby_set_state(obj,2,1);
                W(s,0x220)=0;
                if (W(s,0x218)<300) W(s,0x218)=math_random_int_range(480,600);
            }
        }
        idleTarget=P(s,0x200);
        moby_start_effect_from_entry(obj,mat_fast_helper_a(F(idleTarget,0x10)-F(obj,0x10),F(idleTarget,0x14)-F(obj,0x14)));
        break;
    }
    case 1:
        if ((W(s,0x2FC)==1 || W(s,0x2F8)==1) && B(obj,0x20)!=11) {
            moby_set_state(obj,7,2);
            if (B(obj,0x43)!=2) anim_start_blended(obj,2,0,10);
        }
        break;
    case 2:
    {
        char *attackTarget;
        if (!W(s,0x310) && ((GrelbinContext *)g_hero_state)->mode!=0x31) {
            P(s,0x314)=cam_alloc_override_slot(5);
            F(P(s,0x314),0)=10.0f;
            F(P(s,0x314),4)=0.1f;
            W(P(s,0x314),0xC)=0;
            W(s,0x310)=1;
        }
        attackTarget=P(s,0x200);
        moby_start_effect_from_entry(obj,mat_fast_helper_a(F(attackTarget,0x10)-F(obj,0x10),F(attackTarget,0x14)-F(obj,0x14)));
        if (B(obj,0x20)!=4) math_step_value_toward_target(obj+0x18,s+0x2D4,F(s,0x2D0),0.003888888983f,0.003888888983f,0.7000000477f);
        if (B(obj,0x20)!=4 && B(obj,0x20)!=11) {
            if (vec_distance_xy(obj+0x10,((GrelbinContext *)g_hero_state)->position)<12.0f) F(s,0x2D0)=F(s,0x2D8)-10.0f;
            else if (vec_distance_xy(obj+0x10,((GrelbinContext *)g_hero_state)->position)<26.0f) F(s,0x2D0)=F(s,0x2D8)-7.0f;
            else F(s,0x2D0)=F(s,0x2D8)-4.0f;
        }
        if (W(s,0x2FC)!=1 && W(s,0x2F8)!=1 && B(obj,0x20)!=4 && B(obj,0x20)!=7 && B(obj,0x20)!=8 && B(obj,0x20)!=9 && B(obj,0x20)!=11) {
            moby_set_state(obj,2,1);
            if (B(obj,0x43)!=1) anim_start_blended(obj,1,0,10);
        }
        break;
    }
    case 4:
    {
        char *dyingTarget;
        dyingTarget=P(s,0x200);
        moby_start_effect_from_entry(obj,mat_fast_helper_a(F(dyingTarget,0x10)-F(obj,0x10),F(dyingTarget,0x14)-F(obj,0x14)));
        if (B(obj,0x20)!=4) math_step_value_toward_target(obj+0x18,s+0x2D4,F(s,0x2D0),0.3888888955f,0.3888888955f,0.7000000477f);
        /* fall through */
    }
    case 3:
        if (B(obj,0x60)&2) {func_US2_002A7AA8(obj,0,3);moby_mark_spawned(obj);return;}
    {
    char *childState;
    if (F(s,0x20)<=0.0f && func_US2_002AF9C8(obj,45.0f) && !(D_L19_0021EA30.entries[(s16)(flags=H(obj,0xB2))])) {
        int counts=D_0019B4A8[((s16)flags>>1)+(g_current_map_index<<10)];
        if (!((flags&1) ? (counts>>4)&7 : counts&7)) {
            spawnedActor=CreateMoby(0x1266);
            if (spawnedActor) {
                u16 id=H(obj,0xB2);
                if (id&1) {
                    u8 *marks=D_0019B4A8+(((s16)id>>1)+(g_current_map_index<<10));
                    if (((*marks>>4)&7)!=7) *marks+=0x10;
                } else {
                    u8 *marks=D_0019B4A8+(((s16)id>>1)+(g_current_map_index<<10));
                    if ((*marks&7)!=7) *marks+=1;
                }
                B(spawnedActor,0x23)=0x50;
                H(spawnedActor,0x34)|=0x800;
                B(spawnedActor,0x30)=0xFF; H(spawnedActor,0x32)=0xFF; B(spawnedActor,0x31)=1;
                B(spawnedActor,0x20)=0; B(spawnedActor,0xBC)=0;
                qcopy(spawnedActor+0x10,P(s,0x2F0)+0x10);
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
    switch (B(obj,0x20)) {
    case 4:
    {
        char *newActor;
        if (moby_get_anim_value(obj)>=4.0f && !W(s,0x304) && !B(obj,0x42)) {
            char *shake=D_L19_001B9900;
            int j;
            F(shake,0x160)=0.25f;
            W(shake,0x168)=0x26;W(shake,0x16C)=0;
            H(obj,0x34)=(H(obj,0x34)&0xFFBE)|0x1000;
            W(obj,0x98)=W(P(obj,0x24),0x10);W(s,0x304)=1;
            for (j=0;j<5;j++) {
                char *effect,*src;
                vec_random_direction(v,0.2833333611f,0.3500000238f);
                v[2]=math_fabs(v[2])*6.5f;
                if (v[2]>1.2500001192f) v[2]=1.2500001192f;
                FastVecAdd(v,v,D_L19_001A8F20);
                src=P(s,0x2F0);
                effect=cam_moby_create(src,1,S(src,0xAA),j,src+0x10,src+0xF0,v,0xFF,180.0f,45.0f);
                P(effect,0x64)=(char *)moby_fade_out_update;
            }
            newActor=CreateMoby(0x1208);
            if (newActor) {
                moby_init_child_from_parent(newActor,P(s,0x2F0));
                H(newActor,0x32)=H(obj,0x32);B(newActor,0x30)=B(obj,0x30);
                q=P(s,0x2F0);
                {
                    int row;
                    for (row=0;row<4;row++) qcopy_nc(newActor+0xC0+row*16,q+0xC0+row*16);
                }
                moby_mark_spawned(P(s,0x2F0));P(s,0x2F0)=newActor;
            }
        }
        if (B(obj,0x60)&2) {
            F(s,0x2D0)=F(s,0x2D8)-7.0f;
            moby_set_state(obj,7,-1);
            if (B(obj,0x43)!=2) anim_start_blended(obj,2,0,10);
        }
        break;
    }
    case 2:
        if (B(obj,0x60)&2) {
            n=B(obj,0x43);
            if (n!=math_random_int_below(2)+3) anim_start_blended(obj,math_random_int_below(2)+3,0,2);
            moby_set_state(obj,3,-1);
        }
        break;
    case 3:
        if (B(obj,0x60)&2) {
            if (B(obj,0x43)!=1) anim_start_blended(obj,1,0,4);
            moby_set_state(obj,2,-1);
        }
        break;
    case 5:
        if (B(obj,0x60)&2) {
            moby_set_state(obj,7,-1);
            if (B(obj,0x43)!=2) anim_start_blended(obj,2,0,6);
        }
        break;
    case 7:
        if (func_US2_002AF9C8(obj,13.0f)) PlayMobySound(4,0,obj);
        if (moby_get_anim_value(obj)>17.0f && B(obj,0x42)==2) {
            F(obj,0x48)=0.5f;gfx_add_draw_callback_first(leviathan_draw_charge_flash,obj);
            if (B(obj,0x60)&2) {
                qcopy(s+0x2E0,s+0x1F0);
                moby_set_state(obj,8,-1);
                if (B(obj,0x43)!=4) anim_start_blended(obj,4,20,20);
            }
        }
        break;
    case 8:
        gfx_add_draw_callback_first(part_emit_beam_muzzle_glow,obj);
        if (F(s,0x22C)>=1.0f) {PlayMobySound(3,0,obj);moby_set_state(obj,9,-1);}
        break;
    case 9:
    {
        char *particle;
        gfx_add_draw_callback_first(DrawGrelbinBeamEffect,obj);
        qcopy(v,D_L19_001BFEA0);
        for (i=9;i>=0;i--) {
            part_spawn_random_direction_effect(vel,0.2333333492f,0.2666666806f);
            if (vel[2]<0.0f) vel[2]=-vel[2];
            n=FloatToInt(math_random_signed_float_range(2.0f,5.0f));
            f=math_random_float_range(0.6f,1.0f);
            part_spawn_fading_drift(s+0x2C0,vel,20,0x804020,n,127,127,210000.0f*f,2100.0f,0.00405555591f,D_L19_001B1BF8);
            n=FloatToInt(math_random_signed_float_range(2.0f,5.0f));
            f=math_random_float_range(0.6f,1.0f);
            particle=part_spawn_fading_drift(s+0x2C0,vel,20,0x804040,n,48,48,630000.0f*f,4200.0f,0.00405555591f,0);
            if (particle) {
                char *g=D_L19_001FF5C0;
                B(particle,2)=B(P(g,0xD4),0);
            }
        }
        make_hit_descriptor(mat,obj,0x10001,D_L19_001A8F20,(float)B(s,0x34));
        moby_transform_joint_point(obj,0,mat2);
        qcopy(vel,mat2+0x30);
        vec_scale_to_length(tmp,mat2,0.25f);
        FastVecAdd(vel,vel,tmp);
        FastVecSub(delta,s+0x2E0,vel);
        vec_scale_to_length(delta,delta,F(s,0x238)*60.0f);
        FastVecAdd(delta,delta,vel);
        CollLine(vel,delta,0,obj,mat);
        if (H(obj,0x96)>40) {
            F(s,0x234)-=0.05f;
            if (F(s,0x234)<=0.0f) {
                F(s,0x22C)=0.0f;F(s,0x230)=1.0f;F(s,0x228)=0.1f;F(s,0x234)=0.1f;F(s,0x238)=0.1f;
                moby_set_state(obj,10,-1);
                if (B(obj,0x43)!=3) anim_start_blended(obj,3,0,10);
            }
        } else {
            F(s,0x234)+=0.1f;if (F(s,0x234)>1.0f) F(s,0x234)=1.0f;
            F(s,0x238)+=0.2f;if (F(s,0x238)>1.0f) F(s,0x238)=1.0f;
        }
        break;
    }
    case 10:
        if (B(obj,0x60)&2) {
            moby_set_state(obj,7,-1);
            if (B(obj,0x43)!=2) anim_start_blended(obj,2,0,10);
        }
        break;
    case 11:
    {
        char *finalTarget;
        finalTarget=P(s,0x200);
        if (finalTarget && S(finalTarget,0xAA)==0x10D0) moby_start_effect_from_entry(P(s,0x200),mat_fast_helper_a(F(obj,0x10)-F(finalTarget,0x10),F(obj,0x14)-F(finalTarget,0x14)));
        if (B(obj,0x60)&2) {
            F(s,0x2D0)=F(s,0x2D8)-4.0f;
            if (W(s,0x2FC)!=1 && W(s,0x2F8)!=1) {
                moby_set_state(obj,7,2);
                if (B(obj,0x43)!=2) anim_start_blended(obj,2,0,10);
            } else {
                moby_set_state(obj,2,1);
                if (B(obj,0x43)!=1) anim_start_blended(obj,1,0,10);
            }
        }
        if (func_US2_002AF9C8(obj,11.0f) && B(obj,0x42)==6) {
            GrelbinContext *ctx;
            char *next;
            char *dead=P(s,0x200);
            --g_active_yeti_count;
            moby_mark_spawned(dead);
            ctx=(GrelbinContext *)g_hero_state;
            next=ctx->target;
            W(s,0x204)=1;
            P(s,0x200)=next;
            qcopy(s+0x1F0,ctx->savedPosition);
        }
        break;
    }
    }
    moby_tick_timers_age(obj);
}

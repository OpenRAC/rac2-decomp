#include "include_asm.h"

#include "common.h"
extern void get_moby_color(void *, int *, int *, int *);
extern void moby_set_state(void *, int, int);
extern float vec_distance_xy(void *, void *);
extern int TryClaimNotice(int, int, int);
extern int hero_is_allowed_for_mode(int);
extern int PlayMobySound(int, int, void *);
extern float FastAddRotations(float, float);
extern void hero_start_target_state(void *, int, float);
extern int coll_sweep_from_object(void *, void *, int, int, int, int, float, float, float);
extern int flag_is_third_pending_set(void *);
extern int hero_get_target_state_kind(void);
extern s32 hero_l03_set_move_state_us2(int, int);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void hero_start_loader_state(int);
extern int flag_set_first_pending(void *);
extern float ApproachValue(void *, float, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float coll_probe_ground_height_below(void *, int, float);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void cam_reset_entry(int);
extern void vec_scale_to_length(void *, void *, float);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern int FastTweenColor(int, int, float);
extern void set_moby_color(void *, int, int, int);
extern int math_random_int_below(int);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern void vec_clear_128(void *);
extern float IntToFloat(int);
extern void FastVecAdd(void *, void *, void *);
extern void *part_spawn_hero_relative(void *, void *, int, float, unsigned char, unsigned char, int);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void tube_start_draw_effect(void *);
typedef struct {
    char pad00[0x80];
    float position[4];
    char pad90[0x60];
    float velocity[4];
    char pad100[0x23C];
    char *interaction;
    int interactionActive;
    char pad344[0x1CDC];
    float scale[3];
    char pad202C[0x28B];
    unsigned char interactionLock;
    char pad22B8[0x248];
    unsigned short transform;
} PlayerState;
extern PlayerState g_hero_state;
extern unsigned char g_tube_start_flags[];
extern int g_pad_held_flags[];
extern char *g_linked_effect_records MACRO_ADDR;
extern float g_tube_start_spin_rate __attribute__((sda));
extern float g_tube_start_alpha_min __attribute__((sda));
extern float g_tube_start_alpha_max;
extern int g_tube_start_color_pair[2];
extern int D_L03_001B03F0_0 SDATA(D_L03_001B03F0);
extern int g_tube_start_tint_color __attribute__((sda));
extern float g_tube_start_rate __attribute__((sda));
extern float g_tube_start_step __attribute__((sda));
extern float g_tube_start_scale_threshold __attribute__((sda));
#define I(p,o) (*(int *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))

/* Per-frame update of moby class 2437 (Tube Start): lets the player step in, shoots them along the tube and lights up its glow while it is active. */
void tube_start_update_us2(char *moby)
{
    float pos[4], rot[4];
    int red,green,blue;
    char *vars = *(char **)(moby+0x68);
    int i, countdown, color, life, random, tint, tint_b, tint_g;
    float one;
    int packed_green, packed_blue;
    unsigned int timer, old_timer;
    unsigned char life_byte;
    float angle, scale, alpha, speed, step, rate;
    char *basis_row, *scale_cursor, *scale_ptr, *velocity_ptr;
    switch (B(moby,0x20)) {
    case 0:
        get_moby_color(moby,&red,&green,&blue);
        packed_green = (green << 8) | 0x80000000;
        packed_blue = (blue << 16) | packed_green;
        I(vars,0x20) = packed_blue | red;
        if (I(vars,8) && !g_tube_start_flags[0]) {
            I(moby,0x98)=0;
            H(moby,0x34)=(H(moby,0x34)|0x41)&0xEFFF;
            moby_set_state(moby,5,-1);
            B(moby,0x30)=255;
        } else moby_set_state(moby,1,-1);
        break;
    case 1:
        if (g_hero_state.interaction==moby && g_hero_state.interactionActive
            && vec_distance_xy(moby+0x10,g_hero_state.position)<2.0f) {
            TryClaimNotice(8,0x12FB,1);
            if (hero_is_allowed_for_mode(8) && (g_pad_held_flags[0]&0x10)) {
                PlayMobySound(0,0,moby);
                angle=FastAddRotations(F(moby,0xF8),1.57079637f);
                hero_start_target_state(moby+0x10,0,angle);
                coll_sweep_from_object(moby,moby+0x10,0x10000,0,1,0,2.5f,100.0f,1.0f);
                moby_set_state(moby,2,-1);
            }
        } else if (flag_is_third_pending_set(moby)) {
            moby_set_state(moby,5,-1);
            I(moby,0x98)=0;
            H(moby,0x34)=(H(moby,0x34)|0x41)&0xEFFF;
        }
        break;
    case 2:
        g_hero_state.interactionLock=1;
        if (hero_get_target_state_kind()==2) {
            moby_set_state(moby,3,-1);
            hero_l03_set_move_state_us2(0x6F,1);
        } else {
            timer = H(moby,0x96);
            old_timer = timer++;
            H(moby,0x96) = timer;
            if (old_timer < 0xB5) break;
            FastVecSub(pos,g_hero_state.position,moby+0x10);
            if (FastVecDot(pos,g_hero_state.velocity)<0.0f) qzero(g_hero_state.velocity);
            if (H(moby,0x96)>=0x169) {
                moby_set_state(moby,1,-1);
                hero_start_loader_state(0);
            }
        }
        break;
    case 3:
        if (flag_set_first_pending(moby)) { I(vars,0x1C)=0; B(moby,0x30)=255; }
        H(moby,0x96)++;
        g_hero_state.interactionLock=1;
        ApproachValue(vars+0x1C,1.57079649f,0.104719773f);
        g_hero_state.transform=1;
        g_hero_state.scale[0]=g_hero_state.scale[1]=1.0f-math_fast_sin_or_cos_b(F(vars,0x1C));
        g_hero_state.scale[2]=2.0f-math_fast_sin_or_cos_a(F(vars,0x1C));
        if (H(moby,0x96)==0x30) {
            qcopy(pos,g_linked_effect_records+I(vars,0)*128+0x30);
            pos[2]=coll_probe_ground_height_below(pos,0,0.5f);
            qcopy(rot,g_linked_effect_records+I(vars,0)*128+0x70);
            hero_reset_position_and_direction(pos,rot,0,1);
            if (I(vars,0x10)!=-1) cam_reset_entry(I(vars,0x10));
            moby_set_state(moby,4,-1);
        }
        break;
    case 4:
        if (flag_set_first_pending(moby) && I(vars,0xC)) g_tube_start_flags[0]=1;
        ApproachValue(vars+0x1C,0.0f,0.104719773f);
        g_hero_state.transform=1;
        g_hero_state.scale[0]=g_hero_state.scale[1]=1.0f-math_fast_sin_or_cos_b(F(vars,0x1C));
        g_hero_state.scale[2]=2.0f-math_fast_sin_or_cos_a(F(vars,0x1C));
        g_hero_state.interactionLock=1;
        if (F(vars,0x1C)<=0.0f) {
            B(moby,0x30)=B(moby,0x32);
            g_hero_state.interactionLock=0;
            moby_set_state(moby,1,-1);
        }
        break;
    case 5:
        if ((!I(vars,8) && !flag_is_third_pending_set(moby)) || (I(vars,8) && g_tube_start_flags[0])) {
            moby_set_state(moby,6,-1);
            H(moby,0x34)|=0x100;
            basis_row=moby+0xC0; scale_cursor=vars+0x34;
            for (countdown=2;countdown>=0;countdown--) {
                F(scale_cursor,0)=0.02f;
                I(vars,0x18)=0;
                vec_scale_to_length(basis_row,basis_row,F(scale_cursor,0)); basis_row+=0x10; scale_cursor+=4;
            }
            H(moby,0x34)=(H(moby,0x34)&0xFFBE)|0x1000;
            I(moby,0x98)=I(*(char **)(moby+0x24),0x10);
        }
        break;
    case 6:
        step=g_tube_start_step*0.000277777785f;
        rate=g_tube_start_rate*0.0166666675f;
        if (flag_set_first_pending(moby)) PlayMobySound(1,0,moby);
        scale_cursor=vars+0x34;
        one=1.0f;
        i=0; basis_row=moby+0xC0; velocity_ptr=vars+0x24; scale_ptr=scale_cursor;
        for (;i<3;i++,basis_row+=16,velocity_ptr+=4,scale_ptr+=4,scale_cursor+=4) {
            if (F(scale_cursor,0)<one && (!i || F(scale_cursor,-4)>g_tube_start_scale_threshold)) {
                math_step_value_toward_target(scale_ptr,velocity_ptr,1.0f,step,step,rate);
                if (F(scale_cursor,0)>one) F(scale_cursor,0)=one;
                vec_scale_to_length(basis_row,basis_row,F(scale_cursor,0));
            }
        }
        if (F(vars,0x34)>=1.0f && F(vars,0x38)>=1.0f && F(vars,0x3C)>=1.0f) moby_set_state(moby,1,-1);
        tint=FastTweenColor(g_tube_start_tint_color,I(vars,0x20),F(vars,0x3C));
        tint_b=(tint>>16)&255;
        tint_g=(tint>>8)&255;
        set_moby_color(moby,tint&255,tint_g,tint_b);
        break;
    }
    if (B(moby,0x20)<5) {
        F(vars,0x30)=FastAddRotations(F(vars,0x30),g_tube_start_spin_rate*0.000290888245f);
        if (F(vars,0x18)<1.0f) ApproachValue(vars+0x18,1.0f,0.0333333351f);
        if (math_random_int_below(2)) {
            angle=math_random_angle();
            pos[0]=math_fast_sin_or_cos_a(angle)*0.85f;
            pos[1]=math_fast_sin_or_cos_b(angle)*0.85f;
            pos[2]=0;
            FastVecAdd(pos,pos,moby+0x10);
            pos[2]+=0.1f;
            alpha=math_random_float_range(g_tube_start_alpha_min,g_tube_start_alpha_max);
            scale=math_random_float_range(0,1);
            color=FastTweenColor(D_L03_001B03F0_0,g_tube_start_color_pair[1],scale);
            speed=math_random_float_range(2,3);
            life=math_random_int_range(60,180);
            life_byte = life;
            vec_clear_128(rot);
            rot[2]=speed/IntToFloat(life);
            random=math_random_int_below(255);
            part_spawn_hero_relative(pos,rot,color,alpha,life_byte,random&255,0);
        }
        gfx_add_draw_callback_first(tube_start_draw_effect,moby);
    }
}

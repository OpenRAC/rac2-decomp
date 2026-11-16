#include "common.h"

/* func_PAL_L00_003BCEB8, the PAL copy of func_L00_003B9310: the same C, where the
   delay tunings are scaled to 50 Hz (D_L00_001AFCE4 is a word here), a scaled timer is
   stored after its neighbours (the division's trap holds stores back), the two turn
   rates are multiplied by 1.44f, and the thresholds 16 and 10 become 13 and 8. */

/* The tuning words are one object in two addressing forms (MACRO_ADDR): a read before a  store of the same word keeps its order. The target is the last parameter of func_L00_003B8E58: integer and FP banks are separate. */

#define I(p,o) (*(int *)((char *)(p)+(o)))
#define S(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(unsigned char **)((char *)(p)+(o)))

typedef struct { float v[4]; } AimVector __attribute__((aligned(16)));
typedef struct {
    unsigned char pad0[0x1d8];
    int f1d8;
    unsigned char pad1dc[0x4];
    short f1e0;
    unsigned char pad1e2[0x15e];
    int f340;
    unsigned char pad344[0xa];
    short f34e;
    unsigned char pad350[0x8a8];
    unsigned char * fbf8;
    unsigned char padbfc[0x634];
    int f1230;
    unsigned char pad1234[0xc];
    int f1240;
    unsigned char pad1244[0x104c];
    unsigned char * f2290;
    int f2294;
    unsigned char pad2298[0x1c];
    unsigned char f22b4;
    unsigned char pad22b5[0x3];
    unsigned char f22b8;
    unsigned char pad22b9[0x3];
    unsigned char f22bc;
    unsigned char pad22bd[0x22f];
    short f24ec;
} AimHero;
extern AimHero g_hero_state;
extern unsigned char g_sound_state[];
typedef struct { unsigned char pad0[0x1a0]; int held, pressed; } AimController;
extern AimController g_pad_state;
typedef struct {
    unsigned char pad0[0x60];
    float pitch, f64, yaw;
    unsigned char pad6c[0x14];
} AimAngles;
typedef struct {
    unsigned char pad0[0x1924];
    float pitch, yaw;
} AimAlternateAngles;
extern AimAngles g_target_lock_aim_angles;
extern AimAlternateAngles g_hero_item_attach_records;
extern AimVector g_camera_l00_position, g_cam_follow_matrix;
typedef struct { unsigned char pad0[0x18]; unsigned char *hit; } AimCollision;
extern AimCollision g_collision_result;
typedef struct {
    unsigned char *target;
    short targetId, delay;
    union { int bits; float value; } height;
    unsigned char *candidate;
    int timer, special, mode;
    unsigned char pad1c[4];
    AimVector origin, direction;
    union { int bits; float value; } charge;
    int charge2, held, handle;
} AimState;
extern AimState *g_target_lock_aim_state __attribute__((sda));
extern int g_target_lock_timer __attribute__((sda));
extern int g_target_lock_disabled __attribute__((sda));
extern int g_target_lock_delay __attribute__((sda));
extern float g_target_lock_range MACRO_ADDR, g_target_lock_cone MACRO_ADDR;
extern float ref_L00_003B9310_02 __attribute__((sda));
extern float ref_L00_003B9310_03 __attribute__((sda));
extern void mem_clear(void *,int,int);
extern void moby_collect_special_into_table(void),moby_save_and_clear_values(void),moby_restore_saved_values(void);
extern void FastVecScale(void *,void *,float),FastVecAdd(void *,void *,void *);
extern int FastDecTimer(short *);
extern void moby_transform_joint_to_world(void *,int,void *);
extern unsigned char *moby_get_private_value_0(void *);
extern unsigned char *SelectCurrentOrPreferredTarget(void *,void *,float,float,float,float,float,void *);
extern int CollLine(void *,void *,int,void *,int),math_fast_float_d(int *);
extern float vec_distance_xy(void *,void *),fast_vec_dist(void *,void *),math_fabs(float);
extern void snd_stop_voice(int);
extern void hud_add_moby_marker(void *,float,unsigned int,void *,int,float,int,float,int);
extern void FastVecSub(void *,void *,void *),vec_scale_to_length(void *,void *,float);
extern void matrix_from_basis_rows(void *,void *),transform_vector(void *,void *,void *);
extern float mat_fast_helper_a(float,float),FastAddRotations(float,float),vec_length_xy(void *);
extern void moby_update_eased_node(void *,void *,int,float,float);
extern s32 hero_l00_set_action_pal(int,int);
extern void start_equipped_item_animation_pal(void),cancel_hero_item_animation_pal(void),gfx_add_draw_callback_first(void (*)(void),void *);
extern void target_tether_draw_beam_pal(void);
extern int PlayMobySound(int,int,void *);

/* Handles the targeting and lock-on beam of the player's grabbing tool. It picks targets, tracks
 * them, aims the tool and handles the charge sound and button. (PAL: 50 Hz timings) */
void target_lock_on_update_pal(unsigned char *object,AimState *state)
{
    AimVector target, origin, direction, temp;
    unsigned char matrix[64] __attribute__((aligned(16)));
    unsigned char *candidate, *old, *entry;
    float range, cone, angle;
    int initialized=state->mode;
    g_target_lock_aim_state=state;
    if (!initialized) {
        state->targetId=-1;
        state->charge.bits=0; state->charge2=0; state->target=0;
        state->delay=0; state->height.bits=0; state->special=0;
        state->timer=(g_target_lock_timer * 5 + 2) / 6;
        g_target_lock_disabled=0; state->handle=-1;
        mem_clear(&g_target_lock_aim_angles,0,128);
        state->mode=1;
        moby_collect_special_into_table();
    }
    moby_save_and_clear_values();
    range=g_target_lock_range; cone=g_target_lock_cone;
    g_target_lock_range=35.0f;
    if (g_hero_state.f2294==29 && (U(g_hero_state.f2290,0x34)&1)) {
        qcopy(&state->origin,&g_camera_l00_position); qcopy(&origin,&g_camera_l00_position);
        g_target_lock_cone=0.10471976548433304f; angle=0.0872664749622345f;
        if (!state->special) state->target=0;
        state->special=1;
    } else {
        FastVecScale(&origin,g_hero_state.f2290+0xe0,0.75f);
        FastVecAdd(&origin,(char *)&g_hero_state+0x80,&origin);
        if (g_hero_state.f22b4!=4) moby_transform_joint_to_world(object,1,&state->origin);
        else moby_transform_joint_to_world(g_hero_state.f2290,5,&state->origin);
        angle=0.2617994248867035f; g_target_lock_cone=angle; state->special=0;
    }
    FastDecTimer(&state->delay); old=state->target;
    if (old) {
        unsigned char *descriptor;
        entry=old;
        descriptor=moby_get_private_value_0(entry);
        if (descriptor) {
            FastVecScale(&direction,entry+0xe0,F(descriptor,0x10));
            FastVecAdd(&target,entry+0x10,&direction);
        } else qcopy(&target,entry+0x10);
        if (!old || B(old,0x20)==254 || B(old,0x20)==253 ||
            (descriptor && F(descriptor,0)<=0.0f) || !B(old,0x31) || g_hero_state.f24ec) {
            state->target=0; state->targetId=-1; state->height.bits=0;
        } else g_hero_state.fbf8=old;
    }
    if (state->mode==1 && !g_hero_state.f24ec && !state->delay && !g_target_lock_disabled && !g_hero_state.f1e0) {
        qcopy(&direction,&g_cam_follow_matrix);
        if (g_hero_state.f2294==29) direction.v[2]=0;
        FastVecScale(&state->direction,&direction,1.0f);
        candidate=SelectCurrentOrPreferredTarget(&origin,&direction,angle,cone,range,0.7853982448577881f,0.6108653f,state->target);
        if (!candidate) {
            vec_scale_to_length(&temp,&direction,g_target_lock_range);
            FastVecAdd(&temp,&temp,&origin);
            if (CollLine(&origin,&temp,0,g_hero_state.f2290,0)) {
                unsigned char *hit=g_collision_result.hit;
                if (hit && B(hit,0x20)!=254 && B(hit,0x20)!=253 && S(hit,0xaa)==MOBY_CLASS_RECEIVER_BOT) {
                    entry=P(hit,0x68);
                    if ((B(entry,0x3b1)&0x80) && (F(entry,0x3e4)==0.0f || vec_distance_xy(&origin,object+0x10)<F(entry,0x3e4)))
                        candidate=g_collision_result.hit;
                }
            }
        }
        if (candidate) {
            if (candidate==state->candidate) {
                if (math_fast_float_d(&state->timer)) {
                    unsigned char *newDescriptor;
                    if (state->handle!=-1) {
                        int handle=state->handle;
                        unsigned char *sound=g_sound_state+handle*0x70;
                        if (P(sound,0x88)==object && B(sound,0x74)) snd_stop_voice(handle);
                    }
                    state->target=candidate; state->handle=-1;
                    state->targetId=U(candidate,0xaa); state->height.bits=0; state->delay=(g_target_lock_delay * 5 + 2) / 6;
                    newDescriptor=moby_get_private_value_0(candidate);
                    if (newDescriptor) {
                        state->height.value=F(newDescriptor,0x10);
                        FastVecScale(&temp,state->target+0xe0,F(newDescriptor,0x10));
                        FastVecAdd(&target,state->target+0x10,&temp);
                    } else qcopy(&target,state->target+0x10);
                }
            } else state->timer=(g_target_lock_timer * 5 + 2) / 6;
        } else {
            state->targetId=-1; state->target=0; state->height.bits=0; state->timer=(g_target_lock_timer * 5 + 2) / 6;
        }
        state->candidate=candidate;
    }
    if (g_hero_state.f2294==29) hud_add_moby_marker(object,1.0f,0x600fff0f,0,38,0.0f,-1,90.0f,4);
    if (state->target) {
        float opacity=math_fabs(0.9f-fast_vec_dist(&g_camera_l00_position,&target)*0.006666667f*0.65f);
        hud_add_moby_marker(object,opacity,0xff0fff0f,&target,38,0.0f,-1,90.0f,4);
        FastVecSub(&state->direction,&target,&state->origin);
        vec_scale_to_length(&state->direction,&state->direction,1.0f);
    }
    {
        matrix_from_basis_rows(matrix,object+0xc0);
        transform_vector(&direction,&state->direction,matrix);
        if (g_hero_state.f22b4!=4) {
            g_target_lock_aim_angles.yaw=FastAddRotations(1.5707964f,mat_fast_helper_a(direction.v[0],direction.v[1]));
            g_target_lock_aim_angles.pitch=-mat_fast_helper_a(vec_length_xy(&direction),direction.v[2]);
        } else {
            g_hero_item_attach_records.yaw=mat_fast_helper_a(direction.v[0],direction.v[1]);
            g_hero_item_attach_records.pitch=mat_fast_helper_a(vec_length_xy(&direction),direction.v[2]);
        }
    }
    if (state->mode==1 && g_hero_state.f2294!=28 && g_hero_state.f2294!=49) {
        if (g_hero_state.f2294==1) hero_l00_set_action_pal(29,1);
        if (g_hero_state.f22b4!=4) moby_update_eased_node(object,&g_target_lock_aim_angles,g_hero_state.f22b4==4?5:0,ref_L00_003B9310_02*1.44f,ref_L00_003B9310_03*1.44f);
        if (g_hero_state.f340 && !g_hero_state.f34e && !g_target_lock_disabled && !g_hero_state.f22bc && (g_pad_state.held&g_hero_state.f1230) && (g_hero_state.f1240>=13 || g_hero_state.f22b4==4)) {
            if (!state->held) {
                if (g_hero_state.f22b4!=4) {
                    unsigned char *sound;
                    start_equipped_item_animation_pal(); sound=g_sound_state+state->handle*0x70;
                    if (P(sound,0x88)!=object || !B(sound,0x74)) state->handle=PlayMobySound(0,4,object);
                }
                state->held=1;
            }
            if (g_hero_state.f340 && !g_hero_state.f34e && (g_pad_state.pressed&g_hero_state.f1230)) {
                unsigned char *sound;
                state->charge.bits=0; state->charge2=0;
                sound=g_sound_state+state->handle*0x70;
                if (P(sound,0x88)!=object || !B(sound,0x74)) state->handle=PlayMobySound(0,4,object);
            }
        }
        if (state->charge.value>0.0f || (g_pad_state.held&g_hero_state.f1230) || !g_hero_state.f340 || g_hero_state.f34e)
            gfx_add_draw_callback_first(target_tether_draw_beam_pal,object);
        if (!(g_pad_state.held&g_hero_state.f1230) && (g_hero_state.f1d8>=8 || !g_hero_state.f22b8 || !g_hero_state.f340 || g_hero_state.f34e)) {
            if (state->handle!=-1) {
                int handle=state->handle;
                unsigned char *sound=g_sound_state+handle*0x70;
                if (P(sound,0x88)==object && B(sound,0x74)) snd_stop_voice(handle);
            }
            state->handle=-1;
            if (g_hero_state.f22b4!=4) cancel_hero_item_animation_pal();
            state->held=0;
        }
    }
    moby_restore_saved_values();
}

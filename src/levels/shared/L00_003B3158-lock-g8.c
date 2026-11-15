#include "common.h"

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
extern AimAngles D_L00_0023DB20;
extern AimAlternateAngles D_L00_0025BE10;
extern AimVector g_camera_l00_position, D_L00_001B8FF0;
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
extern AimState *D_L00_001AFD78 __attribute__((sda));
extern int D_L00_001AFCE8 __attribute__((sda));
extern int D_L00_001AFCE0 __attribute__((sda));
extern unsigned short D_L00_001AFCE4 __attribute__((sda));
extern float D_L00_001B28E4 MACRO_ADDR, D_L00_001B28E0 MACRO_ADDR;
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
extern s32 hero_l00_set_action(int,int);
extern void start_equipped_item_animation(void),cancel_hero_item_animation(void),gfx_add_draw_callback_first(void (*)(void),void *);
extern void target_tether_draw_beam(void);
extern int PlayMobySound(int,int,void *);

/* Handles the targeting and lock-on beam of the player's grabbing tool. It picks targets, tracks them, aims the tool and handles the charge sound and button. */
void target_lock_on_update(unsigned char *object,AimState *state)
{
    AimVector target, origin, direction, temp;
    unsigned char matrix[64] __attribute__((aligned(16)));
    unsigned char *candidate, *old, *entry;
    float range, cone, angle;
    int initialized=state->mode;
    D_L00_001AFD78=state;
    if (!initialized) {
        state->targetId=-1; state->timer=D_L00_001AFCE8;
        state->charge.bits=0; state->charge2=0; state->target=0;
        state->delay=0; state->height.bits=0; state->special=0;
        D_L00_001AFCE0=0; state->handle=-1;
        mem_clear(&D_L00_0023DB20,0,128);
        state->mode=1;
        moby_collect_special_into_table();
    }
    moby_save_and_clear_values();
    range=D_L00_001B28E4; cone=D_L00_001B28E0;
    D_L00_001B28E4=35.0f;
    if (g_hero_state.f2294==29 && (U(g_hero_state.f2290,0x34)&1)) {
        qcopy(&state->origin,&g_camera_l00_position); qcopy(&origin,&g_camera_l00_position);
        D_L00_001B28E0=0.10471976548433304f; angle=0.0872664749622345f;
        if (!state->special) state->target=0;
        state->special=1;
    } else {
        FastVecScale(&origin,g_hero_state.f2290+0xe0,0.75f);
        FastVecAdd(&origin,(char *)&g_hero_state+0x80,&origin);
        if (g_hero_state.f22b4!=4) moby_transform_joint_to_world(object,1,&state->origin);
        else moby_transform_joint_to_world(g_hero_state.f2290,5,&state->origin);
        angle=0.2617994248867035f; D_L00_001B28E0=angle; state->special=0;
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
    if (state->mode==1 && !g_hero_state.f24ec && !state->delay && !D_L00_001AFCE0 && !g_hero_state.f1e0) {
        qcopy(&direction,&D_L00_001B8FF0);
        if (g_hero_state.f2294==29) direction.v[2]=0;
        FastVecScale(&state->direction,&direction,1.0f);
        candidate=SelectCurrentOrPreferredTarget(&origin,&direction,angle,cone,range,0.7853982448577881f,0.6108653f,state->target);
        if (!candidate) {
            vec_scale_to_length(&temp,&direction,D_L00_001B28E4);
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
                    state->targetId=U(candidate,0xaa); state->height.bits=0; state->delay=D_L00_001AFCE4;
                    newDescriptor=moby_get_private_value_0(candidate);
                    if (newDescriptor) {
                        state->height.value=F(newDescriptor,0x10);
                        FastVecScale(&temp,state->target+0xe0,F(newDescriptor,0x10));
                        FastVecAdd(&target,state->target+0x10,&temp);
                    } else qcopy(&target,state->target+0x10);
                }
            } else state->timer=D_L00_001AFCE8;
        } else {
            state->targetId=-1; state->timer=D_L00_001AFCE8; state->target=0; state->height.bits=0;
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
            D_L00_0023DB20.yaw=FastAddRotations(1.5707964f,mat_fast_helper_a(direction.v[0],direction.v[1]));
            D_L00_0023DB20.pitch=-mat_fast_helper_a(vec_length_xy(&direction),direction.v[2]);
        } else {
            D_L00_0025BE10.yaw=mat_fast_helper_a(direction.v[0],direction.v[1]);
            D_L00_0025BE10.pitch=mat_fast_helper_a(vec_length_xy(&direction),direction.v[2]);
        }
    }
    if (state->mode==1 && g_hero_state.f2294!=28 && g_hero_state.f2294!=49) {
        if (g_hero_state.f2294==1) hero_l00_set_action(29,1);
        if (g_hero_state.f22b4!=4) moby_update_eased_node(object,&D_L00_0023DB20,g_hero_state.f22b4==4?5:0,ref_L00_003B9310_02,ref_L00_003B9310_03);
        if (g_hero_state.f340 && !g_hero_state.f34e && !D_L00_001AFCE0 && !g_hero_state.f22bc && (g_pad_state.held&g_hero_state.f1230) && (g_hero_state.f1240>=16 || g_hero_state.f22b4==4)) {
            if (!state->held) {
                if (g_hero_state.f22b4!=4) {
                    unsigned char *sound;
                    start_equipped_item_animation(); sound=g_sound_state+state->handle*0x70;
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
            gfx_add_draw_callback_first(target_tether_draw_beam,object);
        if (!(g_pad_state.held&g_hero_state.f1230) && (g_hero_state.f1d8>=10 || !g_hero_state.f22b8 || !g_hero_state.f340 || g_hero_state.f34e)) {
            if (state->handle!=-1) {
                int handle=state->handle;
                unsigned char *sound=g_sound_state+handle*0x70;
                if (P(sound,0x88)==object && B(sound,0x74)) snd_stop_voice(handle);
            }
            state->handle=-1;
            if (g_hero_state.f22b4!=4) cancel_hero_item_animation();
            state->held=0;
        }
    }
    moby_restore_saved_values();
}

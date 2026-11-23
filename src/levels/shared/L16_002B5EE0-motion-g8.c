#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
typedef struct {
    char pad0[0x1B8]; int field1b8;
    char pad1bc[0x160]; float field31c;
    char pad320[0xF00]; int field1220;
    char pad1224[0x16]; u8 field123a;
    char pad123b[0xD]; int field1248;
    char pad124c[0x1048]; int field2294;
    char pad2298[0x1C]; u8 field22b4;
} MotionResident;
extern MotionResident g_hero_state;
#define R ((char *)&D_00189E20)

typedef struct { char pad[0x168]; u16 sentinel; } HudResident;
extern HudResident g_subtitle_history;


extern int g_current_map_index __attribute__((sda));
extern u8 g_follow_state_words[];
extern int g_hero_l16_block_flag;
extern u8 *g_moby_instance_table;
extern float g_follow_speed __attribute__((sda));
extern float g_follow_speed_alt __attribute__((sda));
extern float g_follow_ground_height __attribute__((sda));
extern void cam_compute_view_direction(char *,char *,int);
extern void vec_negate_and_forward(void *,void *,void *);
extern void mat_get_euler_angles(float *,float *);
extern void moby_set_state(u8 *,s32,s32);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int math_fast_float_d(int *);
extern float fast_vec_dist(void *,void *);
extern int subtitle_request_voice_line(int,int);
extern int PadPressedWithin(int,int,int);
extern int moby_is_spot_free_of_blockers(char *);
extern void vec_transform_by_object_or_given(char *,char *,char *,char *);
extern void FastVecSub(void *,void *,void *);
extern float FastVecDot(void *,void *);
extern s32 hero_l16_set_move_state(int,int);
extern void cam_start_blend_to_target(char *);
extern float math_fabs(float);
extern void cam_set_mode_state(int);
extern void hero_switch_push_anim_state(char *);
extern void spinning_object_move_along_ground(char *);
extern void moby_tilt_to_ground_slope(char *);
extern void BlendCameraPose(char *);
extern s32 flag_set_first_pending(u8 *);
/* Updates the moby of class 280: waits for the player to use it, follows the player while active, and bounces to rest when released. */
void follow_player_update(u8 *object)
{
    struct { float position[4],direction[4],forward[4]; } vectors;
#define position vectors.position
#define direction vectors.direction
#define forward vectors.forward
    u8 *state=*(u8 **)(object+0x68);
    u8 *target;
    float value,velocity,zero,ground;
    u8 mode;
    switch (object[0x20]) {
    case 0:
        if (!g_hero_l16_block_flag) return;
        F(object,0x2C)=F(*(u8 **)(object+0x24),0x24);
        cam_compute_view_direction((char *)object+0x10,(char *)position,0);
        *(u16 *)(object+0x34)|=0x100;
        vec_negate_and_forward(object+0xC0,position,0);
        vec_negate_and_forward(object+0xC0,position,0);
        qcopy(state+0x10,object+0x10);
        mat_get_euler_angles((float *)(object+0xC0),(float *)(state+0x20));
        target=g_moby_instance_table+(I(state,4)<<8);
        I(state,0x58)=0;
        if (!target || target[0x20]==254 || target[0x20]==253) { F(state,0x34)=1.0f; moby_set_state(object,4,-1); }
        else { F(state,0x34)=0.0f; goto mode1; }
        return;
    case 1:
        vec_scale_to_length(position,object+0xE0,g_follow_speed);
        FastVecAdd(object+0x10,position,state+0x10);
        if (math_fast_float_d((int *)(state+0x3C)) && fast_vec_dist(object+0x10,R+0x80)<1.75f) {
            if (g_hero_state.field123a || g_hero_state.field22b4) goto decay;
            if (g_subtitle_history.sentinel<65535 && I(g_follow_state_words,0)==0 && I(g_follow_state_words,0x24)==-1) {
                subtitle_request_voice_line(0x9C7,30);
                g_subtitle_history.sentinel=-1;
            }
            if (g_hero_state.field1248!=10) goto decay;
            if (g_hero_state.field1220) {
                if (!PadPressedWithin(0x80,7,0) || !(g_hero_state.field31c<0.2f) || !moby_is_spot_free_of_blockers((char *)object)) goto decay;
                if (F(state,0x34)<1.0f) {
                    vec_transform_by_object_or_given((char *)object,(char *)forward,R,0);
                    FastVecSub(direction,R+0x80,object+0x10);
                    vec_transform_by_object_or_given((char *)object,(char *)direction,(char *)direction,0);
                    zero=0.0f;
                    forward[2]=zero;
                    direction[2]=zero;
                    vec_scale_to_length(direction,direction,1.0f);
                    vec_scale_to_length(forward,forward,1.0f);
                    if (FastVecDot(direction,forward)<0.2f) { hero_l16_set_move_state(0x37,1); cam_start_blend_to_target((char *)object); }
                    moby_set_state(object,2,-1);
                }
            }
        }
decay:
    if (F(state,0x34)==0.0f) return;
    F(state,0x40)-=0.0027777778f;
    F(state,0x34)+=F(state,0x40);
    value=F(state,0x34);
    if (!(value<=0.0f)) return;
    F(state,0x34)=0.0f;
    if (math_fabs(F(state,0x40))>0.0016666668f) { F(state,0x40)*=-0.333f; F(state,0x34)=F(state,0x40); }
    else F(state,0x40)=0.0f;
        return;
    case 2:
        if (PadPressedWithin(0x80,7,0) && g_hero_state.field1b8>=21) goto leaveActive;
        if (F(state,0x34)>=1.0f) goto leaveActive;
        if (g_hero_state.field2294==0x37) goto active;
leaveActive:
        if (g_hero_state.field2294==0x37) hero_l16_set_move_state(0,1);
        cam_set_mode_state(1);
        I(state,0x3C)=20;
        I(state,0x58)++;
        if (I(state,0x58)==3 || I(state,0x58)==6) subtitle_request_voice_line(0x9C7,30);
        if (F(state,0x34)>=1.0f) {
            if (g_current_map_index==26) g_subtitle_history.sentinel=-1;
            F(state,0x34)=1.0f;
            moby_set_state(object,4,-1);
        } else {
mode1:
            moby_set_state(object,1,-1);
        }
        return;
active:
            vec_scale_to_length(position,object+0xE0,g_follow_speed_alt);
            FastVecAdd(object+0x10,position,state+0x10);
            hero_switch_push_anim_state((char *)object);
            spinning_object_move_along_ground((char *)object);
            moby_tilt_to_ground_slope((char *)object);
            BlendCameraPose((char *)object);
        return;
    case 4:
        if (flag_set_first_pending(object)) F(state,0x44)=g_follow_speed;
        velocity=F(state,0x48)-0.0027777778f;
        value=F(state,0x44)+velocity;
        ground=g_follow_ground_height;
        F(state,0x48)=velocity;
        F(state,0x44)=value;
        if (value<=ground) {
            F(state,0x44)=ground;
            if (math_fabs(F(state,0x48))>0.0016666668f) F(state,0x48)*=-0.333f;
            else *(u16 *)(object+0x34)|=2;
        }
        vec_scale_to_length(position,object+0xE0,F(state,0x44));
        FastVecAdd(object+0x10,position,state+0x10);
        return;
    default:
        return;
    }
}

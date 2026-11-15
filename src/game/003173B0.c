#include "include_asm.h"
#include "common.h"

extern int D_001B2758 MACRO_ADDR;
extern float math_random_float_range(float, float), math_random_signed_float_range(float, float);
extern void vec_clear_128(void *), gravity_get_dir_at_object(void *, void *, int);
extern char *moby_get_private_value_0(void *);
extern void FastVecAdd(void *, void *, void *);
extern int FloatToInt(float), math_random_int_range(int, int);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern int CollLine(void *, void *, int, void *, int);
extern void moby_set_state(void *, int, int), anim_start_blended(void *, int, int, int);
extern float D_001BAFA8;

typedef int TI128_00318340 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128_00318340 q[0x260]; } Hero_00318340;
extern u8 g_hero_state[];
extern char g_hero_position[];
extern u8 g_sound_state[];

extern char D_001A8BD0[16] MACRO_ADDR;
extern char D_001AFA80[];
extern void STUB_printf(const char *, ...);
extern void gfx_register_overlay_draw_callback(void (*)(char *), char *);
extern int math_fast_float_d(void *);
extern void FastVecCross(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float fast_vec_dist(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void euler_rotation_basis(void *, void *);
extern void moby_mark_spawned(void *);
extern float moby_get_anim_value(void *);
extern void SetDeathBits(void *, int, int);
extern int math_random_int_below(int);
extern float moby_turn_toward_position(void *, void *, void *, float, float, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern float math_spring_float_to_goal(void *, float, void *, float, float, float);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void part_spawn_explosion_with_sparks(void *, void *, int, float, float);
extern int IsPointInCuboid(void *, int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern int math_is_value_within_step(void *, float);
extern int flag_set_first_pending(void *);
extern int flag_is_third_pending_set(void *);
extern void *part_spawn_gravity_fade(void *, void *, int, u32, int, int, int, int, float, float, float);
extern void path_sample_position(void *, int, void *, void *, int, float);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern void hover_enemy_update_body_group(char *);
extern void hover_enemy_draw_effects(char *);
extern void hover_enemy_tick_timers(char *);
extern int group_claim_lead_token(char *);
extern int group_pass_lead_token(char *);
extern int group_is_moby_member(unsigned char *);
extern int moby_is_target_outside_turn_limit(char *, float);
extern void moby_turn_toward_target(char *);
extern void *part_spawn_spinning_effect_moby(char *, void *, void *, int, int, float);
extern float vec_distance_xy(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_scale_owner_words_by_angles(float, float, char *, char *, float, char *);

/* One of the twelve 0xA0-byte records at *D_001B2758 that func_0031DEE8 steps for their
   owner: the boot counterpart of the level records func_L00_003BBB68 updates. */
typedef struct {
    float out0[4];          /* 0x00: ang0 through the two angle helpers, times amp0 */
    float out1[4];          /* 0x10: the same for ang1 */
    float start[4];         /* 0x20: copied from the owner's position each frame */
    float pos[4];           /* 0x30: follows the target */
    float ang0[3];          /* 0x40 */
    float rate0[3];         /* 0x4C */
    float amp0[3];          /* 0x58 */
    float ang1[3];          /* 0x64 */
    float rate1[3];         /* 0x70 */
    float amp1[3];          /* 0x7C */
    int life;               /* 0x88: timer, frees the record when it expires */
    char *owner;            /* 0x8C */
    char *target;           /* 0x90 */
    int time;               /* 0x94: timer, also counts the approach */
    int duration;           /* 0x98 */
    int hit;                /* 0x9C */
} Slot31DEE8;

/* The 0xE0-byte class records; D_00139568 maps a class number to its record. */
typedef struct {
    char pad_00[0x74];
    float f74;
    char pad_78[0xE0 - 0x78];
} Class31DEE8;

extern unsigned char g_item_slot_to_record[];
extern Class31DEE8 g_weapon_table[];
extern float FastAddRotations(float angle, float step);
extern float math_fast_sin_or_cos_a(float angle);
extern float math_fast_sin_or_cos_b(float angle);
extern float IntToFloat(int ticks);
extern int math_fast_float_d(void *timer);
extern void lerp_vector(void *out, void *from, void *to, float t);
extern void make_hit_descriptor(void *packet, char *owner, int flags, void *direction, float amount);
extern void QueueMobyImpact(char *target, void *packet);
extern void part_spawn_hit_sparks(void *pos, int count, int mode);
extern int StartAttachedEffect(char *target, int kind, int value);

extern char F669d6320_D_001BAFC0[];

extern void F669d6320_FUN_00282F20(void *out, void *in, float scale);

extern void F669d6320_FUN_00282CC0(void *out, void *in1, void *in2);

extern int F669d6320_FUN_002761F8(void *a, void *b, int mode, void *self, int flag);

extern void F669d6320_FUN_00282D30(void *out, void *in, float scale);

extern void F2c74c194_FUN_00282D30(char *dst, char *src, float scale);

extern void F5a19df7a_FUN_002FC560(unsigned int a, unsigned long b);

extern void F5a19df7a_FUN_0031E2A0(char *p);

extern void F5a19df7a_FUN_0031E560(char *p);

extern s32 F5a19df7a_FUN_002A7820(int a, int b);

extern float F5a19df7a_FUN_002A7940(void);

extern void F5a19df7a_FUN_0031EB00(char *a, int b, float e, char *c, float f, int d, int g);

extern void Fc936841d_FUN_00282CF0(char *local, char *first, char *second);

extern void Fc936841d_FUN_00282CC0(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif

/* The four 16-byte blocks the record carries and scales. */
#ifndef RAC2_T_BLOCK_0031A340
#define RAC2_T_BLOCK_0031A340
typedef struct {
    float q[4];
} Block_0031a340;
#endif

/* The 240-byte record func_0031A340 builds: a scaled matrix, a colour, the
   looked-up handle, the fixed fields and the two computed vectors. */
#ifndef RAC2_T_LOC_0031A340
#define RAC2_T_LOC_0031A340
typedef struct {
    Block_0031a340 b0;
    Block_0031a340 b1;
    Block_0031a340 b2;
    Block_0031a340 b3;
    int k0;
    int k1;
    int k2;
    int k3;
    int z80;
    int z84;
    int z88;
    float f92;
    float f96;
    int z100;
    float f104;
    float f108;
    long long v112;
    long long v120;
    long long v128;
    long long v136;
    float m00;
    float m01;
    float m02;
    float m03;
    float m10;
    float m11;
    float m12;
    float m13;
    float m20;
    float m21;
    float m22;
    float m23;
    float v192;
    float v196;
    float v200;
    float v204;
    float v208;
    float f212;
    float f216;
    float v220;
    float e0;
    float e1;
    float e2;
    float e3;
} Loc_0031a340;
#endif

/* The state block whose +0x140 holds the position the record is built around. */
#ifndef RAC2_T_STATE_001B5200
#define RAC2_T_STATE_001B5200
typedef struct {
    char pad_000[0x140];
    float pos[3];
} State_001b5200;
#endif

extern State_001b5200 g_active_camera;

extern void mat_build_rotation_from_angles(void *, float *);

extern int flyer_init_check_death(char *);
extern int flag_set_second_pending(char *);
extern int moby_dispatch_action_by_kind(char *, char *);
extern void snd_stop_voice(int);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern int PlayMobySound(int, int, void *);
extern void SetDeathBits(void *, int, int);
extern void moby_mark_spawned(void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern void func_002A677C(void *);
extern int moby_turn_toward_target_and_step(void *, void *, float);
extern int coll_test_hit_at_bone(void *, int, float, float, int, float, int, int, int);
extern void flyer_tick_timers(char *);
extern unsigned char g_sound_state[];
extern unsigned char g_hero_state[];
typedef struct { char pad[0x249C]; char *target; } Hero3173;
extern char *g_path_table[];
#define FI(p,o) (*(int *)((p)+(o)))
#define FF(p,o) (*(float *)((p)+(o)))
#define FH(p,o) (*(short *)((p)+(o)))
#define FU(p,o) (*(unsigned short *)((p)+(o)))
#define FB(p,o) (*(unsigned char *)((p)+(o)))
#define FP(p,o) (*(char **)((p)+(o)))
/* Keeps state 6's transition from cross-jumping into state 10's identical call tail, as
   RAC1 pause.c does for its duplicate start_audio_stream_read_r3/r4 calls. Both names
   have the same EE interface. */
extern void changeMode3173Six(void *, int, int) __asm__("func_002A7750");
/* Updates the flying enemy each frame: handles its moods, rises, follows its path and attacks. */
void flyer_update_states(char *self)
{
    char *vars = FP(self,0x68);
    int flags, n, i;
    char *sound, *path;
    float target[4], delta[4];
    float f, height, savedHeight;
    /* Written out here and at the end of state 3, not shared through a label: cross-jumping
       merges the two after sched1, which has to see func_0029F338 in the same block as the
       explosion's calls for it to set a3..t3 up before a0..a2. */
    if (flyer_init_check_death(self)) {
        moby_mark_spawned(self);
        return;
    }
    switch (FB(self,0x95)) {
    case 0:
        if (flag_set_second_pending(self))
            moby_set_controller_speed_limits(self,0.006666667f,0.06666667f,0.8377582f,0.8377582f);
        if (FI(vars,0x258)==1 && math_fast_float_d(vars+0x2A4) && FI(vars,0x2AC)) {
            if (FI(vars,0x294)==-1) {
                moby_set_state(self,6,2);
                FF(self,0x18)=FF(vars,0x28C);
                if (FB(self,0x43)!=2) anim_start_blended(self,2,0,5);
            } else moby_set_state(self,4,2);
        } else if (FH(vars,0x276)) {
            moby_set_state(self,3,1);
            FH(vars,0x276)=0;
            if (FH(vars,0x270)<300) FH(vars,0x270)=math_random_int_range(480,600);
        }
        FF(self,0xF8)=FastAddRotations(FF(self,0xF8),0.03490659f);
        break;
    case 1:
        if (flag_set_second_pending(self))
            moby_set_controller_speed_limits(self,0.006666667f,0.06666667f,0.8377582f,0.8377582f);
        if ((FI(vars,0x258)==1 || FI(vars,0x25C)==1) && FI(vars,0x2AC)) {
            if (FI(vars,0x294)!=-1) moby_set_state(self,4,2);
            else {
                moby_set_state(self,6,2);
                FF(self,0x18)=FF(vars,0x28C);
                if (FB(self,0x43)!=2) anim_start_blended(self,2,0,5);
            }
        }
        FF(self,0xF8)=FastAddRotations(FF(self,0xF8),0.03490659f);
        break;
    case 2:
        if (flag_set_second_pending(self))
            moby_set_controller_speed_limits(self,0.006666667f,0.06666667f,0.8377582f,0.8377582f);
        if (FI(vars,0x258)!=1 && FI(vars,0x25C)!=1 && FB(self,0x20)!=4) {
            moby_set_state(self,1,1);
            if (FB(self,0x43)) anim_start_blended(self,0,0,20);
            FH(vars,0x270)=math_random_int_range(580,600);
        }
        break;
    case 3:
        flags=moby_dispatch_action_by_kind(self,vars+0x60);
        if (flags&1) {
            n=FI(vars,0x2A8);
            if (n!=-1) {
                sound=(char *)g_sound_state+n*0x70;
                if (FP(sound,0x88)==self && FB(sound,0x74)) snd_stop_voice(n);
            }
            FI(vars,0x2A8)=-1;
            SpawnExplosion(self+0x10,0,0,0,0,20,45,1,0.3f,20.0f,1,0,0,0);
            PlayMobySound(0,0,self);
            SetDeathBits(self,0,3);
            moby_mark_spawned(self);
            return;
        }
        if (flags&2) {
            if (FI(vars,0x258)==1 || FI(vars,0x25C)==1) {
                moby_set_state(self,5,2);
                if (FB(self,0x43)) anim_start_blended(self,0,0,5);
                if (FI(vars,0x294)!=-1) moby_set_state(self,4,2);
            } else {
                moby_set_state(self,3,1);
                FH(vars,0x270)=math_random_int_range(580,600);
            }
        }
        break;
    }
    switch (FB(self,0x20)) {
    case 1:
        if (FU(self,0x96)>=26) {
            if (FB(self,0x43)) anim_start_blended(self,0,0,5);
            moby_set_state(self,2,-1);
            FF(self,0x18)=FF(vars,0x28C);
        } else {
            f=math_fast_sin_or_cos_b((float)FU(self,0x96)*0.12566361f)*0.02f;
            if (FF(self,0x18)>FF(vars,0x28C)) FF(self,0x18)-=f;
            else FF(self,0x18)+=f;
        }
        break;
    case 4:
        path=g_path_table[FI(vars,0x294)];
        if (FI(vars,0x298)>=FI(path,0)) {
            FI(vars,0x294)=-1;
            FF(vars,0x28C)=coll_probe_ground_height_below(self+0x10,0,0.5f)+0.5f;
            moby_set_state(self,5,-1);
        } else {
            qcopy(target,path+0x10+FI(vars,0x298)*16);
            FastVecSub(delta,target,self+0x10);
            vec_scale_to_length(delta,delta,FF(vars,0x1C0));
            FastVecAdd(self+0x10,self+0x10,delta);
            if (vec_distance_xy(self+0x10,target)<0.5f) FI(vars,0x298)++;
            if (FI(vars,0x298)>=FI(path,0)-6 && FF(vars,0x1C0)>=0.10000001f)
                FF(vars,0x1C0)-=0.0022222223f;
            height=coll_probe_ground_height_below(self+0x10,0,0.5f)+0.5f;
            if (FF(self,0x18)<height) FF(self,0x18)=height;
            FF(vars,0x28C)=FF(self,0x18);
            func_002A677C(self);
        }
        FF(self,0xF8)=FastAddRotations(FF(self,0xF8),0.03490659f);
        break;
    case 5:
        savedHeight=FF(self,0x18);
        moby_turn_toward_target_and_step(self,vars+0x230,FF(vars,0x290));
        FF(self,0x18)=savedHeight;
        if (vec_distance_xy(self+0x10,FP(vars,0x240)+0x10)<1.3f) moby_set_state(self,7,-1);
        FF(self,0xF8)=FastAddRotations(FF(self,0xF8),0.03490659f);
        break;
    case 6:
        if (FB(self,0x60)&2) {
            if (FB(self,0x43)!=3) anim_start_blended(self,3,0,5);
            changeMode3173Six(self,8,-1);
        }
        break;
    case 8:
        height=1.75f;
        FF(self,0x48)=height;
        for (i=0;i<4;i++) coll_test_hit_at_bone(self,i,0.17f,FF(vars,0x2B0),1,1.0f,0,1,0);
        if (((Hero3173 *)g_hero_state)->target==self) moby_set_state(self,9,-1);
        if (vec_distance_xy(self+0x10,FP(vars,0x240)+0x10)>1.3f && (float)FU(self,0x96)>120.0f) {
            if (FB(self,0x43)) anim_start_blended(self,0,0,15);
            moby_set_state(self,5,-1);
            FF(self,0x48)=1.0f;
        }
        break;
    case 9:
        if ((float)FU(self,0x96)>20.0f) {
            moby_set_state(self,10,-1);
            if (FB(self,0x43)!=4) anim_start_blended(self,4,0,5);
            FF(self,0x48)=1.0f;
        }
        break;
    case 10:
        if (FB(self,0x60)&2) {
            if (FB(self,0x43)) anim_start_blended(self,0,0,15);
            moby_set_state(self,5,-1);
        }
        break;
    case 7:
        if (FU(self,0x96)>=30) {
            moby_set_state(self,6,-1);
            if (FB(self,0x43)!=1) anim_start_blended(self,1,0,2);
            FF(self,0x48)=1.0f;
        }
        break;
    }
    if (FB(self,0x20)!=4 && FB(self,0x95)==2 && FF(self,0x18)<FF(vars,0x28C)) FF(self,0x18)=FF(vars,0x28C);
    flyer_tick_timers(self);
}
#undef FI
#undef FF
#undef FH
#undef FU
#undef FB
#undef FP

extern void flyer_alert_group(void *);

/* Called when the enemy dies: wakes up its group mates. */
void flyer_alert_group_on_death(void *object) {
    flyer_alert_group(object);
}

extern void gfx_update_color_fade(char *, char *);
extern int FastDecTimer(void *);
extern void math_update_wrapped_angle_offset(char *, float, float, char *, float, char *);
extern void moby_scale_owner_words_by_angles(float, float, char *, char *, float, char *);

/* Runs the enemy's small timers and counts the frames it has been in this state. */
void flyer_tick_timers(char *object)
{
    char *data = *(char **)(object + 0x68);
    gfx_update_color_fade(object, data + 0x50);
    FastDecTimer(data + 0x270);
    if (FastDecTimer(data + 0x272)) {
        math_update_wrapped_angle_offset(object, 0.1f, 0.08726647496223449707f, data + 0x27C, -1.0f, data + 0x280);
        moby_scale_owner_words_by_angles(0.13962635397911071777f, 0.026179943233728408813f, object, data + 0x284, 0.026179943233728408813f, data + 0x288);
    }
    if (*(unsigned short *)(object + 0x96) <= 65534)
        (*(unsigned short *)(object + 0x96))++;
}

/* func_00318340 is in 00318340.c. */
/* func_00319780 is in 00319780-g8.c. */

/* Sets up the hovering enemy the first time it runs: speeds, sizes, start position and first animation. */
void hover_enemy_init(char *self)
{
    char *d = *(char **)(self + 0x68);
    *(u8 *)(d+0x68) = FloatToInt(15.0f);
    *(u8 *)(d+0x6A) = FloatToInt(12.0f);
    *(float *)(self+0x2C) *= 1.1f;
    *(u16 *)(self+0x34) |= 0x8100;
    *(char **)(d+0x18) = d+0x130;
    *(u8 *)(d+0x48)=3;
    *(u8 *)(d+0x90)=17;
    *(int *)(d+0xC8)=4;
    *(int *)(d+0xFC)=*(int *)(d+0x270);
    *(u8 *)(d+0x95)=13;
    *(float *)(d+220)=0.30000001192092896f;
    *(float *)(d+216)=0.05000000074505806f;
    *(float *)(d+160)=0.06666667014360428f;
    *(float *)(d+164)=0.004166666883975267f;
    *(float *)(d+168)=0.008333333767950535f;
    *(float *)(d+176)=0.5f;
    *(float *)(d+180)=0.5f;
    *(float *)(d+188)=0.4000000059604645f;
    *(float *)(d+156)=0.10000000894069672f;
    if ((float)*(int *)(d+0x2E8)>0.0f) *(float *)(d+0xC0)=(float)*(int *)(d+0x2E8);
    *(float *)(d+0x15C)=0.0f;
    *(float *)(d+320)=12.56637191772461f;
    *(float *)(d+304)=0.800000011920929f;
    *(float *)(d+308)=0.5f;
    *(float *)(d+0x138)=0.4f;
    *(float *)(d+316)=0.4000000059604645f;
    *(float *)(d+352)=0.523598849773407f;
    *(int *)(d+0x168)|=5;
    moby_set_controller_speed_limits(self,0.0033333334140479565f,0.10000000894069672f,0.0011635529808700085f,0.10471977293491364f);
    qcopy(d+0x220,self+0x10);
    *(float *)(d+0x230)=1.0f;
    *(float *)(d+0x23C)=3.0f;
    *(float *)(d+0x240)=10.0f;
    *(int *)(d+0x2D8)=math_random_int_range(120,700);
    *(float *)(d+0x294)*=0.01745329424738884f;
    *(u8 *)(d+0x250)=176;
    *(u8 *)(d+0x251)=128;
    *(u8 *)(d+0x252)=64;
    *(int *)(d+0x2C4)=1;
    *(float *)(d+0x2BC)=0.0f;
    *(int *)(d+0x2C0)=0;
    qcopy(d+0x340,self+0x10);
    *(float *)(d+0x290)=0.0f;
    *(int *)(d+0x2C8)=0;
    *(int *)(d+0x2CC)=0;
    *(int *)(d+0x37C)=0;
    moby_transform_joint_to_world(self,0,d+0x2F0);
    qcopy(d+0x300,d+0x2F0);
    *(float *)(d+0x2F8)+=20.0f;
    if (CollLine(d+0x300,d+0x2F0,0,self,0))
        *(float *)(d+0x2F8)=D_001BAFA8;
    *(int *)(d+0x168)|=4;
    *(u16 *)(self+0x34)|=0x100;
    *(float *)(d+0x140)=12.56637191772461f;
    *(int *)(d+0x168)|=1;
    if (*(int *)(d+0x28C)==0) {
        if (*(int *)(d+0x370)!=-1) {
            moby_set_state(self,15,3);
            if (*(u8 *)(self+0x43)!=7) anim_start_blended(self,7,0,0);
        } else {
            moby_set_state(self,1,0);
            if (*(u8 *)(self+0x43)!=0) anim_start_blended(self,0,0,0);
        }
    } else {
        moby_set_state(self,3,1);
        if (*(u8 *)(self+0x43)!=11) anim_start_blended(self,11,0,0);
    }
}

extern void gfx_update_color_fade(char *, char *);
extern int FastDecTimer(void *);
extern void value_set_and_smooth(char *, char *, int, int, float);

/* Runs the hovering enemy's timers and counts its frames. */
void hover_enemy_tick_timers(char *object)
{
    char *data = *(char **)(object + 0x68);
    gfx_update_color_fade(object, data + 0x70);
    FastDecTimer(data + 0x280);
    FastDecTimer(data + 0x282);
    if (*(unsigned short *)(object + 0x96) < 65535)
        (*(unsigned short *)(object + 0x96))++;
    value_set_and_smooth(object, data + 0x380, 5, 1, 2.0f);
}

extern void gfx_draw_beam_between_points(char *);
extern void gfx_draw_facing_glow_quad(char *, char *, float, int, int, int);

/* Draws the glow effects of the hovering enemy. */
void hover_enemy_draw_effects(char *object)
{
    char *data = *(char **)(object + 0x68);
    int mode = *(unsigned char *)(object + 0x20);
    if (mode == 12 || mode == 14 || mode == 16 || mode == 13 || *(unsigned char *)(object + 0x95) == 1)
        gfx_draw_beam_between_points(object);
    gfx_draw_facing_glow_quad(object, data + 0x310, 0.125f, 0x36F6, 0x20000000, 0x20000000);
    gfx_draw_facing_glow_quad(object, data + 0x320, 0.15f, 0x1050B0, 0x30000000, 0x20000000);
    gfx_draw_facing_glow_quad(object, data + 0x330, 0.15f, 0x1050B0, 0x10000000, 0x30000000);
}

extern void gfx_fill_quad_from_template(void *record);
extern long long func_0027C878_1(int id);
extern float mat_fast_helper_a(float x, float y);
extern float vec_distance_xy(void *a, void *b);
extern float math_random_angle(void);
extern void euler_to_matrix(void *dst, void *src);
extern void FastVecSub(void *dst, void *a, void *b);
extern void vec_scale_to_length(void *dst, void *src, float scale);
extern void FastVecScale(void *dst, void *src, float scale);
extern void draw_world_quad(void *dst, void *src, int flag);

/* Builds the 240-byte record around a position: the looked-up handle, the colour
   of the object, the position the object sits at and the scaled matrix it keeps.
   The first argument is not read. */
void gfx_draw_facing_glow_quad(char *unused, char *p1, float scale, int col0, int col1, int col2)
{
    Loc_0031a340 local;
    float x;

    gfx_fill_quad_from_template(&local);
    local.v120 = func_0027C878_1(11);
    local.k3 = col0 + col1;
    local.k2 = col0 + col1;
    local.k1 = col0 + col1;
    local.k0 = col0 + col1;
    local.v136 = 0x0000008000000048LL;
    local.v220 = 0.0f;
    local.f216 = mat_fast_helper_a(g_active_camera.pos[0] - *(float *)p1,
                                g_active_camera.pos[1] - *(float *)(p1 + 4));
    x = mat_fast_helper_a(vec_distance_xy(p1, &g_active_camera.pos),
                      g_active_camera.pos[2] - *(float *)(p1 + 8));
    local.f212 = -x;
    local.v208 = math_random_angle();
    euler_to_matrix(&local.m00, &local.v208);
    FastVecSub(&local.e0, &g_active_camera.pos, p1);
    vec_scale_to_length(&local.e0, &local.e0, 0.5f);
    local.v192 = *(float *)p1 + local.e0;
    local.v196 = *(float *)(p1 + 4) + local.e1;
    local.v200 = *(float *)(p1 + 8) + local.e2;
    local.v204 = 1.0f;
    FastVecScale(&local.b0, &local.b0, scale);
    FastVecScale(&local.b1, &local.b1, scale);
    FastVecScale(&local.b2, &local.b2, scale);
    FastVecScale(&local.b3, &local.b3, scale);
    draw_world_quad(&local, &local.m00, 0);
    local.k3 = col0 + col2;
    local.k2 = col0 + col2;
    local.k1 = col0 + col2;
    local.k0 = col0 + col2;
    FastVecScale(&local.b0, &local.b0, 0.5f);
    FastVecScale(&local.b1, &local.b1, 0.5f);
    FastVecScale(&local.b2, &local.b2, 0.5f);
    FastVecScale(&local.b3, &local.b3, 0.5f);
    draw_world_quad(&local, &local.m00, 0);
}

/* Tells whether the object belongs to a group. */
int group_is_moby_member(unsigned char *object) {
    return object[0x21] != 255;
}

typedef union { u8 b[0x2600]; float v[0x980][1]; } Hero_0031A718;

extern u8 g_hero_state[];
extern short *D_001EE5A0[];
extern u8 *D_001B1B5C MACRO_ADDR;
extern float fast_vec_dist(void *, void *);

/* Picks the nearest live moby on the object's list (skipping 0x9B4 ones) that is closer than
   the hero, and records it as the object's target. */
void group_pick_nearest_target(u8 *self)
{
    u8 *vars = *(u8 **)(self + 0x68);
    short *list;
    u8 *moby;
    float best;

    best = fast_vec_dist(self + 0x10, &((Hero_0031A718 *)g_hero_state)->b[0x80]);
    if (self[0x21] == 0xFF && D_001EE5A0[self[0x21]] == 0 && *(int *)(vars + 0x350) == 0)
        return;
    list = D_001EE5A0[self[0x21]];
    do {
        moby = D_001B1B5C + ((*list & 0x7FFF) << 8);
        if (*(s8 *)(moby + 0x20) >= 0 && *(s16 *)(moby + 0xAA) != 0x9B4 /* moby class 2484 */) {
            if (fast_vec_dist(self + 0x10, moby + 0x10) < best) {
                *(u8 **)(vars + 0x30) = moby;
                best = fast_vec_dist(self + 0x10, moby + 0x10);
            }
        }
    } while (*list++ >= 0);
}


/* Works out which way to push the object, away from a wall if one is just ahead. */
void moby_compute_push_direction(char *self, char *out_dir, int flip)
{
    float a[4];
    float b[4];

    F669d6320_FUN_00282F20(a, self + 224, 0.1f);
    F669d6320_FUN_00282F20(b, self + 224, -3.0f);
    F669d6320_FUN_00282CC0(a, a, self + 16);
    F669d6320_FUN_00282CC0(b, b, self + 16);

    if (F669d6320_FUN_002761F8(a, b, 2, self, 0))
        F669d6320_FUN_00282F20(out_dir, F669d6320_D_001BAFC0, 1.0f);
    else
        F669d6320_FUN_00282F20(out_dir, self + 224, -1.0f);

    if (flip == 0)
        F669d6320_FUN_00282D30(out_dir, out_dir, -1.0f);
}

extern void FastVecSub(void *, void *, void *);
extern unsigned int moby_get_motion_params(unsigned int);
extern float moby_turn_toward_direction(void *, unsigned int, void *, int);

/* func_0031AAB0 is matched in 0031AAB0.c. */


/* Gets the movement settings the object keeps in its private data. */
unsigned int moby_get_motion_params(unsigned int moby)
{
    unsigned int vars;
    unsigned int result;

    vars = *(unsigned int *)(moby + 0x68);
    result = *(unsigned int *)(vars + 0x18);
    return result;
}

/* func_0031AB18 is defined in 0031AB18-zero-ti.c. */


/* func_0031BCC8 is in 0031BCC8-g8.c. */

/* func_0031C498 is in 0031C498.c. */

extern void gfx_draw_beam_quad_between_points(char *);
extern void gfx_draw_facing_glow_flare(char *, char *, int, int, int, float);
extern void gfx_draw_facing_glow_two_textures(char *, char *, float, int, int);

/* Refresh the auxiliary state for modes 4, 5, 10 or flag 2, then issue
   three calls with the embedded vectors and three with the referenced vectors. */
/* Draws the glow effects of the hovering enemy and its three parts. */
void three_part_turret_draw_effects(char *self)
{
    char *data = *(char **)(self + 0x68);
    unsigned char mode = self[0x20];

    if (mode == 4 || mode == 5 || (unsigned char)self[0x95] == 2 || mode == 10)
        gfx_draw_beam_quad_between_points(self);

    gfx_draw_facing_glow_flare(self, data + 0x370, 0x41DE, 0x10000000, 0x20000000, 0.125f);
    gfx_draw_facing_glow_flare(self, data + 0x380, 0x00800000, 0x10000000, 0x30000000, 0.125f);
    gfx_draw_facing_glow_flare(self, data + 0x390, 0x00800000, 0x10000000, 0x30000000, 0.125f);

    gfx_draw_facing_glow_two_textures(self, *(char **)(data + 0x270) + 0x10, 0.075f, 0x204080, 0x204080);
    gfx_draw_facing_glow_two_textures(self, *(char **)(data + 0x274) + 0x10, 0.075f, 0x204080, 0x204080);
    gfx_draw_facing_glow_two_textures(self, *(char **)(data + 0x278) + 0x10, 0.075f, 0x204080, 0x204080);
}

/* Resets a draw packet to a large square (size 2) with white colour. */
void gfx_init_large_quad_packet(char *packet)
{
    *(long long *)(packet + 112) = 0LL;
    *(int *)(packet + 80) = 0;
    *(int *)(packet + 84) = 0;
    *(float *)(packet + 88) = 1.0f;
    *(int *)(packet + 92) = 0;
    *(int *)(packet + 96) = 0;
    *(float *)(packet + 100) = 1.0f;
    *(float *)(packet + 104) = 1.0f;
    *(float *)(packet + 108) = 1.0f;
    *(float *)(packet + 8) = -2.0f;
    *(float *)(packet + 24) = 2.0f;
    *(float *)(packet + 40) = -2.0f;
    *(float *)(packet + 56) = 2.0f;
    *(float *)(packet + 4) = -2.0f;
    *(float *)(packet + 36) = 2.0f;
    *(int *)(packet + 0) = 0;
    *(int *)(packet + 16) = 0;
    *(int *)(packet + 32) = 0;
    *(int *)(packet + 48) = 0;
    *(float *)(packet + 12) = 1.0f;
    *(float *)(packet + 28) = 1.0f;
    *(float *)(packet + 44) = 1.0f;
    *(long long *)(packet + 128) = 0x0000FF9000000260LL;
    *(float *)(packet + 20) = -2.0f;
    *(float *)(packet + 52) = 2.0f;
    *(float *)(packet + 60) = 1.0f;
}


/* func_0031CB78 is in its own unit: func_0031C7A0 has different placements. */

/* func_0031CDF8 is defined in 0031CDF8.c. */

/* Saves the current position as the newest point of the trail behind the object. */
void gfx_record_trail_point(char *moby) {
    char *state = *(char **)(moby + 0x68);

    *(int *)(state + 0x288) = 0;
    *(int *)(state + 0x284) = (*(int *)(state + 0x284) + 1) % 4;
    if (*(int *)(state + 0x280) < 4)
        (*(int *)(state + 0x280))++;
    mat_build_rotation_from_angles(state + (*(int *)(state + 0x284) * 16 + 0x4A0), (float *)(moby + 0xF0));
    qcopy(state + *(int *)(state + 0x284) * 16 + 0x3A0,
          (char *)(*(int *)(state + 0x278) + 0x10));
}


/* func_0031D308 is in the -G8 sibling. */

/* func_0031D3E0 is in 0031D3E0.c. */

/* func_0031D588 is in 0031D588-g8.c. */


/* Starts a new spark on a free slot, flying toward the target with random spin and speed. */
void spark_spawn_targeted(char *self, char *target, int count)
{
    int pool = D_001B2758;
    char *position = self + 0x10;
    char *target_position = target + 0x10;
    char *data = *(char **)(self + 0x68);
    char *p;
    char *info;
    float v[4];
    int i;
    for (i = 0; i < 12; i++) {
        p = (char *)(pool + i * 0xA0);
        if (*(int *)(p + 0x8C) == 0) {
            *(char **)(p + 0x8C) = self;
            (*(int *)(data + 0x1C))++;
            qcopy(p + 0x20, position);
            *(float *)(p + 64) = math_random_float_range(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 68) = math_random_float_range(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 72) = math_random_float_range(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 100) = math_random_float_range(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 104) = math_random_float_range(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 108) = math_random_float_range(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 76) = math_random_signed_float_range(0.001f, 0.05f);
            *(float *)(p + 80) = math_random_signed_float_range(0.001f, 0.05f);
            *(float *)(p + 84) = math_random_signed_float_range(0.001f, 0.05f);
            *(float *)(p + 112) = math_random_signed_float_range(0.001f, 0.05f);
            *(float *)(p + 116) = math_random_signed_float_range(0.001f, 0.05f);
            *(float *)(p + 120) = math_random_signed_float_range(0.001f, 0.05f);
            *(float *)(p + 88) = math_random_float_range(3.25f, 6.75f);
            *(float *)(p + 92) = math_random_float_range(3.25f, 6.75f);
            *(float *)(p + 96) = math_random_float_range(3.25f, 6.75f);
            *(float *)(p + 124) = math_random_float_range(1.25f, 4.75f);
            *(float *)(p + 128) = math_random_float_range(1.25f, 4.75f);
            *(float *)(p + 132) = math_random_float_range(1.25f, 4.75f);
            vec_clear_128(p);
            vec_clear_128(p + 0x10);
            *(int *)(p + 0x94) = count;
            *(int *)(p + 0x98) = count;
            *(char **)(p + 0x90) = target;
            *(int *)(p + 0x9C) = 0;
            *(int *)(p + 0x88) = 20;
            info = moby_get_private_value_0(target);
            if (info) {
                gravity_get_dir_at_object(target, v, 1);
                FastVecScale(v, v, *(float *)(info + 0x10));
                FastVecAdd(p + 0x30, v, target + 0x10);
            } else {
                qcopy(p + 0x30, target_position);
            }
            break;
        }
    }
}

static inline Class31DEE8 *Class31DEE8At(int index)
{
    return &g_weapon_table[index];
}

/* Steps every record the owner holds: refreshes its start from the owner, advances the two
   angle triples (faster while the approach timer runs), and while it has a target moves its
   position towards it. When the approach timer expires and the target is still live, it
   sends one hit packet (func_002A8C00/func_002A8E20) and marks the record; when the life
   timer expires the record is released and the owner's count drops. */
void spark_update_targeted(char *owner)
{
    float v[4];
    struct {
        char pad_00[0x18];
        unsigned char kind;
        unsigned char mode;
        short id;
        char pad_1c[0x14];
    } packet;
    char *ctx = *(char **)(owner + 0x68);
    Slot31DEE8 *slot;
    char *other;
    float ratio;
    float damage;
    float boost = 100.0f;
    int i;

    for (i = 0; i < 12; i++) {
        if (((Slot31DEE8 *)D_001B2758)[i].owner != owner)
            continue;
        slot = &((Slot31DEE8 *)D_001B2758)[i];
        qcopy(slot->start, owner + 0x10);
        if (slot->time) {
            slot->ang0[0] = FastAddRotations(slot->ang0[0], slot->rate0[0] * boost);
            slot->ang0[1] = FastAddRotations(slot->ang0[1], slot->rate0[1] * boost);
            slot->ang0[2] = FastAddRotations(slot->ang0[2], slot->rate0[2] * boost);
            slot->ang1[0] = FastAddRotations(slot->ang1[0], slot->rate1[0] * boost);
            slot->ang1[1] = FastAddRotations(slot->ang1[1], slot->rate1[1] * boost);
            slot->ang1[2] = FastAddRotations(slot->ang1[2], slot->rate1[2] * boost);
        } else {
            slot->ang0[0] = FastAddRotations(slot->ang0[0], slot->rate0[0]);
            slot->ang0[1] = FastAddRotations(slot->ang0[1], slot->rate0[1]);
            slot->ang0[2] = FastAddRotations(slot->ang0[2], slot->rate0[2]);
            slot->ang1[0] = FastAddRotations(slot->ang1[0], slot->rate1[0]);
            slot->ang1[1] = FastAddRotations(slot->ang1[1], slot->rate1[1]);
            slot->ang1[2] = FastAddRotations(slot->ang1[2], slot->rate1[2]);
        }
        slot->out0[0] = math_fast_sin_or_cos_a(slot->ang0[0]) * slot->amp0[0];
        slot->out0[1] = math_fast_sin_or_cos_b(slot->ang0[1]) * slot->amp0[1];
        slot->out0[2] = -math_fast_sin_or_cos_b(slot->ang0[2]) * slot->amp0[2];
        slot->out1[0] = math_fast_sin_or_cos_a(slot->ang1[0]) * slot->amp1[0];
        slot->out1[1] = math_fast_sin_or_cos_b(slot->ang1[1]) * slot->amp1[1];
        slot->out1[2] = -math_fast_sin_or_cos_b(slot->ang1[2]) * slot->amp1[2];
        if (slot->target) {
            other = moby_get_private_value_0(slot->target);
            if (other) {
                gravity_get_dir_at_object(slot->target, v, 1);
                FastVecScale(v, v, *(float *)(other + 0x10));
                FastVecAdd(slot->pos, v, slot->target + 0x10);
            } else {
                qcopy(slot->pos, slot->target + 0x10);
            }
            ratio = IntToFloat(slot->time);
            ratio /= IntToFloat(slot->duration);
            lerp_vector(slot->pos, slot->start, slot->pos, 1.0f - ratio);
        }
        if (!math_fast_float_d(&slot->time))
            continue;
        if (*(int *)(slot->target + 0x98) && !slot->hit) {
            FastVecSub(v, slot->pos, slot->start);
            vec_scale_to_length(v, v, 0.033333335f);
            damage = Class31DEE8At(g_item_slot_to_record[0x1C])->f74;
            make_hit_descriptor(&packet, owner, 0x210000, v, damage);
            packet.kind = 1;
            packet.mode = 3;
            packet.id = *(short *)(owner + 0xAA);
            QueueMobyImpact(slot->target, &packet);
            slot->hit = 1;
            part_spawn_hit_sparks(slot->pos, 10, 1);
            StartAttachedEffect(slot->target, 28, *(int *)(owner + 0xB8));
        }
        if (math_fast_float_d(&slot->life)) {
            slot->owner = 0;
            --*(int *)(ctx + 0x1C);
        }
    }
}

/* func_0031E3A8 is defined in 0031E3A8-update.c. */


/* func_0031E560 is defined in 0031E560-dbg.c (-g). */



/* Resets a draw packet to a small square (size 1) with white colour. */
void gfx_init_small_quad_packet(char *packet)
{
    *(long long *)(packet + 112) = 0LL;
    *(int *)(packet + 80) = 0;
    *(int *)(packet + 84) = 0;
    *(float *)(packet + 88) = 1.0f;
    *(int *)(packet + 92) = 0;
    *(int *)(packet + 96) = 0;
    *(float *)(packet + 100) = 1.0f;
    *(float *)(packet + 104) = 1.0f;
    *(float *)(packet + 108) = 1.0f;
    *(float *)(packet + 8) = -1.0f;
    *(float *)(packet + 24) = 1.0f;
    *(float *)(packet + 40) = -1.0f;
    *(float *)(packet + 56) = 1.0f;
    *(float *)(packet + 4) = -1.0f;
    *(float *)(packet + 36) = 1.0f;
    *(float *)(packet + 52) = 1.0f;
    *(int *)(packet + 0) = 0;
    *(int *)(packet + 16) = 0;
    *(int *)(packet + 32) = 0;
    *(int *)(packet + 48) = 0;
    *(float *)(packet + 12) = 1.0f;
    *(float *)(packet + 28) = 1.0f;
    *(float *)(packet + 44) = 1.0f;
    *(long long *)(packet + 128) = 280993940374112LL;
    *(float *)(packet + 20) = -1.0f;
    *(float *)(packet + 60) = 1.0f;
}

/* Finds a point along a smooth curve between two points, given by how far along it is (0 to 1). */
void math_interpolate_cubic_curve(float *out, float *a, float *b, float *c, float *d, float t)
{
    float t2, t3, x, y, z;
    if (t == 0.0f) { qcopy(out, a); return; }
    if (t == 1.0f) { qcopy(out, b); return; }
    t2 = t*t;
    t3 = t2*t;
    y = d[0]-b[0]-(c[0]-a[0]); x = c[0]-a[0]-y; z = b[0]-c[0];
    out[0] = y*t3 + x*t2 + z*t + a[0];
    y = d[1]-b[1]-(c[1]-a[1]); x = c[1]-a[1]-y; z = b[1]-c[1];
    out[1] = y*t3 + x*t2 + z*t + a[1];
    y = d[2]-b[2]-(c[2]-a[2]); x = c[2]-a[2]-y; z = b[2]-c[2];
    out[2] = y*t3 + x*t2 + z*t + a[2];
    out[3] = 0.0f;
}

/* Scales all four corners of a draw packet. */
void gfx_scale_quad_corners(char *packet, float scale)
{
    F2c74c194_FUN_00282D30(packet, packet, scale);
    F2c74c194_FUN_00282D30(packet + 16, packet + 16, scale);
    F2c74c194_FUN_00282D30(packet + 32, packet + 32, scale);
    F2c74c194_FUN_00282D30(packet + 48, packet + 48, scale);
}

/* Spawns a burst of glowing sparks at the object. */
void part_spawn_spark_burst(char *p)
{
    char *q;
    char *o;
    char *r;
    float v;
    float w;

    q = p + 16;
    o = *(char **)(p + 104);
    F5a19df7a_FUN_002FC560(0x47, 0x53001UL);
    F5a19df7a_FUN_0031E2A0(p);
    F5a19df7a_FUN_0031E560(p);

    v = *(float *)(o + 24);
    v = v * 0.5f;
    r = F5a19df7a_FUN_002A7820(80, 96);
    w = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(q, 0x103080, v, r, w, 49, 2);

    v = *(float *)(o + 24);
    v = v * 3.00000011920928955078125e-01f;
    r = F5a19df7a_FUN_002A7820(80, 96);
    w = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(q, 0xFFFFFF, v, r, w, 49, 2);

    v = *(float *)(o + 24);
    v = v * 6.99999988079071044921875e-01f;
    r = F5a19df7a_FUN_002A7820(8, 22);
    w = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(q, 0x803010, v, r, w, 11, 2);

    v = *(float *)(o + 24);
    v = v * 4.49999988079071044921875e-01f;
    r = F5a19df7a_FUN_002A7820(32, 64);
    w = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(q, 0x803010, v, r, w, 11, 2);

    F5a19df7a_FUN_002FC560(0x47, 0x5360bUL);
}

extern float D_FLT_001B5200[];
extern long long GetEffectTextureDescriptor(int);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(void *, void *);
extern void euler_to_matrix(void *, void *);
extern void draw_world_quad(void *, void *, int);

/* Draws one glowing sprite at a position, turned to face the hero. */
void gfx_draw_glow_sprite(char *position, int color, float scale, char *resource, float alpha, int mode, int flag)
{
    unsigned char work[0xE0];
    unsigned int rgba;
    unsigned long long mode_bits;
    float first_angle;
    float second_angle;
    float distance;

    gfx_init_small_quad_packet((char *)work);
    *(long long *)(work + 0x78) = GetEffectTextureDescriptor(mode);

    mode_bits = ((unsigned long long)flag << 2) | 0x0000008000000040ULL;
    *(long long *)(work + 0x88) = mode_bits;
    *(long long *)(work + 0x80) = 0x0000FF9000000260ULL;

    rgba = (unsigned int)color + ((unsigned int)resource << 24);
    *(int *)(work + 0x4C) = rgba;
    *(int *)(work + 0x48) = rgba;
    *(int *)(work + 0x44) = rgba;
    *(int *)(work + 0x40) = rgba;
    *(long long *)(work + 0x70) = 0;

    *(int *)(work + 0xDC) = 0;
    first_angle = mat_fast_helper_a(D_FLT_001B5200[0x140 / 4] - *(float *)(position + 0),
                                D_FLT_001B5200[0x144 / 4] - *(float *)(position + 4));
    *(float *)(work + 0xD8) = first_angle;

    distance = vec_distance_xy(position, &D_FLT_001B5200[0x140 / 4]);
    second_angle = mat_fast_helper_a(distance, D_FLT_001B5200[0x148 / 4] - *(float *)(position + 8));
    *(float *)(work + 0xD0) = alpha;
    *(float *)(work + 0xD4) = -second_angle;

    euler_to_matrix(work + 0x90, work + 0xD0);
    *(float *)(work + 0xC0) = *(float *)(position + 0);
    *(float *)(work + 0xC4) = *(float *)(position + 4);
    *(float *)(work + 0xC8) = *(float *)(position + 8);
    *(float *)(work + 0xCC) = 1.0f;
    gfx_scale_quad_corners((char *)work, scale);
    draw_world_quad(work, work + 0x90, 0);
}


/* func_0031EFC8 uses the profile in 003173B0-qcopy.c. */

/* Adds the next ribbon point by continuing the line of the last two points. */
void gfx_extrapolate_ribbon_point(Vec16_Fc936841d *object, int index)
{
    char local[16];

    Fc936841d_FUN_00282CF0(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    Fc936841d_FUN_00282CC0((char *)&object[index - 1], (char *)&object[index - 2], local);
}

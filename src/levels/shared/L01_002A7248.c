#include "common.h"

extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern float FastVecDot(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int FloatToInt(float);
extern unsigned char *g_burst_particle_color_table;
extern char *strncpy(char *, char *, int);
extern void cancel_hero_item_animation(void);
extern void UpdateHeroSlotCallbacks(void);
extern void hero_set_objects_flag_bit(void);
extern void hero_clear_tracked_slots(void);
extern void attachment_reset_all(void);
extern void hero_clear_queued_anim(void);
extern void func_002A677C(int);
extern void ref_L01_002B3458_00(void);
extern void ref_L01_002B3458_01(int, int);

extern void matrix_mul_vec3(void *, void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void draw_world_quad(void *, void *, int);
extern void gfx_init_quad_packet_state(void *, int, int, int);

extern char *g_moby_l01_table MACRO_ADDR;
extern void *func_00325768(int);
extern int func_002E45B8(float);
extern float func_00310580(float, float);
extern void func_002E3738(void *, void *, float);
extern unsigned char *g_particle_l01_texture_table;

typedef int MotionQuad __attribute__((mode(TI)));
typedef union { float v[4]; MotionQuad q; } MotionVec;

typedef struct {
    MotionVec motion;
    char pad10[0x70];
    MotionVec position;
    char pad90[0x50];
    MotionVec probeEnd;
    char padF0[0x4D0];
    char *held;
} MotionHero;
typedef struct {
    MotionVec velocity;
    char pad10[0x10];
    int flags;
    char pad24[0xC];
    int frame;
    float gain;
    float distance;
    int pad3C;
    int sound;
} MotionState;
typedef struct { MotionVec forward[4]; MotionVec inverse[4]; } MotionPath;

extern MotionHero motionHero __asm__("D_00189E20");
typedef struct {
    char pad00[0x30];
    float hitX;
    float hitY;
} MotionCollision;
extern MotionCollision motionCollision __asm__("D_L01_001BF900");

extern char g_sound_state[];
extern int g_oozla_intro_stage[] __attribute__((sda));
extern MotionPath *g_swamp_patrol_positions[] __attribute__((sda));
extern float g_ground_l01_height;
extern void lerp_vector(void *, void *, void *, float);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern void euler_rotation_basis(void *, void *);
extern int coll_sweep_from_object(void *, void *, int, int, int, int, float, float, float);
extern void vec_clamp_length(void *, float);
extern int IsPointInCuboid(void *, int);
extern int path_push_point_away(int, void *, void *, float);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern int func_L00_002E0200(void *, float, float, int, void *);
extern int moby_push_out_of_wall(void *, void *, void *, void *);

extern void func_002E3470(void *, void *, void *);

typedef int ClosestPointQuad __attribute__((mode(TI)));

typedef struct { char *p[6]; } Sep6;

extern Sep6 g_number_separators;

extern char g_str_number_format_millions[];

extern char g_str_number_format_thousands[];

extern char g_str_number_format_plain[];

extern int func_00115DA8_2(char *dst, char *fmt, ...);

extern char g_hero_l01_state_block[];

extern char g_action_table[];

extern s32 g_hero_l01_control_mode[] __attribute__((sda));

extern char D_L01_00189E20_sda[] __attribute__((sda));

extern void func_002C7CA8(void);

extern void func_002B4070(void);

extern void func_002ADDC8(void);

extern void func_002C37C8(void);

extern void func_002AEB80(void);

extern void func_002B9878(void);

extern void func_002A7740(void);

extern void func_002AB1C8(void);

extern void func_002A9520(void);

extern void func_002A9310(void);

extern void func_002FDB00(void *a0);

extern void func_002AB328(void);

extern void func_0030F444(int a0);

extern char g_hero_l01_state_block[];

extern void func_002A8EE0(int a0, int a1);

extern char g_weapon_id_table[];

extern unsigned char g_screen_mode_flag[];

extern void func_002BEB90(unsigned long, unsigned long);

extern void *g_hero_moby;

extern float g_hero_move_speed_threshold;

extern unsigned short *g_group_list_table[];

extern unsigned short *r1_D_L01_001ABFC0[];

extern char *r1_D_L01_00160058 MACRO_ADDR;

extern int r1_D_L01_00160058_m __asm__("r1_D_L01_00160058") MACRO_ADDR;

extern char *g_path_l01_table[];

typedef struct {
    int path;
    float radius;
    int volumes[6];
    int lists[12];
    int mobys[11];
    signed char switches[4];
} SpatialTriggerSettings;

typedef struct { char prefix[0x2290]; void *moby; } ProbeHero;
typedef struct { char pad[0x18]; void *moby; int count; char gap[0x20]; float normal[4]; } ProbeResult;
extern ProbeResult g_collision_l01_hit;

extern char g_hero_l01_velocity[];

extern int g_collision_hit_count;

extern float cam_get_view_space_vector_length(void *);

extern void hero_build_relative_point(void *, float, float, float, int);

extern float vec_length_xy(void *);

extern void cam_set_view_space_height(void *, void *, float);

extern void FastVecScale(void *, void *, float);

extern int CollLine(void *, void *, int, void *, int);

extern int GetCollHitMaterial(void);

extern float cam_get_view_space_angle(void *);

extern char g_level_origin_vec[];

extern char g_hero_position[];

extern int func_311B48(char *a0, void *a1, int a2);

extern int func_3163C8(char *a0, void *a1);

extern int func_316558(char *a0, void *a1);

extern int func_3164A0(char *a0, void *a1);

extern void func_002E3CD8(void *a0, void *a1);

extern void func_002E3F60(void *a0, void *a1);

extern void func_002E34A0(void *a0, void *a1, void *a2);

extern void func_L01_002E3940(void *a0, void *a1, void *a2);

extern void func_002E3470(void *a0, void *a1, void *a2);

extern void func_002E3918(void *a0, void *a1, void *a2);

extern void func_002E3470(void *a0, void *a1, void *a2);

extern float FastAddRotations(float f12, float f13);

extern float math_fast_sin_or_cos_b(float f12);

extern int FastTweenColor(int a0, int a1, float f12);

extern float math_random_float_range(float f12, float f13);

extern void moby_set_light_color(void *a0, int a1);

extern float func_002E3B10(float f12, float f13);

extern int moby_step_controller(char *a0, char *a1, float f12);

extern char *func_00321F08(int a0);

extern void func_003140B0(char *a0, char *a1, int a2, float f12, float f13,
                          float f14, float f15);

extern char g_map_marker_table[];


extern int g_level_group_index;

extern int g_pair_table_group_offsets[];

extern int g_pair_table_keys[];

extern void func_002A6CF0(int a0);

extern float func_002E3618(void *a0, void *a1);

extern unsigned char g_path_segment_data[];

extern char g_sound_state[];

extern int func_003711D8(int a0);

extern unsigned char g_level_flag_table[];

extern void func_003907B8(int a0, int a1, int a2);


/* Runs the hero's per-frame updates, and the extra ones only while the hero is in a mode that needs them. */
void hero_update_subsystems(void) {
    char *hero;

    func_002C7CA8();
    func_002B4070();
    func_002ADDC8();
    func_002C37C8();
    func_002AEB80();
    hero = g_hero_l01_state_block;
    if (*(unsigned char *)(hero + 0x22B4) != 0) {
        func_002B9878();
        func_002A7740();
        if (*(unsigned char *)(hero + 0x22B4) != 0) {
            func_002AB1C8();
            func_002A9520();
            func_002A9310();
            func_002FDB00(hero + 0x80);
            func_002AB328();
            func_0030F444(*(int *)(hero + 0x2290));
        }
    }
}


/* Starts the effect of the equipped weapon when that weapon has one and the hero holds a target. */
void weapon_update_equipped_effect(void) {
    char *hero = g_hero_l01_state_block;
    int i = *(int *)(hero + 0x1248);
    unsigned char weaponId;
    unsigned char *weapon_entry;

    if (i < 0)
        return;
    weaponId = *(unsigned char *)(g_weapon_id_table + i);
    weapon_entry = (unsigned char *)g_action_table + weaponId * 0xE0;
    if (weapon_entry[4] == 0)
        return;
    if (*(int *)(hero + 0x1220) == 0)
        return;
    func_002A8EE0(*(int *)(hero + 0x1220), *(int *)(hero + 0x2290));
}



typedef int LedgeQuad __attribute__((mode(TI)));
typedef struct {
unsigned char pad0[464];
short cooldown;
unsigned char pad1d2[146];
float radius;
unsigned char pad268[180];
float groundHeight;
unsigned char pad320[382];
unsigned char pastApex;
unsigned char pad49f[1945];
float frame;
unsigned char padc3c[5716];
void * moby;
int state;
unsigned char pad2298[4];
int control;
unsigned char pad22a0[20];
unsigned char vehicle;
} LedgeProbeResident;
extern LedgeProbeResident ledgeHero __asm__("D_00189E20");
extern float func_002C9280(void *);
extern void func_002C92D8(void *, void *, float);
extern float func_002C9628(void *);
extern float func_002E3560(void *, void *);
extern float func_002E3A48(float);
extern int func_002D3C80(void *, void *, int, void *, int);
extern int func_002D77E8(void);
extern char *func_003148A0(void *);
extern char *func_00316D00(void *);
extern int func_002D4CE0(void *, int, void *, float);
typedef struct {
    unsigned char pad0[0x18];
    void *moby;
    unsigned char pad1c[4];
    float position[4];
    unsigned char pad30[16];
    float normal[4];
} LedgeProbeHit;
extern LedgeProbeHit ledgeHit __asm__("D_L01_001BF900");
#define FL(p,o) (*(float *)((char *)(p)+(o)))
#define IN(p,o) (*(int *)((char *)(p)+(o)))
/* The ledge probe of func_L00_002ACF88 without its vehicle == 1 branch. */
int ProbeLedgeGrab(void *position, void *unused, char *out)
{
    float v0[4], v1[4], v2[4], v3[4], v4[4], v5[4], v6[4], v7[4], v8[4], v9[4], v10[4], v11[4], v12[4], v13[4], v14[4], v15[4], v16[4], v17[4], v18[4], v19[4];
    char *model_info, *collision_info;
    void *object;
    int can_grab, found, i, kind, grabbable;
    int edge, j;
    float height;
    float step, max;
    float down, top, drop, d, length;
    LedgeProbeResident *hero;
    if (out) IN(out,0x28)=0;
    if (ledgeHero.cooldown) return 0;
    can_grab=0;
    if (ledgeHero.vehicle==0) {
        if ((ledgeHero.control==4 && (ledgeHero.pastApex || func_002C9280((char *)&ledgeHero+0xf0)<0.05833333730697632f)) || ledgeHero.control==2 || ledgeHero.state==8 || ledgeHero.state==25 || ledgeHero.state==26) can_grab=1;
        if (ledgeHero.state==14 && ledgeHero.frame<37.0f) can_grab=0;
    }
    if (out != (char *)&ledgeHero+0x550) can_grab=1;
    if (!can_grab) return 0;
    hero=&ledgeHero;
    down=-0.7f; top=1.15f; drop=-1.43f;
    found=0;
    qcopy(v0,position);
    func_002E3738(v4,hero,hero->radius);
    func_002E3470(v0,v0,v4);
    func_002E3738(v4,(char *)&ledgeHero+0x20,1.65f);
    func_002E3470(v1,v0,v4);
    func_002E3738(v4,(char *)&ledgeHero+0x20,-top);
    func_002E3470(v2,v0,v4);
    func_002E3738(v3,hero,0.075f);
    for(i=0; i<4; i++) {
        func_002E3470(v1,v1,v3);
        func_002E3470(v2,v2,v3);
        if(func_002D3C80(v1,v2,4,ledgeHero.moby,0)) {
            kind=func_002D77E8();
            if(kind!=9 && kind!=12 && kind!=0 && func_002C9628(ledgeHit.normal)<0.349065899848938f) found=1;
        }
        if(found) break;
    }
    object=0;
    if(!found) goto fail;
    if(ledgeHit.moby) {
        grabbable=0;
        model_info=func_003148A0(ledgeHit.moby);
        collision_info=func_00316D00(ledgeHit.moby);
        if(model_info && (*(unsigned short *)(model_info+0x1e)&1)) grabbable=1;
        else if(collision_info) grabbable=IN(collision_info,0x3c)&1;
        if(!grabbable) return 0;
        object=ledgeHit.moby;
    }
    if(out) *(void **)(out+0x38)=ledgeHit.moby;
    qcopy(v6,ledgeHit.position);
    func_002E34A0(v5,v6,position);
    if(1.5f<func_002C9280(v5)) return 0;
    func_002E3738(v7,(char *)&ledgeHero+0x20,0.005f);
    func_002E3470(v7,v7,v6);
    func_002E3738(v8,(char *)&ledgeHero,-1.0f);
    func_002E3470(v8,v8,v7);
    if(func_002D3C80(v8,v7,2,ledgeHero.moby,0)) {
        if(!ledgeHit.moby || ledgeHit.moby!=object) return 0;
    }
    if(out) {
        func_002E3738(v9,(char *)&ledgeHero+0x20,0.6f);
        func_002E3470(v9,v9,v6);
        if(func_002D4CE0(v9,4,ledgeHero.moby,0.45f)) IN(out,0x34)|=1;
        else IN(out,0x34)&=~1;
    }
    height=func_002C9280(v5);
    if(height+ledgeHero.groundHeight<1.8f || height<0.5f) return 0;
    *(LedgeQuad *)v11=0; FL(v11,0)=1.0f; FL(v11,8)=down;
    func_002E3918(v11,v11,(char *)&ledgeHero);
    edge=0;
    func_002E3470(v11,v11,v6);
    func_002E34A0(v9,position,v11);
    func_002C92D8(v9,v9,0.0f);
    func_002E3470(v9,v9,v11);
    func_002E3738(v10,(char *)&ledgeHero+0x20,-down*0.2f);
    for(j=0;j<5;j++) {
        if(func_002D3C80(v9,v11,2,0,0)) {
            func_002E3738(v12,ledgeHit.normal,1.0f);
            edge=1;
            func_002C92D8(v12,v12,0.0f);
            break;
        }
        func_002E3470(v9,v9,v10);
        func_002E3470(v11,v11,v10);
    }
    if(!edge) return 0;
    length=func_002E3560((char *)&ledgeHero,v12);
    if(!(length<func_002E3A48(1.134464144706726f))) return 0;
    step=0.03f;
    max=2.4f;
    qcopy(v18,v6);
    func_002E3738(v17,(char *)&ledgeHero+0x2c0,-0.05f);
    func_002E3738(v16,v12,step);
    func_002E3470(v15,v16,v17);
    func_002E34A0(v16,v16,v17);
    func_002E3470(v13,v18,v16);
    func_002E3470(v14,v18,v15);
    for(d=0.0f;d<max;d+=step) {
        if(!func_002D3C80(v14,v13,4,ledgeHero.moby,0)) {
            if(out) {
                qcopy(out+0x10,v18);
                func_002E3738(v19,v12,0.5f);
                func_002E3738(out,(char *)&ledgeHero+0x2c0,-drop);
                func_002E3470(out,v19,out);
                func_002E3470(out,out+0x10,out);
                FL(out,0x24)=func_002E3B10(FL(v12,0),FL(v12,4));
                IN(out,0x28)=1;
            }
            return 1;
        }
        qcopy(v18,ledgeHit.position);
        func_002E3470(v14,v18,v15);
        func_002E3470(v13,v18,v16);
    }
fail:
    return 0;
}
#undef FL
#undef IN

typedef int HeroQuad __attribute__((mode(TI)));
extern char g_hero_state[];
extern unsigned char g_item_slot_to_record[];
extern char g_hero_attached_moby_buffers[];
extern int get_ammo(int);
extern int hero_slot_item_id(int);
extern void initialize_moby_animation_blend(void *, void *, int, int, int, int);
extern void AdvanceAndDecodeAnimationFrames(void *, void *);
extern f32 ApproachValue(void *, float, float);
extern void release_moby_animation_slot(void *, void *);
extern void vec_clear_128(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float FastAddRotations(float, float);

/* A moby's model: the part of it the file uses. */
typedef struct MobyModel {
    char pad00[0x10];
    int f10;
    char pad14[0x32];
    short kind;                 /* 0x46 */
} MobyModel;

/* A moby (0x100 bytes), as far as the file uses it. */
typedef struct Moby {
    char pad00[5];
    unsigned char flags;
    char pad06[2];
    float fade;                 /* 0x08: 1.0 fully shown, 0.0 gone */
    char pad0C[0x17];
    unsigned char animation;    /* 0x23 */
    MobyModel *model;           /* 0x24 */
    int f28;
    char pad2C[5];
    unsigned char f31;
    char pad32[2];
    unsigned short state;       /* 0x34 */
    char pad36[2];
    char *buffer0;              /* 0x38 */
    char *buffer1;              /* 0x3C */
    char pad40[0x58];
    int f98;
    char pad9C[0x24];
    HeroQuad matrix[3];         /* 0xC0 */
    char padF0[0x10];
} Moby;

/* One entry of the weapon table (0xE0 bytes). */
typedef struct WeaponInfo {
    char pad00[0x2C];
    int animation;              /* 0x2C */
    int altAnimation;           /* 0x30: used while the hero's state is 12 */
    char pad34[0xAC];
} WeaponInfo;

/* The hero block (D_00189E20), the fields func_L01_002B0318 uses. */
typedef struct HeroState {
    char pad00[0x90];
    HeroQuad position;          /* 0x90 */
    char padA0[0x730 - 0xA0];
    HeroQuad matrix[3];         /* 0x730 */
    float f760;
    char pad764[0xC];
    union {
        HeroQuad quad;
        float v[4];
    } f770;                     /* 0x770: copy of position, z eased to 0 */
    char pad780[0xE98 - 0x780];
    Moby *attached[2];          /* 0xE98 */
    char padEA0[4];
    int attachedMode;           /* 0xEA4: 0 shown, 1 fading out, 2 fading out fast */
    char padEA8[0x2290 - 0xEA8];
    Moby *moby;                 /* 0x2290 */
    char pad2294[8];
    int state;                  /* 0x229C */
    char pad22A0[0x22B8 - 0x22A0];
    unsigned char f22B8;
    char pad22B9;
    unsigned char f22BA;
    char pad22BB[8];
    unsigned char f22C3;
    char pad22C4[0x24B0 - 0x22C4];
    int animation;              /* 0x24B0 */
    int weaponId;               /* 0x24B4 */
} HeroState;

/* For the hero's two attached mobys: point them at their buffers, start the animation the
   current item's table entry names, fade them in or out (removing one that has faded out),
   then copy the hero moby's matrix to hero + 0x730 and ease hero + 0x778 to 0. */
void hero_update_attached_mobys(void)
{
    HeroState *hero;
    HeroState *state;
    HeroQuad *matrix;
    WeaponInfo *weapon;
    int weaponId, animation;
    int i;

    hero = (HeroState *)g_hero_state;
    if (hero->f22B8 && hero->f22BA && !get_ammo(-1))
        cancel_hero_item_animation();
    for (i = 0; i < 2; i++) {
        HeroState *player = (HeroState *)g_hero_state;
        Moby **slot = &player->attached[i];

        if (*slot) {
            (*slot)->buffer0 = g_hero_attached_moby_buffers + i * 0xC00;
            (*slot)->buffer1 = g_hero_attached_moby_buffers + 0x600 + i * 0xC00;
            weaponId = hero_slot_item_id(0);
            if (weaponId == player->weaponId) {
                weapon = &((WeaponInfo *)g_action_table)[g_item_slot_to_record[weaponId]];
                animation = weapon->animation;
                if (player->state == 12)
                    animation = weapon->altAnimation;
                if (animation != -1 && (*slot)->animation != animation) {
                    player->animation = animation;
                    initialize_moby_animation_blend(player->moby, *slot, animation, 0, 8, 1);
                }
            }
            {
                HeroState *owner = (HeroState *)g_hero_state;

                AdvanceAndDecodeAnimationFrames(owner->moby, *slot);
                if (owner->attachedMode) {
                    if (owner->attachedMode == 2)
                        ApproachValue(&(*slot)->fade, 0.0f, 0.25f);
                    else
                        ApproachValue(&(*slot)->fade, 0.0f, 0.07f);
                    hero = (HeroState *)g_hero_state;
                    if ((*slot)->fade == 0.0f) {
                        release_moby_animation_slot(hero->moby, slot);
                        return;
                    }
                } else {
                    ApproachValue(&(*slot)->fade, 1.0f, 0.2f);
                    if (((*slot)->flags & 2) && !owner->f22BA) {
                        owner->attachedMode = 1;
                        (*slot)->f28 = 0;
                        owner->f22B8 = 0;
                        return;
                    }
                }
            }
        }
    }
    matrix = ((HeroState *)g_hero_state)->matrix;
    state = (HeroState *)g_hero_state;
    {
        Moby *moby = state->moby;

        matrix[0] = moby->matrix[0];
        matrix[1] = moby->matrix[1];
        matrix[2] = moby->matrix[2];
        vec_clear_128(&state->f760);
    }
    state->f760 = 1.0f;
    matrix_mul_vec3(&state->f760, &state->f760, matrix);
    state->f770.quad = state->position;
    if (!state->f22C3)
        state->f770.v[2] = FastAddRotations(state->f770.v[2], 0.0f);
}

extern void cancel_hero_item_animation(void);
extern void UpdateHeroSlotCallbacks(void);
extern void level_release_slot_list(char *a0);
extern void hero_set_objects_flag_bit(void);
extern void hero_clear_tracked_slots(void);
extern void attachment_reset_all(void);
extern void hero_clear_queued_anim(void);
extern void func_002A677C(int a0);
extern s32 SetHeroMoveState(int a0, int a1);
extern void hero_l01_update_blend_channels(void);
extern char g_hero_state[];

/* Switches the hero to a new mode and a new moby, and resets the hero's state for it. */
void hero_switch_mode_and_moby(int mode, int move_state, int new_moby) {
    char *old_hero = g_hero_state;

    cancel_hero_item_animation();
    old_hero[0x22B6] = 1;
    UpdateHeroSlotCallbacks();
    *(int *)(old_hero + 0x2290) = *(int *)(old_hero + 0xC18);
    level_release_slot_list(old_hero + 0x18E0);
    level_release_slot_list(old_hero + 0x1A30);
    *(int *)(*(int *)(old_hero + 0x2290) + 0x9C) = -1;
    if (mode != 4 || *(unsigned char *)(old_hero + 0x22B4) != mode)
        hero_set_objects_flag_bit();
    hero_clear_tracked_slots();
    attachment_reset_all();
    {
        char *hero_for_mode = g_hero_state;

        *(unsigned char *)(hero_for_mode + 0x22B4) = mode;
        *(int *)(hero_for_mode + 0xC14) = new_moby;
        *(int *)(hero_for_mode + 0x2290) = new_moby;
    }
    hero_l01_update_blend_channels();
    {
        char *hero_for_state = g_hero_state;

        *(float *)(hero_for_state + 0x250) = *(float *)(hero_for_state + 0x258);
        *(float *)(hero_for_state + 0x254) = *(float *)(hero_for_state + 0x25C);
        *(unsigned short *)(*(int *)(hero_for_state + 0x2290) + 0x34) |= 6;
        *(float *)(hero_for_state + 0xC20) = 1.0f;
        *(float *)(hero_for_state + 0xC24) = 1.0f;
        hero_clear_queued_anim();
        func_002A677C(*(int *)(hero_for_state + 0x2290));
        *(unsigned short *)(hero_for_state + 0x24F2) = move_state;
    }
    SetHeroMoveState(move_state, 2);
}



/* func_L01_002B3788 is defined in L01_002B3788-contact.c. */

/* func_L01_002B3D28 is defined in L01_002B3D28.c. */



/* Stops the hero against a wall: casts two rays along the movement direction (or the vector at
   the start of the hero's data when forced or nearly still), keeps the moby it hit and takes the
   velocity component into the wall's flattened normal away. */
void ClipHeroVelocityAgainstWall(int force)
{
    float origin[4] __attribute__((aligned(16)));
    float endpoint[4] __attribute__((aligned(16)));
    float lowOrigin[4] __attribute__((aligned(16)));
    float farEndpoint[4] __attribute__((aligned(16)));
    float height, radius, slope;
    int material;
    char *base;
    char *velocity = g_hero_l01_velocity;

    if (cam_get_view_space_vector_length(velocity) < 0.0016666668f)
        return;
    base = velocity - 0xF0;
    height = 0.37f;
    radius = 0.5f;
    if ((unsigned)(*(int *)(base + 0x229C) - 17) < 2) {
        height = 0;
        radius = 0.7f;
    }
    hero_build_relative_point(origin, 0, 0, height, 1);
    hero_build_relative_point(lowOrigin, 0, 0, height * 0.3f, 1);
    if (force || vec_length_xy(velocity) < 0.01f) {
        vec_scale_to_length(endpoint, base, radius);
        vec_scale_to_length(farEndpoint, base, radius * 1.4f);
    } else {
        cam_set_view_space_height(endpoint, velocity, 0);
        vec_scale_to_length(endpoint, endpoint, radius);
        FastVecScale(farEndpoint, endpoint, 1.4f);
    }
    FastVecAdd(endpoint, endpoint, origin);
    material = -1;
    FastVecAdd(farEndpoint, farEndpoint, lowOrigin);
    {
        char *hero = g_hero_l01_state_block;

        if (CollLine(lowOrigin, farEndpoint, 2, ((ProbeHero *)hero)->moby, 0) && g_collision_hit_count > 0)
            material = GetCollHitMaterial();
    }
    slope = 0;
    {
        char *hero = g_hero_l01_state_block;

        if (CollLine(origin, endpoint, 2, ((ProbeHero *)hero)->moby, 0) && g_collision_l01_hit.count > 0)
            slope = cam_get_view_space_angle(g_collision_l01_hit.normal);
    }
    if (slope >= 0.8726647f || material == 8 || material == 12) {
        float dot;
        char *hero = g_hero_l01_state_block;

        *(void **)(hero + 0x270) = g_collision_l01_hit.moby;
        cam_set_view_space_height(g_collision_l01_hit.normal, g_collision_l01_hit.normal, 0);
        vec_scale_to_length(g_collision_l01_hit.normal, g_collision_l01_hit.normal, 1);
        dot = FastVecDot(g_collision_l01_hit.normal, hero + 0xF0);
        if (dot < 0) {
            FastVecScale(g_collision_l01_hit.normal, g_collision_l01_hit.normal, -dot);
            FastVecAdd(hero + 0xF0, hero + 0xF0, g_collision_l01_hit.normal);
        }
    }
}

/* func_L01_002B5EA0 is in L01_002A7248-collide-g8.c. */

/* func_L01_002B6948 is in L01_002B6948-velocity.c. */

/* func_L01_002BE0E0 is defined in L01_002A7248-timers-g8.c. */

/* Puts the hero into move state 1 or 2 unless a lock flag is set. */
void hero_start_move_state_walk_or_run(unsigned long alternate) {
    unsigned long mode = 1;
    if (alternate)
        mode = 2;
    if (g_screen_mode_flag[0] == 0)
        func_002BEB90(0, mode);
}

/* func_L01_002C2CF0 is defined in L01_002C2CF0-keep-block-order.c. */

/* Sets the first flag bit on the hero's moby. */
void hero_set_moby_flag(void) {
    *(unsigned short *)((char *)g_hero_moby + 0x34) |= 1;
}

/* Clears the first flag bit on the hero's moby. */
void hero_clear_moby_flag(void) {
    *(unsigned short *)((char *)g_hero_moby + 0x34) &= 0xFFFE;
}

/* Puts the hero into one of two move states depending on a speed value. */
void hero_set_move_state_by_speed(void) {
    if (g_hero_move_speed_threshold < 0.045f)
        func_002BEB90(0, 1);
    else
        func_002BEB90(3, 1);
}


/* Transforms each entry of a list by a matrix and then redraws the list several times with a growing matrix. */
void gfx_transform_and_draw_entries(char *entries, int entry_count, char *matrix, int passes, char *draw_arg) {
    float step_matrix[12];
    char *next_row;
    char *row;
    char *draw_ptr;
    int remaining;
    int i;

    if (entry_count > 0) {
        row = entries + 0x30;
        next_row = entries + 0x20;
        remaining = entry_count;
        for (; remaining != 0; remaining--) {
            matrix_mul_vec3(next_row, next_row, matrix);
            next_row += 0x90;
            matrix_mul_vec3(row, row, matrix);
            row += 0x90;
        }
    }
    multiply_matrix3x3(step_matrix, matrix, matrix);
    for (i = 0; i < passes; i++) {
        int k = (i & 1) ? 2 : 0;
        if (entry_count > 0) {
            next_row = entries + (k * 16 + 16);
            row = entries + k * 16;
            draw_ptr = entries;
            remaining = entry_count;
            while (remaining != 0) {
                matrix_mul_vec3(row, row, step_matrix);
                remaining--;
                row += 0x90;
                matrix_mul_vec3(next_row, next_row, step_matrix);
                next_row += 0x90;
                draw_world_quad(draw_ptr, draw_arg, 1);
                draw_ptr += 0x90;
            }
        }
    }
}


/* func_L01_002E1680 is defined in L01_002E1680.c. */

/* Draws a textured quad with the given corners and colour; rotate turns the texture
   coordinates by that many quarter turns. */
void DrawQuadWithRotatedUVs(MotionVec *corners, int texture, int kind, int color, int rotate)
{
    struct {
        MotionVec pos[4];
        int color[4];
        float uv[4][2];
        char reserved[32];
    } packet;
    float rotated[4][2];
    int i, j, k;

    gfx_init_quad_packet_state(&packet, texture, kind, 128);
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;

    packet.uv[0][0] = 0.0f;
    packet.uv[0][1] = 0.0f;
    packet.uv[1][0] = 0.0f;
    packet.uv[1][1] = 1.0f;
    packet.uv[2][0] = 1.0f;
    packet.uv[2][1] = 0.0f;
    packet.uv[3][0] = 1.0f;
    packet.uv[3][1] = 1.0f;
    if (rotate) {
        for (j = 0; j < 4; j++) {
            rotated[j][0] = packet.uv[j][0];
            rotated[j][1] = packet.uv[j][1];
        }
        for (k = 0; k < 4; k++) {
            packet.uv[k][0] = rotated[(k + rotate) % 4][0];
            packet.uv[k][1] = rotated[(k + rotate) % 4][1];
        }
    }

    for (i = 0; i < 4; i++) {
        qcopy(&packet.pos[i], &corners[i]);
        packet.pos[i].v[3] = 1;
    }
    draw_world_quad(&packet, 0, 0);
}

/* func_L01_002EABA8 is defined in L01_002A7248-pre.c. */


/* Defined in L01_002F14E8-g8.c. */

/* func_L01_002F1588 is defined in L01_002F1588.c. */



/* Original assembly: level copy of func_0029D7C0 (RAC1 miscproc func_0020C758): live-in $v1 and unconditional `teq` traps. */
ASM_FUNC("asm/levels", func_L01_00304270);

/* Defined in L01_00310BC0.c. */

/* rac1-decomp src/overlays/shared/mobyutil_0026E8E0.c: func_L01_0026F090 */
// Walks a list of moby indices and sets the state byte of each one that is non-negative.
/* Walks a list of moby indices and sets the state byte of each one that is still in use. */
void moby_set_state_in_list(int list, int state)
{
    unsigned short *cursor;
    unsigned short *index_list = (unsigned short *)r1_D_L01_001ABFC0[list];
    if (index_list != 0) {
        cursor = index_list;
        do {
            char *moby = (char *)(((*cursor & 0x7FFF) << 8) + r1_D_L01_00160058_m);
            if (moby[0x20] >= 0) {
                moby[0x20] = state;
            }
        } while (*(short *)cursor++ >= 0);
    }
}

/* Defined in L01_00311C18.c. */

/* func_L01_003120A8 is defined in L01_003120A8-helpers.c. */

/* Resets two values in a moby's private data to their starting values. */
void moby_reset_vars_defaults(char *vars) {
    *(int *)(vars + 0x70) = 0;
    *(float *)(vars + 0x74) = 0.2f;
}


/* chain of four probes on the same object; the first that reports a hit picks the code */
/* Tests a point against four shapes in turn and says which one it is inside of, or 0 if none. */
int coll_test_point_against_shapes(char *point, int shape_index, char *shape_b, char *shape_c, char *shape_d) {
    if (shape_index >= 0) {
        char *shape = g_path_l01_table[shape_index];
        if (func_311B48(point, shape + 0x10, *(int *)shape))
            return 1;
    }
    if (func_3163C8(point, shape_b))
        return 2;
    if (func_316558(point, shape_c))
        return 3;
    if (func_3164A0(point, shape_d))
        return 4;
    return 0;
}

/* Moves an offset through two rotation matrices and writes the result relative to an origin. */
void mat_transform_offset_two_matrices(void *source, void *result, void *origin, void *rotation_a, void *rotation_b) {
    float matrix_a[0x10];
    float matrix_b[0x10];
    float offset[4];

    func_002E3CD8(matrix_a, rotation_a);
    func_002E3F60(matrix_a, matrix_a);
    func_002E3CD8(matrix_b, rotation_b);
    func_002E34A0(offset, source, origin);
    func_L01_002E3940(offset, offset, matrix_a);
    func_L01_002E3940(offset, offset, matrix_b);
    func_002E3470(result, offset, origin);
}

/* func_L01_00318638 is defined in L01_00318638-qcopy-barrier.c. */

/* Turns a local offset into a world point using the moby's matrix and position. */
void moby_compute_local_point(char *moby, float *out, float x, float y, float z) {
    out[0] = x;
    out[1] = y;
    out[2] = z;
    func_002E3918(out, out, moby + 0xC0);
    func_002E3470(out, out, moby + 0x10);
}

/* Retail compares the vertical speed on landing, then stores the same value on both sides of the
 * test, so this call's arms merge at jump2 and only the comparison stays behind. */
static inline void MotionLandingSpeed(float *speed, float rising, float falling)
{
    if (0 < *speed) {
        *speed = rising;
    } else {
        *speed = falling;
    }
}

/* Moves a crate-like moby that the hero can push or drag: applies friction, gravity, pushback from walls and plays its sliding sound. */
void pushable_moby_update(char *moby, MotionState *state, int path, float height, float radius, float extent)
{
    MotionVec old, start, delta, turn, target, change, samples[8], matrix[3], actual;
    float speed, gain, limit, accel, ground;
    int i, handle;
    int phase = g_oozla_intro_stage[0];

    if ((phase & 15) == (((int)moby >> 8) & 15)) {
        float dist = fast_vec_dist(&motionHero.position, moby + 0x10);

        if (*(unsigned short *)(moby + 0x34) & 0x1000) {
            if (state->distance < dist) {
                *(unsigned short *)(moby + 0x34) &= 0xEFFF;
            }
        } else if (dist < state->distance) {
            *(unsigned short *)(moby + 0x34) |= 0x1000;
        }
    }
    qcopy(&old, moby + 0x10);
    if (motionHero.held == moby) {
        qcopy(&start, moby + 0x10);
        start.v[2] += 0.5f;
        if (CollLine(&start, &motionHero.probeEnd, 2, moby, 0)) {
            motionHero.held = 0;
        }
        FastVecSub(&delta, moby + 0x10, &motionHero.position);
        if (state->frame != -1 && IsPointInCuboid(moby + 0x10, state->frame)) {
            matrix_mul_vec3(&delta, &delta, g_swamp_patrol_positions[0][state->frame].inverse);
            delta.v[1] = 0;
            matrix_mul_vec3(&delta, &delta, g_swamp_patrol_positions[0][state->frame].forward);
        }
        gain = 4.0f;
        if (state->gain != 0) {
            gain = state->gain;
        }
        vec_fast_normalize_helper(&delta, &delta, gain);
        FastVecAdd(&delta, &delta, &motionHero.position);
        vec_scale_to_length(&turn, &motionHero.motion, gain);
        FastVecAdd(&turn, &turn, &motionHero.position);
        turn.v[2] = delta.v[2];
        lerp_vector(&delta, &delta, &turn, 0.5f);
        FastVecSub(&delta, &delta, &motionHero.position);
        vec_scale_to_length(&delta, &delta, gain);
        FastVecAdd(&delta, &delta, &motionHero.position);
        if (state->flags & 4) {
            gain = vec_distance_xy(moby + 0x10, &delta) * 0.5333333611f;
            accel = 0.01388888899f;
            limit = 0.2666666806f;
        } else {
            gain = vec_distance_xy(moby + 0x10, &delta) * 0.06666667014f;
            accel = 0.00555555569f;
            limit = 0.1333333403f;
        }
        if (limit < gain) {
            gain = limit;
        }
        FastVecSub(&target, &delta, moby + 0x10);
        target.v[2] = 0;
        vec_scale_to_length(&target, &target, gain);
        FastVecSub(&change, &target, state);
        vec_clamp_length(&change, accel);
        state->velocity.v[0] += change.v[0];
        state->velocity.v[1] += change.v[1];
    } else {
        speed = FastVecLength(state);
        ApproachValue(&speed, 0, 0.002777777845f);
        vec_scale_to_length(state, state, speed);
    }
    if (0.001f < FastVecLength(state)) {
        if (!(state->flags & 2)) {
            qcopy(&start, moby + 0x10);
            qcopy(&delta, moby + 0x10);
            start.v[2] += 0.25f;
            delta.v[2] -= 1;
            ground = 0;
            if (CollLine(&start, &delta, 16, moby, 0)) {
                ground = g_ground_l01_height;
            }
            if (*(float *)(moby + 0x18) < ground) {
                *(float *)(moby + 0x18) = ground;
                MotionLandingSpeed(&state->velocity.v[2], 0, 0);
            } else {
                state->velocity.v[2] -= 0.00555555569f;
            }
        }
        if (!(state->flags & 4) && vec_distance_xy(moby + 0x10, &motionHero.position) < radius + 2.5f) {
            float toward;

            FastVecSub(&start, &motionHero.position, moby + 0x10);
            start.v[2] = 0;
            vec_scale_to_length(&start, &start, 1);
            toward = FastVecDot(&start, state);
            if (0 < toward) {
                vec_scale_to_length(&delta, &start, -toward);
                FastVecAdd(state, state, &delta);
            }
        }
        turn.q = 0;
        turn.v[2] = 0.7853982449f;
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        qcopy(&delta, moby + 0x10);
        delta.v[2] += 0.25f;
        euler_rotation_basis(matrix, &turn);
        vec_fast_normalize_helper(&start, state, radius);
        for (i = 0; i < 8; i++) {
            matrix_mul_vec3(&start, &start, matrix);
            FastVecAdd(&samples[i], moby + 0x10, &start);
            samples[i].v[2] += 0.25f;
            moby_push_out_of_wall(moby, state, &delta, &samples[i]);
        }
        FastVecScale(&target, state, 5);
        FastVecAdd(&target, &target, moby + 0x10);
        target.v[2] += radius;
        coll_sweep_from_object(moby, &target, 0x4000000, 0, 1, 0, radius + 0.2f, 1, 1);
        qcopy(&change, moby + 0x10);
        change.v[2] += height;
        if (func_L00_002E0200(&change, radius, extent, 0, moby)) {
            *(float *)(moby + 0x10) = motionCollision.hitX;
            *(float *)(moby + 0x14) = motionCollision.hitY;
        }
        if (path != -1) {
            path_push_point_away(path, moby + 0x10, moby + 0x10, radius);
        }
        FastVecSub(&actual, moby + 0x10, &old);
        gain = vec_length_xy(&actual);
        if (gain < vec_length_xy(state)) {
            state->velocity.v[0] = actual.v[0];
            state->velocity.v[1] = actual.v[1];
        }
        if (vec_length_xy(state) != 0) {
            char *sound = g_sound_state + state->sound * 0x70;

            if (*(char **)(sound + 0x88) != moby || !((unsigned char *)sound)[0x74]) {
                state->sound = PlayMobySound(0, 4, moby);
            }
        } else {
            handle = state->sound;
            if (handle != -1) {
                unsigned char *sound = (unsigned char *)g_sound_state + handle * 0x70;

                if (*(char **)(sound + 0x88) == moby && sound[0x74]) {
                    snd_stop_voice(handle);
                }
            }
            state->sound = -1;
        }
    } else {
        handle = state->sound;
        if (handle != -1) {
            char *sound = g_sound_state + handle * 0x70;

            if (*(char **)(sound + 0x88) == moby && ((unsigned char *)sound)[0x74]) {
                snd_stop_voice(handle);
            }
        }
        state->sound = -1;
    }
}

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;
extern float math_fabs(float f12);

/* Casts a short ray for a moby and, if it hits a wall, pushes the moby back out of it. */
int moby_push_out_of_wall(void *moby, void *unused, void *from, void *to) {
    Vector to_hit, normal;
    float saved_height;
    float pushback;
    char *hit;
    char *normal_ptr;
    char *hit_moby;
    int hit_class;

    if (CollLine(from, to, 0x10, moby, 0) == 0)
        goto fail;
    hit = (char *)&g_collision_l01_hit;
    hit_moby = *(char **)(hit + 0x18);
    if (hit_moby != 0) {
        hit_class = *(short *)(hit_moby + 0xAA);
        if (hit_class == 0x881 || hit_class == 0)
            return 0;
        saved_height = *(float *)(moby + 0x18);
    } else {
        saved_height = *(float *)(moby + 0x18);
    }
    qcopy(&normal, hit + 0x40);
    normal_ptr = hit + 0x40;
    vec_scale_to_length(normal.f, normal.f, 1.0f);
    FastVecSub(&to_hit, to, hit + 0x20);
    pushback = math_fabs(FastVecDot(to_hit.f, normal.f));
    vec_scale_to_length(normal.f, (float *)normal_ptr, pushback);
    FastVecAdd(moby + 0x10, moby + 0x10, &normal);
    *(float *)(moby + 0x18) = saved_height;
    return 1;
fail:
    return 0;
}


int PulseColor(int a0, int a1, float phase) {
    float v = math_fast_sin_or_cos_b(phase);
    return FastTweenColor(a0, a1, v * 0.5f + 0.5f);
}




/* Makes a glow flicker with a changing colour and fades its brightness up or down. */
void glow_flicker_update(void *moby, float *phase, int active) {
    unsigned char *bytes = (unsigned char *)moby;
    float wave;
    int color;

    if (bytes[0x23] == 0 && active == 0)
        return;

    wave = FastAddRotations(*phase, 0.14544412f);
    *phase = wave;
    wave = math_fast_sin_or_cos_b(wave);
    color = FastTweenColor(0x8000C020, 0x80008000, (wave + 0.5f) * 0.5f);
    if (math_random_float_range(0.0f, 1.0f) < 0.05f)
        color = FastTweenColor(color, 0x8080FFFF, 0.3f);
    moby_set_light_color(moby, color);

    if (active != 0) {
        if (bytes[0x23] < 0x3D)
            bytes[0x23] = bytes[0x23] + 3;
        else
            bytes[0x23] = 0x40;
    } else {
        if (bytes[0x23] >= 4)
            bytes[0x23] = bytes[0x23] - 3;
        else
            bytes[0x23] = 0;
    }
}

/* One entity of the group: the kind word is at 0xAA. */
typedef struct L01Thing {
    u8 pad[0xAA];
    s16 kind;
} L01Thing;

/* The group: the count is at 0x44, the list of entities at 0x18C. */
typedef struct L01Group {
    u8 pad[0x44];
    s16 count;
    u8 pad46[0x18C - 0x46];
    L01Thing *items[1];     /* bounded by count */
} L01Group;

extern L01Group g_ship_trail_state;
extern u8 g_unlocked_item_flags[] __attribute__((sda));
extern u8 g_effect_match_flags[] __attribute__((sda));
extern f32 g_effect_match_values[] __attribute__((sda));
extern void AttachManipulator(u8 *p, int a1, u8 *a2);

/* Starts an effect on every thing in the group that has the wanted kind. */
void part_spawn_effect_on_matching_things(L01Thing *entry, s32 effect_id, s32 id, f32 value)
{
    L01Thing *thing;
    s32 wanted;
    s32 i;

    if (g_hero_l01_control_mode[0] != 2)
        return;
    if (g_unlocked_item_flags[0] == 0)
        return;
    wanted = entry->kind;
    if (id != -1)
        wanted = id;
    for (i = 0; i < g_ship_trail_state.count; i++) {
        thing = g_ship_trail_state.items[i];
        if (thing->kind != wanted)
            continue;
        if (g_effect_match_flags[1] != 0)
            continue;
        AttachManipulator((u8 *)thing, effect_id, g_effect_match_flags);
        g_effect_match_values[0] = value;
        g_effect_match_values[1] = value;
        g_effect_match_values[2] = value;
    }
}

/* Turns a moby to face a target point. */
int moby_l01_turn_toward_target(char *moby, char *target) {
    float angle = func_002E3B10(*(float *)(target + 0) - *(float *)(moby + 0x10),
                            *(float *)(target + 4) - *(float *)(moby + 0x14));
    return moby_step_controller(moby, target, angle);
}

/* Starts an effect on a moby using values from its table entry. */
int moby_start_effect_from_entry(int moby, float value) {
    char *entry = func_00321F08(moby);
    if (entry == 0)
        return 0;
    func_003140B0((char *)moby + 0xF8, entry + 0xB4, 0, value, *(float *)(entry + 0x14),
                  *(float *)(entry + 0x18), *(float *)(entry + 0x1C));
    return 1;
}



/* shared native body of family d1b66aa7f0ecd20d */
/* Writes a number as text with thousands separators, such as 1,234,567. */
void text_format_number_separators(char *dst, int number, int idx)
{
    Sep6 separators;
    separators = g_number_separators;
    if (number > 999999) {
        int millions = number / 1000000;
        int remainder = number % 1000000;
        func_00115DA8_2(dst, g_str_number_format_millions, millions, separators.p[idx % 6], remainder / 1000,
                          separators.p[idx % 6], remainder % 1000);
    } else if (number >= 1000)
        func_00115DA8_2(dst, g_str_number_format_thousands, number / 1000,
                          separators.p[idx % 6], number % 1000);
    else
        func_00115DA8_2(dst, g_str_number_format_plain, number);
}


extern char *strncpy(char *dst, char *src, int len);

/* Expands a template: copies src into the scratchpad, then writes it to out, replacing %d (next number) and %<n>d (n-th number) with the numbers listed in nums (every second int, up to ten, stopped by -1). */
void text_expand_number_template(char *out, char *src, int *nums)
{
    int numbers[10];
    unsigned char digits[32];
    int count;
    int *num_ptr;
    int *table_ptr;
    unsigned char *read_ptr;
    char *write_ptr;
    int copied;
    int next_index;
    int value;

    num_ptr = nums;
    count = 0;
    strncpy((char *)0x70000000, src, 0xFF);

    table_ptr = numbers;
    for (;;) {
        num_ptr += 2;
        value = num_ptr[-2];
        if (value == -1)
            break;
        *table_ptr++ = value;
        count++;
        if (count >= 10)
            break;
    }

    read_ptr = (unsigned char *)0x70000000;
    write_ptr = out;
    next_index = 0;
    while (*read_ptr != 0) {
        if (*read_ptr == '%') {
            if (read_ptr[1] == 'd') {
                value = next_index++;
                read_ptr += 2;
            } else {
                value = read_ptr[1] - '0';
                read_ptr += 3;
            }
            text_format_number_separators((char *)digits, numbers[value], 0);
            copied = 0;
            if (*digits != 0) {
                while (digits[copied] != 0 && copied < 32) {
                    *write_ptr = digits[copied];
                    copied++;
                    write_ptr++;
                }
            }
            *write_ptr = 0;
        } else {
            *write_ptr = *read_ptr;
            read_ptr++;
            write_ptr++;
        }
    }
    *write_ptr = 0;
}


/* func_L01_00324550 is in L01_00324550-narrowsave.c. */

/* func_L01_003245E0 is defined in L01_002A7248-g8.c (this unit has no $gp access for it). */

/* Marks an entry of the table as used if it is not already. */
void level_mark_table_entry_used(int index) {
    char *table = g_map_marker_table;
    char *entry;
    table = table + 0xC;
    entry = table + index * 16;
    if (*(int *)entry == 0)
        *(int *)entry = 1;
}

/* func_L01_003246D0 is defined in L01_003246D0.c. */

/* Scans the half-open span of the pair table for the caller's key. */
int level_find_key_in_pair_table(int key) {
 unsigned group=(unsigned)g_level_group_index;
 int i;
 int end;
 if(group>=0x13) return 0;
 i=g_pair_table_group_offsets[group];
 end=g_pair_table_group_offsets[group+1];
 while(i<end) {
  if(g_pair_table_keys[i]==key) return i;
  i++;
 }
 return -1;
}

typedef union {
    ClosestPointQuad q;
    float v[4];
} ParticleVec;

typedef struct SpanParticle {
    unsigned char f0;
    unsigned char f1;
    unsigned char texture;      /* 2 */
    unsigned char f3;
    int color0;                 /* 4 */
    char pad8;
    unsigned char f9;
    short kind;                 /* 0xA */
    int color1;                 /* 0xC */
    ParticleVec start;          /* 0x10: v[3] is the life */
    ParticleVec end;            /* 0x20: start plus the scaled velocity, v[3] = 1 */
    ParticleVec velocity;       /* 0x30: v[3] is the caller's scale */
} SpanParticle;

/* RAC1 counterpart: src/overlays/shared/span_particle.c, spawn_span_particle. */
/* Spawns a span particle of the given kind (0 to 2) at pos, moving along vec and carrying scale. */
void SpawnSpanParticle(float *pos, int kind, float *vec, float scale)
{
    float velocity[4];
    float *velocityPtr = velocity;
    float scaled[4];
    float end[4];
    SpanParticle *p;
    int alpha;
    float speed;
    float life;
    int texture;

    *(ClosestPointQuad *)velocity = *(ClosestPointQuad *)vec;
    p = func_00325768(0);
    if (p != 0) {
        alpha = 0;
        texture = kind;
        life = 0.0f;
        speed = life;
        switch (texture) {
        case 0:
            alpha = 0x14;
            life = 0.015f;
            speed = func_00310580(0.01f, 1.0f);
            break;
        case 1:
            alpha = 0xD;
            life = 0.5f;
            speed = func_00310580(1.0f, 5.0f);
            break;
        case 2:
            alpha = 0xD;
            life = 1.0f;
            texture = 1;
            speed = func_00310580(20.0f, 30.0f);
            break;
        }
        *(ClosestPointQuad *)scaled = *(ClosestPointQuad *)velocityPtr;
        func_002E3738(scaled, scaled, speed);
        p->kind = kind;
        p->color0 = ((alpha >> 2) << 24) | 0x606060;
        p->color1 = (alpha << 24) | 0x907070;
        p->f9 = func_002E45B8(4.0f) + 0x60;
        p->f3 = 0x44;
        p->f1 = 3;
        p->texture = g_particle_l01_texture_table[texture];
        p->start.q = *(ClosestPointQuad *)pos;
        func_002E3470(end, pos, scaled);
        p->end.q = *(ClosestPointQuad *)end;
        p->start.v[3] = life;
        p->end.v[3] = 1.0f;
        p->velocity.q = *(ClosestPointQuad *)velocityPtr;
        p->velocity.v[3] = scale;
    }
}

typedef int Quad331CA0 __attribute__((mode(TI)));
typedef struct { unsigned char b0, b1, b2, b3; int color; unsigned char seed, alpha; unsigned short size; float life; union { Quad331CA0 q; float f[4]; } position; float payload[8]; } Particle331CA0;
extern Particle331CA0 *part_alloc(int kind);
extern float math_random_float_range(float low, float high);
extern int FloatToInt(float value);
extern unsigned char *g_burst_particle_color_table;

/* Spawns the burst particle of the given kind at position, carrying the velocity and the size scale in its payload. */
void part_l01_spawn_burst_2(Quad331CA0 *position, int kind, Quad331CA0 *velocity, float scale)
{
    Quad331CA0 saved = *velocity;
    Quad331CA0 *vp = &saved;
    Particle331CA0 *p = part_alloc(0x49);

    if (p) {
        float life = 0.0f;
        int tint = 0;

        switch (kind) {
        case 0:
            math_random_float_range(0.25f, 0.25f);
            life = 0.12f;
            tint = 0x20;
            break;
        case 1:
            math_random_float_range(1.0f, 1.0f);
            life = 0.5f;
            tint = 0xD;
            break;
        }
        p->size = 0x37;
        p->color = (tint << 24) | 0xFFFFFF;
        p->alpha = FloatToInt(4.0f) + 0x20;
        p->b1 = 0;
        p->b3 = 0x48;
        p->b2 = g_burst_particle_color_table[kind];
        p->life = life * 210000.0f;
        p->seed = math_random_float_range(0.0f, 360.0f);
        p->position.q = *position;
        *(Quad331CA0 *)p->payload = *vp;
        p->payload[3] = scale;
    }
}


/* func_L01_00331E08 is in L01_00331E08.c. */

/* Averages each 16-byte record of the table the argument points at against the record
   (i + 1) % n, storing the result in the record's own +0xC field and returning the
   running sum; a null argument reports and answers -1.0f. */
float path_l01_compute_segment_lengths(unsigned char *table) {
    unsigned char *records;
    unsigned char *record;
    int index, next_index, count;
    float total;
    float segment_length;

    records = table;
    total = 0.0f;
    if (records == 0) {
        func_002A6CF0((int)g_path_segment_data);
        return -1.0f;
    }
    count = *(int *)records;
    if (count <= 0)
        return total;
    index = 0;
    do {
        next_index = index + 1;
        segment_length = func_002E3618(records + 0x10 + (index << 4), records + 0x10 + ((next_index % count) << 4));
        record = records + (index << 4);
        *(float *)(record + 0x1C) = segment_length;
        total += segment_length;
        index = next_index;
        count = *(int *)records;
    } while (index < count);
    return total;
}

typedef struct PathPoint {
    float v[4];
} PathPoint;

/* A closed path: the point count, then the points from offset 0x10. */
typedef struct Path {
    int count;
    int pad04[3];
    PathPoint points[1];
} Path;

typedef struct PathFollower {
    char pad00[0x10];
    PathPoint position;
} PathFollower;

/* Moves distance further along the closed path from the given segment, walking forward or
   back by direction; writes the point reached to out and returns the segment it lies on. */
int AdvancePointAlongPolyline(PathFollower *follower, Path *path, PathPoint *out, int segment, int direction, float distance)
{
    float toNext[4];
    float toFollower[4];
    int next;
    int last;
    float length;
    float step = distance;

    last = path->count - 1;
    if (segment == last)
        next = direction > 0 ? 0 : last - 1;
    else if (segment == 0) {
        next = last;
        if (direction > 0)
            next = 1;
    } else
        next = segment + direction;
    FastVecSub(toNext, &path->points[next], &path->points[segment]);
    length = FastVecLength(toNext);
    vec_scale_to_length(toNext, toNext, 1.0f);
    FastVecSub(toFollower, &follower->position, &path->points[segment]);
    distance = FastVecDot(toFollower, toNext);
    distance += step;
    if (length < distance) {
        last = path->count - 1;
        segment = next;
        if (segment == last)
            next = direction > 0 ? 0 : last - 1;
        else if (segment == 0) {
            next = last;
            if (direction > 0)
                next = 1;
        } else
            next = segment + direction;
        FastVecSub(toNext, &path->points[next], &path->points[segment]);
        distance -= length;
        vec_scale_to_length(toNext, toNext, 1.0f);
    }
    vec_scale_to_length(toNext, toNext, distance);
    FastVecAdd(out, toNext, &path->points[segment]);
    return segment;
}

/* Stores a value in a field of a sound slot. */
int snd_set_slot_field(int index, int value) {
    char *sound = g_sound_state + index * 0x70;
    *(unsigned short *)(sound + 0x80) = value;
    return 1;
}


/* Sets one bit in the flag table for the entry found for a key. */
void level_set_bit_in_flag_table(int key, int bit) {
    int slot = func_003711D8(key);
    if (slot >= 0)
        g_level_flag_table[slot] |= (unsigned char)(1 << bit);
}

/* func_L01_003801B8 is in L01_003801B8-g8.c for its GP accesses. */

/* func_L01_003808C0 is in L01_003808C0-g8.c for its GP accesses. */

/* func_L01_0038EF40 is in L01_0038EF40.c: its unit needs -g. */

/* A model with kind 0x12 is exempt from the trigger's visibility switches. */
#define SPATIAL_TRIGGER_EXEMPT(p) \
    ((p) && (p)->model && (p)->model->kind == 0x12)

typedef struct TriggerSettings {
    char pad00[0x7C];
    signed char f7C;
    signed char f7D;
    char pad7E;
    signed char f7F;
} TriggerSettings;

/* Applies a trigger's settings to the moby at index: each switch is positive to turn its
   effect on, negative to turn it off; inactive reverses them. */
void ApplySpatialTriggerObjectSettings(int index, TriggerSettings *settings, int active)
{
    Moby *p = (Moby *)g_moby_l01_table + index;

    if (p) {
        if (active) {
            if (settings->f7C > 0)
                p->state &= ~2;
            else if (settings->f7C < 0)
                p->state |= 2;
            if (settings->f7D > 0 && !SPATIAL_TRIGGER_EXEMPT(p)) {
                p->f31 = 1;
                p->state &= ~1;
            } else if (settings->f7D < 0 && !SPATIAL_TRIGGER_EXEMPT(p)) {
                p->f31 = 0;
                p->state |= 1;
            }
            if (settings->f7F > 0 && p->model) {
                p->f98 = p->model->f10;
            } else if (settings->f7F < 0 && p->model) {
                p->f98 = 0;
            }
        } else {
            if (settings->f7C > 0 && !SPATIAL_TRIGGER_EXEMPT(p)) {
                p->state |= 2;
            } else if (settings->f7C < 0 && !SPATIAL_TRIGGER_EXEMPT(p)) {
                p->state &= ~2;
            }
            if (settings->f7D > 0 && !SPATIAL_TRIGGER_EXEMPT(p)) {
                p->f31 = 0;
                p->state |= 1;
            } else if (settings->f7D < 0 && !SPATIAL_TRIGGER_EXEMPT(p)) {
                p->f31 = 1;
                p->state &= ~1;
            }
            if (settings->f7F > 0) {
                p->f98 = 0;
            } else if (settings->f7F < 0) {
                p->f98 = p->model->f10;
            }
        }
    }
}

#undef SPATIAL_TRIGGER_EXEMPT

/* Applies a trigger's settings to every moby in a list of moby indices. */
void moby_apply_trigger_settings_to_list(int trigger, int settings, int list_index, int active) {
    unsigned short *cursor = g_group_list_table[list_index];
    if (cursor != 0) {
        do {
            func_003907B8(*cursor & 0x7FFF, settings, active);
        } while (*(short *)cursor++ >= 0);
    }
}

extern int point_in_path_xy(float *, float *, int);
extern int IsPointInCuboid(void *, int);

void UpdateSpatialTrigger(char *object)
{
    SpatialTriggerSettings *settings;
    ClosestPointQuad point;
    int flag = 0;
    int i;
    int j;
    int k;
    int *mobys;
    int forced;
    char *path;

    settings = *(SpatialTriggerSettings **)(object + 0x68);
    *(unsigned char *)(object + 0x30) = 0xFF;
    if (settings->switches[2])
        qcopy(&point, g_level_origin_vec);
    else
        qcopy(&point, g_hero_position);
    forced = *(unsigned char *)(object + 0x95);
    if (forced == 0) {
        if (settings->radius > 0.0f && func_002E3618(object + 0x10, &point) < settings->radius)
            flag = 1;
        if (!flag) {
            if (settings->path != -1) {
                path = g_path_l01_table[settings->path];
                flag = point_in_path_xy((float *)&point, (float *)(path + 0x10), *(int *)path) != 0;
            }
        }
        if (!flag) {
            for (i = 0; ; i++) {
                if (i >= 6)
                    goto done;
                if (settings->volumes[i] == -1)
                    continue;
                if (IsPointInCuboid(&point, settings->volumes[i]))
                    break;
            }
            goto set;
        }
    } else {
        do {
            if (forced == 1) {
set:
                flag = 1;
            } else {
                flag = 0;
            }
        } while (0);
    }
done:
    if ((flag && !*(unsigned char *)(object + 0xBC)) ||
        (!flag && *(unsigned char *)(object + 0xBC)) ||
        !*(unsigned char *)(object + 0x20)) {
        if (flag)
            *(unsigned char *)(object + 0xBC) = 1;
        else
            *(unsigned char *)(object + 0xBC) = 0;
        *(unsigned char *)(object + 0x20) = *(unsigned char *)(object + 0xBC) + 1;
        mobys = settings->mobys;
        for (j = 0; j < 12; j++) {
            if (settings->lists[j] != -1)
                moby_apply_trigger_settings_to_list((int)object, (int)settings, settings->lists[j], flag);
        }
        for (k = 0; k < 11; k++) {
            if (mobys[k] != -1)
                ApplySpatialTriggerObjectSettings(mobys[k], (TriggerSettings *)settings, flag);
        }
    }
}

/* Copies the shown or hidden state of the moby this one points to onto itself. */
void moby_copy_owner_visibility(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *owner;
    unsigned char owner_state;

    if (vars == 0)
        return;
    owner = *(char **)vars;
    if (owner == 0)
        return;
    owner_state = *(unsigned char *)(owner + 0x20);
    if (owner_state == 0xFE)
        return;
    if (owner_state == 0xFD)
        return;
    if (*(unsigned short *)(owner + 0x34) & 1)
        *(unsigned short *)(moby + 0x34) |= 0x41;
    else
        *(unsigned short *)(moby + 0x34) &= 0xFFBE;
}

/* Lights up every thing in the group that has one of two kinds. */
void part_flash_matching_things(void)
{
    L01Thing *e;
    s32 i;

    if (g_hero_l01_control_mode[0] != 2)
        return;
    if (g_unlocked_item_flags[0] == 0)
        return;
    for (i = 0; i < g_ship_trail_state.count; i++) {
        e = g_ship_trail_state.items[i];
        if (e->kind != 0x398 /* moby class 920 */ && e->kind != 0x1BF /* moby class 447 */)
            continue;
        if (g_effect_match_flags[1] != 0)
            continue;
        AttachManipulator((u8 *)e, 0, g_effect_match_flags);
        g_effect_match_values[0] = 2.1f;
        g_effect_match_values[1] = 2.1f;
        g_effect_match_values[2] = 2.1f;
    }
}

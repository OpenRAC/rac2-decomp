#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char g_hero_state[];

typedef int V4_F6a70b950 __attribute__((mode(TI)));
typedef struct { float x,y,z,w; } Vec4;
typedef struct {
    unsigned char pad0[0x270]; int contact;
    unsigned char pad274[0x2290-0x274]; void *object;
    unsigned char pad2294[8]; int activity;
    unsigned char pad22a0[0x14]; unsigned char state;
} MotionView;
typedef struct {
    unsigned char pad0[0x18]; int contact; int count;
    unsigned char pad20[0x20]; Vec4 normal;
} ContactView;
#define VELOCITY ((char *)(D_00189E20 + 0xf0))
extern unsigned char D_L20_001C0400[];
#define PLAYER ((MotionView *)D_00189E20)
#define CONTACT ((ContactView *)D_L20_001C0400)
extern float cam_get_view_space_vector_length(char *);
/* EE integer and FP argument banks retain their original order. */
extern void hero_build_relative_point(float *, float, float, int, float);
extern float vec_length_xy(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void cam_set_view_space_height(V4_F6a70b950 *, V4_F6a70b950 *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, void *);
extern int GetCollHitMaterial(void);
extern float cam_get_view_space_angle(char *);
extern float FastVecDot(void *, void *);


extern u8 g_item_slot_to_record[];

extern char D_L20_0026D970[];

extern s32 hero_slot_item_id(s32 index);

extern void weapon_wheel_init(void);
extern void UpdateRadialMenuSelection(void);
extern int DrawRadialSelectorPanel(void);
extern s32 hud_set_slot_contents(s32, s32, void *, void *, void *, s32, s32);
extern void cancel_hero_item_animation(void);
extern void UpdateHeroSlotCallbacks(void);
extern void level_release_slot_list(char *);
extern void hero_set_objects_flag_bit(void);
extern void hero_clear_tracked_slots(void);
extern void attachment_reset_all(void);
extern int level_run_slot_callback(s32);
extern void hero_clear_queued_anim(void);
extern void func_002A677C(s32);
extern s32 hero_l20_set_state(s32, s32);
extern void set_hero_animation(f32, s32, s32);
extern s32 D_00138320[];
extern void UpdateYeedilHeroCollisionCapsule(void);

typedef struct {
    unsigned char pad0[440];
    int state_timer;
    unsigned char pad1bc[148];
    float capsule_top;
    float capsule_bottom;
    float top_target;
    float bottom_target;
    float radius_target;
    float radius;
    float radius_velocity;
    unsigned char pad26c[27];
    unsigned char wall_hit;
    unsigned char pad288[184];
    int field340;
    unsigned char pad344[346];
    unsigned char past_jump_apex;
    unsigned char pad49f[13];
    short takeoff_frame;
    unsigned char pad4ae[10];
    float field4b8;
    unsigned char pad4bc[4054];
    unsigned char field1492;
    unsigned char pad1493[1];
    unsigned char base_condition;
    unsigned char pad1495[3583];
    int move_state;
    unsigned char pad2298[4];
    int control_mode;
    unsigned char pad22a0[4];
    int previous_control_mode;
    unsigned char pad22a8[8];
    int field22b0;
    unsigned char vehicle_mode;
} HeroCapsuleState;
#define CAPSULE (*(HeroCapsuleState *)D_00189E20)
extern float ApproachValue(float *, float, float);
extern float vec_distance_xy(char *, char *);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);


/* func_L20_002B7A48 is defined in L20_002B7A48-selector.c. */

/*W23E*/

/* func_L20_002B93E0 is defined in L20_002B7A48-g8.c (it reaches data through $gp). */

/* Puts the hero into a new mode (on foot or riding) and attaches it to the given object. */
void SetYeedilHeroVehicleMode(s32 new_mode, s32 animation, char *attach_object)
{
    char *D = g_hero_state;
    s32 p0 = new_mode;
    char *p2 = attach_object;
    s32 p1 = animation;
    char *block;

    cancel_hero_item_animation();
    *(u8 *)(D + 0x22B6) = 1;
    UpdateHeroSlotCallbacks();
    *(s32 *)(D + 0x2290) = *(s32 *)(D + 0xC18);
    level_release_slot_list(D + 0x18E0);
    level_release_slot_list(D + 0x1A30);
    *(s32 *)(*(s32 *)(D + 0x2290) + 0x9C) = -1;
    if (p0 != 4 || *(u8 *)(D + 0x22B4) != p0)
        hero_set_objects_flag_bit();
    hero_clear_tracked_slots();
    attachment_reset_all();
    block = g_hero_state;
    *(u8 *)(block + 0x22B4) = p0;
    *(s32 *)(block + 0xC14) = (s32)p2;
    *(s32 *)(block + 0x2290) = (s32)p2;
    if ((p0 & 0xFF) == 1) {
        if (D_00138320[0] & 0x10) {
            hud_set_slot_contents(0x23, 0, (void *)weapon_wheel_init, (void *)UpdateRadialMenuSelection,
                          (void *)DrawRadialSelectorPanel, 0, 0);
            level_run_slot_callback(3);
        }
    }
    UpdateYeedilHeroCollisionCapsule();
    D = g_hero_state;
    *(f32 *)(D + 0x250) = *(f32 *)(D + 0x258);
    *(f32 *)(D + 0x254) = *(f32 *)(D + 0x25C);
    *(u16 *)(*(s32 *)(D + 0x2290) + 0x34) |= 6;
    *(f32 *)(D + 0xC20) = 1.0f;
    *(f32 *)(D + 0xC24) = 1.0f;
    hero_clear_queued_anim();
    func_002A677C(*(s32 *)(D + 0x2290));
    *(u16 *)(D + 0x24F2) = p1;
    switch (p0) {
    case 1:
        *(u16 *)(D + 0x24D4) = *(u16 *)(D + 0x24CC);
        *(s32 *)(D + 0x24CC) = *(s32 *)(D + 0x24D0);
        if (*(s32 *)(D + 0x24CC) >= 5)
            *(s32 *)(D + 0x24CC) = 4;
        break;
    case 4:
        qcopy(D + 0x80, p2 + 0x10);
        qcopy(D + 0x90, p2 + 0xF0);
        *(u16 *)(D + 0x24D4) = *(u16 *)(D + 0x24CC);
        *(s32 *)(D + 0x24CC) = 3;
    }
    hero_l20_set_state(p1, 2);
    if (p0 == 4)
        set_hero_animation(5.0f, 0xF, 0);
}


/* func_L20_002C5A48 is defined in L20_002C5A48-qcopy.c (its copies need the grouped-copy profile). */

/* func_L20_002C5D00 is defined in L20_002B7A48-g8.c (it reaches data through $gp). */

/* Grows or shrinks the hero collision capsule toward the size its current pose needs. */
void UpdateYeedilHeroCollisionCapsule(void)
{
    HeroCapsuleState *initial = (HeroCapsuleState *)g_hero_state;
    switch (initial->vehicle_mode) {
    case 1:
        initial->top_target = 0.5999999642372131f;
        initial->bottom_target = 0.45000001788139343f;
        initial->radius_target = 0.3f;
        break;
    case 0:
    case 4:
        initial->top_target = 0.8f;
        initial->bottom_target = 0.7f;
        initial->radius_target = 0.44999998807907104f;
        break;
    }
    if (CAPSULE.control_mode == 4) {
        if (CAPSULE.takeoff_frame < CAPSULE.state_timer && !CAPSULE.past_jump_apex)
            CAPSULE.bottom_target = CAPSULE.field4b8;
    } else if (CAPSULE.move_state == 6) {
        CAPSULE.bottom_target = 0.5f;
    } else if (CAPSULE.move_state == 4) {
        CAPSULE.top_target = 0.3500000238418579f;
    } else if ((unsigned)(CAPSULE.control_mode - 17) < 2) {
        CAPSULE.top_target = 0.0f;
        CAPSULE.bottom_target = 0.0f;
    } else if (CAPSULE.field1492 && CAPSULE.field340) {
        CAPSULE.top_target = 0.8f;
        CAPSULE.bottom_target = 0.9f;
    } else if (CAPSULE.move_state == 124) {
        CAPSULE.radius_target = 0.8f;
    }
    if (!CAPSULE.wall_hit || CAPSULE.previous_control_mode == 18 ||
        CAPSULE.field22b0 == 18 ||
        (CAPSULE.vehicle_mode == 0 && CAPSULE.capsule_bottom < 0.53f) ||
        CAPSULE.control_mode == 17 || CAPSULE.base_condition ||
        vec_distance_xy((char *)&CAPSULE + 0x240, (char *)&CAPSULE + 0x80) >
            CAPSULE.radius * 0.5f) {
        ApproachValue(&CAPSULE.capsule_top, CAPSULE.top_target, 0.02f);
        ApproachValue(&CAPSULE.capsule_bottom, CAPSULE.bottom_target, 0.02f);
        math_spring_float_to_goal(&CAPSULE.radius, &CAPSULE.radius_velocity,
                     CAPSULE.radius_target, 0.02f, 0.3f, 0.0666666701f);
    }
}

/* Checks for a wall in front of the hero and slides the hero along it instead of into it. */
void hero_slide_along_wall(int force)
{
    Vec4 offset, start, lowerOffset, lowerStart;
    float height, radius, angle;
    float lowerHeight;
    int kind;
    if (cam_get_view_space_vector_length(VELOCITY) < 0.0016666668f) return;
    height = 0.37f;
    radius = 0.5f;
    if ((unsigned int)(PLAYER->activity - 0x11) < 2) {
        height = 0.0f;
        radius = 0.7f;
    } else if (PLAYER->state == 1) {
        height = 0.35f;
        radius = 0.27f;
    } else if (PLAYER->state == 4) height = 0.35f;
    hero_build_relative_point(&offset.x, 0.0f, 0.0f, 1, height);
    lowerHeight = height * 0.3f;
    hero_build_relative_point(&lowerOffset.x, 0.0f, 0.0f, 1, lowerHeight);
    if (force || vec_length_xy(VELOCITY) < 0.01f) {
        vec_scale_to_length(&start, g_hero_state, radius);
        vec_scale_to_length(&lowerStart, g_hero_state, radius * 1.4f);
    } else {
        cam_set_view_space_height((V4_F6a70b950 *)&start, (V4_F6a70b950 *)VELOCITY, 0.0f);
        vec_scale_to_length(&start, &start, radius);
        FastVecScale(&lowerStart, &start, 1.4f);
    }
    kind = -1;
    FastVecAdd(&start, &start, &offset);
    FastVecAdd(&lowerStart, &lowerStart, &lowerOffset);
    if (CollLine(&lowerOffset, &lowerStart, 2, PLAYER->object, 0) && CONTACT->count > 0)
        kind = GetCollHitMaterial();
    angle = 0.0f;
    if (CollLine(&offset, &start, 2, PLAYER->object, 0) && CONTACT->count > 0)
        angle = cam_get_view_space_angle((char *)&CONTACT->normal);
    if (angle >= 0.8726647f || kind == 8 || kind == 12) {
        float dot;
        PLAYER->contact = CONTACT->contact;
        cam_set_view_space_height((V4_F6a70b950 *)&CONTACT->normal, (V4_F6a70b950 *)&CONTACT->normal, 0.0f);
        vec_scale_to_length(&CONTACT->normal, &CONTACT->normal, 1.0f);
        dot = FastVecDot(&CONTACT->normal, VELOCITY);
        if (dot < 0.0f) {
            FastVecScale(&CONTACT->normal, &CONTACT->normal, -dot);
            FastVecAdd(VELOCITY, VELOCITY, &CONTACT->normal);
        }
    }
}

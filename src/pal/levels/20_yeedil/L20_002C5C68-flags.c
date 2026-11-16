#include "include_asm.h"

#include "common.h"
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
extern unsigned char g_collision_contact[];
#define PLAYER ((MotionView *)D_00189E20)
#define CONTACT ((ContactView *)D_L20_001C0400)
extern float cam_get_view_space_vector_length(char *);
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

/* Checks for a wall in front of the hero and slides the hero along it instead of into it. (PAL version) */
void hero_slide_along_wall_pal(int force)
{
    Vec4 offset, start, lower_offset, lower_start;
    float height, radius, angle;
    float lower_height;
    int kind;
    if (cam_get_view_space_vector_length(VELOCITY) < 0.002f) return;
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
    lower_height = height * 0.3f;
    hero_build_relative_point(&lower_offset.x, 0.0f, 0.0f, 1, lower_height);
    if (force || vec_length_xy(VELOCITY) < 0.01f) {
        vec_scale_to_length(&start, g_hero_state, radius);
        vec_scale_to_length(&lower_start, g_hero_state, radius * 1.4f);
    } else {
        cam_set_view_space_height((V4_F6a70b950 *)&start, (V4_F6a70b950 *)VELOCITY, 0.0f);
        vec_scale_to_length(&start, &start, radius);
        FastVecScale(&lower_start, &start, 1.4f);
    }
    kind = -1;
    FastVecAdd(&start, &start, &offset);
    FastVecAdd(&lower_start, &lower_start, &lower_offset);
    if (CollLine(&lower_offset, &lower_start, 2, PLAYER->object, 0) && CONTACT->count > 0)
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

#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct {
    u8 pad0[0xF0];
    float velocity[4];               
    u8 pad100[0x140 - 0x100];
    float lastVelocity[4];           
    u8 pad150[0x174 - 0x150];
    float f174;
    float f178;
    u8 pad17C[0x190 - 0x17C];
    float targetDir[4];              
    float inputAngle;                
    u8 pad1A4[0x1B0 - 0x1A4];
    float inputSpeed;                
    float f1B4;
    u8 pad1B8[0x287 - 0x1B8];
    u8 f287;
    u8 pad288[0x34A - 0x288];
    s16 f34A;
    u8 pad34C[0x524 - 0x34C];
    s16 f524;
    u8 pad526[0xA60 - 0x526];
    float vecA60[4];
    u8 padA70[0x1454 - 0xA70];
    s16 f1454;
    u8 pad1456[0x2294 - 0x1456];
    s32 f2294;
    u8 pad2298[4];
    s32 f229C;
    u8 pad22A0[0x22C3 - 0x22A0];
    u8 moveMode;                     
} HeroVelocity;
extern HeroVelocity g_hero_state;
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float vec_length_xy(void *);
extern float cam_get_view_space_vector_length(void *);
extern float FastVecDot(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void cam_set_view_space_height(void *, void *, float);
extern void cam_set_view_space_vector_length(void *, void *, float);
extern float hero_get_speed_along_forward(void *);

/* Moves the hero's velocity toward the requested one, accelerating harder when reversing. */
void ApproachHeroVelocity_pal(float rate)
{
    float v[4] __attribute__((aligned(16)));
    float t[4] __attribute__((aligned(16)));
    float u[4] __attribute__((aligned(16)));
    float angle, speed, dot, len, velLen;

    switch (g_hero_state.moveMode) {
    case 0:
        angle = g_hero_state.inputAngle;
        speed = g_hero_state.inputSpeed;
        if (g_hero_state.f229C == 4 && g_hero_state.f524 && g_hero_state.f287)
            speed = 0.10000001f;
        if (g_hero_state.f34A && g_hero_state.f2294 == 14 && speed > 0.020000001f)
            speed = 0.020000001f;
        v[0] = math_fast_sin_or_cos_a(angle) * speed;
        v[1] = math_fast_sin_or_cos_b(angle) * speed;
        v[2] = g_hero_state.velocity[2];
        dot = -(g_hero_state.velocity[0] * v[0] + g_hero_state.velocity[1] * v[1]);
        len = vec_length_xy(v);
        velLen = vec_length_xy(g_hero_state.velocity);
        if (len == 0.0f || velLen == 0.0f) {
            dot = 0.0f;
        } else {
            dot /= len;
            dot /= velLen;
        }
        dot += 1.0f;
        dot *= 1.5f;
        if (dot > 3.0f)
            dot = 3.0f;
        if (dot < 1.0f)
            dot = 1.0f;
        rate *= dot;
        FastVecSub(v, v, g_hero_state.velocity);
        if (vec_length_xy(v) > rate)
            vec_fast_normalize_helper(v, v, rate);
        FastVecAdd(g_hero_state.velocity, g_hero_state.velocity, v);
        qcopy(g_hero_state.lastVelocity, g_hero_state.velocity);
        *(Quad *)t = *(Quad *)g_hero_state.vecA60;
        g_hero_state.f1B4 = g_hero_state.f178 - hero_get_speed_along_forward(t);
        if (g_hero_state.f1454)
            g_hero_state.f1B4 = g_hero_state.f174;
        break;
    case 1:
    case 2:
        *(Quad *)t = *(Quad *)g_hero_state.targetDir;
        speed = g_hero_state.inputSpeed;
        cam_set_view_space_height(v, t, 0.0f);
        vec_scale_to_length(v, v, speed);
        cam_set_view_space_height(u, g_hero_state.velocity, 0.0f);
        dot = -FastVecDot(u, v);
        len = cam_get_view_space_vector_length(v);
        velLen = cam_get_view_space_vector_length(g_hero_state.velocity);
        if (len == 0.0f || velLen == 0.0f) {
            dot = 0.0f;
        } else {
            dot /= len;
            dot /= velLen;
        }
        dot += 1.0f;
        dot *= 1.5f;
        if (dot > 3.0f)
            dot = 3.0f;
        if (dot < 1.0f)
            dot = 1.0f;
        rate *= dot;
        FastVecSub(v, v, g_hero_state.velocity);
        cam_set_view_space_height(v, v, 0.0f);
        if (cam_get_view_space_vector_length(v) > rate)
            cam_set_view_space_vector_length(v, v, rate);
        FastVecAdd(g_hero_state.velocity, g_hero_state.velocity, v);
        g_hero_state.f1B4 = g_hero_state.f178;
        if (g_hero_state.f1454)
            g_hero_state.f1B4 = g_hero_state.f174;
        break;
    }
}

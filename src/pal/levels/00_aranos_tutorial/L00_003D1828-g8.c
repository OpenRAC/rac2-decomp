#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x80]; Vec position; } LiftHero;
extern LiftHero g_hero_state;
typedef struct { char head[0x10]; Vec position; char tail[0xD0]; Vec rotation; } LiftMoby;
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; char *owner; } LiftSound;
extern unsigned char g_sound_state[];
typedef struct { char pad[0x140]; Vec from, to; char gap[0x30]; char *camera; } LiftCamera;
extern LiftCamera D_L00_001B8C80;
extern const int D_001A7908;
extern float FastAddRotations(float, float), math_fast_sin_or_cos_b(float), math_fabs(float), math_random_angle(void);
extern float vec_distance_xy(void *, void *), fast_vec_dist(void *, void *);
extern int FloatToInt(float), hero_is_current_selected_id(int), snd_is_voice_playing_for_owner(void *, int), PlayMobySound(int, int, void *);
extern int IsPointInCuboid(void *, int);
extern void moby_set_state(void *, int, int), snd_stop_voice(int), moby_mark_spawned(void *), func_002A0F48(void *);
extern char *CreateMoby(int), *func_PAL_L00_002D7850(int);
extern void cam_end_override(void *), SetCamera5Pose(void *, void *, int, int, int), cam_set_state_rotation(void *);
extern void object_copy_vector_to_selected(void *), cam_set_mode_state(int);
extern void FastVecSub(void *, void *, void *), mat_combine_and_store(void *, void *, void *, void *);
extern float math_spring_float_to_goal(void *, void *, float, float, float, float);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern int snd_play_from_class_bank(int, int, void *, int);
typedef struct {
    char head[0x20], transform[0x3C];
    int flags;
    Vec home;
    char gap[0x10];
    int direction, counter, sound;
    float endpoint;
    int initialDirection;
    float target, otherTarget;
    char *camera, *child;
    int release;
    float phase, velocity;
    int trigger;
} LiftContext;
#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define P(p, o) (*(char **)((p) + (o)))
#define STOP_SOUND() {                                                                  \
        handle = ctx->sound;                                                            \
        if (handle != -1) {                                                             \
            LiftSound *sound = (LiftSound *)(handle * 0x70 + (int)D_00188660);          \
            if (sound->owner == obj && sound->active)                                   \
                func_002E59F8(handle);                                                  \
        }                                                                               \
        ctx->sound = -1;                                                                \
    }
#define RELEASE()                                                                       \
    if (ctx->release) {                                                                 \
        func_L00_002D7140(ctx->camera);                                                 \
        ctx->release = 0;                                                               \
    }
#define START_SOUND(s)                                                                  \
    if (!func_002E59B0(obj, ctx->sound))                                                \
        ctx->sound = func_002E5CF8(s, 4, obj)
#define RESET_CHILD()                                                                   \
    func_002A7750(obj, 1, -1);                                                          \
    I(ctx->child, 0x78) = 0x808C8C8C;                                                   \
    I(ctx->child, 0x98) = I(P(ctx->child, 0x24), 0x10)

void func_PAL_L00_003D1828(LiftMoby *moby) {
    char *obj = (char *)moby;
    struct { Vec old, rotation, delta, camera; } frame;
    LiftContext *ctx = *(LiftContext **)(obj + 0x68);

    int value, handle;
    unsigned int brightness;
    qcopy(&frame.old, &moby->position);
    qcopy(&frame.rotation, &moby->rotation);
    switch ((unsigned char)obj[0x20]) {
    case 0: {
        char *created;
        *(unsigned short *)(obj + 0x34) |= 0x800;
        ctx->flags |= 1;
        qcopy(&ctx->home, &moby->position);
        ctx->velocity = 0.0f;
        obj[0x20] = 1;
        if (!ctx->initialDirection) {
            ctx->target = ctx->home.f[2];
            ctx->otherTarget = ctx->endpoint;
            ctx->direction = 0;
        } else {
            ctx->direction = 1;
            ctx->target = ctx->endpoint;
            ctx->otherTarget = ctx->home.f[2];
        }
        ctx->counter = 0;
        ctx->sound = -1;
        created = CreateMoby(0xC16);
        ctx->child = created;
        if (!created) {
            moby_mark_spawned(obj);
            return;
        }
        created[0x30] = obj[0x30];
        *(short *)(ctx->child + 0x32) = *(short *)(obj + 0x32);
        ctx->child[0x31] = 1;
        {
            char *child = ctx->child;
            qcopy(&((LiftMoby *)child)->position, &moby->position);
            F(child, 0x18) += 0.25f;
        }
        func_002A0F48(ctx->child);
        ctx->phase = math_random_angle();
        break;
    }
    case 1:
        ctx->phase = FastAddRotations(ctx->phase, 0.12566373f);
        value = FloatToInt((math_fast_sin_or_cos_b(ctx->phase) * 4.0f - 3.0f) * 208.0f);
        if (value > 208)
            value = 208;
        else if (value < 80)
            value = 80;
        brightness = value;
        {
            unsigned int low = brightness << 8 | 0x80000000;
            unsigned int color = brightness << 16 | low;
            I(ctx->child, 0x78) = color | brightness;
        }
        if (hero_is_current_selected_id((int)ctx->child) && ctx->direction) {
            moby_set_state(obj, 2, -1);
            ctx->velocity = 0.0f;
            I(ctx->child, 0x78) = 0x8000DF2A;
            if (!D_001A7908) {
                SetCamera5Pose(&D_L00_001B8C80.from, &D_L00_001B8C80.to, 2, 100, 0);
                frame.camera.f[0] = 246.85f;
                frame.camera.f[1] = 198.19f;
                frame.camera.f[2] = g_hero_state.position.f[2] + 1.5f;
                frame.delta.f[2] = 1.5707965f;
                frame.delta.f[0] = 0;
                frame.delta.f[1] = 0;
                cam_set_state_rotation(&frame.delta);
                object_copy_vector_to_selected(&frame.camera);
            }
            snd_play_from_class_bank(0, 0, obj, 0x8A1);
            I(ctx->child, 0x98) = 0;
            START_SOUND(0);
            ctx->camera = func_PAL_L00_002D7850(5);
            F(ctx->camera, 0) = 2.0f;
            F(ctx->camera, 4) = 1.5f;
            ctx->release = 1;
        }
        if (math_fabs(F(obj, 0x18) - g_hero_state.position.f[2]) > 12.0f && !ctx->direction) {
            START_SOUND(0);
            moby_set_state(obj, 3, -1);
            I(ctx->child, 0x78) = 0x8000DF2A;
            I(ctx->child, 0x98) = 0;
        } else if (math_fabs(F(obj, 0x18) - g_hero_state.position.f[2]) > 12.0f && ctx->direction == 1) {
            START_SOUND(1);
            moby_set_state(obj, 2, -1);
            ctx->velocity = 0.0f;
            I(ctx->child, 0x78) = 0x8000DF2A;
            I(ctx->child, 0x98) = 0;
        }
        break;
    case 2:
        qcopy(&frame.delta, &moby->position);
        frame.delta.f[2] = ctx->target;
        if (fast_vec_dist(&moby->position, &frame.delta) > 0.14f) {
            math_step_value_toward_target(obj + 0x18, &ctx->velocity, frame.delta.f[2], 0.0028000001f, 0.0024f,
                          0.120000005f);
            ++ctx->counter;
        } else if (vec_distance_xy(&moby->position, &g_hero_state.position) > 1.2f) {
            RELEASE();
            ctx->direction = 0;
            STOP_SOUND();
            RESET_CHILD();
        } else {
            if (ctx->counter > 0) {
                PlayMobySound(1, 0, obj);
                ctx->counter = 0;
            }
            RELEASE();
            STOP_SOUND();
        }
        if (math_fabs(F(obj, 0x18) - g_hero_state.position.f[2]) > 3.0f
            && g_hero_state.position.f[2] < F(obj, 0x18))
            moby_set_state(obj, 3, -1);
        break;
    case 3:
        if (F(obj, 0x18) > ctx->otherTarget) {
            if (IsPointInCuboid(&g_hero_state.position, ctx->trigger)) {
                if (F(obj, 0x18) - g_hero_state.position.f[2] < 1.8f && g_hero_state.position.f[2] < F(obj, 0x18))
                    break;
                math_spring_float_to_goal(obj + 0x18, &ctx->velocity, ctx->otherTarget, 0.02f, 0.3f, 0.120000005f);
                ++ctx->counter;
            } else {
                F(obj, 0x18) -= 0.08f;
                ++ctx->counter;
            }
        } else if (vec_distance_xy(&moby->position, &g_hero_state.position) > 1.0f) {
            PlayMobySound(1, 0, obj);
            RELEASE();
            ctx->direction = 1;
            STOP_SOUND();
            RESET_CHILD();
            ctx->counter = 0;
        } else {
            RELEASE();
            STOP_SOUND();
        }
        break;
    }
    FastVecSub(&frame.delta, &moby->position, &frame.old);
    mat_combine_and_store(ctx->transform, &frame.delta, &frame.rotation, obj + 0xF0);
    {
        char *child = ctx->child;
        qcopy(child + 0x10, &moby->position);
        F(child, 0x18) += 0.25f;
    }
    if (*(short *)(D_L00_001B8C80.camera + 0x86) == 5) {
        frame.camera.f[0] = 246.85f;
        frame.camera.f[1] = 198.19f;
        frame.camera.f[2] = g_hero_state.position.f[2] + 1.5f;
        object_copy_vector_to_selected(&frame.camera);
        if (vec_distance_xy(D_L00_001B8C80.camera + 0x30, &frame.camera) < 0.5f)
            cam_set_mode_state(1);
    }
}

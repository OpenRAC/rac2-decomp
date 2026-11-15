#include "common.h"

/* This unit is built with -frac2-gcse-unsplit-edges (config/cflags.txt): retail recomputes the
 * position address at the end of a block, before that block's call, rather than on a split edge. */

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union {
    Quad q;
    float f[4];
} Vec;

typedef struct {
    char pad00[0x10];
    int f10;
} LiftModel;

typedef struct LiftMoby {
    char pad00[0x10];
    Vec position;
    unsigned char state;
    char pad21[3];
    LiftModel *model;
    char pad28[8];
    char f30;
    char f31;
    short f32;
    char pad34[4];
    long long f38;
    char pad40[0x28];
    struct LiftContext *ctx;
    char pad6C[0xC];
    unsigned int colour;
    char pad7C[0x1C];
    int f98;
    char pad9C[0x54];
    Vec rotation;
} LiftMoby;

/* The per-object context: state 3 descends to bottomHeight, state 2 climbs back to topHeight. */
typedef struct LiftContext {
    char pad00[0x20];
    char mover[0x3C];
    int flags;
    Vec home;
    char pad70[0x10];
    int atBottom;
    int travelFrames;
    int soundHandle;
    float otherHeight;
    int startsAtBottom;
    float topHeight;
    float bottomHeight;
    LiftMoby *child;
    float blinkPhase;
    int fA4;
    char smoothing[8];
} LiftContext;

typedef struct {
    char pad00[0x80];
    Vec position;
} Player;

/* An entry of the sound table; entries are 0x70 bytes apart from D_00188660. */
typedef struct {
    char pad00[0x74];
    unsigned char playing;
    char pad75[0x13];
    LiftMoby *owner;
} SoundSlot;

extern Player g_hero_state;
extern unsigned char g_sound_state[];
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fabs(float);
extern float math_random_angle(void);
extern float vec_distance_xy(void *, void *);
extern float fast_vec_dist(void *, void *);
extern int FloatToInt(float);
extern int hero_is_current_selected_id(LiftMoby *);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int PlayMobySound(int, int, void *);
extern int IsPointInCuboid(void *, int);
extern void moby_set_state(void *, int, int);
extern void snd_stop_voice(int);
extern void moby_mark_spawned(void *);
extern void func_002A0F48(void *);
extern LiftMoby *CreateMoby(int);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern float math_spring_float_to_goal(float *, void *, float, float, float, float);
extern int snd_play_from_class_bank(int, int, void *, int);

#define PLAYER_POSITION D_00189E20.position

#define STOP_SOUND()                                                                  \
    {                                                                                 \
        SoundSlot *slot;                                                              \
        handle = ctx->soundHandle;                                                    \
        if (handle != -1 && (slot = (SoundSlot *)(handle * 0x70 + D_00188660))->owner == obj \
            && slot->playing)                                                         \
            func_002E59F8(handle);                                                    \
        ctx->soundHandle = -1;                                                        \
    }

#define START_SOUND()                                 \
    if (!func_002E59B0(obj, ctx->soundHandle))        \
        ctx->soundHandle = func_002E5CF8(0, 4, obj)

#define START_MOVING(state)                           \
    func_002A7750(obj, state, -1);                    \
    ctx->child->colour = 0x8000DF2A;                  \
    func_002E5DA0(0, 0, obj, 0x8A1);                  \
    ctx->child->f98 = 0

/* Moves the lift between its top and bottom heights when the player steps on its button, with a blinking light and a looping sound. */
void UpdateAranosButtonLift(LiftMoby *obj) {
    struct {
        Vec old, rotation, delta, offset;
    } frame;
    LiftContext *ctx = obj->ctx;
    LiftMoby *child, *made;
    unsigned int colour;
    int value, handle;

    qcopy(&frame.old, &obj->position);
    qcopy(&frame.rotation, &obj->rotation);
    switch (obj->state) {
    case 0:
        ctx->flags |= 1;
        qcopy(&ctx->home, &obj->position);
        obj->state = 1;
        if (!ctx->startsAtBottom) {
            ctx->topHeight = ctx->home.f[2];
            ctx->bottomHeight = ctx->otherHeight;
            ctx->atBottom = 0;
        } else {
            ctx->atBottom = 1;
            ctx->topHeight = ctx->otherHeight;
            ctx->bottomHeight = ctx->home.f[2];
        }
        ctx->travelFrames = 0;
        ctx->soundHandle = -1;
        made = CreateMoby(0xC16 /* moby class 3094 */);
        ctx->child = made;
        if (!made) {
            moby_mark_spawned(obj);
            return;
        }
        made->f30 = obj->f30;
        ctx->child->f32 = obj->f32;
        ctx->child->f31 = 1;
        ctx->child->f38 = obj->f38;
        child = ctx->child;
        qcopy(&child->position, &obj->position);
        child->position.f[2] += 0.25f;
        frame.delta.f[0] = math_fast_sin_or_cos_a(obj->rotation.f[2]);
        frame.delta.f[1] = math_fast_sin_or_cos_b(obj->rotation.f[2]);
        frame.delta.f[2] = 0;
        FastVecAdd(&ctx->child->position, &ctx->child->position, &frame.delta);
        func_002A0F48(ctx->child);
        ctx->blinkPhase = math_random_angle();
        break;
    case 1:
        ctx->blinkPhase = FastAddRotations(ctx->blinkPhase, 0.10471977f);
        value = FloatToInt((math_fast_sin_or_cos_b(ctx->blinkPhase) * 4.0f - 3.0f) * 208.0f);
        if (value > 208)
            value = 208;
        else if (value < 80)
            value = 80;
        colour = 0x80000000 | value << 16 | value << 8;
        ctx->child->colour = colour | value;
        if (hero_is_current_selected_id(ctx->child)) {
            if (!ctx->atBottom) {
                START_MOVING(3);
                START_SOUND();
            } else {
                moby_set_state(obj, 2, -1);
                ctx->child->f98 = 0;
                ctx->child->colour = 0x8000DF2A;
                snd_play_from_class_bank(0, 0, obj, 0x8A1);
                START_SOUND();
            }
        }
        if (math_fabs(obj->position.f[2] - PLAYER_POSITION.f[2]) > 6.0f && !ctx->atBottom
            && vec_distance_xy(&obj->position, &PLAYER_POSITION) < 25.0f) {
            START_SOUND();
            START_MOVING(3);
        } else if (math_fabs(obj->position.f[2] - PLAYER_POSITION.f[2]) > 6.0f && ctx->atBottom == 1) {
            START_SOUND();
            START_MOVING(2);
        }
        break;
    case 2:
        qcopy(&frame.delta, &obj->position);
        frame.delta.f[2] = ctx->topHeight;
        if (fast_vec_dist(&obj->position, &frame.delta) > 0.25f) {
            math_spring_float_to_goal(&obj->position.f[2], ctx->smoothing, frame.delta.f[2], 0.02f, 0.3f, 0.10000001f);
            ++ctx->travelFrames;
            break;
        }
        if (!hero_is_current_selected_id(ctx->child)
            && (vec_distance_xy(&obj->position, &PLAYER_POSITION) > 2.0f || obj->position.f[2] > PLAYER_POSITION.f[2])) {
            ctx->atBottom = 0;
            STOP_SOUND();
            moby_set_state(obj, 1, -1);
            ctx->child->colour = 0x808C8C8C;
            ctx->child->f98 = ctx->child->model->f10;
        } else {
            if (ctx->travelFrames > 0) {
                PlayMobySound(1, 0, obj);
                ctx->travelFrames = 0;
            }
            STOP_SOUND();
        }
        break;
    case 3:
        if (obj->position.f[2] > ctx->bottomHeight) {
            if (obj->position.f[2] - PLAYER_POSITION.f[2] < 1.8f && PLAYER_POSITION.f[2] < obj->position.f[2]) {
                if (IsPointInCuboid(&PLAYER_POSITION, ctx->fA4))
                    break;
                math_spring_float_to_goal(&obj->position.f[2], ctx->smoothing, ctx->bottomHeight, 0.02f, 0.3f, 0.10000001f);
                ++ctx->travelFrames;
            } else {
                math_spring_float_to_goal(&obj->position.f[2], ctx->smoothing, ctx->bottomHeight, 0.0016666667f, 0.0033333334f,
                              0.10000001f);
                ++ctx->travelFrames;
            }
            break;
        }
        if (!hero_is_current_selected_id(ctx->child)
            && (vec_distance_xy(&obj->position, &PLAYER_POSITION) > 2.0f || obj->position.f[2] > PLAYER_POSITION.f[2])) {
            ctx->atBottom = 1;
            STOP_SOUND();
            moby_set_state(obj, 1, -1);
            ctx->child->colour = 0x808C8C8C;
            ctx->child->f98 = ctx->child->model->f10;
            ctx->travelFrames = 0;
        } else {
            if (ctx->travelFrames > 0) {
                PlayMobySound(1, 0, obj);
                ctx->travelFrames = 0;
            }
            STOP_SOUND();
        }
        break;
    }
    FastVecSub(&frame.delta, &obj->position, &frame.old);
    mat_combine_and_store(ctx->mover, &frame.delta, &frame.rotation, &obj->rotation);
    qcopy(&ctx->child->position, &obj->position);
    frame.offset.f[0] = math_fast_sin_or_cos_a(obj->rotation.f[2]);
    frame.offset.f[1] = math_fast_sin_or_cos_b(obj->rotation.f[2]);
    frame.offset.f[2] = 0;
    FastVecAdd(&ctx->child->position, &ctx->child->position, &frame.offset);
    ctx->child->position.f[2] += 0.25f;
}

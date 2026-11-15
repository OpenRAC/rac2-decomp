#include "common.h"

typedef unsigned int TI128 __attribute__((mode(TI)));

/* A quadword vector: .q moves or clears all four floats at once. */
typedef union {
    TI128 q;
    float v[4];
} Vector;

/* The moby fields this unit reads. */
typedef struct {
    u8 pad00[0x10];
    float position[4];          /* 0x10 */
    u8 pad20[0x34 - 0x20];
    u16 modeBits;               /* 0x34: bit 0 skips the actor */
    u8 pad36[0x68 - 0x36];
    void *vars;                 /* 0x68 */
    u8 pad6C[0xC0 - 0x6C];
    float matrix[3][4];         /* 0xC0: orientation, row 0 is the forward axis */
    float rotation[4];          /* 0xF0 */
} Moby;

/* The instance data of the pair moby: one actor per controller. */
typedef struct {
    Moby *actors[2];
    float steering[2];
    Vector positions[2];
    Vector velocities[2];
    int timers[2];
    int scores[2];
    int phase;
} PairContext;

/* Prefix of a controller state (RAC1 include/pad.h PadState); the full size is not measured. */
typedef struct {
    u8 pad000[0x100];
    float analog[16];           /* 0x100: [2] is the left stick's x axis */
    u8 pad140[0x1A0 - 0x140];
    u32 held;                   /* 0x1A0 */
    u32 pressed;                /* 0x1A4 */
} PadState;

#define PAD_CROSS  0x0040
#define PAD_CIRCLE 0x0020
#define PAD_SQUARE 0x0080
#define PAD_RIGHT  0x2000
#define PAD_LEFT   0x8000

extern PadState g_pad_state;     /* controller 1 */
extern PadState D_00138500;     /* controller 2 */

extern float D_L00_001B8FF0[12];                    /* frame of the y-z plane the actors move in */
extern float D_L00_001AFAA8 __attribute__((sda));   /* turn rate, degrees per second */
extern float D_L00_001AFAAC __attribute__((sda));   /* turn acceleration, degrees per second^2 */
extern float D_L00_001AFAB0 __attribute__((sda));   /* thrust, per second^2 */
extern float D_L00_001AFAB4 __attribute__((sda));   /* top speed, per second */
extern float D_L00_001AFAB8 __attribute__((sda));   /* shot speed, per second */
extern Vector D_L00_001AFAC0 __attribute__((sda));  /* muzzle offset in the actor's frame */
extern float D_L00_001AFA40 __attribute__((sda));   /* central pull, per second^2 */
extern int D_L00_001AFA48 __attribute__((sda));     /* frames between shots */

extern void matrix_from_basis_rows(void *out, void *matrix);
extern void matrix_mul_vec3(void *out, void *vector, void *matrix);
extern void vec_scale_to_length(void *out, void *in, float length);
extern void FastVecAdd(void *out, void *a, void *b);
extern float ApproachValue(float *value, float target, float step);
extern float FastAddRotations(float angle, float delta);
extern int math_fast_float_d(int *timer);   /* counts down; nonzero once it has run out */
extern void part_spawn_two_colored_sparkles(Moby *actor, void *position);
extern void *pair_game_spawn_shot(Moby *owner, void *position, void *velocity, void *player);
extern void pair_game_apply_centre_pull(float y, float z, float strength, float *vy, float *vz);
extern void vec_clamp_length(float *vector, float limit);

/* Steers both actors from their controllers, applies thrust and firing, and moves them. */
void UpdatePairedActorMovement(Moby *object)
{
    float axes[2];
    u32 held[2];
    u32 pressed[2];
    float inverse[16] __attribute__((aligned(16)));
    Vector impulse;
    Vector local;
    Vector muzzle;
    PairContext *context = object->vars;
    Moby *actor;
    int i;

    axes[0] = -g_pad_state.analog[2];
    if (g_pad_state.held & PAD_LEFT)
        axes[0] = 1.0f;
    else if (g_pad_state.held & PAD_RIGHT)
        axes[0] = -1.0f;
    axes[1] = -D_00138500.analog[2];
    if (D_00138500.held & PAD_LEFT)
        axes[1] = 1.0f;
    else if (D_00138500.held & PAD_RIGHT)
        axes[1] = -1.0f;
    held[0] = g_pad_state.held;
    held[1] = D_00138500.held;
    pressed[0] = g_pad_state.pressed;
    pressed[1] = D_00138500.pressed;

    matrix_from_basis_rows(inverse, D_L00_001B8FF0);
    for (i = 0; i < 2; ++i) {
        actor = context->actors[i];
        if (actor->modeBits & 1)
            continue;

        /* Turn by the stick (degrees per second to radians per frame). */
        ApproachValue(&context->steering[i], D_L00_001AFAA8 * (axes[i] * 0.00029088825f),
                      D_L00_001AFAAC * 0.0000048481375f);
        actor->rotation[2] = FastAddRotations(actor->rotation[2], context->steering[i]);

        /* Thrust along the actor's forward axis while cross is held. */
        if (held[i] & PAD_CROSS) {
            matrix_mul_vec3(&impulse, actor->matrix[0], inverse);
            vec_scale_to_length(&impulse, &impulse, D_L00_001AFAB0 * 0.00027777778f);
            impulse.v[0] = 0.0f;
            FastVecAdd(&context->velocities[i], &context->velocities[i], &impulse);
            local.q = 0;
            local.v[0] = -0.4f;
            matrix_mul_vec3(&local, &local, actor->matrix);
            FastVecAdd(&local, &local, actor->position);
            part_spawn_two_colored_sparkles(actor, &local);
        }

        /* Fire on circle or square once the reload timer has run out. */
        if (!context->phase && math_fast_float_d(&context->timers[i])
            && (pressed[i] & (PAD_CIRCLE | PAD_SQUARE))) {
            muzzle.q = 0;
            muzzle.v[1] = context->velocities[i].v[1];
            muzzle.v[2] = context->velocities[i].v[2];
            local.q = muzzle.q;
            matrix_mul_vec3(&muzzle, &D_L00_001AFAC0, actor->matrix);
            FastVecAdd(&muzzle, &muzzle, actor->position);
            vec_scale_to_length(&impulse, actor->matrix[0], D_L00_001AFAB8 * 0.016666668f);
            matrix_mul_vec3(&local, &local, D_L00_001B8FF0);
            FastVecAdd(&impulse, &impulse, &local);
            pair_game_spawn_shot(actor, &muzzle, &impulse, (void *)i);
            context->timers[i] = D_L00_001AFA48;
        }

        /* Pull toward the centre, cap the speed and move. */
        pair_game_apply_centre_pull(context->positions[i].v[1], context->positions[i].v[2],
                          D_L00_001AFA40 * 0.00027777778f,
                          &context->velocities[i].v[1], &context->velocities[i].v[2]);
        vec_clamp_length(context->velocities[i].v, D_L00_001AFAB4 * 0.016666668f);
        FastVecAdd(&context->positions[i], &context->positions[i], &context->velocities[i]);
    }
}

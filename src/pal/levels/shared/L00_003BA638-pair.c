#include "include_asm.h"

#include "common.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float v[4];
} Vector;
typedef struct {
    u8 pad00[0x10];
    float position[4];           
    u8 pad20[0x34 - 0x20];
    u16 modeBits;                
    u8 pad36[0x68 - 0x36];
    void *vars;                  
    u8 pad6C[0xC0 - 0x6C];
    float matrix[3][4];          
    float rotation[4];           
} Moby;
typedef struct {
    Moby *actors[2];
    float steering[2];
    Vector positions[2];
    Vector velocities[2];
    int timers[2];
    int scores[2];
    int phase;
} PairContext;
typedef struct {
    u8 pad000[0x100];
    float analog[16];            
    u8 pad140[0x1A0 - 0x140];
    u32 held;                    
    u32 pressed;                 
} PadState;
#define PAD_CROSS  0x0040
#define PAD_CIRCLE 0x0020
#define PAD_SQUARE 0x0080
#define PAD_RIGHT  0x2000
#define PAD_LEFT   0x8000
extern PadState g_pad_state;
extern PadState g_pad_device_state;
extern float g_cam_follow_matrix[12];
extern float g_pair_game_turn_rate __attribute__((sda));
extern float g_pair_game_turn_accel __attribute__((sda));
extern float g_pair_game_thrust __attribute__((sda));
extern float g_pair_game_top_speed __attribute__((sda));
extern float g_pair_game_shot_speed __attribute__((sda));
extern Vector g_pair_game_muzzle_offset __attribute__((sda));
extern float g_pair_game_centre_pull __attribute__((sda));
extern int g_pair_game_shot_interval __attribute__((sda));
extern void matrix_from_basis_rows(void *out, void *matrix);
extern void matrix_mul_vec3(void *out, void *vector, void *matrix);
extern void vec_scale_to_length(void *out, void *in, float length);
extern void FastVecAdd(void *out, void *a, void *b);
extern float ApproachValue(float *value, float target, float step);
extern float FastAddRotations(float angle, float delta);
extern int math_fast_float_d(int *timer);
extern void part_spawn_two_colored_sparkles_pal(Moby *actor, void *position);
extern void *pair_game_spawn_shot(Moby *owner, void *position, void *velocity, void *player);
extern void pair_game_apply_centre_pull_pal(float y, float z, float strength, float *vy, float *vz);
extern void vec_clamp_length(float *vector, float limit);

/* Steers both actors from their controllers, applies thrust and firing, and moves them. */
void update_paired_actor_movement_pal(Moby *object)
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
    axes[1] = -g_pad_device_state.analog[2];
    if (g_pad_device_state.held & PAD_LEFT)
        axes[1] = 1.0f;
    else if (g_pad_device_state.held & PAD_RIGHT)
        axes[1] = -1.0f;
    held[0] = g_pad_state.held;
    held[1] = g_pad_device_state.held;
    pressed[0] = g_pad_state.pressed;
    pressed[1] = g_pad_device_state.pressed;

    matrix_from_basis_rows(inverse, g_cam_follow_matrix);
    for (i = 0; i < 2; ++i) {
        actor = context->actors[i];
        if (actor->modeBits & 1)
            continue;

        /* Turn by the stick (degrees per second to radians per frame). */
        ApproachValue(&context->steering[i], g_pair_game_turn_rate * (axes[i] * 0.0003490659f),
                      g_pair_game_turn_accel * 6.981318e-06f);
        actor->rotation[2] = FastAddRotations(actor->rotation[2], context->steering[i]);

        /* Thrust along the actor's forward axis while cross is held. */
        if (held[i] & PAD_CROSS) {
            matrix_mul_vec3(&impulse, actor->matrix[0], inverse);
            vec_scale_to_length(&impulse, &impulse, g_pair_game_thrust * 0.00040000002f);
            impulse.v[0] = 0.0f;
            FastVecAdd(&context->velocities[i], &context->velocities[i], &impulse);
            local.q = 0;
            local.v[0] = -0.4f;
            matrix_mul_vec3(&local, &local, actor->matrix);
            FastVecAdd(&local, &local, actor->position);
            part_spawn_two_colored_sparkles_pal(actor, &local);
        }

        /* Fire on circle or square once the reload timer has run out. */
        if (!context->phase && math_fast_float_d(&context->timers[i])
            && (pressed[i] & (PAD_CIRCLE | PAD_SQUARE))) {
            muzzle.q = 0;
            muzzle.v[1] = context->velocities[i].v[1];
            muzzle.v[2] = context->velocities[i].v[2];
            local.q = muzzle.q;
            matrix_mul_vec3(&muzzle, &g_pair_game_muzzle_offset, actor->matrix);
            FastVecAdd(&muzzle, &muzzle, actor->position);
            vec_scale_to_length(&impulse, actor->matrix[0], g_pair_game_shot_speed * 0.020000001f);
            matrix_mul_vec3(&local, &local, g_cam_follow_matrix);
            FastVecAdd(&impulse, &impulse, &local);
            pair_game_spawn_shot(actor, &muzzle, &impulse, (void *)i);
            context->timers[i] = ((s32)(g_pair_game_shot_interval) * 5 + 2) / 6;
        }

        /* Pull toward the centre, cap the speed and move. */
        pair_game_apply_centre_pull_pal(context->positions[i].v[1], context->positions[i].v[2],
                          g_pair_game_centre_pull * 0.00040000002f,
                          &context->velocities[i].v[1], &context->velocities[i].v[2]);
        vec_clamp_length(context->velocities[i].v, g_pair_game_top_speed * 0.020000001f);
        FastVecAdd(&context->positions[i], &context->positions[i], &context->velocities[i]);
    }
}

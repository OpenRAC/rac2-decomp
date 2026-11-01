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
extern PadState D_00138180;
extern PadState D_00138500;
extern float D_L00_001B8FF0[12];
extern float D_L00_001AFAA8 __attribute__((sda));
extern float D_L00_001AFAAC __attribute__((sda));
extern float D_L00_001AFAB0 __attribute__((sda));
extern float D_L00_001AFAB4 __attribute__((sda));
extern float D_L00_001AFAB8 __attribute__((sda));
extern Vector D_L00_001AFAC0 __attribute__((sda));
extern float D_L00_001AFA40 __attribute__((sda));
extern int D_L00_001AFA48 __attribute__((sda));
extern void func_00283698(void *out, void *matrix);
extern void func_00283098(void *out, void *vector, void *matrix);
extern void func_00282F20(void *out, void *in, float length);
extern void func_00282CC0(void *out, void *a, void *b);
extern float func_002AA2E8(float *value, float target, float step);
extern float func_00283B98(float angle, float delta);
extern int func_00282948(int *timer);
extern void func_PAL_L00_003BAFE0(Moby *actor, void *position);
extern void *func_L00_003B7410(Moby *owner, void *position, void *velocity, void *player);
extern void func_PAL_L00_003BAD50(float y, float z, float strength, float *vy, float *vz);
extern void func_002AC9F8(float *vector, float limit);

/* Steers both actors from their controllers, applies thrust and firing, and moves them. */
void func_PAL_L00_003BA638(Moby *object)
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

    axes[0] = -D_00138180.analog[2];
    if (D_00138180.held & PAD_LEFT)
        axes[0] = 1.0f;
    else if (D_00138180.held & PAD_RIGHT)
        axes[0] = -1.0f;
    axes[1] = -D_00138500.analog[2];
    if (D_00138500.held & PAD_LEFT)
        axes[1] = 1.0f;
    else if (D_00138500.held & PAD_RIGHT)
        axes[1] = -1.0f;
    held[0] = D_00138180.held;
    held[1] = D_00138500.held;
    pressed[0] = D_00138180.pressed;
    pressed[1] = D_00138500.pressed;

    func_00283698(inverse, D_L00_001B8FF0);
    for (i = 0; i < 2; ++i) {
        actor = context->actors[i];
        if (actor->modeBits & 1)
            continue;

        /* Turn by the stick (degrees per second to radians per frame). */
        func_002AA2E8(&context->steering[i], D_L00_001AFAA8 * (axes[i] * 0.0003490659f),
                      D_L00_001AFAAC * 6.981318e-06f);
        actor->rotation[2] = func_00283B98(actor->rotation[2], context->steering[i]);

        /* Thrust along the actor's forward axis while cross is held. */
        if (held[i] & PAD_CROSS) {
            func_00283098(&impulse, actor->matrix[0], inverse);
            func_00282F20(&impulse, &impulse, D_L00_001AFAB0 * 0.00040000002f);
            impulse.v[0] = 0.0f;
            func_00282CC0(&context->velocities[i], &context->velocities[i], &impulse);
            local.q = 0;
            local.v[0] = -0.4f;
            func_00283098(&local, &local, actor->matrix);
            func_00282CC0(&local, &local, actor->position);
            func_PAL_L00_003BAFE0(actor, &local);
        }

        /* Fire on circle or square once the reload timer has run out. */
        if (!context->phase && func_00282948(&context->timers[i])
            && (pressed[i] & (PAD_CIRCLE | PAD_SQUARE))) {
            muzzle.q = 0;
            muzzle.v[1] = context->velocities[i].v[1];
            muzzle.v[2] = context->velocities[i].v[2];
            local.q = muzzle.q;
            func_00283098(&muzzle, &D_L00_001AFAC0, actor->matrix);
            func_00282CC0(&muzzle, &muzzle, actor->position);
            func_00282F20(&impulse, actor->matrix[0], D_L00_001AFAB8 * 0.020000001f);
            func_00283098(&local, &local, D_L00_001B8FF0);
            func_00282CC0(&impulse, &impulse, &local);
            func_L00_003B7410(actor, &muzzle, &impulse, (void *)i);
            context->timers[i] = ((s32)(D_L00_001AFA48) * 5 + 2) / 6;
        }

        /* Pull toward the centre, cap the speed and move. */
        func_PAL_L00_003BAD50(context->positions[i].v[1], context->positions[i].v[2],
                          D_L00_001AFA40 * 0.00040000002f,
                          &context->velocities[i].v[1], &context->velocities[i].v[2]);
        func_002AC9F8(context->velocities[i].v, D_L00_001AFAB4 * 0.020000001f);
        func_00282CC0(&context->positions[i], &context->positions[i], &context->velocities[i]);
    }
}

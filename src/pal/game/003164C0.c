#include "include_asm.h"



#include "common.h"
typedef struct {
    float velocity[4];           
    char pad10[0x34 - 0x10];
    short lifetime;              
    char pad36[0x5C - 0x36];
    int spawnFrame;              
} ThrownVars;
typedef struct Moby {
    char pad00[0x10];
    float position[4];           
    unsigned char state;         
    char pad21[0x28 - 0x21];
    struct Moby *next;           
    float scale;                 
    char pad30[0x68 - 0x30];
    ThrownVars *vars;            
    char pad6C[0xAA - 0x6C];
    short oClass;                
} Moby;
typedef struct {
    char pad000[0x110];
    float velocity[4];           
    char pad120[0x33C - 0x120];
    Moby *groundMoby;            
    char pad340[0x2290 - 0x340];
    Moby *moby;                  
} Hero;
typedef struct {
    char pad00[0x20];
    float point[4];              
    char pad30[0x10];
    float normal[4];             
} Collision;
extern Hero g_hero_state;
extern Collision g_collision_hit;
extern Moby *D_001B1B68 __attribute__((sda));
extern float math_random_float_range(float min, float max);
extern void FastVecAdd(void *out, void *a, void *b);
extern void vec_scale_to_length(void *out, void *vector, float scale);
extern void FastVecScale(void *out, void *vector, float scale);
extern void vec_fast_normalize(void *out, void *vector, void *normal);
extern char *moby_get_private_value_2(Moby *moby);
extern int CollLine(void *start, void *end, int, void *moby, int);

/* Launches self from position with velocity plus a random spread (plus the velocity of the
 * moby the hero stands on) and 120 frames of life, retires the oldest other moby of its class
 * when there are nine, and if the line from the hero hits something, starts at the hit point
 * with its velocity bounced off the surface. */
void func_PAL_00316EC0(float *position, Moby *self, float *velocity)
{
    /* Quadword unions: the clear and the copies are single 128-bit register moves. */
    typedef unsigned int Quad __attribute__((mode(TI)));
    union {
        Quad q;
        float f[4];
    } spread, random;
    float offset[4];
    ThrownVars *vars = self->vars;
    Moby *moby;
    int count;
    Moby *oldest;
    int oldestFrame;

    random.q = 0;
    random.f[0] = math_random_float_range(-1.0f, 1.0f);
    random.f[1] = math_random_float_range(-1.0f, 1.0f);
    random.f[2] = math_random_float_range(-1.0f, 1.0f);
    spread.q = random.q;
    self->state = 0;
    self->scale *= 1.5384616f;
    vec_scale_to_length(&spread, &spread, math_random_float_range(0.00020000001f, 0.002f));
    FastVecAdd(vars->velocity, &spread, velocity);
    if (g_hero_state.groundMoby != 0 && moby_get_private_value_2(g_hero_state.groundMoby) != 0)
        FastVecAdd(vars->velocity, vars->velocity, g_hero_state.velocity);

    vars->lifetime = 100;
    count = 0;
    oldest = 0;
    oldestFrame = 0;
    for (moby = D_001B1B68; moby != 0; moby = moby->next) {
        /* Grouped to the right: left to right, the two state tests fold into a range check. */
        if (moby->state == 0xFE ||
            (moby->state == 0xFD || (moby->oClass != self->oClass || moby == self)))
            continue;
        if (oldest == 0 || moby->vars->spawnFrame < oldestFrame) {
            oldestFrame = moby->vars->spawnFrame;
            oldest = moby;
        }
        count++;
    }
    if (count >= 9)
        oldest->vars->spawnFrame = -1;

    qcopy(self->position, position);
    /* The line test starts at the hero, at the height of position. */
    random.q = *(Quad *)g_hero_state.moby->position;
    random.f[2] = position[2];
    if (CollLine(&random, position, 0, g_hero_state.moby, 0) != 0) {
        qcopy(self->position, g_collision_hit.point);
        vec_scale_to_length(offset, g_collision_hit.normal, 0.0038800002f);
        FastVecAdd(self->position, self->position, offset);
        vec_fast_normalize(vars->velocity, vars->velocity, g_collision_hit.normal);
        FastVecScale(vars->velocity, vars->velocity, 0.6f);
    }
}


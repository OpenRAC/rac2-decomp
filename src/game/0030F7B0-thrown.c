#include "common.h"

/* The thrown moby's instance data. */
typedef struct {
    float velocity[4];          /* 0x00 */
    char pad10[0x34 - 0x10];
    short lifetime;             /* 0x34 */
    char pad36[0x5C - 0x36];
    int spawnFrame;             /* 0x5C: the frame counter when it was spawned */
} ThrownVars;

/* The moby fields this unit reads. */
typedef struct Moby {
    char pad00[0x10];
    float position[4];          /* 0x10 */
    unsigned char state;        /* 0x20 */
    char pad21[0x28 - 0x21];
    struct Moby *next;          /* 0x28 */
    float scale;                /* 0x2C */
    char pad30[0x68 - 0x30];
    ThrownVars *vars;           /* 0x68 */
    char pad6C[0xAA - 0x6C];
    short oClass;               /* 0xAA */
} Moby;

/* Prefix of the hero. */
typedef struct {
    char pad000[0x110];
    float velocity[4];          /* 0x110 */
    char pad120[0x33C - 0x120];
    Moby *groundMoby;           /* 0x33C: the moby the hero stands on */
    char pad340[0x2290 - 0x340];
    Moby *moby;                 /* 0x2290 */
} Hero;

/* The result of the last collision line test. */
typedef struct {
    char pad00[0x20];
    float point[4];             /* 0x20 */
    char pad30[0x10];
    float normal[4];            /* 0x40 */
} Collision;

extern Hero D_00189E20;
extern Collision D_001BAF80;
extern Moby *D_001B1B68 __attribute__((sda));   /* the first moby of the moby list */

extern float func_002A7878(float min, float max);
extern void func_00282CC0(void *out, void *a, void *b);
extern void func_00282F20(void *out, void *vector, float scale);
extern void func_00282D30(void *out, void *vector, float scale);
extern void func_00283028(void *out, void *vector, void *normal);
extern char *func_002AD0B0(Moby *moby);
extern int func_002761F8(void *start, void *end, int, void *moby, int);

/* Launches self from position with velocity plus a random spread (plus the velocity of the
 * moby the hero stands on) and 120 frames of life, retires the oldest other moby of its class
 * when there are nine, and if the line from the hero hits something, starts at the hit point
 * with its velocity bounced off the surface. */
void func_003159D0(float *position, Moby *self, float *velocity)
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
    random.f[0] = func_002A7878(-1.0f, 1.0f);
    random.f[1] = func_002A7878(-1.0f, 1.0f);
    random.f[2] = func_002A7878(-1.0f, 1.0f);
    spread.q = random.q;
    self->state = 0;
    self->scale *= 1.5384616f;
    vec_scale_to_length(&spread, &spread, func_002A7878(0.00016666666f, 0.0016666668f));
    FastVecAdd(vars->velocity, &spread, velocity);
    if (D_00189E20.groundMoby != 0 && func_002AD0B0(D_00189E20.groundMoby) != 0)
        FastVecAdd(vars->velocity, vars->velocity, D_00189E20.velocity);

    vars->lifetime = 120;
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
    random.q = *(Quad *)D_00189E20.moby->position;
    random.f[2] = position[2];
    if (CollLine(&random, position, 0, D_00189E20.moby, 0) != 0) {
        qcopy(self->position, D_001BAF80.point);
        vec_scale_to_length(offset, D_001BAF80.normal, 0.0026944445f);
        FastVecAdd(self->position, self->position, offset);
        func_00283028(vars->velocity, vars->velocity, D_001BAF80.normal);
        FastVecScale(vars->velocity, vars->velocity, 0.6f);
    }
}

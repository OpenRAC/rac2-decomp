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
extern Hero D_00189E20;
extern Collision D_001BAF80;
extern Moby *D_001B1B68 __attribute__((sda));
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
    random.f[0] = func_002A7878(-1.0f, 1.0f);
    random.f[1] = func_002A7878(-1.0f, 1.0f);
    random.f[2] = func_002A7878(-1.0f, 1.0f);
    spread.q = random.q;
    self->state = 0;
    self->scale *= 1.5384616f;
    func_00282F20(&spread, &spread, func_002A7878(0.00020000001f, 0.002f));
    func_00282CC0(vars->velocity, &spread, velocity);
    if (D_00189E20.groundMoby != 0 && func_002AD0B0(D_00189E20.groundMoby) != 0)
        func_00282CC0(vars->velocity, vars->velocity, D_00189E20.velocity);

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
    random.q = *(Quad *)D_00189E20.moby->position;
    random.f[2] = position[2];
    if (func_002761F8(&random, position, 0, D_00189E20.moby, 0) != 0) {
        qcopy(self->position, D_001BAF80.point);
        func_00282F20(offset, D_001BAF80.normal, 0.0038800002f);
        func_00282CC0(self->position, self->position, offset);
        func_00283028(vars->velocity, vars->velocity, D_001BAF80.normal);
        func_00282D30(vars->velocity, vars->velocity, 0.6f);
    }
}


#include "include_asm.h"
#include "names.h"

/* func_002C3F88 in its own unit for the grouped lq/sq profile. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    unsigned char unk00;
    unsigned char unk01;
    unsigned char unk02;
    unsigned char unk03;
    int colour;
    unsigned char unk08;
    unsigned char unk09;
    short life;
    float unk0C;
    TI128 position;
    struct {
        float velocity[3];
        int owner;
        float unk10;
        float unk14;
        short age;
        short fade;
        short mode;
    } motion;
} Particle_002C3F88;

extern Particle_002C3F88 *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern int func_002A77E0(int);
extern unsigned char *D_001F264C;

/* Spawns a spark particle at position for owner; mode 0 fades it out over its
   life, a velocity is copied when given. */
/* Creates a spark that belongs to an owner and can fade out over its life. */
Particle_002C3F88 *func_002C3F88(int owner, TI128 *position, int life, int mode, int alpha,
                                 float *velocity, float extraA, float extraB)
{
    Particle_002C3F88 *p = AllocParticle(0x43);
    typeof(p->motion) *m = &p->motion;

    if (p != 0) {
        p->position = *position;
        m->owner = owner;
        m->unk10 = extraA;
        m->unk14 = extraB;
        p->colour = alpha | 0x409B9B00;
        p->unk09 = FloatToInt(4.0f) + 0x40;
        p->unk01 = 0;
        p->unk03 = 0x48;
        p->unk0C = 52500.0f;
        p->unk08 = RandomIntBelow(0xFF);
        m->mode = mode;
        m->age = 0;
        if (mode == 0)
            p->unk02 = D_001F264C[0];
        else
            p->unk02 = D_001F264C[1];
        if (mode == 0)
            m->fade = FloatToInt(127.0f / IntToFloat(life));
        if (velocity != 0) {
            m->velocity[0] = velocity[0];
            m->velocity[1] = velocity[1];
            m->velocity[2] = velocity[2];
        }
        p->life = life;
    }
    return p;
}

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    short fade;
    unsigned char kind;
    unsigned char unk03;
} ParticleMotion_002C36D0;
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
    ParticleMotion_002C36D0 motion;
} Particle_002C36D0;

extern Particle_002C36D0 *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern int func_002A77E0(int);
extern unsigned char *D_001F2638;

/* Creates a bluish particle that fades out over the given life. */
Particle_002C36D0 *func_002C36D0(TI128 *position, int life, int kind, int extra)
{
    Particle_002C36D0 *p = AllocParticle(0x3E);

    if (p != 0) {
        ParticleMotion_002C36D0 *m = &p->motion;

        p->position = *position;
        p->colour = 0x7F7F4040;
        p->unk09 = FloatToInt(4.0f) + 0x40;
        p->unk01 = 0;
        p->unk03 = 0x48;
        p->unk0C = 30000.0f;
        p->unk08 = RandomIntBelow(0xFF);
        m->kind = kind;
        m->unk03 = extra;
        if (kind >= 2) {
            kind = 0;
        }
        p->unk02 = D_001F2638[kind];
        m->fade = FloatToInt(127.0f / IntToFloat(life));
        p->life = life;
    }
    return p;
}

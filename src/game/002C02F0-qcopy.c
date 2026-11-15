#include "include_asm.h"
#include "names.h"

/* func_002C02F0 in its own unit for the grouped lq/sq profile. */

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
        TI128 velocity;
        float unk10;
        short unk14;
        short unk16;
        unsigned char kind;
        unsigned char scale;
        char pad1A[2];
        int unk1C;
    } motion;
} Particle_002C02F0;

extern Particle_002C02F0 *func_002B9030(int);
extern int func_002AAE98(float, float, float, float);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern int func_001163B0(void);
extern unsigned char *D_001F2570;

/* Spawns a grey smoke particle like func_002C0CC0, sized by scale; kinds below 5
   get a random size and a shorter random life. */
/* Creates a grey smoke puff whose size depends on the given scale. */
Particle_002C02F0 *func_002C02F0(TI128 *position, TI128 *velocity, unsigned char kind, int extra,
                                 unsigned char scale, int shade)
{
    Particle_002C02F0 *p = AllocParticle(0x28);
    typeof(p->motion) *m = &p->motion;
    float turn;

    if (p != 0) {
        p->position = *position;
        m->velocity = *velocity;
        p->colour = PackColorFloatsToWord(0.7f, 0.7f, 0.7f, 0.08f);
        p->unk09 = (shade >> 5 << 4) + FloatToInt(4.0f);
        p->unk01 = 0;
        p->unk03 = 0x44;
        turn = RandomAngle();
        m->unk10 = turn;
        p->unk08 = (int)(turn * 256.0f);
        p->unk02 = D_001F2570[Rand() & 7];
        m->scale = scale;
        m->kind = kind;
        m->unk14 = 0;
        m->unk16 = 0;
        if (kind < 5) {
            p->unk0C = RandomFloatRange(IntToFloat(m->scale) * 656.25f, IntToFloat(m->scale) * 937.5f);
            p->life = 0x12 - Rand() % 15;
        } else {
            p->unk0C = IntToFloat(m->scale) * 937.5f;
            p->life = 0x12;
        }
        m->unk1C = extra;
    }
    return p;
}

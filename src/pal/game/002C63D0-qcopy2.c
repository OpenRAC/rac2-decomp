#include "include_asm.h"

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
        char pad19[3];
        int unk1C;
    } motion;
} Particle_002C0CC0;
extern Particle_002C0CC0 *func_002B9030(int);
extern int func_002AAE98(float, float, float, float);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_001163B0(void);
extern unsigned char *D_001F2570;

extern unsigned char *D_PAL_001F2688;

/* Spawns a grey smoke particle at position with velocity; kinds below 5 get a
   random size and a shorter random life. */
Particle_002C0CC0 *func_PAL_002C6890(TI128 *position, TI128 *velocity, unsigned char kind, int arg3)
{
    Particle_002C0CC0 *p = func_002B9030(0x52);
    typeof(p->motion) *m = &p->motion;
    float f;

    if (p != 0) {
        p->position = *position;
        m->velocity = *velocity;
        p->colour = func_002AAE98(0.7f, 0.7f, 0.7f, 0.08f);
        p->unk09 = func_00283CF0(4.0f) + 0x40;
        p->unk01 = 0;
        p->unk03 = 0x44;
        f = func_002A7878(0.0f, 1.0f);
        m->unk10 = f;
        p->unk08 = (int)(f * 256.0f);
        p->unk02 = D_PAL_001F2688[func_001163B0() & 7];
        m->kind = kind;
        m->unk14 = 0;
        m->unk16 = 0;
        if (kind < 5) {
            p->unk0C = func_002A7878(7000.0f, 10000.0f);
            p->life = 0xF - func_001163B0() % 12;
        } else {
            p->life = 0xF;
            p->unk0C = 1e+04f;
        }
        m->unk1C = arg3;
    }
    return p;
}



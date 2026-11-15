#include "include_asm.h"
#include "names.h"

/* func_002C5B70 in its own unit for the grouped lq/sq profile. */

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
} Particle_002C5B70;

extern Particle_002C5B70 *part_alloc(int);
extern int gfx_pack_color_floats(float, float, float, float);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern int func_001163B0(void);
extern unsigned char *D_001F2688;

/* Spawns a grey smoke particle at position with velocity; kinds below 5 get a
   random size and a shorter random life. */
/* Creates a grey smoke puff at a position with a starting speed. */
Particle_002C5B70 *part_spawn_smoke_alt(TI128 *position, TI128 *velocity, unsigned char kind, int extra)
{
    Particle_002C5B70 *p = part_alloc(0x52);
    typeof(p->motion) *m = &p->motion;
    float turn;

    if (p != 0) {
        p->position = *position;
        m->velocity = *velocity;
        p->colour = gfx_pack_color_floats(0.7f, 0.7f, 0.7f, 0.08f);
        p->unk09 = FloatToInt(4.0f) + 0x40;
        p->unk01 = 0;
        p->unk03 = 0x44;
        turn = math_random_float_range(0.0f, 1.0f);
        m->unk10 = turn;
        p->unk08 = (int)(turn * 256.0f);
        p->unk02 = D_001F2688[func_001163B0() & 7];
        m->kind = kind;
        m->unk14 = 0;
        m->unk16 = 0;
        if (kind < 5) {
            p->unk0C = math_random_float_range(7000.0f, 10000.0f);
            p->life = 0x12 - func_001163B0() % 15;
        } else {
            p->life = 0x12;
            p->unk0C = 10000.0f;
        }
        m->unk1C = extra;
    }
    return p;
}

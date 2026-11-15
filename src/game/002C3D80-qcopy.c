#include "include_asm.h"
#include "names.h"

/* func_002C3D80 in its own unit for the grouped lq/sq profile. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    unsigned char unk00;
    unsigned char unk01;
    unsigned char unk02;
    unsigned char unk03;
    int colour;
    unsigned char unk08;
    unsigned char unk09;
    short unk0A;
    float unk0C;
    TI128 position;
    struct {
        float velocity[4];
        float offset[3];
        int mode;
    } motion;
} Particle_002C3D80;

extern Particle_002C3D80 *part_alloc(int);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern int func_001163B0(void);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern unsigned char *D_001F2648;

/* Spawns a puff particle at position drifting outward in a random direction;
   colour -1 picks a random grey. */
/* Creates a puff that drifts outward in a random direction. */
Particle_002C3D80 *part_spawn_puff(TI128 *position, int colour, float scale, float rise)
{
    Particle_002C3D80 *p = part_alloc(0x42);
    float angle;
    float speed;
    typeof(p->motion) *m;

    if (p != 0) {
        p->position = *position;
        p->colour = colour == -1 ? ((math_random_int_below(6) + 0x14) << 24) | 0x808080 : colour;
        p->unk09 = FloatToInt(1.0f) + 0x20;
        p->unk03 = 0x48;
        p->unk01 = 1;
        if (math_random_int_below(0x100) & 1)
            p->unk02 = D_001F2648[0];
        else
            p->unk02 = D_001F2648[1];
        p->unk08 = func_001163B0();
        p->unk0A = 4;
        p->unk0C = scale * 210000.0f;
        m = &p->motion;
        angle = math_random_angle();
        speed = math_random_float_range(0.0015f, 0.0025f);
        p->motion.velocity[0] = math_fast_sin_or_cos_a(angle) * speed;
        m->velocity[1] = math_fast_sin_or_cos_b(angle) * speed;
        m->offset[0] = rise;
        m->velocity[2] = 0.0f;
    }
    return p;
}

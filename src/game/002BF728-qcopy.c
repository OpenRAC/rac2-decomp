#include "include_asm.h"
#include "names.h"

/* func_002BF728 in its own unit for the grouped lq/sq profile. */

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
    float size;
    TI128 position;
    struct {
        float velocity[3];
        float scale;
        float floor;
        float angle;
        float spin;
        float drift;
    } motion;
} Particle_002BF728;

typedef struct {
    char pad000[0x88];
    float z;
    char pad08C[0x2A4];
    float water;
    char pad334[0x1F60];
    int state;
} HeroView_002BF728;

extern Particle_002BF728 *part_alloc(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern unsigned char *D_001F25C8;
extern char g_hero_state[];

/* Spawns a bubble particle at position with velocity; a floor of -1 follows
   the hero (just above it while swimming, else the water level). */
/* Creates a bubble that floats up through the water. */
Particle_002BF728 *part_spawn_bubble(TI128 *position, float *velocity, float scale, float floor)
{
    Particle_002BF728 *p = part_alloc(0x22);
    typeof(p->motion) *m = &p->motion;

    if (p != 0) {
        p->colour = 0x88A0A0A0;
        p->unk09 = FloatToInt(4.0f) + 0x40;
        p->unk01 = 0;
        p->unk03 = 0x44;
        m->scale = math_random_float_range(0.75f, 1.25f) * scale;
        p->size = 5250.0f;
        p->unk08 = math_random_int_range(-10, 10) - 0x80;
        p->unk02 = *D_001F25C8;
        p->life = math_random_int_range(0x46, 0x8C);
        if (floor == -1.0f) {
            HeroView_002BF728 *hero = (HeroView_002BF728 *)g_hero_state;

            if (hero->state == 0x30)
                m->floor = hero->z + 0.4f;
            else
                m->floor = hero->water;
        } else {
            m->floor = floor;
        }
        m->angle = math_random_angle();
        m->spin = math_random_float_range(0.0290888250f, 0.1163553f);
        m->drift = math_random_float_range(0.008333334f, 0.023333334f);
        m->velocity[0] = velocity[0];
        m->velocity[1] = velocity[1];
        m->velocity[2] = velocity[2];
        p->position = *position;
    }
    return p;
}

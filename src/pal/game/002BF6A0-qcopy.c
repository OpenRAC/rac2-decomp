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
extern Particle_002BF728 *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern unsigned char *D_001F25C8;
extern char D_00189E20[];

/* Spawns a bubble particle at position with velocity; a floor of -1 follows
   the hero (just above it while swimming, else the water level). */
Particle_002BF728 *func_PAL_002C0428(TI128 *position, float *velocity, float scale, float floor)
{
    Particle_002BF728 *p = func_002B9030(0x22);
    typeof(p->motion) *m = &p->motion;

    if (p != 0) {
        p->colour = 0x88A0A0A0;
        p->unk09 = func_00283CF0(4.0f) + 0x40;
        p->unk01 = 0;
        p->unk03 = 0x44;
        m->scale = func_002A7878(0.75f, 1.25f) * scale;
        p->size = 5.25e+03f;
        p->unk08 = func_002A7820(-10, 10) - 0x80;
        p->unk02 = *D_001F25C8;
        p->life = func_002A7820(0x3A, 0x75);
        if (floor == -1.0f) {
            HeroView_002BF728 *hero = (HeroView_002BF728 *)D_00189E20;

            if (hero->state == 0x30)
                m->floor = hero->z + 0.4f;
            else
                m->floor = hero->water;
        } else {
            m->floor = floor;
        }
        m->angle = func_002A7940();
        m->spin = func_002A7878(0.03490659f, 0.13962635f);
        m->drift = func_002A7878(0.010000001f, 0.028f);
        m->velocity[0] = velocity[0];
        m->velocity[1] = velocity[1];
        m->velocity[2] = velocity[2];
        p->position = *position;
    }
    return p;
}

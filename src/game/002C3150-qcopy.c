#include "include_asm.h"
#include "names.h"

/* func_002C3150: spawns a particle at position with velocity; mode 1 keeps it
   relative to the hero. Its own unit for the grouped lq/sq profile. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    unsigned char unk00;
    unsigned char unk01;
    unsigned char unk02;
    unsigned char unk03;
    int unk04;
    unsigned char unk08;
    unsigned char unk09;
    short unk0A;
    float unk0C;
    TI128 position;
    struct {
        TI128 velocity;
        float offset[3];
        int mode;
    } motion;
} Particle_002C3150;

extern Particle_002C3150 *part_alloc(int);
extern int FloatToInt(float);
typedef struct {
    char pad00[0x80];
    float position[3];
} HeroView_002C3150;

extern char g_hero_state[];
extern unsigned char *D_001F2614;

/* Creates a particle with a starting speed. In mode 1 it keeps its distance from the hero. */
Particle_002C3150 *part_spawn_hero_relative(TI128 *position, TI128 *velocity, int colour,
                                 unsigned char life, unsigned char seed, int mode, float scale)
{
    Particle_002C3150 *p = part_alloc(0x3C);
    typeof(p->motion) *m;

    if (p != 0) {
        m = &p->motion;
        p->position = *position;
        m->velocity = *velocity;
        m->mode = mode;
        if (mode == 1) {
            m->offset[0] = ((float *)&p->position)[0] - ((HeroView_002C3150 *)g_hero_state)->position[0];
            m->offset[1] = ((float *)&p->position)[1] - ((HeroView_002C3150 *)g_hero_state)->position[1];
            m->offset[2] = ((float *)&p->position)[2] - ((HeroView_002C3150 *)g_hero_state)->position[2];
        }
        p->unk04 = colour;
        p->unk09 = FloatToInt(1.0f) + 0x20;
        p->unk03 = 0x48;
        p->unk08 = seed;
        p->unk01 = 0;
        p->unk0C = scale * 210000.0f;
        p->unk02 = *D_001F2614;
        p->unk0A = life;
    }
    return p;
}

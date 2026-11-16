#include "include_asm.h"
#include "names.h"

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
        float velocity[4];
        short unk10;
        unsigned char mode;
        unsigned char unk13;
        unsigned char unk14;
        unsigned char unk15;
        unsigned char alpha;
        unsigned char unk17;
        int unk18;
        float unk1C;
    } motion;
} Particle_002C56B0;
extern Particle_002C56B0 *part_alloc(int);
extern int FloatToInt(float);
extern int func_001163B0(void);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);
extern unsigned char *g_part_tex_burst_ember_table;

/* Spawns a debris particle at position: mode 0 sits still for life frames, mode 1
   flies off at a random speed and direction for life1 frames. */
Particle_002C56B0 *part_spawn_debris_two_mode_pal(TI128 *position, unsigned char arg1, unsigned char mode, short life,
                                 unsigned char arg4, unsigned char life1, int arg6, float arg7,
                                 float speed)
{
    Particle_002C56B0 *p = part_alloc(0x51);
    typeof(p->motion) *m;
    float v;
    float a;

    if (p != 0) {
        p->position = *position;
        m = &p->motion;
        p->unk09 = FloatToInt(0.0f) + 0x70;
        p->unk01 = 0;
        p->unk03 = 0x44;
        p->unk02 = g_part_tex_burst_ember_table[func_001163B0() & 7];
        p->size = 21000.0f;
        p->unk08 = func_001163B0();
        m->mode = mode;
        m->unk13 = arg4;
        m->unk18 = arg6;
        m->unk1C = arg7;
        m->unk17 = arg1;
        m->unk10 = life;
        m->unk15 = life1;
        switch (m->mode) {
        case 0:
            p->life = life;
            p->colour = 0xFF808080;
            m->unk14 = 0;
            break;
        case 1:
            v = math_random_float_range(3.0f, 9.0f) * speed * 0.020000001f;
            a = math_random_angle();
            vec_build_spherical_offset(m, v, a, math_random_float_range(1.343903660774231f, 1.7976893186569214f));
            p->size = 42000.0f;
            m->alpha = (func_001163B0() & 0x1F) + 0x10;
            p->colour = (m->alpha << 24) | 0x808080;
            p->life = life1;
            m->unk14 = 1;
            break;
        }
    }
    return p;
}

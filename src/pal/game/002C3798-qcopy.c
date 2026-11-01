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
        float velocity[4];
        unsigned char mode;
        unsigned char life0;
        unsigned char unk12;
        unsigned char unk13;
        unsigned char unk14;
        unsigned char unk15;
        unsigned char alpha;
        unsigned char unk17;
        int unk18;
        float unk1C;
    } motion;
} Particle_002C2A88;
extern Particle_002C2A88 *func_002B9030(int);
extern int func_00283CF0(float);
extern int func_001163B0(void);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
extern unsigned char *D_001F2628;

/* Spawns a debris particle at position: modes 0 and 1 sit still for life frames,
   mode 2 flies off at a random speed and direction for life1 frames. */
Particle_002C2A88 *func_PAL_002C3798(TI128 *position, unsigned char mode, unsigned char life,
                                 unsigned char arg3, unsigned char arg4, unsigned char life1, int arg6,
                                 float arg7, float speed)
{
    Particle_002C2A88 *p = func_002B9030(0x3A);
    typeof(p->motion) *m;
    float v;
    float a;

    if (p != 0) {
        p->position = *position;
        m = &p->motion;
        p->unk09 = func_00283CF0(0.0f) + 0x70;
        p->unk01 = 0;
        p->unk03 = 0x44;
        p->unk02 = D_001F2628[func_001163B0() & 7];
        p->size = 21000.0f;
        p->unk08 = func_001163B0();
        m->mode = mode;
        m->unk12 = arg3;
        m->unk13 = arg4;
        m->unk18 = arg6;
        m->unk1C = arg7;
        m->life0 = life;
        m->unk15 = life1;
        switch (m->mode) {
        case 0:
        case 1:
            p->life = life;
            p->colour = 0xFF808080;
            m->unk14 = 0;
            break;
        case 2:
            v = func_002A7878(3.0f, 9.0f) * speed * 0.020000001f;
            a = func_002A7940();
            func_002AF000(m, v, a, func_002A7878(1.343903660774231f, 1.7976893186569214f));
            p->size = 42000.0f;
            m->alpha = (func_001163B0() & 0x1F) + 0x10;
            p->colour = (m->alpha << 24) | 0x808080;
            p->life = life1;
            m->unk14 = 2;
            break;
        }
    }
    return p;
}

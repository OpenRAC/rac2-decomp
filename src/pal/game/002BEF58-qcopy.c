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
        TI128 velocity;
        float scale[3];
        float alpha;
    } motion;
} Particle_002BE278;
extern Particle_002BE278 *func_002B9030(int);
extern int func_002AAE98(float, float, float, float);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern unsigned char *D_001F25A4;

/* Spawns a white flash particle at position moving with velocity; growing, or
   shrinking when flag is set; a negative size picks a random one. */
void func_PAL_002BEF58(TI128 *position, TI128 *velocity, int flag, float size)
{
    Particle_002BE278 *p = func_002B9030(0x19);
    typeof(p->motion) *m = &p->motion;

    if (p != 0) {
        p->position = *position;
        if (flag == 0) {
            p->colour = func_002AAE98(1.0f, 1.0f, 1.0f, 0.6f);
            m->scale[0] = 1.0f;
            m->scale[1] = 1.0f;
            m->scale[2] = 1.0f;
        } else {
            p->colour = func_002AAE98(1.0f, 1.0f, 1.0f, 0.6f);
            m->scale[0] = -1.0f;
            m->scale[1] = -1.0f;
            m->scale[2] = -1.0f;
        }
        p->unk09 = func_00283CF0(4.0f) + 0x40;
        p->unk03 = 0x48;
        p->unk01 = 0;
        if (size < 0.0f)
            p->size = func_002A7878(5000.0f, 30000.0f);
        else
            p->size = size;
        p->unk08 = 0;
        p->unk02 = *D_001F25A4;
        m->alpha = 0.6f;
        p->life = 0x43;
        m->velocity = *velocity;
    }
}

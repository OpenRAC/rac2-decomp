#include "include_asm.h"

#include "common.h"
extern int func_00283CF0(float);
extern unsigned char *D_L01_001FF164;
extern float func_002A7878(float f12, float f13);
typedef int Quad331CA0 __attribute__((mode(TI)));
typedef struct { unsigned char b0, b1, b2, b3; int color; unsigned char seed, alpha; unsigned short size; float life; union { Quad331CA0 q; float f[4]; } position; float payload[8]; } Particle331CA0;
extern Particle331CA0 *func_002B9030(int kind);
extern float func_002A7878(float low, float high);
extern int func_00283CF0(float value);
extern unsigned char *D_L01_001FF164;

/* Spawns the burst particle of the given kind at position, carrying the velocity and the size scale in its payload. */
void func_PAL_L01_00333E88(Quad331CA0 *position, int kind, Quad331CA0 *velocity, float scale)
{
    Quad331CA0 saved = *velocity;
    Quad331CA0 *vp = &saved;
    Particle331CA0 *p = func_002B9030(0x49);

    if (p) {
        float life = 0.0f;
        int tint = 0;

        switch (kind) {
        case 0:
            func_002A7878(0.25f, 0.25f);
            life = 0.12f;
            tint = 0x20;
            break;
        case 1:
            func_002A7878(1.0f, 1.0f);
            life = 0.5f;
            tint = 0xD;
            break;
        }
        p->size = 0x2E;
        p->color = (tint << 24) | 0xFFFFFF;
        p->alpha = func_00283CF0(4.0f) + 0x20;
        p->b1 = 0;
        p->b3 = 0x48;
        p->b2 = D_L01_001FF164[kind];
        p->life = life * 210000.0f;
        p->seed = func_002A7878(0.0f, 360.0f);
        p->position.q = *position;
        *(Quad331CA0 *)p->payload = *vp;
        p->payload[3] = scale;
    }
}



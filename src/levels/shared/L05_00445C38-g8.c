#include "common.h"

extern float D_L05_001B98F0[];
extern int D_L05_001B1C24 SDATA(D_L05_001B1C24);
extern int D_L05_001B1C28 SDATA(D_L05_001B1C28);
extern float D_L05_001B1C2C SDATA(D_L05_001B1C2C);
extern float D_L05_001B1C30 SDATA(D_L05_001B1C30);
extern float D_L05_001B1C34 SDATA(D_L05_001B1C34);
extern float D_L05_001B1C38 SDATA(D_L05_001B1C38);
extern int D_L05_001B1C3C SDATA(D_L05_001B1C3C);
extern void FastVecScale(void *, void *, float);
extern float IntToFloat(int);
extern float math_random_angle(void);
extern void vec_add_random_offset(void *, float);
extern void gfx_draw_billboard_quad(void *, int, int, int, float, float, float);
extern void FastVecAdd(void *, void *, void *);

/* Spawns a trail of small particles along the spot where the ship just hit something. */
void part_spawn_impact_trail(unsigned char *object)
{
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float step[4], position[4], particle[4];
    float fraction, size, heading, inverse;
    int i;
    FastVecScale(step, D_L05_001B98F0, -D_L05_001B1C38);
    qcopy(position, state + 0x90);
    inverse = 1.0f / IntToFloat(D_L05_001B1C3C);
    for (i = 0; i < D_L05_001B1C3C; i++) {
        fraction = IntToFloat(i) * inverse;
        size = D_L05_001B1C2C;
        size += (D_L05_001B1C30 - size) * fraction;
        heading = math_random_angle();
        qcopy(particle, position);
        vec_add_random_offset(particle, D_L05_001B1C34);
        gfx_draw_billboard_quad(particle, D_L05_001B1C24, D_L05_001B1C28, 1, size, 0.0f, heading);
        FastVecAdd(position, position, step);
    }
}

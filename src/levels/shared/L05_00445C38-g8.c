#include "common.h"

extern float D_L05_001B98F0[];
extern int D_L05_001B1C24 SDATA(D_L05_001B1C24);
extern int D_L05_001B1C28 SDATA(D_L05_001B1C28);
extern float D_L05_001B1C2C SDATA(D_L05_001B1C2C);
extern float D_L05_001B1C30 SDATA(D_L05_001B1C30);
extern float D_L05_001B1C34 SDATA(D_L05_001B1C34);
extern float D_L05_001B1C38 SDATA(D_L05_001B1C38);
extern int D_L05_001B1C3C SDATA(D_L05_001B1C3C);
extern void func_00282D30(void *, void *, float);
extern float func_00283CE0(int);
extern float func_002A7940(void);
extern void func_002ACB48(void *, float);
extern void func_00281EB8(void *, int, int, int, float, float, float);
extern void func_00282CC0(void *, void *, void *);

/* Spawns a trail of small particles along the spot where the ship just hit something. */
void func_L05_00445C38(unsigned char *object)
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
        heading = RandomAngle();
        qcopy(particle, position);
        AddRandomOffsetToVector(particle, D_L05_001B1C34);
        DrawBillboardQuad_00281EB8(particle, D_L05_001B1C24, D_L05_001B1C28, 1, size, 0.0f, heading);
        FastVecAdd(position, position, step);
    }
}

#include "common.h"

extern int D_L11_001B1DB4 SDATA(D_L11_001B1DB4);
extern int D_L11_001B1DB8 SDATA(D_L11_001B1DB8);
extern float D_L11_001B1DBC SDATA(D_L11_001B1DBC);
extern float func_002A7940(void);
extern void func_00281EB8(void *, int, int, int, float, float, float);

/* Draws a pair of glowing sprites at each point of the ring effect, one large and one smaller. */
void func_L11_00456EA0(unsigned char *object)
{
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float *point;
    int i;
    float size, heading;
    for (i = 0; i < *(int *)(state + 0x80); i++) {
        point = (float *)(state + i * 16);
        heading = RandomAngle();
        DrawBillboardQuad_00281EB8(point, D_L11_001B1DB4, D_L11_001B1DB8, 1,
                       D_L11_001B1DBC, 0.08f, heading);
        size = D_L11_001B1DBC * 0.4f;
        heading = RandomAngle();
        DrawBillboardQuad_00281EB8(point, D_L11_001B1DB4, 0x80808080, 1, size, 0.08f, heading);
    }
}

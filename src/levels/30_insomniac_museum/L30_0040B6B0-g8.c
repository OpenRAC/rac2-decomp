#include "common.h"

extern int D_001A79F0 MACRO_ADDR;
extern int D_L30_001B1820[] SDATA(D_L30_001B1820);
extern int D_L30_001B1824[] SDATA(D_L30_001B1824);
extern int D_L30_001B18B8[] SDATA(D_L30_001B18B8);
extern int D_L30_001B18BC[] SDATA(D_L30_001B18BC);
extern float D_L30_001B1858[] SDATA(D_L30_001B1858);
extern float D_L30_001B185C[] SDATA(D_L30_001B185C);
extern float D_L30_001B18AC[] SDATA(D_L30_001B18AC);
extern float D_L30_001B18B0[] SDATA(D_L30_001B18B0);
extern float D_L30_001B1828[] SDATA(D_L30_001B1828);
extern float D_L30_001B182C[] SDATA(D_L30_001B182C);
extern float D_L30_001B1830[] SDATA(D_L30_001B1830);
extern float D_L30_001B1834[] SDATA(D_L30_001B1834);
extern float D_L30_001B1838[] SDATA(D_L30_001B1838);
extern float D_L30_001B183C[] SDATA(D_L30_001B183C);
extern int func_00278E78(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282DF0(void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float);
extern int func_001163B0(void);
extern char *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

/* rac1-decomp's clobber-free quadword clear: cse forgets the vector addresses at it, so
   the spawn call builds its velocity and acceleration pointers again (addiu from $sp). */
static __inline__ void vzero(float *v) {
    qzero_nc(v);
}

/* A museum dust burst in the style of func_L08_00424FF8: the moby's own vector at vars
   joins the velocity, scaled in z. Own unit for -g: its line label gives the pre-div.s
   nop pair. */
void func_L30_0040B6B0(char *m, void *position, int count,
                      float speed, float rise, float maxRadius, float minRadius,
                      float size, float endSize)
{
    float offset[4], velocity[4], accel[4], motion[4];
    int start, end;
    int a, b, c;
    char *particle;
    char *vars = *(char **)(m + 0x68);

    if (D_001A79F0 == 21 || D_001A79F0 == 30) {
        start = 0x30301010;
        end = D_L30_001B1824[0];
    } else {
        start = D_L30_001B1820[0];
        end = D_L30_001B1824[0];
    }
    if (!func_00278E78()) {
        start = D_L30_001B18B8[0];
        end = D_L30_001B18BC[0];
    }
    {
        int i;
        for (i = 0; i < count; i++) {
            float x, y;
            x = func_00283180(func_002A7878(-3.1415927410125732f, 3.1415927410125732f));
            offset[0] = x * func_002A7878(minRadius, maxRadius);
            y = func_00283198(func_002A7878(-3.1415927410125732f, 3.1415927410125732f));
            y *= func_002A7878(minRadius, maxRadius);
            offset[1] = y;
            offset[2] = 0;
            func_00283098(offset, offset, m + 0xC0);
            {
                float range = speed * ((maxRadius - func_00282DF0(offset)) * 0.01666666753590107f) / maxRadius;
                func_00282F20(velocity, offset, func_002A7878(range / D_L30_001B1858[0], range));
            }
            qcopy(motion, vars);
            motion[2] *= D_L30_001B18AC[0];
            func_00282CC0(velocity, velocity, motion);
            velocity[2] += func_002A7878(rise / D_L30_001B185C[0], rise) * 0.01666666753590107f;
            vzero(accel);
            func_00282CC0(offset, offset, position);
            offset[2] += D_L30_001B18B0[0];
            velocity[3] = size;
            accel[3] = endSize;
            a = func_00283CF0(func_002A7878(D_L30_001B1828[0], D_L30_001B182C[0]));
            b = func_00283CF0(func_002A7878(D_L30_001B1830[0], D_L30_001B1834[0]));
            c = func_00283CF0(func_002A7878(D_L30_001B1838[0], D_L30_001B183C[0]));
            particle = func_002BAA28(offset, velocity, accel, start, end, a, b, c, -1);
            if (particle && (func_001163B0() & 1))
                particle[3] = 0x48;
        }
    }
}

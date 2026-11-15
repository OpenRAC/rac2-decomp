#include "common.h"
typedef int BurstVector __attribute__((mode(TI)));
extern float func_002A7878(float,float), func_002A78D8(float,float), func_002A7940(void);
extern int func_002A77E0(int);
extern void func_002AF000(void *,float,float,float);
extern void func_00282D30(void *,void *,float);
extern void func_00282CD8(void *,void *,void *);
extern void *func_002C2210(void *,int,int,int,int,void *,int,float,float,float);
extern float ref_L22_003FD958_00 __attribute__((sda));
extern float ref_L22_003FD958_01 __attribute__((sda));
extern float ref_L22_003FD958_02 __attribute__((sda));
extern float ref_L22_003FD958_03 __attribute__((sda));
extern int ref_L22_003FD958_04 __attribute__((sda));
extern int ref_L22_003FD958_05 __attribute__((sda));
extern float ref_L22_003FD958_06 __attribute__((sda));
extern int ref_L22_003FD958_07 __attribute__((sda));
/* Emit two particles for each randomly perturbed point. */
void func_L22_003FD958(float *position, float *direction, int count) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float scaled[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    float life, yaw, tilt, speed;
    int sign, remaining;
    for (remaining = 0; remaining < count; remaining++) {
        life = func_002A7878(ref_L22_003FD958_00, ref_L22_003FD958_01);
        sign = func_002A77E0(2);
        if (sign == 0) sign--;
        yaw = func_002A7940();
        tilt = func_002A7878(0.6981318f, 1.5358899f);
        speed = func_002A7878(ref_L22_003FD958_02 * 0.016666668f, ref_L22_003FD958_03 * 0.016666668f);
        func_002AF000(velocity, speed, yaw, tilt);
        *(BurstVector *)scaled = *(BurstVector *)direction;
        FastVecScale(scaled, direction, func_002A7878(0.75f, 0.95f));
        add_vectors(difference, velocity, scaled);
        qcopy(point, position);
        point[0] += func_002A78D8(0.0f, 0.0375f);
        point[1] += func_002A78D8(0.0f, 0.0375f);
        point[2] += func_002A78D8(0.0f, 0.0375f);
        func_002C2210(point, ref_L22_003FD958_07, ref_L22_003FD958_04, 0, sign, velocity, 0, life * 0.1f, life, ref_L22_003FD958_06);
        func_002C2210(point, ref_L22_003FD958_07, ref_L22_003FD958_05, 1, -sign, velocity, 0, life * 0.05f, life * 0.5f, ref_L22_003FD958_06);
    }
}

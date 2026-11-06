/* func_PAL_L22_00401788, the PAL copy of func_L22_003FCF08, worded as func_PAL_L22_00402258 and built
   with gcse: 0.016666668f becomes 0.020000001f and the second argument of both func_002C2210 calls
   gets the 50 Hz scale. */
#include "common.h"
typedef int BurstVector __attribute__((mode(TI)));
extern float func_002A7878(float,float), func_002A78D8(float,float), func_002A7940(void);
extern int func_002A77E0(int);
extern void func_002AF000(void *,float,float,float);
extern void func_00282D30(void *,void *,float);
extern void func_00282CD8(void *,void *,void *);
extern void *func_002C2210(void *,int,int,int,int,void *,int,float,float,float);
extern float D_L22_001B0D08 __attribute__((sda));
extern float D_L22_001B0D0C __attribute__((sda));
extern float D_L22_001B0D10 __attribute__((sda));
extern float D_L22_001B0D1C __attribute__((sda));
extern float D_L22_001B0D20 __attribute__((sda));
extern int D_L22_001B0D2C __attribute__((sda));
extern int D_L22_001B0D30 __attribute__((sda));
extern int D_L22_001B0D34 __attribute__((sda));
/* Emit two particles for each randomly perturbed point. */
void func_PAL_L22_00401788(float *position, float *direction, int count) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float scaled[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    float life, yaw, tilt, speed;
    int sign, remaining;
    for (remaining = 0; remaining < count; remaining++) {
        life = func_002A7878(D_L22_001B0D1C, D_L22_001B0D20);
        sign = func_002A77E0(2);
        if (sign == 0) sign--;
        yaw = func_002A7940();
        tilt = func_002A7878(0.6981318f, 1.5358899f);
        speed = func_002A7878(D_L22_001B0D0C * 0.020000001f, D_L22_001B0D10 * 0.020000001f);
        func_002AF000(velocity, speed, yaw, tilt);
        *(BurstVector *)scaled = *(BurstVector *)direction;
        func_00282D30(scaled, direction, func_002A7878(0.75f, 0.95f));
        func_00282CD8(difference, velocity, scaled);
        qcopy(point, position);
        point[0] += func_002A78D8(0.0f, 0.0375f);
        point[1] += func_002A78D8(0.0f, 0.0375f);
        point[2] += func_002A78D8(0.0f, 0.0375f);
        func_002C2210(point, ((s32)(D_L22_001B0D34) * 5 + 2) / 6, D_L22_001B0D2C, 0, sign, velocity, 0, life * 0.1f, life, D_L22_001B0D08);
        func_002C2210(point, ((s32)(D_L22_001B0D34) * 5 + 2) / 6, D_L22_001B0D30, 1, -sign, velocity, 0, life * 0.07f, life * 0.7f, D_L22_001B0D08);
    }
}

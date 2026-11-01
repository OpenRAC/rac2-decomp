#include "include_asm.h"

#include "common.h"
typedef int SpawnVectorWord __attribute__((mode(TI)));
extern char D_L00_001B8DC0[];
extern void func_00282CF0(char *, char *, char *);
extern float func_00283248(float, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_002AF000(float *, float, float, float);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern void func_002A7A00(float *, float, float);
extern void *func_PAL_002C23B8(void *, void *, int, u32, int, int, float, float, float, float, float);
extern void *func_002C2210(float, void *, int, float, u32, int, int, void *, int, float);

/* Fifteen particles thrown from the point, as in func_L00_003FC820, then five pairs of trail
   effects around it, differently coloured and with opposite random signs. */
void func_PAL_L00_004019F8(float *point)
{
    float delta[4];
    float direction[4];
    float position[4];
    float base_angle;
    float scale;
    float angle;
    float elevation;
    float speed;
    float trail_scale;
    int kind;
    int sign;
    int i;
    int j;
    char *effect;

    func_00282CF0((char *)delta, D_L00_001B8DC0, (char *)point);
    base_angle = func_00283248(delta[0], delta[1]);
    for (i = 0; i < 15; i++) {
        scale = func_002A7878(0.5f, 1.25f);
        kind = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        elevation = func_002A7878(0.0f, 1.3962636f);
        angle = func_00283B98(base_angle, func_002A78D8(0.0f, 1.3962636f));
        func_002AF000(direction, scale * 0.020000001f, angle, elevation);
        position[0] = point[0] + func_002A78D8(0.0f, 0.2f);
        position[1] = point[1] + func_002A78D8(0.0f, 0.2f);
        position[2] = point[2] + func_002A78D8(0.0f, 0.2f);
        func_PAL_002C23B8(position, direction, 25, 127, 0x007F7F7F, kind,
                      func_002A7878(0.1f, 0.3f) * 210000.0f, 500.0f, 1.0f, 0.0f, 0.0f);
    }
    for (j = 0; j < 5; j++) {
        trail_scale = func_002A7878(0.25f, 0.75f);
        sign = func_002A77E0(2);
        if (sign == 0)
            sign--;
        speed = func_002A7878(1.0f, 4.0f);
        func_002A7A00(direction, speed * 0.020000001f, speed * 0.020000001f);
        *(SpawnVectorWord *)position = *(SpawnVectorWord *)point;
        position[0] += func_002A78D8(0.0f, 0.15f);
        position[1] += func_002A78D8(0.0f, 0.15f);
        position[2] += func_002A78D8(0.0f, 0.15f);
        effect = func_002C2210(trail_scale * 0.1f, position, 50, trail_scale,
                               0x7FFF1010, 0, sign, direction, 0, 0.0043200003f);
        if (effect != 0)
            effect[9] = func_00283CF0(4.0f) + 112;
        effect = func_002C2210(trail_scale * 0.05f, position, 50, trail_scale * 0.5f,
                               0x7F7F7F7F, 1, -sign, direction, 0, 0.0043200003f);
        if (effect != 0)
            effect[9] = func_00283CF0(4.0f) + 112;
    }
}

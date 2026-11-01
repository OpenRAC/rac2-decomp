#include "include_asm.h"

#include "common.h"
extern int func_00283CF0(float value);
extern char D_L00_001B8DC0[];
extern void func_00282CF0(char *, char *, char *);
extern float func_00283248(float, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_00283B98(float, float);
extern void func_002AF000(float *, float, float, float);
extern char D_L00_001B8DC0[];
extern void func_00282CF0(char *dst, char *src, char *arg);
extern float func_00283248(float, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_00283B98(float, float);
extern void func_002AF000(float *, float, float, float);
extern void func_PAL_002C23B8(float *, float *, int, int, unsigned int, int,
                          float, float, float, float, float);
extern float func_002A78D8(float, float);
#include "common.h"

/* Twenty rounds that spawn a particle at the point: each round draws a step and a random
   magnitude, jitters the point on each axis and hands the result to the spawn helper with
   210000.0f, 500.0f, 1.0f, 0.0f and 1.0f; the original game role is unknown. */
void func_PAL_L00_003E78E8(float *pos)
{
    float v[4];
    float dir[4];
    float out[4];
    float ang;
    float angle;
    float scale;
    float mag;
    float speed;
    int id;
    int i;

    func_00282CF0((char *)v, D_L00_001B8DC0, (char *)pos);
    ang = func_00283248(v[0], v[1]);

    for (i = 19; i >= 0; i--) {
        scale = func_002A7878(0.25f, 0.5f);
        id = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        func_002A7878(0.05f, 0.2f);
        speed = 210000.0f;
        mag = func_002A7878(0.0f, 1.396263599395752f);
        angle = func_00283B98(ang, func_002A78D8(0.0f, 1.396263599395752f));
        func_002AF000(dir, scale * 0.020000001f, angle, mag);
        out[0] = pos[0] + func_002A78D8(0.0f, 0.075f);
        out[1] = pos[1] + func_002A78D8(0.0f, 0.075f);
        out[2] = pos[2] + func_002A78D8(0.0f, 0.075f);
        func_PAL_002C23B8(out, dir, 12, 127, 0x007F7F7F, id,
                      func_002A7878(0.05f, 0.2f) * speed, 500.0f, 1.0f, 0.0f, 1.0f);
    }
}

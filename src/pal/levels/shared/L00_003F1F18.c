#include "include_asm.h"

extern char D_L00_001B8DC0[];
extern void func_00282CF0(char *, char *, char *);
extern float func_00283248(float, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern void func_002AF000(float *, float, float, float);
extern void func_PAL_002C23B8(float *, float *, int, int, unsigned int, int,
                          float, float, float, float, float);
extern void func_00282CF0(char *local, char *first, char *second);
extern float func_00283248(float a, float b);
extern void func_00282D30(char *dst, char *src, float scale);
extern float func_002A7878(float a, float b);
extern float func_002A78D8(float a, float b);
extern int func_00283CF0(float f);
extern float func_00283CE0(int v);
extern float func_00283B98(float a, float b);
extern void func_002AF000(float *p, float a, float b, float c);
extern char *func_PAL_002BE9A8(char *p, float fa, float fb, float fc, float fd, int v, char *local,
                            unsigned int color, int flag);
extern void func_PAL_002C23B8(float *out, float *dir, int a, int b, unsigned int color, int id,
                           float fa, float fb, float fc, float fd, float fe);
extern char D_L00_001B8DC0[];
extern char D_0018A0E0[];

/* Twenty times over: take the angle of the constant vector at D_L00_001B8DC0 and the point,
   scale the hero facing direction by a random small amount, spawn a particle at the point
   jittered by a random amount on each axis and fill the new record's fields, then spawn a
   second particle along a random direction with a random magnitude; the original game role
   is unknown. */
void func_PAL_L00_003F1F18(float *p)
{
    float v[4];
    float dir[4];
    float out[4];
    float ang;
    float scale;
    float mag;
    float angle;
    float f;
    int id;
    int i;
    char *r;
    char *q;

    func_00282CF0((char *)v, D_L00_001B8DC0, (char *)p);
    ang = func_00283248(v[0], v[1]);

    for (i = 19; i >= 0; i--) {
        f = func_002A7878(0.2f, 3.0f);
        func_00282D30((char *)dir, D_0018A0E0, -(f * 0.020000001f));
        id = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        f = func_002A7878(0.3f, 0.75f) * 210000.0f;
        out[0] = p[0] + func_002A78D8(0.0f, 0.2f);
        out[1] = p[1] + func_002A78D8(0.0f, 0.2f);
        out[2] = p[2] + func_002A78D8(0.0f, 0.2f);
        r = func_PAL_002BE9A8((char *)out, 0.0f, 1.0f, 1.01f, f, id, (char *)dir, 0x7F202020, 1);
        if (r != 0) {
            q = r + 32;
            *(unsigned char *)(r + 3) = 0x44;
            *(short *)(r + 10) = 0x4B;
            *(unsigned char *)(r + 9) = func_00283CF0(4.0f) + 0x40;
            *(float *)(q + 0x1C) = func_00283CE0(4);
            *(int *)(q + 4) = 3;
            *(unsigned char *)(q + 0xA) = 0x30;
            *(unsigned char *)(q + 0xB) = *(unsigned char *)(r + 10);
        }
        scale = func_002A7878(1.0f, 2.0f);
        mag = func_002A7878(0.0f, 1.396263599395752f);
        angle = func_00283B98(ang, func_002A78D8(0.0f, 1.396263599395752f));
        func_002AF000(dir, scale * 0.020000001f, angle, mag);
        out[0] = p[0] + func_002A78D8(0.0f, 0.1f);
        out[1] = p[1] + func_002A78D8(0.0f, 0.1f);
        out[2] = p[2] + func_002A78D8(0.0f, 0.1f);
        func_PAL_002C23B8(out, dir, 25, 127, 0x007F7F7F, id,
                      func_002A7878(0.1f, 0.5f) * 210000.0f, 500.0f, 1.0f, 0.0f, 1.0f);
    }
}


/* Twenty rounds: take the angle of the constant vector at D_L00_001B8DC0 and the point,
   build a direction from a random step and a random magnitude, jitter the point by a
   random small amount on each axis and hand the result to the spawn helper with
   210000.0f, 500.0f, 1.0f, 0.0f and 1.0f; the original game role is unknown. */
void func_PAL_L00_003F2260(float *pos)
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
        scale = func_002A7878(0.5f, 1.0f);
        id = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        func_002A7878(0.05f, 0.2f);
        speed = 210000.0f;
        mag = func_002A7878(0.0f, 1.396263599395752f);
        angle = func_00283B98(ang, func_002A78D8(0.0f, 1.396263599395752f));
        func_002AF000(dir, scale * 0.020000001f, angle, mag);
        out[0] = pos[0] + func_002A78D8(0.0f, 0.1f);
        out[1] = pos[1] + func_002A78D8(0.0f, 0.1f);
        out[2] = pos[2] + func_002A78D8(0.0f, 0.1f);
        func_PAL_002C23B8(out, dir, 25, 127, 0x007F7F7F, id,
                      func_002A7878(0.05f, 0.2f) * speed, 500.0f, 1.0f, 0.0f, 1.0f);
    }
}


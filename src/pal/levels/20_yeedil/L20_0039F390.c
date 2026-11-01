#include "include_asm.h"




#include "common.h"
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
extern char D_L20_001B9FC0[];
extern char D_0018A0E0[];

void func_PAL_L20_0039F810(float *p)
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

    func_00282CF0((char *)v, D_L20_001B9FC0, (char *)p);
    ang = func_00283248(v[0], v[1]);

    for (i = 19; i >= 0; i--) {
        f = func_002A7878(0.2f, 3.0f);
        func_00282D30((char *)dir, D_0018A0E0, -(f * 0.020000001f));
        id = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        f = func_002A7878(0.3f, 0.75f) * 210000.0f;
        out[0] = p[0] + func_002A78D8(0.0f, 0.2f);
        out[1] = p[1] + func_002A78D8(0.0f, 0.2f);
        out[2] = p[2] + func_002A78D8(0.0f, 0.2f);
        r = func_PAL_002BE9A8((char *)out, 0.0f, 1.0f, 1.01f, f, id, (char *)dir, 0x7F202020, 0);
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
                      func_002A7878(0.1f, 0.5f) * 210000.0f, 500.0f, 1.0f, 0.0f, 0.0f);
    }
}


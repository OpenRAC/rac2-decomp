#include "include_asm.h"

#include "common.h"
extern void func_00282D30(void *, void *, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float value);
extern char D_0018A0E0[];
extern unsigned char *D_L00_001FEA14;
extern char D_L00_001B8DC0[];
extern char D_L00_001A8F20_1[] __attribute__((sda));
extern void func_00282CF0(char *, char *, char *);
extern float func_00283248(float, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_00283B98(float, float);
extern void func_002AF000(float *, float, float, float);
extern int func_002A77E0(int);
extern char *func_PAL_002BE9A8(float *, float, float, int, float *, float, float, unsigned, int);
extern char *func_PAL_002C23B8(float *, float *, int, int, unsigned, int, float, float, float, float, float);
extern char D_L00_001B8DC0[];
extern void func_00282CF0(char *dst, char *src, char *arg);
extern float func_00283248(float, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_00283B98(float, float);
extern void func_002AF000(float *, float, float, float);
extern void func_00282D30(void *, void *, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
#include "common.h"

/* Emit twenty paired particles around a position, optionally adding two final flashes. */
void func_PAL_L00_003E74D8(float *pos, int unused, int extra)
{
    float v[4], dir[4], out[4];
    float angle, speed, scale, mag, direction;
    int id, i, n;
    char *p, *d;
    func_00282CF0((char *)v, D_L00_001B8DC0, (char *)pos);
    angle = func_00283248(v[0], v[1]);
    for (i = 19; i >= 0; i--) {
        func_00282D30(dir, D_0018A0E0, -(func_002A7878(0.2f, 3.0f) * 0.020000001f));
        id = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        speed = func_002A7878(0.3f, 0.75f) * 210000.0f;
        out[0] = pos[0] + func_002A78D8(0.0f, 0.2f);
        out[1] = pos[1] + func_002A78D8(0.0f, 0.2f);
        out[2] = pos[2] + func_002A78D8(0.0f, 0.2f);
        p = func_PAL_002BE9A8(out, 0.0f, 1.0f, id, dir, 1.01f, speed, 0x7F202020, 1);
        if (p) {
            p[3] = 68;
            *(short *)(p + 10) = 75;
            d = p + 32;
            p[9] = func_00283CF0(4.0f) + 64;
            *(float *)(d + 28) = func_00283CE0(4);
            *(int *)(d + 4) = 3;
            d[10] = 48;
            d[11] = p[10];
        }
        scale = func_002A7878(1.0f, 2.0f);
        mag = func_002A7878(0.0f, 1.396263599395752f);
        direction = func_00283B98(angle, func_002A78D8(0.0f, 1.396263599395752f));
        func_002AF000(dir, scale * 0.020000001f, direction, mag);
        out[0] = pos[0] + func_002A78D8(0.0f, 0.1f);
        out[1] = pos[1] + func_002A78D8(0.0f, 0.1f);
        out[2] = pos[2] + func_002A78D8(0.0f, 0.1f);
        func_PAL_002C23B8(out, dir, 25, 127, 0x7F7F7F, id,
            func_002A7878(0.1f, 0.5f) * 210000.0f, 500.0f, 1.0f, 0.0f, 1.0f);
    }
    if (extra == 1) {
        char *last;
        speed = 525000.0f;
        n = func_002A77E0(255);
        last = func_PAL_002C23B8(pos, (float *)D_L00_001A8F20_1, 4, 127, 0x207080, n, speed, 0.0f, 1.0f, 0.0f, 1.0f);
        if (last) last[2] = *D_L00_001FEA14;
        last = func_PAL_002C23B8(pos, (float *)D_L00_001A8F20_1, 4, 127, 0x207080, (n + 128) & 255, speed, 0.0f, 1.0f, 0.0f, 1.0f);
        if (last) last[2] = *D_L00_001FEA14;
    }
}



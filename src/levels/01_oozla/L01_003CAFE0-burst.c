#include "common.h"

typedef struct {
    int color;          /* 0x00 */
    int color2;         /* 0x04 */
    int altColor;       /* 0x08 */
    int altColor2;      /* 0x0C */
    float x[2];         /* 0x10 */
    float y[2];         /* 0x18 */
    float z[2];         /* 0x20 */
    float radialDiv;    /* 0x28 */
    float verticalDiv;  /* 0x2C */
    int count;          /* 0x30 */
    float height;       /* 0x34 */
    float radialSpeed;  /* 0x38 */
    float verticalSpeed;/* 0x3C */
    float outer;        /* 0x40 */
    float inner;        /* 0x44 */
    float velW;         /* 0x48 */
    float accW;         /* 0x4C */
} ParticleConfig;

extern const ParticleConfig D_L01_002A4E78;
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00283098(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_001163B0(void);
extern int func_00283CF0(float);
extern u8 *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

typedef struct {
    u8 pad[0x10];
    float position[4];  /* 0x10 */
    u8 pad20[0xA0];
    float rotation[16]; /* 0xC0 */
} ParticleOwner;

void func_L01_003D8830(ParticleOwner *a0)
{
    float pos[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    float acc[4] __attribute__((aligned(16)));
    u8 *r;
    ParticleOwner *owner = a0;
    int color = D_L01_002A4E78.color, color2 = D_L01_002A4E78.color2, flag, x, y, z;
    int i, count;
    float trig, radialSpeed, verticalSpeed, w;

    count = D_L01_002A4E78.count;
    for (i = 0; i < count; i++) {
        trig = func_00283180(func_002A7878(-3.1415927f, 3.1415927f));
        trig *= func_002A7878(D_L01_002A4E78.inner, D_L01_002A4E78.outer);
        pos[0] = trig;
        trig = func_00283198(func_002A7878(-3.1415927f, 3.1415927f));
        trig *= func_002A7878(D_L01_002A4E78.inner, D_L01_002A4E78.outer);
        pos[1] = trig;
        pos[2] = 0;
        func_00283098(pos, pos, owner->rotation);
        radialSpeed = func_00282DF0(pos);
        w = D_L01_002A4E78.outer;
        radialSpeed = D_L01_002A4E78.radialSpeed * ((w - radialSpeed) * 0.016666668f) / w;
        func_00282F20(vel, pos, func_002A7878(radialSpeed / D_L01_002A4E78.radialDiv, radialSpeed));
        verticalSpeed = D_L01_002A4E78.verticalSpeed;
        vel[2] += func_002A7878(verticalSpeed / D_L01_002A4E78.verticalDiv, verticalSpeed) * 0.016666668f;
        qzero(acc);
        func_00282CC0(pos, pos, owner->position);
        pos[2] += D_L01_002A4E78.height;
        vel[3] = D_L01_002A4E78.velW;
        acc[3] = D_L01_002A4E78.accW;
        flag = func_001163B0() & 1;
        if (!flag && (func_001163B0() & 1)) {
            color = D_L01_002A4E78.altColor;
            color2 = D_L01_002A4E78.altColor2;
        }
        x = func_00283CF0(func_002A7878(D_L01_002A4E78.x[0], D_L01_002A4E78.x[1]));
        y = func_00283CF0(func_002A7878(D_L01_002A4E78.y[0], D_L01_002A4E78.y[1]));
        z = func_00283CF0(func_002A7878(D_L01_002A4E78.z[0], D_L01_002A4E78.z[1]));
        r = func_002BAA28(pos, vel, acc, color, color2, x, y, z, -1);
        if (r && flag)
            r[3] = 0x48;
    }
}

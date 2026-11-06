#include "common.h"
typedef unsigned int WeatherQuad __attribute__((mode(TI)));
typedef struct {
    char pad[0x140];
    float position[4];
    float rotation[4];
} WeatherHero;

extern int D_001A79F0[] __attribute__((sda));
extern int D_L01_001C9A40 NOT_SDA;
extern int D_L01_001A94C0 SDATA(D_L01_001A94C0);
extern float D_L01_001AF62C SDATA(D_L01_001AF62C);
extern float D_L01_001AF630 SDATA(D_L01_001AF630);
extern float D_L01_001AF634 SDATA(D_L01_001AF634);
extern float D_L01_001AF640 SDATA(D_L01_001AF640);
extern int D_L01_001AF644 SDATA(D_L01_001AF644);
extern float D_L01_001AF648 SDATA(D_L01_001AF648);
extern float D_L01_001AF64C SDATA(D_L01_001AF64C);
extern float D_L01_001AF650 SDATA(D_L01_001AF650);
extern float D_L01_001AF654 SDATA(D_L01_001AF654);
extern float D_L01_001B27B0 SDATA(D_L01_001B27B0);
extern float D_L01_001B2F00[] __attribute__((sda));
extern int D_L01_001B2F04;
extern float D_L01_001B2EF0[] __attribute__((sda));
extern float D_L01_001B2EF4[] __attribute__((sda));
extern float D_L01_001B208C[] __attribute__((sda));
extern float D_L01_001B2090[] __attribute__((sda));
extern char D_L01_001B94C0[];
typedef struct { WeatherQuad vec; } WeatherWind;
extern WeatherWind D_L01_001B27A0 __attribute__((sda));
extern int func_002ACD38(void *);
extern void func_L01_003993C8(int);
extern int func_002829D8(void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E20(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_L00_00323F28(void *, void *, float, float, float);
extern float func_002B0520(void *);
extern void func_002B0668(void *);
extern void func_L01_00326DD8(void *, int, float, void *);
extern void func_L01_00331CA0(void *, int, void *, float);


void func_L01_00399510(char *m)
{
    float pos[4], delta[4], origin[4], velocity[4], velocity2[4];
    int special, extras, count, i, level;
    float falloff, speed, minimum, jitter;
    char *p;

    if (!func_002ACD38(m + 0x10))
        return;
    D_L01_001A94C0 = D_L01_001C9A40;
    level = D_001A79F0[0];
    switch (level) {
    case 12: case 19: case 512: special = 1; break;
    default: special = 0; break;
    }
    switch (special) {
    case 1:
        falloff = 0.2f; speed = 5.0f; minimum = 0.5f;
        jitter = 0.01666666753590107f; extras = 0;
        break;
    case 0:
    default:
        falloff = 0.15f; extras = 1; speed = 18.0f;
        minimum = D_L01_001AF62C; jitter = 0.033333335070610046f;
        break;
    }
    if (D_L01_001AF640 >= 0.0f)
        minimum = D_L01_001AF640;
    p = *(char **)(m + 0x68);
    switch (*(unsigned char *)(m + 0x20)) {
    case 0:
        *(unsigned char *)(m + 0x20) = 2;
        *(unsigned char *)(m + 0x30) = 255;
        func_L01_003993C8(special);
        goto finish;
    case 2: {
        float x, y, scale, z, top;
        if (func_002829D8(D_L01_001B2F00))
            func_L01_003993C8(special);
        func_00282CF0(delta, D_L01_001B94C0, p + 0x30);
        D_L01_001B27A0.vec = *(WeatherQuad *)(delta);
        x = D_L01_001B2090[0] - D_L01_001AF64C;
        y = D_L01_001B208C[0] - D_L01_001AF650;
        count = D_L01_001B2F04;
        if (x < 0.0f) x = 0.0f;
        if (y < 0.0f) y = 0.0f;
        x /= 1.0f - D_L01_001AF64C;
        y /= 1.0f - D_L01_001AF650;
        z = func_00283CE0(count);
        scale = 1.0f - (x > y ? x : y) * D_L01_001AF654;
        count = func_00283CF0(z * scale);
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(((WeatherHero *)(D_L01_001B94C0 - 0x140))->position);
        func_L00_00323F28(origin, origin, 16.0f, ((WeatherHero *)(D_L01_001B94C0 - 0x140))->rotation[2], ((WeatherHero *)(D_L01_001B94C0 - 0x140))->rotation[1]);
        origin[2] = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] + D_L01_001AF630;
        for (i = 0; i < count; i++) {
            float offset, length, z, floor, scale;
            *(WeatherQuad *)(pos) = *(WeatherQuad *)(origin);
            offset = func_00283180(func_002A7878(0.0f, 6.2831854820251465f));
            offset *= func_002A7878(0.0f, D_L01_001AF634);
            pos[0] += offset;
            offset = func_00283198(func_002A7878(0.0f, 6.2831854820251465f));
            offset *= func_002A7878(0.0f, D_L01_001AF634);
            pos[1] += offset;
            func_00282CF0(velocity, pos, ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position);
            length = func_00282E20(velocity);
            if (length <= 8.0f) {
                velocity2[0] = D_L01_001B2EF0[0] + func_002A7878(-jitter, jitter);
                velocity2[1] = D_L01_001B2EF4[0] + func_002A7878(-jitter, jitter);
                velocity2[2] = -(speed * 0.01666666753590107f);
                velocity2[3] = 0.0f;
            } else {
                scale = (length - 8.0f) * falloff;
                scale = speed - scale;
                if (scale < minimum) scale = minimum;
                velocity2[0] = D_L01_001B2EF0[0] + func_002A7878(-jitter, jitter);
                velocity2[1] = D_L01_001B2EF4[0] + func_002A7878(-jitter, jitter);
                velocity2[2] = -(scale * 0.01666666753590107f);
                velocity2[3] = 0.0f;
            }
            D_L01_001B27B0 = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] - D_L01_001AF648;
            z = func_002B0520(pos);
            top = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] + D_L01_001AF630;
            if (z < top) {
                int flag = 0;
                floor = z < D_L01_001B27B0 ? D_L01_001B27B0 : z;
                if (length > 8.0f) flag = D_L01_001AF644;
                if (special == 0) func_L01_00326DD8(pos, flag, floor, velocity2);
                if (special == 1) func_L01_00331CA0(pos, flag, velocity2, floor);
            }
        }
        count = (int)((float)count * 1.4f);
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(((WeatherHero *)(D_L01_001B94C0 - 0x140))->position);
        origin[2] = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] + D_L01_001AF630;
        for (i = 0; i < count; i++) {
            float offset, z, floor;
            velocity[0] = D_L01_001B2EF0[0] + func_002A7878(-jitter, jitter);
            velocity[1] = D_L01_001B2EF4[0] + func_002A7878(-jitter, jitter);
            velocity[2] = -(speed * 0.01666666753590107f);
            velocity[3] = 0.0f;
            *(WeatherQuad *)(pos) = *(WeatherQuad *)(origin);
            offset = func_00283180(func_002A7878(0.0f, 6.2831854820251465f));
            offset *= func_002A7878(0.0f, 8.0f);
            pos[0] += offset;
            offset = func_00283198(func_002A7878(0.0f, 6.2831854820251465f));
            offset *= func_002A7878(0.0f, 8.0f);
            pos[1] += offset;
            D_L01_001B27B0 = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] - D_L01_001AF648;
            z = func_002B0520(pos);
            top = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] + D_L01_001AF630;
            if (z < top) {
                floor = z < D_L01_001B27B0 ? D_L01_001B27B0 : z;
                if (special == 0) func_L01_00326DD8(pos, 0, floor, velocity);
                if (special == 1) func_L01_00331CA0(pos, 0, velocity, floor);
            }
        }
        break;
    }
    default:
        goto finish;
    }
    if (extras) {
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(D_L01_001B94C0);
        func_L00_00323F28(origin, origin, 30.0f, ((WeatherHero *)(D_L01_001B94C0 - 0x140))->rotation[2], ((WeatherHero *)(D_L01_001B94C0 - 0x140))->rotation[1]);
        origin[2] = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] + D_L01_001AF630;
        for (i = 0; i < count; i++) {
            float offset;
            *(WeatherQuad *)(pos) = *(WeatherQuad *)(origin);
            offset = func_00283180(func_002A7878(0.0f, 6.2831854820251465f));
            offset *= func_002A7878(0.0f, 30.0f);
            pos[0] += offset;
            offset = func_00283198(func_002A7878(0.0f, 6.2831854820251465f));
            offset *= func_002A7878(0.0f, 30.0f);
            pos[1] += offset;
            func_002B0668(pos);
        }
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(D_L01_001B94C0);
        func_L00_00323F28(origin, origin, 4.0f, ((WeatherHero *)(D_L01_001B94C0 - 0x140))->rotation[2], ((WeatherHero *)(D_L01_001B94C0 - 0x140))->rotation[1]);
        origin[2] = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] + D_L01_001AF630;
        for (i = 0; i < count; i++) {
            float offset;
            *(WeatherQuad *)(pos) = *(WeatherQuad *)(origin);
            offset = func_00283180(func_002A7878(0.0f, 6.2831854820251465f));
            offset *= func_002A7878(0.0f, 8.0f);
            pos[0] += offset;
            offset = func_00283198(func_002A7878(0.0f, 6.2831854820251465f));
            offset *= func_002A7878(0.0f, 8.0f);
            pos[1] += offset;
            func_002B0668(pos);
        }
    }
finish:
    p += 0x30;
    *(WeatherQuad *)(p) = *(WeatherQuad *)(D_L01_001B94C0);
}

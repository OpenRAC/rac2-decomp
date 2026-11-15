#include "names.h"
/* func_PAL_L01_0039C970, the PAL copy of func_L01_00399510: the same C, where 0.01666666753590107f
   becomes 0.020000001f; 0.033333335070610046f becomes 0.040000003f; func_L01_003993C8 becomes
   func_PAL_L01_0039C7E8; func_L01_00331CA0 becomes func_PAL_L01_00333E88. */
#include "common.h"
typedef unsigned int WeatherQuad __attribute__((mode(TI)));
typedef struct {
    char pad[0x140];
    float position[4];
    float rotation[4];
} WeatherHero;

extern int g_current_map_index[] __attribute__((sda));
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
extern int moby_is_in_selected_zone(void *);
extern void func_PAL_L01_0039C7E8(int);
extern int vec_fast_helper_b(void *);
extern void FastVecSub(void *, void *, void *);
extern float vec_length_xy(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void vec_add_offset(void *, void *, float, float, float);
extern float coll_get_heightmap_height(void *);
extern void part_spawn_ground_impact_effect(void *);
extern void SpawnSpanParticle(void *, int, float, void *);
extern void func_PAL_L01_00333E88(void *, int, void *, float);


void func_PAL_L01_0039C970(char *m)
{
    float pos[4], delta[4], origin[4], velocity[4], velocity2[4];
    int special, extras, count, i, level;
    float falloff, speed, minimum, jitter;
    char *p;

    if (!moby_is_in_selected_zone(m + 0x10))
        return;
    D_L01_001A94C0 = D_L01_001C9A40;
    level = g_current_map_index[0];
    switch (level) {
    case 12: case 19: case 512: special = 1; break;
    default: special = 0; break;
    }
    switch (special) {
    case 1:
        falloff = 0.2f; speed = 5.0f; minimum = 0.5f;
        jitter = 0.020000001f; extras = 0;
        break;
    case 0:
    default:
        falloff = 0.15f; extras = 1; speed = 18.0f;
        minimum = D_L01_001AF62C; jitter = 0.040000003f;
        break;
    }
    if (D_L01_001AF640 >= 0.0f)
        minimum = D_L01_001AF640;
    p = *(char **)(m + 0x68);
    switch (*(unsigned char *)(m + 0x20)) {
    case 0:
        *(unsigned char *)(m + 0x20) = 2;
        *(unsigned char *)(m + 0x30) = 255;
        func_PAL_L01_0039C7E8(special);
        goto finish;
    case 2: {
        float x, y, scale, z, top;
        if (vec_fast_helper_b(D_L01_001B2F00))
            func_PAL_L01_0039C7E8(special);
        FastVecSub(delta, D_L01_001B94C0, p + 0x30);
        D_L01_001B27A0.vec = *(WeatherQuad *)(delta);
        x = D_L01_001B2090[0] - D_L01_001AF64C;
        y = D_L01_001B208C[0] - D_L01_001AF650;
        count = D_L01_001B2F04;
        if (x < 0.0f) x = 0.0f;
        if (y < 0.0f) y = 0.0f;
        x /= 1.0f - D_L01_001AF64C;
        y /= 1.0f - D_L01_001AF650;
        z = IntToFloat(count);
        scale = 1.0f - (x > y ? x : y) * D_L01_001AF654;
        count = FloatToInt(z * scale);
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(((WeatherHero *)(D_L01_001B94C0 - 0x140))->position);
        vec_add_offset(origin, origin, 16.0f, ((WeatherHero *)(D_L01_001B94C0 - 0x140))->rotation[2], ((WeatherHero *)(D_L01_001B94C0 - 0x140))->rotation[1]);
        origin[2] = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] + D_L01_001AF630;
        for (i = 0; i < count; i++) {
            float offset, length, z, floor, scale;
            *(WeatherQuad *)(pos) = *(WeatherQuad *)(origin);
            offset = math_fast_sin_or_cos_a(math_random_float_range(0.0f, 6.2831854820251465f));
            offset *= math_random_float_range(0.0f, D_L01_001AF634);
            pos[0] += offset;
            offset = math_fast_sin_or_cos_b(math_random_float_range(0.0f, 6.2831854820251465f));
            offset *= math_random_float_range(0.0f, D_L01_001AF634);
            pos[1] += offset;
            FastVecSub(velocity, pos, ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position);
            length = vec_length_xy(velocity);
            if (length <= 8.0f) {
                velocity2[0] = D_L01_001B2EF0[0] + math_random_float_range(-jitter, jitter);
                velocity2[1] = D_L01_001B2EF4[0] + math_random_float_range(-jitter, jitter);
                velocity2[2] = -(speed * 0.020000001f);
                velocity2[3] = 0.0f;
            } else {
                scale = (length - 8.0f) * falloff;
                scale = speed - scale;
                if (scale < minimum) scale = minimum;
                velocity2[0] = D_L01_001B2EF0[0] + math_random_float_range(-jitter, jitter);
                velocity2[1] = D_L01_001B2EF4[0] + math_random_float_range(-jitter, jitter);
                velocity2[2] = -(scale * 0.020000001f);
                velocity2[3] = 0.0f;
            }
            D_L01_001B27B0 = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] - D_L01_001AF648;
            z = coll_get_heightmap_height(pos);
            top = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] + D_L01_001AF630;
            if (z < top) {
                int flag = 0;
                floor = z < D_L01_001B27B0 ? D_L01_001B27B0 : z;
                if (length > 8.0f) flag = D_L01_001AF644;
                if (special == 0) SpawnSpanParticle(pos, flag, floor, velocity2);
                if (special == 1) func_PAL_L01_00333E88(pos, flag, velocity2, floor);
            }
        }
        count = (int)((float)count * 1.4f);
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(((WeatherHero *)(D_L01_001B94C0 - 0x140))->position);
        origin[2] = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] + D_L01_001AF630;
        for (i = 0; i < count; i++) {
            float offset, z, floor;
            velocity[0] = D_L01_001B2EF0[0] + math_random_float_range(-jitter, jitter);
            velocity[1] = D_L01_001B2EF4[0] + math_random_float_range(-jitter, jitter);
            velocity[2] = -(speed * 0.020000001f);
            velocity[3] = 0.0f;
            *(WeatherQuad *)(pos) = *(WeatherQuad *)(origin);
            offset = math_fast_sin_or_cos_a(math_random_float_range(0.0f, 6.2831854820251465f));
            offset *= math_random_float_range(0.0f, 8.0f);
            pos[0] += offset;
            offset = math_fast_sin_or_cos_b(math_random_float_range(0.0f, 6.2831854820251465f));
            offset *= math_random_float_range(0.0f, 8.0f);
            pos[1] += offset;
            D_L01_001B27B0 = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] - D_L01_001AF648;
            z = coll_get_heightmap_height(pos);
            top = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] + D_L01_001AF630;
            if (z < top) {
                floor = z < D_L01_001B27B0 ? D_L01_001B27B0 : z;
                if (special == 0) SpawnSpanParticle(pos, 0, floor, velocity);
                if (special == 1) func_PAL_L01_00333E88(pos, 0, velocity, floor);
            }
        }
        break;
    }
    default:
        goto finish;
    }
    if (extras) {
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(D_L01_001B94C0);
        vec_add_offset(origin, origin, 30.0f, ((WeatherHero *)(D_L01_001B94C0 - 0x140))->rotation[2], ((WeatherHero *)(D_L01_001B94C0 - 0x140))->rotation[1]);
        origin[2] = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] + D_L01_001AF630;
        for (i = 0; i < count; i++) {
            float offset;
            *(WeatherQuad *)(pos) = *(WeatherQuad *)(origin);
            offset = math_fast_sin_or_cos_a(math_random_float_range(0.0f, 6.2831854820251465f));
            offset *= math_random_float_range(0.0f, 30.0f);
            pos[0] += offset;
            offset = math_fast_sin_or_cos_b(math_random_float_range(0.0f, 6.2831854820251465f));
            offset *= math_random_float_range(0.0f, 30.0f);
            pos[1] += offset;
            part_spawn_ground_impact_effect(pos);
        }
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(D_L01_001B94C0);
        vec_add_offset(origin, origin, 4.0f, ((WeatherHero *)(D_L01_001B94C0 - 0x140))->rotation[2], ((WeatherHero *)(D_L01_001B94C0 - 0x140))->rotation[1]);
        origin[2] = ((WeatherHero *)(D_L01_001B94C0 - 0x140))->position[2] + D_L01_001AF630;
        for (i = 0; i < count; i++) {
            float offset;
            *(WeatherQuad *)(pos) = *(WeatherQuad *)(origin);
            offset = math_fast_sin_or_cos_a(math_random_float_range(0.0f, 6.2831854820251465f));
            offset *= math_random_float_range(0.0f, 8.0f);
            pos[0] += offset;
            offset = math_fast_sin_or_cos_b(math_random_float_range(0.0f, 6.2831854820251465f));
            offset *= math_random_float_range(0.0f, 8.0f);
            pos[1] += offset;
            part_spawn_ground_impact_effect(pos);
        }
    }
finish:
    p += 0x30;
    *(WeatherQuad *)(p) = *(WeatherQuad *)(D_L01_001B94C0);
}

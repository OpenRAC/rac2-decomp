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
extern int g_weather_saved_word NOT_SDA;
extern int g_weather_hero_ptr SDATA(D_L01_001A94C0);
extern float g_weather_min_value SDATA(D_L01_001AF62C);
extern float g_weather_height_offset SDATA(D_L01_001AF630);
extern float g_weather_offset_range SDATA(D_L01_001AF634);
extern float g_weather_min_override SDATA(D_L01_001AF640);
extern int g_weather_flag_value SDATA(D_L01_001AF644);
extern float g_weather_floor_offset SDATA(D_L01_001AF648);
extern float g_weather_fade_start SDATA(D_L01_001AF64C);
extern float g_weather_blend_start SDATA(D_L01_001AF650);
extern float g_weather_scale_factor SDATA(D_L01_001AF654);
extern float g_falling_part_floor_height SDATA(D_L01_001B27B0);
extern float g_wind_change_delay[] __attribute__((sda));
extern int g_wind_particle_count;
extern float g_wind_x[] __attribute__((sda));
extern float g_wind_y[] __attribute__((sda));
extern float g_breakable_alpha_check_b[] __attribute__((sda));
extern float g_breakable_alpha_check_a[] __attribute__((sda));
extern char g_level_origin_vec[];
typedef struct { WeatherQuad vec; } WeatherWind;
extern WeatherWind g_falling_l01_part_gravity __attribute__((sda));
extern int moby_is_in_selected_zone(void *);
extern void part_pick_random_wind_and_count_pal(int);
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
extern void part_l01_spawn_burst_2_pal(void *, int, void *, float);


/* Spawns the falling rain or snow particles around the hero and the ground impacts, and follows the wind (PAL: 50 Hz speeds). */
void update_weather_particles_pal(char *moby)
{
    float pos[4], delta[4], origin[4], velocity[4], velocity2[4];
    int special, extras, count, i, level;
    float falloff, speed, minimum, jitter;
    char *vars;

    if (!moby_is_in_selected_zone(moby + 0x10))
        return;
    g_weather_hero_ptr = g_weather_saved_word;
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
        minimum = g_weather_min_value; jitter = 0.040000003f;
        break;
    }
    if (g_weather_min_override >= 0.0f)
        minimum = g_weather_min_override;
    vars = *(char **)(moby + 0x68);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned char *)(moby + 0x20) = 2;
        *(unsigned char *)(moby + 0x30) = 255;
        part_pick_random_wind_and_count_pal(special);
        goto finish;
    case 2: {
        float x, y, scale, z, top;
        if (vec_fast_helper_b(g_wind_change_delay))
            part_pick_random_wind_and_count_pal(special);
        FastVecSub(delta, g_level_origin_vec, vars + 0x30);
        g_falling_l01_part_gravity.vec = *(WeatherQuad *)(delta);
        x = g_breakable_alpha_check_a[0] - g_weather_fade_start;
        y = g_breakable_alpha_check_b[0] - g_weather_blend_start;
        count = g_wind_particle_count;
        if (x < 0.0f) x = 0.0f;
        if (y < 0.0f) y = 0.0f;
        x /= 1.0f - g_weather_fade_start;
        y /= 1.0f - g_weather_blend_start;
        z = IntToFloat(count);
        scale = 1.0f - (x > y ? x : y) * g_weather_scale_factor;
        count = FloatToInt(z * scale);
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(((WeatherHero *)(g_level_origin_vec - 0x140))->position);
        vec_add_offset(origin, origin, 16.0f, ((WeatherHero *)(g_level_origin_vec - 0x140))->rotation[2], ((WeatherHero *)(g_level_origin_vec - 0x140))->rotation[1]);
        origin[2] = ((WeatherHero *)(g_level_origin_vec - 0x140))->position[2] + g_weather_height_offset;
        for (i = 0; i < count; i++) {
            float offset, length, z, floor, scale;
            *(WeatherQuad *)(pos) = *(WeatherQuad *)(origin);
            offset = math_fast_sin_or_cos_a(math_random_float_range(0.0f, 6.2831854820251465f));
            offset *= math_random_float_range(0.0f, g_weather_offset_range);
            pos[0] += offset;
            offset = math_fast_sin_or_cos_b(math_random_float_range(0.0f, 6.2831854820251465f));
            offset *= math_random_float_range(0.0f, g_weather_offset_range);
            pos[1] += offset;
            FastVecSub(velocity, pos, ((WeatherHero *)(g_level_origin_vec - 0x140))->position);
            length = vec_length_xy(velocity);
            if (length <= 8.0f) {
                velocity2[0] = g_wind_x[0] + math_random_float_range(-jitter, jitter);
                velocity2[1] = g_wind_y[0] + math_random_float_range(-jitter, jitter);
                velocity2[2] = -(speed * 0.020000001f);
                velocity2[3] = 0.0f;
            } else {
                scale = (length - 8.0f) * falloff;
                scale = speed - scale;
                if (scale < minimum) scale = minimum;
                velocity2[0] = g_wind_x[0] + math_random_float_range(-jitter, jitter);
                velocity2[1] = g_wind_y[0] + math_random_float_range(-jitter, jitter);
                velocity2[2] = -(scale * 0.020000001f);
                velocity2[3] = 0.0f;
            }
            g_falling_part_floor_height = ((WeatherHero *)(g_level_origin_vec - 0x140))->position[2] - g_weather_floor_offset;
            z = coll_get_heightmap_height(pos);
            top = ((WeatherHero *)(g_level_origin_vec - 0x140))->position[2] + g_weather_height_offset;
            if (z < top) {
                int flag = 0;
                floor = z < g_falling_part_floor_height ? g_falling_part_floor_height : z;
                if (length > 8.0f) flag = g_weather_flag_value;
                if (special == 0) SpawnSpanParticle(pos, flag, floor, velocity2);
                if (special == 1) part_l01_spawn_burst_2_pal(pos, flag, velocity2, floor);
            }
        }
        count = (int)((float)count * 1.4f);
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(((WeatherHero *)(g_level_origin_vec - 0x140))->position);
        origin[2] = ((WeatherHero *)(g_level_origin_vec - 0x140))->position[2] + g_weather_height_offset;
        for (i = 0; i < count; i++) {
            float offset, z, floor;
            velocity[0] = g_wind_x[0] + math_random_float_range(-jitter, jitter);
            velocity[1] = g_wind_y[0] + math_random_float_range(-jitter, jitter);
            velocity[2] = -(speed * 0.020000001f);
            velocity[3] = 0.0f;
            *(WeatherQuad *)(pos) = *(WeatherQuad *)(origin);
            offset = math_fast_sin_or_cos_a(math_random_float_range(0.0f, 6.2831854820251465f));
            offset *= math_random_float_range(0.0f, 8.0f);
            pos[0] += offset;
            offset = math_fast_sin_or_cos_b(math_random_float_range(0.0f, 6.2831854820251465f));
            offset *= math_random_float_range(0.0f, 8.0f);
            pos[1] += offset;
            g_falling_part_floor_height = ((WeatherHero *)(g_level_origin_vec - 0x140))->position[2] - g_weather_floor_offset;
            z = coll_get_heightmap_height(pos);
            top = ((WeatherHero *)(g_level_origin_vec - 0x140))->position[2] + g_weather_height_offset;
            if (z < top) {
                floor = z < g_falling_part_floor_height ? g_falling_part_floor_height : z;
                if (special == 0) SpawnSpanParticle(pos, 0, floor, velocity);
                if (special == 1) part_l01_spawn_burst_2_pal(pos, 0, velocity, floor);
            }
        }
        break;
    }
    default:
        goto finish;
    }
    if (extras) {
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(g_level_origin_vec);
        vec_add_offset(origin, origin, 30.0f, ((WeatherHero *)(g_level_origin_vec - 0x140))->rotation[2], ((WeatherHero *)(g_level_origin_vec - 0x140))->rotation[1]);
        origin[2] = ((WeatherHero *)(g_level_origin_vec - 0x140))->position[2] + g_weather_height_offset;
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
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(g_level_origin_vec);
        vec_add_offset(origin, origin, 4.0f, ((WeatherHero *)(g_level_origin_vec - 0x140))->rotation[2], ((WeatherHero *)(g_level_origin_vec - 0x140))->rotation[1]);
        origin[2] = ((WeatherHero *)(g_level_origin_vec - 0x140))->position[2] + g_weather_height_offset;
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
    vars += 0x30;
    *(WeatherQuad *)(vars) = *(WeatherQuad *)(g_level_origin_vec);
}

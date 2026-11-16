#include "include_asm.h"

#include "common.h"
extern float math_random_angle(void);
extern float math_random_float_range(float angle, float speed);
extern float math_fast_sin_or_cos_a(float angle);
extern float math_fast_sin_or_cos_b(float angle);
extern int math_random_int_range(int angle, int speed);
extern int math_random_int_below(int angle);
extern void *part_spawn_spark_2_pal(char *p, float *q, int angle, int speed);

/* func_00329768 uses small data in 00329768-g8.c. */



/* Per frame: scales the value one helper returns by the factor another helper returns, stores both scaled samples and a third sample into a three-float record, and hands the record to a setter with two selector results. */
void part_emit_spark_burst_pal(char *self)
{
    float velocity[3];
    float angle;
    float speed;
    int i;
    int life;
    int kind;

    for (i = 47; i >= 0; i--) {
        angle = math_random_angle();
        speed = math_random_float_range(0.0f, 0.060000002f);
        velocity[0] = math_fast_sin_or_cos_a(angle) * speed;
        velocity[1] = math_fast_sin_or_cos_b(angle) * speed;
        velocity[2] = math_random_float_range(0.060000002f, 0.13000001f);
        life = math_random_int_range(90, 120);
        kind = math_random_int_below(2);
        part_spawn_spark_2_pal(self + 16, velocity, kind, life);
    }
}


extern unsigned char *g_hit_result[];
extern char g_music_state[];
extern int snd_resume_music_stream(void);
extern void moby_set_byte_on_group(int, int);
extern void STUB_printf(const char *, ...);
extern char g_str_hero_under_falling_debug[];
extern int g_surface_height_tiles[] __attribute__((sda));
extern int g_surface_box_count[] __attribute__((sda));
extern int SampleSurfaceHeightMap(float *, float *, float, float, float);
extern void RippleDisturb(int, int, int, float, float, float, float);
extern int stub_empty_30(void);

/* Checks whether a falling chunk is over the hero: the chunk lands on the hero, ripples the
   water, counts the hit and may resume the music (PAL: same as USA v1.01). */
void hero_check_under_falling_object_pal(char *self)
{
    unsigned char *target = g_hit_result[0];
    char *state = *(char **)(self + 0x68);
    unsigned char *object;
    unsigned char *obj_state;
    char *object_vars;
    float unused_hit[4];
    float surface_point[4];
    char *music;
    int mode;

    if (target == 0) {
        if (*(int *)(state + 0x38) != 2)
            return;
    }
    mode = *(int *)(state + 0x38);
    object = target;
    if (mode == 2)
        object = *(unsigned char **)(state + 0x48);
    if (*(short *)(*(char **)(object + 0x24) + 0x46) == 18) {
        obj_state = *(unsigned char **)(object + 0x68);
        if (obj_state != 0) {
            if (*(short *)(obj_state + 0x16) == 0) {
                *(int *)&surface_point[0] = 0;
                if (mode != 2)
                    SampleSurfaceHeightMap(surface_point, unused_hit, *(float *)(self + 0x10), *(float *)(self + 0x14), *(float *)(self + 0x18));
                else
                    SampleSurfaceHeightMap(surface_point, unused_hit, *(float *)(state + 0x20), *(float *)(state + 0x24), *(float *)(state + 0x28));
                object_vars = *(char **)(object + 0x68);
                if (*(float *)(self + 0x18) > surface_point[0] && *(float *)(object_vars + 0xC) == 0.0f) {
                    *(unsigned char **)(state + 0x48) = object;
                    *(int *)(state + 0x38) = 2;
                    return;
                }
                if (obj_state[0x14] == 0) {
                    RippleDisturb(g_surface_height_tiles[0], g_surface_box_count[0], 1, *(float *)(self + 0x10), *(float *)(self + 0x14), 0.5f, -0.03f);
                    if (stub_empty_30() == 0) {
                        object[0xBC] += 1;
                        if (object[0xBC] >= 25) {
                            music = g_music_state;
                            if (*(short *)(music + 0x72) == 3 && *(short *)(music + 0x6C) < 6000)
                                snd_resume_music_stream();
                        }
                        if (object[0x21] != 255)
                            moby_set_byte_on_group(object[0x21], object[0xBC]);
                    }
                }
                *(int *)(state + 0x44) = 0;
            } else {
                *(int *)(state + 0x44) = 1;
            }
        } else {
            STUB_printf(g_str_hero_under_falling_debug, *(short *)(object + 0xAA));
        }
        *(int *)(state + 0x38) = 1;
    } else {
        *(int *)(state + 0x38) = 0;
    }
}


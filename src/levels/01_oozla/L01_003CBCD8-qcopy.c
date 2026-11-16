#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"

/* Needs the quadword copy (-frac2-qcopy with the barrier) and -fno-gcse. The table base is an `sda` incomplete array so the assembler expands it as one `la` in the loop instead of cc1 hoisting the %hi out of it. */

typedef int OozlaQuad __attribute__((mode(TI)));

extern int g_oozla_intro_stage __attribute__((sda));
extern char g_str_swamp_splash[];
extern void func_002A6CF0(char *, int, int);
extern float level_get_water_height(void);
extern void *moby_spawn_scaled_effect(float *, float);
extern void set_moby_color(void *, int, int, int);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern void *part_spawn_drifting(void *, void *, int, float, float);
extern void *part_spawn_spark_2(void *, void *, int, int);
extern float g_water_l01_height[] __attribute__((sda));



/* Makes a water splash with bubbles and drops where the swamp monster hits the water. It will not repeat for a few frames. */
void swamp_monster_spawn_splash(char *object, int bubbles, int drops, int splash)
{
    float velocity[4], position[4];
    float height, angle, radius, size;
    void *effect;
    int i, j, type, lifetime;
    int *timer = 0;
    int dropCount = drops;
    int currentFrame;
    if (*(short *)(object + 0xAA) == MOBY_CLASS_SWAMP_MONSTER_I_ARM) {
        timer = (int *)(*(char **)(object + 0x68) + 0xF4);
    } else if (*(short *)(object + 0xAA) == MOBY_CLASS_SWAMP_MONSTER_I_EYE) {
        timer = (int *)(*(char **)(object + 0x68) + 0xC8);
    }
    if (timer == 0)
        func_002A6CF0(g_str_swamp_splash, *(short *)(object + 0xAA), *(short *)(object + 0xB2));
    currentFrame = g_oozla_intro_stage;
    if (currentFrame - *timer < 11)
        return;
    height = level_get_water_height();
    if (splash) {
        *(OozlaQuad *)velocity = *(OozlaQuad *)(object + 0x10);
        velocity[2] = height;
        effect = moby_spawn_scaled_effect(velocity, 4.0f);
        if (effect)
            set_moby_color(effect, 0x60, 0x50, 0);
    }
    if (bubbles > 0) {
      i = bubbles;
      do {
        --i;
        velocity[0] = *(float *)(object + 0x10) + math_random_float_range(-0.3f, 0.3f);
        velocity[1] = *(float *)(object + 0x14) + math_random_float_range(-0.3f, 0.3f);
        velocity[2] = height;
        size = math_random_float_range(0.5f, 0.9f);
        type = ((math_random_int_below(6) + 20) << 24) | 0x5060;
        part_spawn_drifting(velocity, g_water_l01_height, type, size, 5250.0f);
      } while (i != 0);
    }
    if (dropCount > 0) {
      j = dropCount;
      do {
        --j;
        angle = math_random_angle();
        radius = math_random_float_range(0.0f, 0.0500000045f);
        velocity[0] = math_fast_sin_or_cos_a(angle) * radius;
        velocity[1] = math_fast_sin_or_cos_b(angle) * radius;
        velocity[2] = math_random_float_range(0.0500000045f, 0.13333334f);
        position[0] = *(float *)(object + 0x10) + velocity[0] * 8.0f;
        position[1] = *(float *)(object + 0x14) + velocity[0] * 8.0f;
        position[2] = height - math_random_float_range(0.0f, 0.2f);
        type = math_random_int_below(2);
        lifetime = math_random_int_range(90, 120);
        part_spawn_spark_2(position, velocity, type, lifetime);
      } while (j != 0);
    }
    *timer = g_oozla_intro_stage;
}

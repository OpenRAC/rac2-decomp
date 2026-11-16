#include "names.h"
/* func_PAL_L04_0041A790, the PAL copy of func_L04_00416018: the same C. */

typedef unsigned char u8;
typedef short s16;

/* Collects the racers, sorts their recorded times, and records each rank and
   the next racer in the ordered list. */
typedef unsigned int u32;

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

/* Eight-sample trail records; the retail loop visits 140 entries of stride 0x150. */
typedef struct Trail416018 {
    float points[8][4];
    float velocities[8][4];
    float origin[4];
    float *offset, *impulse;
    short ages[8], landed[8];
    int count, lifetime;
    u32 colour;
    int active;
    char *owner;
    int tail;
} Trail416018;
extern Trail416018 g_racer_trail_pool[] __attribute__((sda));
extern unsigned char g_hero_state[];
extern int g_race_bike_mode __attribute__((sda));
extern void *g_race_controller __attribute__((sda));
extern void FastVecAdd(float *, float *, float *);
extern void FastVecScale(float *, float *, float);
extern void matrix_mul_vec3(float *, float *, char *);
extern int math_fast_float_d(int *);
extern int FastTweenColor(int, int, float);
extern void trail_update_active_entries(void *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
/* Moves the trails left behind by the racers: drops them to the ground, ages them, adds new points and fades finished ones away (PAL). */
void racer_update_trails_pal(void)
{
    float local[4] __attribute__((aligned(16)));
    float floor_z, scale;
    Trail416018 *trail;
    float *point, *velocity;
    float gravity;
    short *age;
    int i, j, count;
    char *owner;
    for (i = 0; i < 140; i++) {
        trail = &g_racer_trail_pool[i];
        if (!trail->active)
            continue;
        owner = trail->owner;
        count = trail->count;
        if (*(short *)(owner + 0xaa) == 0xbbc) {
            /* Through a pointer, as retail keeps the hero base in a register. */
            unsigned char *hero = g_hero_state;
            floor_z = *(float *)(hero + 0x318) + 0.1f;
        } else {
            floor_z = *(float *)(owner + 0x18) - 0.25f;
        }
        for (j = 0; j < count; j++) {
            float width_step = 0.0009f;
            gravity = 0.0028000001f;
            point = trail->points[j];
            age = &trail->ages[j];
            velocity = trail->velocities[j];
            /* velocities[j][2], addressed from the point as retail does. */
            if ((*age)++ > 8)
                ((float *)((char *)point + 0x80))[2] -= gravity;
            scale = 1.0f;
            scale -= (*age - 4) * 0.01f;
            FastVecAdd(point, point, velocity);
            FastVecScale(local, trail->impulse, scale);
            FastVecAdd(point, point, local);
            if (point[2] < floor_z) {
                point[2] = floor_z;
                trail->landed[j] = 1;
            }
            point[3] = trail->ages[0] * width_step + 0.01f + *age * width_step;
        }
        if (count < 8 &&
            ((*(short *)(trail->owner + 0xaa) == 0xbbc && g_race_bike_mode) ||
             (*(short *)(trail->owner + 0xaa) == 0xb2d && /* moby class 2861 */
              *(int *)(*(char **)(trail->owner + 0x68) + 0x244)))) {
            if (trail->ages[count - 1] < 3)
                continue;
            point = trail->points[count];
            matrix_mul_vec3(local, trail->origin, trail->owner + 0xc0);
            FastVecAdd(point, trail->offset, local);
            FastVecAdd(point, point, trail->impulse);
            qcopy(trail->velocities[count], local);
            point[3] = 0.005f;
            trail->ages[count] = 0;
            trail->count++;
        } else if (trail->landed[count - 1] == 1) {
            if (math_fast_float_d(&trail->lifetime)) {
                trail->active = 0;
            } else {
                trail->colour = FastTweenColor(0x00858585, 0x80858585,
                    trail->lifetime * 0.04f);
            }
        }
    }
    gfx_add_draw_callback_first(trail_update_active_entries, g_race_controller);
}

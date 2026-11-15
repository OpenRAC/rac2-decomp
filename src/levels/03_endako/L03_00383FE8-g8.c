#include "common.h"
extern void moby_set_state(void *, int, int);
extern char *part_find_owned_effect_slot(void *, int, int);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern void *moby_spawn_bolt_pickup(void *, void *, void *, int, int, int);
extern int D_L03_001AEC30 __attribute__((sda));
extern char D_L03_001AEC10[8] __attribute__((sda)), D_L03_001AEC08[8] __attribute__((sda)), D_L03_001AEC00[8] __attribute__((sda));
extern void part_explode_object_into_pieces(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern char *SpawnExplosion(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void moby_mark_spawned(void *);
extern int flag_set_first_pending(void *);
extern void timer_start_countdown(int, float);
extern float D_L03_001B2460;
extern char *CreateMoby(int);
extern char D_L03_001B9980[];
extern int D_L03_001A8FB4, D_L03_001A8FB0;
/* Updates a hit-reactive object. It waits to be struck, bursts into sparks, and when the Dynamo hits it, it drops a pickup item and shows a message. */
void hit_spark_update(char *moby)
{
    float pos[4], vel[4];
    int i;
    char *spawned;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned short *)(moby + 0x34) |= 0x1000;
        moby_set_state(moby, 1, -1);
        break;
    case 1: {
        char *hit;
        hit = part_find_owned_effect_slot(moby, 0x4010000, 0);
        if (hit) {
            hit = *(char **)(hit + 0x20);
            if (hit && *(short *)(hit + 0xAA) == MOBY_CLASS_DYNAMO)
                moby_set_state(moby, 3, -1);
            else moby_set_state(moby, 2, -1);
        }
        *(unsigned char *)(moby + 0xA8) = 0xFF;
        break;
    }
    case 2: {
        char *position = moby + 0x10;
        if (!D_L03_001AEC30) {
            D_L03_001AEC30 = 1;
            qcopy(pos, position);
            pos[2] += 0.5f;
            i = 9;
            do {
                float angle, speed;
                i--;
                angle = math_random_angle();
                speed = math_random_float_range(0, 1) * (1.0f/60.0f);
                vel[0] = math_fast_sin_or_cos_a(angle) * speed;
                vel[1] = math_fast_sin_or_cos_b(angle) * speed;
                vel[2] = 0;
                vel[2] = math_random_float_range(5, 10) * (1.0f/60.0f);
                moby_spawn_bolt_pickup(moby, pos, vel, 0, 100, 0);
            } while (i >= 0);
        }
        part_explode_object_into_pieces(moby, D_L03_001AEC10, D_L03_001AEC08, D_L03_001AEC00, 65535, 0, -1, 6, 65535, 255, 0);
        SpawnExplosion(position, 0, 25, 20, 20, 20, 45, 1, 1, 1, 0, 0, 0.5f, 20);
        moby_mark_spawned(moby);
        break;
    }
    case 3:
        if (flag_set_first_pending(moby)) timer_start_countdown(1, 15);
        if (D_L03_001B2460 >= 1) {
            spawned = CreateMoby(0x1335);
            if (spawned) {
                qcopy(spawned + 0x10, D_L03_001B9980);
                *(unsigned char *)(spawned + 0x30) = 255;
            }
            D_L03_001A8FB4 = 2;
            D_L03_001A8FB0 = 15;
            moby_set_state(moby, 1, -1);
        } else {
            unsigned int count = *(unsigned short *)(moby + 0x96);
            unsigned int old_count = count++;
            *(unsigned short *)(moby + 0x96) = count;
            if (old_count >= 61) moby_set_state(moby, 1, -1);
        }
        break;
    }
}

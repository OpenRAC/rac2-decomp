#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, int, int);
extern char *part_find_owned_effect_slot(void *, int, int);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern void *moby_spawn_bolt_pickup_pal(void *, void *, void *, int, int, int);
extern int g_hit_spark_init_flag __attribute__((sda));
extern char g_hit_spark_piece_params_c[8] __attribute__((sda)), g_hit_spark_piece_params_b[8] __attribute__((sda)), g_hit_spark_piece_params_a[8] __attribute__((sda));
extern void part_explode_object_into_pieces_pal(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void moby_mark_spawned(void *);
extern int flag_set_first_pending(void *);
extern void timer_start_countdown(int, float);
extern float g_hit_spark_threshold;
extern char *CreateMoby(int);
extern char g_camera_pose_buffer[];
extern int g_hero_allowed_mode, g_hit_spark_timer;

/* Updates the hit spark: waits to be struck, then throws sparks, pieces and an explosion, or starts a countdown and spawns a camera object. (PAL) */
void hit_spark_update_pal(char *moby)
{
    float pos[4], vel[4];
    int i;
    char *flash;
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
            if (hit && *(short *)(hit + 0xAA) == 0x825)
                moby_set_state(moby, 3, -1);
            else moby_set_state(moby, 2, -1);
        }
        *(unsigned char *)(moby + 0xA8) = 0xFF;
        break;
    }
    case 2: {
        char *position = moby + 0x10;
        if (!g_hit_spark_init_flag) {
            g_hit_spark_init_flag = 1;
            qcopy(pos, position);
            pos[2] += 0.5f;
            i = 9;
            do {
                float angle, speed;
                i--;
                angle = math_random_angle();
                speed = math_random_float_range(0, 1) * (0.020000001f);
                vel[0] = math_fast_sin_or_cos_a(angle) * speed;
                vel[1] = math_fast_sin_or_cos_b(angle) * speed;
                vel[2] = 0;
                vel[2] = math_random_float_range(5, 10) * (0.020000001f);
                moby_spawn_bolt_pickup_pal(moby, pos, vel, 0, 100, 0);
            } while (i >= 0);
        }
        part_explode_object_into_pieces_pal(moby, g_hit_spark_piece_params_c, g_hit_spark_piece_params_b, g_hit_spark_piece_params_a, 65535, 0, -1, 6, 65535, 255, 0);
        SpawnExplosion_pal(position, 0, 25, 20, 20, 20, 45, 1, 1, 1, 0, 0, 0.5f, 20);
        moby_mark_spawned(moby);
        break;
    }
    case 3:
        if (flag_set_first_pending(moby)) timer_start_countdown(1, 15);
        if (g_hit_spark_threshold >= 1) {
            flash = CreateMoby(0x1335);
            if (flash) {
                qcopy(flash + 0x10, g_camera_pose_buffer);
                *(unsigned char *)(flash + 0x30) = 255;
            }
            g_hero_allowed_mode = 2;
            g_hit_spark_timer = 12;
            moby_set_state(moby, 1, -1);
        } else {
            unsigned int count = *(unsigned short *)(moby + 0x96);
            unsigned int old = count++;
            *(unsigned short *)(moby + 0x96) = count;
            if (old >= 51) moby_set_state(moby, 1, -1);
        }
        break;
    }
}

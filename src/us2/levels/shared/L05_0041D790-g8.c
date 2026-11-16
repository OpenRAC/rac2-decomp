#include "include_asm.h"

#include "common.h"
typedef struct { int bolts; int counter; u8 suffix[0x38]; } PlayerStatBlock;
extern PlayerStatBlock g_player_bolts __attribute__((sda));
extern int g_homing_pickup_target __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern unsigned short g_map_flag_word __attribute__((nosda));
extern float fast_vec_dist(void *, void *);
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern float FastAddRotations(float, float);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void moby_mark_spawned(void *);
extern void glow_l05_ring_draw_2(char *);
extern int func_US2_00289840(int, int);
extern char *GetLocalizedString(int);
extern int level_l00_call_module_handler_with_arg_9_us2(int, int);

/* Flies the object at the cached class-0xFBF moby. On arrival it plays a sound, bumps the
   player-stat counter and deletes itself; until then it keeps turning. */
void UpdateHomingPickup_us2(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (g_homing_pickup_target != 0) {
        scale = fast_vec_dist((void *)(g_homing_pickup_target + 0x10), object + 0x10);

        if (g_current_map_index[0] == 0x14) {
            vec_spring_to_target(object + 0x10, (void *)(g_homing_pickup_target + 0x10), state + 0x40,
                         0.008888889104127884f, 0.0033333334140479565f, 1.0666667222976685f);
        } else if (scale < 60.0f) {
            float *p = *(float **)(object + 0x24);
            float v = p[9] * 0.02222222276031971f * scale;

            *(float *)(object + 0x2C) = v;
            {
                float cap = p[9] * 0.30000001192092896f;

                if (v < cap)
                    *(float *)(object + 0x2C) = cap;
            }
            vec_spring_to_target(object + 0x10, (void *)(g_homing_pickup_target + 0x10), state + 0x40,
                         0.0055555556900799274f, 0.0016666667070239782f, 0.5f);
        }
        if (scale < 0.5f) {
            if (g_player_bolts.counter == 0) {
                if (g_map_flag_word == 0 && g_current_map_index[0] == 0x19)
                    func_US2_00289840(0xA3B, 0x92);
            } else {
                level_l00_call_module_handler_with_arg_9_us2(GetLocalizedString(0x1282), -1);
            }
            snd_play_from_class_bank(0xC, 0, object, 0xFBF);
            g_player_bolts.counter = g_player_bolts.counter + 1;
            moby_mark_spawned(object);
            return;
        }
    }
    glow_l05_ring_draw_2(object);
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.03f);
    *(float *)(object + 0xF0) = FastAddRotations(*(float *)(object + 0xF0), 0.01f);
}

#include "common.h"

extern const float ref_L11_00445DF8_00 __attribute__((sda));
extern const s32 ref_L11_00445DF8_01 __attribute__((sda));
extern float ref_L11_00445DF8_02 __attribute__((sda));
extern float ref_L11_00445DF8_03 __attribute__((sda));
extern s32 ref_L11_00445DF8_04 __attribute__((sda));
extern s32 g_player_stats;
extern char g_music_state[];
extern char g_hero_state[];
extern s32 math_fast_float_d(void *);
extern s32 math_random_int_below(s32);
extern int arena_queue_voice_line(char *, int);

/* Collects the actions the Joba boss may use now and starts a random one after a random cooldown. */
void joba_boss_start_random_action(char *moby, s32 count_delta, float accum_delta, float level_value) {
    char *state = *(char **)(moby + 0x68);
    char *world = g_music_state;
    char *hero;
    char *hero2;
    s32 id23;
    s32 id24;
    s32 off;
    s32 candidates[12];
    s32 *list_ptr;
    s32 num_candidates;
    s32 j;
    s32 k;
    s32 counter;
    float accum;

    if (*(s32 *)(world + 0x68) != 0)
        return;
    if (*(s32 *)(world + 0x24) != -1)
        return;
    if (*(s32 *)(state + 0x190) != 0)
        return;
    num_candidates = 0;
    accum = *(float *)(state + 0x194) + accum_delta;
    counter = *(s32 *)(state + 0x198) + count_delta;
    *(s32 *)(state + 0x198) = counter;
    *(float *)(state + 0x194) = accum;
    if (ref_L11_00445DF8_00 < accum || ref_L11_00445DF8_01 < counter) {
        list_ptr = candidates;
        for (j = 0; j < 4; j++) {
            s32 id;

            id = j + 0x14;
            if (*(s16 *)(state + 0x2A0 + id * 2) == 0)
                list_ptr[num_candidates++] = id;
        }
        *(s32 *)(state + 0x198) = 0;
        *(s32 *)(state + 0x194) = 0;
    }
    if (math_fast_float_d(state + 0x1B0) != 0) {
        *(s32 *)(state + 0x198) = 0;
        *(s32 *)(state + 0x1B0) = 300;
        *(s32 *)(state + 0x194) = 0;
    }
    if (ref_L11_00445DF8_02 < level_value) {
        list_ptr = candidates;
        for (k = 0; k < 2; k++) {
            s32 id = k + 0x12;

            if (*(s16 *)(state + 0x2A0 + id * 2) == 0)
                list_ptr[num_candidates++] = id;
        }
    }
    hero = g_hero_state;
    if ((float)*(s32 *)(hero + 0x24CC) < (float)g_player_stats * ref_L11_00445DF8_03) {
        id23 = 0x18;
        if (*(s16 *)(state + 0x2D0) == 0)
            candidates[num_candidates++] = id23;
    }
    hero2 = g_hero_state;
    if (*(s32 *)(hero2 + 0x24CC) <= 0) {
        id24 = math_random_int_below(2) + 0x19;
        off = id24 * 2;
        if (*(s16 *)(state + off + 0x2A0) == 0)
            candidates[num_candidates++] = id24;
    }
    if (num_candidates != 0) {
        arena_queue_voice_line(moby, candidates[math_random_int_below(num_candidates)]);
        *(s32 *)(state + 0x190) = ref_L11_00445DF8_04 + math_random_int_below(ref_L11_00445DF8_04);
    }
}

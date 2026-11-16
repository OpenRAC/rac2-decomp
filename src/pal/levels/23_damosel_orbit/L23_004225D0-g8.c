#include "names.h"
/* func_PAL_L23_004225D0, the PAL copy of func_L23_0041D398: the same C, where
 * the timer limits take the 50 Hz scale and the release's own callees their names.
 * Level 23 encounter damage phases. The function reads $gp data (hence -G8)
 * and lives in a unit of its own, like its neighbours.
 * The effect phases keep their index, table base, slot and direction in
 * block locals: sched1 then keeps the slot address after the random call,
 * and local-alloc gives direction, slot and index $s0, $s1 and $s2.
 * The local holding 10 puts its load ahead of the 1 while the stores keep
 * their order, as in retail.
 * The byte at PlayerStats +0xFD is read at a nonzero offset: that is a tied
 * two-word macro load, so reorg leaves the reread at its join instead of
 * copying it into the two branch slots as a $gp load.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
/* Two five-part windows share this ten-pointer table. */
typedef struct { u8 prefix[0x358]; char *parts[10]; } PartState;
extern char *g_mothership_boss_moby __attribute__((sda));
extern int g_boss_phase_timer_base __attribute__((sda));
extern int g_boss_damage_phase_started __attribute__((sda));
extern char *g_mothership_moby __attribute__((sda));
extern float g_boss_debris_speed __attribute__((sda));
extern int g_boss_debris_countdown;
/* PlayerStats. */
extern u8 g_player_stats[] __attribute__((sda));
extern int game_is_either_mode_two(void);
extern void SetDeathBits_pal(char *, int, int);
extern void mothership_destroy_parts_pal(void);
extern void moby_set_flag_bit(unsigned char *, int);
extern void moby_mark_spawned(void *);
extern void *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern int PlayMobySound(int, int, char *);
extern void moby_transform_joint_point(char *, int, char *);
extern void FastVecScale(char *, char *, float);
extern float math_random_float_range(float, float);
extern void FastVecAdd(char *, char *, char *);
extern char *cam_moby_create_pal(char *, int, int, int, char *, char *, float *, int, float, float);
extern void moby_fade_out_update(u8 *);
extern int math_random_int_below(int);

/* Move through the encounter's damage phases, detaching pieces and spawning debris. */
void func_PAL_L23_004225D0(char *object) {
    struct { Quad velocity, matrix[4], random; } local;
    /* The encounter state becomes a cursor into its part table in each phase. */
    union { PartState *state; char **parts; } cursor;
    char *particle;
    unsigned short timer;
    float scale;
    cursor.state = *(PartState **)(g_mothership_boss_moby + 0x68);
    if (g_player_stats[0xFD]) {
        if (*(unsigned short *)(object + 0x96) > (((int)(g_boss_phase_timer_base + 60) * 5 + 2) / 6)) {
            SetDeathBits_pal(object, 0, 3);
            mothership_destroy_parts_pal();
            return;
        }
    } else {
        if (*(unsigned short *)(object + 0x96) > (((int)(g_boss_phase_timer_base + 200) * 5 + 2) / 6) && !game_is_either_mode_two()) {
            SetDeathBits_pal(object, 0, 3);
            mothership_destroy_parts_pal();
            return;
        }
        if (!g_player_stats[0xFD] && *(unsigned short *)(object + 0x96) > (((int)(g_boss_phase_timer_base + 60) * 5 + 2) / 6)) {
            char *entryState;
            if (!g_mothership_moby) return;
            entryState = *(char **)(g_mothership_moby + 0x68);
            entryState[13] = 1;
            entryState[8] = 0;
            moby_set_flag_bit((unsigned char *)g_mothership_moby, 1);
            g_mothership_moby = 0;
            return;
        }
    }
    if (g_boss_damage_phase_started) {
        int i;
        cursor.parts = cursor.state->parts + 5;
        for (i = 5; i < 10; i++, cursor.parts++) {
            if (!g_boss_debris_countdown) {
                moby_mark_spawned(*cursor.parts);
                *cursor.parts = 0;
                *(unsigned short *)(object + 0x34) |= 0x41;
                SpawnExplosion_pal(object + 16, 1, 135, 120, 120, 115, 125, 1, 6.5f, 20.0f, 1, 1, 1, 0);
                PlayMobySound(12, 0, object);
            } else if (*cursor.parts) {
                int debrisIndex = 10 - g_boss_debris_countdown;
                moby_transform_joint_point(object, i - 4, (char *)local.matrix);
                FastVecScale((char *)&local.velocity, (char *)&local.matrix[1], g_boss_debris_speed);
                scale = math_random_float_range(0.0f, g_boss_debris_speed * 0.5f);
                FastVecScale((char *)&local.random, object + 0xE0, scale);
                FastVecAdd((char *)&local.velocity, (char *)&local.velocity, (char *)&local.random);
                {
                    char *oldPart = *cursor.parts;
                    particle = cam_moby_create_pal(oldPart, 1, *(short *)(oldPart + 0xAA), debrisIndex, oldPart + 16, oldPart + 0xF0, (float *)&local.velocity, 255, 140.0f, 25.0f);
                    if (particle) *(void (**)(u8 *))(particle + 0x64) = moby_fade_out_update;
                }
            }
        }
        g_boss_debris_countdown--;
        return;
    }
    timer = *(unsigned short *)(object + 0x96);
    if ((((int)((g_boss_phase_timer_base << 1) / 3) * 5 + 2) / 6) < timer) {
        int i;
        cursor.parts = cursor.state->parts;
        SpawnExplosion_pal(object + 16, 1, 45, 30, 40, 25, 85, 1, 4.5f, 20.0f, 1, 1, 1, 0);
        PlayMobySound(11, 0, object);
        for (i = 4; i >= 0; i--, cursor.parts++) {
            char *replacement = cursor.parts[5];
            if (replacement) {
                char *old = *cursor.parts;
                if (!old) continue;
                qcopy(replacement + 0xC0, old + 0xC0);
                qcopy(replacement + 0xD0, old + 0xD0);
                qcopy(replacement + 0xE0, old + 0xE0);
                qcopy(replacement + 0x10, old + 0x10);
                *(unsigned short *)(replacement + 0x34) &= 0xFFF9;
                *(unsigned short *)(cursor.parts[5] + 0x34) |= 0x4000;
                *(unsigned short *)(cursor.parts[5] + 0x34) &= 0xFFBE;
                moby_mark_spawned(*cursor.parts);
                *cursor.parts = 0;
            }
        }
        {
            int countdown = 10;
            g_boss_damage_phase_started = 1;
            g_boss_debris_countdown = countdown;
        }
        return;
    }
    if ((((int)(g_boss_phase_timer_base / 3) * 5 + 2) / 6) < timer) {
        if (timer & 15) return;
        {
            int index = math_random_int_below(5);
            char **base = cursor.state->parts;
            char **slot = base + index;
            char *direction = *slot + 0xD0;
            int parity;
            scale = math_random_float_range(4.0f, 12.0f);
            FastVecScale((char *)&local.velocity, direction, scale);
            FastVecAdd((char *)&local.velocity, (char *)&local.velocity, *slot + 16);
            scale = math_random_float_range(2.3f, 3.7f);
            parity = index & 1;
            SpawnExplosion_pal(&local.velocity, parity, 20, 10, 14, 15, 25, 0, scale, 20.0f, parity, 0, 0, 0);
        }
        PlayMobySound(math_random_int_below(3) + 13, 0, object);
        return;
    }
    if (timer & 31) return;
    {
        int index = math_random_int_below(5);
        char **base = cursor.state->parts;
        char **slot = base + index;
        char *direction = *slot + 0xD0;
        int parity;
        scale = math_random_float_range(4.0f, 12.0f);
        FastVecScale((char *)&local.velocity, direction, scale);
        FastVecAdd((char *)&local.velocity, (char *)&local.velocity, *slot + 16);
        scale = math_random_float_range(2.3f, 3.7f);
        parity = index & 1;
        SpawnExplosion_pal(&local.velocity, parity, 20, 10, 14, 15, 25, 0, scale, 20.0f, parity, 0, 0, 0);
    }
    PlayMobySound(math_random_int_below(3) + 13, 0, object);
}

#include "common.h"

typedef struct {
    char pad0[0x1a8];
    int path;
    char pad1[0x38];
    int slots[21];
    char pad2[0x4a8];
    int links[6];
    int branches[4];
    int value;
} L04RaceState;

typedef struct {
    char pad0[0x54];
    int links[6];
    int branches[4];
    int value;
    char pad1[0x23];
    unsigned char count;
    char pad2[0xc0];
    unsigned char *owner;
    char pad3[0x40];
    int group;
    char pad4[4];
    float delay;
    float duration;
    int f1b8;
    char pad5[8];
    int f1c4, f1c8, f1cc, f1d0;
    float f1d4;
    int f1d8, f1dc, f1e0;
    char pad6[0xec];
    int f2d0;
} L04RacerState;

typedef struct { int count; char pad[0x18]; float duration; } L04RacePath;

typedef struct { int delay; char pad[0x3c]; } L04RaceDelay;

/* D_001A7B90 is the 40-byte saved settings block; only its first word is read here. */
typedef struct { int f00; char pad[0x24]; } L04Settings;

typedef struct {
    char pad0[0x20];
    unsigned char state;
    char pad1[0x47];
    L04RacerState *vars;
    char pad2[0x94];
} L04Moby;

extern L04Moby *g_moby_l04_pool;
extern L04RacePath *g_route_path_table[];
extern L04RaceDelay D_L04_002C63D4[];
extern int g_current_race_index __attribute__((sda));
extern float D_L04_001B0928 __attribute__((sda));
extern L04Settings g_is_pal_video __attribute__((sda));
extern int math_random_int_range(int, int);
extern unsigned int race_get_course_finish_count(int);
extern void racer_reset_for_race(L04Moby *);

/* Sets up a race controller's participants: counts the 21 member slots, copies the route links of
   the first racer into the controller, gives each racer a random group (at most four per group),
   its start delay and route duration, then starts it. */
void InitRaceParticipants(unsigned char *controller)
{
    int used[10];
    L04RaceState *raceState = *(L04RaceState **)(controller + 0x68);
    int first;
    int count;
    int i, j, startDelay;
    L04RacePath *path;
    L04RacerState *racerVars;

    count = 0;
    first = 0;
    for (i = 0; i < 21; i++)
        if (raceState->slots[i] != -1)
            count++;
    for (i = 9; i >= 0; i--)
        used[i] = 0;
    for (i = 0; i < 21; i++) {
        if (raceState->slots[i] != -1) {
            racerVars = g_moby_l04_pool[raceState->slots[i]].vars;
            if (!first) {
                int *dst = raceState->branches;
                int *src = racerVars->branches;

                for (j = 0; j < 6; j++)
                    raceState->links[j] = racerVars->links[j];
                for (j = 0; j < 4; j++)
                    dst[j] = src[j];
                raceState->value = racerVars->value;
                first = 1;
            }
            racerVars->count = count;
            racerVars->owner = controller;
            j = math_random_int_range(0, 9);
            while (used[j] >= 4)
                j = math_random_int_range(0, 9);
            used[j]++;
            racerVars->group = j + 1;
            startDelay = D_L04_002C63D4[g_current_race_index].delay;
            racerVars->f2d0 = 0;
            if (g_is_pal_video.f00) {
                startDelay = (int)((float)startDelay * 0.8333334f + 0.01f);
                if (g_current_race_index == 0)
                    startDelay += race_get_course_finish_count(0) * 100;
                racerVars->delay = (float)startDelay * 0.006666667f;
            } else {
                if (g_current_race_index == 0)
                    startDelay += race_get_course_finish_count(0) * 120;
                racerVars->delay = (float)startDelay * 0.005555556f;
            }
            path = g_route_path_table[raceState->path];
            racerVars->duration = path->duration * (float)path->count;
            D_L04_001B0928 = racerVars->duration;
            racerVars->f1d4 = -1.0f;
            racerVars->f1b8 = 0;
            racerVars->f1c4 = -1;
            racerVars->f1c8 = 0;
            racerVars->f1cc = -1;
            racerVars->f1d0 = -1;
            racerVars->f1e0 = 0;
            racerVars->f1d8 = 0;
            racerVars->f1dc = 0;
            racer_reset_for_race(&g_moby_l04_pool[raceState->slots[i]]);
            g_moby_l04_pool[raceState->slots[i]].state = 1;
        }
    }
}

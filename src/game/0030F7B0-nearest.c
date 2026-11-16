#include "common.h"

/* The moby fields this unit reads. */
typedef struct Moby {
    char pad00[0x10];
    float position[4];          /* 0x10 */
    unsigned char state;        /* 0x20 */
    char pad21[0x28 - 0x21];
    struct Moby *next;          /* 0x28 */
    char pad2C[0x68 - 0x2C];
    char *vars;                 /* 0x68 */
    char pad6C[0xAA - 0x6C];
    short oClass;               /* 0xAA */
} Moby;

/* The result of the last collision line test. */
typedef struct {
    char pad00[0x18];
    Moby *moby;                 /* 0x18: the moby hit, 0 for none */
    char pad1C[4];
    float point[4];             /* 0x20 */
} Collision;

/* Prefix of the hero. */
typedef struct {
    char pad0000[0x2290];
    Moby *moby;                 /* 0x2290 */
} Hero;

extern Moby *g_moby_list_head __attribute__((sda));   /* the first moby of the moby list */
extern float g_nearest_search_range;                        /* the search range */
extern char g_camera_eye_state[];                       /* the camera position */
extern Collision g_collision_hit;
extern Hero g_hero_state;

extern int math_fast_helper_a(void *sphere, float);
extern int CollLine(void *start, void *end, int, void *moby, int);
extern float vec_distance_xy(void *a, void *b);
extern float fast_vec_dist(void *a, void *b);

/* Returns the moby of class 0xCB5 or 0x12EA nearest the hero, not in state 2, that the camera
 * can see: func_00283DB8 passes and the line from the camera hits nothing, or only the hero
 * or a 0xCB5 moby (or ends within 1.0 of a 0x12EA moby). */
Moby *FindNearestEligibleTarget(Moby *self)
{
    Moby *best = 0;
    Moby *moby = g_moby_list_head;
    float nearest;
    float sphere[4];

    nearest = g_nearest_search_range;
    while (moby != 0) {
        if ((moby->oClass == 0xCB5 /* moby class 3253 */ || moby->oClass == 0x12EA /* moby class 4842 */) && moby->state != 2) {
            int accept;

            qcopy(sphere, moby->position);
            sphere[3] = 0.5f;
            if (math_fast_helper_a(sphere, *(float *)(moby->vars + 8)) != -1) {
                accept = 1;
                if (CollLine(g_camera_eye_state, moby->position, 6, moby, 0)) {
                    Moby *hit = g_collision_hit.moby;

                    if (hit == 0 || (hit->oClass != 0xCB5 && g_hero_state.moby != hit))
                        accept = 0;
                    if (moby->oClass == 0x12EA &&
                        vec_distance_xy(g_collision_hit.point, moby->position) < 1.0f)
                        accept = 1;
                }
                if (accept) {
                    float distance = fast_vec_dist(moby->position, g_hero_state.moby->position);

                    if (distance < nearest) {
                        nearest = distance;
                        best = moby;
                    }
                }
            }
        }
        moby = moby->next;
    }
    return best;
}

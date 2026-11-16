#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct { TI128 position, next, offset, origin; char *owner; int mode; float progress; int hit; } Entry05;
typedef struct { char pad[0x160]; float strength; int unused; int timer, mode; } Camera05;
extern Entry05 g_beam_records[];
extern Camera05 g_hero_l05_state;
extern struct { char pad[0x18]; char *hit; } g_collision_l05_result;
extern int g_feltzin_challenge_state[];
extern char *moby_get_motion_data(char *object);
extern void moby_transform_joint_to_world(char *object, int a1, char *out);
extern void FastVecAdd(void *dst, void *src, char *src2);
extern void FastVecScale(void *dst, void *src, float value);
extern void FastVecSub(void *dst, void *src, char *src2);
extern void lerp_vector(char *, char *, char *, float);
extern float fast_vec_dist(char *, char *);
extern int CollLine(void *a0, void *a1, int a2, char *a3, int a4);
extern void hero_apply_damage_pal(float value);

void beam_update_records_pal(char *obj)
{
    char a[16] __attribute__((aligned(16)));
    char b[16] __attribute__((aligned(16)));
    int i;
    char *position;
    for (i = 0; i < 128; i++) {
        Entry05 *p = &g_beam_records[i];
        char *state;
        if (p->owner != obj) continue;
        position = (char *)&p->position;
        state = moby_get_motion_data(obj);
        if (g_feltzin_challenge_state[11] == 1 || *(int *)(state + 0x110) == 0) {
            p->owner = 0;
            continue;
        }
        moby_transform_joint_to_world(obj, 0, (char *)&p->origin);
        qcopy(a, *(char **)(state + 0x120) + 0x10);
        FastVecAdd(a, (char *)&p->offset, a);
        FastVecScale(b, *(char **)(state + 0x120) + 0xC0, 0.5f);
        FastVecSub(a, a, b);
        switch (p->mode) {
        case 0: {
            float d;
            qcopy(position, (char *)&p->origin);
            lerp_vector((char *)&p->next, (char *)p, a, p->progress);
            d = fast_vec_dist((char *)&p->origin, a);
            if (d > 64.0f) d = 64.0f;
            else if (d < 1.0f) d = 1.0f;
            p->progress += 2.0f / d;
            if (p->progress >= 1.0f) {
                p->progress = 1.0f;
                p->mode = 1;
            }
            break;
        }
        case 1:
            qcopy((char *)&p->next, a);
            lerp_vector((char *)p, a, (char *)&p->origin, p->progress);
            p->progress -= 0.25f;
            if (p->progress <= 0.0f) p->owner = 0;
            break;
        }
        if (p->hit == 0 && CollLine(p, (char *)&p->next, 4, obj, 0)) {
            char *hit = g_collision_l05_result.hit;
            if (hit && *(short *)(hit + 0xAA) == 0xFBF) {
                g_hero_l05_state.timer = 25;
                g_hero_l05_state.strength = 0.05f;
                g_hero_l05_state.mode = 0;
                hero_apply_damage_pal(1.0f);
                p->hit = 1;
            }
        }
    }
}

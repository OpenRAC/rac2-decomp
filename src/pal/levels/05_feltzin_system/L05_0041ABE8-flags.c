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

/* Updates the beam records owned by this object: each one sweeps from the object toward its target and back, and hurts the player on a hit. */
void beam_update_records_pal(char *obj)
{
    char target_pos[16] __attribute__((aligned(16)));
    char half_extent[16] __attribute__((aligned(16)));
    int i;
    char *position;
    for (i = 0; i < 128; i++) {
        Entry05 *rec = &g_beam_records[i];
        char *state;
        if (rec->owner != obj) continue;
        position = (char *)&rec->position;
        state = moby_get_motion_data(obj);
        if (g_feltzin_challenge_state[11] == 1 || *(int *)(state + 0x110) == 0) {
            rec->owner = 0;
            continue;
        }
        moby_transform_joint_to_world(obj, 0, (char *)&rec->origin);
        qcopy(target_pos, *(char **)(state + 0x120) + 0x10);
        FastVecAdd(target_pos, (char *)&rec->offset, target_pos);
        FastVecScale(half_extent, *(char **)(state + 0x120) + 0xC0, 0.5f);
        FastVecSub(target_pos, target_pos, half_extent);
        switch (rec->mode) {
        case 0: {
            float dist;
            qcopy(position, (char *)&rec->origin);
            lerp_vector((char *)&rec->next, (char *)rec, target_pos, rec->progress);
            dist = fast_vec_dist((char *)&rec->origin, target_pos);
            if (dist > 64.0f) dist = 64.0f;
            else if (dist < 1.0f) dist = 1.0f;
            rec->progress += 2.0f / dist;
            if (rec->progress >= 1.0f) {
                rec->progress = 1.0f;
                rec->mode = 1;
            }
            break;
        }
        case 1:
            qcopy((char *)&rec->next, target_pos);
            lerp_vector((char *)rec, target_pos, (char *)&rec->origin, rec->progress);
            rec->progress -= 0.25f;
            if (rec->progress <= 0.0f) rec->owner = 0;
            break;
        }
        if (rec->hit == 0 && CollLine(rec, (char *)&rec->next, 4, obj, 0)) {
            char *hit = g_collision_l05_result.hit;
            if (hit && *(short *)(hit + 0xAA) == 0xFBF) {
                g_hero_l05_state.timer = 25;
                g_hero_l05_state.strength = 0.05f;
                g_hero_l05_state.mode = 0;
                hero_apply_damage_pal(1.0f);
                rec->hit = 1;
            }
        }
    }
}

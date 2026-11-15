#include "include_asm.h"
#include "names.h"

typedef int Rac2TI128 __attribute__((mode(TI)));

extern int joba_group_has_three_live_objects(char *object);
extern void FastVecSub(void *, void *, void *);
extern float vec_get_heading_angle(char *object, float *src, char *third);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_vec_dist(void *, void *);
extern int math_random_int_below(int);
extern void moby_set_state(char *, int, int);
extern void anim_start_blended(char *, int, int, int);
extern char g_hero_position[];

/* Picks the attack variant the actor plays against its target: the aim vector comes from the
   state's target record, or the shared default, and a close and well aimed target starts one
   of three attacks. */
int security_robot_try_start_attack(char *object)
{
    char *state = *(char **)(object + 0x68);
    float targetPos[4];
    float offset[4];
    float angleToTarget;
    char *targetRecord;

    if (joba_group_has_three_live_objects(object) != 0)
        return 0;
    targetRecord = *(char **)(state + 0x350);
    if (targetRecord != 0)
        *(Rac2TI128 *)targetPos = *(Rac2TI128 *)(targetRecord + 0x10);
    else
        *(Rac2TI128 *)targetPos = *(Rac2TI128 *)g_hero_position;
    if (*(short *)(state + 0x36E) != 0) {
        FastVecSub(offset, targetPos, object + 0x10);
        angleToTarget = vec_get_heading_angle(object, offset, state + 0x2F0);
    } else {
        angleToTarget = FastDiffRots(mat_fast_helper_a(targetPos[0] - *(float *)(object + 0x10), targetPos[1] - *(float *)(object + 0x14)),
                            *(float *)(object + 0xF8));
    }
    if (fast_vec_dist(object + 0x10, targetPos) < 4.0f) {
        if (angleToTarget < 0.26179942f) {
            if (math_random_int_below(4) == 0) {
                moby_set_state(object, 0xC, 5);
                if (*(unsigned char *)(object + 0x43) != 7)
                    anim_start_blended(object, 7, 0, 0xA);
            } else if (*(int *)(state + 0x354) != 0) {
                moby_set_state(object, 0xE, 6);
                if (*(unsigned char *)(object + 0x43) != 9)
                    anim_start_blended(object, 9, 8, 0xF);
            } else {
                moby_set_state(object, 0xD, 6);
                if (*(unsigned char *)(object + 0x43) != 8)
                    anim_start_blended(object, 8, 8, 0xF);
            }
            return 1;
        }
    }
    return 0;
}

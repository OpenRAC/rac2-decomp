#include "common.h"

typedef struct {
    float pos[4];
    u8 pad10[0x80 - 0x10];
    float origin[4];
    u8 pad90[0x98 - 0x90];
    float yaw;
    u8 pad9C[0x190 - 0x9C];
    float altPos[4];
    float altYaw;
    u8 pad1A4[0xBC0 - 0x1A4];
    float aim[4];
    u8 padBD0[0xBE4 - 0xBD0];
    char *target;
    int active;
    float aimAngle;
    u8 padBF0[0x1248 - 0xBF0];
    int state;
    u8 pad124C[0x24B8 - 0x124C];
    float f24B8;
} HeroTargetState;

extern HeroTargetState D_00189E20_target;
extern void hero_resolve_stick_direction(int, float);
extern char *SelectBestEligibleTarget(float, float, float, float, float *, int, int);
extern float mat_fast_helper_a(float, float);
extern void FastVecSub(float *, char *, float *);
extern void cam_set_view_space_height(float *, float *, float);

/* Unless the hero state is 0x20 or a target is already active, selects the best eligible target from the
 * hero position and yaw (or, when the value at 0x24B8 exceeds 0.5, from the alternate position and yaw after
 * clearing the target and marking it active), then aims: the angle and offset to the chosen target, else the
 * saved yaw and vector. Finally passes the aim vector to a helper. */
/* Picks the best thing in front of the hero to aim at and turns the aim toward it. */
void hero_l00_select_aim_target(float a, float b, float c)
{
    HeroTargetState *hero = &D_00189E20_target;
    char *best_target;
    float yaw;
    float vector[4];

    if (hero->state == 0x20 || hero->active != 0)
        return;
    yaw = hero->yaw;
    qcopy(vector, hero->pos);
    if (0.5f < hero->f24B8) {
        hero_resolve_stick_direction(0, 1.0f);
        yaw = hero->altYaw;
        qcopy(vector, hero->altPos);
        hero->target = 0;
        hero->active = 1;
    }
    best_target = SelectBestEligibleTarget(a, yaw, b, c, vector, -1, 0);
    if (best_target != 0 && (hero->target == 0 || hero->active != 0)) {
        hero->aimAngle = mat_fast_helper_a(*(float *)(best_target + 0x10) - hero->origin[0],
                                    *(float *)(best_target + 0x14) - hero->origin[1]);
        FastVecSub(hero->aim, best_target + 0x10, hero->origin);
        hero->target = best_target;
    } else {
        D_00189E20_target.aimAngle = yaw;
        qcopy(D_00189E20_target.aim, vector);
    }
    cam_set_view_space_height(D_00189E20_target.aim, D_00189E20_target.aim, 0.0f);
}

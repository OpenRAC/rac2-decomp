#include "common.h"

typedef struct Moby Moby;

/* A crate's instance data. */
typedef struct {
    char pad00[0x50];
    char f50[0x40];             /* 0x50: updated by func_002AD6F0 from the movement */
    float velocity[4];          /* 0x90: w is the speed of the lift towards its target */
    Moby *above;                /* 0xA0: the crate stacked on this one */
    Moby *below;                /* 0xA4: the crate this one stands on */
    char padA8[4];
    int flags;                  /* 0xAC: 2 stops the update, 4 set while falling */
    float height;               /* 0xB0 */
    int frame;                  /* 0xB4: D_001B1688 when last updated */
    char padB8[0xD0 - 0xB8];
    float attachOffset[4];      /* 0xD0 */
    float attachRotation[4];    /* 0xE0 */
    void *attachment;           /* 0xF0: what the crate rides on, 0 for none */
    float lift;                 /* 0xF4: height above the attachment point */
} CrateVars;

/* The moby fields this unit reads. */
struct Moby {
    char pad00[0x10];
    float position[4];          /* 0x10 */
    unsigned char state;        /* 0x20 */
    char pad21[0x36 - 0x21];
    short f36;                  /* 0x36 */
    char pad38[0x68 - 0x38];
    CrateVars *vars;            /* 0x68 */
    char pad6C[0xAA - 0x6C];
    short oClass;               /* 0xAA */
    char padAC[0xBC - 0xAC];
    unsigned char fBC;          /* 0xBC */
    char padBD[0xC0 - 0xBD];
    float matrix[12];           /* 0xC0 */
    float rotation[4];          /* 0xF0 */
};

/* Prefix of the hero. */
typedef struct {
    char pad000[0x80];
    float position[4];          /* 0x80 */
    char pad090[0x250 - 0x90];
    float f250;                 /* 0x250 */
    char pad254[0x264 - 0x254];
    float f264;                 /* 0x264 */
} Hero;

/* The record func_002AD0B0 returns for an attachment. */
typedef struct {
    char pad00[0x3C];
    int flags;                  /* 0x3C */
} AttachmentInfo;

/* The result of the last collision line test. */
typedef struct {
    char pad00[0x20];
    float point[4];             /* 0x20 */
} Collision;

extern int g_game_time __attribute__((sda));     /* the frame counter */
extern Hero g_hero_state;
extern Collision g_collision_hit;

extern int moby_is_in_special_class_range(Moby *moby);
extern void FastVecSub(void *out, void *a, void *b);
extern void matrix_mul_vec3(void *out, void *vector, void *matrix);
extern void FastVecAdd(void *out, void *a, void *b);
extern float math_fabs(float value);
extern float ApproachValue(void *value, float target, float step);
extern float FastVecLength(void *vector);
extern void DestroyCrate(Moby *moby, int, int);
extern void crate_drop_loot(Moby *moby);
extern void coll_apply_push_to_object(Moby *moby, void *attachment, void *position, void *rotation,
                          void *outPosition, void *outRotation);
extern void mat_combine_and_store(void *, void *movement, void *previousRotation, void *rotation);
extern AttachmentInfo *moby_get_private_value_2(void *attachment);
extern int CollLine(void *start, void *end, int, void *moby, int);

/* Adapted from RAC1 update_crate_stack_motion (GPL-3.0).
 * Moves a stack of crates once a frame, from the bottom crate up: breaks a crate the hero
 * touches from below, then lets each one ride what it is attached to, or fall until it lands
 * on the ground or on the crate below. */
void UpdateCrateStackMotion(Moby *moby)
{
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    float hit[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float attachPosition[4] __attribute__((aligned(16)));
    float previousPosition[4] __attribute__((aligned(16)));
    float previousRotation[4] __attribute__((aligned(16)));
    float movement[4] __attribute__((aligned(16)));
    CrateVars *vars;
    Moby *bottom;
    Moby *next;
    Moby *below;
    int landed;

    if (moby->state == 0)
        return;
    vars = moby->vars;
    if (vars->frame == g_game_time)
        return;

    next = moby;
    do {
        bottom = next;
        next = bottom->vars->below;
    } while (next != 0);

    next = bottom;
    do {
        moby = next;
        vars = moby->vars;
        next = vars->above;
        if (!(vars->flags & 4))
            vars->flags &= ~0x10;
        vars->flags &= ~4;
        if (!moby_is_in_special_class_range(moby) || (vars->flags & 2))
            return;
        vars->frame = g_game_time;
        if (moby->state != 0) {
            /* A crate the hero touches from below breaks and drops its loot. */
            FastVecSub(delta, g_hero_state.position, moby->position);
            matrix_mul_vec3(delta, delta, moby->matrix);
            if (math_fabs(delta[0]) < 0.55f && math_fabs(delta[1]) < 0.55f &&
                delta[2] < 0.0f && delta[2] > -(g_hero_state.f250 + g_hero_state.f264) &&
                (moby->state == 1 || moby->state == 5)) {
                DestroyCrate(moby, moby->oClass == 0x1F9 /* Explosive Crate */, 0);
                crate_drop_loot(moby);
            }

            {
                float fall = vars->velocity[2] - 0.0027222224f;

                fall = fall < -0.3f ? -0.3f : fall;
                fall = fall > 0.3f ? 0.3f : fall;
                vars->velocity[2] = fall;
            }

            if (vars->attachment != 0) {
                /* Ride the attachment, the lift easing towards its target. */
                if (vars->below == 0) {
                    vars->velocity[3] -= 0.0027777778f;
                    if (ApproachValue(&vars->lift, 0.0f, math_fabs(vars->velocity[3])) == 0.0f)
                        vars->velocity[3] = 0.0f;
                } else {
                    float target;

                    vars->velocity[3] -= 0.0027777778f;
                    target = vars->below->vars->lift + 1.0f;
                    if (ApproachValue(&vars->lift, target,
                                      math_fabs(vars->velocity[3])) == 0.0f)
                        vars->velocity[3] = 0.0f;
                }
                qcopy(attachPosition, vars->attachOffset);
                attachPosition[2] += vars->lift;
                if (moby != 0)
                    moby->f36 = 0x7F80;
                qcopy(previousPosition, moby->position);
                qcopy(previousRotation, moby->rotation);
                coll_apply_push_to_object(moby, vars->attachment, attachPosition, vars->attachRotation,
                              moby->position, moby->rotation);
                if (moby_get_private_value_2(vars->attachment)->flags & 4) {
                    qcopy(vars->attachOffset, attachPosition);
                    vars->attachOffset[2] -= vars->lift;
                }
                FastVecSub(movement, moby->position, previousPosition);
                movement[3] = vars->velocity[3];
                qcopy(vars->velocity, movement);
                mat_combine_and_store(vars->f50, vars->velocity, previousRotation, moby->rotation);
            } else {
                /* Fall until the line down from the crate hits the ground, or onto the crate
                 * below. */
                if (vars->below == 0) {
                    qcopy(start, moby->position);
                    qcopy(end, moby->position);
                    start[2] += vars->height * 0.75f;
                    end[2] += vars->velocity[2];
                    landed = CollLine(start, end, 2, 0, 0);
                    qcopy(hit, g_collision_hit.point);
                } else {
                    qcopy(hit, vars->below->position);
                    hit[2] += 1.0f;
                    landed = 0;
                    if (moby->position[2] + vars->velocity[2] < hit[2])
                        landed = 1;
                }
                if (landed) {
                    /* A fast landing sets off a Explosive Crate (class 0x1F9) in state 1: this one, or the
                     * one below. */
                    if ((vars->flags & 0x20) && FastVecLength(vars->velocity) > 0.008333334f) {
                        if (moby->oClass == 0x1F9 /* Explosive Crate */ && moby->state == 1) {
                            moby->fBC = 0;
                            moby->state = 5;
                        } else {
                            below = vars->below;
                            if (below != 0 && below->oClass == 0x1F9 /* Explosive Crate */ && below->state == 1) {
                                below->state = 5;
                                vars->below->fBC = 0;
                            }
                        }
                    }
                    moby->position[2] = hit[2];
                    vars->velocity[2] = 0.0f;
                } else {
                    vars->flags |= 4;
                    FastVecAdd(moby->position, moby->position, vars->velocity);
                }
            }
        }
    } while (next != 0);
}

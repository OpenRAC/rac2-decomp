#include "names.h"
/* func_L01_003C0408 (Oozla): steer a moby around its arena centre towards its target.
   Each mode-1 branch stores the height itself and `return distance` follows the inner
   if/else, so the return-value copy is a block of its own: the scheduler cannot hoist
   it over the height store, the height temporary takes $f0 as in retail, and the
   -1000 fallback's store (through $f1) is not cross-jumped with it.
   -frac2-hazard-labels keeps the forward branch into the division on its hazard nop
   (docs/build/compiler-notes.md, Labels on hazard nops). */
#include "common.h"

extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern float math_fabs(float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void moby_set_animation_and_speed(void *, int, int, int);
extern int moby_l01_turn_toward_target(void *, void *);
extern void moby_step_at_own_position_factor(void *, float);

/* 128-byte arena rows with a full 16-byte centre at +0x30. */
typedef struct {
    u8 prefix[0x30];
    float centre[4];
    u8 rest[0x40];
} L01ArenaRow;

/* The table pointer, read with retail's absolute macro load at each use
   (docs/build/compiler-notes.md, incomplete sda array read as element 0). */
extern L01ArenaRow *D_L01_001B264C[] __attribute__((sda));
extern float D_L01_001AFED0 __attribute__((sda));

/* The hero's position at +0x80; the owner stays an incomplete byte array. */
typedef struct {
    u8 prefix[0x80];
    float position[4];
} L01HeroPositionView;
extern u8 g_hero_state[];

/* Moves the Swamp Monster II around the arena centre towards its target, and returns its distance to the target. */
float swamp_monster_move_around_arena(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    float distance, angle, delta, magnitude;

    if (*(int *)(vars + 0x124) == 1) {
        distance = vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x120) + 0x10);
        angle = mat_fast_helper_a(
            *(float *)(moby + 0x10) - D_L01_001B264C[0][*(int *)(vars + 0x2CC)].centre[0],
            *(float *)(moby + 0x14) - D_L01_001B264C[0][*(int *)(vars + 0x2CC)].centre[1]);
        delta = fast_subtract_rotations(
            mat_fast_helper_a(
                *(float *)(*(u8 **)(vars + 0x120) + 0x10) - D_L01_001B264C[0][*(int *)(vars + 0x2CC)].centre[0],
                *(float *)(*(u8 **)(vars + 0x120) + 0x14) - D_L01_001B264C[0][*(int *)(vars + 0x2CC)].centre[1]),
            angle);
        magnitude = math_fabs(delta);
        if (distance > *(float *)(vars + 0x2EC)) {
            if (moby[0x43] != vars[0x2E1])
                moby_set_animation_and_speed(moby, vars[0x2E1], 0, 20);
            if (magnitude < D_L01_001AFED0 * 0.017453294f) {
                qcopy(vars + 0x2A0, *(u8 **)(vars + 0x120) + 0x10);
            } else {
                delta = delta / magnitude;
                delta = delta * 0.087266474f;
                qcopy(vars + 0x2A0, D_L01_001B264C[0][*(int *)(vars + 0x2CC)].centre);
                *(float *)(vars + 0x2A0) += math_fast_sin_or_cos_a(FastAddRotations(angle, delta)) * 38.0f;
                *(float *)(vars + 0x2A4) += math_fast_sin_or_cos_b(FastAddRotations(angle, delta)) * 38.0f;
            }
            moby_l01_turn_toward_target(moby, vars + 0x2A0);
            *(float *)(moby + 0x18) = *(float *)(vars + 0x2E8);
        } else {
            if (moby[0x43] != vars[0x2E2] && moby[0x95] != 3)
                moby_set_animation_and_speed(moby, vars[0x2E2], 0, 20);
            moby_step_at_own_position_factor(moby, mat_fast_helper_a(*(float *)(*(u8 **)(vars + 0x120) + 0x10) - *(float *)(moby + 0x10),
                                             *(float *)(*(u8 **)(vars + 0x120) + 0x14) - *(float *)(moby + 0x14)));
            *(float *)(moby + 0x18) = *(float *)(vars + 0x2E8);
        }
        return distance;
    }
    if (moby[0x43] != vars[0x2E2] && moby[0x95] != 3)
        moby_set_animation_and_speed(moby, vars[0x2E2], 0, 20);
    moby_step_at_own_position_factor(moby, mat_fast_helper_a(((L01HeroPositionView *)g_hero_state)->position[0] - *(float *)(moby + 0x10),
                                     ((L01HeroPositionView *)g_hero_state)->position[1] - *(float *)(moby + 0x14)));
    *(float *)(moby + 0x18) = *(float *)(vars + 0x2E8);
    return -1000.0f;
}

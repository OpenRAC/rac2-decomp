#include "names.h"
/* Rotate a direction by the effect slot while retaining its length and W lane.
 * This uses the same 32-byte record layout as 002FED90, which scans 128 slots.
 * The complete external allocation remains unknown and incompletely bounded.
 * Every scratch vector spans 16 bytes. Cross-product W is carried opaquely by
 * the XYZ scale and overwritten before quaternion multiplication. The
 * length/dot/sine/cosine helpers return float; other vector helpers return void.
 * Default -G0 keeps the two flag guards absolute; the single GP view below
 * describes the measured read of that same mode word during weight selection.
 */
#include "common.h"

typedef struct {
    float basis[4];
    float ordinaryWeight, activeWeight, attachedWeight;
    char *owner;
} SteeringEffectSlot __attribute__((aligned(16)));
typedef struct {
    char reserved00[0x348];
    short attached;
    char reserved34A[0x1F46];
    char *object;
} SteeringHeroPrefix;
extern SteeringEffectSlot D_002212E0[];
extern SteeringHeroPrefix g_hero_state;
extern int D_001A8CA0 MACRO_ADDR;
extern int D_001A8CA4 MACRO_ADDR;
/* The same mode word is read absolutely at the guards and through GP when
 * selecting the coefficient; this explicit view keeps the canonical storage. */
extern int D_001A8CA4_gp SDATA(D_001A8CA4) __attribute__((sda));
extern float FastVecLength(void *);
extern void cam_compute_view_direction(void *, void *, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern void FastVecScale(void *, void *, float);
extern void multiply_quaternions(void *, void *, void *);

/* Turns the given direction a bit toward the camera-linked effect slot's new facing, keeping its length. */
void part_steer_effect_direction(int index, float *direction, void *position)
{
    float oldBasis[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    float conjugate[4] __attribute__((aligned(16)));
    float rotated[4] __attribute__((aligned(16)));
    float origin[4] __attribute__((aligned(16)));
    SteeringEffectSlot *effect;
    float weight;
    float length, savedW, angle, cosine;
    int mode;
    if (index < 0)
        return;
    mode = D_001A8CA0;
    if (!mode && !D_001A8CA4 && !g_hero_state.attached)
        return;
    effect = &D_002212E0[index];
    weight = 1.0f;
    if (position) {
        qcopy(origin, position);
    } else {
        if (!effect->owner)
            return;
        qcopy(origin, effect->owner + 0x10);
    }
    if (g_hero_state.attached) {
        if (D_001A8CA4_gp)
            weight = effect->activeWeight;
        else
            weight = effect->attachedWeight;
    } else if (D_001A8CA4_gp) {
        weight = effect->activeWeight;
    }
    if (mode)
        weight = effect->ordinaryWeight;
    qcopy(oldBasis, effect->basis);
    savedW = direction[3];
    direction[3] = 0.0f;
    length = FastVecLength(direction);
    if (g_hero_state.attached && !D_001A8CA4)
        qcopy(effect->basis, g_hero_state.object + 0xE0);
    else
        cam_compute_view_direction(origin, effect, 1);
    vec_scale_to_length(direction, direction, 1.0f);
    FastVecCross(axis, oldBasis, effect);
    angle = -FastVecDot(oldBasis, effect);
    angle *= weight * 0.5f;
    FastVecScale(rotation, axis, math_fast_sin_or_cos_b(angle));
    cosine = math_fast_sin_or_cos_a(angle);
    conjugate[0] = -rotation[0];
    conjugate[1] = -rotation[1];
    conjugate[2] = -rotation[2];
    rotation[3] = cosine;
    conjugate[3] = cosine;
    multiply_quaternions(rotated, rotation, direction);
    multiply_quaternions(direction, rotated, conjugate);
    vec_scale_to_length(direction, direction, length);
    direction[3] = savedW;
}

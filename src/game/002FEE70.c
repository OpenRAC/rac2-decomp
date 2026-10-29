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
extern SteeringHeroPrefix D_00189E20;
extern int D_001A8CA0 MACRO_ADDR;
extern int D_001A8CA4 MACRO_ADDR;
/* The same mode word is read absolutely at the guards and through GP when
 * selecting the coefficient; this explicit view keeps the canonical storage. */
extern int D_001A8CA4_gp SDATA(D_001A8CA4) __attribute__((sda));
extern float func_00282DF0(void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00283198(float);
extern float func_00283180(float);
extern void func_00282D30(void *, void *, float);
extern void func_002837D0(void *, void *, void *);

void func_002FEE70(int index, float *direction, void *position)
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
    if (!mode && !D_001A8CA4 && !D_00189E20.attached)
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
    if (D_00189E20.attached) {
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
    length = func_00282DF0(direction);
    if (D_00189E20.attached && !D_001A8CA4)
        qcopy(effect->basis, D_00189E20.object + 0xE0);
    else
        func_002AFFD8(origin, effect, 1);
    func_00282F20(direction, direction, 1.0f);
    func_00282DD8(axis, oldBasis, effect);
    angle = -func_00282DB0(oldBasis, effect);
    angle *= weight * 0.5f;
    func_00282D30(rotation, axis, func_00283198(angle));
    cosine = func_00283180(angle);
    conjugate[0] = -rotation[0];
    conjugate[1] = -rotation[1];
    conjugate[2] = -rotation[2];
    rotation[3] = cosine;
    conjugate[3] = cosine;
    func_002837D0(rotated, rotation, direction);
    func_002837D0(direction, rotated, conjugate);
    func_00282F20(direction, direction, length);
    direction[3] = savedW;
}

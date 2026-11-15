/* func_002E64A0 in its own unit (flags in config/cflags.txt: -O2 -G32 -Wa,-G32 -ffunction-sections):
 * the 16-byte vectors below are reached through $gp. The third copy's source stays a block-scoped
 * pointer: its longer lifetime is what makes loop hoist it with the two stack addresses.
 */
#include "common.h"

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct {
    char header[0x10];
    float position[4];
    char pad20[4];
    char *model;
    char pad28[12];
    unsigned short flags;
    char pad36[0x32];
    char *state;
    char pad6c[0x2c];
    int render;
    char pad9c[0x20];
    unsigned char blocked;
    char padbd[3];
    float basis[3][4];
    float previous[4];
} Object;

typedef struct {
    float position[4];
    char gap[0x50];
    float focus[4];
} HeroPosition;

typedef struct {
    char prefix[0x80];
    HeroPosition hero;
    char gapF0[0x24c];
    Object *selected;
    int count;
    char gap344[0x1f4c];
    int collision;
} HeroGlobals;

typedef int Quad __attribute__((mode(TI)));

extern Object *D_00214920[];
extern char D_00214970[], D_00214978[];
extern int D_001A8BB0[] __attribute__((sda));
extern int D_001A8BB0_gp SDATA(D_001A8BB0);
extern int D_001A79F0[] __attribute__((sda));
extern float D_001ABF84 __attribute__((sda)), D_001ABF88 __attribute__((sda)), D_001ABF8C __attribute__((sda));
extern char D_001ABF18[16] __attribute__((sda)), D_001ABF28[16] __attribute__((sda));
extern char D_001ABF38[16] __attribute__((sda)), D_001ABF48[16] __attribute__((sda));
extern char D_001ABF58[16] __attribute__((sda)), D_001ABF68[16] __attribute__((sda));
extern char D_001ABF78[16] __attribute__((sda));
extern HeroGlobals D_00189E20;

#define HERO ((char *)&D_00189E20.hero)

extern void func_002E6178(void *);
extern float func_002A89A8(void *, int, float);
extern void func_002B41A8(void *, void *, int, int, void *, void *, void *, void *, void *, void *, void *);
extern void func_00282D60(void *, void *, float);
extern int func_00283DB8(void *, float);
extern float func_00282E80(void *, void *);
extern int func_002761F8(void *, void *, int, int, int);
extern void func_00282CF0(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AA548(void *, void *, float, float, float, float);
extern void func_0029FC20(void *, int, void *), func_0029FCC0(void *, int, void *);
extern void func_00283098(void *, void *, void *), func_002AB6D8(void *, void *), func_002A10E8(void *);
extern void func_002AD6F0(void *, void *, void *, void *), func_002B44C0(void *, void *, void *);

/* Spawns the equipment pieces if needed, then makes each piece follow the base object. */
void func_002E64A0(Object *object)
{
    float p[4], old[4], matrix[16], previous[4], delta[4], offset[4];
    char *target;
    int i, j;
    unsigned char blocked;

    if (!gEquipmentPieces[0]) {
        SpawnEquipmentPieces(object);
        if (!gCurrentGameMode[0]) {
            float height = ProbeGroundHeightBelow(object->position, 0, 0.5f);
            if (height != 0.0f)
                object->position[2] = height + D_001ABF84;
            D_001ABF88 = object->position[2];
        }
        InitMovementControllerParams(object, D_00214970, 0, 0, D_001ABF48, D_001ABF58, D_001ABF18, D_001ABF78,
                      D_001ABF68, D_001ABF28, D_001ABF38);
    }
    target = 0;
    if (!gCurrentGameMode[0]) {
        scale_vector(p, object, 0.0009765625f);
        p[3] += 1.0f;
        if (FastMathHelperA(p, 50.0f) == -1)
            return;
        if (!D_001A8BB0_gp) {
            blocked = 0;
            if (vec_distance_xy(object->position, HERO) < 6.0f) {
                if (object->blocked) {
                    qcopy(p, HERO + 0x60);
                    p[2] += 2.0f;
                    if (CollLine(HERO + 0x60, p, 0, gHeroState.collision, 0))
                        blocked = 1;
                    else {
                        FastVecSub(old, object->position, HERO);
                        old[2] = 0;
                        vec_scale_to_length(old, old, 0.4f);
                        FastVecAdd(p, p, old);
                        blocked = CollLine(HERO + 0x60, p, 0, gHeroState.collision, 0) != 0;
                    }
                } else {
                    qcopy(p, HERO + 0x60);
                    p[2] += 2.0f;
                    blocked = CollLine(HERO + 0x60, p, 0, *(int *)(HERO + 0x2210), 0) != 0;
                }
            }
            object->blocked = blocked;
            if (object->blocked)
                StepValueTowardTarget(D_00214978, &D_001ABF8C, D_001ABF88 + 0.75f, 0.00055555557f, 0.00055555557f, 0.0166666675f);
            else
                StepValueTowardTarget(D_00214978, &D_001ABF8C, D_001ABF88, 0.00055555557f, 0.00055555557f, 0.0166666675f);
        }
    }
    TransformMobyJointPoint(object, 1, matrix);
    TransformMobyJointToWorld(object, 1, p);
    for (i = 0; gEquipmentPieces[i]; i++) {
        if (object->flags & 1)
            gEquipmentPieces[i]->flags |= 0x41;
        else
            gEquipmentPieces[i]->flags &= 0xFFBE;
        {
            Object *part = gEquipmentPieces[i];
            qcopy(old, part->position);
            qcopy(previous, part->previous);
            {
                float *from = object->position;
                qcopy(part->position, from);
            }
        }
        for (j = 0; j < 3; j++) {
            gEquipmentPieces[i]->basis[j][0] = matrix[j * 4];
            gEquipmentPieces[i]->basis[j][1] = matrix[j * 4 + 1];
            gEquipmentPieces[i]->basis[j][2] = matrix[j * 4 + 2];
        }
        if (gCurrentGameMode[0] == 2 && gCurrentMapIndex[0] == 5) {
            *(Quad *)offset = 0;
            offset[0] = -0.3372f;
            offset[1] = -0.5364f;
            offset[2] = -1.79489f;
            matrix_mul_vec3(offset, offset, gEquipmentPieces[i]->basis);
            FastVecAdd(delta, p, offset);
            qcopy(gEquipmentPieces[i]->position, delta);
        }
        GetEulerAnglesFromMatrix(gEquipmentPieces[i]->basis, gEquipmentPieces[i]->previous);
        func_002A10E8(gEquipmentPieces[i]);
        {
            char *state = gEquipmentPieces[i]->state;
            FastVecSub(delta, gEquipmentPieces[i]->position, old);
            CombineTransformsAndStore(state + 0x20, delta, previous, gEquipmentPieces[i]->previous);
        }
        if (gHeroState.count >= 2 && gHeroState.selected == gEquipmentPieces[i])
            target = HERO;
        if (gCurrentGameMode[0]) {
            gEquipmentPieces[i]->render = 0;
            object->render = 0;
        } else if (object->render)
            gEquipmentPieces[i]->render = *(int *)(gEquipmentPieces[i]->model + 0x10);
    }
    if (!gCurrentGameMode[0])
        UpdateObjectSway(object, D_00214970, target);
}

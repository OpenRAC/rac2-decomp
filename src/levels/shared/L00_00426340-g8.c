#include "include_asm.h"
#include "common.h"

extern void ref_L00_00428560_00(char *);

extern void ref_L00_0042ABF8_00(char *);

extern void ref_L00_0042B688_00(char *);

/* Calls this level's own setup routine for the object. */
void func_L00_00428560(char *object)
{
    ref_L00_00428560_00(object);
}

/* Calls this level's own setup routine for the object. */
void func_L00_0042ABF8(char *object)
{
    ref_L00_0042ABF8_00(object);
}

/* Calls this level's own setup routine for the object. */
void func_L00_0042B688(char *object)
{
    ref_L00_0042B688_00(object);
}
extern char D_L00_001ADC68[4] __attribute__((sda));

extern char D_L00_001ADC48[4] __attribute__((sda));

extern void func_L00_0042B408(char *);

/* Stores the first shared data pointer in the object and then runs its common setup. */
void func_L00_0042B6A8(char *object)
{
    *(char **)object = D_L00_001ADC68;
    func_L00_0042B408(object);
}

/* Stores the second shared data pointer in the object and then runs its common setup. */
void func_L00_0042B6C8(char *object)
{
    *(char **)object = D_L00_001ADC48;
    func_L00_0042B408(object);
}

/* The global this one writes sits at a different address from level to level, and it is
 * not the one func_L00_004272A0 reads in every level, so it takes a name of its own. */
extern int ref_L00_00427290_00 __attribute__((sda));

/* Turns on a flag that other code checks later. */
void func_L00_00427290(void)
{
    ref_L00_00427290_00 = 1;
}


extern int D_L00_001B2700 __attribute__((sda));

extern int D_L00_001B15DC __attribute__((sda));

/* Returns a saved value from this level. */
int func_L00_004272A0(void)
{
    return D_L00_001B15DC;
}

/* Returns another saved value from this level. */
int func_L00_0042B730(void)
{
    return D_L00_001B2700;
}

extern float D_L00_001B15B8 __attribute__((sda));

extern char D_L00_001B9040[];

extern char D_00189F70[];

extern int D_001A7BAC;

extern float D_L00_001A8904;

extern int D_L00_001A8FF0;

extern void func_00282CC0(char *, char *, char *);

extern float func_00283B98(float, float);

extern void func_L00_004208C8(char *, float *);

extern void func_L00_004224D0(char *);

extern void func_L00_00421C50(char *);

extern void func_L00_00426340(int);

extern void func_L00_00422268(char *);

/* Builds the hero's 16-byte block from the hero record and the parameter block, stores the
   table's current blend weight in the global, refines the block's last float with the
   parameter block's own float (the hero's own float only when the global allows it) and
   hands the block to the object's own refresh, which then runs the five owner helpers.
   The retail reaches the blend table through $gp, so this body needs the small-data
   profile (-G8, from this file's name). */
void func_L00_004263B8(char *object)
{
    char local[16];
    char *hero = D_00189F70;
    char *self = object;
    char *parameters = D_L00_001B9040;
    float value = (&D_L00_001B15B8)[D_001A7BAC];
    float first;

    D_L00_001A8904 = value;
    FastVecAdd(local, hero, parameters);
    first = *(float *)(hero + 12);
    if (D_L00_001A8FF0 != 0) {
        first = 0.0f;
    }
    *(float *)(local + 12) = FastAddRotations(first, *(float *)(parameters + 12));
    TranslateObjectAndView(self, (float *)local);
    UpdateFollowCameraMoby(self);
    UpdateFollowCameraCollision(self);
    RunFollowCameraFrame((int)self);
    ResetWeaponViewState(self);
}


typedef struct {
    char pad0[0xE0];
    float mE0[4];
} Model_42A698;

typedef struct {
    char pad0[0x20];
    Model_42A698 *model;
    int f24;
    float f28;
    float f2C;
    float f30;
    float f34;
    char pad38[0x60 - 0x38];
    float v60[4];
} Ent_42A698;

typedef struct {
    char pad0[0x1C];
    Ent_42A698 *ent;
} Rec_42A698;

typedef struct {
    float m0[4];
    float m10[4];
    float m20[4];
    float m30[4];
    char pad40[0x84 - 0x40];
    short idx;
} Self_42A698;

extern int func_L00_003DF108(void *);
extern int func_L00_003DE260(void);
extern int func_L00_00400F38(void);
extern int func_L00_00401E28(void);
extern void func_L00_003252C8(void *, void *);
extern void func_L00_0042A908(void *, void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern void func_002ACF68(void *, void *, void *, int, float);

extern Rec_42A698 *D_L00_001B1844;
extern float D_L00_001B1644 __attribute__((sda));
extern float D_L00_001B1648 __attribute__((sda));

/* Works out the object's position and facing from the hero and the model, then nudges its position gradually toward the new spot. */
void func_L00_0042A698(Self_42A698 *self)
{
    float baseRow[4];
    float l1[4];
    float l2[4];
    float l3[4];
    float l4[4];
    float modelRow[4];
    float l6[4];
    float l7[4];
    float l8[4];
    Ent_42A698 *entity;
    float *position;
    float dot;

    entity = D_L00_001B1844[self->idx].ent;
    if (GetTrackedObjectFlag(self) != 0 || GetGlobalObjectFlag() != 0) {
        qcopy(baseRow, entity->model->mE0);
    } else {
        ClearOrComputeVector(self->m30, baseRow);
    }
    position = self->m30;
    if (IsTrackedObjectActive() != 0 || IsGlobalObjectBusy() != 0) {
        entity->f28 = D_L00_001B1644;
        entity->f2C = D_L00_001B1648;
    }
    vec_scale_to_length(l1, entity->model->mE0, 0.25f);
    FastVecAdd((char *)l1, (char *)entity->model + 0x10, (char *)l1);
    FastVecSub(l2, l1, position);
    vec_scale_to_length(self, l2, 1.0f);
    FastVecCross(self->m10, self, baseRow);
    vec_scale_to_length(self->m10, self->m10, 1.0f);
    FastVecCross(self->m20, self->m10, self);
    qcopy(modelRow, entity->model->mE0);
    BuildRotationTowardVector(entity->v60, entity->v60, modelRow, 0, 0.125f);
    FastVecScale(l2, l2, -1.0f);
    dot = FastVecDot(l2, entity->v60);
    FastVecScale(l3, entity->v60, dot);
    FastVecSub(l4, l2, l3);
    vec_scale_to_length(l3, l3, entity->f34);
    vec_scale_to_length(l6, l4, entity->f30);
    FastVecAdd((char *)l6, (char *)l3, (char *)l6);
    FastVecAdd((char *)l7, (char *)l1, (char *)l6);
    ClampCameraSegmentByCollision(self, l8, l1, l7);
    lerp_vector(position, position, l8, 0.1f);
}

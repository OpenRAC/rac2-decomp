#include "include_asm.h"
#include "common.h"

extern void ref_L00_00428560_00(char *);

extern void ref_L00_0042ABF8_00(char *);

extern void ref_L00_0042B688_00(char *);

/* Calls this level's own setup routine for the object. */
void lancer_call_setup(char *object)
{
    ref_L00_00428560_00(object);
}

/* Calls this level's own setup routine for the object. */
void moby_call_setup_b(char *object)
{
    ref_L00_0042ABF8_00(object);
}

/* Calls this level's own setup routine for the object. */
void moby_call_setup_c(char *object)
{
    ref_L00_0042B688_00(object);
}
extern char D_L00_001ADC68[4] __attribute__((sda));

extern char D_L00_001ADC48[4] __attribute__((sda));

extern void func_L00_0042B408(char *);

/* Stores the first shared data pointer in the object and then runs its common setup. */
void moby_init_with_table_a(char *object)
{
    *(char **)object = D_L00_001ADC68;
    func_L00_0042B408(object);
}

/* Stores the second shared data pointer in the object and then runs its common setup. */
void moby_init_with_table_b(char *object)
{
    *(char **)object = D_L00_001ADC48;
    func_L00_0042B408(object);
}

/* The global this one writes sits at a different address from level to level, and it is
 * not the one func_L00_004272A0 reads in every level, so it takes a name of its own. */
extern int ref_L00_00427290_00 __attribute__((sda));

/* Turns on a flag that other code checks later. */
void level_set_flag(void)
{
    ref_L00_00427290_00 = 1;
}


extern int D_L00_001B2700 __attribute__((sda));

extern int D_L00_001B15DC __attribute__((sda));

/* Returns a saved value from this level. */
int level_get_saved_value(void)
{
    return D_L00_001B15DC;
}

/* Returns another saved value from this level. */
int level_get_saved_value_b(void)
{
    return D_L00_001B2700;
}

extern float D_L00_001B15B8 __attribute__((sda));

extern char D_L00_001B9040[];

extern char D_00189F70[];

extern int D_001A7BAC;

extern float D_L00_001A8904;

extern int D_L00_001A8FF0;

extern void FastVecAdd(char *, char *, char *);

extern float FastAddRotations(float, float);

extern void TranslateObjectAndView(char *, float *);

extern void cam_follow_update(char *);

extern void cam_follow_update_collision(char *);

extern void cam_follow_run_frame(int);

extern void weapon_reset_view_state(char *);

/* Builds the hero's 16-byte block from the hero record and the parameter block, stores the
   table's current blend weight in the global, refines the block's last float with the
   parameter block's own float (the hero's own float only when the global allows it) and
   hands the block to the object's own refresh, which then runs the five owner helpers.
   The retail reaches the blend table through $gp, so this body needs the small-data
   profile (-G8, from this file's name). */
void hero_refresh_linked_object(char *object)
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
    cam_follow_update(self);
    cam_follow_update_collision(self);
    cam_follow_run_frame((int)self);
    weapon_reset_view_state(self);
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

extern int tracked_moby_get_flag(void *);
extern int tracked_moby_is_active(void);
extern int global_object_is_busy(void);
extern int global_object_get_flag(void);
extern void vec_clear_or_compute(void *, void *);
extern void cam_clamp_segment_by_collision(void *, void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern void mat_build_rotation_toward_vector(void *, void *, void *, int, float);

extern Rec_42A698 *D_L00_001B1844;
extern float D_L00_001B1644 __attribute__((sda));
extern float D_L00_001B1648 __attribute__((sda));

/* Works out the object's position and facing from the hero and the model, then nudges its position gradually toward the new spot. */
void moby_update_follow_position(Self_42A698 *self)
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
    if (tracked_moby_get_flag(self) != 0 || global_object_get_flag() != 0) {
        qcopy(baseRow, entity->model->mE0);
    } else {
        vec_clear_or_compute(self->m30, baseRow);
    }
    position = self->m30;
    if (tracked_moby_is_active() != 0 || global_object_is_busy() != 0) {
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
    mat_build_rotation_toward_vector(entity->v60, entity->v60, modelRow, 0, 0.125f);
    FastVecScale(l2, l2, -1.0f);
    dot = FastVecDot(l2, entity->v60);
    FastVecScale(l3, entity->v60, dot);
    FastVecSub(l4, l2, l3);
    vec_scale_to_length(l3, l3, entity->f34);
    vec_scale_to_length(l6, l4, entity->f30);
    FastVecAdd((char *)l6, (char *)l3, (char *)l6);
    FastVecAdd((char *)l7, (char *)l1, (char *)l6);
    cam_clamp_segment_by_collision(self, l8, l1, l7);
    lerp_vector(position, position, l8, 0.1f);
}

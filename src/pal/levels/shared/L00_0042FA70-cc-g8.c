#include "names.h"
/* func_PAL_L00_0042FA70, the PAL copy of func_L00_0042A520: the same C, where scale D_L00_001B164C. */
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x10];
    float m10[4];
    char pad20[0xC0 - 0x20];
    float mC0[4];
    char padD0[0x10];
    float mE0[4];
} Model_42A520;

typedef struct {
    char pad0[0x20];
    Model_42A520 *model;
    int f24;
    float f28;
    float f2C;
    float f30;
    float f34;
    char pad38[0x60 - 0x38];
    float v60[4];
} Ent_42A520;

typedef struct {
    char pad0[0x1C];
    Ent_42A520 *ent;
} Rec_42A520;

typedef struct {
    float m0[4];
    float m10[4];
    float m20[4];
    float m30[4];
    char pad40[0x84 - 0x40];
    short idx;
} Self_42A520;

extern float math_fabs(float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern Rec_42A520 *g_camera_def_table;
extern float g_cam_trigger_model_param_a __attribute__((sda));
extern float g_cam_trigger_model_param_b __attribute__((sda));
extern int g_cam_trigger_model_flags __attribute__((sda));

/* Builds the camera for a trigger model from two scale parameters and the model's axes (PAL copy). */
void cam_set_from_trigger_model_pal(Self_42A520 *self)
{
    float side[4];
    float up[4];
    float sum[4];
    float axis[4];
    Ent_42A520 *ent;
    Model_42A520 *model;

    ent = g_camera_def_table[self->idx].ent;
    ent->f28 = g_cam_trigger_model_param_a;
    ent->f2C = g_cam_trigger_model_param_b;
    ent->f30 = math_fabs(g_cam_trigger_model_param_a);
    ent->f34 = g_cam_trigger_model_param_b;
    model = ent->model;
    *(TI128 *)ent->v60 = *(TI128 *)model->mE0;
    vec_scale_to_length(side, model->mC0, ent->f28);
    vec_scale_to_length(up, ent->model->mE0, ent->f2C);
    FastVecAdd(sum, up, side);
    FastVecAdd(self->m30, sum, ent->model->m10);
    FastVecAdd(sum, self->m30, side);
    *(TI128 *)axis = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    FastVecSub(self->m0, self->m30, sum);
    vec_scale_to_length(self->m0, self->m0, 1.0f);
    FastVecCross(self->m10, self->m0, axis);
    vec_scale_to_length(self->m10, self->m10, 1.0f);
    FastVecCross(self->m20, self->m10, self->m0);
    ent->f24 = (((int)(g_cam_trigger_model_flags) * 5 + 2) / 6);
}

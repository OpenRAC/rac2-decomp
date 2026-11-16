#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern void moby_set_state(void *, int, int);
extern float math_fabs(float);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
typedef struct {
    char pad0[0x20];
    char x20[0x3C];
    int flags;
    int index;
    float t;
    float angle;
    char pad6c[8];
    float lx;
    float ly;
    float lz;
    int slot;
} State;
typedef struct {
    char pad0[0x10];
    float pos[4];
    unsigned char kind;
    char pad21[0x43];
    int update;
    State *state;
    char pad6c[0x84];
    float vel[4];
} Actor;
extern int PlayMobySound(int, int, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void func_PAL_L02_003EFD50();
extern char g_sound_state[];
extern char *g_matrix_l02_record_table;
extern float g_platform_rider_amplitude __attribute__((sda));
extern float g_platform_rider_angle_speed __attribute__((sda));

void func_PAL_L02_003EFAA0(Actor *arg0) {
    State *state = arg0->state;
    float pos[4];
    float vel[4];
    float tmp[4];
    float tmp2[4];
    char *rec;
    TI128 t;

    *(TI128 *)pos = *(TI128 *)arg0->pos;
    *(TI128 *)vel = *(TI128 *)arg0->vel;
    switch (arg0->kind) {
    case 0:
        if (state->index == -1) {
            moby_set_state(arg0, 3, -1);
            return;
        }
        if (math_fabs(*(float *)((char *)((state->index << 7) + (int)g_matrix_l02_record_table) + 0x28) - 2.0f) < 0.01f) {
            arg0->update = (int)func_PAL_L02_003EFD50;
            return;
        }
        state->flags |= 0x10;
        FastVecSub(tmp, arg0->pos, g_matrix_l02_record_table + (state->index << 7) + 0x30);
        matrix_mul_vec3(tmp, tmp, g_matrix_l02_record_table + (state->index << 7) + 0x40);
        state->angle = state->t * 6.2831855f - 3.1415927f;
        state->lx = tmp[0];
        state->lz = tmp[2];
        state->slot = -1;
        moby_set_state(arg0, 2, -1);
        break;
    case 2:
        state->angle = FastAddRotations(state->angle, g_platform_rider_angle_speed * 0.0003490659f);
        state->ly = g_platform_rider_amplitude * math_fast_sin_or_cos_b(state->angle);
        rec = g_sound_state + state->slot * 0x70;
        if (*(int *)(rec + 0x88) != (int)arg0 || *(unsigned char *)(rec + 0x74) == 0)
            state->slot = PlayMobySound(0, 4, arg0);
        *(TI128 *)tmp2 = 0;
        tmp2[0] = state->lx;
        tmp2[1] = state->ly;
        tmp2[2] = state->lz;
        tmp2[3] = 1.0f;
        t = *(TI128 *)tmp2;
        *(TI128 *)tmp = t;
        transform_vector(arg0->pos, tmp, g_matrix_l02_record_table + (state->index << 7));
        break;
    }
    FastVecSub(tmp, arg0->pos, pos);
    mat_combine_and_store(state->x20, tmp, vel, arg0->vel);
}

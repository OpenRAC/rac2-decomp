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
    float phase;
    float angle;
    char pad6c[8];
    float local_x;
    float local_y;
    float local_z;
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
extern void elevator_l02_l02_update_pal();
extern char g_sound_state[];
extern char *g_matrix_l02_record_table;
extern float g_platform_rider_amplitude __attribute__((sda));
extern float g_platform_rider_angle_speed __attribute__((sda));

/* Attaches a rider moby to a moving platform surface and bobs it up and down on it (PAL). */
void platform_rider_update_pal(Actor *moby) {
    State *state = moby->state;
    float pos[4];
    float vel[4];
    float offset[4];
    float local_point[4];
    char *sound_slot;
    TI128 local_quad;

    *(TI128 *)pos = *(TI128 *)moby->pos;
    *(TI128 *)vel = *(TI128 *)moby->vel;
    switch (moby->kind) {
    case 0:
        if (state->index == -1) {
            moby_set_state(moby, 3, -1);
            return;
        }
        if (math_fabs(*(float *)((char *)((state->index << 7) + (int)g_matrix_l02_record_table) + 0x28) - 2.0f) < 0.01f) {
            moby->update = (int)elevator_l02_l02_update_pal;
            return;
        }
        state->flags |= 0x10;
        FastVecSub(offset, moby->pos, g_matrix_l02_record_table + (state->index << 7) + 0x30);
        matrix_mul_vec3(offset, offset, g_matrix_l02_record_table + (state->index << 7) + 0x40);
        state->angle = state->phase * 6.2831855f - 3.1415927f;
        state->local_x = offset[0];
        state->local_z = offset[2];
        state->slot = -1;
        moby_set_state(moby, 2, -1);
        break;
    case 2:
        state->angle = FastAddRotations(state->angle, g_platform_rider_angle_speed * 0.0003490659f);
        state->local_y = g_platform_rider_amplitude * math_fast_sin_or_cos_b(state->angle);
        sound_slot = g_sound_state + state->slot * 0x70;
        if (*(int *)(sound_slot + 0x88) != (int)moby || *(unsigned char *)(sound_slot + 0x74) == 0)
            state->slot = PlayMobySound(0, 4, moby);
        *(TI128 *)local_point = 0;
        local_point[0] = state->local_x;
        local_point[1] = state->local_y;
        local_point[2] = state->local_z;
        local_point[3] = 1.0f;
        local_quad = *(TI128 *)local_point;
        *(TI128 *)offset = local_quad;
        transform_vector(moby->pos, offset, g_matrix_l02_record_table + (state->index << 7));
        break;
    }
    FastVecSub(offset, moby->pos, pos);
    mat_combine_and_store(state->x20, offset, vel, moby->vel);
}

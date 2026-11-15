#include "common.h"

typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
extern int D_L05_00221D94[];
extern int g_current_map_index MACRO_ADDR;
extern u8 D_0019B2E8[];
extern char *D_L05_001B251C;
extern float D_L05_001B1680 __attribute__((sda));
extern float D_L05_001B1688 __attribute__((sda));
extern float D_L05_001B168C __attribute__((sda));
extern float D_L05_001B1690 __attribute__((sda));
extern float D_L05_001B1694 __attribute__((sda));
extern float D_L05_001B1698 __attribute__((sda));
extern float D_L05_001B169C __attribute__((sda));
extern float D_L05_001B16D4 __attribute__((sda));
extern float D_L05_001B16D8 __attribute__((sda));
extern float D_L05_001B16DC __attribute__((sda));
extern float D_L05_001B16E0 __attribute__((sda));
extern float D_L05_001B16E4 __attribute__((sda));
extern float D_L05_001B16E8 __attribute__((sda));
extern float D_L05_001B16EC __attribute__((sda));
extern float D_L05_001B16F0 __attribute__((sda));
extern float D_L05_001B16F4 __attribute__((sda));
extern float D_L05_001B16F8 __attribute__((sda));
extern float D_L05_001B16FC __attribute__((sda));
extern float D_L05_001B1704 __attribute__((sda));
extern float D_L05_001B170C __attribute__((sda));
extern void *D_L05_001B1728 __attribute__((sda));
extern void moby_mark_spawned(void *);
extern void euler_rotation_basis(void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void mat_transform_via_copy(void *, void *);
extern char *stream_spawn_piece(void *, void *, float, float);
extern float math_step_spring_damper_clamped(float *, float, float, float, float, float);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
/* The registered entry includes its measured pre-prologue F1 load. */
extern void gfx_draw_scrolling_stream_layers(void *);

typedef union { float f[0x40]; int i[0x40]; u16 uh[0x80]; } Fields;

void func_PAL_L05_00430828(u8 *actor)
{
    Vector position, step, rotation;
    u8 *state = *(u8 **)(actor + 0x68);
    if (D_L05_00221D94[0] != 0 || (D_0019B2E8[actor[0xB0] + (g_current_map_index << 4)] & 0x80)) {
        moby_mark_spawned(actor);
        return;
    }
    if (actor[0x20] == 0) {
        float span;
        float phase = 0.0f;
        ((Fields *)actor)->uh[0x34 / 2] |= 0x41;
        euler_rotation_basis(actor + 0xC0, actor + 0xF0);
        actor[0x30] = 0xFF;
        actor[0x20] = 1;
        ((Fields *)actor)->f[0x2C / 4] = *(float *)(*(char **)(actor + 0x24) + 0x24) * (D_L05_001B1680 * D_L05_001B1688);
        span = D_L05_001B169C;
        span *= 6.0f;
        D_L05_001B16FC = D_L05_001B16F8 = D_L05_001B16E4 = D_L05_001B1690 = 0.0f;
        D_L05_001B16E8 = D_L05_001B16D4 = D_L05_001B170C = D_L05_001B1704 = 0.0f;
        ((Fields *)state)->f[0x20 / 4] = span;
        FastVecScale(&position, actor + 0xC0, span);
        FastVecAdd(&position, &position, actor + 0x10);
        {
            float *head = (float *)(state + 0x24);
            head[0] = position.f[0];
            head[1] = position.f[1];
            head[2] = position.f[2];
        }
        span *= 0.14285715f;
        FastVecScale(&step, actor + 0xC0, -span);
        mat_transform_via_copy(&rotation, actor + 0xC0);
        {
        char **child = (char **)state;
        int i;
        for (i = 6; i >= 0; i--, child++) {
            *child = stream_spawn_piece(&position, &rotation, D_L05_001B1680, phase);
            phase += span;
            FastVecAdd(&position, &position, &step);
        }
        }
        D_L05_001B1728 = actor;
    }
    {
    int j;
    for (j = 0; j < 7; j++) {
        u8 *object = ((u8 **)state)[j];
        if (object != 0) {
            float amount = D_L05_001B168C * 0.020000001f;
            float *pos = (float *)(object + 0x10);
            u8 *objectState;
            amount += amount;
            FastVecScale(&position, actor + 0xC0, -amount);
            FastVecAdd(pos, pos, &position);
            objectState = *(u8 **)(object + 0x68);
            ((Fields *)objectState)->f[0x10 / 4] += amount;
            if (((Fields *)state)->f[0x20 / 4] <= ((Fields *)objectState)->f[0x10 / 4]) {
                float *base = (float *)(state + 0x24);
                pos[0] = base[0];
                pos[1] = base[1];
                pos[2] = base[2];
                pos[3] = 0;
                ((Fields *)objectState)->i[0x10 / 4] = 0;
            }
        }
    }
    }
    if (*(int *)(*(char **)(D_L05_001B251C + (((Fields *)state)->i[0x1C / 4] << 8) + 0x68) + 0x34) != 0) {
        D_L05_001B168C = math_step_spring_damper_clamped(&D_L05_001B1690, D_L05_001B168C, D_L05_001B1698, 0.02f, 0.2f, 0.0f);
        D_L05_001B16D8 = math_step_spring_damper_clamped(&D_L05_001B16E4, D_L05_001B16D8, D_L05_001B16E0, 0.02f, 0.2f, 0.0f);
        D_L05_001B16EC = math_step_spring_damper_clamped(&D_L05_001B16F8, D_L05_001B16EC, D_L05_001B16F4, 0.02f, 0.2f, 0.0f);
    } else {
        D_L05_001B168C = math_step_spring_damper_clamped(&D_L05_001B1690, D_L05_001B168C, D_L05_001B1694, 0.02f, 0.2f, 0.0f);
        D_L05_001B16D8 = math_step_spring_damper_clamped(&D_L05_001B16E4, D_L05_001B16D8, D_L05_001B16DC, 0.02f, 0.2f, 0.0f);
        D_L05_001B16EC = math_step_spring_damper_clamped(&D_L05_001B16F8, D_L05_001B16EC, D_L05_001B16F0, 0.02f, 0.2f, 0.0f);
    }
    gfx_add_draw_callback_first(gfx_draw_scrolling_stream_layers, actor);
}

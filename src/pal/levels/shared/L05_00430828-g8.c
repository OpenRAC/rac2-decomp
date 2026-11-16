#include "common.h"

typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
extern int g_stream_scroll_flags[];
extern int g_current_map_index MACRO_ADDR;
extern u8 g_moby_group_flags[];
extern char *g_feltzin_target_mobys;
extern float g_stream_ring_radius_a __attribute__((sda));
extern float g_stream_speed_scale __attribute__((sda));
extern float g_stream_speed_current __attribute__((sda));
extern float g_stream_speed_velocity __attribute__((sda));
extern float g_stream_speed_target_a __attribute__((sda));
extern float g_stream_speed_target_b __attribute__((sda));
extern float g_stream_span_a __attribute__((sda));
extern float g_stream_scroll_u_a __attribute__((sda));
extern float g_stream_scroll_u_speed __attribute__((sda));
extern float g_stream_scroll_u_target_a __attribute__((sda));
extern float g_stream_scroll_u_target_b __attribute__((sda));
extern float g_stream_scroll_u_velocity __attribute__((sda));
extern float g_stream_scroll_v_a __attribute__((sda));
extern float g_stream_scroll_v_speed __attribute__((sda));
extern float g_stream_scroll_v_target_a __attribute__((sda));
extern float g_stream_scroll_v_target_b __attribute__((sda));
extern float g_stream_scroll_v_velocity __attribute__((sda));
extern float g_stream_scroll_w_a __attribute__((sda));
extern float g_stream_scroll_x_a __attribute__((sda));
extern float g_stream_scroll_y_a __attribute__((sda));
extern void *g_scrolling_stream_actor __attribute__((sda));
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

/* Updates a stream of seven moving pieces that slide along a line and wrap around to the start, and draws them (PAL: 50 Hz). */
void scrolling_stream_update_pal(u8 *actor)
{
    Vector position, step, rotation;
    u8 *state = *(u8 **)(actor + 0x68);
    if (g_stream_scroll_flags[0] != 0 || (g_moby_group_flags[actor[0xB0] + (g_current_map_index << 4)] & 0x80)) {
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
        ((Fields *)actor)->f[0x2C / 4] = *(float *)(*(char **)(actor + 0x24) + 0x24) * (g_stream_ring_radius_a * g_stream_speed_scale);
        span = g_stream_span_a;
        span *= 6.0f;
        g_stream_scroll_w_a = g_stream_scroll_v_velocity = g_stream_scroll_u_velocity = g_stream_speed_velocity = 0.0f;
        g_stream_scroll_v_a = g_stream_scroll_u_a = g_stream_scroll_y_a = g_stream_scroll_x_a = 0.0f;
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
            *child = stream_spawn_piece(&position, &rotation, g_stream_ring_radius_a, phase);
            phase += span;
            FastVecAdd(&position, &position, &step);
        }
        }
        g_scrolling_stream_actor = actor;
    }
    {
    int j;
    for (j = 0; j < 7; j++) {
        u8 *object = ((u8 **)state)[j];
        if (object != 0) {
            float amount = g_stream_speed_current * 0.020000001f;
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
    if (*(int *)(*(char **)(g_feltzin_target_mobys + (((Fields *)state)->i[0x1C / 4] << 8) + 0x68) + 0x34) != 0) {
        g_stream_speed_current = math_step_spring_damper_clamped(&g_stream_speed_velocity, g_stream_speed_current, g_stream_speed_target_b, 0.02f, 0.2f, 0.0f);
        g_stream_scroll_u_speed = math_step_spring_damper_clamped(&g_stream_scroll_u_velocity, g_stream_scroll_u_speed, g_stream_scroll_u_target_b, 0.02f, 0.2f, 0.0f);
        g_stream_scroll_v_speed = math_step_spring_damper_clamped(&g_stream_scroll_v_velocity, g_stream_scroll_v_speed, g_stream_scroll_v_target_b, 0.02f, 0.2f, 0.0f);
    } else {
        g_stream_speed_current = math_step_spring_damper_clamped(&g_stream_speed_velocity, g_stream_speed_current, g_stream_speed_target_a, 0.02f, 0.2f, 0.0f);
        g_stream_scroll_u_speed = math_step_spring_damper_clamped(&g_stream_scroll_u_velocity, g_stream_scroll_u_speed, g_stream_scroll_u_target_a, 0.02f, 0.2f, 0.0f);
        g_stream_scroll_v_speed = math_step_spring_damper_clamped(&g_stream_scroll_v_velocity, g_stream_scroll_v_speed, g_stream_scroll_v_target_a, 0.02f, 0.2f, 0.0f);
    }
    gfx_add_draw_callback_first(gfx_draw_scrolling_stream_layers, actor);
}

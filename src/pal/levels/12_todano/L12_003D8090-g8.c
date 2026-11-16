#include "include_asm.h"

#include "common.h"
extern float math_random_angle(void);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);
extern void moby_set_state(char *, int, int);
extern void *part_spawn_object_following_effect(void *, char *, int, float, int, int, float, int, int, int);
extern int flag_is_third_pending_set(char *);
extern int PlayMobySound(int, int, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *g_platform_actor_ref[3] __attribute__((sda));
typedef struct { unsigned short value; } FlagA180;
extern FlagA180 g_tether_flag_state NOT_SDA;
extern float g_tether_anchor_max_position __attribute__((sda));
extern float g_tether_anchor_force __attribute__((sda));
extern float g_tether_anchor_spring __attribute__((sda));
extern float g_tether_anchor_damping __attribute__((sda));
typedef struct { char pad[0x78]; int color; } ActorA180;
typedef int QuadA180 __attribute__((mode(TI)));
typedef struct { float origin[4]; float position, velocity, angle; } StateA180;

/* Updates a tether anchor platform: pulses its glow, then when the tether hits it, pushes it out along its axis like a spring until it settles. */
void todano_tether_anchor_update(char *moby) {
    StateA180 *anchor = *(StateA180 **)(moby + 0x68);
    QuadA180 vector;
    int color;
    float direction;

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        anchor->angle = math_random_angle();
        qcopy(anchor, moby + 0x10);
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        vector = 0;
        ((float *)&vector)[1] = -1.25f;
        ((float *)&vector)[2] = -2.0f;
        anchor->angle = FastAddRotations(anchor->angle, 0.062831864f);
        color = FloatToInt((math_fast_sin_or_cos_b(anchor->angle) * 4.0f - 3.0f) * 208.0f);
        if (color > 208) color = 208;
        else if (color < 80) color = 80;
        if (g_platform_actor_ref[0] != 0 && *(short *)(g_platform_actor_ref[0] + 0xAA) == 0xA61 && color >= 101) {
            part_spawn_object_following_effect(&vector, moby, 0x20000012, 3.15e+05f, -1, 0, 0.0f, 12, 0, -1);
            part_spawn_object_following_effect(&vector, moby, 0x20000012, 3.15e+05f, -1, 1, 0.0f, 12, 0, -1);
        }
        ((ActorA180 *)moby)->color = color | 0x800C0C00;
        if (flag_is_third_pending_set(moby)) {
            PlayMobySound(0, 0, moby);
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2: {
        float force, spring;
        ((ActorA180 *)moby)->color = 0xFF0CFF0C;
        force = g_tether_anchor_force * 0.00040000002f;
        spring = anchor->position * 0.00040000002f * g_tether_anchor_spring;
        force += spring;
        anchor->velocity += force;
        anchor->position += anchor->velocity;
        g_tether_flag_state.value = -1;
        if (anchor->position > g_tether_anchor_max_position) {
            anchor->position = g_tether_anchor_max_position;
            if (anchor->velocity > 0.020000001f) {
                anchor->velocity *= g_tether_anchor_damping;
            } else {
                anchor->velocity = 0;
                moby_set_state(moby, 3, -1);
            }
        }
        direction = -1.0f;
        if (*(short *)(moby + 0xAA) == 0xAAC) direction = 1.0f;
        vec_scale_to_length(moby + 0x10, moby + 0xC0, direction * anchor->position);
        FastVecAdd(moby + 0x10, moby + 0x10, anchor);
        break;
    }
    }
    return;
}

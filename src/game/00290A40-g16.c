/* The -G16 sibling of 00290A40.c: func_002914B8 reaches its sixteen-byte default
   ambient colour D_001A9190 through $gp, which needs -G16 and -Wa,-G16. */
#include "common.h"

typedef struct {
    float color[3];
    float spread;
    float position[3];
    float radius;
} DynamicLight;

typedef struct {
    char pad00[0x10];
    int state;
    char pad14[0xC];
    float position[4];
} DynamicLightState;

/* Prefix of the lighting environment; the object continues past flags. */
typedef struct {
    char pad000[0x340];
    float ambient[4];
    float direction[3];
    int flags;
} LightEnvironment;

extern float g_ambient_color[4] __attribute__((sda));
extern float g_rotation_base_angle __attribute__((nosda));
extern LightEnvironment g_light_environment;
extern DynamicLight g_dynamic_lights[8];
extern DynamicLightState g_dynamic_light_states[8];
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float fast_vec_dist(void *, void *);
extern float math_fabs(float);
extern void CreatePointLight(int);
extern void gfx_refresh_light_parts(int);

/* Resets the ambient colour and the directional light, then resynchronises every
   active dynamic light whose position or radius moved by more than one unit. */
void UpdateLightingEnvironment(void)
{
    float angle;
    int i;
    DynamicLight *light;
    DynamicLightState *state;

    qcopy(g_light_environment.ambient, g_ambient_color);
    angle = FastAddRotations(g_rotation_base_angle, -0.8f);
    g_light_environment.direction[0] = math_fast_sin_or_cos_a(angle) * 0.866f;
    g_light_environment.direction[1] = math_fast_sin_or_cos_b(angle) * 0.866f;
    g_light_environment.direction[2] = -0.5f;
    g_light_environment.flags = 0;
    for (i = 0; i < 8; i++) {
        light = &g_dynamic_lights[i];
        state = &g_dynamic_light_states[i];
        if (state->state != 0) {
            if (fast_vec_dist(light->position, state->position) > 1.0f
                || math_fabs(light->radius - state->position[3]) > 1.0f) {
                qcopy(state->position, light->position);
                if (state->state == 1) {
                    CreatePointLight(i);
                    state->state = 2;
                } else if (state->state == 2) {
                    gfx_refresh_light_parts(i);
                }
            }
        }
    }
}

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

extern float D_001A9190[4] __attribute__((sda));
extern float D_001B5358 __attribute__((nosda));
extern LightEnvironment D_001C2740;
extern DynamicLight D_001C2B40[8];
extern DynamicLightState D_001C2C40[8];
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282E48(void *, void *);
extern float func_00282C48(float);
extern void func_00291640(int);
extern void func_00291758(int);

/* Resets the ambient colour and the directional light, then resynchronises every
   active dynamic light whose position or radius moved by more than one unit. */
void func_002914B8(void)
{
    float angle;
    int i;
    DynamicLight *light;
    DynamicLightState *state;

    qcopy(D_001C2740.ambient, D_001A9190);
    angle = FastAddRotations(D_001B5358, -0.8f);
    D_001C2740.direction[0] = func_00283180(angle) * 0.866f;
    D_001C2740.direction[1] = func_00283198(angle) * 0.866f;
    D_001C2740.direction[2] = -0.5f;
    D_001C2740.flags = 0;
    for (i = 0; i < 8; i++) {
        light = &D_001C2B40[i];
        state = &D_001C2C40[i];
        if (state->state != 0) {
            if (fast_vec_dist(light->position, state->position) > 1.0f
                || func_00282C48(light->radius - state->position[3]) > 1.0f) {
                qcopy(state->position, light->position);
                if (state->state == 1) {
                    CreatePointLight(i);
                    state->state = 2;
                } else if (state->state == 2) {
                    func_00291758(i);
                }
            }
        }
    }
}

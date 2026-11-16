#include "common.h"

typedef struct {
    char pad000[0x140];
    float position[4];
    char pad150[0x40];
    char *active;
} CameraMotionState;
extern CameraMotionState g_scalar_transition_state;
extern char g_collision_position[];
typedef struct {
    char pad000[0x2290];
    void *collision;
} CameraCollisionContext;
extern CameraCollisionContext g_hero_state;
extern int g_cam_collision_point_mask __attribute__((sda));

extern void FastVecSub(void *out, void *a, void *b);
extern void FastVecAdd(void *out, void *a, void *b);
extern float FastVecLength(void *v);
extern void divide_vector_xyz(void *out, void *a, float f);
extern int FloatToInt(float f);
extern float IntToFloat(int v);
extern int coll_test_point(void *pos, int a, void *b, float step);

/* Moves the camera in radius-scaled steps and resolves up to six contacts per step.
 * Counterpart: RAC1 resolve_camera_movement_collisions. */
/* Moves the camera toward a target point in small steps and pushes it out of walls. */
void ResolveCameraMovementCollisions(char *pos, float step)
{
    float delta[4];
    float previous[4];
    char *cam_obj;
    float *src;
    int steps;
    int i;
    int j;

    cam_obj = g_scalar_transition_state.active;
    src = (float *)(cam_obj + 0x64);
    previous[0] = src[0];
    previous[1] = src[1];
    previous[2] = src[2];
    previous[3] = 0.0f;
    if (*(short *)(cam_obj + 0x8A) != 0) {
        qcopy(g_scalar_transition_state.position, pos);
        *(short *)(cam_obj + 0x8A) = 0;
        return;
    }
    FastVecSub(delta, pos, previous);
    steps = FloatToInt(FastVecLength(delta) / (step * 0.9f)) + 1;
    divide_vector_xyz(delta, delta, IntToFloat(steps));
    qcopy(pos, previous);
    for (j = 0; j < steps; j++) {
        FastVecAdd(pos, pos, delta);
        i = 0;
        while (i < 6 && coll_test_point(pos, g_cam_collision_point_mask, g_hero_state.collision, step) != 0) {
            qcopy(pos, g_collision_position);
            {
                char *hit = g_scalar_transition_state.active;
                if (*(unsigned char *)(hit + 0x89) == 0)
                    *(unsigned char *)(hit + 0x89) = 1;
            }
            i++;
        }
    }
    qcopy(g_scalar_transition_state.position, pos);
}

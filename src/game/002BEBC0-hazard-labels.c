#include "names.h"
/* func_002BEBC0: a particle that follows a joint of its parent object.  It grows or
 * shrinks its size towards 159600, spins, fades in and out between two limits (0.3
 * while at full size or growing, 0.15 while shrinking) and eases towards the camera.
 *
 * Retail keeps the branch label of the limit selection on its mtc1 hazard nop, so the
 * unit is built with -frac2-hazard-labels (docs/build/compiler-notes.md, "Labels on hazard
 * nops").  The two limit cases are separate statements: cross-jumping merges their
 * common compare, which keeps the two constant loads in their own arms. */
#include "common.h"

extern int FastDecTimer(void *timer);
extern void part_kill(void *particle);
extern int FloatToInt(float f);
extern void moby_transform_joint_to_world(void *object, int joint, void *out);
extern void FastVecSub(void *out, void *a, void *b);
extern void vec_scale_to_length(void *out, void *a, float scale);
extern void FastVecAdd(void *out, void *a, void *b);
extern char g_camera_eye_state[];
extern unsigned char *g_part_tex_joint_glow_table;

#define SIZE   (*(float *)(p + 0xC))
#define ALPHA  (*(float *)(q + 4))
#define SPIN   (*(float *)(q + 8))
#define FRAME  (*(short *)(q + 0xC))
#define JOINT  (*(short *)(q + 0xE))
#define SPEED  (*(float *)(q + 0x10))
#define EASE   (*(float *)(q + 0x14))

/* Updates a glowing particle that sticks to a joint of its parent object, pulsing in size and brightness until it fades away. */
void part_update_joint_glow(char *p)
{
    char *q;
    float pos[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));

    if (p == 0)
        return;
    q = p + 0x20;
    if (FastDecTimer(p + 0xA) || *(char **)q == 0 || *(signed char *)(*(char **)q + 0x20) < 0) {
        part_kill(p);
        return;
    }
    FRAME = (*(unsigned short *)(q + 0xC) + 1) & 15;
    if (SIZE < 159600.0f) {
        SIZE += 3989.999755859375f;
        if (SIZE > 159600.0f)
            SIZE = 159600.0f;
    } else if (SIZE > 159600.0f) {
        SIZE -= 15959.9990234375f;
        if (SIZE < 159600.0f)
            SIZE = 159600.0f;
    }
    SPIN += 0.001f;
    p[8] = FloatToInt(SPIN * 255.0f);
    p[2] = g_part_tex_joint_glow_table[FRAME];
    if (SIZE <= 159600.0f || SPEED > 0.0f)
        ALPHA += SPEED;
    if (SIZE <= 159600.0f) {
        if (ALPHA > 0.3f) {
            SPEED = -SPEED;
            ALPHA += SPEED;
        } else if (ALPHA < 0.0f) {
            part_kill(p);
            return;
        }
    } else {
        if (ALPHA > 0.15f) {
            SPEED = -SPEED;
            ALPHA += SPEED;
        } else if (ALPHA < 0.0f) {
            part_kill(p);
            return;
        }
    }
    *(int *)(p + 4) = (*(int *)(p + 4) & 0xFFFFFF) + (FloatToInt(ALPHA * 256.0f) << 24);
    EASE += (1.0f - EASE) * 0.175f;
    if (JOINT != -1) {
        moby_transform_joint_to_world(*(void **)q, JOINT, pos);
        FastVecSub(delta, g_camera_eye_state, pos);
        vec_scale_to_length(delta, delta, EASE);
        FastVecAdd(p + 0x10, pos, delta);
    }
}

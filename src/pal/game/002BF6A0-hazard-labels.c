#include "include_asm.h"

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

void func_PAL_002BF8A8(char *p)
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
        SIZE += 4788.0f;
        if (SIZE > 159600.0f)
            SIZE = 159600.0f;
    } else if (SIZE > 159600.0f) {
        SIZE -= 19152.0f;
        if (SIZE < 159600.0f)
            SIZE = 159600.0f;
    }
    SPIN += 0.0012f;
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
    EASE += (1.0f - EASE) * 0.21000001f;
    if (JOINT != -1) {
        moby_transform_joint_to_world(*(void **)q, JOINT, pos);
        FastVecSub(delta, g_camera_eye_state, pos);
        vec_scale_to_length(delta, delta, EASE);
        FastVecAdd(p + 0x10, pos, delta);
    }
}

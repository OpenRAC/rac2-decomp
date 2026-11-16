#include "include_asm.h"

#include "common.h"
extern int FastDecTimer(short *);
extern void part_kill(void *);
extern int FloatToInt(float);
extern void moby_transform_joint_to_world(void *,int,void *);
extern float g_camera_eye_state[];
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern unsigned char *g_part_tex_following_glow_table;

/* Follows an animated source joint, easing size and alpha toward their limits.
 * Corresponds to RAC1's update_animated_source_attached_fade_in_out_effect_particle. */
void part_update_joint_following_glow_pal(char *p)
{
    char *q;
    float a[4], b[4];
    float f;

    if (!p)
        return;
    q = p + 32;
    if (FastDecTimer((short *)(p + 10)) || !*(char **)q ||
        *(signed char *)(*(char **)q + 32) < 0) {
        part_kill(p);
        return;
    }
    *(short *)(q + 12) = (*(unsigned short *)(q + 12) + 1) & 15;
    if (*(float *)(p + 12) < 159600.0f) {
        *(float *)(p + 12) += 4788.0f;
        if (*(float *)(p + 12) > 159600.0f)
            *(float *)(p + 12) = 159600.0f;
    } else if (*(float *)(p + 12) > 159600.0f) {
        *(float *)(p + 12) -= 19152.0f;
        if (*(float *)(p + 12) < 159600.0f)
            *(float *)(p + 12) = 159600.0f;
    }
    *(float *)(q + 8) += 0.0012f;
    p[8] = FloatToInt(*(float *)(q + 8) * 255.0f);
    p[2] = g_part_tex_following_glow_table[*(short *)(q + 12)];
    if (*(float *)(p + 12) <= 159600.0f || *(float *)(q + 16) > 0.0f)
        *(float *)(q + 4) += *(float *)(q + 16);
    {
        float x;
        if (*(float *)(p + 12) <= 159600.0f) {
            x = *(float *)(q + 4);
            f = 0.3f;
        } else {
            x = *(float *)(q + 4);
            f = 0.15f;
        }
        if (!(f < x)) {
            if (x < 0.0f) {
                part_kill(p);
                return;
            }
        } else {
            *(float *)(q + 16) = -*(float *)(q + 16);
            *(float *)(q + 4) = x + *(float *)(q + 16);
        }
    }
    *(int *)(p + 4) = (*(int *)(p + 4) & 0xffffff) +
        (FloatToInt(*(float *)(q + 4) * 256.0f) << 24);
    *(float *)(q + 20) += (1.0f - *(float *)(q + 20)) * 0.21000001f;
    moby_transform_joint_to_world(*(void **)q, *(short *)(q + 14), a);
    FastVecSub(b, g_camera_eye_state, a);
    vec_scale_to_length(b, b, *(float *)(q + 20));
    FastVecAdd(p + 16, (char *)a, (char *)b);
}

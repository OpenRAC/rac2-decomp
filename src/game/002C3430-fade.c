#include "common.h"
extern int FastDecTimer(short *);
extern void part_kill(void *);
extern int FloatToInt(float);
extern void moby_transform_joint_to_world(void *,int,void *);
extern float g_camera_eye_state[];
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern unsigned char *D_001F2634;
/* Follows an animated source joint, easing size and alpha toward their limits.
 * Corresponds to RAC1's update_animated_source_attached_fade_in_out_effect_particle. */
/* Updates a glow that sticks to a joint of another object, grows and shrinks, and fades. */
void part_update_joint_following_glow(char *particle)
{
    char *motion;
    float jointPos[4], offset[4];
    float limit;

    if (!particle)
        return;
    motion = particle + 32;
    if (FastDecTimer((short *)(particle + 10)) || !*(char **)motion ||
        *(signed char *)(*(char **)motion + 32) < 0) {
        part_kill(particle);
        return;
    }
    *(short *)(motion + 12) = (*(unsigned short *)(motion + 12) + 1) & 15;
    if (*(float *)(particle + 12) < 159600.0f) {
        *(float *)(particle + 12) += 3989.999755859375f;
        if (*(float *)(particle + 12) > 159600.0f)
            *(float *)(particle + 12) = 159600.0f;
    } else if (*(float *)(particle + 12) > 159600.0f) {
        *(float *)(particle + 12) -= 15959.9990234375f;
        if (*(float *)(particle + 12) < 159600.0f)
            *(float *)(particle + 12) = 159600.0f;
    }
    *(float *)(motion + 8) += 0.001f;
    particle[8] = FloatToInt(*(float *)(motion + 8) * 255.0f);
    particle[2] = D_001F2634[*(short *)(motion + 12)];
    if (*(float *)(particle + 12) <= 159600.0f || *(float *)(motion + 16) > 0.0f)
        *(float *)(motion + 4) += *(float *)(motion + 16);
    {
        float size;
        if (*(float *)(particle + 12) <= 159600.0f) {
            size = *(float *)(motion + 4);
            limit = 0.3f;
        } else {
            size = *(float *)(motion + 4);
            limit = 0.15f;
        }
        if (!(limit < size)) {
            if (size < 0.0f) {
                part_kill(particle);
                return;
            }
        } else {
            *(float *)(motion + 16) = -*(float *)(motion + 16);
            *(float *)(motion + 4) = size + *(float *)(motion + 16);
        }
    }
    *(int *)(particle + 4) = (*(int *)(particle + 4) & 0xffffff) +
        (FloatToInt(*(float *)(motion + 4) * 256.0f) << 24);
    *(float *)(motion + 20) += (1.0f - *(float *)(motion + 20)) * 0.175f;
    moby_transform_joint_to_world(*(void **)motion, *(short *)(motion + 14), jointPos);
    FastVecSub(offset, g_camera_eye_state, jointPos);
    vec_scale_to_length(offset, offset, *(float *)(motion + 20));
    FastVecAdd(particle + 16, (char *)jointPos, (char *)offset);
}

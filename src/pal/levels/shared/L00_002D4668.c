#include "include_asm.h"

#include "common.h"
typedef int VectorWord4140 __attribute__((mode(TI)));
typedef union { VectorWord4140 q; float f[4]; } Vector4140;
typedef struct {
    unsigned char pad0[128];
    Vector4140 pos;
    Vector4140 rot;
    unsigned char pada0[96];
    Vector4140 f100;
    unsigned char pad110[64];
    Vector4140 f150;
    Vector4140 f160;
    unsigned char pad170[52];
    float f1a4;
    unsigned char pad1a8[110];
    short f216;
    unsigned char pad218[14];
    short f226;
    unsigned char pad228[276];
    int ground_platform;
    unsigned char pad340[14];
    short platform_timer;
    Vector4140 f350;
    Vector4140 f360;
    Vector4140 f370;
    unsigned char pad380[16];
    Vector4140 platform_delta;
    int platform;
    int platform_flags;
    unsigned char pad3a8[424];
    Vector4140 ledge_offset;
    unsigned char pad560[20];
    float ledge_angle;
    unsigned char pad578[16];
    int ledge_platform;
    unsigned char pad58c[7428];
    int f2290;
    int state;
    unsigned char pad2298[4];
    int state2;
    unsigned char pad22a0[21];
    unsigned char f22b5;
} Hero4140;
extern Hero4140 D_00189E20_4140;
extern f32 IntToFloat(int);
typedef struct {
    unsigned char pad0[60];
    int flags;
} PlatformObject;
extern PlatformObject *moby_get_private_value_2(int);
extern float FastVecLength(void *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int moby_transform_point_and_rotation_by_parent(int, int, void *, void *, void *, void *);
extern int moby_get_attachment_rotation_angles(int, int, void *, void *, void *, void *);
extern int coll_apply_push_to_object(int, int, void *, void *, void *, void *);
extern void vec_clear_128(void *);
extern float vec_length_xy(void *);
extern f32 ApproachValue(float *, float, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
typedef int V4_F6a70b950 __attribute__((mode(TI)));
extern void vec_fast_normalize_helper(char *a, int b, float f);

/* Carry the hero with the supporting platform, including ledge anchors,
 * rotation and the displacement retained while the hero leaves the platform.
 * Counterpart: RAC1 update_hero_attachment in hero_mapped_animations.c.
 */
void func_PAL_L00_002D4668(void)
{
    float local_pos[4], local_rot[4], delta[4], next[4];
    float hero_pos[4], hero_rot[4], anchor_pos[4], anchor_rot[4], anchor2_pos[4], anchor2_rot[4];
    float offset[4];
    float height, length;
    int mode = 0;
    float blend = 0.0f;
    float old_yaw = D_00189E20_4140.rot.f[2];
    PlatformObject *object;

    if (D_00189E20_4140.platform_timer == 0) {
        if (D_00189E20_4140.ground_platform) {
            mode = 1;
            if (D_00189E20_4140.platform != D_00189E20_4140.ground_platform)
                D_00189E20_4140.platform_flags &= ~1;
            D_00189E20_4140.platform = D_00189E20_4140.ground_platform;
        } else {
            D_00189E20_4140.platform = 0;
            D_00189E20_4140.platform_flags &= ~1;
            D_00189E20_4140.platform_flags &= ~2;
        }
    } else if (D_00189E20_4140.state == 27 && D_00189E20_4140.ledge_platform) {
        D_00189E20_4140.platform = D_00189E20_4140.ledge_platform;
        mode = 1;
    } else if (D_00189E20_4140.state2 == 3 && D_00189E20_4140.ledge_platform) {
        D_00189E20_4140.platform = D_00189E20_4140.ledge_platform;
        mode = 1;
    } else if (D_00189E20_4140.platform) {
        mode = 1;
        IntToFloat(100 - D_00189E20_4140.platform_timer);
        blend = D_00189E20_4140.platform_timer;
    } else {
        D_00189E20_4140.platform = 0;
        D_00189E20_4140.platform_flags &= ~1;
        D_00189E20_4140.platform_flags &= ~2;
    }

    if (!mode)
        return;
    object = moby_get_private_value_2(D_00189E20_4140.platform);
    if (!object)
        return;

    if (((D_00189E20_4140.state2 == 0 || D_00189E20_4140.state2 == 12) &&
         FastVecLength(&D_00189E20_4140.f160) == 0.0f &&
         D_00189E20_4140.platform_timer == 0 && D_00189E20_4140.f216 == 0) ||
        (unsigned)(D_00189E20_4140.state - 23) < 2) {
        if (((D_00189E20_4140.platform_flags ^ 1) & 1)) {
            if ((unsigned)(D_00189E20_4140.state - 23) < 2) {
                qcopy(delta, &D_00189E20_4140.ledge_offset);
                delta[0] += math_fast_sin_or_cos_a(FastAddRotations(D_00189E20_4140.ledge_angle,
                        3.1415925f)) * 0.45f;
                delta[1] += math_fast_sin_or_cos_b(FastAddRotations(D_00189E20_4140.ledge_angle,
                        3.1415925f)) * 0.45f;
                delta[2] -= -1.43f;
                moby_transform_point_and_rotation_by_parent(D_00189E20_4140.f2290, D_00189E20_4140.platform,
                        &D_00189E20_4140.ledge_offset, &D_00189E20_4140.rot, next, hero_pos);
                moby_transform_point_and_rotation_by_parent(D_00189E20_4140.f2290, D_00189E20_4140.platform, delta,
                        &D_00189E20_4140.rot, delta, hero_pos);
                moby_get_attachment_rotation_angles(D_00189E20_4140.f2290, D_00189E20_4140.platform,
                        &D_00189E20_4140.ledge_offset, &D_00189E20_4140.rot, &D_00189E20_4140.f350,
                        hero_pos);
                moby_get_attachment_rotation_angles(D_00189E20_4140.f2290, D_00189E20_4140.platform, delta,
                        &D_00189E20_4140.rot, &D_00189E20_4140.f370, hero_pos);
            } else if (object->flags & 4) {
                moby_get_attachment_rotation_angles(D_00189E20_4140.f2290, D_00189E20_4140.platform,
                        &D_00189E20_4140.pos, &D_00189E20_4140.rot, &D_00189E20_4140.f350, delta);
            } else {
                moby_transform_point_and_rotation_by_parent(D_00189E20_4140.f2290, D_00189E20_4140.platform,
                        &D_00189E20_4140.pos, &D_00189E20_4140.rot, next, hero_pos);
                moby_get_attachment_rotation_angles(D_00189E20_4140.f2290, D_00189E20_4140.platform, next, hero_pos,
                        &D_00189E20_4140.f350, delta);
            }
            D_00189E20_4140.platform_flags |= 1;
        }
    } else
        D_00189E20_4140.platform_flags &= ~1;

    if ((D_00189E20_4140.state2 == 0 || D_00189E20_4140.state2 == 12) && D_00189E20_4140.f1a4 == 0.0f &&
        D_00189E20_4140.platform_timer == 0) {
        if (!(D_00189E20_4140.platform_flags & 2)) {
            moby_get_attachment_rotation_angles(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.pos,
                    &D_00189E20_4140.rot, delta, &D_00189E20_4140.f360);
            D_00189E20_4140.platform_flags |= 2;
        }
    } else
        D_00189E20_4140.platform_flags &= ~2;

    if (D_00189E20_4140.platform_flags & 3)
        mode = 2;
    vec_clear_128(delta);
    vec_clear_128(next);

    if (blend != 0.0f) {
        int flags;
        float planar = vec_length_xy(&D_00189E20_4140.platform_delta);

        flags = object->flags;
        height = D_00189E20_4140.platform_delta.f[2];
        length = planar;
        if (!(flags & 2)) {
            float rate = 2.0f;

            if (flags & 16)
                rate = 20.0f;
            rate *= 0.00040000002f;
            ApproachValue(&height, 0.0f, blend * 0.010000001f);
            ApproachValue(&length, 0.0f, rate * blend);
            vec_fast_normalize_helper((char *)delta, (int)&D_00189E20_4140.platform_delta, length);
            delta[2] = height;
        } else if (D_00189E20_4140.platform) {
            moby_transform_point_and_rotation_by_parent(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.pos,
                    &D_00189E20_4140.rot, local_pos, local_rot);
            if (D_00189E20_4140.f226 == 0)
                D_00189E20_4140.rot.q = *(V4_F6a70b950 *)local_rot;
            FastVecSub(delta, local_pos, &D_00189E20_4140.pos);
            qcopy(&D_00189E20_4140.platform_delta, delta);
        } else
            qcopy(delta, &D_00189E20_4140.platform_delta);
        qcopy(next, delta);
    } else if (mode == 1) {
        moby_transform_point_and_rotation_by_parent(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.pos,
                &D_00189E20_4140.rot, local_pos, local_rot);
        if (D_00189E20_4140.f226 == 0)
            D_00189E20_4140.rot.q = *(V4_F6a70b950 *)local_rot;
        FastVecSub(delta, local_pos, &D_00189E20_4140.pos);
        qcopy(&D_00189E20_4140.platform_delta, delta);
    } else if (mode == 2) {
        moby_transform_point_and_rotation_by_parent(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.pos,
                &D_00189E20_4140.rot, hero_pos, hero_rot);
        coll_apply_push_to_object(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.f350,
                &D_00189E20_4140.f360, anchor_pos, anchor_rot);
        coll_apply_push_to_object(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.f370,
                &D_00189E20_4140.f360, anchor2_pos, anchor2_rot);
        if (D_00189E20_4140.f226 == 0) {
            if ((D_00189E20_4140.state == 1 || D_00189E20_4140.state == 29) &&
                D_00189E20_4140.f22b5)
                D_00189E20_4140.rot.f[2] = hero_rot[2];
            else
                D_00189E20_4140.rot.f[2] =
                    (D_00189E20_4140.platform_flags & 2) ? anchor_rot[2] : hero_rot[2];
        }
        if (D_00189E20_4140.platform_flags & 1) {
            if ((unsigned)(D_00189E20_4140.state - 23) < 2) {
                offset[0] = math_fast_sin_or_cos_a(D_00189E20_4140.ledge_angle) * 0.45f;
                offset[1] = math_fast_sin_or_cos_b(D_00189E20_4140.ledge_angle) * 0.45f;
                offset[2] = 0;
                FastVecAdd(offset, offset, anchor2_pos);
                offset[2] += -1.43f;
                FastVecSub(delta, hero_pos, &D_00189E20_4140.pos);
                qcopy(&D_00189E20_4140.ledge_offset, offset);
                D_00189E20_4140.ledge_angle = mat_fast_helper_a(anchor_pos[0] - anchor2_pos[0],
                        anchor_pos[1] - anchor2_pos[1]);
            } else {
                float distance;

                FastVecSub(delta, anchor_pos, &D_00189E20_4140.pos);
                distance = FastVecLength(delta);
                if (distance < 0.0001f) {
                    vec_clear_128(delta);
                    qcopy(&D_00189E20_4140.pos, anchor_pos);
                } else if (distance > 2.0f) {
                    vec_clear_128(delta);
                    D_00189E20_4140.platform_flags &= ~2;
                    D_00189E20_4140.platform_flags &= ~1;
                }
                FastVecAdd(&D_00189E20_4140.ledge_offset, &D_00189E20_4140.ledge_offset, delta);
                FastVecSub(offset, delta, &D_00189E20_4140.f150);
                if (FastVecLength(offset) > 0.1f)
                    D_00189E20_4140.platform_flags &= ~1;
            }
        } else {
            FastVecSub(delta, hero_pos, &D_00189E20_4140.pos);
            qcopy(next, delta);
        }
        qcopy(&D_00189E20_4140.platform_delta, delta);
    }

    FastVecAdd(&D_00189E20_4140.f100, &D_00189E20_4140.f100, delta);
    D_00189E20_4140.f100.f[3] = fast_subtract_rotations(D_00189E20_4140.rot.f[2], old_yaw);
}


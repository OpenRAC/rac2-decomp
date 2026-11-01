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
extern void func_00283CE0(int);
typedef struct {
    unsigned char pad0[60];
    int flags;
} PlatformObject;
extern PlatformObject *func_002AD0B0(int);
extern float func_00282DF0(void *);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002AD0E0(int, int, void *, void *, void *, void *);
extern int func_002AD5F8(int, int, void *, void *, void *, void *);
extern int func_002AD470(int, int, void *, void *, void *, void *);
extern void func_00282C88(void *);
extern float func_00282E20(void *);
extern void func_002AA2E8(float *, float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
typedef int V4_F6a70b950 __attribute__((mode(TI)));
extern void func_00282F70(char *a, int b, float f);

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
        func_00283CE0(100 - D_00189E20_4140.platform_timer);
        blend = D_00189E20_4140.platform_timer;
    } else {
        D_00189E20_4140.platform = 0;
        D_00189E20_4140.platform_flags &= ~1;
        D_00189E20_4140.platform_flags &= ~2;
    }

    if (!mode)
        return;
    object = func_002AD0B0(D_00189E20_4140.platform);
    if (!object)
        return;

    if (((D_00189E20_4140.state2 == 0 || D_00189E20_4140.state2 == 12) &&
         func_00282DF0(&D_00189E20_4140.f160) == 0.0f &&
         D_00189E20_4140.platform_timer == 0 && D_00189E20_4140.f216 == 0) ||
        (unsigned)(D_00189E20_4140.state - 23) < 2) {
        if (((D_00189E20_4140.platform_flags ^ 1) & 1)) {
            if ((unsigned)(D_00189E20_4140.state - 23) < 2) {
                qcopy(delta, &D_00189E20_4140.ledge_offset);
                delta[0] += func_00283180(func_00283B98(D_00189E20_4140.ledge_angle,
                        3.1415925f)) * 0.45f;
                delta[1] += func_00283198(func_00283B98(D_00189E20_4140.ledge_angle,
                        3.1415925f)) * 0.45f;
                delta[2] -= -1.43f;
                func_002AD0E0(D_00189E20_4140.f2290, D_00189E20_4140.platform,
                        &D_00189E20_4140.ledge_offset, &D_00189E20_4140.rot, next, hero_pos);
                func_002AD0E0(D_00189E20_4140.f2290, D_00189E20_4140.platform, delta,
                        &D_00189E20_4140.rot, delta, hero_pos);
                func_002AD5F8(D_00189E20_4140.f2290, D_00189E20_4140.platform,
                        &D_00189E20_4140.ledge_offset, &D_00189E20_4140.rot, &D_00189E20_4140.f350,
                        hero_pos);
                func_002AD5F8(D_00189E20_4140.f2290, D_00189E20_4140.platform, delta,
                        &D_00189E20_4140.rot, &D_00189E20_4140.f370, hero_pos);
            } else if (object->flags & 4) {
                func_002AD5F8(D_00189E20_4140.f2290, D_00189E20_4140.platform,
                        &D_00189E20_4140.pos, &D_00189E20_4140.rot, &D_00189E20_4140.f350, delta);
            } else {
                func_002AD0E0(D_00189E20_4140.f2290, D_00189E20_4140.platform,
                        &D_00189E20_4140.pos, &D_00189E20_4140.rot, next, hero_pos);
                func_002AD5F8(D_00189E20_4140.f2290, D_00189E20_4140.platform, next, hero_pos,
                        &D_00189E20_4140.f350, delta);
            }
            D_00189E20_4140.platform_flags |= 1;
        }
    } else
        D_00189E20_4140.platform_flags &= ~1;

    if ((D_00189E20_4140.state2 == 0 || D_00189E20_4140.state2 == 12) && D_00189E20_4140.f1a4 == 0.0f &&
        D_00189E20_4140.platform_timer == 0) {
        if (!(D_00189E20_4140.platform_flags & 2)) {
            func_002AD5F8(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.pos,
                    &D_00189E20_4140.rot, delta, &D_00189E20_4140.f360);
            D_00189E20_4140.platform_flags |= 2;
        }
    } else
        D_00189E20_4140.platform_flags &= ~2;

    if (D_00189E20_4140.platform_flags & 3)
        mode = 2;
    func_00282C88(delta);
    func_00282C88(next);

    if (blend != 0.0f) {
        int flags;
        float planar = func_00282E20(&D_00189E20_4140.platform_delta);

        flags = object->flags;
        height = D_00189E20_4140.platform_delta.f[2];
        length = planar;
        if (!(flags & 2)) {
            float rate = 2.0f;

            if (flags & 16)
                rate = 20.0f;
            rate *= 0.00040000002f;
            func_002AA2E8(&height, 0.0f, blend * 0.010000001f);
            func_002AA2E8(&length, 0.0f, rate * blend);
            func_00282F70((char *)delta, (int)&D_00189E20_4140.platform_delta, length);
            delta[2] = height;
        } else if (D_00189E20_4140.platform) {
            func_002AD0E0(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.pos,
                    &D_00189E20_4140.rot, local_pos, local_rot);
            if (D_00189E20_4140.f226 == 0)
                D_00189E20_4140.rot.q = *(V4_F6a70b950 *)local_rot;
            func_00282CF0(delta, local_pos, &D_00189E20_4140.pos);
            qcopy(&D_00189E20_4140.platform_delta, delta);
        } else
            qcopy(delta, &D_00189E20_4140.platform_delta);
        qcopy(next, delta);
    } else if (mode == 1) {
        func_002AD0E0(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.pos,
                &D_00189E20_4140.rot, local_pos, local_rot);
        if (D_00189E20_4140.f226 == 0)
            D_00189E20_4140.rot.q = *(V4_F6a70b950 *)local_rot;
        func_00282CF0(delta, local_pos, &D_00189E20_4140.pos);
        qcopy(&D_00189E20_4140.platform_delta, delta);
    } else if (mode == 2) {
        func_002AD0E0(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.pos,
                &D_00189E20_4140.rot, hero_pos, hero_rot);
        func_002AD470(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.f350,
                &D_00189E20_4140.f360, anchor_pos, anchor_rot);
        func_002AD470(D_00189E20_4140.f2290, D_00189E20_4140.platform, &D_00189E20_4140.f370,
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
                offset[0] = func_00283180(D_00189E20_4140.ledge_angle) * 0.45f;
                offset[1] = func_00283198(D_00189E20_4140.ledge_angle) * 0.45f;
                offset[2] = 0;
                func_00282CC0(offset, offset, anchor2_pos);
                offset[2] += -1.43f;
                func_00282CF0(delta, hero_pos, &D_00189E20_4140.pos);
                qcopy(&D_00189E20_4140.ledge_offset, offset);
                D_00189E20_4140.ledge_angle = func_00283248(anchor_pos[0] - anchor2_pos[0],
                        anchor_pos[1] - anchor2_pos[1]);
            } else {
                float distance;

                func_00282CF0(delta, anchor_pos, &D_00189E20_4140.pos);
                distance = func_00282DF0(delta);
                if (distance < 0.0001f) {
                    func_00282C88(delta);
                    qcopy(&D_00189E20_4140.pos, anchor_pos);
                } else if (distance > 2.0f) {
                    func_00282C88(delta);
                    D_00189E20_4140.platform_flags &= ~2;
                    D_00189E20_4140.platform_flags &= ~1;
                }
                func_00282CC0(&D_00189E20_4140.ledge_offset, &D_00189E20_4140.ledge_offset, delta);
                func_00282CF0(offset, delta, &D_00189E20_4140.f150);
                if (func_00282DF0(offset) > 0.1f)
                    D_00189E20_4140.platform_flags &= ~1;
            }
        } else {
            func_00282CF0(delta, hero_pos, &D_00189E20_4140.pos);
            qcopy(next, delta);
        }
        qcopy(&D_00189E20_4140.platform_delta, delta);
    }

    func_00282CC0(&D_00189E20_4140.f100, &D_00189E20_4140.f100, delta);
    D_00189E20_4140.f100.f[3] = func_00283BE0(D_00189E20_4140.rot.f[2], old_yaw);
}


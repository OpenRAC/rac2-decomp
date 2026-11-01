#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct {
    Vector previous, position, velocity;
    char *owner;
    int *ignore;
    int ignoreCount;
    float radius, friction, bounce;
    int flags, mask, response, surface, gravity;
    float maxTurn;
} CollisionQuery;
extern int D_L00_001A8FF4 MACRO_ADDR;
extern Vector D_L00_001BF240;
extern u16 D_L00_001B1FF0[] MACRO_ADDR;
extern void func_PAL_002A7E68(char *, int, int, int), func_002FE8D8(void *, float *);
extern void func_00282F20(void *, void *, float), func_00282DD8(void *, void *, void *);
extern float func_00282DB0(void *, void *), func_00283198(float), func_00283180(float);
extern void func_00282D30(void *, void *, float), func_00283958(void *, void *), func_00283738(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *), func_002FEE70(int, void *, void *), func_002FE880(void *, float *, float);
extern void func_00300190(void *, void *), func_00300248(int, int);
extern int func_002FE9D0(CollisionQuery *), func_00300540(int);
extern void func_002ACB48(float *, float);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern float func_002A7878(float, float);
extern void func_0030E8A8(char *), func_PAL_L00_0039BE70(char *), func_002FEE50(int), func_002ACAD0(int, u16 *), func_0029F338(void *);
extern void func_00283658(void *, void *), func_002AB6D8(float *, float *), func_002833F0(void *, void *);
extern int func_002AD0E0(int, int, void *, void *, void *, void *);

/* Steers a moving projectile, resolves its collision, then follows a struck actor. */
void func_PAL_L00_0039B4C8(char *actor) {
    /* The 96-byte collision query and following attachment transform have
     * disjoint lifetimes and occupy the same measured stack workspace. */
    struct {
        Vector oldPosition, desired, forward, quaternion, axis;
        Vector rotation[3];
        int ignore[2];
        union {
            CollisionQuery query;
            struct { Vector transform[4], angles, adjusted; } attachment;
        } phase;
        Vector scatter;
    } scratch;
    char *state = *(char **)(actor + 0x68);
    ++*(int *)(state + 0x3C);
    switch (((u8 *)actor)[0x20]) {
    case 0:
        actor[0x20] = 1;
        if (((u8 *)actor)[0x43]) func_PAL_002A7E68(actor, 0, 0, 0);
        *(int *)(actor + 0x98) = 0;
        /* fall through */
    case 1: {
        int collision;
        char *hit;
        float halfAngle;
        short type;
        func_002FE8D8(actor + 0x10, scratch.desired.f);
        func_00282F20(&scratch.forward, actor + 0xE0, 1.0f);
        func_00282DD8(&scratch.axis, &scratch.forward, &scratch.desired);
        halfAngle = func_00282DB0(&scratch.forward, &scratch.desired) * 0.5f;
        func_00282D30(&scratch.quaternion, &scratch.axis, func_00283198(halfAngle));
        scratch.quaternion.f[3] = func_00283180(halfAngle);
        func_00283958(&scratch.quaternion, scratch.rotation);
        func_00283738(actor + 0xC0, scratch.rotation, actor + 0xC0);
        qcopy(&scratch.oldPosition, (actor + 0x10));
        func_00282CC0(actor + 0x10, actor + 0x10, state + 0x10);
        func_002FEE70(*(int *)(state + 0x20), state + 0x10, 0);
        func_002FE880(actor + 0x10, (float *)(state + 0x10), 0.0044f);
        func_00300190(actor + 0x10, actor + 0x10);
        func_00300248((int)(state + 0x10), (int)(state + 0x10));
        scratch.ignore[0] = 0; scratch.ignore[1] = 0x232;
        qcopy(&scratch.phase.query.previous, &scratch.oldPosition);
        qcopy(&scratch.phase.query.position, (actor + 0x10));
        qcopy(&scratch.phase.query.velocity, (state + 0x10));
        scratch.phase.query.owner = actor; scratch.phase.query.ignore = scratch.ignore; scratch.phase.query.ignoreCount = 2;
        scratch.phase.query.radius = 0.2f; scratch.phase.query.friction = 0.45f; scratch.phase.query.bounce = 0.5555556f;
        scratch.phase.query.flags = 0; scratch.phase.query.mask = 0; scratch.phase.query.gravity = 1; scratch.phase.query.response = 1; scratch.phase.query.maxTurn = 0.174f;
        collision = func_002FE9D0(&scratch.phase.query);
        qcopy((actor + 0x10), &scratch.phase.query.position);
        qcopy((state + 0x10), &scratch.phase.query.velocity);
        if (D_L00_001A8FF4 && *(float *)(actor + 0x18) < 462.43f) {
            func_002ACB48(scratch.scatter.f, 0.6f);
            func_PAL_002AC718(actor, &scratch.scatter, 0, 0.0f, 0.0f, 0, 0, 0,
                         4.0f, 3.0f, 9.0f, 1.0f, 2, 12.0f, 1, 1, -1, 0, 0x810001);
            actor[0x20] = 6;
        }
        if (collision != 2) break;
        hit = scratch.phase.query.owner;
        if (hit) {
            type = *(short *)(hit + 0xAA);
            if (type == 0xCB || type == 0x1366 || type == 0x1367) goto accelerate;
            *(char **)(state + 0x38) = hit;
        }
        {
            func_00282D30(&scratch.desired, &D_L00_001BF240, 0.0009765625f);
            func_00282F20(&scratch.desired, &scratch.desired, 1);
            func_00282F20(&scratch.forward, actor + 0xE0, 1);
            func_00282DD8(&scratch.axis, &scratch.forward, &scratch.desired);
            halfAngle = func_00282DB0(&scratch.forward, &scratch.desired) * 0.5f;
            func_00282D30(&scratch.quaternion, &scratch.axis, func_00283198(halfAngle));
            scratch.quaternion.f[3] = func_00283180(halfAngle);
            func_00283958(&scratch.quaternion, scratch.rotation);
            func_00283738(actor + 0xC0, scratch.rotation, actor + 0xC0);
            actor[0x20] = collision;
            if (((u8 *)actor)[0x43] != 1) func_PAL_002A7E68(actor, 1, 0, 8);
            *(int *)(actor + 0x98) = *(int *)(*(char **)(actor + 0x24) + 0x10);
        }
        goto response_done;
accelerate:
        func_00282D30(state + 0x10, state + 0x10, 1.1f);
response_done:
        if (func_00300540(scratch.phase.query.surface)) {
            func_002ACB48(scratch.scatter.f, 0.6f);
            func_PAL_002AC718(actor, &scratch.scatter, 0, 0.0f, 0.0f, 0, 0, 0,
                         4.0f, 3.0f, 9.0f, 1.0f, 2, 12.0f, 1, 1, -1, 0, 0x810001);
            actor[0x20] = 6;
        }
        break;
    }
    case 2: actor[0x20] = 3; break;
    case 3:
        if (((u8 *)actor)[0x60] & 2) {
            if (((u8 *)actor)[0x43] != 2) func_PAL_002A7E68(actor, 2, 0, 8);
            *(float *)(actor + 0x48) = func_002A7878(0.7f, 1.05f);
        }
        func_0030E8A8(actor); func_PAL_L00_0039BE70(actor);
        break;
    case 5: actor[0x20] = 4; break;
    case 4:
        *(float *)(actor + 0x2C) -= *(float *)(actor + 0x2C) * 0.024f;
        if (*(float *)(actor + 0x2C) < *(float *)(*(char **)(actor + 0x24) + 0x24) * 0.1f) actor[0x20] = 6;
        break;
    case 6:
        func_002FEE50(*(int *)(state + 0x20));
        if (!*(int *)(state + 0x40)) func_002ACAD0((int)actor, D_L00_001B1FF0);
        func_0029F338(actor);
        return;
    }
    if ((u32)(((u8 *)actor)[0x20] - 2) < 3 && *(char **)(state + 0x38)) {
        func_00283658(scratch.phase.attachment.transform, actor + 0xC0);
        func_002AB6D8((float *)scratch.phase.attachment.transform, scratch.phase.attachment.angles.f);
        if (func_002AD0E0((int)actor, *(int *)(state + 0x38), actor + 0x10, &scratch.phase.attachment.angles, actor + 0x10, &scratch.phase.attachment.adjusted))
            func_002833F0(actor + 0xC0, &scratch.phase.attachment.adjusted);
    }
}

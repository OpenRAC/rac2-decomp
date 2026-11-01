#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void func_PAL_L00_002D4668(u32, void *, void *);
extern float func_L00_002D3A58(char *);
extern void func_L00_002D3BD8(char *, int, float);
extern float func_L00_002D3B00(char *);
extern void func_L00_002D3B58(TI128 *, TI128 *, float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282C88(TI128 *);
extern void func_L00_002B5A88(void);
extern void func_L09_002B7238(void);
extern void func_00282CF0(void *, void *, void *);
extern void func_PAL_L00_002B5178(void);
extern float func_00282DB0(void *, void *);
extern void func_L00_002D3960(char *, char *);
extern float func_L00_002B5590(void *);
extern void func_00282D30(void *, void *, float);
typedef union MotionVector {
    TI128 q;
    float f[4];
} MotionVector;
typedef struct HeroMotionPrefix {
    u8 unknown00[0x80];
    MotionVector position;
    u8 unknown90[0x60];
    MotionVector velocity, impulse, displacement, projected, up, flat, impulseMove;
    u8 unknown160[0x10];
    float speed, flatSpeed, forwardSpeed, slope, verticalSpeed, impulseSpeed;
    u8 unknown188[0x68];
    short collisionOffFrames;
    u8 unknown1F2[0x72];
    float radius;
    u8 unknown268[4];
    u32 wallHit;
    u8 unknown270[0x17];
    u8 collHit;
    u8 unknown288[0x94];
    float downLimit;
    u8 unknown320[0x268];
    u32 attachment;
    u8 unknown58C[0x4D4];
    MotionVector extraStep;
    u8 unknownA70[0x1824];
    int state;
    u8 unknown2298[4];
    int controlMode;
} HeroMotionPrefix;
extern HeroMotionPrefix D_00189E20;

/* Integrate hero motion, resolve contacts, and measure the resulting displacement. */
void func_PAL_L11_002CDDB8(void)
{
    MotionVector initial, planar, vertical;
    MotionVector *resolved;
    float limit, magnitude, component, savedW;
    int state;

    qcopy(initial.f, (char *)&D_00189E20.position);
    func_PAL_L00_002D4668(D_00189E20.attachment, (char *)&D_00189E20.impulse, (u8 *)&D_00189E20 + 0x90);
    state = D_00189E20.state;
    if (state == 0x14 || state == 0x5B || state == 0x58 || state == 0x81) {
        if (D_00189E20.collisionOffFrames == 0) {
            magnitude = func_L00_002D3A58((char *)&D_00189E20.velocity);
            limit = D_00189E20.radius - 0.02f;
            if (limit < magnitude)
                func_L00_002D3BD8((char *)&D_00189E20.velocity, (int)(char *)&D_00189E20.velocity, limit);
        }
        component = func_L00_002D3B00((char *)&D_00189E20.velocity);
        if (component < -D_00189E20.downLimit) {
            limit = -D_00189E20.downLimit - 0.02f;
            if (limit > 0.0f)
                limit = 0.0f;
            func_L00_002D3B58((TI128 *)(char *)&D_00189E20.velocity, (TI128 *)(char *)&D_00189E20.velocity, limit);
        }
    } else if (D_00189E20.controlMode != 13) {
        if (D_00189E20.controlMode != 14) {
            if (state != 0x44 && D_00189E20.collisionOffFrames == 0) {
                magnitude = func_00282DF0((char *)&D_00189E20.velocity);
                limit = D_00189E20.radius - 0.02f;
                if (limit < magnitude)
                    func_00282F20((char *)&D_00189E20.velocity, (char *)&D_00189E20.velocity, limit);
            }
        }
    }
    func_00282CC0((char *)&D_00189E20.position, (char *)&D_00189E20.position, (char *)&D_00189E20.velocity);
    func_00282CC0((char *)&D_00189E20.position, (char *)&D_00189E20.position, &D_00189E20.extraStep);
    func_00282C88((TI128 *)&D_00189E20.extraStep);
    D_00189E20.collHit = 0;
    D_00189E20.wallHit = 0;
    if (func_00282DF0((char *)&D_00189E20.impulse) <= 0.0001f) {
        func_L00_002B5A88();
        func_L09_002B7238();
        func_00282CF0((char *)&D_00189E20.displacement, (char *)&D_00189E20.position, initial.f);
        func_PAL_L00_002B5178();
    } else {
        func_L09_002B7238();
    }

    resolved = &D_00189E20.projected;
    func_00282CF0((char *)resolved, (char *)&D_00189E20.position, initial.f);
    qcopy((char *)&D_00189E20.flat, (char *)resolved);
    qcopy((char *)&D_00189E20.up, (char *)resolved);
    func_00282F20((char *)resolved, (char *)resolved, 1.0f);
    magnitude = func_00282DB0((char *)resolved, (char *)&D_00189E20.velocity);
    if (magnitude < 0.0f)
        magnitude = 0.0f;
    func_00282F20((char *)resolved, (char *)&D_00189E20.velocity, magnitude);
    qcopy(planar.f, (char *)&D_00189E20.velocity);
    func_L00_002D3960((char *)planar.f, (char *)planar.f);
    func_L00_002D3960((char *)&D_00189E20.flat, (char *)&D_00189E20.flat);
    func_00282F20((char *)&D_00189E20.flat, (char *)&D_00189E20.flat, 1.0f);
    magnitude = func_00282DB0((char *)&D_00189E20.flat, planar.f);
    if (magnitude < 0.0f)
        magnitude = 0.0f;
    func_00282F20((char *)&D_00189E20.flat, planar.f, magnitude);
    qcopy(vertical.f, (char *)&D_00189E20.velocity);
    func_L00_002D3BD8((char *)vertical.f, (int)vertical.f, 0.0f);
    func_L00_002D3BD8((char *)&D_00189E20.up, (int)(char *)&D_00189E20.up, 0.0f);
    func_00282F20((char *)&D_00189E20.up, (char *)&D_00189E20.up, 1.0f);
    magnitude = func_00282DB0((char *)&D_00189E20.up, vertical.f);
    if (magnitude < 0.0f)
        magnitude = 0.0f;
    func_00282F20((char *)&D_00189E20.up, vertical.f, magnitude);
    D_00189E20.speed = func_00282DF0((char *)resolved);
    magnitude = func_L00_002D3A58((char *)resolved);
    planar.q = resolved->q;
    D_00189E20.flatSpeed = magnitude;
    D_00189E20.forwardSpeed = func_L00_002B5590(planar.f);
    D_00189E20.verticalSpeed = func_L00_002D3B00((char *)resolved);
    if (D_00189E20.forwardSpeed < 0.0f)
        D_00189E20.forwardSpeed = 0.0f;
    qcopy(planar.f, (char *)&D_00189E20.position);
    if (func_00282DF0((char *)&D_00189E20.impulse) > 0.0001f) {
        func_00282CC0((char *)&D_00189E20.position, (char *)&D_00189E20.position, (char *)&D_00189E20.impulse);
        savedW = D_00189E20.impulse.f[3];
        func_00282C88((TI128 *)(char *)&D_00189E20.impulse);
        D_00189E20.impulse.f[3] = savedW;
        func_L00_002B5A88();
        func_L09_002B7238();
        func_00282CF0((char *)&D_00189E20.displacement, (char *)&D_00189E20.position, initial.f);
        func_PAL_L00_002B5178();
    }
    func_00282CF0((char *)&D_00189E20.impulseMove, (char *)&D_00189E20.position, planar.f);
    D_00189E20.impulseSpeed = func_00282DF0((char *)&D_00189E20.impulseMove);
    D_00189E20.impulseMove.f[3] = D_00189E20.impulse.f[3];
    D_00189E20.impulse.f[3] = 0.0f;
    func_00282CF0((char *)&D_00189E20.displacement, (char *)&D_00189E20.position, initial.f);
    D_00189E20.slope = 0.0f;
    if (D_00189E20.flatSpeed > 0.004f) {
        D_00189E20.slope = D_00189E20.displacement.f[2] / D_00189E20.flatSpeed;
        if (D_00189E20.slope > 0.5f)
            D_00189E20.slope = 0.5f;
        else if (D_00189E20.slope < -0.5f)
            D_00189E20.slope = -0.5f;
    }
    if (D_00189E20.speed > 1.0400001f) {
        func_00282D30((char *)&D_00189E20.displacement, (char *)&D_00189E20.displacement, 1.0400001f / D_00189E20.speed);
        D_00189E20.speed = 1.0400001f;
    }
}

/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
#include "common.h"
/* sol-high, 29 October 2026. Retained matching attempt.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
 * Current USA check: 972/972 bytes, 0/27 placements; first mismatch +0x11C.
 * The typed state views and independent hero-position/parent pointers recover
 * the retail frame, saved registers, camera initialization and final vector work.
 * Remaining differences: movement/orientation/rotation store scheduling and
 * plane/tracker global-load ordering and FPR allocation. No linked-build credit.
 * The rebuild call belongs only to the non-handoff branch, as retail shows.
 * RAC1 reference: src/overlays/shared/follow_camera.c, follow_camera_setup
 * (func_L00_002E8210); its state layout differs from RAC2's measured offsets.
 * Required declarations and partial state views are included below. The hero
 * parent is reached from its independently established resident position at +0x80.
 * Tested remedies that did not close the mismatch: raw pointers, manual qcopy,
 * MACRO_ADDR/SDATA scalar views, and disabling either scheduling pass or aliasing.
 */
typedef unsigned int CameraQuad __attribute__((mode(TI)));
extern CameraQuad D_00189EA0;
extern CameraQuad D_0018A0E0;
extern int D_L00_001B1580 SDATA(D_L00_001B1580), D_L00_001B1584 SDATA(D_L00_001B1584);
extern unsigned short D_L00_001B1514 SDATA(D_L00_001B1514), D_L00_001B1518 SDATA(D_L00_001B1518);
extern float D_L00_001B14A0 SDATA(D_L00_001B14A0), D_L00_001B14A4 SDATA(D_L00_001B14A4);
extern float D_L00_001B1510 SDATA(D_L00_001B1510), D_L00_001B14D4 SDATA(D_L00_001B14D4), D_L00_001B14D8 SDATA(D_L00_001B14D8), D_L00_001B14DC SDATA(D_L00_001B14DC);
extern float D_L00_001A8900, D_L00_001A8904;
extern int D_L00_001B1854;
typedef struct { unsigned char pad0[0x86]; short mode; } CameraControl;
extern CameraControl *D_L00_001B8E14[];

extern void func_00282C88(void *);
extern void func_L00_00423290(unsigned char *);
extern float func_00283CE0(int);
extern void func_L00_00420638(char *);
extern void func_L00_00423038(int);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DF0(void *);
#define CF(p, o) (*(float *)((p) + (o)))
#define CI(p, o) (*(int *)((p) + (o)))
#define CS(p, o) (*(short *)((p) + (o)))

typedef struct {
    short h0, h2;
    float f4, f8;
    int iC, i10, i14, i18;
    float f1C, f20, f24;
    int i28, i2C, i30;
    float f34, f38;
    char pad3C[4];
} OrientationState;
typedef struct {
    float pos[4]; char pad10[0x40]; float direction[4]; char pad60[0x50];
    float fB0; int iB4; float fB8; int iBC, iC0;
    unsigned char bC4, bC5; short hC6;
    char padC8[0xE]; unsigned char bD6, bD7; short hD8, hDA;
    float fDC, fE0, fE4, fE8; short hEC, hEE;
    int iF0, iF4, iF8, iFC;
} CameraSettings;
typedef struct {
    float pos[4], previous[4]; int i20, i24, i28; float f2C, f30;
    int i34, i38; short h3C, h3E; char pad40[4]; int i44;
    float f48; char pad4C[4]; int i50; float f54, f58; char pad5C[4];
} MovementState;
typedef struct {
    int i0, i4, i8, iC, i10; float f14, f18; int i1C, i20, i24;
} RotationState;
typedef struct {
    char pad0[0x10]; float direction[4], previous[4]; float f30;
    short h34, h36, h38, h3A; float f3C, f40, f44; int i48; short h4C, h4E;
} TrackerState;
typedef struct { int i0; short h4, h6; float f8, fC; int i10; } PlaneState;
typedef struct {
    float pos[4]; short h10, h12, h14, h16; char pad18[8];
    OrientationState orientation; CameraSettings camera; MovementState movement;
    RotationState rotation; char pad1E8[8]; TrackerState tracker; PlaneState plane;
} FollowState;
typedef struct {
    float basis[12], pos[4], previous[4]; char pad50[0x20]; FollowState *state;
    char pad74[9]; unsigned char handoff; short transition;
} CameraOwner;

void func_L00_004233F8(CameraOwner *owner)
{
    CameraQuad projected, difference;
    CameraSettings *camera = &owner->state->camera;
    MovementState *movement;
    FollowState *root;
    OrientationState *orientation;
    RotationState *rotation;
    PlaneState *plane;
    TrackerState *tracker;
    float distance;
    unsigned char *initialPosition = (unsigned char *)&D_00189EA0;
    unsigned char *hero;
    D_L00_001B1580 = 0;
    D_L00_001B1584 = 0;
    *(CameraQuad *)camera = *(CameraQuad *)initialPosition;
    hero = initialPosition - 0x80;
    camera->fB0 = 1.5f;
    camera->iC0 = CI(hero, 0x2290);
    camera->bC4 = 0;
    camera->bD6 = 0;
    camera->fE0 = 0.2f;
    camera->hEC = D_L00_001B1514;
    camera->fDC = D_L00_001B14A0;
    camera->fE4 = D_L00_001B14A4;
    camera->fE8 = 0.2f;
    camera->fB8 = 0.005f;
    camera->hC6 = 0;
    camera->hD8 = 0;
    camera->hEE = 0;
    camera->iB4 = 0;
    camera->hDA = 0;
    camera->iBC = 0;
    camera->iF0 = 0;
    camera->iF4 = 0;
    camera->iF8 = 0;
    camera->iFC = 0;
    movement = &owner->state->movement;
    movement->f30 = 2.0f;
    movement->f2C = 4.64f;
    movement->i34 = 0;
    movement->i38 = 0;
    movement->i28 = 0;
    movement->i20 = 0;
    movement->i24 = 0;
    movement->h3C = 0;
    movement->h3E = 0;
    movement->f54 = 0.003f;
    movement->f58 = 4.64f;
    movement->f48 = 0.003f;
    movement->i44 = 0;
    movement->i50 = 0;
    root = owner->state;
    root->h10 = 1;
    root->h12 = 0;
    root->h14 = 0;
    root->h16 = 0;
    D_L00_001A8900 = 0.85f;
    orientation = &owner->state->orientation;
    orientation->h0 = 0;
    orientation->f20 = 0.2f;
    orientation->f38 = 0.0002908882452175021f;
    orientation->f34 = 0.0002908882452175021f;
    orientation->f1C = 0.005f;
    orientation->i10 = 0;
    orientation->iC = 0;
    orientation->h2 = 0;
    orientation->i14 = 0;
    orientation->i18 = 0;
    orientation->i28 = 0;
    orientation->i2C = 0;
    orientation->i30 = 0;
    rotation = (RotationState *)((char *)owner->state + 0x1C0);
    rotation->i0 = 0;
    rotation->f14 = D_L00_001A8904;
    rotation->i8 = 0;
    rotation->i4 = 0;
    rotation->iC = 0;
    rotation->i10 = 0;
    rotation->f18 = 0.523598849773407f;
    rotation->i24 = 0;
    rotation->i1C = 0;
    rotation->i20 = 0;
    plane = (PlaneState *)((char *)owner->state + 0x240);
    plane->i0 = 0;
    plane->i10 = 0;
    plane->h4 = 0;
    plane->h6 = 0;
    plane->f8 = movement->f2C;
    plane->fC = D_L00_001B1510;
    tracker = (TrackerState *)((char *)owner->state + 0x1F0);
    tracker->f30 = 0.0f;
    tracker->h3A = 0;
    tracker->h36 = 0;
    tracker->h38 = 0;
    tracker->h4C = 0;
    tracker->h4E = 0;
    tracker->i48 = D_L00_001B1854;
    tracker->h34 = 2000;
    tracker->f44 = D_L00_001B14D4;
    tracker->f3C = D_L00_001B14DC;
    tracker->f40 = D_L00_001B14D8;
    func_00282C88(tracker->direction);
    if (owner->handoff == 2) {
        func_L00_00423290((unsigned char *)owner);
        *(CameraQuad *)(owner->previous) = *(CameraQuad *)owner;
        if (D_L00_001B8E14[0]->mode == 7 && CS(hero, 0x34C) == 0)
            orientation->h0 = 0;
        else {
            orientation->h0 = D_L00_001B1518;
            orientation->f24 = 1.0f / func_00283CE0((short)D_L00_001B1518);
        }
    } else {
        func_L00_00420638((char *)owner);
        func_L00_00423038(1);
    }
    func_00282CF0(movement, owner->pos, camera->direction);
    *(CameraQuad *)(movement->previous) = *(CameraQuad *)movement;
    *(CameraQuad *)root = *(CameraQuad *)(owner->pos);
    *(CameraQuad *)(tracker->previous) = *(CameraQuad *)(owner->pos);
    distance = func_00282DB0(movement, &D_0018A0E0);
    func_00282D30(&projected, &D_0018A0E0, distance);
    func_00282CF0(&difference, movement, &projected);
    distance = movement->f2C - func_00282DF0(&difference);
    tracker->f30 = distance;
    if (distance < -0.1f) tracker->h3A = 1;
    orientation->f8 = movement->f30;
    orientation->f4 = camera->fB0;
    owner->transition = 0;
}
#undef CF
#undef CI
#undef CS

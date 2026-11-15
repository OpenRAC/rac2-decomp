#include "common.h"

/* the hero object, with the fields this function reads */
typedef struct {
    u8  pad00[0x20];
    f32 axis20[4];
    u8  pad30[0x50];
    f32 position[4];
    u8  pad90[0x156];
    s16 f1E6;
    u8  pad1E8[8];
    s16 air_frames;
    u8  pad1F2[0x26];
    s16 f218;
    u8  pad21A[0x16];
    f32 contact_a[4];
    f32 contact_b[4];
    f32 f250;
    f32 f254;
    u8  pad258[0xC];
    f32 radius;
    u8  pad268[4];
    s32 collision_id;
    u8  pad270[0x17];
    u8  collision_flag;
    u8  pad288[0x38];
    f32 axis2C0[4];
    u8  pad2D0[0x1FC0];
    s32 object;
    u8  pad2294[8];
    s32 control_mode;
    u8  pad22A0[0x14];
    u8  f22B4;
    u8  pad22B5[0xE];
    u8  f22C3;
    u8  pad22C4[0x23A];
    s16 f24FE;
} Hero;

/* -G8 is required for the movement-mode flag at D_001A8FF0. */
extern Hero D_00189E20;
extern char D_L04_001BFAF0[];
extern int D_001A8FF0 MACRO_ADDR;
extern void func_00282C88(void *);
extern void func_L00_002D49F0(void);
extern float func_00282DB0(void *, void *);
extern void func_L00_002D38A0(void *, void *, float);
extern void func_L00_002D36E0(void *, int, float, float, float);
extern void func_00282CC0(void *, void *, void *);
/* EE argument banks retain radius/height in F12/F13 and position/mask/object
   in A0/A1/A2. */
extern int func_00277258(float, void *, int, int);
extern int func_L00_002E0200(float, float, void *, int, int);
extern int func_00278870(float, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);

/* Moves the hero by a step derived from its control mode and pushes it out of
   anything it hits, up to eight times; returns 1 when the net move is small, -1
   when it exceeds the hero's radius (clamping it first when reason is 15). */
int func_L04_002DB970(int reason)
{
    float old[4] __attribute__((aligned(16)));
    float move[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    int grounded;
    int n;
    int hit;

    if (D_00189E20.air_frames)
        return 1;

    qcopy(old, D_00189E20.position);
    func_00282C88(move);
    if (D_00189E20.f24FE) {
        func_L00_002D49F0();
        D_00189E20.f24FE = 0;
    }

    grounded = 0;
    if (FastVecDot(D_00189E20.axis20, D_00189E20.axis2C0) > -0.92f)
        grounded = 1;

    if (D_00189E20.control_mode != 0x11) {
        if (D_00189E20.f22C3 || D_00189E20.f218 || grounded) {
            if (D_00189E20.f22B4 == 2) {
                func_L00_002D38A0(move, move, 5.0f);
            } else if (D_00189E20.f22C3 == 1 || D_00189E20.f218) {
                func_L00_002D36E0(move, 0, 0.0f, 0.0f, 0.6f);
            } else if (D_001A8FF0) {
                func_L00_002D38A0(move, move, 0.77f);
            } else {
                func_L00_002D36E0(move, 0, 0.0f, 0.0f, D_00189E20.f254);
            }
        } else {
            move[2] = D_00189E20.f254;
        }
    }
    FastVecAdd(D_00189E20.position, D_00189E20.position, move);

    for (n = 0; n < 8; n++) {
        if (D_00189E20.control_mode == 0x11) {
            if (!func_00277258(0.6f, D_00189E20.position, 0x24, D_00189E20.object))
                break;
        } else {
            if (D_00189E20.f22C3 || grounded) {
                hit = func_00277258(D_00189E20.radius, D_00189E20.position, 0x24,
                                    D_00189E20.object) |
                      (D_00189E20.f1E6 ? 0 : func_00278870(D_00189E20.radius,
                                                           D_00189E20.position));
            } else {
                float height = D_00189E20.f250 - D_00189E20.f254;

                if (height < 0.05f)
                    height = 0.05f;
                hit = func_L00_002E0200(D_00189E20.radius, height, D_00189E20.position, 0x24,
                                        D_00189E20.object) |
                      (D_00189E20.f1E6 ? 0 : func_00278870(D_00189E20.radius,
                                                           D_00189E20.position));
            }
            if (!hit)
                break;
        }

        {
            char *collision = D_L04_001BFAF0;

            qcopy(D_00189E20.position, collision);
            qcopy(D_00189E20.contact_a, collision + 0x10);
            qcopy(D_00189E20.contact_b, collision - 0x10);
            D_00189E20.collision_flag = 1;
            D_00189E20.collision_id = *(s32 *)(collision - 0x18);
        }
    }

    FastVecSub(D_00189E20.position, D_00189E20.position, move);
    FastVecSub(delta, D_00189E20.position, old);
    if (FastVecLength(delta) > D_00189E20.radius * 1.5f) {
        if (reason == 15) {
            if (delta[0] > 512.0f)
                delta[0] = 512.0f;
            else if (delta[0] < -512.0f)
                delta[0] = -512.0f;
            if (delta[1] > 512.0f)
                delta[1] = 512.0f;
            else if (delta[1] < -512.0f)
                delta[1] = -512.0f;
            if (delta[2] > 512.0f)
                delta[2] = 512.0f;
            else if (delta[2] < -512.0f)
                delta[2] = -512.0f;
            vec_scale_to_length(delta, delta, D_00189E20.radius);
            FastVecAdd(D_00189E20.position, old, delta);
        }
        return -1;
    }
    return 1;
}

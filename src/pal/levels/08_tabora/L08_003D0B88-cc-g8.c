/* func_PAL_L08_003D0B88, the PAL copy of func_L08_003CCD80: the same C, where wrap D_L08_001AFF58 (({e}) * 1.2f); wrap D_L08_001AFF34 (({e}) * 1.2f); wrap D_L08_001AFF34 (({e}) * 1.2f). */
#include "common.h"

#define FIELD(base, T, offset) (((struct { u8 pad[offset]; T value; } *)(base))->value)

extern char D_00188660[], D_L08_001B9B00[];
extern s16 D_L08_001AFF24 __attribute__((sda));
extern s16 D_L08_001AFF26 __attribute__((sda));
extern s16 D_L08_001AFF28 __attribute__((sda));
extern s16 D_L08_001AFF2A __attribute__((sda));
extern u8 D_L08_001AFF2C __attribute__((sda));
extern u8 D_L08_001AFF2E __attribute__((sda));
extern u8 D_L08_001AFF30 __attribute__((sda));
extern u8 D_L08_001AFF32 __attribute__((sda));
extern int D_L08_001AFF5C __attribute__((sda));
extern int D_L08_001AFFC0 __attribute__((sda));
extern float D_L08_001AFFC8 __attribute__((sda));
extern float D_L08_001AFFCC __attribute__((sda));
extern float D_L08_001AFF34 __attribute__((sda));
extern float D_L08_001AFF38 __attribute__((sda));
extern float D_L08_001AFF3C __attribute__((sda));
extern float D_L08_001AFF40 __attribute__((sda));
extern float D_L08_001AFF44 __attribute__((sda));
extern float D_L08_001AFF48 __attribute__((sda));
extern float D_L08_001AFF4C __attribute__((sda));
extern float D_L08_001AFF50 __attribute__((sda));
extern float D_L08_001AFF54 __attribute__((sda));
extern float D_L08_001AFF58 __attribute__((sda));
extern float D_L08_001AFF60 __attribute__((sda));
extern float D_L08_001AFF64 __attribute__((sda));
extern float D_L08_001AFF68 __attribute__((sda));
extern float D_L08_001AFF6C __attribute__((sda));
extern float D_L08_001AFF70 __attribute__((sda));
extern float D_L08_001AFF74 __attribute__((sda));
extern float D_L08_001AFF78 __attribute__((sda));
extern float D_L08_001AFF90 __attribute__((sda));
extern float D_L08_001AFF94 __attribute__((sda));
extern float D_L08_001AFF98 __attribute__((sda));
extern float D_L08_001AFF9C __attribute__((sda));
extern float D_L08_001AFFA0 __attribute__((sda));
extern float D_L08_001AFFA4 __attribute__((sda));
extern float D_L08_001AFFA8 __attribute__((sda));
extern float D_L08_001AFFAC __attribute__((sda));
extern float D_L08_001AFFB0 __attribute__((sda));
extern float D_L08_001AFFB4 __attribute__((sda));
extern float D_L08_001AFFBC __attribute__((sda));
extern float D_L08_001AFFC4 __attribute__((sda));
extern int D_L08_001AFF7C __attribute__((sda));
extern int D_L08_001AFF80 __attribute__((sda));
extern int D_L08_001AFF84 __attribute__((sda));
extern int D_L08_001AFF88 __attribute__((sda));
extern int D_L08_001AFF8C __attribute__((sda));
extern float func_00283CE0(int);
extern float func_L08_003CCD58(int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern int func_L08_003CCD28(int);
extern int func_002A77E0(int);
extern int func_002E5CF8(int, int, void *);
extern void *func_L08_003CCC30(void *, int, short, int, int, unsigned char, unsigned char);
extern void func_L00_00310838(void *, int, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002836E8(void *, void *);
extern void func_00282CD8(void *, void *, void *);
extern void func_002E59F8(int);
extern void func_L08_003D0010(float, float, float, float);
extern void func_002C19D8(void *, int, int, float, float);
extern void func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

void func_PAL_L08_003D0B88(char * object) {
    char * state = FIELD(object, char *, 0x68), *sound;
    int rotationDelta;
    int slot;
    float first, second;
    float velocityX, velocityY, accelerationX, accelerationY;
    float velocity[4] __attribute__((aligned(16)));
    float acceleration[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float inverseBasis[12] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));

    if (!FIELD(object, u8, 0x20)) {
        if (FIELD(object, s16, 0xAA) == 0x8F9) {
            FIELD(state, s16, 4) = D_L08_001AFF24;
            FIELD(state, u8, 0x1E) = D_L08_001AFF2C;
            FIELD(state, float, 8) = func_00283CE0(FIELD(state, u8, 0x1C));
            FIELD(state, void *, 0x10) = func_L08_003CCC30(object, 0x8F8, D_L08_001AFF26, FIELD(state, u8, 0x1C), FIELD(state, int, 0), D_L08_001AFF2E, FIELD(state, u8, 0x1D));
            FIELD(state, void *, 0x14) = func_L08_003CCC30(object, 0x8F7, D_L08_001AFF28, FIELD(state, u8, 0x1C), FIELD(state, int, 0), D_L08_001AFF30, FIELD(state, u8, 0x1D));
            FIELD(state, void *, 0x18) = func_L08_003CCC30(object, 0x8F6, D_L08_001AFF2A, FIELD(state, u8, 0x1C), FIELD(state, int, 0), D_L08_001AFF32, FIELD(state, u8, 0x1D));
        }
        FIELD(state, float, 0xC) = func_L08_003CCD58(FIELD(state, int, 0));
        FIELD(object, float, 0x18) += D_L08_001AFFC8;
        FIELD(object, u16, 0x34) |= 0x2008;
        FIELD(state, s8, 0x1F) = -1;
        FIELD(object, u8, 0x20) = 1;
    }
    FIELD(object, float, 0x18) += ((FIELD(state, float, 0xC) + 0.2f + D_L08_001AFFC8 * (1.0f - FIELD(state, float, 8))) - FIELD(object, float, 0x18)) * 0.1f;
    if (func_L08_003CCD28(FIELD(state, int, 0))) {
        if (!FIELD(state, u8, 0x1C)) {
            FIELD(state, float, 8) += ((D_L08_001AFF34) * 1.2f);
            if (FIELD(state, float, 8) > 1) {
                FIELD(state, float, 8) = 1;
                FIELD(state, u8, 0x1C) = 1;
            }
        }
    } else if (FIELD(state, u8, 0x1C)) {
        FIELD(state, float, 8) -= ((D_L08_001AFF34) * 1.2f);
        if (FIELD(state, float, 8) < 0) {
            FIELD(state, float, 8) = 0;
            FIELD(state, u8, 0x1C) = 0;
        }
    }
    FIELD(object, u8, 0x23) = FIELD(state, u8, 0x1E) + func_00283CF0(func_00283CE0(255 - FIELD(state, u8, 0x1E)) * FIELD(state, float, 8));
    if (FIELD(state, float, 8) < 1) {
        if (FIELD(state, u8, 0x1D)) {
            rotationDelta = -func_00283CF0(func_00283CE0(FIELD(state, s16, 4)) * (1.0f - FIELD(state, float, 8)));
            FIELD(state, s16, 6) += rotationDelta;
            if (FIELD(state, s16, 6) > 4096) {
                FIELD(state, s16, 6) -= 4096;
                rotationDelta -= 4096;
            } else if (FIELD(state, s16, 6) < 0) {
                FIELD(state, s16, 6) += 4096;
                rotationDelta += 4096;
            }
            func_L00_00310838(FIELD(object, void *, 0x24), 0, rotationDelta);
        }
        if (!func_002A77E0(D_L08_001AFF5C + func_00283CF0(D_L08_001AFF60 * FIELD(state, float, 8)) - 1)) {
            func_00282F20(acceleration, object + 0xC0, func_002A7878(-D_L08_001AFF38, D_L08_001AFF38));
            func_00282CC0(velocity, object + 0x10, acceleration);
            func_00282F20(acceleration, object + 0xD0, func_002A7878(-D_L08_001AFF3C, D_L08_001AFF3C));
            func_00282CC0(velocity, velocity, acceleration);
            velocity[2] = FIELD(state, float, 0xC) + D_L08_001AFFCC;
            first = func_002A7878(D_L08_001AFF40, D_L08_001AFF44);
            second = func_002A7878(D_L08_001AFF48, D_L08_001AFF4C);
            func_L08_003D0010(velocity[0], velocity[1], first, second);
            func_002C19D8(velocity, 0, -1, func_002A7878(D_L08_001AFF50, D_L08_001AFF54), ((D_L08_001AFF58) * 1.2f));
        }
    }
    if (!FIELD(state, u8, 0x1C)) {
        if (FIELD(object, s16, 0xAA) == 0x8F9) {
            slot = FIELD(state, s8, 0x1F);
            sound = D_00188660 + slot * 0x70;
            if (FIELD(sound, void *, 0x88) != object || !FIELD(sound, u8, 0x74))
                slot = func_002E5CF8(0, 4, object);
            FIELD(state, s8, 0x1F) = slot;
            if (!func_002A77E0(D_L08_001AFFC0 - 1)) {
                velocity[3] = func_002A7878(D_L08_001AFF90, D_L08_001AFF94);
                acceleration[3] = func_002A7878(D_L08_001AFF98, D_L08_001AFF9C);
                if (!func_002A77E0(2)) {
                    qcopy(position, object + 0x10);
                    position[2] += D_L08_001AFFC4;
                    func_00282F20(offset, object + 0xC0, func_002A7878(D_L08_001AFFA0, D_L08_001AFFA4));
                    func_00282CC0(position, position, offset);
                    func_00282F20(offset, object + 0xD0, func_002A7878(D_L08_001AFFA8, D_L08_001AFFAC));
                    func_00282CC0(position, position, offset);
                } else {
                    func_00282CF0(position, D_L08_001B9B00, object + 0x10);
                    func_00282F20(position, position, 1);
                    position[2] = 0;
                    func_002836E8(inverseBasis, object + 0xC0);
                    func_00283098(position, position, inverseBasis);
                    position[0] *= func_002A7878(D_L08_001AFFB0, D_L08_001AFFB4);
                    position[1] *= func_002A7878(0, D_L08_001AFFBC);
                    position[2] = func_002A7878(0, D_L08_001AFFC4);
                    func_00283098(position, position, object + 0xC0);
                    func_00282CD8(delta, position, object + 0x10);
                }
                velocityX = func_00283180(func_002A7940());
                velocityX *= func_002A7878(0, D_L08_001AFF64 * 0.020000001f);
                velocity[0] = velocityX;
                velocityY = func_00283198(func_002A7940());
                velocityY *= func_002A7878(0, D_L08_001AFF64 * 0.020000001f);
                velocity[1] = velocityY;
                velocity[2] = 0;
                velocity[2] = func_002A7878(D_L08_001AFF68, D_L08_001AFF6C) * 0.020000001f;
                accelerationX = func_00283180(func_002A7940());
                accelerationX *= func_002A7878(0, D_L08_001AFF70 * 0.020000001f);
                acceleration[0] = accelerationX;
                accelerationY = func_00283198(func_002A7940());
                accelerationY *= func_002A7878(0, D_L08_001AFF70 * 0.020000001f);
                acceleration[1] = accelerationY;
                acceleration[2] = 0;
                acceleration[2] = func_002A7878(D_L08_001AFF74, D_L08_001AFF78) * 0.020000001f;
                func_002BAA28(position, velocity, acceleration, D_L08_001AFF7C, D_L08_001AFF80, D_L08_001AFF84, D_L08_001AFF88, D_L08_001AFF8C, -1);
            }
        }
        FIELD(object, int, 0x98) = 0;
    } else {
        int stopSlot;
        if (FIELD(object, s16, 0xAA) == 0x8F9 && FIELD(state, s8, 0x1F) != -1) {
            stopSlot = FIELD(state, s8, 0x1F);
            sound = D_00188660 + stopSlot * 0x70;
            if (FIELD(sound, void *, 0x88) == object && FIELD(sound, u8, 0x74))
                func_002E59F8(stopSlot);
            stopSlot = -1;
            FIELD(state, s8, 0x1F) = stopSlot;
        }
        FIELD(object, int, 0x98) = FIELD(FIELD(object, char *, 0x24), int, 0x10);
    }
}

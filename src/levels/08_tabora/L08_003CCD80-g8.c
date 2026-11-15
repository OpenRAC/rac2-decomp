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

/* Waterfall: opens and closes with its linked switch, spins its texture, and sprays mist and drops while flowing. */
void func_L08_003CCD80(char * moby) {
    char * vars = FIELD(moby, char *, 0x68), *soundSlotEntry;
    int rotationDelta;
    int soundSlot;
    float sizeMin, sizeMax;
    float velocityX, velocityY, accelerationX, accelerationY;
    float velocity[4] __attribute__((aligned(16)));
    float acceleration[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float inverseBasis[12] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));

    if (!FIELD(moby, u8, 0x20)) {
        if (FIELD(moby, s16, 0xAA) == 0x8F9 /* Waterfall (frozen) */) {
            FIELD(vars, s16, 4) = D_L08_001AFF24;
            FIELD(vars, u8, 0x1E) = D_L08_001AFF2C;
            FIELD(vars, float, 8) = IntToFloat(FIELD(vars, u8, 0x1C));
            FIELD(vars, void *, 0x10) = SpawnWaterfallPiece(moby, 0x8F8 /* Waterfall (frozen) */, D_L08_001AFF26, FIELD(vars, u8, 0x1C), FIELD(vars, int, 0), D_L08_001AFF2E, FIELD(vars, u8, 0x1D));
            FIELD(vars, void *, 0x14) = SpawnWaterfallPiece(moby, 0x8F7 /* Waterfall (frozen) */, D_L08_001AFF28, FIELD(vars, u8, 0x1C), FIELD(vars, int, 0), D_L08_001AFF30, FIELD(vars, u8, 0x1D));
            FIELD(vars, void *, 0x18) = SpawnWaterfallPiece(moby, 0x8F6 /* Waterfall */, D_L08_001AFF2A, FIELD(vars, u8, 0x1C), FIELD(vars, int, 0), D_L08_001AFF32, FIELD(vars, u8, 0x1D));
        }
        FIELD(vars, float, 0xC) = GetMobyHeight(FIELD(vars, int, 0));
        FIELD(moby, float, 0x18) += D_L08_001AFFC8;
        FIELD(moby, u16, 0x34) |= 0x2008;
        FIELD(vars, s8, 0x1F) = -1;
        FIELD(moby, u8, 0x20) = 1;
    }
    FIELD(moby, float, 0x18) += ((FIELD(vars, float, 0xC) + 0.2f + D_L08_001AFFC8 * (1.0f - FIELD(vars, float, 8))) - FIELD(moby, float, 0x18)) * 0.1f;
    if (IsLinkedMobySwitchedOn(FIELD(vars, int, 0))) {
        if (!FIELD(vars, u8, 0x1C)) {
            FIELD(vars, float, 8) += D_L08_001AFF34;
            if (FIELD(vars, float, 8) > 1) {
                FIELD(vars, float, 8) = 1;
                FIELD(vars, u8, 0x1C) = 1;
            }
        }
    } else if (FIELD(vars, u8, 0x1C)) {
        FIELD(vars, float, 8) -= D_L08_001AFF34;
        if (FIELD(vars, float, 8) < 0) {
            FIELD(vars, float, 8) = 0;
            FIELD(vars, u8, 0x1C) = 0;
        }
    }
    FIELD(moby, u8, 0x23) = FIELD(vars, u8, 0x1E) + FloatToInt(IntToFloat(255 - FIELD(vars, u8, 0x1E)) * FIELD(vars, float, 8));
    if (FIELD(vars, float, 8) < 1) {
        if (FIELD(vars, u8, 0x1D)) {
            rotationDelta = -FloatToInt(IntToFloat(FIELD(vars, s16, 4)) * (1.0f - FIELD(vars, float, 8)));
            FIELD(vars, s16, 6) += rotationDelta;
            if (FIELD(vars, s16, 6) > 4096) {
                FIELD(vars, s16, 6) -= 4096;
                rotationDelta -= 4096;
            } else if (FIELD(vars, s16, 6) < 0) {
                FIELD(vars, s16, 6) += 4096;
                rotationDelta += 4096;
            }
            offset_moby_class_point_pairs(FIELD(moby, void *, 0x24), 0, rotationDelta);
        }
        if (!RandomIntBelow(D_L08_001AFF5C + FloatToInt(D_L08_001AFF60 * FIELD(vars, float, 8)) - 1)) {
            vec_scale_to_length(acceleration, moby + 0xC0, RandomFloatRange(-D_L08_001AFF38, D_L08_001AFF38));
            FastVecAdd(velocity, moby + 0x10, acceleration);
            vec_scale_to_length(acceleration, moby + 0xD0, RandomFloatRange(-D_L08_001AFF3C, D_L08_001AFF3C));
            FastVecAdd(velocity, velocity, acceleration);
            velocity[2] = FIELD(vars, float, 0xC) + D_L08_001AFFCC;
            sizeMin = RandomFloatRange(D_L08_001AFF40, D_L08_001AFF44);
            sizeMax = RandomFloatRange(D_L08_001AFF48, D_L08_001AFF4C);
            StopSharedWaterEffect(velocity[0], velocity[1], sizeMin, sizeMax);
            SpawnDriftingParticle_002C19D8(velocity, 0, -1, RandomFloatRange(D_L08_001AFF50, D_L08_001AFF54), D_L08_001AFF58);
        }
    }
    if (!FIELD(vars, u8, 0x1C)) {
        if (FIELD(moby, s16, 0xAA) == 0x8F9 /* Waterfall (frozen) */) {
            soundSlot = FIELD(vars, s8, 0x1F);
            soundSlotEntry = gSoundState + soundSlot * 0x70;
            if (FIELD(soundSlotEntry, void *, 0x88) != moby || !FIELD(soundSlotEntry, u8, 0x74))
                soundSlot = PlayMobySound(0, 4, moby);
            FIELD(vars, s8, 0x1F) = soundSlot;
            if (!RandomIntBelow(D_L08_001AFFC0 - 1)) {
                velocity[3] = RandomFloatRange(D_L08_001AFF90, D_L08_001AFF94);
                acceleration[3] = RandomFloatRange(D_L08_001AFF98, D_L08_001AFF9C);
                if (!RandomIntBelow(2)) {
                    qcopy(position, moby + 0x10);
                    position[2] += D_L08_001AFFC4;
                    vec_scale_to_length(offset, moby + 0xC0, RandomFloatRange(D_L08_001AFFA0, D_L08_001AFFA4));
                    FastVecAdd(position, position, offset);
                    vec_scale_to_length(offset, moby + 0xD0, RandomFloatRange(D_L08_001AFFA8, D_L08_001AFFAC));
                    FastVecAdd(position, position, offset);
                } else {
                    FastVecSub(position, D_L08_001B9B00, moby + 0x10);
                    vec_scale_to_length(position, position, 1);
                    position[2] = 0;
                    FastMatrixHelperC(inverseBasis, moby + 0xC0);
                    matrix_mul_vec3(position, position, inverseBasis);
                    position[0] *= RandomFloatRange(D_L08_001AFFB0, D_L08_001AFFB4);
                    position[1] *= RandomFloatRange(0, D_L08_001AFFBC);
                    position[2] = RandomFloatRange(0, D_L08_001AFFC4);
                    matrix_mul_vec3(position, position, moby + 0xC0);
                    add_vectors(delta, position, moby + 0x10);
                }
                velocityX = FastSinOrCosA(RandomAngle());
                velocityX *= RandomFloatRange(0, D_L08_001AFF64 * 0.016666668f);
                velocity[0] = velocityX;
                velocityY = FastSinOrCosB(RandomAngle());
                velocityY *= RandomFloatRange(0, D_L08_001AFF64 * 0.016666668f);
                velocity[1] = velocityY;
                velocity[2] = 0;
                velocity[2] = RandomFloatRange(D_L08_001AFF68, D_L08_001AFF6C) * 0.016666668f;
                accelerationX = FastSinOrCosA(RandomAngle());
                accelerationX *= RandomFloatRange(0, D_L08_001AFF70 * 0.016666668f);
                acceleration[0] = accelerationX;
                accelerationY = FastSinOrCosB(RandomAngle());
                accelerationY *= RandomFloatRange(0, D_L08_001AFF70 * 0.016666668f);
                acceleration[1] = accelerationY;
                acceleration[2] = 0;
                acceleration[2] = RandomFloatRange(D_L08_001AFF74, D_L08_001AFF78) * 0.016666668f;
                SpawnTrailParticle_002BAA28(position, velocity, acceleration, D_L08_001AFF7C, D_L08_001AFF80, D_L08_001AFF84, D_L08_001AFF88, D_L08_001AFF8C, -1);
            }
        }
        FIELD(moby, int, 0x98) = 0;
    } else {
        int playingSlot;
        if (FIELD(moby, s16, 0xAA) == 0x8F9 /* Waterfall (frozen) */ && FIELD(vars, s8, 0x1F) != -1) {
            playingSlot = FIELD(vars, s8, 0x1F);
            soundSlotEntry = gSoundState + playingSlot * 0x70;
            if (FIELD(soundSlotEntry, void *, 0x88) == moby && FIELD(soundSlotEntry, u8, 0x74))
                StopSoundVoice(playingSlot);
            playingSlot = -1;
            FIELD(vars, s8, 0x1F) = playingSlot;
        }
        FIELD(moby, int, 0x98) = FIELD(FIELD(moby, char *, 0x24), int, 0x10);
    }
}

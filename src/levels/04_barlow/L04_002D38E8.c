#include "common.h"

/* Ground-material portion of the shared hero input handler. */

typedef struct {
    unsigned char pad0[136];
    float positionZ;
    unsigned char pad8c[140];
    float displacementZ;
    unsigned char pad11c[194];
    short inputLock;
    unsigned char pad1e0[312];
    float groundZ;
    float groundDistance;
    unsigned char pad320[16];
    float waterSurfaceZ;
    unsigned char pad334[12];
    int groundedFrames;
    unsigned char pad344[4];
    short pendingJump;
    unsigned char pad34a[2];
    short framesOffGround;
    unsigned char pad34e[4418];
    short groundType;
    unsigned char onIceGround;
    unsigned char pad1493[1];
    unsigned char baseCondition;
    unsigned char pad1495[2];
    unsigned char onMagnetGround;
    unsigned char pad1498[2];
    unsigned char onSlipGround;
    unsigned char pad149b[1];
    unsigned char sinkGround;
    unsigned char groundSoundClass;
    unsigned char pad149e[3574];
    int moveState;
    unsigned char pad2298[28];
    unsigned char vehicleMode;
    unsigned char pad22b5[4];
    unsigned char wading;
    unsigned char pad22ba[3];
    unsigned char disabled;
    unsigned char pad22be[518];
    float waterDepth;
} HeroGroundFlags;
extern HeroGroundFlags D_00189E20;
extern unsigned char D_001A7B0B __attribute__((sda));
extern void func_00282A88(void *, int);
extern float func_00282C48(float);
extern void func_L04_002E7C08(int, int);

/* Checks what kind of ground the hero stands on (ice, water, slippery) and sets the matching flags. */
void func_L04_002D38E8(void)
{
    short state = gHeroState.groundType;
    unsigned char saved = gHeroState.groundSoundClass;
    FastMemoryHelperB(&gHeroState.groundType, 16);
    gHeroState.groundSoundClass = saved;
    gHeroState.groundType = state;
    gHeroState.wading = 0;
    gHeroState.pendingJump = 0;
    if (gHeroState.disabled) return;
    /* Retained eligibility calculation from the corresponding common input
     * handler, func_L00_002ACA08. Its result is unused in this reduced variant;
     * the compiler retains the groundedFrames read found in retail. */
    {
        int active = 0;
        if (gHeroState.groundedFrames ||
            (gHeroState.moveState == 123 && gHeroState.groundDistance < 0.4f))
            active = 1;
    }
    if (state == -1) return;
    if (state == 2 && gHeroState.inputLock == 0 &&
        (gHeroState.framesOffGround == 0 || gHeroState.groundDistance < 2.5f)) {
        gHeroState.onMagnetGround = 1;
        if (gHeroState.vehicleMode == 0 && D_001A7B0B)
            gHeroState.pendingJump = 1;
    }
    if (state == 14) {
        gHeroState.baseCondition = 1;
        gHeroState.waterDepth = 0.2f;
        gHeroState.waterSurfaceZ = gHeroState.groundZ + 0.2f;
    }
    if (state == 0) {
        float remaining = gHeroState.waterSurfaceZ - gHeroState.groundZ;
        gHeroState.waterDepth = remaining;
        if (remaining < 0.85f && remaining > 0.25f)
            gHeroState.wading = 1;
        gHeroState.baseCondition = 1;
    }
    if (state == 7) gHeroState.onIceGround = 1;
    if (state == 13) gHeroState.sinkGround = 1;
    if (state == 8) gHeroState.onSlipGround = 1;
    if (state == 12) gHeroState.onSlipGround = 1;
    if (gHeroState.sinkGround && gHeroState.moveState != 124 &&
        FloatAbs(gHeroState.waterSurfaceZ - (gHeroState.positionZ + 0.25f)) < 1.0f &&
        gHeroState.waterSurfaceZ - gHeroState.positionZ > 0.0f &&
        (gHeroState.displacementZ < 0.0f || gHeroState.moveState == 123))
        EnterHeroState_L04(124, 1);
}


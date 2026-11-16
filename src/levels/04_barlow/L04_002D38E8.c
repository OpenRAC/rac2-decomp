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
extern HeroGroundFlags g_hero_state;
extern unsigned char g_hero_input_enabled __attribute__((sda));
extern void mem_fast_helper_b(void *, int);
extern float math_fabs(float);
extern s32 hero_l04_enter_state(int, int);

/* Checks what kind of ground the hero stands on (ice, water, slippery) and sets the matching flags. */
void UpdateHeroGroundMaterialFlags(void)
{
    short state = g_hero_state.groundType;
    unsigned char saved = g_hero_state.groundSoundClass;
    mem_fast_helper_b(&g_hero_state.groundType, 16);
    g_hero_state.groundSoundClass = saved;
    g_hero_state.groundType = state;
    g_hero_state.wading = 0;
    g_hero_state.pendingJump = 0;
    if (g_hero_state.disabled) return;
    /* Retained eligibility calculation from the corresponding common input
     * handler, func_L00_002ACA08. Its result is unused in this reduced variant;
     * the compiler retains the groundedFrames read found in retail. */
    {
        int active = 0;
        if (g_hero_state.groundedFrames ||
            (g_hero_state.moveState == 123 && g_hero_state.groundDistance < 0.4f))
            active = 1;
    }
    if (state == -1) return;
    if (state == 2 && g_hero_state.inputLock == 0 &&
        (g_hero_state.framesOffGround == 0 || g_hero_state.groundDistance < 2.5f)) {
        g_hero_state.onMagnetGround = 1;
        if (g_hero_state.vehicleMode == 0 && g_hero_input_enabled)
            g_hero_state.pendingJump = 1;
    }
    if (state == 14) {
        g_hero_state.baseCondition = 1;
        g_hero_state.waterDepth = 0.2f;
        g_hero_state.waterSurfaceZ = g_hero_state.groundZ + 0.2f;
    }
    if (state == 0) {
        float remaining = g_hero_state.waterSurfaceZ - g_hero_state.groundZ;
        g_hero_state.waterDepth = remaining;
        if (remaining < 0.85f && remaining > 0.25f)
            g_hero_state.wading = 1;
        g_hero_state.baseCondition = 1;
    }
    if (state == 7) g_hero_state.onIceGround = 1;
    if (state == 13) g_hero_state.sinkGround = 1;
    if (state == 8) g_hero_state.onSlipGround = 1;
    if (state == 12) g_hero_state.onSlipGround = 1;
    if (g_hero_state.sinkGround && g_hero_state.moveState != 124 &&
        math_fabs(g_hero_state.waterSurfaceZ - (g_hero_state.positionZ + 0.25f)) < 1.0f &&
        g_hero_state.waterSurfaceZ - g_hero_state.positionZ > 0.0f &&
        (g_hero_state.displacementZ < 0.0f || g_hero_state.moveState == 123))
        hero_l04_enter_state(124, 1);
}


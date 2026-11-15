/* Update the oscillating effect parameter and submit a complete 144-byte quad packet.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L23_001AFA18 __attribute__((sda));
extern float D_L23_001AFA1C __attribute__((sda));
extern float D_L23_001AFA20 __attribute__((sda));
extern int D_L23_001AFA24 __attribute__((sda));
extern int D_L23_001AFA28 __attribute__((sda));
extern int D_L23_001AFA2C __attribute__((sda));
extern int D_L23_001AFA30 __attribute__((sda));
extern int D_L23_001AFA34 __attribute__((sda));
extern int D_L23_001AFA38 __attribute__((sda));
extern float D_L23_001AFA3C __attribute__((sda));
extern float D_L23_001AFA40 __attribute__((sda));
extern float D_L23_001AFA44 __attribute__((sda));
extern int D_L23_001AFA48 __attribute__((sda));

extern char D_L23_001BA640[];

extern float func_002A7878(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern u64 func_0027C878(int);
extern void func_002FC560(u32, u64);
extern void func_00280B90(void *, int, int);

/* Makes the beam strength swing up and down, then draws a glowing beam strip between the enemy and its helper object. */
void func_L23_003C1E88(char *moby) {
    TI128 pullBack;
    TI128 sideways;
    TI128 toCamera;
    TI128 forward;
    TI128 endPoint;
    TI128 startPoint;
    char packet[0x90] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);
    TI128 *startPtr;
    TI128 *forwardPtr;
    char *mobyPos;
    char *mobyForward;
    float width;
    float level;
    float limit;
    u64 texBits;
    int color;
    float zero;
    long long gifBits;

    if (*(short *)(vars + 0x3BC) > 0) {
        level = *(float *)(vars + 0x3B8) + RandomFloatRange(D_L23_001AFA40, D_L23_001AFA44);
        limit = D_L23_001AFA3C;
        *(float *)(vars + 0x3B8) = level;
        if (limit < level) {
            *(float *)(vars + 0x3B8) = limit;
            *(short *)(vars + 0x3BC) = -1;
        }
    } else {
        level = *(float *)(vars + 0x3B8) - RandomFloatRange(D_L23_001AFA40, D_L23_001AFA44);
        limit = (float)D_L23_001AFA38;
        *(float *)(vars + 0x3B8) = level;
        if (level < limit) {
            *(float *)(vars + 0x3B8) = limit;
            *(short *)(vars + 0x3BC) = 1;
        }
    }
    startPtr = &startPoint;
    width = D_L23_001AFA18;
    qcopy(startPtr, moby + 0x10);
    mobyPos = moby + 0x10;
    FastVecSub(&endPoint, *(char **)(vars + 0x2A0) + 0x10, mobyPos);
    FastVecScale(&endPoint, &endPoint, D_L23_001AFA1C);
    FastVecAdd(&endPoint, &endPoint, startPtr);
    mobyForward = moby + 0xE0;
    forwardPtr = &forward;
    qcopy(forwardPtr, mobyForward);
    FastVecSub(&toCamera, startPtr, gCameraPosition_L23);
    FastVecCross(&sideways, forwardPtr, &toCamera);
    vec_scale_to_length(&sideways, &sideways, width);
    vec_scale_to_length(&pullBack, &toCamera, -D_L23_001AFA20);
    FastVecAdd(startPtr, startPtr, &pullBack);
    FastVecAdd(&endPoint, &endPoint, &pullBack);
    FastVecAdd(packet + 0x00, startPtr, &sideways);
    FastVecSub(packet + 0x10, startPtr, &sideways);
    FastVecAdd(packet + 0x20, &endPoint, &sideways);
    FastVecSub(packet + 0x30, &endPoint, &sideways);
    texBits = GetEffectTextureDescriptor(D_L23_001AFA24);
    color = D_L23_001AFA48;
    *(int *)(packet + 0x4C) = color;
    *(u64 *)(packet + 0x78) = texBits;
    *(unsigned long long *)(packet + 0x80) = 0xFF9000000260ULL;
    *(u64 *)(packet + 0x70) = 0;
    *(int *)(packet + 0x48) = color;
    *(int *)(packet + 0x44) = color;
    *(int *)(packet + 0x40) = color;
    VU1_addGSregister(0x47, 0x53001);
    gifBits = D_L23_001AFA28;
    gifBits |= (long long)D_L23_001AFA2C << 2;
    gifBits |= (long long)D_L23_001AFA30 << 4;
    gifBits |= (long long)D_L23_001AFA34 << 6;
    gifBits |= (long long)(int)*(float *)(vars + 0x3B8) << 32;
    *(int *)(packet + 0x54) = 0;
    *(float *)(packet + 0x5C) = 1.0f;
    *(int *)(packet + 0x50) = 0;
    *(long long *)(packet + 0x88) = gifBits;
    *(int *)(packet + 0x64) = 0;
    zero = *(float *)(packet + 0x50);
    *(float *)(packet + 0x68) = zero;
    *(float *)(packet + 0x6C) = 1.0f;
    *(float *)(packet + 0x60) = zero;
    *(float *)(packet + 0x58) = 0.99f;
    *(float *)(packet + 0x50) = 0.99f;
    draw_world_quad(packet, 0, 0);
}

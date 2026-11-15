#include "common.h"

typedef struct { char pad[0x228]; float f228, f22C; } WaterFog;
typedef struct { char pad0[0x348]; short f348; char pad34A[0x1F4A]; int currentState; } WaterHero;
typedef struct { char pad[0x140]; float x, y, z; } WaterCamera;
typedef struct {
    int color0, color1, color2, color3, color4;
    float f14, range;
    int texture;
    int f20;
    float f24, reach, f2C;
} WaterState;

extern WaterFog D_L06_001BDD40;
extern WaterHero D_00189E20;
extern WaterCamera D_L06_001B9700;
extern int D_L06_001A8A48 MACRO_ADDR;
extern int D_001A79F0 __attribute__((sda));
extern float D_L06_001B3290[3][4] __attribute__((sda));
extern float D_L06_001B9A70[][4];
extern float D_L06_001B3280 MACRO_ADDR;
extern float D_L06_001B0060[] SDATA(D_L06_001B0060);
extern float D_L06_001B3270[][2] MACRO_ADDR;
extern float D_L06_0023E5A0[][3], D_L06_0023E9A0[][3];
extern int D_L06_0023E8A0[], D_L06_0023ECA0[];
extern float D_L06_0023EDA0[][2], D_L06_0023EFA0[][2];

extern void func_002FC560(int, unsigned long);
extern unsigned long func_0027C878(int);
extern void func_00280328(void);
extern void func_00282DD8(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00283D38(int, int, float);
extern void func_00282D30(void *, void *, float);
extern void func_00281810(int, void *, void *, void *, int);
extern float func_00282E20(void *);
extern void func_00282A28(void);

/* Draws the level's water sheet: a fading edge strip and two scrolling layers of grid cells
 * around the camera. RAC1's draw_pokitaru_ocean is its counterpart. */
void func_L06_00402570(unsigned char *owner)
{
    float edgeStart[4], edgeOffset[4], axisX[4], axisY[4], corner[4][4], topEdge[4], bottomEdge[4];
    WaterState *state;
    int layer;
    float saved22C;
    float saved228;
    int i, count, color;
    int nearColor, farColor;
    float range, heightAboveWater, waveLift, cellX, cellY, blend;

    saved228 = D_L06_001BDD40.f228;
    state = *(WaterState **)(owner + 0x68);
    saved22C = D_L06_001BDD40.f22C;
    if (gHeroState.currentState != 28 && !D_L06_001A8A48) {
        D_L06_001BDD40.f228 = 255.0f;
        D_L06_001BDD40.f22C = 249.9f;
    }
    VU1_addGSregister(0x42, 0x3200000044UL);
    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x14, 0xFF9000000260UL);
    if (state->color0 < 0)
        VU1_addGSregister(0x47, 0x5310B);
    else
        VU1_addGSregister(0x47, 0x513F1);
    VU1_addGSregister(6, GetEffectTextureDescriptor(22));
    font_queue_vu_state();
    if (gCurrentMapIndex == 13 || (gCurrentMapIndex == 16 && gHeroState.f348 == 1)) {
        qcopy(D_L06_001B3290[1], D_L06_001B9A70[1]);
        D_L06_001B3290[2][0] = 0;
        D_L06_001B3290[2][1] = 0;
        D_L06_001B3290[2][2] = 1;
        D_L06_001B3290[2][3] = 0;
        FastVecCross(D_L06_001B3290[0], D_L06_001B3290[2], D_L06_001B3290[1]);
        axisX[0] = 1;
        axisX[1] = 0;
        axisX[2] = 0;
        axisX[3] = 1;
        matrix_mul_vec3(axisX, axisX, D_L06_001B3290);
        axisY[0] = 0;
        axisY[1] = 1;
        axisY[2] = 0;
        axisY[3] = 1;
        matrix_mul_vec3(axisY, axisY, D_L06_001B3290);
    } else {
        axisX[0] = 1;
        axisX[1] = 0;
        axisX[2] = 0;
        axisX[3] = 1;
        matrix_mul_vec3(axisX, axisX, D_L06_001B9A70);
        axisY[0] = 0;
        axisY[1] = 1;
        axisY[2] = 0;
        axisY[3] = 1;
        matrix_mul_vec3(axisY, axisY, D_L06_001B9A70);
    }
    if (gCurrentMapIndex != 16) {
        axisX[2] = 0;
        vec_scale_to_length(axisX, axisX, 1);
        axisY[2] = 0;
        vec_scale_to_length(axisY, axisY, 1);
    } else if (gHeroState.f348 == 1) {
        axisX[0] = 0;
        axisX[1] = 1;
        axisX[2] = 0;
        axisX[3] = 1;
        axisY[0] = -0.79706f;
        axisY[1] = 0;
        axisY[2] = -0.60389f;
        axisY[3] = 1.00405f;
    }
    if (gCurrentMapIndex != 16) {
        vec_scale_to_length(edgeStart, axisX, -75);
        vec_scale_to_length(edgeOffset, axisY, -87);
        FastVecAdd(corner[0], edgeStart, edgeOffset);
        vec_scale_to_length(edgeOffset, axisY, 87);
        FastVecAdd(corner[2], edgeStart, edgeOffset);
        vec_scale_to_length(edgeStart, axisX, state->reach);
        vec_scale_to_length(edgeOffset, axisY, -750);
        FastVecAdd(corner[1], edgeStart, edgeOffset);
        vec_scale_to_length(edgeOffset, axisY, 750);
        FastVecAdd(corner[3], edgeStart, edgeOffset);
    } else {
        vec_scale_to_length(edgeStart, axisX, -150);
        vec_scale_to_length(edgeOffset, axisY, -175);
        FastVecAdd(corner[0], edgeStart, edgeOffset);
        vec_scale_to_length(edgeOffset, axisY, 175);
        FastVecAdd(corner[2], edgeStart, edgeOffset);
        vec_scale_to_length(edgeStart, axisX, state->reach);
        vec_scale_to_length(edgeOffset, axisY, -1500);
        FastVecAdd(corner[1], edgeStart, edgeOffset);
        vec_scale_to_length(edgeOffset, axisY, 1500);
        FastVecAdd(corner[3], edgeStart, edgeOffset);
    }
    for (i = 0; i < 4; i++) {
        float *cornerPoint = corner[i];
        FastVecAdd(cornerPoint, cornerPoint, &gCameraState_L06.x);
        cornerPoint[2] = gWaterSurfaceHeight;
    }
    FastVecSub(topEdge, corner[1], corner[0]);
    FastVecSub(bottomEdge, corner[3], corner[2]);
    blend = 10;
    for (i = 0; i < 12; i += 2) {
        float fraction = IntToFloat(i) * 0.1f;
        color = FastTweenColor(state->color0, state->color1, IntToFloat(i) / blend);
        FastVecScale(edgeStart, topEdge, fraction);
        D_L06_0023E8A0[i] = color;
        D_L06_0023EDA0[i][0] = 0;
        D_L06_0023EDA0[i][1] = 0;
        FastVecAdd(edgeStart, edgeStart, corner[0]);
        D_L06_0023E5A0[i][0] = edgeStart[0];
        D_L06_0023E5A0[i][1] = edgeStart[1];
        D_L06_0023E5A0[i][2] = edgeStart[2];
        FastVecScale(edgeStart, bottomEdge, fraction);
        D_L06_0023E8A0[i + 1] = color;
        D_L06_0023EDA0[i + 1][0] = 0;
        D_L06_0023EDA0[i + 1][1] = 0;
        FastVecAdd(edgeStart, edgeStart, corner[2]);
        D_L06_0023E5A0[i + 1][0] = edgeStart[0];
        D_L06_0023E5A0[i + 1][1] = edgeStart[1];
        D_L06_0023E5A0[i + 1][2] = edgeStart[2];
    }
    DrawGlintEffect(12, D_L06_0023E5A0, D_L06_0023E8A0, D_L06_0023EDA0, 1);
    VU1_addGSregister(0x42, 0x8000000048UL);
    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x14, 0xFF9000000260UL);
    VU1_addGSregister(0x47, 0x513F1);
    nearColor = state->color3;
    farColor = state->color4;
    range = state->range;
    if (gHeroState.currentState == 28 || D_L06_001A8A48) {
        if (range > 32)
            range = 32;
    }

    for (layer = 0; layer < 2; layer++) {
        int textureOffset = layer + 63;
        VU1_addGSregister(6, GetEffectTextureDescriptor(state->texture + textureOffset));
        for (cellY = range * -2; cellY < range * 2; cellY += range) {
            count = 0;
            heightAboveWater = gCameraState_L06.z - gWaterSurfaceHeight;
            if (heightAboveWater < 10)
                heightAboveWater = 10;
            waveLift = heightAboveWater * range * 0.00002f;
            if (waveLift < 0.125f)
                waveLift = 0.125f;
            for (cellX = range * -2; cellX < range * 2; cellX += range) {
                D_L06_0023EFA0[count][0] = cellX / (range * 2) * D_L06_001B0060[layer] + D_L06_001B3270[layer][0];
                D_L06_0023EFA0[count][1] = cellY / (range * 2) * D_L06_001B0060[layer] + D_L06_001B3270[layer][1];
                D_L06_0023E9A0[count][0] = cellX + gCameraState_L06.x + 1;
                D_L06_0023E9A0[count][1] = cellY + gCameraState_L06.y + 1;
                D_L06_0023E9A0[count][2] = gWaterSurfaceHeight + waveLift;
                i = count + 1;
                D_L06_0023EFA0[i][0] = cellX / (range * 2) * D_L06_001B0060[layer] + D_L06_001B3270[layer][0];
                D_L06_0023EFA0[i][1] = (cellY + range) / (range * 2) * D_L06_001B0060[layer] + D_L06_001B3270[layer][1];
                D_L06_0023E9A0[i][0] = cellX + gCameraState_L06.x + 1;
                D_L06_0023E9A0[i][1] = (cellY + range) + gCameraState_L06.y + 1;
                D_L06_0023E9A0[i][2] = gWaterSurfaceHeight + waveLift;
                i = count + 2;
                D_L06_0023EFA0[i][0] = (cellX + range) / (range * 2) * D_L06_001B0060[layer] + D_L06_001B3270[layer][0];
                D_L06_0023EFA0[i][1] = cellY / (range * 2) * D_L06_001B0060[layer] + D_L06_001B3270[layer][1];
                D_L06_0023E9A0[i][0] = (cellX + range) + gCameraState_L06.x + 1;
                D_L06_0023E9A0[i][1] = cellY + gCameraState_L06.y + 1;
                D_L06_0023E9A0[i][2] = gWaterSurfaceHeight + waveLift;
                i = count + 3;
                D_L06_0023EFA0[i][0] = (cellX + range) / (range * 2) * D_L06_001B0060[layer] + D_L06_001B3270[layer][0];
                D_L06_0023EFA0[i][1] = (cellY + range) / (range * 2) * D_L06_001B0060[layer] + D_L06_001B3270[layer][1];
                D_L06_0023E9A0[i][0] = (cellX + range) + gCameraState_L06.x + 1;
                D_L06_0023E9A0[i][1] = (cellY + range) + gCameraState_L06.y + 1;
                D_L06_0023E9A0[i][2] = gWaterSurfaceHeight + waveLift;
                for (i = count; i < count + 4; i++) {
                    edgeStart[0] = D_L06_0023E9A0[i][0] - gCameraState_L06.x;
                    edgeStart[1] = D_L06_0023E9A0[i][1] - gCameraState_L06.y;
                    edgeStart[2] = D_L06_0023E9A0[i][2] - gCameraState_L06.z;
                    edgeStart[3] = 1;
                    blend = vec_length_xy(edgeStart) / (range * 2);
                    if (blend > 1)
                        blend = 1;
                    D_L06_0023ECA0[i] = FastTweenColor(nearColor, farColor, blend);
                }
                count += 4;
                if (count >= 64)
                    TrapAlways();
            }
            DrawGlintEffect(count, D_L06_0023E9A0, D_L06_0023ECA0, D_L06_0023EFA0, 1);
        }
    }
    D_L06_001BDD40.f228 = saved228;
    D_L06_001BDD40.f22C = saved22C;
    VU1_addGSregister(0x47, 0x5360B);
}

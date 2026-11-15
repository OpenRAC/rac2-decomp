#include "common.h"

/* func_L06_00403130 updates the level's water sheet; RAC1's ocean_pokitaru_update
 * (homing_missile_and_water_sheet.c) is its counterpart. Its draw callback is
 * func_L06_00402570 (L06_00402570.c), which reads the same layer tables. */

typedef int OceanQuad __attribute__((mode(TI)));
typedef union { OceanQuad q; float f[4]; } OceanVector;
typedef struct { float u, v; } OceanUV;

typedef struct {
    int drawMode;          /* 0x00: its sign selects the draw list */
    char pad04[0x10];
    float level;           /* 0x14 */
    float scale;           /* 0x18 */
    char pad1C[0x4];
    float limit;           /* 0x20 */
    char pad24[0xC];
    int outerArea;         /* 0x30 */
    int innerArea;         /* 0x34 */
    int f38;               /* 0x38 */
    float amplitude;       /* 0x3C */
} OceanVars;

typedef struct {
    char pad00[0x20];
    unsigned char state;   /* 0x20 */
    char pad21[0xF];
    unsigned char f30;     /* 0x30 */
    char pad31[0x37];
    OceanVars *vars;       /* 0x68 */
} OceanMoby;

typedef struct {
    char pad000[0x80];
    float position[4];     /* 0x80 */
    char pad090[0x16E];
    short waterState;      /* 0x1FE */
    char pad200[0x2094];
    int action;            /* 0x2294 */
    int pad2298;
    int animation;         /* 0x229C */
} OceanHero;

typedef struct {
    char pad000[0x140];
    OceanVector pos;       /* 0x140 */
    float f150, f154;
    float angle;           /* 0x158 */
} OceanCamera;

extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void gfx_add_draw_callback_second(void (*)(void *), void *);
extern void DrawOceanWaterSheet(void *);
extern int IsPointInCuboid(void *, int);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_b(float);

extern OceanHero g_hero_state;
extern OceanCamera g_camera_state;
extern int D_L06_001C9DC0;
extern int g_current_map_index __attribute__((sda));
extern float D_001A7928 __attribute__((sda));
extern int D_L06_001A9010 __attribute__((sda));
extern int D_L06_001A8A48 __attribute__((sda));
extern int D_L06_001B2348 __attribute__((sda));
extern float g_water_surface_height __attribute__((sda));
extern float D_L06_001B3284 __attribute__((sda));
extern OceanVector D_L06_001B9A70[];
extern OceanVector D_L06_001B3290[3] __attribute__((sda));
extern OceanUV D_L06_001B3270[] __attribute__((sda));
extern OceanVector D_L06_001B3260 SDATA(D_L06_001B3260);
extern float D_L06_001B0060[] SDATA(D_L06_001B0060);
/* Layer scroll speeds: retail reads the u column through $gp and the v column
 * (0x001B0074) through an absolute address, so the table has both views. */
extern OceanUV D_L06_001B0070[] __attribute__((sda));
extern OceanUV D_L06_001B0070_gp[] SDATA(D_L06_001B0070);

void UpdateOceanWaterSheet(OceanMoby *moby)
{
    OceanVector movement, scaled;
    OceanVars *vars = moby->vars;
    float range, tide;
    int i;

    if (D_L06_001C9DC0 != vars->f38)
        return;
    if (g_current_map_index == 13 && g_hero_state.position[2] < 88.0f && g_hero_state.action != 116)
        return;
    if (g_current_map_index == 11 && D_L06_001A9010 != 0)
        return;
    D_L06_001B3284 = vars->level;
    if (moby->state == 0) {
        moby->state = 1;
        moby->f30 = 0xFF;
        qcopy(&D_L06_001B3290[0], &D_L06_001B9A70[0]);
        qcopy(&D_L06_001B3290[1], &D_L06_001B9A70[1]);
        qcopy(&D_L06_001B3290[2], &D_L06_001B9A70[2]);
        for (i = 0; i < 2; i++) {
            D_L06_001B3270[i].u = 0.0f;
            D_L06_001B3270[i].v = 0.0f;
        }
        qcopy(&D_L06_001B3260, &g_camera_state.pos);
        D_L06_001B3284 = vars->level;
        return;
    }
    if (IsPointInCuboid(g_hero_state.position, vars->outerArea)) {
        g_hero_state.waterState = 0;
        return;
    }
    if (IsPointInCuboid(g_hero_state.position, vars->innerArea) && g_current_map_index != 13 &&
        (vars->f38 != 0 || g_camera_state.angle > 0.031f || g_camera_state.angle < -1.62f ||
         (unsigned int)(g_hero_state.animation - 17) < 2)) {
        g_hero_state.waterState = 0;
        return;
    }
    if (IsPointInCuboid(g_hero_state.position, vars->innerArea)) {
        g_hero_state.waterState = 0;
        return;
    }
    range = vars->scale;
    if (g_hero_state.action == 28 || D_L06_001A8A48 != 0) {
        if (range > 32.0f)
            range = 32.0f;
    }
    g_hero_state.waterState = 2;
    FastVecSub(&movement, &g_camera_state.pos, &D_L06_001B3260);
    qcopy(&D_L06_001B3260, &g_camera_state.pos);
    if (!(g_camera_state.pos.f[2] > vars->limit))
        return;
    for (i = 0; i < 2; i++) {
        float layer = D_L06_001B0060[i] + D_L06_001B0060[i];
        FastVecScale(&scaled, &movement, layer / (range * 5.0f));
        if (scaled.f[0] > 1.0f || scaled.f[0] < 1.0f)
            scaled.f[0] -= IntToFloat(FloatToInt(scaled.f[0]));
        if (scaled.f[1] > 1.0f || scaled.f[1] < 1.0f)
            scaled.f[1] -= IntToFloat(FloatToInt(scaled.f[1]));
        D_L06_001B3270[i].u += scaled.f[0];
        D_L06_001B3270[i].v += scaled.f[1];
        if (D_L06_001B3270[i].u > 1.0f)
            D_L06_001B3270[i].u -= 1.0f;
        if (D_L06_001B3270[i].u < -1.0f)
            D_L06_001B3270[i].u += 1.0f;
        if (D_L06_001B3270[i].v > 1.0f)
            D_L06_001B3270[i].v -= 1.0f;
        if (D_L06_001B3270[i].v < -1.0f)
            D_L06_001B3270[i].v += 1.0f;
    }
    tide = IntToFloat(D_L06_001B2348 % 360) * 0.017444445f - 3.14f;
    g_water_surface_height = D_L06_001B3284 + math_fast_sin_or_cos_b(tide) * vars->amplitude;
    for (i = 0; i < 2; i++) {
        D_L06_001B3270[i].u += D_L06_001B0070_gp[i].u * D_001A7928;
        if (D_L06_001B3270[i].u > 1.0f)
            D_L06_001B3270[i].u -= 1.0f;
        if (D_L06_001B3270[i].u < -1.0f)
            D_L06_001B3270[i].u += 1.0f;
        D_L06_001B3270[i].v += D_L06_001B0070[i].v * D_001A7928;
        if (D_L06_001B3270[i].v > 1.0f)
            D_L06_001B3270[i].v -= 1.0f;
        if (D_L06_001B3270[i].v < -1.0f)
            D_L06_001B3270[i].v += 1.0f;
    }
    if (vars->drawMode < 0)
        gfx_add_draw_callback_second(DrawOceanWaterSheet, moby);
    else
        gfx_add_draw_callback_first(DrawOceanWaterSheet, moby);
}

#include "names.h"
typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef short s16;

extern s32 D_L02_001A9018;
extern u16 **D_L02_001A9014;
extern char *D_L02_001B3C1C;
extern char D_L02_001B1510[8] __attribute__((sda));
extern char D_L02_001BA500[];

extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern int func_L00_0031C998(int, int, float);
extern void func_L00_00325AE8(void *, int, float, float);

/* Draws glowing markers at nearby records that face the player. The closer they face, the brighter they get. */
void func_L02_004004D0(char *moby) {
    char *state = *(char **)(moby + 0x68);
    s32 listIndex = *(s32 *)(state + 0x104);
    u16 *listStart;
    u16 *entry;
    char *record;
    float v0[4];
    float v1[4];
    float v2[4];
    float v3[4];
    float dot;

    if (listIndex == -1)
        return;
    if (listIndex >= D_L02_001A9018)
        return;
    listStart = D_L02_001A9014[listIndex];
    if (listStart == 0)
        return;
    entry = listStart;
    do {
        record = D_L02_001B3C1C + ((*entry & 0x7FFF) << 6);
        *(TI128 *)v0 = *(TI128 *)(record + 0x30);
        matrix_mul_vec3(v1, D_L02_001B1510, record);
        FastVecAdd(v0, v0, v1);
        FastVecSub(v2, gCameraPosition_L02, v0);
        vec_scale_to_length(v2, v2, 1.0f);
        FastVecScale(v3, record + 0x20, -1.0f);
        dot = FastVecDot(v2, v3);
        if (dot > 0.5f) {
            dot = dot - 0.5f;
            dot = dot + dot;
            DrawBillboardQuad_L00(v0, LerpIntegerFraction(0xFF8020, 0x88FF8020, dot * dot), 3.0f, 1.0f);
        }
    } while ((s16)*entry++ >= 0);
}

#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
typedef unsigned short u16;

typedef struct {
    s32 pad0;
    s32 pad1;
    s32 pad2;
    s32 fieldC;
} L06Entry;

extern L06Entry D_L06_00139A28[];

extern s32 func_L01_003246F8();

extern u8 D_001A7BC8[] __attribute__((sda));
extern u8 D_001A7BE0 __attribute__((sda));
extern char D_00189EA0[];
extern int D_L06_001B2348 __attribute__((sda));
extern void func_002A7750(void *, int, int);
extern float func_00282E80(void *, void *);
extern float func_00282DF0(void *);
extern void func_002AD7B8(int);
extern float func_002AA2E8(float *, float, float);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L06_003E1040(void);
extern int func_00282948(int *);
extern void func_0029F338(void *);
extern void func_00282F20(void *, void *, float);


typedef struct { float point[4][4]; u32 color[4]; float uv[8]; unsigned long tag[4]; } L06Quad;
extern void func_002FC560(int, unsigned long);
extern void func_00281DE8(void *, int, int, int);
extern void func_L01_0031A278(void *, void *, float, float, float);
extern void func_00280B90(void *, int, int);

/* func_L06_0035EA68 is defined in L06_0035EA68-fall.c. */

/* Looks up a table entry from an id and stores a value in it. */
void func_L06_0036F728(s32 id, s32 value) {
    s32 entryIndex = FindKeyInPairTable(id);
    if (entryIndex != -1)
        D_L06_00139A28[entryIndex].fieldC = value;
}

/* func_L06_00382608 is defined in L06_00382608.c. */

extern float func_00282E48(char *, char *);
extern float func_00282C48(float);

/* Finds the point in a list whose distance from a given point is closest to a wanted distance. Returns its index. */
s32 func_L06_00382850(char *point, char *pointList, float wantedDistance) {
    s32 i;
    s32 best = 0;
    float bestValue = 1.0e11f;
    float baseDistance = wantedDistance;

    for (i = 0; i < *(s32 *)pointList; i++) {
        float distance = fast_vec_dist(pointList + 0x10 + i * 0x10, point);
        if (FloatAbs(distance - baseDistance) < bestValue) {
            bestValue = distance;
            best = i;
        }
    }
    return best;
}


extern void ref_L06_0039A2F0_00(void *, s32, s32);

/* Looks for a matching record in a small list and updates it, or adds a new record at the end of the list. */
void func_L06_0039A2F0(s32 valueA, s32 valueB, s32 owner, s32 mode, s32 *list)
{
    char *newEntry;
    s32 count;
    s32 index;
    s32 tag = mode;
    s16 key;
    s16 subtype = *(s16 *)(owner + 0xB2);
    s16 classId = *(s16 *)(owner + 0xAA);

    if (mode == 1)
        key = (s16)(valueA - owner);
    else
        key = (s16)(valueA - *(u16 *)(owner + 0x68));

    for (index = 0; index < list[0]; index++) {
        char *entry = (char *)list + 4 + index * 16;
        if (*(s32 *)entry != key) continue;
        if (*(u16 *)(entry + 8) != valueB) continue;
        if (subtype != *(s16 *)(entry + 0xC)) continue;
        if (classId != *(s16 *)(entry + 0xE)) continue;
        tag = *(s16 *)(entry + 0xA);
        if (tag != 0) {
            ref_L06_0039A2F0_00(entry + 4, valueA, valueB);
            return;
        }
    }
    count = list[0];
    newEntry = (char *)list + 4 + count * 16;
    list[0] = count + 1;
    *(s32 *)newEntry = key;
    ref_L06_0039A2F0_00(newEntry + 4, valueA, valueB);
    *(u16 *)(newEntry + 8) = valueB;
    *(s16 *)(newEntry + 0xA) = tag;
    *(s16 *)(newEntry + 0xC) = subtype;
    *(s16 *)(newEntry + 0xE) = classId;
}

/* Updates a collectable pickup (moby class 750): it waits for the hero to touch it, gives the item, then shrinks and fades away. */
void func_L06_003E0D88(u8 *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float scale, inverse;
    switch ((u8)moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        if (!D_001A7BC8[*(int *)vars]) SetMobyState(moby, 1, -1);
        else MarkMobySpawned(moby);
        break;
    case 1:
        if (vec_distance_xy(moby + 0x10, gHeroPosition) < 2.0f &&
            FloatAbs(*(float *)(moby + 0x18) - *(float *)(gHeroPosition + 8)) < 2.0f) {
            MarkFlagAndAppendToList(*(int *)vars);
            SetMobyState(moby, 2, -1);
            *(u16 *)(moby + 0x34) |= 0x100;
            *(int *)(vars + 8) = 180;
        }
        if (*(int *)vars == 24 && D_001A7BE0) {
            MarkFlagAndAppendToList(24);
            SetMobyState(moby, 2, -1);
            *(u16 *)(moby + 0x34) |= 0x100;
            *(int *)(vars + 8) = 180;
        }
        break;
    case 2:
        if ((*(u16 *)(moby + 0x34) ^ 1) & 1) {
            scale = FastVecLength(moby + 0xC0);
            ApproachValue(&scale, 0, 0.06666667014360428f);
            inverse = 2.0f - scale;
            vec_scale_to_length(moby + 0xC0, moby + 0xC0, scale);
            vec_scale_to_length(moby + 0xD0, moby + 0xD0, scale);
            vec_scale_to_length(moby + 0xE0, moby + 0xE0, inverse);
            if (scale <= 0) {
                moby[0x31] = 0;
                *(u16 *)(moby + 0x34) |= 1;
            }
        }
        AddDrawCallbackToList1(ShowPickupNotice, moby);
        if ((D_L06_001B2348 ^ 1) & 1) (*(int *)(vars + 4))++;
        if (FastFloatHelperD((int *)(vars + 8))) {
            ApproachValue((float *)(vars + 12), 0, 0.05000000447034836f);
            if (*(float *)(vars + 12) <= 0) MarkMobySpawned(moby);
        } else {
            ApproachValue((float *)(vars + 12), 1, 0.05000000447034836f);
        }
        break;
    }
}



/* Returns 1 if this is a Taxi moby that is in one of its flying states (2 to 6). */
s32 func_L06_003E3CC8(u8 *moby) {
    if (*(s16 *)(moby + 0xAA) != 0x330 /* Taxi */)
        return 0;
    return (u32)(moby[0x20] - 2) < 5;
}







extern char D_L17_001FE880[];
extern char D_L17_00296F80[];
extern u8 D_00189E20[];
extern void func_00283098(void *, void *, void *);
extern void func_2EEEB8(void *, void *, void *);

/* Same body as func_L17_003C3250, with this function's own callees. */
/* Moves a set of seven local points to follow the moby, and stores them in a shared table entry. */
void func_L06_003E4FA0(char *moby)
{
    char *vars;
    char *outPoint;
    char *sourcePoint;
    char *position;
    char *matrix;
    char *base;
    int tableEntry;
    int i;

    vars = *(char **)(moby + 0x68);
    tableEntry = *(int *)(vars + 0xF8);
    if (tableEntry == -1)
        return;
    tableEntry = *(int *)(gPathTable_L17 + tableEntry * 4);
    if (*(int *)tableEntry != 7)
        return;
    matrix = moby + 0xC0;
    position = moby + 0x10;
    sourcePoint = D_L17_00296F80;
    outPoint = tableEntry + 0x10;
    for (i = 6; i >= 0; i--) {
        matrix_mul_vec3(outPoint, sourcePoint, matrix);
        sourcePoint += 0x10;
        func_2EEEB8(outPoint, outPoint, position);
        outPoint += 0x10;
    }
    base = gHeroState;
    *(unsigned short *)(base + 0x24FE) = *(unsigned short *)(vars + 0xF8);
}



/* func_L06_003E5D30 is defined in L06_003E5D30-g8.c. */

/* func_L06_004009B8 is defined in L06_004009B8-g8.c. */

/* func_L06_00402570 is defined in L06_00402570.c. */

/* func_L06_00403130 is defined in L06_00403130.c. */

/* func_L06_00403710 is defined in L06_00403710-g8.c. */

/* func_L06_00403DA8 is defined in L06_00403DA8.c. */


/* func_L06_00444D00 is defined in L06_00444D00.c. */

/* func_L06_004638F0 is defined in L06_004638F0.c. */


/* Draws a flat textured square twice, the second one slightly in front, as the look of the swaying effect moby. */
void func_L06_00463FC0(char *moby)
{
    L06Quad q;
    u8 *vars = *(u8 **)(moby + 0x68);
    if (vars[0x4D]) {
        q.uv[0] = 0; q.uv[1] = 0; q.uv[2] = 0; q.uv[3] = 1;
        q.uv[4] = 1; q.uv[5] = 0; q.uv[6] = 1; q.uv[7] = 1;
    } else {
        q.uv[0] = 0; q.uv[1] = 0; q.uv[2] = 1; q.uv[3] = 0;
        q.uv[4] = 0; q.uv[5] = 1; q.uv[6] = 1; q.uv[7] = 1;
    }
    *(u32 *)(vars + 0x58) &= 0xFFFFFF;
    *(u32 *)(vars + 0x58) += (u8)moby[0x23] << 24;
    q.color[0] = q.color[1] = q.color[2] = q.color[3] = *(u32 *)(vars + 0x58);
    q.tag[0] = 0;
    VU1_addGSregister(0x42, 0x8000000048UL);
    VU1_addGSregister(0x14, 0xFF9000000260UL);
    VU1_addGSregister(0x47, 0x50000);
    InitQuadPacketState(&q, vars[0x4E], 0, 0x80);
    ComputeMobyLocalPoint(moby, q.point[0], 0, *(float *)(vars + 0x50), -*(float *)(vars + 0x54));
    ComputeMobyLocalPoint(moby, q.point[1], 0, *(float *)(vars + 0x50), *(float *)(vars + 0x54));
    ComputeMobyLocalPoint(moby, q.point[2], 0, -*(float *)(vars + 0x50), -*(float *)(vars + 0x54));
    ComputeMobyLocalPoint(moby, q.point[3], 0, -*(float *)(vars + 0x50), *(float *)(vars + 0x54));
    draw_world_quad(&q, 0, 0);
    InitQuadPacketState(&q, vars[0x4F], 0, 0x80);
    VU1_addGSregister(0x47, 0x50000);
    ComputeMobyLocalPoint(moby, q.point[0], -0.001f, *(float *)(vars + 0x50), -*(float *)(vars + 0x54));
    ComputeMobyLocalPoint(moby, q.point[1], -0.001f, *(float *)(vars + 0x50), *(float *)(vars + 0x54));
    ComputeMobyLocalPoint(moby, q.point[2], -0.001f, -*(float *)(vars + 0x50), -*(float *)(vars + 0x54));
    ComputeMobyLocalPoint(moby, q.point[3], -0.001f, -*(float *)(vars + 0x50), *(float *)(vars + 0x54));
    draw_world_quad(&q, 0, 0);
}

extern s32 D_L06_001B9890;

/* Sets a camera distance value, unless the camera is switched off. */
void func_L06_00475C10(float distance) {
    s32 cameraState = D_L06_001B9890;
    if (*(s16 *)(cameraState + 0x86) == 0)
        *(float *)(*(s32 *)(cameraState + 0x70) + 0x24C) = distance;
}



/* func_L06_0047A408 is defined in L06_0047A408.c. */

/* func_L06_0047AC68 is defined in L06_0047AC68-g8.c. */

/* Separate camera activate, update and exit entries, shared by seven levels. */
/* Empty camera activate entry. */
void func_L06_0047C1D0(void *camera)
{
}

/* Empty camera update entry. */
void func_L06_0047C1D8(void *camera)
{
}

/* Empty camera exit entry. */
void func_L06_0047C1E0(void *camera)
{
}

#include "include_asm.h"

#include "common.h"
extern int D_001A8BB0;
extern int D_001A8BB0_gp SDATA(D_001A8BB0);
extern short D_00152C00[];
extern char D_001ABF90[32] SDATA(D_001ABF90);
extern char D_001ABFB0[64] SDATA(D_001ABFB0);
typedef struct {
    float v[4];
} Vector;
typedef struct {
    Vector rows[4];
    int colors[4];
    char block[32];
    long long tags[4];
} Packet;
extern void func_00282D60(void *, void *, float);
extern int func_00283EB0(void *, int *, float);
extern u64 func_0027C878(int);
extern void func_00282B50(void *, void *, int);
extern void func_00282D30(void *, void *, float);
extern float func_002A89A8(void *, int, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);

void func_PAL_L08_003714F8(char *object)
{
    float projected[4];
    Packet packet;
    float pos[4];
    int alpha;
    int i;
    float height;
    char *point;

    alpha = 0;
    func_00282D60(projected, object, 0.0009765625f);
    if (func_00283EB0(projected, &alpha, 32.0f) < 0)
        return;
    if (D_001A8BB0_gp == 6 && D_00152C00[16] == 1 && D_00152C00[17] >= 126) {
        alpha -= (D_00152C00[17] - 125) * 4;
        if (alpha <= 0)
            return;
    }
    packet.tags[1] = func_0027C878(0);
    packet.tags[2] = 0xFF9000000260ULL;
    packet.tags[3] = 0x8000000044ULL;
    packet.tags[0] = 0;
    func_00282B50(packet.block, D_001ABF90, 32);
    func_00282D30(pos, object, 0.0009765625f);
    height = *(float *)(object + 24) + 0.1f;
    if (D_001A8BB0 == 6 || D_001A8BB0 == 0)
        height = func_002A89A8(object + 16, 0, 0.5f) + 0.1f;
    point = object + 16;
    for (i = 0; i < 4; i++) {
        Vector *row;

        packet.colors[i] = ((alpha >> 1) << 24) | 0x808080;
        row = &packet.rows[i];
        func_00283098(row, D_001ABFB0 + 16 * i, object + 192);
        func_00282CC0(row, row, point);
        row->v[2] = height;
    }
    func_00280B90(packet.rows, 0, 0);
}

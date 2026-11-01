/* func_L00_003E6030, 1220 bytes, 27 places. USA v1.01, -O2 -G8 -ffunction-sections -frac2-qcopy
 * -ffast-math: 1220/1220 bytes, 9 rows off, one slot swap: `i` is at 0x114 and the record at 0x110,
 * retail has them the other way round.
 * Non-gcse spill slots go up with pseudo number, gcse reaching registers come after them by hash
 * bucket (14029 + regno + offset). Taking object from an argument copy declared late raises its
 * regno, which fixes object+0xC0's slot. `i + 1`'s slot needs regno(i) about 120 or more, which only a
 * block-scope `i` after the setup gives, and then the record, declared first, sorts below it. A real
 * `next` variable lands in the wrong group of slots (0x118, retail 0x124). Forcing 101..181 buckets
 * with `i` 1 to 8 places later finds nothing. Reopen with a way to give the record a higher pseudo
 * than `i` although the setup reads it first.
 */
#include "common.h"

typedef int VectorBits __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));
typedef struct { float vertices[4][4]; unsigned int colors[4]; float uv[4][2]; u64 registers[4]; } __attribute__((aligned(16))) BeamQuad;
typedef struct { short vertex; short uv; } QuadCorner;
typedef struct { float u; float v; } QuadUV;
typedef struct { unsigned char pad[0x10]; float scale; unsigned char pad14[8]; int brightness; } GlowRecord;
typedef struct { unsigned char pad[0x7C]; int live; } GlowSlot;
extern void func_00282C88(void *);
extern void func_00283098(void *, void *, void *);
extern float func_00282E20(void *);
extern float func_002A7798(float);
extern float func_00282DB0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern unsigned long func_0027C878(int);
extern GlowSlot *func_L00_003E6778(int, int, void *, float, float);
extern int D_L00_001B0634 __attribute__((sda));
extern int D_L00_001B0620 __attribute__((sda));
extern int D_L00_001B0624 __attribute__((sda));
extern int D_L00_001B0628 __attribute__((sda));
extern int D_L00_001B062C __attribute__((sda));
extern int D_L00_001B0630 __attribute__((sda));
extern int D_L00_001B0638 __attribute__((sda));
extern float D_L00_001B063C __attribute__((sda));
extern float D_L00_001B05D8 __attribute__((sda));
extern int D_L00_001B2B50 __attribute__((sda));
extern GlowSlot **D_L00_001B2B58;
extern QuadCorner D_L00_0029A090[][4];
extern float D_L00_00299830[][4];
extern QuadUV D_L00_0029A990[];
extern char D_L00_001B8DC0[];

void func_L00_003E6030(void *arg)
{
    BeamQuad quad;
    Vector matrix[3];
    Vector view, center, saved, edge1, edge2;
    int j;
    GlowRecord *rec;
    u64 alpha;
    int colour;
    unsigned char *object = arg;

    rec = *(GlowRecord **)(object + 0x68);
    quad.registers[1] = func_0027C878(D_L00_001B0634);
    alpha = D_L00_001B0620 | ((u64)D_L00_001B0624 << 2);
    alpha |= (u64)D_L00_001B0628 << 4;
    alpha |= (u64)D_L00_001B062C << 6;
    alpha |= (u64)D_L00_001B0630 << 32;
    quad.registers[3] = alpha;
    quad.registers[2] = 0xFF9000000260;
    quad.registers[0] = 0;
    func_00282C88(matrix[0]);
    func_00282C88(matrix[1]);
    func_00282C88(matrix[2]);
    matrix[0][0] = rec->scale * 0.0625f + 1.0f;
    matrix[1][1] = rec->scale * 0.0625f + 1.0f;
    matrix[2][2] = 1.0f;
    colour = D_L00_001B0638 + (rec->brightness << 24);
    quad.colors[3] = colour;
    quad.colors[2] = colour;
    quad.colors[1] = colour;
    quad.colors[0] = colour;
    {
    int i;
    for (i = 0; i < 0x8F; i++) {
        for (j = 0; j < 4; j++) {
            int k = D_L00_0029A090[i][j].uv;

            func_00282D30(quad.vertices[j], D_L00_00299830[D_L00_0029A090[i][j].vertex], D_L00_001B063C);
            quad.uv[j][0] = D_L00_0029A990[k].u;
            quad.uv[j][1] = D_L00_0029A990[k].v - D_L00_001B05D8;
        }
        func_00282C88(center);
        for (j = 0; j < 4; j++) {
            float *v = quad.vertices[j];
            float t, amp;

            func_00283098(v, v, matrix);
            t = 1.5f - func_00282E20(v) * 0.6666667f;
            t = t > 0.0f ? t : 0.0f;
            t = func_002A7798(t * 0.6666667f);
            amp = rec->scale * 1.5f;
            v[2] += t * amp * 0.00825f;
            v[2] += rec->scale * 0.15f;
            func_00283098(v, v, object + 0xC0);
            v[0] += ((float *)(object + 0x10))[0];
            v[1] += ((float *)(object + 0x10))[1];
            v[2] += ((float *)(object + 0x10))[2];
            func_00282CC0(center, center, v);
        }
        func_00282D30(center, center, 0.25f);
        qcopy(saved, center);
        func_00282CF0(view, center, D_L00_001B8DC0);
        func_00282F20(view, view, 1.0f);
        func_00282CF0(edge1, quad.vertices[2], quad.vertices[0]);
        func_00282CF0(edge2, quad.vertices[2], quad.vertices[1]);
        func_00282DD8(center, edge1, edge2);
        func_00282F20(center, center, 1.0f);
        if (func_00282DB0(view, center) > 0.0f) {
            if (D_L00_001B2B58[i] == 0) {
                if (object[0x20] != 6)
                    D_L00_001B2B58[i] = func_L00_003E6778(D_L00_001B2B50, 1, saved, 0.0f, 0.0f);
            } else if (D_L00_001B2B58[i]->live == 0) {
                if (object[0x20] != 6)
                    D_L00_001B2B58[i] = func_L00_003E6778(D_L00_001B2B50, 1, saved, 0.0f, 0.0f);
                else
                    D_L00_001B2B58[i] = 0;
            }
            if (D_L00_001B2B58[i] != 0)
                qcopy(D_L00_001B2B58[i], saved);
            func_00280B90(&quad, 0, 0);
        }
    }
    }
}

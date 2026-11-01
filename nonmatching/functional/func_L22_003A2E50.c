/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* GPT-6.1 Sol (high), worker v0836, 29 October 2026.
 * USA v1.01, default -O2 -G0 -ffunction-sections profile.
 * Best retained check.py: 1300/1304 bytes, 0/2 places (levels 22 and 23).
 * The prologue and signed direction negation agree. Computing the path-table
 * pointer inside the preparation loop lets LICM retain its separate base.
 * Distinct case-3 index/rejection locals recover that whole arm and cause the
 * case-2 rejection flag to spill as in retail. A union of word and halfword
 * endpoint views recovers the final endpoint-base reload instead of a folded
 * stack displacement. All declarations needed for this draft are below.
 * Still differs: two ushort-call argument narrowings (canonical callee kept),
 * table-base/index addu operand order, default switch exits bypassing the
 * case-3 exit branch, case-2 index/matrix registers s2/s1 versus retail s1/s2,
 * and final direction selection / id-load scheduling (one instruction short).
 * A typed state prefix, integer-address table view and guarded do/while tie.
 * Separate case-2 locals rotate three saved registers; sharing its index with
 * case 1 worsens allocation. Explicit final direction locals emit movz.
 * Next useful input: evidence for the original endpoint/index live ranges and
 * callee parameter type. No forced accesses, barriers or register pins used.
 * No linked build: neither local placement matched. Sixteen check invocations
 * included one rejected -fno-if-conversion diagnostic; that flag is absent.
 */
#include "common.h"
typedef struct Rec_003A2D58 {
    int count;
    unsigned char pad04[0x18];
    float angle;
} Rec_003A2D58;
extern Rec_003A2D58 *D_L22_001FE940[];
extern char D_00189EA0[];
extern void func_002F3AB0(void *, void *, void *);
extern float func_002F3C40(void *, void *);
extern int func_L22_003A2CB8(float, int, int *, int);
extern int func_L22_003A2D58(char *, int, int);
extern void func_L22_003A2E10(char *, unsigned short);
extern int func_002A77E0(int);
extern int func_L22_003A6128(float);
extern float func_002F3B88(void *, void *);
extern float func_002F39F0(float);
extern void func_002F3BB0(void *, void *, void *);
extern void func_0032A5F8(void *, void *, int);
extern void func_002F3D60(void *, void *, float);
void func_L22_003A2E50(char *obj, int mode, int filter, float bits) {
    int ids[4];
    char *points[4];
    union Endpoint { int value; unsigned short half[2]; } ends[4];
    char a[16], b[16], c[16], d[16], e[48], f[48];
    char *p = *(char **)(obj + 0x68);
    int *table;
    int count, i, selected, blocked, end, id;
    char *rec;
    float best, score;
    count = func_L22_003A2CB8(bits, (int)obj, ids, filter);
    if (!count) {
        int direction = *(short *)(p + 0x352);
        *(short *)(p + 0x352) = -direction;
        return;
    }
    if (!mode) {
        id = ids[func_002A77E0(count)];
        end = func_L22_003A2D58(obj, id, *(short *)(p + 0x354));
        *(short *)(p + 0x352) = end == 0 ? 1 : -1;
        *(short *)(p + 0x356) = end;
        func_L22_003A2E10(obj, id);
        return;
    }
    for (i = 0; i < count; i++) {
        table = (int *)(p + 0x2A0);
        id = ids[i];
        ends[i].value = func_L22_003A2D58(obj, id, *(short *)(p + 0x354));
        rec = (char *)D_L22_001FE940[*(int *)((char *)table + id * 4)];
        if (!ends[i].value) points[i] = rec + *(int *)rec * 16;
        else points[i] = rec + 16;
    }
    selected = 0;
    switch (mode) {
    case 1: {
        int j, rejected;
        best = 30000.0f;
        for (j = 0; j < count; j++) {
            rejected = 0;
            if (filter) rejected = func_L22_003A6128(*(float *)(points[j] + 12));
            score = func_002F3C40(points[j], *(void **)(p + 0x3AC));
            if ((score < best && !rejected) || count == 1) {
                selected = j;
                best = score;
            }
        }
        break;
    }
    case 3: {
        int k, rejected;
        best = -30000.0f;
        for (k = 0; k < count; k++) {
            rejected = 0;
            if (filter) rejected = func_L22_003A6128(*(float *)(points[k] + 12));
            func_002F3AB0(a, D_00189EA0, obj + 0x10);
            func_002F3AB0(b, points[k], obj + 0x10);
            score = func_002F3B88(a, b);
            if ((best < score && !rejected) || count == 1) {
                selected = k;
                best = score;
            }
        }
        break;
    }
    case 2: {
        float bias = -0.35f;
        float closest = 30000.0f;
        for (i = 0; i < count; i++) {
            blocked = 0;
            if (filter) blocked = func_L22_003A6128(*(float *)(points[i] + 12));
            func_002F3AB0(a, p + 0x3F0, p + 0x400);
            func_002F3AB0(b, points[i], p + 0x400);
            func_002F3D60(c, a, 1.0f);
            func_002F3D60(d, b, 1.0f);
            qcopy(e, c);
            qcopy(f, d);
            qcopy_nc(e + 32, obj + 0xE0);
            qcopy_nc(f + 32, obj + 0xE0);
            func_002F3BB0(e + 16, e + 32, e);
            func_002F3BB0(f + 16, f + 32, f);
            func_0032A5F8(e, p + 0x200, 0);
            func_0032A5F8(f, p + 0x200, 0);
            score = func_002F39F0(func_002F3B88(e, f) - bias);
            if ((score < closest && !blocked) || count == 1) {
                selected = i;
                closest = score;
            }
        }
        break;
    }
    }
    if (ends[selected].value == 0) *(short *)(p + 0x352) = 1;
    else *(short *)(p + 0x352) = -1;
    id = ids[selected];
    *(short *)(p + 0x356) = ends[selected].half[0];
    func_L22_003A2E10(obj, id);
}

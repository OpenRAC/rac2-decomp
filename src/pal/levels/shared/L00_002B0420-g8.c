#include "include_asm.h"

typedef float Row[4];
typedef struct {
    unsigned char pad0[472];
    int f1d8;
    unsigned char pad1dc[0x1530 - 0x1dc];
    Row history[16][3];
    unsigned char pad1830[0x2294 - 0x1830];
    int f2294;
    unsigned char pad2298[32];
    unsigned char f22b8;
    unsigned char pad22b9[275];
    int history_index;
    int history_count;
    int filter_count;
} Root;
extern Root D_00189E20;
extern int ref_L00_002B0528_0 __attribute__((sda));
extern void func_00283678(void *, void *);
extern void func_002AB028(void *);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002AB6D8(void *, void *);
extern float func_L00_002B0480(Row *, Row *);

void func_PAL_L00_002B0420(char *object, void *matrix, int filter)
{
    Row sum[4];
    /* Retail accumulates into this scratch array without clearing it. */
    float scores[16];
    int i, j, n, rejected, accepted;
    Row *cursor;
    float max;
    int index = D_00189E20.history_index;

    {
        Row *history = D_00189E20.history[0];
        func_00283678(history + index * 3, matrix);
        func_002AB028(history + D_00189E20.history_index * 3);
    }
    D_00189E20.history_index = (D_00189E20.history_index + 1) % 16;
    D_00189E20.history_count++;
    if (D_00189E20.history_count > 16)
        D_00189E20.history_count = 16;
    if (!filter)
        return;
    for (cursor = sum, j = 2; j >= 0; j--, cursor++)
        func_00282C88(cursor);
    if (D_00189E20.f2294 == 2)
        ref_L00_002B0528_0 = 5;
    else
        ref_L00_002B0528_0 = 11;
    if (D_00189E20.filter_count < ref_L00_002B0528_0)
        D_00189E20.filter_count++;
    else if (D_00189E20.filter_count > ref_L00_002B0528_0)
        D_00189E20.filter_count--;
    n = D_00189E20.filter_count;
    if (n < 2)
        n = 2;
    if (D_00189E20.f22b8 && D_00189E20.f1d8 < 8) {
        if (n > 3)
            n = 3;
    }
    if (D_00189E20.history_count < n)
        return;
    rejected = 0;
    for (i = 0; i < n; i++) {
        int a = (D_00189E20.history_index + 15 - i) % 16;
        for (j = 0; j < n; j++) {
            if (i != j) {
                int b = (D_00189E20.history_index + 15 - j) % 16;
                scores[i] += func_L00_002B0480(D_00189E20.history[0] + a * 3,
                                              D_00189E20.history[0] + b * 3);
            }
        }
    }
    max = 0.0f;
    for (i = 0; i < n; i++) {
        if (max < scores[i])
            max = scores[i];
    }
    for (i = 0; i < n; i++) {
        if (max * 0.2f < scores[i])
            rejected++;
    }
    accepted = 0;
    for (i = 0; i < n; i++) {
        if (max * 0.2f < scores[i] && rejected > 0 && rejected < 3)
            continue;
        accepted++;
        {
            int sample = (D_00189E20.history_index + 15 - i) % 16;
            {
                Row *p = D_00189E20.history[0] + sample * 3;
                Row *out;
                for (out = sum, j = 2; j >= 0; out++, j--, p++)
                    func_00282CC0(out, out, p);
            }
        }
    }
    for (cursor = sum, j = 2; j >= 0; j--, cursor++)
        func_00282D30(cursor, cursor, 1.0f / (float)accepted);
    func_002AB6D8(sum, object + 0xf0);
}

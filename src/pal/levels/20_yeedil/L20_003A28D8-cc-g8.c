/* func_PAL_L20_003A28D8, the PAL copy of func_L20_0039F968: the same C. */
/* func_PAL_L20_003A28D8 is a unit of its own: the history-copy loop needs -frac2-mult-add-no-flatten
   (docs/COMPILER-NOTES.md) so its source cursor keeps retail's i*400 + (D - 16) grouping. */
#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern void func_00282D30(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern int func_L02_002F1658(void);
extern void func_002AB668(void *, int, float);
extern void func_002ACDE8(void *, const void *, const void *);
extern void func_002ACB48(float *, float);
extern float func_00282DF0(const void *);
extern unsigned char *func_002C36D0(void *, int, int, int);
extern void func_L00_003C5310(void *, int, int, int, unsigned int, unsigned int, unsigned int, unsigned int,
                             int, int, int, float, float, float);
extern Vector D_L20_00234880[][25];
extern Vector D_L20_00235500[];
extern int D_L20_001B3870[] __attribute__((sda));
extern float D_L20_001AED3C __attribute__((sda));
extern float D_L20_001AED40 __attribute__((sda));
extern float D_L20_001AED50 __attribute__((sda));
extern float D_L20_001AED58 __attribute__((sda));
extern unsigned int D_L20_001AED44 __attribute__((sda));
extern unsigned int D_L20_001AED48 __attribute__((sda));
extern unsigned int D_L20_001AED4C __attribute__((sda));
extern float D_L20_001AED54 __attribute__((sda));
extern unsigned char D_L20_001FFB40[];

void func_PAL_L20_003A28D8(unsigned char *object) {
    Vector points[25];
    Vector origin, offset, rotation;
    int i = 0;
    int *counts = D_L20_001B3870;
    unsigned char *level = D_L20_001FFB40;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *particle;
    int j, last;
    float length, limit;
    func_00282D30(&offset, object + 0xE0, D_L20_001AED3C);
    func_00282CC0(&origin, object + 0x10, &offset);
    for (; i < 8; ++i) {
        if (func_L02_002F1658()) {
            Vector *head;
            int historyIndex;
            ++counts[i];
            if (counts[i] > 24) counts[i] = 25;
            last = counts[i] - 1;
            for (historyIndex = last; historyIndex > 0; --historyIndex)
                qcopy_nc(&D_L20_00234880[i][historyIndex], &D_L20_00234880[i][historyIndex - 1]);
            head = D_L20_00234880[i];
            func_002AB668(&rotation, (int)&D_L20_00235500[i], D_L20_001AED58 * 0.017453294f);
            func_002ACDE8(head, head, &rotation);
            func_002ACB48(head->f, 0.125f);
            length = func_00282DF0(head);
            limit = D_L20_001AED40 * 1.1f;
            if (limit < length) func_00282D30(head, head, limit / length);
            else {
                limit = D_L20_001AED40 * 0.9f;
                if (length < limit) func_00282D30(head, head, limit / length);
            }
        }
        last = counts[i] - 1;
        if (last < 0) last = 0;
        {
            int n = 0;
            for (j = last; j > 0; --j) {
                func_00282CC0(&points[n], &origin, &D_L20_00234880[i][j]);
                points[n].f[3] = 0.5f;
                ++n;
            }
        }
        func_00282CC0(&points[last], &origin, D_L20_00234880[i]);
        points[last].f[3] = 0.05f;
        if (func_L02_002F1658()) {
            int top = counts[i] - 1;
            Vector *tip = &points[top];
            particle = func_002C36D0(tip, 8, 0, 1);
            if (particle) {
                float size = D_L20_001AED50 * 210000.0f;
                *(unsigned int *)(particle + 4) = D_L20_001AED44 | *(unsigned int *)(state + 4);
                *(float *)(particle + 0xC) = size;
                particle[2] = (*(unsigned char **)(level + 0xF8))[1];
            }
            particle = func_002C36D0(tip, 8, 0, 1);
            if (particle) {
                *(float *)(particle + 0xC) = D_L20_001AED50 * 63000.00390625f;
                *(unsigned int *)(particle + 4) = 0x407F7F7F;
            }
        }
        func_L00_003C5310(points, 25, 14, 14, D_L20_001AED48, D_L20_001AED48 & 0xFFFFFF,
                          D_L20_001AED4C | *(unsigned int *)(state + 4), D_L20_001AED4C,
                          0, counts[i] - 1, counts[i], 0.1f, 0.2f, D_L20_001AED54);
    }
}

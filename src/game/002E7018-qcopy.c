#include "include_asm.h"
#include "common.h"

/* The ring's quads are copied with the grouped `lq`/`sq` profile, so this
 * function needs its own unit. */

typedef int TI128 __attribute__((mode(TI)));

extern int D_00152C00[];
extern float func_00283CE0(int);
extern float func_002A7940(void);
extern void func_002ACB48(float *, float);
extern void func_00281EB8(void *, unsigned int, unsigned int, int, float, float, float);
extern void func_00282CC0(void *, void *, void *);

/* Draws `count` copies of one quad along the segment from `from` to `to`,
 * each jittered by `radius` and turned by the engine's matrix. The mode flag
 * is the short at D_00152C20, 0x20 into the table at D_00152C00. */
void func_002E7570(void *src, void *matrix, int count, unsigned int colour,
                   float from, float to, float radius)
{
    TI128 quad[2];
    float step;
    int i;

    quad[0] = *(TI128 *)src;
    step = 1.0f / func_00283CE0(count);
    for (i = 0; i < count; i++) {
        short *table = (short *)D_00152C00;
        float f = func_00283CE0(i) * step;
        float t = from + (to - from) * f;
        float angle = func_002A7940();

        quad[1] = quad[0];
        func_002ACB48((float *)&quad[1], radius);
        func_00281EB8((char *)&quad[1], table[0x10] == 2 ? 5 : 0x2E, colour, 1,
                      t, 0.0f, angle);
        func_00282CC0((char *)&quad[0], (char *)&quad[0], matrix);
    }
}

extern float ref_L00_002E8F80_00[][4];
extern void func_00283098(void *, void *, void *);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

/* Six sparks from the table, each placed by the object's matrices and given a
   small random drift; `height` lifts the drift's z. */
void func_002E8F80(char *object, float height)
{
    float from[4] __attribute__((aligned(16)));
    float to[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    int i;

    for (i = 0; i < 6; i++) {
        from[0] = func_002A7878(-0.016666668f, 0.016666668f);
        from[1] = func_002A7878(-0.016666668f, 0.016666668f);
        from[2] = height + func_002A7878(-0.004166667f, 0.004166667f);
        from[3] = 0.4f;
        qcopy(to, from);
        to[3] = 0.6f;
        qcopy(position, ref_L00_002E8F80_00[i]);
        func_00283098(position, position, object + 0xC0);
        func_00282CC0(position, position, object + 0x10);
        func_002BAA28(position, from, to, 0x30F0F0F0, 0x14F0F0F0, 4, 4, func_002A77E0(4) + 4, 0x17);
    }
}

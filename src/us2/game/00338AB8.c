#include "include_asm.h"

extern int *func_00335E20(void *);
extern void func_00335E68(void *, int);
extern void func_003361E0(void *, void *, void *);
extern void func_00336390(void *, int, int);
extern void func_003363C0(void *, float);
extern void *func_00115484(void *, int, unsigned int);
extern char D_001ADB40[];
extern char D_001ADB50[];
extern char *D_001A8CFC[] __attribute__((sda));

/* Initialises a text panel: clears its state and, when a pool is given, takes four 16-byte
   cells from it with func_00336E40/func_00336DA8 (255,108 / colour 0x60442D00 / two cleared
   cells), then sets up the "aTxBrack" and "aTxTop" widgets at +0x10 and +0x5C with
   D_001A8CFC[0] + 0x8710 and colour 0x55F0C070. The cleared cells store word 0 last, as in
   func_00339078; the colour cell is cleared as floats before its integer colour is stored. */
void func_US2_00338AB8(char *obj, void *pool)
{
    char *top;
    char *bracket;

    obj[0xA8] = 0;
    *(int *)(obj + 0x1AC) = 0;
    *(int *)(obj + 0x1A8) = 0;
    *(int *)(obj + 0x1C8) = 0;
    *(int *)(obj + 0x1CC) = 0;
    *(int *)(obj + 0x1C4) = 2;
    *(int *)(obj + 0x1D4) = 0x28;
    *(int *)(obj + 0x1B0) = 1;
    func_00115484(obj + 0x1D8, 0, 0x78);
    if (pool != 0) {
        float *xy;
        float *colour;
        int *cell4;
        int *cellC;

        xy = func_00336DA8((void *)16, func_00336E40(pool));
        xy[0] = 255.0f;
        xy[1] = 108.0f;
        ((int *)xy)[2] = 0;
        ((int *)xy)[3] = 0;
        *(float **)(obj + 0) = xy;
        colour = func_00336DA8((void *)16, func_00336E40(pool));
        colour[0] = 0.0f;
        colour[1] = 0.0f;
        *(int *)colour = 0x60442D00;
        ((int *)colour)[2] = 0;
        ((int *)colour)[3] = 0;
        *(float **)(obj + 8) = colour;
        cell4 = func_00336DA8((void *)16, func_00336E40(pool));
        *(int **)(obj + 4) = cell4;
        cell4[1] = 0;
        cell4[2] = 0;
        cell4[3] = 0;
        cell4[0] = 0;
        cellC = func_00336DA8((void *)16, func_00336E40(pool));
        *(int **)(obj + 12) = cellC;
        cellC[1] = 0;
        cellC[2] = 0;
        cellC[3] = 0;
        cellC[0] = 0;
    }
    bracket = obj + 0x10;
    top = obj + 0x5C;
    func_003361E0(bracket, D_001ADB40, pool);
    func_00336390(bracket, (int)(D_001A8CFC[0] + 0x8710), 0x57);
    func_003363C0(bracket, 0.02f);
    func_00335E68(bracket, 1);
    *func_00335E20(bracket) = 0x55F0C070;
    func_003361E0(top, D_001ADB50, pool);
    func_00336390(top, (int)(D_001A8CFC[0] + 0x8710), 0x58);
    func_00335E68(top, 1);
    *func_00335E20(top) = 0x55F0C070;
    **(int **)(obj + 12) = 0x80F0F0F0;
    *(int *)(obj + 0x1B8) = 0;
    **(int **)(obj + 4) = 0;
}


extern int func_0027F178(unsigned char *text, int length); /* text width */

/* func_US2_00338CD8, the v2.00 copy of func_00337E30, which also stores its second argument at
   +0x1C4. */
void func_US2_00338CD8(unsigned char *p, int a1, int a2, float f12, float f13)
{
    unsigned char *q = p + 168;

    *(int *)(p + 452) = a1;
    *(float *)(*(int *)p) = f12;
    *(float *)(*(int *)p + 4) = f13;
    p[423] = 0;
    *(int *)(p + 440) = a2;
    *(int *)(p + 472) = (int)q;
    *(int *)(p + 468) = func_0027F178(q, -1);
    *(int *)(p + 432) = 1;
    *(float *)(*(int *)(p + 4)) = 1.0f;
}

extern void func_00115AC0(void *, int, int);
extern void func_US2_00338D48(void *, int, int, float, float);

/* clamps a caller-supplied terminator value (-1 meaning unset) to 360, then runs two callees on two sub-objects of one handle, the second with a float pair */
void func_US2_00338F18(int object, int value, int count)
{
    int limit = (count == -1) ? 360 : count;
    int inner = object + 8156;

    func_00115AC0((void *)(object + 8324), value, 255);
    func_US2_00338D48((void *)inner, 2, limit, 255.0f, 80.0f);
}





/* clamps a caller-supplied terminator value (-1 meaning unset) to 180, then runs two callees on two sub-objects of one handle, the second with a float pair */
void func_US2_00339678(int object, int value, int count)
{
    int limit = (count == -1) ? 180 : count;
    int inner = object + 7564;

    func_00115AC0((void *)(object + 7732), value, 254);
    func_US2_00338D48((void *)inner, 2, limit, 255.0f, 123.0f);
}


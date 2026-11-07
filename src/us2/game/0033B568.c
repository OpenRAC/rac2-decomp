#include "include_asm.h"

typedef struct { float x, y, width, height; } TitlePosition;
extern void func_00336710(void *, void *, void *);
extern int func_00335E20(void *);
extern void func_US2_003377B0(void *, void *, void *);
extern int *func_00336DA8(int, int);
extern int func_00336E40(void *);
extern void func_00335F88(void *, float, float, float, float);
extern float D_001B23A4 __attribute__((sda));
extern char D_001ADC88[];

/* func_US2_0033B568, the USA v2.00 copy of func_0033A520: the same C, with the object's
 * fields 0x10 further on. */
void func_US2_0033B568(unsigned char *obj, void *arg)
{
    float v;
    TitlePosition *p;
    char *text;

    *(int *)(obj + 0x208) = 0;
    *(void **)(obj + 0x210) = arg;
    if (arg != 0) {
        int *alloc = func_00336DA8(16, func_00336E40(arg));
        *(int **)(obj + 0x20C) = alloc;
        alloc[1] = 0;
        alloc[2] = 0;
        alloc[3] = 0;
        alloc[0] = 0;
    }
    do {
        float position;
        int y;
        p = *(TitlePosition **)(obj + 0x20C);
        p->x = 70.0f;
        position = 300.0f;
        y = (int)(D_001B23A4 * position + 0.5f);
        v = y;
    } while (0);
    text = D_001ADC88;
    p = *(TitlePosition **)(obj + 0x20C);
    p->y = v;
    func_00336710(obj + 0x134, text, *(void **)(obj + 0x210));
    func_00335F88(obj + 0x134, 24.0f, 24.0f, 0.0f, 0.0f);
    *(int *)func_00335E20(obj + 0x134) = 0x60F0F0B0;
    v = 65.0f;
    *(float *)(obj + 0x214) = v;
    func_US2_003377B0(obj + 0x170, text, *(void **)(obj + 0x210));
    *(int *)func_00335E20(obj + 0x170) = 0x80F0F0F0;
    func_00335F88(obj + 0x170, 0.7f, 0.7f, 0.0f, 0.0f);
}

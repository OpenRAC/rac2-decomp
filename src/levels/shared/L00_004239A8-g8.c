#include "common.h"

/* func_L00_004239A8 needs -G8 for the $gp-relative bias constant. The bias is a read-only
 * tuning value: retail schedules its load across the preceding halfword store, which only an
 * unchanging (const) read allows. */
typedef int TI128 __attribute__((mode(TI)));

extern char D_L00_001B8E10[];
extern char D_L00_001BF220_1[];
extern char D_L00_001BF230[];
extern const float D_L00_001B14D0 __attribute__((sda));
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern int func_L00_00420388(void *, float);
extern int func_00277258(void *, float, void *, void *);
extern void *func_L00_004237C8(char *, void *, int, int);

/* Probes up to three positions from the owner block's blend point, records which probe
   succeeded, classifies the view direction into the +0x38 flag and hands the result on. */
void *func_L00_004239A8(char *a0)
{
    char *base = *(char **)(a0 + 0x70);
    char *st = base + 0x1F0;
    void *mid = base + 0x60;
    char *end = base + 0x160;
    TI128 v, w;
    void *q;
    void *tgt;
    void *ret;
    float f20;
    float d;
    int gotA = 0;
    int gotB = 0;
    int i = 0;
    char *cam = D_L00_001B8E10 + 0x10;

    FastVecAdd(&v, base + 0xB0, end);
    *(short *)(st + 0x38) = 2;
    q = *(void **)(*(char **)D_L00_001B8E10 + 0x70);
    tgt = *(void **)(st + 0x48);
    f20 = D_L00_001B14D0 + *(float *)((char *)q + 0x234) * *(float *)((char *)q + 0x22C) *
              (*(float *)((char *)q + 0x230) - 1.0f);
    while (i < 3) {
        if (func_L00_00420388(&v, f20))
            gotA = 1;
        else if (!func_00277258(&v, f20, tgt, *(void **)(cam + 0xC4)))
            break;
        else
            gotB = 1;
        if (*(short *)(st + 0x38) != 0) {
            FastVecSub(&w, D_L00_001BF220_1, &v);
            vec_scale_to_length(&w, &w, 1.0f);
            d = FastVecDot(cam + 0x30, &w);
            if (d > 0.75f)
                *(short *)(st + 0x38) = 1;
            else if (d < -0.75f)
                *(short *)(st + 0x38) = -1;
            else
                *(short *)(st + 0x38) = 0;
        }
        qcopy(&v, D_L00_001BF230);
        i++;
    }
    ret = func_L00_004237C8(a0, &v, gotA, gotB);
    FastVecAdd(st + 0x20, (char *)mid + 0x50, end);
    if (*(short *)(st + 0x38) == 2)
        *(short *)(st + 0x38) = 0;
    return ret;
}

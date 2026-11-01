#include "include_asm.h"

extern int func_002A77E0(int x);
extern float func_002A7878(float, float);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern void func_002A7A00(char *, float, float);
extern char *func_PAL_002BE9A8(float, float, float, float, char *, int, char *,
                     unsigned int, int);
extern void func_00282F20(void *, void *, float);
extern void func_00312B70(void *, void *, void *, void *);
extern char ref_L00_003FE310_00[];

/* Twenty rounds that spawn a particle at the second argument: each round draws a radius
   (70000..150000) and a byte (10..127), builds a three-float direction on the stack and
   fills the new record's short and byte fields; the level's own data address is then
   handed to the vector routine with the third argument and a scale of 1.5, and to the
   level-object starter with the second argument. */
void func_PAL_L00_00402B98(void *a0, void *a1, void *a2)
{
    char local[16];
    float f;
    int i;
    unsigned int v;
    unsigned int w;
    unsigned int x;
    char *r;

    for (i = 19; i >= 0; i--) {
        func_002A77E0(2);
        func_002A77E0(2);
        f = func_002A7878(70000.0f, 1.5e+05f);
        v = func_002A7820(10, 127);
        w = (v << 8) | 0x7f000000U;
        x = (v << 16) | w;
        v = x | v;
        func_002A7A00(local, 2.0000003e-05f,
                0.008f);
        r = func_PAL_002BE9A8(0.3f, 1.0f, 1.01f, f, a1, 0, local, v, 1);
        if (r != 0) {
            char *q = r + 32;

            *(short *)(r + 10) = 100;
            *(int *)(q + 4) = 2;
            *(char *)(q + 10) = 127;
            *(char *)(q + 11) = *(unsigned char *)(r + 10);
        }
    }
    func_00282F20(ref_L00_003FE310_00, a2, 1.5f);
    func_00312B70(ref_L00_003FE310_00, a1, 0, 0);
}


typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;
typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;
extern void func_002FDBD8_6(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void func_PAL_L00_00402D18(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_6(1.0f, context, context->vector_10, 0);
    }
}

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00402D4C);

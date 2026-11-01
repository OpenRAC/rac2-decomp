#include "include_asm.h"
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
extern void func_002FDBD8_2(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void func_PAL_L00_003C7128(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_2(1.0f, context, context->vector_10, 0);
    }
}

#include "common.h"
extern void func_L00_00323448();
extern void func_L00_00323958(unsigned char *, unsigned char *);
extern float func_00283B98(float, float);

void func_PAL_L00_003C6C58(unsigned char *a0) {
    unsigned char *s0 = a0;
    unsigned char *s1 = *(unsigned char **)(s0 + 0x68);
    switch (s0[0x20]) {
    case 0:
        if (*(long long *)s1 == -1) {
            break;
        }
        {
            unsigned char stamp = 0xFF;
            *(unsigned char *)(s0 + 0x30) = stamp;
        }
        func_L00_00323448(s0, s1 + 0x30, 0x64, *(int *)(s1 + 4), *(int *)s1, -1, 7, 0);
        s1[0xC5A] = 1;
        s0[0x20] = 1;
        break;
    case 1:
        *(float *)(s0 + 0xF4) = func_00283B98(
            *(float *)(s0 + 0xF4), *(float *)(s1 + 8) * 0.0003490659f);
        func_L00_00323958(s0, s1 + 0x30);
        break;
    }
}

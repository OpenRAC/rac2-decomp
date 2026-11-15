#include "include_asm.h"
#include "names.h"

/* Qwen draft (branch qwen/autonomy, 9650d156), checked by tools/check.py */
// Helper function declarations, using exact symbol names from externals
void func_002AFDD8(char *, char *, char *, char *);

float func_00282E20(unsigned char (*)[16]);

// Implementation of func_002AFF08
/* Returns the horizontal length of the offset between the object and a point. */
float func_002AFF08(char *object, char *point, char *flag) {
    unsigned char offset[16];

    TransformVectorByObjectOrGiven(object, (char *)offset, point, flag);
    return vec_length_xy((unsigned char (*)[16])offset);
}

/* Returns the height part of the offset between the object and a point. */
float func_002AFF38(char *first, char *second, char *third) {
    float offset[4];
    TransformVectorByObjectOrGiven(first, (char *)offset, second, third);
    return offset[2];
}

/* D_001A8CB0 is `sda`: cc1 emits its address as one `la` insn, which changes the schedule so
   that parameter a is copied to $v0 on entry and moved to $a2 in the call's delay slot, as in
   retail. Without `sda` the copy is coalesced and the function is 116 bytes. */
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern char D_001A8CB0[] __attribute__((sda));

void func_002AFF60(char *point, char *outDir, int flag)
{
    FastVecSub(outDir, D_001A8CB0, point);
    *(int *)(outDir + 8) = 0;
    vec_scale_to_length(outDir, outDir, 1.0f);
    if (flag == 0)
        FastVecScale(outDir, outDir, -1.0f);
}

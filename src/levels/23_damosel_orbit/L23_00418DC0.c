#include "include_asm.h"
#include "names.h"

/* func_L23_00418DC0 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef int s32;
typedef short s16;
typedef int TI128 __attribute__((mode(TI)));

extern void func_00282CF0(float *, const float *, const float *);

extern void func_00282F20(char *, char *, float);

extern void func_00282CC0(char *, char *, char *);

extern float func_00282E48(char *, char *);

extern char D_00189EA0[];

extern int *D_L23_001FF300[];

extern s32 func_L23_00419CA0(s32 arg0);

/* Picks the nearest entry of the object each measured slot names, and stores the index found. */
void func_L23_00418DC0(char *moby, s32 onlyAllowed) {
    extern void func_L23_00419088();
    struct {
        TI128 a;
        float b[4];
    } loc;
    char *src = moby + 0x10;
    char *state;
    char *slots;
    float best;
    s32 i;

    state = *(char **)(moby + 0x68);
    loc.a = *(TI128 *)src;
    FastVecSub(loc.b, (float *)src, (float *)gHeroPosition);
    slots = state + 0x230;
    best = 30000.0f;
    vec_scale_to_length((char *)loc.b, (char *)loc.b, 4.0f);
    FastVecAdd((char *)&loc.a, (char *)&loc.a, (char *)loc.b);
    for (i = 0; i < 0x2F; i++) {
        int *obj;
        s32 k;

        if (onlyAllowed != 0 && IsValueNotInSlotTable(i) == 0)
            continue;
        obj = gPathLists[*(int *)(slots + (i << 2))];
        for (k = 0; k < *obj; k++) {
            float d = fast_vec_dist((char *)obj + 0x10 + k * 0x10, (char *)&loc.a);

            if (d < best) {
                best = d;
                PushPathHistory(moby, i);
                *(s16 *)(state + 0x396) = k;
            }
        }
    }
}

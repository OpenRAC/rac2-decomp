#include "include_asm.h"
#include "names.h"

/* func_L23_00418650 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef int V4_L23_418650 __attribute__((mode(TI)));

extern char D_00189ED0[];
extern float D_L23_001B36A4 __attribute__((sda));
extern void func_00282CF0(char *dst, char *src, char *arg);
extern void func_00282F20(char *dst, char *src, float arg);
extern void func_00282CC0(char *dst, char *src, char *arg);

/* Moves a point onto the round planet surface, at the given height above it. */
void func_L23_00418650(char *pos, float heightOffset) {
    char local[16];

    FastVecSub(local, pos, D_00189ED0);
    vec_scale_to_length(local, local, heightOffset + D_L23_001B36A4);
    FastVecAdd(local, local, D_00189ED0);
    *(V4_L23_418650 *)pos = *(V4_L23_418650 *)local;
}

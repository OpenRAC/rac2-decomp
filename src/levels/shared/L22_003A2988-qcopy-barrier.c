#include "include_asm.h"
#include "names.h"


typedef int V4_L23_418650 __attribute__((mode(TI)));
extern char D_00189ED0[];
extern float D_L23_001B36A4 __attribute__((sda));
extern void func_00282CF0(char *dst, char *src, char *arg);
extern void func_00282F20(char *dst, char *src, float arg);
extern void func_00282CC0(char *dst, char *src, char *arg);

/* Same body as func_L23_00418650, with this function's own callees. */
extern float ref_L22_003A2988_00 __attribute__((sda));
/* Pushes a point away from the center of the round arena by the given extra distance. */
void func_L22_003A2988(char *point, float extra) {
    char scratch[16];

    FastVecSub(scratch, point, D_00189ED0);
    vec_scale_to_length(scratch, scratch, extra + ref_L22_003A2988_00);
    FastVecAdd(scratch, scratch, D_00189ED0);
    *(V4_L23_418650 *)point = *(V4_L23_418650 *)scratch;
}

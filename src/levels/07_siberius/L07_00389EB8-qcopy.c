#include "include_asm.h"
#include "names.h"

/* func_L07_003E6E00 copies a 16-byte vector, which needs the grouped quadword
   copy: it is in this sibling file, and config/cflags.txt gives it the
   -frac2-qcopy flag. */

/* The 16-byte vector the object and the entity keep. */
typedef int TI128 __attribute__((mode(TI)));

extern void func_00282948(char *);

extern void func_002B0990(char *, char *, int, int, float);

extern int D_L07_001C9780;

extern void func_L07_003E6FE8(char *);

extern void func_00325DA0(char *, char *);

extern void func_00282CF0(void *, void *, void *);

extern float func_00283B98(float, float);

extern void func_00325C50(char *, char *, int, void *, float);

/* Clear the two resource slots, step the state counter, refresh the object's
   transform and hand the entity to the shared launcher. */
/* Finishes the entity's frame: counts up its timer, saves its old position and hands it to the
   shared launcher. */
void func_L07_003E6E00(char *moby)
{
    char *vars;
    char *src;
    char *dst;
    TI128 oldPos;
    unsigned short timer;
    float smoothedAngle;

    vars = *(char **)(moby + 0x68);
    FastFloatHelperD(vars + 0x344);
    FastFloatHelperD(vars + 0x348);
    timer = *(unsigned short *)(moby + 0x96);
    if (timer <= 0xFFFE)
        *(unsigned short *)(moby + 0x96) = timer + 1;
    SyncGroupCounter(moby, vars + 0x340);
    src = moby + 0x10;
    dst = vars + 0x2E0;
    FastVecSub(&oldPos, src, dst);
    *(TI128 *)dst = *(TI128 *)src;
    if (D_L07_001C9780 != 0)
        RideMobyBelow(moby);
    if (*(unsigned char *)(moby + 0x95) == 2) {
        smoothedAngle = FastAddRotations(*(float *)(vars + 0x2DC), 0.20943954586982727f);
        *(float *)(vars + 0x2DC) = smoothedAngle;
        AttachAndTurnChildParts(moby, vars + 0x330, 1, &oldPos, smoothedAngle);
    } else {
        smoothedAngle = FastAddRotations(*(float *)(vars + 0x2DC), 0.011635531f);
        *(float *)(vars + 0x2DC) = smoothedAngle;
        AttachAndTurnChildParts(moby, vars + 0x330, 0, &oldPos, smoothedAngle);
    }
    SetValueAndStartSmoothChange(moby, vars + 0x230, 7, 1, 2.5f);
}

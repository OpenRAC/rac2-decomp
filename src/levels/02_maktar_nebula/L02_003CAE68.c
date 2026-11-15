#include "include_asm.h"
#include "names.h"

/* func_L02_003CAE68 is a unit of its own: it needs the opt-in quadword-copy profile
   (-frac2-qcopy, #262), which gives retail's grouped `lq`/`sq` with register addresses. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    float x, y, z, w;
} Vec4;

extern Vec4 *D_L02_001FF1C0[];
extern u16 *D_L02_001FC060[];
extern u8 *D_L02_001B359C_1[] __attribute__((sda));
extern int D_L02_001B35B8 __attribute__((sda));

extern void func_00282D08(Vec4 *, Vec4 *, Vec4 *, float);
extern float func_00282E48(Vec4 *, Vec4 *);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(char *, char *, Vec4 *);
extern void func_L02_0032EF10(Vec4 *, char *, char *, int, float);
extern void func_L01_00311C18(Vec4 *, char *, char *, u8 *);
extern float func_00282E80(void *, u8 *);

/* Builds the actor's target point: the path's middle point plus an offset of `len` (the distance
   from that middle point to the path's first point) at a random angle (func_002A7940), adjusted by
   func_L02_0032EF10.  For path step 0 it then walks the group's id list, and when the way from
   the actor to the point passes within 3.0 of an entity that the actor is not itself within 3.0
   of, the point becomes the actor's own position (the 16-byte copy).
   Spelling: the walk is the matched id-list walk (a `for` loop with the redundant `p != 0 &&`
   in its test, which keeps jump.c from duplicating the test), and `p` is looked up from the raw
   group word before `g` takes it; that order gives retail's registers for the entry block. */
/* The update caller also supplies an output pointer; this body derives it from self. */
/* Picks a new spot for the enemy to walk to, near the middle of its path, and avoids spots where it would run into something. */
void func_L02_003CAE68(char *self, char *unused_output) {
    char *state = *(char **)(self + 0x68);
    char *rec;
    Vec4 *path;
    Vec4 midPoint, toPoint;
    u16 *idPtr;
    u8 *entity;
    float len, ang;
    int group;

    rec = state + (*(int *)(state + 0x3C4) << 5);
    path = gRoutePolygons[*(int *)(rec + 0x290)];
    lerp_vector(&midPoint, path + 1, path + 1 + (*(int *)path >> 1), 0.5f);
    len = fast_vec_dist(&midPoint, path + 1);
    ang = RandomAngle();
    *(float *)(state + 0x3A0) = FastSinOrCosA(ang) * len;
    *(float *)(state + 0x3A4) = FastSinOrCosB(ang) * len;
    *(int *)(state + 0x3A8) = 0;
    FastVecAdd(state + 0x3A0, state + 0x3A0, &midPoint);
    ClampMoveToPathArea(&midPoint, state + 0x3A0, state + 0x3A0, *(int *)(rec + 0x290), 2.0f);
    if (*(int *)(state + 0x3C4) != 0)
        return;
    for (idPtr = gEntityGroupLists[*(int *)(state + 0x39C)], group = *(int *)(state + 0x39C);
         (u8)group != 0xFF && group <= D_L02_001B35B8 && idPtr != 0 &&
         ((idPtr != 0 && (s16)idPtr[-1] >= 0) || idPtr == gEntityGroupLists[group]);
         idPtr++) {
        entity = D_L02_001B359C_1[0] + ((*idPtr & 0x7FFF) << 8);
        if (entity == 0)
            return;
        ClosestPointOnSegment(&toPoint, self + 0x10, state + 0x3A0, entity + 0x10);
        if (vec_distance_xy(&toPoint, entity + 0x10) < 3.0f && vec_distance_xy(self + 0x10, entity + 0x10) > 3.0f)
            *(TI128 *)(state + 0x3A0) = *(TI128 *)(self + 0x10);
        group = *(int *)(state + 0x39C);
    }
}

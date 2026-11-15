#include "include_asm.h"
#include "common.h"

/* func_L23_003C0A60 is a unit of its own: it reads $gp data. */

typedef int TI128 __attribute__((mode(TI)));

extern float D_L23_001AFA70 __attribute__((sda));
extern float D_L23_001AFAB0 __attribute__((sda));

extern float func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, int, int);
extern void func_L23_00418650(void *, float);

typedef struct { u8 pad[0x18]; char *hit; } VisibilityCollision;
extern VisibilityCollision D_L23_001C0A80;
typedef struct { u8 pad[0x2290]; char *hero; } VisibilityHero;
extern VisibilityHero D_00189E20;

int func_L23_003C0A60(char *obj, TI128 *p1, TI128 *p2) {
    char *state = *(char **)(obj + 0x68);
    TI128 loc[6];
    int found;
    char *hit;

    if (D_L23_001AFA70 < fast_vec_dist(p1, p2))
        return 0;
    qcopy(&loc[0], p2);
    func_L23_00418650(&loc[0], *(float *)(state + 0x54) + *(float *)(state + 0x50));
    FastVecSub(&loc[1], &loc[0], p1);
    vec_scale_to_length(&loc[1], &loc[1], D_L23_001AFAB0);
    qcopy(&loc[4], p1);
    qcopy(&loc[2], p1);
    func_L23_00418650(&loc[2], *(float *)(state + 0x54) + *(float *)(state + 0x50));
    found = 0;
    do {
        float d = fast_vec_dist(&loc[4], &loc[0]);

        if (d < D_L23_001AFAB0) {
            if (d < 0.0f)
                return 1;
            vec_scale_to_length(&loc[5], &loc[1], d);
            found = 1;
            FastVecAdd(&loc[3], &loc[4], &loc[5]);
            func_L23_00418650(&loc[3], *(float *)(state + 0x54) + *(float *)(state + 0x50));
        } else {
            FastVecAdd(&loc[3], &loc[4], &loc[1]);
            func_L23_00418650(&loc[3], *(float *)(state + 0x54) + *(float *)(state + 0x50));
        }
        if (CollLine(&loc[2], &loc[3], 0x10, 0, 0)) {
            hit = D_L23_001C0A80.hit;
            if (hit != obj && hit != D_00189E20.hero)
                return 0;
        }
        qcopy(&loc[2], &loc[3]);
        FastVecAdd(&loc[4], &loc[4], &loc[1]);
    } while (found == 0);
    return 1;
}

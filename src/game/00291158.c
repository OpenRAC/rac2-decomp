#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    float x;
    float y;
    float z;
} Vec3_00291158;

/* the two ten-entry tables: the source heights and the scaled copy the pointer is aimed at */
extern Vec3_00291158 D_00255B40[];

extern Vec3_00291158 D_00255BB8[];

extern Vec3_00291158 *D_001B1990 __attribute__((sda));

/* the mode word: 2 turns the reference axis from +x to -y */
extern s32 D_001A8BB0 MACRO_ADDR;

/* the axis the reference is measured against */
extern float D_001B5570[];

/* the record whose count drives the per-entry pass, and the overflow entry's block */
extern char *D_001B20C0 MACRO_ADDR;

extern float D_001B20F0[] MACRO_ADDR;

extern float func_00282DB0(void *, void *);

extern void func_00283388(void *);

extern void func_002E3478(s32);

extern void func_002E3940(s32);

/* scales the ten heights by the negated projection of the reference axis, then runs the
   per-entry pass (entries past the tenth only get the overflow block) */
void func_00291158(void) {
    union {
        TI128 q;
        float f[4];
    } axis;
    float scale;
    s32 j;
    s32 i;

    axis.q = 0;
    axis.f[0] = 1.0f;
    D_001B1990 = D_00255BB8;
    if (D_001A8BB0 == 2) {
        axis.f[0] = 0.0f;
        axis.f[1] = -1.0f;
    }
    scale = -FastVecDot(D_001B5570, &axis);
    for (j = 0; j < 10; j++) {
        D_00255BB8[j].z = D_00255B40[j].z * scale;
    }
    for (i = 0; i < *(short *)(D_001B20C0 + 6); i++) {
        if (i >= 10) {
            set_identity_matrix(D_001B20F0);
        } else {
            func_002E3478(i);
        }
        func_002E3940(i);
    }
}

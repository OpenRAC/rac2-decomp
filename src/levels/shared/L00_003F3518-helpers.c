/* Collect transformed group points and blended colors for the shared draw emitter.
 * The local snapshots remain complete 16-byte vectors in the stack workspace.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* Partial global view with the complete vector consumed by the math helper. */
typedef struct {
    char reserved_000[0x140];
    float x_140;
    float y_144;
    float z_148;
    float w_14C;
} Aimvec_F0b10;

extern Aimvec_F0b10 D_L00_001B8C80;

extern int func_00283DB8(char *local, float value);
extern void func_00283098(char *, char *, char *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282CF0(char *off, char *v, char *pos);
extern void func_00282F20(char *dst, char *src, float angle);
extern float func_00282DB0(char *, char *);
extern int func_L00_0031C998(int, int, float);
extern void func_L00_003F34D8(char *, int *, char *, int *, int *);
extern void func_L00_00325CC0(int, void *, void *, float, float);

extern unsigned short **D_L00_001A9014 __attribute__((sda));
extern unsigned char *D_L00_001B2514 __attribute__((sda));
extern unsigned char *D_L00_001B251C __attribute__((sda));

/* Goes through a list of lit points near the object, keeps the ones in view, and works out
   each colour from how much the point faces the camera. Then it sends them all to be drawn. */
void func_L00_003F3518(char *obj)
{
    unsigned char *vars = *(unsigned char **)(obj + 0x68);
    char buf0[0x460] __attribute__((aligned(16)));
    char buf1[0x120] __attribute__((aligned(16)));
    char pos[16] __attribute__((aligned(16)));
    char groupPoint[16] __attribute__((aligned(16)));
    char offset[16] __attribute__((aligned(16)));
    char scratch[16] __attribute__((aligned(16)));
    char facing[16] __attribute__((aligned(16)));
    char facingBase[16] __attribute__((aligned(16)));
    int idx;
    int count;
    int color;
    unsigned short *indexList;
    unsigned char *entry;
    float dot;

    idx = *(int *)vars;
    count = 0;
    indexList = D_L00_001A9014[idx];
    for (; indexList != 0 && ((short)indexList[-1] >= 0 || indexList == D_L00_001A9014[*(int *)vars]) &&
           (entry = D_L00_001B251C + ((*indexList & 0x7FFF) << 6)) != 0;
         indexList++) {
        qcopy(pos, D_L00_001B2514 + ((*indexList & 0x7FFF) << 5));
        *(float *)(pos + 12) += *(float *)(vars + 0x4C);
        if (FastMathHelperA(pos, *(float *)(vars + 0x60)) < 0)
            continue;
        qcopy(groupPoint, entry + 0x30);
        *(TI128 *)scratch = 0;
        *(float *)(scratch + 0) = *(float *)(vars + 0x50);
        *(float *)(scratch + 4) = *(float *)(vars + 0x54);
        *(float *)(scratch + 8) = *(float *)(vars + 0x58);
        *(TI128 *)offset = *(TI128 *)scratch;
        matrix_mul_vec3(offset, offset, (char *)entry);
        FastVecAdd(groupPoint, groupPoint, offset);
        if (*(int *)(vars + 0x6C) != 0) {
            AppendPointAndColorToList(groupPoint, (int *)(vars + 0x30), buf0, (int *)buf1, &count);
            continue;
        }
        FastVecSub(scratch, (char *)&D_L00_001B8C80.x_140, groupPoint);
        vec_scale_to_length(scratch, scratch, 1.0f);
        *(TI128 *)facingBase = 0;
        *(float *)(facingBase + 0) = *(float *)(vars + 0x40);
        *(float *)(facingBase + 4) = *(float *)(vars + 0x44);
        *(float *)(facingBase + 8) = *(float *)(vars + 0x48);
        *(TI128 *)facing = *(TI128 *)facingBase;
        matrix_mul_vec3(facing, facing, (char *)entry);
        vec_scale_to_length(facing, facing, 1.0f);
        dot = FastVecDot(scratch, facing);
        if (*(float *)(vars + 0x3C) < dot) {
            dot = dot * 0.5f + 0.5f;
            if (*(int *)(vars + 0x38) != 0)
                dot = dot * dot;
            color = LerpIntegerFraction(*(int *)(vars + 0x34), *(int *)(vars + 0x30), dot);
            AppendPointAndColorToList(groupPoint, &color, buf0, (int *)buf1, &count);
        }
    }
    DrawOffsetBillboardBatch(count, buf0, buf1, *(float *)(vars + 0x4C), *(float *)(vars + 0x5C));
}

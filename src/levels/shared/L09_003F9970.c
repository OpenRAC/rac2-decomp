#include "common.h"

struct family_27f9_object;
extern float func_002A7E08(struct family_27f9_object *, float *, float *, float, float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_002AA458(void *, void *, void *, float, float, float);
extern void func_L02_00332D28(char *, char *, void *, void *, char *);
extern char *D_L09_001FE6C0[];
extern char D_00189EA0[];
extern char D_L09_001A8F20[] MACRO_ADDR;

void func_L09_003F9970(char *object)
{
    float endpoint[4] __attribute__((aligned(16)));
    float before[4] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x68);
    char *data;
    char *path;
    qcopy(before, object + 0x10);
    func_002A7E08((struct family_27f9_object *)object, *(float **)(state + 0x200),
        (float *)(state + 0x4B4), *(float *)(state + 0x114), *(float *)(state + 0x118),
        *(float *)(state + 0x11C));
    if (*(int *)(state + 0x2BC) != 255) {
        path = D_L09_001FE6C0[*(int *)(state + 0x2BC)];
        qcopy(endpoint, path + *(int *)path * 16);
        FastVecSub(endpoint, endpoint, path + 0x10);
        FastVecAdd(endpoint, endpoint, D_00189EA0);
        data = *(char **)(*(char **)(object + 0x68) + 0x18);
        func_002AA458(object + 0x10, endpoint, state + 0x4B8, *(float *)(state + 0x120),
            *(float *)(state + 0x124), *(float *)(state + 0x128));
        func_L02_00332D28(object, data, before, D_L09_001A8F20, 0);
    }
}

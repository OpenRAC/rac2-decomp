#include "include_asm.h"

typedef struct {
    unsigned char pad_000[0x18];
    int object_18;
    unsigned char pad_01C[4];
    float vector_20[4];
} L00AimState;
typedef struct {
    unsigned char pad_000[0x70];
    float value_70;
    unsigned char pad_074[0x6C];
} L00AimEntry;
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *,void *,int,void *,void *);
extern float func_00282E48(void *, void *);
extern char *func_PAL_L00_004012A0(char *, char *, char *, int);
extern void func_002A8E20(int, void *);
extern void func_PAL_0032F0B8(int, int, char *);
extern int D_0018C0B0;
extern unsigned char D_00139582;
extern L00AimState D_L00_001BF200;
extern L00AimEntry D_L00_00262570[];

int func_PAL_L00_003D6A38(char *a0, char *a1, char *a2, char *a3)
{
    char local[16];
    float distance;
    float saved;
    int ret;

    func_00282CF0(a3, a2, a1);
    func_00282F20(a3, a3, 1.5f);
    *(float *)(a3 + 0xC) = 5627.9248046875f;
    if (func_002761F8(a1, a2, 0x10, D_0018C0B0, 0) != 0) {
        func_00282CF0(local, a2, a1);
        func_00282F20(local, local, 1.0f);
        func_00282CF0(local, (char *)D_L00_001BF200.vector_20, a1);
        func_PAL_L00_004012A0(a1, local, (char *)D_L00_001BF200.vector_20, 1);
        if (D_L00_001BF200.object_18 != 0) {
            saved = (D_L00_00262570 + D_00139582)->value_70;
            distance = func_00282E48((char *)D_L00_001BF200.vector_20, a1);
            if (distance < 10.0f) {
                *(float *)(a3 + 0x1C) = saved;
            } else if (distance < 14.0f) {
                *(float *)(a3 + 0x1C) = saved * 0.75f;
            } else if (distance < 20.0f) {
                *(float *)(a3 + 0x1C) = saved * 0.5f;
            } else {
                *(float *)(a3 + 0x1C) = saved * 0.125f;
            }
            func_002A8E20(D_L00_001BF200.object_18, a3);
            func_PAL_0032F0B8(D_L00_001BF200.object_18, 0x44, a0);
        }
        ret = D_L00_001BF200.object_18;
    } else {
    func_00282CF0(local, a2, a1);
    func_PAL_L00_004012A0(a1, local, a2, 0);
    ret = 0;
    }
    return ret;
}

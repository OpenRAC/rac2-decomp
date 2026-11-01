#include "include_asm.h"

#include "common.h"
extern int D_0018C0B4 NOT_SDA;
extern int ref_L00_002FE5A0_00[] __attribute__((sda));
typedef struct { char pad[0x1C]; int count; float point[4]; char rest[0x20]; } CollisionE5;
extern CollisionE5 ref_L00_002FE5A0_01;
extern int D_001A79F0;
extern float *ref_L00_002FE5A0_02;
extern float ref_L00_002FE5A0_03[];
extern int func_002FED90(void *, void *, float, float, float);
extern void func_002FEE70(int, float *, int);
extern void func_002FE880(void *, float *, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern int func_00282948(int *);
extern void func_00282CC0(float *, float *, float *);
extern void func_00282CF0(float *, float *, float *);
extern void func_00282D30(float *, float *, float);
extern void func_00282F20(float *, float *, float);
extern void func_002FEE50(int);

int func_PAL_002FF5F8(float *start, float *motion, float *destination, float *normal,
                 void *owner, int *object_out, int *type_out, float scale)
{
    float current[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    float previous[4] __attribute__((aligned(16)));
    struct { float header[4]; float last[4]; char rest[0xE0]; } effect __attribute__((aligned(16)));
    float adjustment[4] __attribute__((aligned(16)));
    int count;
    int result = 0;
    int slot, i, type;
    if (D_0018C0B4 == 111 || ref_L00_002FE5A0_00[0]) return 0;
    qcopy(effect.last, start);
    slot = func_002FED90(&effect, 0, 1.0f, 1.0f, 1.0f);
    qcopy(previous, start);
    qcopy(current, start);
    qcopy(step, motion);
    count = 250;
    while (!func_00282948(&count)) {
        qcopy(previous, current);
        for (i = 9; i >= 0; i--) {
            func_002FEE70(slot, step, 0);
            func_00282CC0(current, current, step);
            qcopy(effect.last, current);
            func_002FE880(current, step, scale);
        }
        if (func_002761F8(previous, current, 18, owner, 0)) {
            type = func_00278E78();
            if (ref_L00_002FE5A0_01.count > 0 || type != -1) {
                if (type_out) *type_out = type;
                qcopy(destination, ref_L00_002FE5A0_01.point);
                if (D_001A79F0 == 1 && type == 3 && ref_L00_002FE5A0_02) {
                    destination[2] = *ref_L00_002FE5A0_02;
                    qcopy(adjustment, step);
                    adjustment[2] = 0;
                    func_00282F20(adjustment, adjustment, -0.9f);
                    func_00282CC0(destination, adjustment, destination);
                }
                break;
            }
        }
    }
    if (count) {
        func_00282D30(normal, (float *)((char *)&ref_L00_002FE5A0_01 + 0x40), 0.0009765625f);
        func_00282F20(normal, normal, 1.0f);
        if (object_out) *object_out = *(int *)((char *)&ref_L00_002FE5A0_01 + 0x18);
        result = 1;
        func_00282CF0(previous, destination, ref_L00_002FE5A0_03);
        func_00282D30(previous, previous, 0.94f);
        func_00282CC0(destination, previous, ref_L00_002FE5A0_03);
    }
    func_002FEE50(slot);
    return result;
}

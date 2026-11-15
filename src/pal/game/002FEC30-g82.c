#include "include_asm.h"

#include "common.h"
extern int D_0018C0B4 NOT_SDA;
extern int ref_L00_002FE5A0_00[] __attribute__((sda));
typedef struct { char pad[0x1C]; int count; float point[4]; char rest[0x20]; } CollisionE5;
extern CollisionE5 ref_L00_002FE5A0_01;
extern int g_current_map_index;
extern float *ref_L00_002FE5A0_02;
extern float ref_L00_002FE5A0_03[];
extern int part_alloc_effect_slot(void *, void *, float, float, float);
extern void part_steer_effect_direction(int, float *, int);
extern void vec_add_object_direction_scaled(void *, float *, float);
extern int CollLine(void *, void *, int, void *, int);
extern int GetCollHitMaterial(void);
extern int math_fast_float_d(int *);
extern void FastVecAdd(float *, float *, float *);
extern void FastVecSub(float *, float *, float *);
extern void FastVecScale(float *, float *, float);
extern void vec_scale_to_length(float *, float *, float);
extern void table_clear_entry_flag(int);

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
    slot = part_alloc_effect_slot(&effect, 0, 1.0f, 1.0f, 1.0f);
    qcopy(previous, start);
    qcopy(current, start);
    qcopy(step, motion);
    count = 250;
    while (!math_fast_float_d(&count)) {
        qcopy(previous, current);
        for (i = 9; i >= 0; i--) {
            part_steer_effect_direction(slot, step, 0);
            FastVecAdd(current, current, step);
            qcopy(effect.last, current);
            vec_add_object_direction_scaled(current, step, scale);
        }
        if (CollLine(previous, current, 18, owner, 0)) {
            type = GetCollHitMaterial();
            if (ref_L00_002FE5A0_01.count > 0 || type != -1) {
                if (type_out) *type_out = type;
                qcopy(destination, ref_L00_002FE5A0_01.point);
                if (g_current_map_index == 1 && type == 3 && ref_L00_002FE5A0_02) {
                    destination[2] = *ref_L00_002FE5A0_02;
                    qcopy(adjustment, step);
                    adjustment[2] = 0;
                    vec_scale_to_length(adjustment, adjustment, -0.9f);
                    FastVecAdd(destination, adjustment, destination);
                }
                break;
            }
        }
    }
    if (count) {
        FastVecScale(normal, (float *)((char *)&ref_L00_002FE5A0_01 + 0x40), 0.0009765625f);
        vec_scale_to_length(normal, normal, 1.0f);
        if (object_out) *object_out = *(int *)((char *)&ref_L00_002FE5A0_01 + 0x18);
        result = 1;
        FastVecSub(previous, destination, ref_L00_002FE5A0_03);
        FastVecScale(previous, previous, 0.94f);
        FastVecAdd(destination, previous, ref_L00_002FE5A0_03);
    }
    table_clear_entry_flag(slot);
    return result;
}

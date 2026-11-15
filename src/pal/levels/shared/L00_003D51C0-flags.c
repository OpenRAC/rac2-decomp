#include "include_asm.h"
#include "names.h"

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
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int CollLine(void *,void *,int,void *,void *);
extern float fast_vec_dist(void *, void *);
extern char *func_PAL_L00_004012A0(char *, char *, char *, int);
extern void QueueMobyImpact(int, void *);
extern void func_PAL_0032F0B8(int, int, char *);
extern int g_hero_moby;
extern unsigned char D_00139582;
extern L00AimState g_collision_result;
extern L00AimEntry g_weapon_l00_table[];

int func_PAL_L00_003D6A38(char *a0, char *a1, char *a2, char *a3)
{
    char local[16];
    float distance;
    float saved;
    int ret;

    FastVecSub(a3, a2, a1);
    vec_scale_to_length(a3, a3, 1.5f);
    *(float *)(a3 + 0xC) = 5627.9248046875f;
    if (CollLine(a1, a2, 0x10, g_hero_moby, 0) != 0) {
        FastVecSub(local, a2, a1);
        vec_scale_to_length(local, local, 1.0f);
        FastVecSub(local, (char *)g_collision_result.vector_20, a1);
        func_PAL_L00_004012A0(a1, local, (char *)g_collision_result.vector_20, 1);
        if (g_collision_result.object_18 != 0) {
            saved = (g_weapon_l00_table + D_00139582)->value_70;
            distance = fast_vec_dist((char *)g_collision_result.vector_20, a1);
            if (distance < 10.0f) {
                *(float *)(a3 + 0x1C) = saved;
            } else if (distance < 14.0f) {
                *(float *)(a3 + 0x1C) = saved * 0.75f;
            } else if (distance < 20.0f) {
                *(float *)(a3 + 0x1C) = saved * 0.5f;
            } else {
                *(float *)(a3 + 0x1C) = saved * 0.125f;
            }
            QueueMobyImpact(g_collision_result.object_18, a3);
            func_PAL_0032F0B8(g_collision_result.object_18, 0x44, a0);
        }
        ret = g_collision_result.object_18;
    } else {
    FastVecSub(local, a2, a1);
    func_PAL_L00_004012A0(a1, local, a2, 0);
    ret = 0;
    }
    return ret;
}

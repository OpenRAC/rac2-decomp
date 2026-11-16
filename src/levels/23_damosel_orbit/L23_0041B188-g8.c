#include "names.h"
/* func_L23_0041B188 is a unit of its own: it reads $gp data (-G8).  Each branch keeps its own
   block-local pointer to the slot ids, which lets gcse's copy at the join stay out of the call in
   the step < 0 branch.  The kind-2 mask is read through `second`, a pointer to the table's second
   mask: `masks + 8` stays a sum of its own until combine moves the +8 into the ld displacement,
   which leaves the table base as the first operand of the addu, as in func_L23_00418FD0. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern float g_boss_timer_value __attribute__((sda));
extern float g_boss_path_half_width __attribute__((sda));
extern float g_boss_path_target_distance __attribute__((sda));
extern float g_boss_path_max_deviation __attribute__((sda));
extern float g_boss_drift_active_flag __attribute__((sda));
extern TI128 g_boss_drift_vector;
extern char g_path_end_masks[];
extern int *g_path_lists[];

extern void mothership_project_point_onto_surface(char *, float);
extern float math_fabs(float);
extern float fast_vec_dist(char *, char *);
extern void SelectMaskedEncounterTarget(char *, u64, int, int);
extern void FastVecSub(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);

/* Moves the boss along its path toward the next point, reverses or picks a new path at the ends, and eases it back toward the middle. */
void boss_drift_along_path(char *obj) {
    char *state = *(char **)(obj + 0x68);
    char *slots;
    int *list;
    TI128 vec;
    float x, mid, dev;
    int side, flip, step, slot;

    mothership_project_point_onto_surface(state + 0x3A0, *(float *)(state + 0x588));
    mid = g_boss_timer_value;
    x = *(float *)(state + 0x5B8);
    if (mid + g_boss_path_half_width <= x || x <= mid - g_boss_path_half_width) {
        flip = 0;
        if (mid - g_boss_path_half_width < x) {
            side = 3;
            dev = math_fabs(x - mid);
            if (*(u32 *)(state + 0x5F0) >= 2) {
                flip = 1;
                *(short *)(state + 0x392) = -*(short *)(state + 0x392);
            }
            *(int *)(state + 0x5F0) = 1;
        } else {
            side = 2;
            dev = math_fabs(x - mid);
            if (*(int *)(state + 0x5F0) != 0 && *(int *)(state + 0x5F0) != 2) {
                flip = 1;
                *(short *)(state + 0x392) = -*(short *)(state + 0x392);
            }
            *(int *)(state + 0x5F0) = 2;
        }
        if (flip != 0 || fast_vec_dist(obj + 0x10, state + 0x3A0) < g_boss_path_target_distance) {
            step = *(short *)(state + 0x396) + *(short *)(state + 0x392);
            if (step < 0) {
                char *ids = state + 0x230;

                SelectMaskedEncounterTarget(obj, *(u64 *)(g_path_end_masks + (*(int *)(ids + (*(short *)(state + 0x394) << 2)) << 4)), side, 1);
            } else {
                char *ids = state + 0x230;

                slot = *(int *)(ids + (*(short *)(state + 0x394) << 2));
                list = g_path_lists[slot];
                if (step >= *list) {
                    char *masks = g_path_end_masks;
                    char *second = masks + 8;

                    SelectMaskedEncounterTarget(obj, *(u64 *)(second + (slot << 4)), side, 1);
                } else
                    *(short *)(state + 0x396) = step;
            }
            slots = state + 0x230;
            qcopy(state + 0x3A0, (char *)g_path_lists[*(int *)(slots + (*(short *)(state + 0x394) << 2))] + *(short *)(state + 0x396) * 16 + 0x10);
            mothership_project_point_onto_surface(state + 0x3A0, *(float *)(state + 0x588));
        }
        FastVecSub((char *)&vec, state + 0x3A0, obj + 0x10);
        dev = dev * 0.0625f;
        if (g_boss_path_max_deviation < dev)
            dev = g_boss_path_max_deviation;
        else if (dev < g_boss_path_max_deviation * 0.05f)
            dev = g_boss_path_max_deviation * 0.05f;
        vec_scale_to_length((char *)&vec, (char *)&vec, dev);
        qcopy(&g_boss_drift_vector, &vec);
        FastVecAdd(obj + 0x10, obj + 0x10, (char *)&vec);
        mothership_project_point_onto_surface(obj + 0x10, *(float *)(state + 0x588));
    }
    g_boss_drift_active_flag = 1.0f;
}

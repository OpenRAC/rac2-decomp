/* func_PAL_L23_0041D738, the PAL copy of func_L23_004186D0: the same C. */
#include "common.h"

/* func_PAL_L23_0041D738 is a unit of its own: it stores the $gp datum D_L23_001B1410 (-G8 by the
   file name) and calls func_L23_0041BFF0, which L23_00416388-g8.c defines.
   Retail recomputes object+16 at each use: gcse's PRE gives those uses one reaching register,
   and the middle endpoint arm's own computation survives with an end-of-arm copy into it. */

typedef int Quad __attribute__((mode(TI)));
typedef unsigned long long Mask;
extern int *g_path_lists[];
extern Mask g_path_end_masks[][2];
extern float D_L23_001B1410 __attribute__((sda));
extern void mothership_project_point_onto_surface(char *, float);
extern int mothership_check_clear_path(char *, char *, char *);
extern void mothership_pick_nearest_path_point(char *, int);
extern float fast_vec_dist(char *, char *);
extern float coll_project_point_on_segment(float *, const float *, const float *, const float *);
extern void SelectMaskedEncounterTarget(char *, Mask, int, int);
extern void FastVecSub(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern void mothership_disable_part_flags(char *);
extern int moby_copy_vector_to_child(char *, Quad *);
extern void mothership_restore_part_flags(char *);
/* Path follower state: phase at 0x390, direction (+1/-1) at 0x392, path slot index at 0x394,
   point index at 0x396, per-slot path numbers at 0x230. */
typedef struct { char pad[0x392]; short direction; } PathState;
typedef struct { int id[16]; } PathSlots;
typedef struct { char pad[0x230]; int slot[16]; } SlotState;
#define DIR (((PathState *)state)->direction)
#define H(off) (*(short *)(state + (off)))

/* Advance the selected path segment and send its displacement to the object. */
void func_PAL_L23_0041D738(char *object, float height) {
    struct { Quad target, raised, secondary, point; float before, after; } local;
    char *state = *(char **)(object + 0x68);
    char *point;
    int *list;
    int index, next;
    float distance;
    short mode;
    char *source = *(char **)(state + 0x400);
    qcopy(&local.target, source);
    qcopy(&local.raised, source);
    mothership_project_point_onto_surface((char *)&local.raised, 0.0f);
    qcopy(&local.secondary, *(char **)(state + 0x400));
    mothership_project_point_onto_surface((char *)&local.secondary, height);
    mothership_check_clear_path(object, object+16, *(char **)(state + 0x400));
    if (H(0x390) != 0)
        mothership_project_point_onto_surface(state + 0x3A0, *(float *)(state + 0x588));
    if (H(0x390) == 0) H(0x390) = 1;
    mode = H(0x390);
    H(0x406) = 0;
    if (mode) {
        switch (mode) {
        case 1:
            mothership_pick_nearest_path_point(object, 1);
            index = H(0x396);
            list = g_path_lists[((SlotState *)state)->slot[H(0x394)]];
            point = (char *)(index * 16 + (int)list + 16);
            qcopy(&local.point, point);
            H(0x390) = 2;
            distance = fast_vec_dist((char *)list + (index * 16 + 16), (char *)&local.raised);
            if (H(0x396) == 0) {
                if (fast_vec_dist((char *)list + 32, (char *)&local.raised) < distance) {
                    DIR = 1;
                    coll_project_point_on_segment((float *)(state + 0x3A0), (float *)&local.point,
                        (float *)((char *)list + (H(0x396) * 16 + 32)), (float *)(object + 16));
                } else {
                    *(Quad *)(state + 0x3A0) = local.point;
                    DIR = -1;
                }
            } else if (H(0x396) == *list - 1) {
                if (fast_vec_dist((char *)list + (*list * 16 - 16), (char *)&local.raised) < distance) {
                    DIR = -1;
                    coll_project_point_on_segment((float *)(state + 0x3A0), (float *)&local.point,
                        (float *)((char *)list + (H(0x396) * 16)), (float *)(object + 16));
                } else {
                    *(Quad *)(state + 0x3A0) = local.point;
                    DIR = 1;
                }
            } else {
                local.before = fast_vec_dist((char *)list + (H(0x396) * 16), (char *)&local.raised);
                local.after = fast_vec_dist((char *)list + (H(0x396) * 16 + 32), (char *)&local.raised);
                if (local.before < local.after) DIR = -1;
                else DIR = 1;
                coll_project_point_on_segment((float *)(state + 0x3A0), (float *)&local.point,
                    (float *)((char *)list + (DIR * 16 + 16)), (float *)(object + 16));
            }
            mothership_project_point_onto_surface(state + 0x3A0, height);
            break;
        case 2:
            if (fast_vec_dist(object + 16, state + 0x3A0) < 2.0f) H(0x390) = 3;
            else qcopy(&local.target, state + 0x3A0);
            break;
        case 3:
            if (fast_vec_dist(object + 16, state + 0x3A0) < 2.0f) {
                next = H(0x396) + DIR;
                if (next < 0) {
                    PathSlots *slots = (PathSlots *)(state + 0x230);
                    int slot = slots->id[H(0x394)];
                    SelectMaskedEncounterTarget(object, g_path_end_masks[slot][0], 1, 1);
                } else {
                    PathSlots *slots = (PathSlots *)(state + 0x230);
                    int slot = slots->id[H(0x394)];
                    if (next >= *g_path_lists[slot])
                        SelectMaskedEncounterTarget(object, g_path_end_masks[slot][1], 1, 1);
                    else H(0x396) = next;
                }
                {
                    PathSlots *slots = (PathSlots *)(state + 0x230);
                    int slot = slots->id[H(0x394)];
                    char *target = (char *)(H(0x396) * 16 + (int)g_path_lists[slot] + 16);
                    qcopy(state + 0x3A0, target);
                }
                mothership_project_point_onto_surface(state + 0x3A0, height);
            }
            qcopy(&local.target, state + 0x3A0);
            break;
        case 4:
            H(0x390) = 0;
            break;
        }
    }
    FastVecSub((char *)&local.point, (char *)&local.target, object + 16);
    vec_scale_to_length((char *)&local.point, (char *)&local.point, *(float *)(state + 0x5C8) * 0.020000001f);
    mothership_disable_part_flags(object);
    moby_copy_vector_to_child(object, &local.point);
    mothership_restore_part_flags(object);
    D_L23_001B1410 = 1.0f;
}

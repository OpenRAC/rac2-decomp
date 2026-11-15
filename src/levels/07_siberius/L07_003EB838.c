#include "common.h"

typedef int Quad __attribute__((mode(TI)));

extern int CollLine(void *, void *, int, void *, int);
extern char *moby_get_private_value_2(char *);
extern void FastVecSub(void *, void *, void *);
extern void vec_transform_by_object_or_given(void *, void *, void *, int);
extern void moby_get_attachment_rotation_angles(void *, void *, void *, void *, void *, void *);
extern void coll_apply_push_to_object(void *, void *, void *, void *, void *, void *);
extern void moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern void euler_rotation_basis(void *, void *);
extern void mat_align_to_dir(void *, void *, int);
extern void mat_get_euler_angles(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void part_queue_impact_effect(void *, int, int, void *, void *, float);

/* The last collision probe's result; +0x18 is the object it hit. */
typedef struct { char pad[24]; char *object; } Collision;
extern Collision D_L07_001BF640;
extern int g_hero_moby;
/* `sda` on an incomplete array: the one-instruction address the assembler expands absolute. */
extern char D_L07_001A8F20[] __attribute__((sda));

/* With no platform recorded at +0x314, probe from 2 above to 3 below the object and record a hit
   object whose flags have bit 1; otherwise carry the object along with its platform (states 7 and
   11 use func_002AD470) and, in mode 3, recompute its height on it. In that branch the position
   and +0xF0 vector are written `arg + 0x10` / `arg + 0xF0` at each use, without a variable:
   gcse then shares them through the copies retail has. */
void entity_ride_platform_snap_height(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float probe_start[4] __attribute__((aligned(16)));
    float probe_end[4] __attribute__((aligned(16)));
    float local_offset[4] __attribute__((aligned(16)));
    char *platform = *(char **)(vars + 0x314);
    char *pos;

    if (platform == 0) {
        pos = moby + 0x10;
        *(Quad *)probe_start = *(Quad *)pos;
        *(Quad *)probe_end = *(Quad *)pos;
        probe_start[2] += 2.0f;
        probe_end[2] -= 3.0f;
        if (CollLine(probe_start, probe_end, 0, moby, 0) && D_L07_001BF640.object != 0) {
            if (*(int *)(moby_get_private_value_2(D_L07_001BF640.object) + 0x3C) & 2) {
                *(char **)(vars + 0x314) = D_L07_001BF640.object;
                FastVecSub(local_offset, pos, *(char **)(vars + 0x314) + 0x10);
                vec_transform_by_object_or_given(*(char **)(vars + 0x314), local_offset, local_offset, 0);
                *(float *)(vars + 0x318) = local_offset[2] - 1.0f;
                moby_get_attachment_rotation_angles(moby, *(char **)(vars + 0x314), pos, moby + 0xF0, vars + 0x2F0, vars + 0x300);
            }
            *(int *)(vars + 0x88) |= 0x100;
        }
    } else {
        *(Quad *)(vars + 0x2E0) = *(Quad *)(moby + 0x10);
        if (*(unsigned char *)(moby + 0x20) == 7 || *(unsigned char *)(moby + 0x20) == 11)
            coll_apply_push_to_object(moby, platform, vars + 0x2F0, vars + 0x300, moby + 0x10, moby + 0xF0);
        else
            moby_transform_point_and_rotation_by_parent(moby, platform, moby + 0x10, moby + 0xF0, moby + 0x10, moby + 0xF0);
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        mat_align_to_dir(moby + 0xC0, *(char **)(vars + 0x314) + 0xE0, 0);
        mat_get_euler_angles(moby + 0xC0, moby + 0xF0);
        if (*(unsigned char *)(moby + 0x95) == 3) {
            FastVecSub(probe_start, moby + 0x10, *(char **)(vars + 0x314) + 0x10);
            vec_transform_by_object_or_given(*(char **)(vars + 0x314), probe_start, probe_start, 0);
            probe_start[2] = *(float *)(vars + 0x318);
            matrix_mul_vec3(probe_start, probe_start, *(char **)(vars + 0x314) + 0xC0);
            *(float *)(vars + 0x180) = probe_start[2] + *(float *)(*(char **)(vars + 0x314) + 0x18);
            if (*(float *)(moby + 0x18) < *(float *)(vars + 0x180))
                part_queue_impact_effect(moby, g_hero_moby, 0x10000, moby + 0x10, D_L07_001A8F20, 7.0f);
        }
    }
}

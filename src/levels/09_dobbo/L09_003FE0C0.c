#include "common.h"

extern int math_fast_helper_a(void *, float);
extern float vec_distance_xy(void *, void *);
extern void FastVecSub(float *, const float *, const float *);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern int coll_process_hit(void *, int, void *, void *, float);
extern void moby_transform_joint_point(char *, int, void *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void target_marker_draw(void *);
extern unsigned char *g_impact_l09_moby_table[];

/* Unit of its own for -fno-gcse: with gcse, cprop carries the copy's destination into the
   ray call's argument and keeps it in a saved register (548 bytes).

   When the object is within twice its 0x32 range of the sub-object's 0x140 point: refreshes
   the sub-object's 0x340 block, aims its 0x278/0x3DC and 0x274/0x3E0 angles along the
   0x370 to 0x390 direction, copies 0x390 to 0x330, optionally registers func_L09_003FD7D0
   when the 1.4 * 0x434 sphere test hits, and records in 0x3AC/0x44C the last hit whose
   type is 0xCB, 0x76C or 0xEB0. Returns whether it was in range. */
int aim_update_at_target(unsigned char *moby, int register_overlay) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float vec[8] __attribute__((aligned(16)));
    int done = 0;
    int count;
    int i;
    unsigned char *hit;

    if (vec_distance_xy(moby + 0x10, vars + 0x140) <
        (float)*(short *)(moby + 0x32) * 2.0f) {
        unsigned char *target_point;
        unsigned char *hit_point;
        float yaw;
        float pitch;
        float angle;

        moby_transform_joint_point((char *)moby, 1, vars + 0x340);
        done = 1;
        target_point = vars + 0x390;
        FastVecSub(vec, (float *)target_point, (float *)(vars + 0x370));
        yaw = mat_fast_helper_a(vec[0], vec[1]);
        pitch = -mat_fast_helper_a(vec_length_xy(vec), vec[2]);
        angle = fast_subtract_rotations(yaw, *(float *)(moby + 0xF8));
        *(float *)(vars + 0x278) = angle;
        *(float *)(vars + 0x3DC) = angle;
        angle = fast_subtract_rotations(pitch, *(float *)(moby + 0xF4));
        *(float *)(vars + 0x274) = angle;
        *(float *)(vars + 0x3E0) = angle;
        qcopy(vars + 0x330, target_point);
        hit_point = vars + 0x330;
        if (register_overlay != 0) {
            qcopy(vec + 4, hit_point);
            vec[7] = *(float *)(vars + 0x434) * 1.4f;
            if (math_fast_helper_a(vec + 4, (float)*(short *)(moby + 0x32)) != -1) {
                gfx_add_draw_callback_third(target_marker_draw, moby);
            }
        }
        count = coll_process_hit(hit_point, 0, 0, 0, *(float *)(vars + 0x434) * 0.9f);
        if (count > 0) {
            for (i = 0; i < count; i++) {
                if (g_impact_l09_moby_table[i] != 0) {
                    if (*(short *)(g_impact_l09_moby_table[i] + 0xAA) == MOBY_CLASS_DECOY ||
                        *(short *)(g_impact_l09_moby_table[i] + 0xAA) == 0x76C /* moby class 1900 */ ||
                        *(short *)(g_impact_l09_moby_table[i] + 0xAA) == MOBY_CLASS_DARK_SHEEP) {
                        hit = g_impact_l09_moby_table[i];
                        *(unsigned char **)(vars + 0x3AC) = hit;
                        *(int *)(vars + 0x44C) = *(short *)(hit + 0xAA);
                    }
                }
            }
        }
        if (register_overlay != 0) {
            *(int *)(vars + 0x42C) |= 2;
        }
    }
    return done;
}

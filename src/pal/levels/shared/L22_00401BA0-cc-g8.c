#include "names.h"
/* func_PAL_L22_00401BA0, the PAL copy of func_L22_003FD2D8: the same C, where rename func_L22_003FD958 becomes func_PAL_L22_00402258; wrap D_L22_001B0D48 (({e}) * 1.2f); wrap D_L22_001B0D48 (({e}) * 1.2f); wrap D_L22_001B0D48 (({e}) * 1.2f); wrap D_L22_001B0D48 (({e}) * 1.2f). */
#include "common.h"

extern char g_hero_state[], D_L22_001C00E0[];
extern float D_L22_001AF380;
extern float D_L22_001AF308;
extern float D_L22_001AF308_gp SDATA(D_L22_001AF308);
extern float D_L22_001B0D44 __attribute__((sda));
extern float D_L22_001B0D48 __attribute__((sda));
extern float D_L22_001B0D58 __attribute__((sda));
extern int D_L22_001B0D54 __attribute__((sda));
extern char *ref_L22_003FD2D8_00 __attribute__((sda));
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void cam_compute_view_direction(void *, void *, int);
extern void vec_negate_and_forward(void *, void *, int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void set_identity_rotation_rows(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void arena_push_point_out(void *, float);
extern void moby_mark_spawned(void *);
extern void snd_start_in_slot(int, int, int);
extern int flag_set_first_pending(void *);
extern int math_random_int_below(int);
extern int CollLine(void *, void *, int, int, int);
extern float fast_vec_dist(void *, void *);
extern void func_PAL_L22_00402258(void *, void *, int, int);

void func_PAL_L22_00401BA0(char *o) {
    float rot[4] __attribute__((aligned(16)));
    /* The matrix and scale workspace is reused for the late collision vectors. */
    union {
        struct { float matrix[12], a[4], b[4], scale[12]; } early;
        struct { float trace[4], random[4], a[4], b[4]; } late;
    } scratch __attribute__((aligned(16)));

    char *ctl = *(char **)(o + 0x68);
    float step;
    unsigned int count;
    if (flag_set_first_pending(o) && *(u8 *)(o + 0x20) == 16)
        snd_start_in_slot(18, 0, 0);
    if (*(u8 *)(o + 0x31)) {
        float d = fast_vec_dist(g_hero_state + 0x80, o + 0x10);
        float threshold = D_L22_001AF380;
        *(float *)(ctl + 0x44) = d;
        if (d >= threshold)
            *(u8 *)(o + 0x23) = 127;
    }
    else *(float *)(ctl + 0x44) = 2000.0f;
    if (*(u8 *)(o + 0x20) == 0) {
        qzero(rot);
        rot[2] = 0.022689285f;
        euler_rotation_basis(scratch.early.matrix, rot);
        multiply_matrix3x3(o + 0xc0, o + 0xc0, scratch.early.matrix);
        cam_compute_view_direction(o + 0x10, ctl + 0x10, 0);
        vec_negate_and_forward(o + 0xc0, ctl + 0x10, 0);
    }
    else {
        qzero(rot);
        rot[2] = ((37.0f - (float)*(u16 *)(o + 0x96)) * 22.0f + 155.0f)
                 * 0.0003490659f;
        euler_rotation_basis(scratch.early.matrix, rot);
        if (flag_set_first_pending(o)) *(u8 *)(o + 0x23) = 127;
        if (*(u8 *)(o + 0x23) >= 3) --*(u8 *)(o + 0x23);
        if (*(u8 *)(o + 0x23) >= 11 && *(u8 *)(o + 0x20) == 16) {
            switch (*(u16 *)(o + 0x96) & 3) {
            case 0:
                FastVecScale(scratch.early.a, o + 0xc0, -D_L22_001B0D58);
                FastVecAdd(scratch.early.a, scratch.early.a, o + 0x10);
                FastVecScale(scratch.early.b, o + 0xd0, -((D_L22_001B0D48) * 1.2f));
                break;
            case 1:
                FastVecScale(scratch.early.a, o + 0xc0, D_L22_001B0D58);
                FastVecAdd(scratch.early.a, scratch.early.a, o + 0x10);
                FastVecScale(scratch.early.b, o + 0xd0, ((D_L22_001B0D48) * 1.2f));
                break;
            case 2:
                FastVecScale(scratch.early.a, o + 0xd0, D_L22_001B0D58);
                FastVecAdd(scratch.early.a, scratch.early.a, o + 0x10);
                FastVecScale(scratch.early.b, o + 0xc0, ((D_L22_001B0D48) * 1.2f));
                break;
            case 3:
                FastVecScale(scratch.early.a, o + 0xd0, -D_L22_001B0D58);
                FastVecAdd(scratch.early.a, scratch.early.a, o + 0x10);
                FastVecScale(scratch.early.b, o + 0xc0, -((D_L22_001B0D48) * 1.2f));
                break;
            }
            func_PAL_L22_00402258(scratch.early.a, scratch.early.b, D_L22_001B0D54, 0);
        }
        step = 0.027027028f;
        set_identity_rotation_rows(scratch.early.scale);
        scratch.early.scale[0] = scratch.early.scale[5] = scratch.early.scale[10] =
            (37.0f - (float)*(u16 *)(o + 0x96) * step) * (D_L22_001B0D44 * step);
        multiply_matrix3x3(scratch.early.matrix, scratch.early.scale, scratch.early.matrix);
        multiply_matrix3x3(o + 0xc0, o + 0xc0, scratch.early.matrix);
        if (*(u16 *)(o + 0x96) >= 38) {
            moby_mark_spawned(o);
            return;
        }
        if (*(u8 *)(o + 0x20) == 16) {
            qcopy(o + 0x10, g_hero_state + 0x80);
            cam_compute_view_direction(o + 0x10, ctl + 0x10, 0);
            vec_negate_and_forward(o + 0xc0, ctl + 0x10, 0);
            vec_scale_to_length(scratch.early.a, ctl + 0x10, -((float)*(u16 *)(o + 0x96) * step) * 7.5f);
            FastVecAdd(o + 0x10, o + 0x10, scratch.early.a);
        }
        else {
            qcopy(o + 0x10, ref_L22_003FD2D8_00 + 0x10);
            cam_compute_view_direction(o + 0x10, ctl + 0x10, 0);
            vec_negate_and_forward(o + 0xc0, ctl + 0x10, 0);
            vec_scale_to_length(scratch.early.a, ctl + 0x10, -((float)*(u16 *)(o + 0x96) * step) * 7.5f);
            FastVecAdd(o + 0x10, o + 0x10, scratch.early.a);
        }
    }
    count = *(u16 *)(o + 0x96);
    if (count <= 65534) *(u16 *)(o + 0x96) = count + 1;
    else *(u16 *)(o + 0x96) = 0;
    if (*(short *)(ctl + 0x2a) != 0 && (*(u16 *)(o + 0x96) & 31) == 0) {
        FastVecScale(rot, ctl + 0x10, 6.0f);
        FastVecScale(scratch.late.trace, ctl + 0x10, -3.0f);
        FastVecAdd(rot, rot, o + 0x10);
        FastVecAdd(scratch.late.trace, scratch.late.trace, o + 0x10);
        if (CollLine(scratch.late.trace, rot, 18, 0, 0)) return;
        arena_push_point_out(o + 0x10, 0.0f);
        {
            float *random = scratch.late.random;
            char *dir = o + 0xc0 + math_random_int_below(2) * 16;
            float f;
            if (math_random_int_below(2)) f = D_L22_001AF308_gp;
            else f = -D_L22_001AF308;
            FastVecScale(random, dir, f);
            FastVecAdd(o + 0x10, o + 0x10, scratch.late.random);
        }
        arena_push_point_out(o + 0x10, 0.0f);
        FastVecScale(scratch.late.a, ctl + 0x10, 3.0f);
        FastVecScale(scratch.late.b, ctl + 0x10, -3.0f);
        FastVecAdd(scratch.late.a, scratch.late.a, o + 0x10);
        FastVecAdd(scratch.late.b, scratch.late.b, o + 0x10);
        if (CollLine(scratch.late.b, scratch.late.a, 18, 0, 0))
            qcopy(o + 0x10, D_L22_001C00E0);
        *(short *)(ctl + 0x2a) = 0;
    }
}

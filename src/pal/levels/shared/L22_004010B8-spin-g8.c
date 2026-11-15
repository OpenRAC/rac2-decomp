#include "names.h"
/* func_PAL_L22_004010B8, the PAL copy of func_L22_003FC870: the same C at 50 Hz, where the 45-frame
   spin becomes 37 frames (46 becomes 38, 1/45 becomes 1/37), the rotation rates scale by 6/5 and
   ref_L22_003FC870_01 by 1.2. */
#include "common.h"
extern u8 g_hero_state[];
extern f32 fast_vec_dist(void *, void *);
extern void cam_compute_view_direction(void *, void *, int);
extern int flag_set_first_pending(void *);
extern void snd_start_in_slot(int, int, int);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void vec_negate_and_forward(void *, void *, int);
extern void FastVecScale(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern void set_identity_rotation_rows(void *);
extern void part_kill(void *);
extern void moby_mark_spawned(void *);
extern void vec_scale_to_length(void *, void *, f32);
extern int CollLine(void *, void *, int, int, int);
extern void arena_push_point_out(void *, f32);
extern int math_random_int_below(int);
extern f32 ref_L22_003FC870_00 __attribute__((sda));
extern f32 ref_L22_003FC870_01 __attribute__((sda));
extern int ref_L22_003FC870_02 __attribute__((sda));
extern f32 ref_L22_003FC870_03 __attribute__((sda));
extern u8 * ref_L22_003FC870_04 __attribute__((sda));
extern f32 ref_L22_003FC870_05 __attribute__((sda));
extern f32 ref_L22_003FC870_06;
extern const f32 ref_L22_003FC870_07;
extern u8 ref_L22_003FC870_08[];
extern u8 * ref_L22_003FC870_09;
extern void func_PAL_L22_00401788(void *, void *, int, int);

void func_PAL_L22_004010B8(u8 *obj) {
    u8 *ctl = *(u8 **)(obj + 0x68);
    f32 f;
    int i;
    u8 *basis;
    f32 side;
    f32 rot[4] __attribute__((aligned(16)));
    union {
        struct {
            f32 mat[12];
            f32 start[4];
            f32 end[4];
            f32 scale[12];
        } transform;
        struct {
            f32 mat[4];
            f32 move[4];
            f32 start[4];
            f32 end[4];
        } collision;
    } scratch __attribute__((aligned(16)));
    if (flag_set_first_pending(obj) && obj[0x20] == 0x10) snd_start_in_slot(0x12, 0, 0);
    if (obj[0x31]) {
        f = fast_vec_dist(g_hero_state + 0x80, obj + 0x10);
        *(f32 *)(ctl + 0x44) = f;
    if (ref_L22_003FC870_07 <= f) obj[0x23] = 127;
    } else *(f32 *)(ctl + 0x44) = 2000.0f;
    if (obj[0x20] == 0) {
        qzero_nc(rot);
        rot[2] = 0.022689285f;
        euler_rotation_basis(scratch.transform.mat, rot);
        multiply_matrix3x3(obj + 0xC0, obj + 0xC0, scratch.transform.mat);
        cam_compute_view_direction(obj + 0x10, ctl + 0x10, 0);
        vec_negate_and_forward(obj + 0xC0, ctl + 0x10, 0);
    } else {
        qzero_nc(rot);
        rot[2] = ((37.0f - (f32)*(u16 *)(obj + 0x96)) * 22.0f + 155.0f) * 0.0003490659f;
        euler_rotation_basis(scratch.transform.mat, rot);
        if (flag_set_first_pending(obj)) { obj[0x23] = 127; *(f32 *)(obj + 0x2C) *= 1.2f; }
        if (obj[0x23] >= 3) obj[0x23]--;
        if (obj[0x23] >= 11 && obj[0x20] == 0x10) {
            switch (*(u16 *)(obj + 0x96) & 3) {
            case 0:
                FastVecScale(scratch.transform.start, obj + 0xC0, -ref_L22_003FC870_00);
                FastVecAdd(scratch.transform.start, scratch.transform.start, obj + 0x10);
                FastVecScale(scratch.transform.end, obj + 0xD0, -(ref_L22_003FC870_01 * 1.2f));
                break;
            case 1:
                FastVecScale(scratch.transform.start, obj + 0xC0, ref_L22_003FC870_00);
                FastVecAdd(scratch.transform.start, scratch.transform.start, obj + 0x10);
                FastVecScale(scratch.transform.end, obj + 0xD0, ref_L22_003FC870_01 * 1.2f);
                break;
            case 2:
                FastVecScale(scratch.transform.start, obj + 0xD0, ref_L22_003FC870_00);
                FastVecAdd(scratch.transform.start, scratch.transform.start, obj + 0x10);
                FastVecScale(scratch.transform.end, obj + 0xC0, ref_L22_003FC870_01 * 1.2f);
                break;
            case 3:
                FastVecScale(scratch.transform.start, obj + 0xD0, -ref_L22_003FC870_00);
                FastVecAdd(scratch.transform.start, scratch.transform.start, obj + 0x10);
                FastVecScale(scratch.transform.end, obj + 0xC0, -(ref_L22_003FC870_01 * 1.2f));
                break;
            }
            func_PAL_L22_00401788(scratch.transform.start, scratch.transform.end, ref_L22_003FC870_02, 0);
        }
        set_identity_rotation_rows(scratch.transform.scale);
        scratch.transform.scale[0] = scratch.transform.scale[5] = scratch.transform.scale[10] = (37.0f - (f32)*(u16 *)(obj + 0x96) * 0.027027028f) * (ref_L22_003FC870_03 * 0.027027028f);
        multiply_matrix3x3(scratch.transform.mat, scratch.transform.scale, scratch.transform.mat);
        multiply_matrix3x3(obj + 0xC0, obj + 0xC0, scratch.transform.mat);
        
        if (*(u16 *)(obj + 0x96) >= 38) {
            moby_mark_spawned(obj);
            return;
        }
        if (obj[0x20] == 0x10) {
            qcopy(obj + 0x10, g_hero_state + 0x80);
            cam_compute_view_direction(obj + 0x10, ctl + 0x10, 0);
            vec_negate_and_forward(obj + 0xC0, ctl + 0x10, 0);
            vec_scale_to_length(scratch.transform.start, ctl + 0x10, -((f32)*(u16 *)(obj + 0x96) * 0.027027028f) * 7.5f);
            FastVecAdd(obj + 0x10, obj + 0x10, scratch.transform.start);
        } else {
            qcopy(obj + 0x10, ref_L22_003FC870_04 + 0x10);
            cam_compute_view_direction(obj + 0x10, ctl + 0x10, 0);
            vec_negate_and_forward(obj + 0xC0, ctl + 0x10, 0);
            vec_scale_to_length(scratch.transform.start, ctl + 0x10, -((f32)*(u16 *)(obj + 0x96) * 0.027027028f) * 7.5f);
            FastVecAdd(obj + 0x10, obj + 0x10, scratch.transform.start);
        }
    }
    if (*(u16 *)(obj + 0x96) < 65535) (*(u16 *)(obj + 0x96))++;
    else *(u16 *)(obj + 0x96) = 0;
    if (*(s16 *)(ctl + 0x2A) != 0 && (*(u16 *)(obj + 0x96) & 31) == 0) {
        FastVecScale(rot, ctl + 0x10, 6.0f);
        FastVecScale(scratch.collision.mat, ctl + 0x10, -3.0f);
        FastVecAdd(rot, rot, obj + 0x10);
        FastVecAdd(scratch.collision.mat, scratch.collision.mat, obj + 0x10);
        if (CollLine(scratch.collision.mat, rot, 0x12, 0, 0) == 0) {
            arena_push_point_out(obj + 0x10, 0.0f);
            FastVecScale(scratch.collision.move,
                obj + 0xC0 + math_random_int_below(2) * 16,
                math_random_int_below(2) ? ref_L22_003FC870_05 : -ref_L22_003FC870_06);
            FastVecAdd(obj + 0x10, obj + 0x10, scratch.collision.move);
            arena_push_point_out(obj + 0x10, 0.0f);
            FastVecScale(scratch.collision.start, ctl + 0x10, 3.0f);
            FastVecScale(scratch.collision.end, ctl + 0x10, -3.0f);
            FastVecAdd(scratch.collision.start, scratch.collision.start, obj + 0x10);
            FastVecAdd(scratch.collision.end, scratch.collision.end, obj + 0x10);
            if (CollLine(scratch.collision.end, scratch.collision.start, 0x12, 0, 0)) qcopy(obj + 0x10, ref_L22_003FC870_08);
            *(s16 *)(ctl + 0x2A) = 0;
        }
    }
}

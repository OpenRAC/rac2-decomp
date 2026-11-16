#include "include_asm.h"

#include "common.h"
extern char g_active_camera[];
extern char g_camera_state_block[];
extern unsigned char g_cheat_flags[] __attribute__((sda));
extern void cam_update_scalar_transition(void);
extern void cam_update_second_scalar_transition(void);
extern void cam_select_coll_masks(void);
extern void cam_update_follow_hero(void);
extern int cam_update_active(void);
extern void func_PAL_00270D50(void *);
extern int stub_empty_22(void);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void mat_get_euler_angles(void *, void *);
extern void cam_update_shake_pal(void *, int);
extern void cam_update_grounded(void);
extern void gfx_blend_fog_from_cam_region(void *);
extern void cam_update_fov_transition(void);

void cam_update_state_pal(void) {
    char *d = g_active_camera;
    char *obj;
    char *p;
    char *q;
    char *r;

    *(int *)(d + 0x404) = *(int *)(d + 0x404) + 1;
    cam_update_scalar_transition();
    cam_update_second_scalar_transition();
    cam_select_coll_masks();
    cam_update_follow_hero();
    cam_update_active();
    obj = *(char **)(d + 0x190);
    if ((unsigned)(*(unsigned short *)(d + 0x290) - 1) < 2)
        func_PAL_00270D50(*(void **)(d + 0x194));
    if (*(short *)(d + 0x290) == 3) {
        moby_test_and_snapshot(obj);
    } else {
        qcopy(d + 0x140, obj + 0x30);
        qcopy(d + 0x370, obj);
        qcopy(d + 0x380, obj + 0x10);
        qcopy(d + 0x390, obj + 0x20);
    }
    if (stub_empty_22()) {
        p = g_active_camera + 0x140;
        qcopy(p, g_camera_state_block);
        qcopy(p + 0x230, g_camera_state_block + 0x10);
        FastVecCross(p + 0x240, p + 0x230, g_camera_state_block - 0x14B0);
        vec_scale_to_length(p + 0x240, p + 0x240, 1.0f);
        FastVecCross(p + 0x250, p + 0x240, p + 0x230);
        vec_scale_to_length(p + 0x250, p + 0x250, 1.0f);
    }
    q = g_active_camera + 0x370;
    mat_get_euler_angles(q, q - 0x220);
    cam_update_shake_pal(q - 0x210, 0);
    cam_update_shake_pal(q - 0x200, 1);
    cam_update_shake_pal(q - 0x1F0, 2);
    cam_update_grounded();
    gfx_blend_fog_from_cam_region(q - 0x230);
    if (g_cheat_flags[0])
        FastVecCross(q + 0x10, q + 0x20, q);
    cam_update_fov_transition();
    qzero(q + 0x50);
}

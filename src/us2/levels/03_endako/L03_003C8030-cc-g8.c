/* func_US2_L03_003C8030, the USA v2.00 copy of func_L03_003C6A28: the same C, where rename func_0029B810 becomes func_US2_0029C600; rename func_0029B7C0 becomes func_US2_0029C5B0. */

#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));

typedef struct {
    char pad0[0x80];
    float pos[4];      /* 0x80 */
    float rot[4];      /* 0x90 */
    char padA0[0x13C];
    short mode;        /* 0x1DC */
    char pad1DE[0x1652];
    int field1830;     /* 0x1830 */
} Hero6A28;

typedef struct {
    char pad[0x3D4];
    float f;           /* 0x3D4 */
    char pad2[0x10];
    char b0;           /* 0x3E8 */
    char b1;           /* 0x3E9 */
} AimState6A28;

extern void moby_mark_spawned(char *);
extern void moby_set_state(char *, int, int);
extern float vec_distance_xy(char *, char *);
extern void matrix_from_basis_rows(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern int flag_is_third_pending_set(char *);
extern int hero_is_allowed_for_mode(int);
extern void TryClaimNotice(int, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void vec_clear_128(void *);
extern float FastAddRotations(float, float);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void camera_select_remote_view(char *, void *, void *);
extern void SetCamera5Pose(void *, void *, int, int, int);
extern void console_start_remote_view(char *);
extern void console_end_remote_view(char *);
extern void cam_set_mode_state(int);
extern void func_US2_0029C600(int);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern int entity_prepare_shot(void *);
extern void moby_set_flag_bit(void *, int);
extern void func_US2_0029C5B0(void *, void *, int);
extern void menu_draw_two_line_panel(void);

extern Hero6A28 g_hero_state;
extern char g_hero_position[];
/* Entity pool base (256-byte entries): absolute and $gp-relative views. */
extern char *D_L03_001B2A1C MACRO_ADDR;
extern char *D_L03_001B2A1C_GP SDATA(D_L03_001B2A1C);
extern char *D_0018B650 NOT_SDA;
extern int D_00138324 NOT_SDA;
extern AimState6A28 D_L03_001B9840;
extern char D_L03_003C7010[];

void func_US2_L03_003C8030(char *obj)
{
    char mat[0x40] __attribute__((aligned(16)));
    float local[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float cam1[4] __attribute__((aligned(16)));
    float cam2[4] __attribute__((aligned(16)));
    char *vars = *(char **)(obj + 0x68);

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        if (*(int *)vars == -1) {
            moby_mark_spawned(obj);
            break;
        }
        *(int *)(vars + 0x30) = -1;
        *(int *)(obj + 0x98) = 0;
        *(unsigned short *)(obj + 0x34) |= 1;
        obj[0x31] = 0;
        moby_set_state(obj, 1, -1);
        break;

    case 1:
    case 2:
        if (vec_distance_xy(obj + 0x10, g_hero_position) < 6.0f && *(int *)(g_hero_position + 0x2C0)) {
            matrix_from_basis_rows(mat, obj + 0xC0);
            FastVecSub(local, g_hero_position, obj + 0x10);
            matrix_mul_vec3(local, local, mat);
            if (*(u8 *)(obj + 0x20) == 1 && flag_is_third_pending_set(obj))
                moby_set_state(obj, 2, -1);
            if (local[0] < 4.0f && local[0] > 0.0f && local[1] < 2.5f && local[1] > -2.5f) {
                if (*(u8 *)(obj + 0x20) == 1) {
                    TryClaimNotice(8, 0x1310, 1);
                    break;
                }
                TryClaimNotice(8, 0x12fa, 1);
                if (hero_is_allowed_for_mode(8) && (D_00138324 & 0x10)) {
                    moby_set_state(obj, 3, -1);
                    *(Quad *)pos = 0;
                    pos[0] = 2.0f;
                    matrix_mul_vec3(pos, pos, obj + 0xC0);
                    FastVecAdd(pos, pos, obj + 0x10);
                    vec_clear_128(rot);
                    rot[2] = FastAddRotations(*(float *)(obj + 0xF8), 3.14159f);
                    hero_reset_position_and_direction(pos, rot, 0x31, 1);
                    D_0018B650 = D_L03_001B2A1C + (*(int *)vars << 8);
                    camera_select_remote_view(obj, cam1, cam2);
                    SetCamera5Pose(cam1, cam2, 1, 0, 0);
                    console_start_remote_view(D_L03_001B2A1C + (*(int *)vars << 8));
                }
            }
        }
        break;

    case 3:
        g_hero_state.mode = 5;
        if (D_00138324 & 0x10) {
            cam_set_mode_state(0);
            hero_reset_position_and_direction(g_hero_state.pos, g_hero_state.rot, 0, 1);
            g_hero_state.field1830 = 0;
            console_end_remote_view(D_L03_001B2A1C + (*(int *)vars << 8));
            D_L03_001B9840.f = 64.42f;
            D_L03_001B9840.b1 = 1;
            D_L03_001B9840.b0 = 0;
            moby_set_state(obj, 2, -1);
            func_US2_0029C600(0);
        } else {
            camera_select_remote_view(obj, mat, mat + 0x10);
            object_copy_vector_to_selected(mat);
            cam_set_state_rotation(mat + 0x10);
            if (*(int *)(vars + 0x1C) != -1
                && entity_prepare_shot(D_L03_001B2A1C_GP + (*(int *)(vars + 0x1C) << 8))) {
                if (*(int *)(vars + 0x20) != -1)
                    moby_set_flag_bit(D_L03_001B2A1C_GP + (*(int *)(vars + 0x20) << 8), 1);
            }
            func_US2_0029C5B0(D_L03_003C7010, menu_draw_two_line_panel, 0);
        }
        break;
    }
}

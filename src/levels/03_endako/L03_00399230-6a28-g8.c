#include "include_asm.h"

#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));

typedef struct {
    char pad0[0x80];
    float position[4];      /* 0x80 */
    float rotation[4];      /* 0x90 */
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
extern int TryClaimNotice(int, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void vec_clear_128(void *);
extern float FastAddRotations(float, float);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void camera_select_remote_view(char *, void *, void *);
extern void SetCamera5Pose(void *, void *, int, int, int);
extern void console_start_remote_view(char *);
extern void console_end_remote_view(char *);
extern void cam_set_mode_state(int);
extern void level_clear_table_entry(int);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern int entity_prepare_shot(void *);
extern void moby_set_flag_bit(void *, int);
extern int level_set_table_entry(void *, void *, int);
extern int menu_draw_two_line_panel(void);

extern Hero6A28 g_hero_state;
extern char g_hero_position[];
/* Entity pool base (256-byte entries): absolute and $gp-relative views. */
extern char *g_moby_record_base MACRO_ADDR;
extern char *D_L03_001B2A1C_GP SDATA(D_L03_001B2A1C);
extern char *g_held_object_ptr NOT_SDA;
extern int g_pad_held_flags NOT_SDA;
extern AimState6A28 g_hero_l03_state_alias;
extern char g_str_camera_console_entry[];

/* Updates a camera console. When the player stands in front of it and presses the button, the view switches to a remote camera, and it switches back on the next press. */
void camera_console_update(char *obj)
{
    char mat[0x40] __attribute__((aligned(16)));
    float local_pos[4] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float camera_pos[4] __attribute__((aligned(16)));
    float camera_rot[4] __attribute__((aligned(16)));
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
            FastVecSub(local_pos, g_hero_position, obj + 0x10);
            matrix_mul_vec3(local_pos, local_pos, mat);
            if (*(u8 *)(obj + 0x20) == 1 && flag_is_third_pending_set(obj))
                moby_set_state(obj, 2, -1);
            if (local_pos[0] < 4.0f && local_pos[0] > 0.0f && local_pos[1] < 2.5f && local_pos[1] > -2.5f) {
                if (*(u8 *)(obj + 0x20) == 1) {
                    TryClaimNotice(8, 0x27BE, 1);
                    break;
                }
                TryClaimNotice(8, 0x27A8, 1);
                if (hero_is_allowed_for_mode(8) && (g_pad_held_flags & 0x10)) {
                    moby_set_state(obj, 3, -1);
                    *(Quad *)position = 0;
                    position[0] = 2.0f;
                    matrix_mul_vec3(position, position, obj + 0xC0);
                    FastVecAdd(position, position, obj + 0x10);
                    vec_clear_128(rotation);
                    rotation[2] = FastAddRotations(*(float *)(obj + 0xF8), 3.14159f);
                    hero_reset_position_and_direction(position, rotation, 0x31, 1);
                    g_held_object_ptr = g_moby_record_base + (*(int *)vars << 8);
                    camera_select_remote_view(obj, camera_pos, camera_rot);
                    SetCamera5Pose(camera_pos, camera_rot, 1, 0, 0);
                    console_start_remote_view(g_moby_record_base + (*(int *)vars << 8));
                }
            }
        }
        break;

    case 3:
        g_hero_state.mode = 5;
        if (g_pad_held_flags & 0x10) {
            cam_set_mode_state(0);
            hero_reset_position_and_direction(g_hero_state.position, g_hero_state.rotation, 0, 1);
            g_hero_state.field1830 = 0;
            console_end_remote_view(g_moby_record_base + (*(int *)vars << 8));
            g_hero_l03_state_alias.f = 64.42f;
            g_hero_l03_state_alias.b1 = 1;
            g_hero_l03_state_alias.b0 = 0;
            moby_set_state(obj, 2, -1);
            level_clear_table_entry(0);
        } else {
            camera_select_remote_view(obj, mat, mat + 0x10);
            object_copy_vector_to_selected(mat);
            cam_set_state_rotation(mat + 0x10);
            if (*(int *)(vars + 0x1C) != -1
                && entity_prepare_shot(D_L03_001B2A1C_GP + (*(int *)(vars + 0x1C) << 8))) {
                if (*(int *)(vars + 0x20) != -1)
                    moby_set_flag_bit(D_L03_001B2A1C_GP + (*(int *)(vars + 0x20) << 8), 1);
            }
            level_set_table_entry(g_str_camera_console_entry, menu_draw_two_line_panel, 0);
        }
        break;
    }
}

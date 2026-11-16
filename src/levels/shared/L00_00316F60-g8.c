#include "include_asm.h"
#include "common.h"

extern int g_counter_list_head;
extern int g_counter_list_count_a __attribute__((sda));
extern int g_counter_list_alt_head;
extern int g_counter_list_count_b __attribute__((sda));

/* Clears a list of five counters and a related value. */
void level_l00_clear_counter_list(void) {
    int count = 4;
    int *cursor = &g_counter_list_head;

    do {
        *cursor = 0;
        --cursor;
        --count;
    } while (count >= 0);
    g_counter_list_count_a = 0;
}

/* Clears a second list of five counters and a related value. */
void level_l00_clear_counter_list_2(void) {
    int count = 4;
    int *cursor = &g_counter_list_alt_head;

    do {
        *cursor = 0;
        --cursor;
        --count;
    } while (count >= 0);
    g_counter_list_count_b = 0;
}

extern int g_input_block_flag;
extern int D_L00_001A8FB4_1 __attribute__((sda));
extern int g_hit_streak_state;
extern int g_hit_streak_hud_slot;
extern int D_L00_001B2084_1 __attribute__((sda));
extern void level_l00_call_module_handler_9(void);
extern int hud_close_element_by_key(int);

/* If the value matches the current one, resets that state and releases the resource, returning 1. */
int level_release_matching_resource(int value) {
    if (g_input_block_flag != value)
        return 0;
    if (g_hit_streak_hud_slot == -1)
        return 0;

    g_hit_streak_state = 0;
    D_L00_001A8FB4_1 = 0;
    level_l00_call_module_handler_9();
    hud_close_element_by_key(D_L00_001B2084_1);
    g_hit_streak_hud_slot = -1;
    return 1;
}

extern unsigned char *g_collision_cylinder_table;

extern void func_2EE138(void *, void *, void *);
extern void func_2EE5B0(void *, void *, void *);
extern float func_2EE268(void *);

/* Screens the 128-byte record the index picks out of the resident object table: runs the
   caller's transform through the record's two matrices and accepts only when the remaining
   length is under 1 and the record's own z direction stays inside [-1, 1]. */
int coll_point_inside_record_volume(void *transform, int index)
{
    unsigned char *entry;
    float b1[4];
    float b2[4];

    if (index < 0)
        return 0;
    entry = g_collision_cylinder_table + (index << 7);
    func_2EE138(b1, transform, entry + 0x30);
    *(int *)((unsigned char *)b1 + 0xC) = 0;
    func_2EE5B0(b2, b1, entry + 0x40);
    if (func_2EE268(b2) < 1.0f) {
        if (*(float *)((unsigned char *)b2 + 8) >= -1.0f) {
            if (*(float *)((unsigned char *)b2 + 8) <= 1.0f)
                return 1;
        }
    }
    return 0;
}

extern void moby_transform_joint_point(void *, int, void *);
extern void euler_rotation_basis(void *, void *);
extern void copy_matrix3x4(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern char *g_moby_array_base;
extern char *g_tie_matrix_table;
extern char *g_shrub_matrix_table;
typedef struct {
    char transform[48];
    float position[4];
    void *offset;
    void *attachment;
    short index;
    unsigned char end, joint, type, copy_matrix, period, phase;
} B1320Entry;
extern void mem_fast_helper_c(void *, void *, int);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_copy_helper_b(void *, void *, void *);
extern void copy_matrix_rotation(void *, void *);
extern void mat_get_euler_angles(void *, void *);
extern void func_002A0F48(void *);
extern void gfx_setup_scale_record(int, int);
extern float FastVecLength(void *);
extern int FloatToInt(float);
extern void scale_vector(void *, void *, float);
extern int g_frame_l00_counter __attribute__((sda));
extern char *g_shrub_table;
extern char *g_shrub_l00_class_table[];
/* Moves linked objects, lights and similar items to follow an object using a list of attachment entries. */
void moby_update_attached_transforms(char *object, B1320Entry *entries)
{
    char matrix[64] __attribute__((aligned(16)));
    char temp[64] __attribute__((aligned(16)));
    char rotation[64] __attribute__((aligned(16)));
    unsigned int i;
    float x, y;
    int sx, sy, active;
    if (!entries->end) return;
    if (entries->copy_matrix) mem_fast_helper_c(matrix, object + 0xC0, 48);
    else euler_rotation_basis(matrix, object + 0xF0);
    qcopy_nc(matrix + 48, object + 0x10);
    *(int *)(matrix + 60) = 0;
    i = 0;
    do {
        if (entries[i].attachment) {
            moby_transform_joint_point(entries[i].attachment, entries[i].joint, temp);
            copy_matrix3x4(matrix, temp);
        }
        switch (entries[i].type) {
        case 0:
            matrix_mul_vec3(temp, entries[i].position, matrix);
            FastVecAdd(g_moby_array_base + entries[i].index * 256 + 0x10, matrix + 48, temp);
            if (entries[i].offset) FastVecAdd(g_moby_array_base + entries[i].index * 256 + 0x10, g_moby_array_base + entries[i].index * 256 + 0x10, (char *)entries[i].offset + 0x10);
            break;
        case 1:
            matrix_mul_vec3(temp, entries[i].position, matrix);
            vec_copy_helper_b(g_tie_matrix_table + entries[i].index * 64 + 0x30, matrix + 48, temp);
            break;
        case 2:
            matrix_mul_vec3(temp, entries[i].position, matrix);
            vec_copy_helper_b(g_shrub_matrix_table + entries[i].index * 64 + 0x30, matrix + 48, temp);
            break;
        }
        switch (entries[i].type) {
        case 0: {
            char *item;
            item = g_moby_array_base + entries[i].index * 256;
            if (!*(int *)(item + 0x24)) euler_rotation_basis(item + 0xC0, item + 0xF0);
            multiply_matrix3x3(item + 0xC0, matrix, &entries[i]);
            if (entries[i].offset) {
                euler_rotation_basis(temp + 16, entries[i].offset);
                multiply_matrix3x3(item + 0xC0, item + 0xC0, temp + 16);
            }
            if (!*(int *)(item + 0x24)) {
                copy_matrix_rotation(rotation, item + 0xC0);
                mat_get_euler_angles(rotation, item + 0xF0);
            }
            break;
        }
        case 1: {
            char *item;
            item = g_tie_matrix_table + entries[i].index * 64;
            multiply_matrix3x3(item, matrix, &entries[i]);
            if (entries[i].offset) {
                euler_rotation_basis(temp + 16, entries[i].offset);
                multiply_matrix3x3(item, item, temp + 16);
            }
            break;
        }
        case 2:
            multiply_matrix3x3(g_shrub_matrix_table + entries[i].index * 64, matrix, &entries[i]);
            break;
        }
        switch (entries[i].type) {
        case 0: {
            typedef struct { char p[0x24]; int f; char q[256-0x28]; } M;
            if (((M *)g_moby_array_base)[entries[i].index].f) func_002A0F48(&((M *)g_moby_array_base)[entries[i].index]);
            break;
        }
        case 1:
            active = 0;
            if (entries[i].period == 0) active = 1;
            else if (entries[i].period != 255) {
                if (g_frame_l00_counter % entries[i].period == entries[i].phase) active = 1;
            }
            gfx_setup_scale_record(entries[i].index, active);
            break;
        case 2: {
            char *item, *data;
            item = g_shrub_matrix_table + entries[i].index * 64;
            data = g_shrub_table + entries[i].index * 32;
            x = FastVecLength(item);
            x += FastVecLength(item + 0x10);
            x *= 0.5f;
            y = FastVecLength(item + 0x20);
            sx = FloatToInt(x * 4096.0f);
            sy = FloatToInt(y * 4096.0f);
            sy = sy <= 65536 ? sy : 65536;
            sy <<= 16;
            if (sx > 65536) sx = 65536;
            *(int *)(item + 0x2C) = sx | sy;
            matrix_mul_vec3(data, g_shrub_l00_class_table[(unsigned char)data[0x1A]], item);
            scale_vector(data, data, *(float *)(item + 0x3C));
            FastVecAdd(data, data, item + 0x30);
            break;
        }
        }
    } while (entries[i++].end != 1);
}

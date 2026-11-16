#include "common.h"

extern int g_current_map_index[] __attribute__((sda));
typedef struct {
    char pad[0x30];
    int mode, timer;
    char gap38[0x44-0x38];
    short count;
    char gap46[0x50-0x46];
    char *output;
    char gap54[0x18C-0x54];
    char *parts[4];
} Hero;
extern Hero g_hero_part_state;
extern char g_level_scratch_buffer[];
extern float g_hero_vertex_table[4][4] __attribute__((sda));
extern void vec_fast_to_int_helper(void *, void *);
extern void quaternion_to_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

/* Places the four corner points of a quad on the hero's part so the quad follows it, and removes
   the quad after a fixed time. */
void UpdateJammingArrayQuadVertices(void) {
    float matrix[12];
    float rotation[12];
    char *child;
    int index;

    float *out;
    float *vertex;
    float scale;
    int count;
    if (g_current_map_index[0] != 26) return;
    child = 0;
    index = -1;
    switch (g_hero_part_state.mode) {
    case 0:
        child = g_hero_part_state.parts[2];
        index = 1;
        break;
    case 1:
        index = 1;
        child = g_hero_part_state.parts[2];
        break;
    }
    if (index != -1 && child != 0 && g_hero_part_state.parts[index] != 0) {
        g_hero_part_state.output = g_level_scratch_buffer;
        out = (float *)(g_level_scratch_buffer + 0x20);
        vertex = g_hero_vertex_table[0];
        vec_fast_to_int_helper(*(char **)(child + 0x58) + 0x10, rotation);
        quaternion_to_rotation_basis(rotation, matrix);
        scale = *(float *)(child + 0x2C) / *(float *)(*(char **)(child + 0x24) + 0x24);
        count = 3;
        do {
            matrix_mul_vec3(out, vertex, matrix);
            vertex += 4;
            FastVecScale(out, out, scale);
            FastVecAdd(out, out, child + 0x10);
            out += 4;
        } while (--count >= 0);
        *(char **)(g_hero_part_state.output + 0x68) = g_hero_part_state.parts[index];
    }
    if (g_hero_part_state.timer >= 0x597) g_hero_part_state.output = 0;
}

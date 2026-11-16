#include "include_asm.h"
#include "names.h"
extern int g_level_group_index;
extern void *tv_screen_find_nearest(float, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char g_ship_trail_mesh[];
extern int g_ship_trail_constants __attribute__((sda));
typedef struct {
    char pad0[0x30];
    int mode;
    int count;
    char pad1[0x18];
    int mesh;
    char pad2[0x138];
    int *entries[4];
} L01_002F2098_STATE;
extern L01_002F2098_STATE g_ship_trail_state;

/* Builds the ship's four trail slices for the level's current colour. */
void ship_build_trail_slices_pal(void)
{
    int index;
    void *obj;
    float scale;
    char *vertex;
    char *constants;
    int i;

    if (g_level_group_index != 1)
        return;

    index = -1;
    obj = tv_screen_find_nearest(0.0f, 0.0f, 0.0f);
    if (g_ship_trail_state.mode == 3)
        index = 1;
    if (index != -1 && obj != 0) {
        if (g_ship_trail_state.entries[index] != 0) {
            char *position = obj + 0x10;
            char *matrix = obj + 0xC0;
            g_ship_trail_state.mesh = (int)g_ship_trail_mesh;
            vertex = (char *)g_ship_trail_mesh + 0x20;
            constants = (char *)&g_ship_trail_constants;
            i = 3;
            scale = *(float *)(obj + 0x2C) / *(float *)(*(int *)(obj + 0x24) + 0x24);
            for (; i >= 0; i--) {
                matrix_mul_vec3(vertex, constants, matrix);
                FastVecScale(vertex, vertex, scale);
                FastVecAdd(vertex, vertex, position);
                vertex += 0x10;
                constants += 0x10;
            }
            *(int *)(g_ship_trail_state.mesh + 0x68) = g_ship_trail_state.entries[index];
        }
    }
    if (g_ship_trail_state.count >= 0x4DE)
        g_ship_trail_state.mesh = 0;
}

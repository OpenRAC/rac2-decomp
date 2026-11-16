#include "include_asm.h"
#include "names.h"
extern int g_current_map_index;
extern void *tv_screen_find_nearest(float, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char g_trail_slice_mesh[];
extern int g_trail_slice_source __attribute__((sda));
typedef struct {
    char pad0[0x30];
    unsigned int mode;
    int count;
    char pad1[0x18];
    int mesh;
    char pad2[0x138];
    int *entries[4];
} L12_002FFF88_STATE;
extern L12_002FFF88_STATE g_trail_slice_state;

/* Builds the level's four trail slices for the mesh its state points at. */
void todano_build_trail_slice_meshes_pal(void)
{
    int index;
    void *screen;
    float mesh_scale;
    char *source;
    int i;
    int offset;

    if (g_current_map_index != 12)
        return;

    screen = 0;
    index = -1;
    if (g_trail_slice_state.mode < 2) {
        screen = tv_screen_find_nearest(0.0f, 0.0f, 0.0f);
        index = 2;
    }
    if (index != -1 && screen != 0) {
        if (g_trail_slice_state.entries[index] != 0) {
            char *position = screen + 0x10;
            char *basis = screen + 0xC0;
            g_trail_slice_state.mesh = (int)g_trail_slice_mesh;
            source = (char *)&g_trail_slice_source;
            offset = 0x20;
            i = 3;
            mesh_scale = *(float *)(screen + 0x2C) / *(float *)(*(int *)(screen + 0x24) + 0x24);
            for (; i >= 0; i--) {
                matrix_mul_vec3((char *)(g_trail_slice_state.mesh + offset), source, basis);
                FastVecScale((char *)(g_trail_slice_state.mesh + offset),
                              (char *)(g_trail_slice_state.mesh + offset), mesh_scale);
                FastVecAdd((char *)(g_trail_slice_state.mesh + offset),
                              (char *)(g_trail_slice_state.mesh + offset), position);
                offset += 0x10;
                source += 0x10;
            }
            *(int *)(g_trail_slice_state.mesh + 0x68) = g_trail_slice_state.entries[index];
        }
    }
    if (g_trail_slice_state.mode == 0 && g_trail_slice_state.count >= 0x79F)
        g_trail_slice_state.mesh = 0;
    if (g_trail_slice_state.mode == 1 && g_trail_slice_state.count < 0x32)
        g_trail_slice_state.mesh = 0;
}

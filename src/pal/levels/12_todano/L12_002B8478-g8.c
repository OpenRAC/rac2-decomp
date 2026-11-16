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
    void *obj;
    float scale;
    char *q;
    int i;
    int off;

    if (g_current_map_index != 12)
        return;

    obj = 0;
    index = -1;
    if (g_trail_slice_state.mode < 2) {
        obj = tv_screen_find_nearest(0.0f, 0.0f, 0.0f);
        index = 2;
    }
    if (index != -1 && obj != 0) {
        if (g_trail_slice_state.entries[index] != 0) {
            char *d = obj + 0x10;
            char *c = obj + 0xC0;
            g_trail_slice_state.mesh = (int)g_trail_slice_mesh;
            q = (char *)&g_trail_slice_source;
            off = 0x20;
            i = 3;
            scale = *(float *)(obj + 0x2C) / *(float *)(*(int *)(obj + 0x24) + 0x24);
            for (; i >= 0; i--) {
                matrix_mul_vec3((char *)(g_trail_slice_state.mesh + off), q, c);
                FastVecScale((char *)(g_trail_slice_state.mesh + off),
                              (char *)(g_trail_slice_state.mesh + off), scale);
                FastVecAdd((char *)(g_trail_slice_state.mesh + off),
                              (char *)(g_trail_slice_state.mesh + off), d);
                off += 0x10;
                q += 0x10;
            }
            *(int *)(g_trail_slice_state.mesh + 0x68) = g_trail_slice_state.entries[index];
        }
    }
    if (g_trail_slice_state.mode == 0 && g_trail_slice_state.count >= 0x79F)
        g_trail_slice_state.mesh = 0;
    if (g_trail_slice_state.mode == 1 && g_trail_slice_state.count < 0x32)
        g_trail_slice_state.mesh = 0;
}

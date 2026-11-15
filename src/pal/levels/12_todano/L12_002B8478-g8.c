#include "include_asm.h"
#include "names.h"
extern int g_current_map_index;
extern void *tv_screen_find_nearest(float, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char D_L12_0027F710[];
extern int D_L12_001A9410 __attribute__((sda));
typedef struct {
    char pad0[0x30];
    unsigned int mode;
    int count;
    char pad1[0x18];
    int mesh;
    char pad2[0x138];
    int *entries[4];
} L12_002FFF88_STATE;
extern L12_002FFF88_STATE D_L12_001BDB00;

/* Builds the level's four trail slices for the mesh its state points at. */
void func_PAL_L12_00301950(void)
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
    if (D_L12_001BDB00.mode < 2) {
        obj = tv_screen_find_nearest(0.0f, 0.0f, 0.0f);
        index = 2;
    }
    if (index != -1 && obj != 0) {
        if (D_L12_001BDB00.entries[index] != 0) {
            char *d = obj + 0x10;
            char *c = obj + 0xC0;
            D_L12_001BDB00.mesh = (int)D_L12_0027F710;
            q = (char *)&D_L12_001A9410;
            off = 0x20;
            i = 3;
            scale = *(float *)(obj + 0x2C) / *(float *)(*(int *)(obj + 0x24) + 0x24);
            for (; i >= 0; i--) {
                matrix_mul_vec3((char *)(D_L12_001BDB00.mesh + off), q, c);
                FastVecScale((char *)(D_L12_001BDB00.mesh + off),
                              (char *)(D_L12_001BDB00.mesh + off), scale);
                FastVecAdd((char *)(D_L12_001BDB00.mesh + off),
                              (char *)(D_L12_001BDB00.mesh + off), d);
                off += 0x10;
                q += 0x10;
            }
            *(int *)(D_L12_001BDB00.mesh + 0x68) = D_L12_001BDB00.entries[index];
        }
    }
    if (D_L12_001BDB00.mode == 0 && D_L12_001BDB00.count >= 0x79F)
        D_L12_001BDB00.mesh = 0;
    if (D_L12_001BDB00.mode == 1 && D_L12_001BDB00.count < 0x32)
        D_L12_001BDB00.mesh = 0;
}

#include "include_asm.h"
#include "names.h"

extern int D_L01_001B2088 __attribute__((sda));

extern int D_L01_001AEC38 __attribute__((sda));

extern unsigned char D_L01_001A7A6F;

extern int D_L01_001A907C;

extern void func_3558E0(int, int, int);

extern void func_31BEC0(int, int);

/* Fires the Oozla intro once the level's mode and counter allow it. */

extern int D_L01_001A79F0;

extern void *tv_screen_find_nearest(float, float, float);

extern void matrix_mul_vec3(void *, void *, void *);

extern void FastVecScale(void *, void *, float);

extern void FastVecAdd(void *, void *, void *);

extern char D_L01_0027F810[];

extern int D_001A9420 __attribute__((sda));

typedef struct {
    char pad0[0x30];
    int mode;
    int count;
    char pad1[0x18];
    int mesh;
    char pad2[0x138];
    int *entries[4];
} L01_002F2098_STATE;

extern L01_002F2098_STATE D_L01_001BD1C0;

/* Builds the ship's four trail slices for the level's current colour. */
void ship_build_trail_slices(void)
{
    int index;
    void *obj;
    float scale;
    char *p;
    char *q;
    int i;

    if (D_L01_001A79F0 != 1)
        return;

    index = -1;
    obj = tv_screen_find_nearest(0.0f, 0.0f, 0.0f);
    if (D_L01_001BD1C0.mode == 3)
        index = 1;
    if (index != -1 && obj != 0) {
        if (D_L01_001BD1C0.entries[index] != 0) {
            char *d = obj + 0x10;
            char *c = obj + 0xC0;
            D_L01_001BD1C0.mesh = (int)D_L01_0027F810;
            p = (char *)D_L01_0027F810 + 0x20;
            q = (char *)&D_001A9420;
            i = 3;
            scale = *(float *)(obj + 0x2C) / *(float *)(*(int *)(obj + 0x24) + 0x24);
            for (; i >= 0; i--) {
                matrix_mul_vec3(p, q, c);
                FastVecScale(p, p, scale);
                FastVecAdd(p, p, d);
                p += 0x10;
                q += 0x10;
            }
            *(int *)(D_L01_001BD1C0.mesh + 0x68) = D_L01_001BD1C0.entries[index];
        }
    }
    if (D_L01_001BD1C0.count >= 0x5D7)
        D_L01_001BD1C0.mesh = 0;
}

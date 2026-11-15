#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad0[0x30];
    int state;
    int timer;
    char pad38[12];
    short count;
    char pad46[10];
    char *out;
    char pad54[0x138];
    char *objects[1];
} Context;
extern int g_current_map_index[] __attribute__((sda));
extern char D_L00_001A93E0[64] SDATA(D_L00_001A93E0);
extern char g_camera_l00_position[];
extern Context D_L00_001BCAC0;
extern char D_L00_0027E600[];
extern char D_L00_0027E620[];
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);

/* While the timer is in its window, builds four points around the 0xD54 moby and selects an object. */
void func_PAL_L00_002FE328(void) {
    char temp[16];
    int low;
    int high;
    int which;
    int i;
    int n;
    char *found;
    char *out;

    if (g_current_map_index[0] != 0)
        return;

    low = -1;
    high = 9999;
    which = 0;
    if (D_L00_001BCAC0.state == 0) {
        low = 183;
        high = 308;
        which = 1;
    }
    if (low == -1)
        return;

    if (D_L00_001BCAC0.timer >= low && D_L00_001BCAC0.timer <= high) {
        D_L00_001BCAC0.out = D_L00_0027E600;

        found = 0;
        for (i = 0; i < D_L00_001BCAC0.count; i++) {
            char *obj = D_L00_001BCAC0.objects[i];

            if (*(short *)(obj + 0xAA) == 0xD54) {
                found = obj;
                break;
            }
        }

        if (found) {
            char *matrix;

            out = D_L00_0027E620;
            matrix = found + 0xC0;
            for (n = 0; n < 4; n++) {
                matrix_mul_vec3(out, D_L00_001A93E0 + n * 16, matrix);
                FastVecAdd(out, out, found + 0x10);
                FastVecSub(temp, g_camera_l00_position, out);
                vec_scale_to_length(temp, temp, 0.15f);
                FastVecAdd(out, out, temp);
                out += 16;
            }
        }
        *(char **)(D_L00_001BCAC0.out + 0x68) = D_L00_001BCAC0.objects[which];
    } else {
        D_L00_001BCAC0.out = 0;
    }
}

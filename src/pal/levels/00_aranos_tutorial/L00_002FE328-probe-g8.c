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
extern int D_001A79F0[] __attribute__((sda));
extern char D_L00_001A93E0[64] SDATA(D_L00_001A93E0);
extern char D_L00_001B8DC0[];
extern Context D_L00_001BCAC0;
extern char D_L00_0027E600[];
extern char D_L00_0027E620[];
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00283098(void *, void *, void *);

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

    if (D_001A79F0[0] != 0)
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
                func_00283098(out, D_L00_001A93E0 + n * 16, matrix);
                func_00282CC0(out, out, found + 0x10);
                func_00282CF0(temp, D_L00_001B8DC0, out);
                func_00282F20(temp, temp, 0.15f);
                func_00282CC0(out, out, temp);
                out += 16;
            }
        }
        *(char **)(D_L00_001BCAC0.out + 0x68) = D_L00_001BCAC0.objects[which];
    } else {
        D_L00_001BCAC0.out = 0;
    }
}

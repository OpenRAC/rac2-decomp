#include "include_asm.h"
#include "names.h"

extern void *part_find_owned_effect_slot(char *a0, int a1, int a2);
typedef int TI128 __attribute__((mode(TI)));
extern char D_L14_001B1870[8] __attribute__((sda));
extern char D_L14_001B1878[8] __attribute__((sda));
extern int D_L14_001B18A0 __attribute__((sda));
extern void moby_set_state(char *a0, int a1, int a2);
extern void vec_scale_to_length(void *out, void *in, float scale);
extern void FastVecSub(void *out, void *in1, void *in2);
extern void FastVecAdd(void *out, void *in1, void *in2);
extern void func_PAL_L00_0032C328(char *, void *, void *, void *, int, int, int, int, int, int, int);
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(char *a0);

void func_PAL_L14_0042CB20(char *a0) {
    float pts[2][4] __attribute__((aligned(16)));
    char *state = *(char **)(a0 + 0x68);
    char *obj;

    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        moby_set_state(a0, 1, -1);
        break;
    case 1:
        obj = (char *)part_find_owned_effect_slot(a0, 0x4010000, 0);
        if (obj != 0 && *(int *)state == 0) {
            float off[4] __attribute__((aligned(16)));
            *(TI128 *)off = 0;
            off[0] = 3.0f;
            off[1] = 3.0f;
            vec_scale_to_length(pts[0], obj + 0x10, 8.0f);
            vec_scale_to_length(pts[1], obj + 0x10, 18.0f);
            FastVecSub(pts[0], pts[0], off);
            FastVecAdd(pts[1], pts[1], off);
            func_PAL_L00_0032C328(a0, pts, D_L14_001B1878, D_L14_001B1870, 0xFFFF, 0, D_L14_001B18A0, 8, 0xFFFF, 0xFF, 0);
            PlayMobySound(0, 0, a0);
            moby_set_state(a0, 2, -1);
        }
        *(unsigned char *)(a0 + 0xA8) = 0xFF;
        break;
    case 2:
        moby_mark_spawned(a0);
        break;
    }
}

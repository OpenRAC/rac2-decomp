#include "include_asm.h"

#include "common.h"
extern float D_L17_001B0328 __attribute__((sda));
extern int D_L17_001C0018 NOT_SDA;
extern unsigned char D_L17_001DBF81[];
extern char *D_L17_001DAD00[];
extern float coll_probe_ground_height_below(void *, int, float);
extern void anim_start_immediate(void *, int, int);
extern int math_fast_float_d(void *);
extern void moby_mark_spawned(void *);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
typedef unsigned int StateQuad __attribute__((mode(TI)));

void func_PAL_L17_003C9D00(char *self) {
    union { StateQuad q; float f[4]; } oldpos, delta;
    char *data = *(char **)(self + 0x68);
    float ground;
    unsigned char index;
    oldpos.q = *(StateQuad *)(self + 0x10);
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        if (*(int *)(data + 0x90) != -1) {
            ground = coll_probe_ground_height_below(self + 0x10, 0, 0.5f);
            *(int *)(data + 0x9C) = D_L17_001C0018;
            if (ground < *(float *)(self + 0x18)) {
                *(float *)(data + 0x98) += D_L17_001B0328 * 0.00040000002f;
                *(float *)(self + 0x18) -= *(float *)(data + 0x98);
            } else {
                *(int *)(data + 0x98) = 0;
                *(float *)(self + 0x18) = ground;
            }
        }
        break;
    case 1:
        if (*(unsigned char *)(self + 0x42) == 1 && (*(unsigned char *)(self + 0x60) & 2)) {
            *(short *)(self + 0xAA) = 0x921;
            index = D_L17_001DBF81[0];
            *(unsigned char *)(self + 0x22) = index;
            *(char **)(self + 0x24) = D_L17_001DAD00[*(unsigned char *)(self + 0x22)];
            *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
            anim_start_immediate(self, 0, 0);
            *(unsigned char *)(self + 0x20) = 2;
            if (*(int *)(data + 0x90) != -1) *(int *)(data + 0x94) = 500;
        }
        break;
    case 2:
        if (*(int *)(data + 0x90) != -1 && math_fast_float_d(data + 0x94)) {
            moby_mark_spawned(self);
            return;
        }
        break;
    }
    FastVecSub(&delta, self + 0x10, &oldpos);
    mat_combine_and_store(data + 0x50, &delta, self + 0xF0, self + 0xF0);
}

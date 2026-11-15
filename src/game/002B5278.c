#include "include_asm.h"
#include "common.h"

/* Measured partial C views; original types and object ownership are unknown. */
typedef unsigned char QwenRecovery_84e23fd54f9f_AbiByte16;

extern int func_002B50E0(QwenRecovery_84e23fd54f9f_AbiByte16 *owner, QwenRecovery_84e23fd54f9f_AbiByte16 *input, float factor);

void func_002B5278(QwenRecovery_84e23fd54f9f_AbiByte16 *param_1, float factor)
{
    func_002B50E0(param_1, param_1 + 0x10, factor);
}


/* func_002B52A0 is defined in 002B52A0-g8.c. */

/* func_002B5678 is defined in 002B5678-copy.c. */

/* func_002B5828 is matched in 002B5828.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

typedef int TI128_002B5BC0 __attribute__((mode(TI)));
typedef union { TI128_002B5BC0 q; float f[4]; } Vec4Q_002B5BC0;

extern char D_001BAF80[];
extern int func_002761F8(void *, void *, int, void *, const void *);
extern int func_00278E78(void);
extern void func_00282F20(char *, char *, float);
extern void func_00282C88(void *);

void func_002B5BC0(char *obj, char *moby, float factor)
{
    Vec4Q_002B5BC0 v, t;
    char *data;
    int hit;

    qcopy(&v, obj + 0x10);
    v.f[2] = v.f[2] + (*(float *)(moby + 8) + 0.1f);
    if (factor != 0.0f) {
        qcopy(&t, obj + 0x10);
        t.f[2] = t.f[2] - factor;
    } else {
        qcopy(&t, obj + 0x10);
        t.f[2] = t.f[2] - (*(float *)(moby + 0xC) + 0.1f);
    }
    hit = CollLine(&v, &t, 0, obj, 0);
    if (hit) {
        data = D_001BAF80;
        *(float *)(moby + 0x90) = *(float *)(data + 0x28);
        *(void **)(moby + 0x88) = *(void **)(data + 0x18);
        *(void **)(moby + 0x8C) = *(void **)(data + 0x1C);
        *(int *)(moby + 0xD8) = GetCollHitMaterial();
        vec_scale_to_length(moby + 0x50, data + 0x40, 1.0f);
    } else {
        *(float *)(moby + 0x90) = 0.0f;
        *(void **)(moby + 0x88) = 0;
        *(void **)(moby + 0x8C) = 0;
        *(int *)(moby + 0xD8) = -1;
        func_00282C88(moby + 0x50);
    }
}

extern int func_002AD0E0(void *, void *, void *, void *, void *, void *);

void func_002B5CD8(char *first, char *second) {
    void *target = *(void **)(second + 0x88);
    if (target != 0 && func_002AD0E0(first, target, first + 0x10, first + 0xF0, first + 0x10, first + 0xF0) != 0)
        *(unsigned int *)(second + 0x94) |= 0x40;
}

void *func_002B5D28(u8 *a0) { return *(void **)(*(u8 **)(a0 + 0x68) + 0x18); }


/* func_002B5E48 is matched in 002B5E48.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_002B5EF8 is matched in 002B5EF8.c (built with -g). */


/* func_002B60B0 is matched in 002B60B0.c. */


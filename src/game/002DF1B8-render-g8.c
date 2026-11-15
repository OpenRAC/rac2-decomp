#include "common.h"

typedef struct {
    int count, flags;
    float depth, radius;
    float xyz[4];
    float params[4];
} RenderDFBB0;

/* Header offsets use the shared byte packet cursor. */
extern unsigned char *D_001B22A8 MACRO_ADDR;
extern char D_001390B0[];
extern void *D_001B2080;
extern int D_001A72DC[] __attribute__((sda));
extern void func_002DF838(void);
extern void func_002DF640(float *, float);
extern RenderDFBB0 *func_002DF750(RenderDFBB0 *);
extern void func_002E0BA8(float *, float *);
extern void func_002E0088(int, void *, int);
extern void func_002DF7A8(int, int, int);
extern void func_002FC560(int, long);
extern void func_002DF9E0(long);

void func_002DFBB0(RenderDFBB0 *data) {
    RenderDFBB0 *next = data;
    RenderDFBB0 *current;
    int i;
    float a[4], b[4];
    func_002DF838();
    current = next;
    *(int *)D_001B22A8 = 0x30000007;
    *(int *)(D_001B22A8 + 4) = (int)D_001390B0;
    *(int *)(D_001B22A8 + 8) = 0x13000000;
    *(int *)(D_001B22A8 + 12) = 0x50000007;
    D_001B22A8 = D_001B22A8 + 16;
    while (current->count) {
        next = next + 1;
        func_002DF640(current->params, 1000.0f);
        b[0] = a[0] = current->xyz[0];
        b[1] = a[1] = current->xyz[1];
        b[2] = a[2] = current->xyz[2];
        a[3] = -current->depth - current->radius;
        {
            float depth = current->depth;
            b[3] = current->radius - depth;
        }
        for (i = 0; i < current->count; i++) {
            next = func_002DF750(next);
            func_002E0BA8(a, b);
            func_002E0088(0x70000000, D_001B2080, current->flags);
            func_002DF7A8(2, 1, 2);
            func_002DF7A8(1, 0, 2);
        }
        current = next;
    }
    VU1_addGSregister(0x4C, (D_001A72DC[0] >> 13) | 0x80000);
    VU1_addGSregister(0x42, 0x2000000064L);
    func_002DF9E0(0);
    VU1_addGSregister(0x47, 0x5360B);
    VU1_addGSregister(0x42, 0x8000000044L);
}

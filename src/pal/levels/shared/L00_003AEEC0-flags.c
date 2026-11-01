#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[4];
    unsigned char flag;
    unsigned char pad1[0x74 - 5];
    float scale;
    unsigned char pad2[0xE0 - 0x78];
} Entry262570b;
extern void func_00282D30(void *, void *, float);
extern int func_00277F48(float, int, int, int, int);
extern void func_PAL_0032F0B8(int, int, int);
extern void func_002A9850(void *, void *, int *, int, int, int, int, int, float, float, float);
extern unsigned char D_00139568[];
extern Entry262570b D_L00_00262570[];
extern int D_L00_001C3280[];
typedef struct {
    float head[4];
    float vec[4];
    int arg;
} Trail_3AC8E8;

void func_PAL_L00_003B00B8(char *a0, void *a1, int a2)
{
    Trail_3AC8E8 s;
    Entry262570b *e;
    float scale;
    int count;
    int i;

    s.arg = a2;
    func_00282D30(s.head, a1, -3.0f);
    e = &D_L00_00262570[D_00139568[0x1B]];
    scale = e->scale;
    count = func_00277F48(e->flag != 0 ? 3.0f : 4.0f, (int)(a0 + 0x10), 0x10, (int)a0, 0);
    for (i = 0; i < count; i++) {
        if ((D_L00_00262570 + D_00139568[0x1B])->flag != 0)
            func_PAL_0032F0B8(D_L00_001C3280[i], 0x45, *(int *)(a0 + 0xB8));
        else
            func_PAL_0032F0B8(D_L00_001C3280[i], 0x1B, *(int *)(a0 + 0xB8));
    }
    *(TI128 *)s.vec = *(TI128 *)(a0 + 0x10);
    func_002A9850(a0, s.vec, D_L00_001C3280, count, s.arg, 0x810000, 3, 1, scale, 1.0f, 1.0f);
}

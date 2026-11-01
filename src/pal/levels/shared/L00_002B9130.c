#include "include_asm.h"

#include "common.h"
typedef int TI_F41eb487e __attribute__((mode(TI)));
extern void func_002830C0(void *a, void *b, void *c);
extern void func_00282D30(void *a, void *b, float value);
extern void func_L00_002B8F00(void *a, void *b, int c, float p, float q, float r);
extern void func_00282CF0(void *a, void *b, void *c);
extern void func_00282CC0(void *a, void *b, void *c);
typedef struct {
    int a;
    int b;
    float c;
    float d;
} Vec4_F41eb487e;
typedef struct {
    u8 pad000[0x80];
    u8 area080[0x218 - 0x80];
    short h218;
    u8 pad21a[0x2a0 - 0x21a];
    TI_F41eb487e q2A0;
    u8 pad2b0[0x2c0 - 0x2b0];
    u8 area2C0[0x31c - 0x2c0];
    float f31C;
    u8 pad320[0x34e - 0x320];
    short h34E;
    u8 pad350[0x22c3 - 0x350];
    u8 b22C3;
} ResidentState_F41eb487e;
extern ResidentState_F41eb487e D_00189E20_5;

/* initialises three 16-byte records, folds a resident 32-byte quad into the first of them, then for the stored mode 2 runs a four-argument fallback and for mode 1 with a short or low field re-copies the resident quad; finally scales and copies the two remaining records through three more calls */
void func_PAL_L00_002B9130(void)
{
    u8 scratch[64];
    Vec4_F41eb487e A, B, C;
    float hi = 0.050400004f;
    float lo = 0.43200004f;

    *(TI_F41eb487e *)&A = 0;
    *(TI_F41eb487e *)&B = 0;
    *(TI_F41eb487e *)&C = 0;

    A.c = 1.0f;
    B.c = 0.8f;
    C.c = 0.8f;

    func_002830C0(&B, &B, &D_00189E20_5);

    *(TI_F41eb487e *)&A = *(TI_F41eb487e *)&D_00189E20_5.q2A0;
    if (D_00189E20_5.b22C3 == 2) {
        func_00282D30(&A, &D_00189E20_5.area2C0, -1.0f);
    }

    if (D_00189E20_5.b22C3 == 1 && (D_00189E20_5.h34E < 8 || D_00189E20_5.f31C < 1.0f))
        *(TI_F41eb487e *)&A = *(TI_F41eb487e *)&D_00189E20_5.q2A0;

    if (D_00189E20_5.h34E != 0 && D_00189E20_5.h218 != 0) {
        lo = 0.0014400001f;
        hi = lo;
    }

    func_L00_002B8F00(&A, scratch, 0, hi, lo, 0.0f);

    if (D_00189E20_5.b22C3 == 1 && D_00189E20_5.h34E != 0) {
        func_002830C0(&C, &C, scratch);
        func_00282CF0(&D_00189E20_5.area080, &D_00189E20_5.area080, &C);
        func_00282CC0(&D_00189E20_5.area080, &D_00189E20_5.area080, &B);
    }
}



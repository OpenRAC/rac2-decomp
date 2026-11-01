#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    float v[4][4];           
    s32 c[4];                
    float uv[4][2];          
    u64 w[4];                
} Quad;
typedef struct { s16 a; s16 b; } Pair;
typedef struct { float angle; s32 fix; } Vars;
extern u8 *D_L23_001B1484 MACRO_ADDR;
extern s32 D_L23_001B1480 MACRO_ADDR;
extern float D_L23_001B1470 MACRO_ADDR;
extern s32 D_L23_001B1474 MACRO_ADDR;
extern float D_L23_001B1478 MACRO_ADDR;
extern s32 D_L23_001B147C MACRO_ADDR;
extern float D_L23_001B39D8 MACRO_ADDR;
extern s32 D_L23_001B1C68 __attribute__((sda));
extern s32 D_L23_001B1C6C __attribute__((sda));
extern s32 D_L23_001B1C70 __attribute__((sda));
extern s32 D_L23_001B1C74 __attribute__((sda));
extern s32 D_L23_001B1C7C __attribute__((sda));
extern s32 D_L23_001B1C80 __attribute__((sda));
extern float D_L23_001B1C84 __attribute__((sda));
extern float D_L23_002A7F50[][4];
extern float D_L23_002A8460[][2];
extern Pair D_L23_002A81E0[][4];
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern u64 func_0027C878(s32);
extern void func_002FC560(u16, u64);
extern void func_L22_002F3B38(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00282D30(float, void *, void *);
extern void func_00280B90(void *, void *, s32);

void func_PAL_L23_004302F8(u8 *obj) {
    Quad q;
    float m[12];
    float v3[4];
    float v5[4];
    float v4[4];
    float x[12];
    u64 alpha;
    float wave;
    s32 fix;
    s32 base;
    Vars *payload;
    s32 n;
    s32 i;
    s32 j;
    s32 uv;

    if (D_L23_001B1484 != 0) {
        payload = *(Vars **)(obj + 0x68);
        D_L23_001B39D8 = D_L23_001B1470 * 1.1f;
        payload->angle = func_00283B98(payload->angle, (float)D_L23_001B1480 * 0.0003490659f);
        n = D_L23_001B1474;
        wave = func_00283198((float)(s32)(*(u16 *)(obj + 0x96) % n) * (1.0f / (float)n) * 3.1415927f);
        fix = D_L23_001B147C;
        base = fix;
        fix = (s32)(wave * D_L23_001B1478) + base;
        payload->fix = fix;
        alpha = (u64)D_L23_001B1C68 | ((u64)D_L23_001B1C6C << 2);
        alpha |= (u64)D_L23_001B1C70 << 4;
        alpha |= (u64)D_L23_001B1C74 << 6;
        q.w[3] = alpha | ((u64)payload->fix << 32);
        q.w[1] = func_0027C878(D_L23_001B1C7C);
        q.w[2] = 0xFF9000000260ULL;
        q.w[0] = 0;
        func_002FC560(0x47, 0x53001);
        qcopy(m, obj + 0xC0);
        qcopy(m + 4, obj + 0xD0);
        qcopy(m + 8, obj + 0xE0);
        qcopy_nc(m, D_L23_001B1484 + 0xC0);
        qcopy_nc(m + 4, D_L23_001B1484 + 0xD0);
        qcopy_nc(m + 8, D_L23_001B1484 + 0xE0);
        qcopy_nc(v3, D_L23_001B1484 + 0x10);
        *(TI128 *)v4 = 0;
        v4[3] = 1.0f;
        v4[2] = D_L23_001B1C84;
        *(TI128 *)v5 = *(TI128 *)v4;
        func_L22_002F3B38(v5, v5, D_L23_001B1484 + 0xE0);
        func_00282CC0(v3, D_L23_001B1484 + 0x10, v5);
        qzero_nc(v4);
        v4[2] = payload->angle;
        func_002833F0(x, v4);
        func_00283738(m, m, x);
        v3[3] = 1.0f;
        q.c[3] = D_L23_001B1C80;
        q.c[2] = D_L23_001B1C80;
        q.c[1] = D_L23_001B1C80;
        q.c[0] = D_L23_001B1C80;
        for (i = 0; i < 40; i++) {
            for (j = 0; j < 4; j++) {
                uv = D_L23_002A81E0[i][j].b;
                func_00282D30(D_L23_001B39D8, &q.v[j], D_L23_002A7F50[D_L23_002A81E0[i][j].a]);
                q.uv[j][0] = D_L23_002A8460[uv][0];
                q.uv[j][1] = D_L23_002A8460[uv][1];
            }
            func_00280B90(&q, m, 0);
        }
    }
}

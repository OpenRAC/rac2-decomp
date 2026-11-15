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
extern u8 *g_mothership_boss_moby MACRO_ADDR;
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
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern u64 GetEffectTextureDescriptor(s32);
extern void VU1_addGSregister(u16, u64);
extern void func_L22_002F3B38(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void FastVecScale(float, void *, void *);
extern void draw_world_quad(void *, void *, s32);

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

    if (g_mothership_boss_moby != 0) {
        payload = *(Vars **)(obj + 0x68);
        D_L23_001B39D8 = D_L23_001B1470 * 1.1f;
        payload->angle = FastAddRotations(payload->angle, (float)D_L23_001B1480 * 0.0003490659f);
        n = D_L23_001B1474;
        wave = math_fast_sin_or_cos_b((float)(s32)(*(u16 *)(obj + 0x96) % n) * (1.0f / (float)n) * 3.1415927f);
        fix = D_L23_001B147C;
        base = fix;
        fix = (s32)(wave * D_L23_001B1478) + base;
        payload->fix = fix;
        alpha = (u64)D_L23_001B1C68 | ((u64)D_L23_001B1C6C << 2);
        alpha |= (u64)D_L23_001B1C70 << 4;
        alpha |= (u64)D_L23_001B1C74 << 6;
        q.w[3] = alpha | ((u64)payload->fix << 32);
        q.w[1] = GetEffectTextureDescriptor(D_L23_001B1C7C);
        q.w[2] = 0xFF9000000260ULL;
        q.w[0] = 0;
        VU1_addGSregister(0x47, 0x53001);
        qcopy(m, obj + 0xC0);
        qcopy(m + 4, obj + 0xD0);
        qcopy(m + 8, obj + 0xE0);
        qcopy_nc(m, g_mothership_boss_moby + 0xC0);
        qcopy_nc(m + 4, g_mothership_boss_moby + 0xD0);
        qcopy_nc(m + 8, g_mothership_boss_moby + 0xE0);
        qcopy_nc(v3, g_mothership_boss_moby + 0x10);
        *(TI128 *)v4 = 0;
        v4[3] = 1.0f;
        v4[2] = D_L23_001B1C84;
        *(TI128 *)v5 = *(TI128 *)v4;
        func_L22_002F3B38(v5, v5, g_mothership_boss_moby + 0xE0);
        FastVecAdd(v3, g_mothership_boss_moby + 0x10, v5);
        qzero_nc(v4);
        v4[2] = payload->angle;
        euler_rotation_basis(x, v4);
        multiply_matrix3x3(m, m, x);
        v3[3] = 1.0f;
        q.c[3] = D_L23_001B1C80;
        q.c[2] = D_L23_001B1C80;
        q.c[1] = D_L23_001B1C80;
        q.c[0] = D_L23_001B1C80;
        for (i = 0; i < 40; i++) {
            for (j = 0; j < 4; j++) {
                uv = D_L23_002A81E0[i][j].b;
                FastVecScale(D_L23_001B39D8, &q.v[j], D_L23_002A7F50[D_L23_002A81E0[i][j].a]);
                q.uv[j][0] = D_L23_002A8460[uv][0];
                q.uv[j][1] = D_L23_002A8460[uv][1];
            }
            draw_world_quad(&q, m, 0);
        }
    }
}

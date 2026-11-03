#include "common.h"

/* func_L23_0042A438 is a unit of its own: it reads its globals through $gp (-G8) and needs the
 * qcopy/qzero macros (see config/cflags.txt). */

typedef int TI16 __attribute__((mode(TI)));

/* the state object word, read through an absolute access */
extern u8 *D_L23_001B1484_2;

extern float D_L23_001B1470;

extern s32 D_L23_001B1474;

extern float D_L23_001B39D0 __attribute__((sda));

extern float D_L23_001B3930;

extern s16 D_L23_001B1B94 __attribute__((sda));

extern s32 D_L23_001B1BAC __attribute__((sda));

extern s32 D_L23_001B1BB0 __attribute__((sda));

extern s32 D_L23_001B1BB4 __attribute__((sda));

extern s32 D_L23_001B1BB8 __attribute__((sda));

extern s32 D_L23_001B1BC4 __attribute__((sda));

extern s32 D_L23_001B1BC8 __attribute__((sda));

extern float D_L23_001B1C00 __attribute__((sda));

extern float D_L23_001B1C04 __attribute__((sda));

extern float D_L23_001B1C0C __attribute__((sda));

extern float D_L23_001B1C10 __attribute__((sda));

extern s32 D_L23_001B1C14 __attribute__((sda));

extern float D_L23_001B1C18 __attribute__((sda));

extern float D_L23_001B1C1C __attribute__((sda));

extern float D_L23_001B1C20 __attribute__((sda));

extern s32 D_L23_001B1C24 __attribute__((sda));

extern float D_L23_001B1C28 __attribute__((sda));

extern float D_L23_001B1C2C __attribute__((sda));

extern float D_L23_001B1C30 __attribute__((sda));

/* the quad record handed to the draw helper */
typedef struct {
    TI16 pos[4];
    u32 col[4];
    float uv[4][2];
    s64 tail[4];
} L23Quad;

/* the spin state at object + 0x68 */
typedef struct {
    float turn;
    s32 alpha;
} L23Spin3;

/* the object this update runs on */
typedef struct {
    u8 pad0[0x68];
    L23Spin3 *vars;
} L23Obj;

extern s32 D_L23_0025E8B0[];

extern TI16 D_L23_002A75F0[];

extern TI16 D_L23_002A7170[];

extern TI16 D_L23_001BA640[];

extern void func_00291450(s32);

extern void func_00282D30(void *, void *, float);

extern void func_00282CC0(void *, void *, void *);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282DD8(void *, void *, void *);

extern void func_00282F20(void *, void *, float);

extern float func_00282DF0(void *);

extern float func_002A7878(float, float);

extern s32 func_L00_002FCF18(void *, float, float, float, float, float);

extern long long func_0027C878(s32);

extern void func_002FC560(u32, u64);

extern void func_L03_002EFB60(void *, void *, float);

extern void func_002833F0(void *, void *);

extern void func_00283738(void *, void *, void *);

extern void func_002830C0(void *, void *, void *);

extern void func_00283098(void *, void *, void *);

extern void func_00280B90(void *, void *, s32);

/* releases the held handle, spawns a new one from jittered values, updates the globals, then
   draws one quad for every live entry of the 72-entry table, tilted by the spin state */
void func_L23_0042A438(u8 *moby) {
    L23Spin3 *vars;
    L23Quad pkt;
    struct { TI16 rows[4]; } matrix;
    TI16 *mp;
    float *basis;
    TI16 w[1];
    TI16 axis[1];
    TI16 rot[3];
    TI16 v120[1];
    TI16 v130[1];
    TI16 v140[1];
    TI16 v150[1];
    TI16 v160[1];
    float fa;
    float fb;
    float fc;
    float f;
    float t;
    float alphaScale;
    float scaledLength;
    float ribbonWidth;
    s32 i;
    u8 *hero;
    s64 reg;
    s64 tex;

    if (D_L23_001B1484_2 != 0) {
        if (D_L23_001B1B94 != -1) {
            func_00291450(D_L23_001B1B94);
        }
        func_00282D30(w, D_L23_001B1484_2 + 0xE0, 10.0f);
        func_00282CC0(w, w, D_L23_001B1484_2 + 0x10);
        f = func_002A7878(0.0f, D_L23_001B1C28);
        fa = D_L23_001B1C28 + f;
        f = func_002A7878(0.0f, D_L23_001B1C2C);
        fb = D_L23_001B1C2C + f;
        f = func_002A7878(0.0f, D_L23_001B1C30 * 0.5f);
        fc = D_L23_001B1C30 + f;
        D_L23_001B1B94 = func_L00_002FCF18(w, 20.0f, 0.0f, fa, fb, fc);
        D_L23_001B1C00 = D_L23_001B1C00 - D_L23_001B1C04;
        D_L23_001B39D0 = D_L23_001B1470 * 0.94f;
        vars = ((L23Obj *)moby)->vars;
        if (D_L23_001B1C00 <= -6.0f) {
            D_L23_001B1C00 = D_L23_001B1C00 + 6.0f;
        }
        i = *(u16 *)(moby + 0x96) % (D_L23_001B1474 >> 2);
        vars->alpha = D_L23_001B1C24;
        reg = D_L23_001B1BAC | ((s64)D_L23_001B1BB0 << 2);
        reg |= (s64)D_L23_001B1BB4 << 4;
        reg |= (s64)D_L23_001B1BB8 << 6;
        reg |= (s64)vars->alpha << 32;
        pkt.tail[3] = reg;
        D_L23_001B1C18 = (float)vars->alpha * D_L23_001B1C1C;
        tex = func_0027C878(D_L23_001B1C14);
        pkt.tail[2] = 0xFF9000000260LL;
        pkt.tail[1] = tex;
        pkt.tail[0] = 0;
        func_002FC560(0x47, 0x53001);
        hero = D_L23_001B1484_2;
        qcopy_nc(&matrix.rows[0], hero + 0xC0);
        qcopy_nc(&matrix.rows[1], hero + 0xD0);
        qcopy_nc(&matrix.rows[2], hero + 0xE0);
        qzero_nc(&matrix.rows[3]);
        mp = matrix.rows;
        func_L03_002EFB60(mp, mp, D_L23_001B1C0C);
        qcopy(&matrix.rows[3], D_L23_001B1484_2 + 0x10);
        ((float *)&matrix.rows[3])[3] = 1.0f;
        basis = (float *)mp;
        qzero_nc(axis);
        ((float *)axis)[2] = vars->turn;
        func_002833F0(rot, axis);
        func_00283738(basis, basis, rot);
        pkt.col[0] = pkt.col[1] = D_L23_001B1BC4;
        pkt.col[2] = pkt.col[3] = D_L23_001B1BC8;
        for (i = 0; i < 0x48; i++) {
            if (D_L23_0025E8B0[i] != 0) {
                alphaScale = D_L23_001B1C18;
                func_002830C0(v120, &D_L23_002A75F0[i], &matrix);
                func_00283098(v140, &D_L23_002A7170[i], mp);
                func_00282CF0(v150, v120, D_L23_001BA640);
                func_00282DD8(v160, v140, v150);
                func_00282F20(v160, v160, alphaScale);
                f = func_00282DF0(v150);
                scaledLength = f * D_L23_001B1C10;
                t = D_L23_001B3930;
                ribbonWidth = scaledLength * t;
                D_L23_001B3930 = t + D_L23_001B1C20;
                if (D_L23_001B3930 > 1.0f) {
                    D_L23_001B3930 = 1.0f;
                }
                func_00282D30(v130, v140, ribbonWidth);
                func_00282CC0(v130, v130, v120);
                func_00282CC0(&pkt.pos[0], v120, v160);
                func_00282CF0(&pkt.pos[1], v120, v160);
                func_00282CC0(&pkt.pos[2], v130, v160);
                func_00282CF0(&pkt.pos[3], v130, v160);
                pkt.uv[0][1] = 0.0f;
                pkt.uv[1][1] = 1.0f;
                pkt.uv[2][1] = 0.0f;
                pkt.uv[3][1] = 1.0f;
                pkt.uv[2][0] = pkt.uv[3][0] = D_L23_001B1C00 + 1.0f;
                pkt.uv[0][0] = pkt.uv[1][0] = D_L23_001B1C00;
                func_00280B90(&pkt, 0, 0);
            }
        }
    }
}

/* func_L09_0037FCE8: the water sheet draw callback of Dobbo and Yeedil.
 * Adapted from public OpenRAC/rac1-decomp draw_pokitaru_ocean
 * (src/overlays/shared/homing_missile_and_water_sheet.c, GPL-3.0): RAC2 drops
 * the far quad and the height fade, and lifts each grid layer 0.05 above the
 * water height. Own unit: -G8 for the gp-relative wave speeds, -g for the
 * nops before the strip's div.s. */
#include "common.h"
typedef struct { float x,y,z,w; } Vec4f;
extern void func_00282CC0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282D30(void *,void *,float);
extern int func_00283D38(int,int,float);
extern u64 func_0027C878(int);
extern float func_00282E20(void *);
extern void func_00282A28(void);
typedef struct { float u, v; } UV_30BCD8;
typedef struct { float x, y, z; } Pos_30BCD8;
typedef struct {
    Vec4f v[4];
    int col[4];
    UV_30BCD8 uv[4];
    long long z70;
    long long z78;
    long long q80;
    long long q88;
} Quad_30BCD8;
typedef struct {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    float f14;
    float f18;
    int f1C;
    int f20;
    float f24;
    float f28;
    float f2C;
    int pad30, pad34, f38;
} Data_30BCD8;
typedef struct { char pad[0x140]; float x, y, z; } Cam_30BCD8;
typedef struct { char pad[0x228]; float f228, f22C; } Fog_30BCD8;

extern void func_002FC560(unsigned int, unsigned long long);
extern void func_00280328(void);
extern void func_00283098(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283CE0(int);
extern void func_00281810(int, void *, void *, void *, int);
extern int D_0018C0B4 __attribute__((nosda));
extern int D_001A79F0 MACRO_ADDR;
extern char D_L09_001BDF00[];
extern int D_L09_001A8A48 MACRO_ADDR;
extern char D_L09_001B9C30[];
extern float D_L09_001B9A00[];
extern float D_L09_001B3120 MACRO_ADDR;
extern char D_L09_001B98C0[];
extern Pos_30BCD8 D_L09_002336A0[];
extern int D_L09_002339A0[];
extern UV_30BCD8 D_L09_00233EA0[];
extern Pos_30BCD8 D_L09_00233AA0[];
extern int D_L09_00233DA0[];
extern UV_30BCD8 D_L09_002340A0[];
extern float D_L09_001AEC38[2] __attribute__((sda));
extern UV_30BCD8 D_L09_001B3110[] MACRO_ADDR;

/* Draws the fading edge strip and two scrolling water grid layers. */
void func_L09_0037FCE8(char *moby) {
    Vec4f v0;
    Vec4f v1;
    Vec4f a;
    Vec4f b;
    Vec4f c[4];
    Vec4f d0;
    Vec4f d1;
    Quad_30BCD8 q;
    Data_30BCD8 *d = (Data_30BCD8 *)*(void **)(moby + 0x68);
    float s228 = ((Fog_30BCD8 *)D_L09_001BDF00)->f228;
    float s22C = ((Fog_30BCD8 *)D_L09_001BDF00)->f22C;
    int i;
    int layer;
    int colA;
    int colB;
    int n;
    float t;
    float x;
    float y;

    if (D_0018C0B4 != 0x1C && D_L09_001A8A48 == 0) {
        ((Fog_30BCD8 *)D_L09_001BDF00)->f228 = 255.0f;
        ((Fog_30BCD8 *)D_L09_001BDF00)->f22C = 249.9f;
    }
    func_002FC560(0x42, 0x3200000044LL);
    func_002FC560(8, 0);
    func_002FC560(0x14, 0xFF9000000260LL);
    if (d->f38) func_002FC560(0x47, 0x5310B);
    else func_002FC560(0x47, 0x513F1);
    func_002FC560(6, func_0027C878(0x16));
    func_00280328();
    a.x = 1.0f;
    a.y = 0.0f;
    a.z = 0.0f;
    a.w = 1.0f;
    func_00283098(&a, &a, D_L09_001B9C30);
    b.x = 0.0f;
    b.y = 1.0f;
    b.z = 0.0f;
    b.w = 1.0f;
    func_00283098(&b, &b, D_L09_001B9C30);
    if (D_001A79F0 != 13) a.z = 0.0f;
    func_00282F20(&a, &a, 1.0f);
    if (D_001A79F0 != 13) b.z = 0.0f;
    func_00282F20(&b, &b, 1.0f);
    func_00282F20(&v0, &a, -75.0f);
    func_00282F20(&v1, &b, -87.0f);
    func_00282CC0(&c[0], &v0, &v1);
    func_00282F20(&v1, &b, 87.0f);
    func_00282CC0(&c[2], &v0, &v1);
    func_00282F20(&v0, &a, d->f28);
    func_00282F20(&v1, &b, -750.0f);
    func_00282CC0(&c[1], &v0, &v1);
    func_00282F20(&v1, &b, 750.0f);
    func_00282CC0(&c[3], &v0, &v1);
    for (i = 0; i < 4; i++) {
        Vec4f *p = &c[i];
        func_00282CC0(p, p, D_L09_001B9A00);
        p->z = D_L09_001B3120;
    }
    func_00282CF0(&d0, &c[1], &c[0]);
    func_00282CF0(&d1, &c[3], &c[2]);
    t = 10.0f;
    for (i = 0; i < 12; i += 2) {
        float f = func_00283CE0(i) * 0.1f;
        float blend = func_00283CE0(i);
        int col;
        blend = blend / t;
        col = func_00283D38(d->f0, d->f4, blend);
        func_00282D30(&v0, &d0, f);
        D_L09_002339A0[i] = col;
        D_L09_00233EA0[i].u = 0.0f;
        D_L09_00233EA0[i].v = 0.0f;
        func_00282CC0(&v0, &v0, &c[0]);
        D_L09_002336A0[i].x = v0.x;
        D_L09_002336A0[i].y = v0.y;
        D_L09_002336A0[i].z = v0.z;
        func_00282D30(&v0, &d1, f);
        D_L09_002339A0[i + 1] = col;
        D_L09_00233EA0[i + 1].u = 0.0f;
        D_L09_00233EA0[i + 1].v = 0.0f;
        func_00282CC0(&v0, &v0, &c[2]);
        D_L09_002336A0[i + 1].x = v0.x;
        D_L09_002336A0[i + 1].y = v0.y;
        D_L09_002336A0[i + 1].z = v0.z;
    }
    func_00281810(0xC, D_L09_002336A0, D_L09_002339A0, D_L09_00233EA0, 1);
    q.z78 = func_0027C878(0x16);
    q.q80 = 0xFF9000000260LL;
    q.q88 = 0x8000000044LL;
    q.z70 = 0;
    func_002FC560(0x42, 0x8000000048LL);
    func_002FC560(8, 0);
    func_002FC560(0x14, 0xFF9000000260LL);
    func_002FC560(0x47, 0x513F1);
    colA = d->fC;
    colB = d->f10;
    t = 1.0f;
    {
        colA = func_00283D38(0, colA, t);
        colB = func_00283D38(0, colB, t);
        for (layer = 0; layer < 2; layer++) {
            int id = layer + 0x3F;
            func_002FC560(6, func_0027C878(d->f1C + id));
            for (y = d->f18 * -2.0f; y < d->f18 * 2.0f; y += d->f18) {
                n = 0;
                for (x = d->f18 * -2.0f; x < d->f18 * 2.0f; x += d->f18) {
                    float z;

                    D_L09_002340A0[n].u = x / (d->f18 * 2.0f) * D_L09_001AEC38[layer] + D_L09_001B3110[layer].u;
                    D_L09_002340A0[n].v = y / (d->f18 * 2.0f) * D_L09_001AEC38[layer] + D_L09_001B3110[layer].v;
                    D_L09_00233AA0[n].x = x + ((Cam_30BCD8 *)D_L09_001B98C0)->x + 1.0f;
                    D_L09_00233AA0[n].y = y + ((Cam_30BCD8 *)D_L09_001B98C0)->y + 1.0f;
                    z = D_L09_001B3120;
                    z += (float)(layer + 1) * 0.05f;
                    D_L09_00233AA0[n].z = z;
                    i = n + 1;
                    D_L09_002340A0[i].u = x / (d->f18 * 2.0f) * D_L09_001AEC38[layer] + D_L09_001B3110[layer].u;
                    D_L09_002340A0[i].v = (y + d->f18) / (d->f18 * 2.0f) * D_L09_001AEC38[layer] + D_L09_001B3110[layer].v;
                    D_L09_00233AA0[i].x = x + ((Cam_30BCD8 *)D_L09_001B98C0)->x + 1.0f;
                    D_L09_00233AA0[i].y = y + d->f18 + ((Cam_30BCD8 *)D_L09_001B98C0)->y + 1.0f;
                    D_L09_00233AA0[i].z = z;
                    i = n + 2;
                    D_L09_002340A0[i].u = (x + d->f18) / (d->f18 * 2.0f) * D_L09_001AEC38[layer] + D_L09_001B3110[layer].u;
                    D_L09_002340A0[i].v = y / (d->f18 * 2.0f) * D_L09_001AEC38[layer] + D_L09_001B3110[layer].v;
                    D_L09_00233AA0[i].x = x + d->f18 + ((Cam_30BCD8 *)D_L09_001B98C0)->x + 1.0f;
                    D_L09_00233AA0[i].y = y + ((Cam_30BCD8 *)D_L09_001B98C0)->y + 1.0f;
                    D_L09_00233AA0[i].z = z;
                    i = n + 3;
                    D_L09_002340A0[i].u = (x + d->f18) / (d->f18 * 2.0f) * D_L09_001AEC38[layer] + D_L09_001B3110[layer].u;
                    D_L09_002340A0[i].v = (y + d->f18) / (d->f18 * 2.0f) * D_L09_001AEC38[layer] + D_L09_001B3110[layer].v;
                    D_L09_00233AA0[i].x = x + d->f18 + ((Cam_30BCD8 *)D_L09_001B98C0)->x + 1.0f;
                    D_L09_00233AA0[i].y = y + d->f18 + ((Cam_30BCD8 *)D_L09_001B98C0)->y + 1.0f;
                    D_L09_00233AA0[i].z = z;
                    for (i = n; i < n + 4; i++) {
                        v0.x = D_L09_00233AA0[i].x - ((Cam_30BCD8 *)D_L09_001B98C0)->x;
                        v0.y = D_L09_00233AA0[i].y - ((Cam_30BCD8 *)D_L09_001B98C0)->y;
                        v0.z = D_L09_00233AA0[i].z - ((Cam_30BCD8 *)D_L09_001B98C0)->z;
                        v0.w = 1.0f;
                        t = func_00282E20(&v0) / (d->f18 * 2.0f);
                        if (t > 1.0f) {
                            t = 1.0f;
                        }
                        D_L09_00233DA0[i] = func_00283D38(colA, colB, t);
                    }
                    n += 4;
                    if (n >= 0x40) {
                        func_00282A28();
                    }
                }
                func_00281810(n, D_L09_00233AA0, D_L09_00233DA0, D_L09_002340A0, 1);
            }
        }
    }
    ((Fog_30BCD8 *)D_L09_001BDF00)->f228 = s228;
    ((Fog_30BCD8 *)D_L09_001BDF00)->f22C = s22C;
    func_002FC560(0x47, 0x5360B);
}

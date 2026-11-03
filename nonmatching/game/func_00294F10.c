/* Claude Opus 5.5 (xhigh), task v2065 (from v2058's partial unit), USA v1.01.
 * Best: 1452/1452 bytes, 0/28 places. Profile: -O2 -G64 -Wa,-G64
 * -ffunction-sections -g (own unit; -G0 -g gave the same size before the
 * resource fixes). Exact from the TOC test through the end except the
 * func_0029D4D0 setup: per-arm `size << 7` lets jump2 cross-jump the arms'
 * shared sll (retail a0 temp); the two later sizes are separate scoped locals
 * (local-alloc single-death rule -> s0, 7 saved GPRs like retail); the else
 * tail lists [0x28/4] last because sched1 pulls the store carrying the base's
 * REG_DEAD forward. Loop 2 reads x0 and writes ax through SDATA aliases only
 * (all-alias gives the exact body but gp at every offset; canonical-only adds
 * two lui).
 * Remaining: (1) prologue: retail loads func_00295C50's argument before
 * v0 = -1; (2) coefficient loops: FPR choice for x0/y0/v0 (ours f5/f6/f7,
 * retail f7/f5/f6) and loop-2 load/store order (retail bx, ax, by, ay); (3)
 * retail computes &D_001A95B8 into s2 and does the arg moves before the
 * [0x238/4] store, ahead of func_0029D4D0 (ours sets s2 after the call);
 * (4) 32x32 mask loop: 256.0f before 15.5f, i in v1 with i+1 copied back,
 * address i*4 + j/8 + (D_001C4FA0 + 0x1B0) in that order, one nop fewer.
 * All declarations needed by this standalone draft are included. Not linked.
 */
#include "common.h"
extern unsigned int func_00294EC8(int);
extern int D_001C4FA0[];
extern int D_001A79F0_3[] __attribute__((sda));
typedef struct { int sector, size; } MapFile;
typedef struct {
    char pad0[0x36C];
    int base;           /* 0x36C */
    char pad370[0x14F0 - 0x370];
    MapFile files0[28]; /* 0x14F0 */
    MapFile files1[28]; /* 0x15D0 */
} MapToc;
extern char D_0014B540_1[];
#define TOC ((MapToc *)D_0014B540_1)
typedef struct { float x0, y0, x1, y1, u0, v0, u1, v1; } UiMapEndpoints;
typedef struct { float ax, bx, ay, by; } UiMapCoefficients;
extern int D_00256028[][2];
extern UiMapEndpoints D_00255C30[];
extern UiMapCoefficients D_00255ED0[];
extern UiMapEndpoints D_001A93D0[2] MACRO_ADDR;
extern UiMapEndpoints D_001A93D0_gp[2] SDATA(D_001A93D0);
extern UiMapCoefficients D_001A9428[2] MACRO_ADDR;
extern UiMapCoefficients D_001A9428_gp[2] SDATA(D_001A9428);
extern unsigned char D_001A7AF8[] MACRO_ADDR;
#define OWNED5 D_001A7AF8[5]
extern char *D_001BAED0 __attribute__((nosda));
extern char D_001A95A0[], D_001A95B8[];
extern unsigned char D_0018D278[];
extern void func_00295C50(int);
extern int func_002B7C80(void *, int, int);
extern int func_002EED58(void *, int, int, char *);
extern void func_0029D4D0(void *, void *);
extern void *func_0028B2B8(int, int, char *, int);
extern void func_00282B50(void *, void *, int);
extern void func_00297730(char *, unsigned char *, int);
extern void func_00297400(u8 *, u8 *, short *);

void func_00294F10(void)
{
    int i, j;
    float x0, y0, x1, y1, u0, v0, u1, v1;
    char *scratch, *packed;
    int bytes;

    D_001C4FA0[4] = 1;
    { int i; for (i = 0; i < 21; i++) {
        D_001C4FA0[0x108 / 4 + i] = D_00256028[i][0];
        ((float *)D_001C4FA0)[0xB4 / 4 + i] = 0.65f;
        D_001C4FA0[0x15C / 4 + i] = D_00256028[i][1];
    } }
    D_001C4FA0[0x238 / 4] = -1;
    func_00295C50(D_001A79F0_3[0]);
    { int i; for (i = 0; i < 21; i++) {
        float sx, sy;
        x0 = D_00255C30[i].x0;
        y0 = D_00255C30[i].y0;
        x1 = D_00255C30[i].x1;
        y1 = D_00255C30[i].y1;
        u0 = D_00255C30[i].u0;
        v0 = D_00255C30[i].v0;
        u1 = D_00255C30[i].u1;
        v1 = D_00255C30[i].v1;
        sx = (u0 - u1) / (x0 - x1);
        sy = (v0 - v1) / (y0 - y1);
        D_00255ED0[i].bx = sx;
        D_00255ED0[i].ax = u0 - sx * x0;
        D_00255ED0[i].by = sy;
        D_00255ED0[i].ay = v0 - sy * y0;
    } }
    { int i; for (i = 0; i < 2; i++) {
        float sx, sy;
        x0 = D_001A93D0_gp[i].x0;
        y0 = D_001A93D0[i].y0;
        x1 = D_001A93D0[i].x1;
        y1 = D_001A93D0[i].y1;
        u0 = D_001A93D0[i].u0;
        v0 = D_001A93D0[i].v0;
        u1 = D_001A93D0[i].u1;
        v1 = D_001A93D0[i].v1;
        sx = (u0 - u1) / (x0 - x1);
        sy = (v0 - v1) / (y0 - y1);
        D_001A9428[i].bx = sx;
        D_001A9428_gp[i].ax = u0 - sx * x0;
        D_001A9428[i].by = sy;
        D_001A9428[i].ay = v0 - sy * y0;
    } }
    if ((TOC->files0[D_001C4FA0[0x230 / 4]].size != 0 && !OWNED5)
        || (TOC->files1[D_001C4FA0[0x230 / 4]].size != 0 && OWNED5)) {
        D_001C4FA0[0x28 / 4] = 1;
        if (OWNED5)
            bytes = TOC->files1[D_001C4FA0[0x230 / 4]].size << 7;
        else
            bytes = TOC->files0[D_001C4FA0[0x230 / 4]].size << 7;
        scratch = D_001BAED0;
        packed = scratch + 0x9A800;
        if (OWNED5) {
            func_002B7C80(packed, TOC->files1[D_001C4FA0[0x230 / 4]].sector + TOC->base, TOC->files1[D_001C4FA0[0x230 / 4]].size);
            D_001C4FA0[0x23C / 4] = 1;
        } else {
            func_002B7C80(packed, TOC->files0[D_001C4FA0[0x230 / 4]].sector + TOC->base, TOC->files0[D_001C4FA0[0x230 / 4]].size);
            D_001C4FA0[0x23C / 4] = 0;
        }
        D_001C4FA0[0x238 / 4] = func_002EED58(packed, bytes, 0x3C00, D_001A95A0);
        D_001C4FA0[0x240 / 4] = bytes;
        func_0029D4D0(packed, scratch);
        {
            int size = ((int *)scratch)[1] - ((int *)scratch)[0];
            D_001C4FA0[0] = (int)func_0028B2B8(size, 0, D_001A95B8, 0x2EB);
            func_00282B50((void *)D_001C4FA0[0], scratch + ((int *)scratch)[0], size);
        }
        D_001C4FA0[0] += 8;
        D_001C4FA0[1] = D_001C4FA0[0];
        {
            int size = ((int *)scratch)[2] - ((int *)scratch)[1];
            D_001C4FA0[5] = (int)func_0028B2B8(size, 0, D_001A95B8, 0x2FC);
            func_00282B50((void *)D_001C4FA0[5], scratch + ((int *)scratch)[1], size);
        }
        D_001C4FA0[2] = (int)func_0028B2B8(0x1000, 0, D_001A95B8, 0x303);
        for (i = 0; i < 8; i++) {
            D_001C4FA0[0x30 / 4 + i * 4] = -1;
            D_001C4FA0[0x34 / 4 + i * 4] = -1;
            D_001C4FA0[0x38 / 4 + i * 4] = D_001C4FA0[2] + (i << 9);
        }
        D_001C4FA0[3] = (int)func_0028B2B8(0x8000, 0, D_001A95B8, 0x30C);
        if (func_00294EC8(D_001C4FA0[0x230 / 4]))
            func_00297730((char *)D_001C4FA0[3], D_0018D278 + (D_001C4FA0[0x230 / 4] << 11), D_001C4FA0[5]);
        else
            func_00297400((u8 *)D_001C4FA0[3], (u8 *)D_001C4FA0[0], (short *)D_001C4FA0[1]);
        for (i = 0; i < 32; i++) {
            float dy = 15.5f - (float)i;
            float dy2 = dy * dy;
            for (j = 0; j < 32; j++) {
                float dx = 15.5f - (float)j;
                if (dx * dx + dy2 > 256.0f)
                    ((u8 *)D_001C4FA0)[0x1B0 + i * 4 + j / 8] |= 1 << (j % 8);
            }
        }
    } else {
        D_001C4FA0[0] = 0;
        D_001C4FA0[2] = 0;
        D_001C4FA0[3] = 0;
        D_001C4FA0[1] = 0;
        D_001C4FA0[0x28 / 4] = 0;
    }
}

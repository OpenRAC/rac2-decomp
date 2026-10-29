/* Nonmatching interface overlay reconstruction, 2026-10-28. No C credit.
 * Four US checks, 0/5. Retained 736/768B, frame0x70 exact, with -O2 -G0
 * -ffunction-sections. First diagnostic728B had rectangle-top375 rather
 * than the actual later374; retained code corrects that constant. Explicit
 * coordinate/factor lifetimes and narrow unsplit edges give736B; broad
 * -fno-gcse and one truthful bank-equivalent interleaving are identical.
 * Three forms converge. Canonical actual object/flags/five-FP declaration
 * is retained, with no useless profile option. Remaining: camera high-half
 * lifetime and saved GPR versus extra saved FP, literal250 retention, FP
 * conversion/call scheduling and projection restore order.
 * Reopen with independent original source/lifetime evidence.
 *
 * Actual callback user002F14E8 confirms int(void); each exit returns the
 * GP control word. Actual00336D50 returns signed32 address, explicitly
 * cast; actual00300A00 takes a0 object,a1 flags and f12..f16 five floats,
 * returns void. Actual0028E588 returns int and0028E868 returns void.
 * Actual0027EAE8 forwards its color pointer to actual0027EA28, which reads
 * exactly two32-bit words. Both words are assigned before the full8B struct
 * copy and drawing call; no third color or unstored padding is consumed.
 * Raw-only0027AB40 mutation/return interface remains provisional.
 * Unknown external data extents are incomplete; scalar float-to-int casts
 * naturally reproduce the observed cvt.w.s mechanism without handwritten asm.
 */

#include "common.h"
typedef struct { int first, second; } OverlayColorPair;
extern unsigned char *D_L01_001A908C __attribute__((sda));
extern unsigned char D_L01_0027EAC8[];
extern int D_L01_001A90D0[] SDATA(D_L01_001A90D0);
extern int D_L01_001A90CC[] SDATA(D_L01_001A90CC);
extern float D_L01_001A90C4[] SDATA(D_L01_001A90C4);
extern float D_L01_001B2DC4[] __attribute__((sda));
extern unsigned char D_L01_001BD9C0[];
extern void func_0027AB40(void);
extern int func_00336D50(void *, int);
extern void func_00300A00(void *, int, float, float, float, float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_0027EAE8(int, int, int, int, int, const void *);
extern int func_0028E588(int, int);
extern void func_0028E868(int, int, int, int, int, int);

int func_L01_002F1588(void)
{
    OverlayColorPair colors, source;
    float oldProjection, span, rounding, unit, zero, height;
    int top, bottom;
    unsigned char *node;
    int x2;
    if (!D_L01_001A908C || *(int *)D_L01_0027EAC8 || *(int *)(D_L01_0027EAC8 + 0x24) != -1)
        return D_L01_001A90D0[0];
    oldProjection = *(float *)(D_L01_001BD9C0 + 0xB0);
    *(float *)(D_L01_001BD9C0 + 0xB0) = 0.6200000047683716f;
    span = 375.0f;
    func_0027AB40();
    rounding = 0.5f;
    node = (unsigned char *)func_00336D50(D_L01_001A908C + 0x8710, 142);
    height = (float)(int)(D_L01_001B2DC4[0] * span + rounding);
    unit = 1.0f;
    zero = 0.0f;
    func_00300A00(node, 0x60442D00, 250.0f, height, unit, unit, zero);
    node = (unsigned char *)func_00336D50(D_L01_001A908C + 0x8710, 143);
    height = (float)(int)(D_L01_001B2DC4[0] * span + rounding);
    func_00300A00(node, 0x60241700, 250.0f, height, unit, unit, zero);
    node = (unsigned char *)func_00336D50(D_L01_001A908C + 0x8710, 144);
    height = (float)(int)(D_L01_001B2DC4[0] * span + rounding);
    func_00300A00(node, 0x55F0C070, 250.0f, height, unit, unit, zero);
    source.first = (int)0x800050C0;
    source.second = func_00283D38(0x800050C0, 0x80C04000, D_L01_001A90C4[0]);
    colors = source;
    x2 = func_00283CF0(190.0f + func_00283CE0(198) * D_L01_001A90C4[0]);
    top = (int)(D_L01_001B2DC4[0] * 374.0f + rounding);
    bottom = (int)(D_L01_001B2DC4[0] * 388.0f + rounding);
    func_0027EAE8(190, top, x2, bottom, 0, &colors);
    if (D_L01_001A90CC[0]) {
        int icon = func_0028E588(0xEAA7, D_L01_001A90CC[0] - 1);
        top = (int)(D_L01_001B2DC4[0] * 352.0f + rounding);
        bottom = (int)(D_L01_001B2DC4[0] * 43.0f + rounding);
        func_0028E868(icon, 139, top, 43, bottom, 128);
    }
    *(float *)(D_L01_001BD9C0 + 0xB0) = oldProjection;
    func_0027AB40();
    return D_L01_001A90D0[0];
}

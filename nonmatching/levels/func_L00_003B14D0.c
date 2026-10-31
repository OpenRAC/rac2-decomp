/* Reconstruction retained 30 October 2026; not a linked match.
 * Profile: -O2 -G0 -ffunction-sections -frac2-zero-ti-por -g.
 * Equal 1332-byte extent, but frame is 0x110 instead of 0x120; floating constant lifetimes and prologue differ.
 * Reopen with a lifetime witness for the retained unit scale and separate RGB pointer locals.
 * ABI/bounds: Two full 24-byte palette objects, explicitly aligned locals, full vector unions, real query return count and shared query-result list; damage helper retains all eight GPR and three FP inputs.
 * Local checks and release presence are recorded in the shared NMC index.
 * Semantic equivalence has not been validated by the functional gate.
 */
#include "common.h"

typedef union { int q __attribute__((mode(TI))); float f[4]; } BurstVector;
typedef struct { u32 color[6]; } BurstColors;
extern unsigned char D_00189E20[];
extern unsigned char D_00139568[];
extern unsigned char D_L00_00262570[];
extern unsigned char D_L00_001B8DC0[];
extern int D_L00_001C3280[];
extern BurstColors D_L00_001AF858;
extern BurstColors D_L00_001AF870;
extern int func_00277F48(void *, int, void *, void *, float);
extern void func_002A9850(void *, void *, int *, int, int, int, int, int, float, float, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern int func_002AAFA0(u32, int);
extern void func_002AAF40(int *, int *, int *, int);
extern char *func_002BBCB0(void *, void *, int, int, int, int, int, int, float, float);
extern void func_L00_003A0DA0(void *, void *, void *, int, int, int, int, int, float);

/* Burst at the centroid of a consumed trail group. Palette records are complete
 * 24-byte objects, and the query result uses the helper's shared object list. */
void func_L00_003B14D0(float x, float y, float z)
{
    BurstVector position, velocity, delta;
    BurstColors start __attribute__((aligned(16)));
    BurstColors end __attribute__((aligned(16)));
    int c0, c1, life, age, n, i;
    int red, green, blue, rr, gg, bb;
    float distance, fade, jitter;
    position.q = 0;
    position.f[0] = x; position.f[1] = y; position.f[2] = z;
    n = func_00277F48(&position, 16, *(void **)(D_00189E20 + 0x2290), 0, 3.0f);
    func_002A9850(*(void **)(D_00189E20 + 0x2290), &position, D_L00_001C3280,
        n, 0, 0x830000, 2, 1, 8.0f, 1.0f, 1.0f);
    velocity.q = 0;
    velocity.f[2] = 0.033333335f;
    func_00282CF0(&delta, D_L00_001B8DC0, &position);
    distance = func_00282DF0(&delta);
    n = distance < 6.0f ? func_00283CF0(distance) + 1 : 4;
    fade = 0.0f;
    if (distance < 7.0f) fade = 7.0f - distance;
    for (i = n; i != 0; --i) {
        jitter = func_002A7878(8.0f, 10.0f) * 0.016666668f - fade * 0.016666668f;
        start = D_L00_001AF858;
        end = D_L00_001AF870;
        c0 = func_002AAFA0(start.color[func_002A77E0(6)],
            D_L00_00262570[D_00139568[0x23] * 0xe0 + 4] != 0);
        c1 = func_002AAFA0(end.color[func_002A77E0(6)],
            D_L00_00262570[D_00139568[0x23] * 0xe0 + 4] != 0);
        life = func_002A7820(15, 20);
        age = func_002A7820(25, 30);
        func_002BBCB0(&position, &velocity, c0, c1, life, age, 0, 0, 400000.0f, jitter);
    }
    if (distance > 9.0f) {
        func_L00_003A0DA0(*(void **)(D_00189E20 + 0x2290), &position,
            &velocity, 15, 127, 127, 127, 32, 4.0f);
        red = 127; green = 32; blue = 0;
        func_002AAF40(&red, &green, &blue, D_L00_00262570[D_00139568[0x23] * 0xe0 + 4] != 0);
        func_L00_003A0DA0(*(void **)(D_00189E20 + 0x2290), &position,
            &velocity, 24, (u8)red, (u8)green, (u8)blue, 32, 4.0f);
    }
    rr = 127; gg = 63; bb = 0;
    func_002AAF40(&rr, &gg, &bb, D_L00_00262570[D_00139568[0x23] * 0xe0 + 4] != 0);
    func_L00_003A0DA0(*(void **)(D_00189E20 + 0x2290), &position,
        &velocity, 20, (u8)rr, (u8)gg, (u8)bb, 48, 4.0f);
    rr = 96; gg = 16; bb = 0;
    func_002AAF40(&rr, &gg, &bb, D_L00_00262570[D_00139568[0x23] * 0xe0 + 4] != 0);
    func_L00_003A0DA0(*(void **)(D_00189E20 + 0x2290), &position,
        &velocity, 27, (u8)rr, (u8)gg, (u8)bb, 64, 3.5f);
    rr = 32; gg = bb = 0;
    func_002AAF40(&rr, &gg, &bb, D_L00_00262570[D_00139568[0x23] * 0xe0 + 4] != 0);
    func_L00_003A0DA0(*(void **)(D_00189E20 + 0x2290), &position,
        &velocity, 29, (u8)rr, (u8)gg, (u8)bb, 32, 3.0f);
}

/* functional: high. Same mover set-up as retail (state fields, tuning constants, first animation); the constants are held in other registers. */
/* Retained complete C reconstruction, 30 October 2026. NOT MATCHING.
 * Profile: -O2 -G8 -ffunction-sections.
 * us: 09_dobbo: instruction at +0x74 differs; us2: 09_dobbo: instruction at +0x74 differs; pal: ABSENT.
 * Measured state fields are represented by their true widths and offsets, and func_002B60B0 has
 * its real pointer result. Modern qcopy keeps all 16-byte transfers. The typed initializer is
 * retail-sized but differs first at +0x74; measured-order volatile fields grow it to 584 and
 * were reverted.
 * Reopen: Independent initializer source-order and FP argument lifetime witness.
 * Local placement checks only; no strict linked or native-runtime claim.
 */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));

extern int func_00283CF0(float);
extern void *func_002B60B0(char *, float, float, float, float);
extern float func_L09_0033E7A0(int);
extern int func_L09_003EA2D0(char *, int, int);
extern void func_002A7750(char *, int, int);
extern unsigned int D_L09_001FE6C0[];
extern float D_L09_001B0BF0_g SDATA(D_L09_001B0BF0);
extern float D_L09_001B0BF4_g SDATA(D_L09_001B0BF4);
extern float D_L09_001B0BF8_g SDATA(D_L09_001B0BF8);
extern float D_L09_001B0BFC_g SDATA(D_L09_001B0BFC);

typedef struct {
    char pad0[0x28];
    unsigned char f28;
    char pad29[0x6];
    unsigned char f2F;
    float f30;
    char pad34[0x14];
    unsigned char f48;
    char pad49[0x1];
    unsigned char f4A;
    char pad4B[0x5];
    float f50;
    int f54;
    int f58;
    int f5C;
    float f60;
    char pad64[0x18];
    int f7C;
    float f80;
    char pad84[0x10C];
    unsigned char f190;
    unsigned char f191;
    unsigned char f192;
    char pad193[0x3];
    unsigned char f196;
    unsigned char f197;
    char pad198[0x4];
    int f19C;
    int f1A0;
    float f1A4;
    float f1A8;
    float f1AC;
    float f1B0;
    int f1B4;
    short f1B8;
    char pad1BA[0x2];
    float f1BC;
    char pad1C0[0x8];
    int f1C8;
    char pad1CC[0x20];
    unsigned char f1EC;
    unsigned char f1ED;
    unsigned char f1EE;
    unsigned char f1EF;
    char pad1F0[0x2];
    unsigned char f1F2;
    unsigned char f1F3;
    char pad1F4[0x2];
    unsigned char f1F6;
    char pad1F7[0x159];
    int f350;
    int f354;
    char pad358[0x14];
    int f36C;
    char pad370[0x4];
    int f374;
    char pad378[0x8];
    int f380;
} DobboMoverState;

/* Initialises the state block of a new object: copies its position and heading into the
   block, sets the tuning constants and starts the first animation. */
void func_L09_003EA798(char *object) {
    DobboMoverState *state = *(DobboMoverState **)(object + 0x68);
    char *pos = object + 0x10;
    int entry;
    float ax;
    float ay;
    float az;
    float aw;

    qcopy((char *)state + 0x330, pos);
    qcopy((char *)state + 0x340, object + 0xF0);
    state->f48 = func_00283CF0(25.0f);
    state->f4A = func_00283CF0(19.2f);
    state->f1F2 = 4;
    state->f1EC = 4;
    state->f1EE = 4;
    state->f1F3 = 8;
    state->f1F6 = 1;
    state->f28 = 3;
    state->f2F = 2;
    state->f191 = 2;
    state->f192 = 2;
    state->f196 = 2;
    state->f197 = 2;
    state->f1ED = 8;
    state->f1EF = 8;
    state->f190 = 5;
    ay = 0.016666668f * D_L09_001B0BF4_g;
    az = 4.8481374e-06f * D_L09_001B0BF8_g;
    aw = 0.00029088825f * D_L09_001B0BFC_g;
    ax = 0.00027777778f * D_L09_001B0BF0_g;
    state->f1A8 = 0.0025f;
    state->f1B0 = 1.5f;
    state->f1BC = 0.4f;
    state->f30 = 1.0f;
    state->f1C8 = 5;
    state->f1AC = 0.0013888889f;
    state->f19C = 0;
    state->f1A0 = 0;
    state->f1B4 = 0;
    state->f1B8 = 0;
    state->f54 = 0;
    state->f58 = 0;
    state->f5C = 0;
    state->f7C = 0;
    state->f50 = 3.5f;
    state->f60 = 3.141593f;
    state->f80 = 0.52359885f;
    state->f1A4 = 0.0025f;
    func_002B60B0(object, ax, ay, az, aw);
    state->f354 = state->f374;
    func_L09_0033E7A0(state->f36C);
    func_L09_0033E7A0(state->f350);
    entry = state->f36C;
    if (entry != -1) {
        qcopy(pos, (char *)D_L09_001FE6C0[entry] + 0x10);
        func_L09_003EA2D0(object, entry, -1);
        state->f380 = 0;
    } else {
        state->f380 = 1;
    }
    func_002A7750(object, 1, 1);
}

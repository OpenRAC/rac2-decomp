#include "common.h"

/* Incomplete sda arrays at -G0: the status table's address is rebuilt on each pass. */
extern float D_L08_001B3A20[] __attribute__((sda));
extern int D_L08_001B3A30[] __attribute__((sda));
extern int D_L08_001B39A0[] __attribute__((sda));
extern char D_L08_002604A0[];
extern void func_002FC560(int, u64);
extern int func_L02_002F1658(void);
extern void func_L08_0042A980(int, int);
extern void func_L08_0042A0B0(int, int, void *, int, int, int, int);
extern int func_002A7820(int, int);
extern void func_L08_00389B68(int, int, u64, int, u64);

/* The spawner's per-frame draw callback: each live slot past state 1 scrolls its phase
   (wrapping at -8) and has its two 0x140-byte strips drawn. */
void func_L08_00429EE8(char *spawner) {
    char *vars = *(char **)(spawner + 0x68);
    int i;

    VU1_addGSregister(0x47, 0x51001);
    for (i = 0; i < 3; i++) {
        float *phase = &D_L08_001B3A20[i];
        int firstStrip, secondStrip, x, y;
        char *strip2;

        if (!gBeamSlotKey[i] || gBeamSlotState[i] < 2) continue;
        firstStrip = i * 2;
        secondStrip = firstStrip + 1;
        if (IsResidentFlagClear()) {
            *phase -= 0.2f;
            if (*phase <= -8.0f) *phase += 8.0f;
        }
        strip2 = D_L08_002604A0 + secondStrip * 0x140;
        DrawGlowBillboardPair(gBeamSlotKey[i], i);
        y = *(int *)(vars + 4) + 63;
        x = *(int *)vars + 63;
        DrawRibbonStrips(y, x, D_L08_002604A0 + firstStrip * 0x140, 128, 64, i, -1);
        DrawRibbonStrips(y, x, strip2, 48, 16, i, RandomIntRange(1, 20));
    }
    AppendVectorsToPacket(2, 0x47, 0x5340B, 0x42, 0x8000000044ULL);
}

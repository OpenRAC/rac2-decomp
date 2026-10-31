/* 30 October 2026 retained ordinary C; no linked match or semantic proof.
 * Profile: -O2 -G0 -ffunction-sections -mno-split-addresses.
 * us: 17_smolg: 512 bytes, expected 520.
 * us2: 17_smolg: 512 bytes, expected 520.
 * pal: func_L17_003A4740 is in neither catalogue of pal.
 * Corrected the actual global float read at D_L17_001AF52C; old integer conversion was not
 * truthful. Current512/520 bytes. The generator already excludes8 leading bytes (entry003A4748),
 * so the old prefix-store blocker is superseded: do not insert that store in this function.
 * Address materialization and scheduling remain. The older516-byte form with wrong type is
 * preserved as an explicitly unsafe historical alternative.
 */
#include "common.h"

extern int D_001A7340;
extern int D_001A7344;
extern int D_001A7348;
extern int D_001A734C;
extern float D_L17_001AF52C[];

extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern unsigned long func_0027C878(int);
extern int func_002A77E0(int);
extern void func_0027E018(int, int, int, int, int, int, int, int, unsigned long long, unsigned long long);

void func_L17_003A4740(char *self) {
    char *data = *(char **)(self + 0x68);
    float fv[2];
    unsigned long packet;
    int nx, ny, i, j;
    float pv[2];
    float base, a, b;
    int color;
    int t0, t1;

    fv[0] = func_00283CE0(D_001A7348);
    fv[1] = func_00283CE0(D_001A734C);
    packet = func_0027C878(0x1E);
    nx = D_001A7340 / 32 + 1;
    ny = D_001A7344 / 32 + 1;

    for (i = 0; i < nx; i++) {
        for (j = 0; j < ny; j++) {
            pv[0] = (float)(i * 32);
            pv[1] = (float)(j * 32);
            base = D_L17_001AF52C[0];
            a = func_00283CE0(*(int *)(data + 0x140));
            b = func_00283CE0(0x5A);
            color = (func_00283CF0(a * 127.5f / b) << 24) + 0xFF7F7F;
            t0 = func_002A77E0(0x20);
            t1 = func_002A77E0(0x20);
            func_0027E018(func_00283CF0(pv[0] - base), func_00283CF0(pv[1] - base), 0x20, 0x20, t0, t1, 0x20, 0x20, color, packet);
        }
    }
}

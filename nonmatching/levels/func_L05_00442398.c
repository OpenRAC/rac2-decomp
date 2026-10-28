/* Retained reconstruction, USA v1.01, game -O2 -G0.
 * 288/288 bytes, 0/4 local places. The guard constant uses a different GPR
 * and the guard store is scheduled before the descriptor calculation.
 * The measured 64-byte stack transform and the helper's pointer return are
 * preserved. Default G0 and explicit G8 views do not close the guard schedule.
 * No volatile ordering, raw assembler-name alias or invented dependency.
 * Reopen with guard/descriptor lifetime evidence; no strict linked match.
 */
#include "common.h"

extern int D_L05_001B1B20_gp SDATA(D_L05_001B1B20);
extern int D_L05_001B1ADC_gp SDATA(D_L05_001B1ADC);
extern int D_L05_001B1B24_gp SDATA(D_L05_001B1B24);
extern unsigned char *D_L05_001B1EC4 __attribute__((sda));
extern unsigned char *D_L05_001B251C __attribute__((sda));
extern int D_L05_001B1F60 __attribute__((sda));
extern int D_L05_001B1F64 __attribute__((sda));
extern float D_L05_001B3620[4];
extern float D_L05_001B3610[];
extern int D_001A79F0 __attribute__((sda));
extern void *func_L05_003D1E60(void *, void *, int);
extern void func_L05_004424B8(void *, float);
extern void func_002AB6D8(float *, float *);

/* The transform passed to func_002AB6D8 is four complete, aligned rows.
 * That helper reads all 64 bytes and writes three angle floats to its output. */
void func_L05_00442398(unsigned char *object)
{
    float transform[4][4];
    unsigned char *descriptor, *record, *actors;
    float scale;
    if (D_L05_001B1B20_gp == 6)
        return;
    descriptor = D_L05_001B1EC4 + *(s16 *)(object + 0x84) * 0x20;
    actors = D_L05_001B251C;
    D_L05_001B1B20_gp = 6;
    record = *(unsigned char **)(descriptor + 0x1C);
    D_L05_001B1F60 = 0;
    D_L05_001B1F64 = 0;
    record = actors + *(int *)(record + 0x20) * 0x100;
    func_L05_003D1E60(record + 0x10, 0, 1);
    qcopy(D_L05_001B3620, object + 0x30);
    scale = 1.0f;
    if (D_001A79F0 == 20)
        scale = 2.0f;
    func_L05_004424B8(object, scale);
    D_L05_001B1B24_gp = D_L05_001B1ADC_gp;
    qcopy(transform[0], object);
    qcopy(transform[1], object + 0x10);
    qcopy(transform[2], object + 0x20);
    qzero(transform[3]);
    transform[3][3] = 1.0f;
    transform[0][3] = transform[1][3] = transform[2][3] = 0.0f;
    func_002AB6D8(&transform[0][0], D_L05_001B3610);
}

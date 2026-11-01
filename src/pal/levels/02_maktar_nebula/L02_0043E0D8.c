#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct { u8 reserved_00[0x34]; int timer; } L02_State;
extern L02_State D_L02_001BE200;
extern void func_00282CC0(void *, void *, void *);
extern unsigned short **D_L02_001A9014 __attribute__((sda));
extern u8 *D_L02_001B3C1C __attribute__((sda));
extern float D_L02_001B2640[] MACRO_ADDR;
extern float func_00282E80(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_L01_002E2608(void *, int, int, int, int);

void func_PAL_L02_0043E0D8(u8 *a0) {
    u8 *st = *(u8 **)(a0 + 0x68);
    float pt[4] __attribute__((aligned(16)));
    float tmp[4] __attribute__((aligned(16)));
    float m[16] __attribute__((aligned(16)));
    unsigned short *q;
    u8 *e;
    u8 *rec;
    float best;
    float d;
    int idx;
    int bestid;
    int i;
    int k;

    for (i = 0; i < 2; i++) {
        idx = -1;
        if (i == 0) {
            if (D_L02_001BE200.timer >= 0x318) {
                if (D_L02_001BE200.timer < 0x466) {
                    *(TI128 *)tmp = 0;
                    tmp[0] = 495.0f;
                    tmp[1] = 587.0f;
                    tmp[2] = 513.0f;
                    qcopy(pt, tmp);
                    idx = 0x3F;
                }
            }
        }
        if (i == 1) {
            if (D_L02_001BE200.timer >= 0x3E8) {
                if (D_L02_001BE200.timer < 0x4E3) {
                    *(TI128 *)tmp = 0;
                    tmp[0] = 515.0f;
                    tmp[1] = 596.0f;
                    tmp[2] = 512.0f;
                    qcopy(pt, tmp);
                    idx = 0x40;
                }
            }
        }
        if (idx != -1) {
            bestid = -1;
            best = 99999.0f;
            for (q = D_L02_001A9014[*(int *)st];
                 q != 0 && ((short)q[-1] >= 0 || q == D_L02_001A9014[*(int *)st]) &&
                 (e = D_L02_001B3C1C + ((*q & 0x7FFF) << 6)) != 0;
                 q++) {
                d = func_00282E80(e + 0x30, pt);
                if (d < best) {
                    best = d;
                    bestid = *q & 0x7FFF;
                }
            }
            if (bestid != -1) {
                rec = D_L02_001B3C1C + (bestid << 6);
                for (k = 0; k < 4; k++) {
                    func_00283098(m + k * 4, D_L02_001B2640 + k * 4, rec);
                    func_00282CC0(m + k * 4, m + k * 4, rec + 0x30);
                }
                func_L01_002E2608(m, idx, 2, 0xFF808080, 0);
            }
        }
    }
}


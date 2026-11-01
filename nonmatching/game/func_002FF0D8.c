/* Closer C, 1 November 2026: 428/428, -O2 -G0 -g, 31 rows. D_001B2310 is one incomplete sda struct array: every field then has
 * retail's absolute form. Left: the constant 1 fills bnez's slot from the target (retail fills from the fall-through),
 * which also moves the D_001AD7E4 stores; first two arms' base/index registers.
 */
/* Retained reconstruction, USA v1.01.
 * 416/428 bytes, game -O2 -G0 -g, measured on the initial retained copy spelling. Reconstructs transition count/rate, vector snapshots, resident defaults and mode-dependent actor selection with the actual pointer return of func_002FF300. Scalar SDA metadata retains mixed address forms, but copied-vector addressing and later branch/store scheduling differ. A pointer variant with -mno-split-addresses reaches an assembler internal assertion; no tool changes were attempted.
 * No strict linked match.
 */
#include "common.h"

extern u16 D_001AD7F8 SDATA(D_001AD7F8);
typedef struct {
    s16 elapsed;
    s16 count;
    float rate;
    s16 item;
    s16 pad1A;
    u8 flag1C;
    u8 flag1D;
    u8 pad1E[2];
    float from[4];
    float to[4];
    unsigned char *model;
    u8 pad44;
    u8 owned;
} Transition;
extern Transition D_001B2310[] __attribute__((sda));
extern int D_001AD7E4[] SDATA(D_001AD7E4);
extern int D_001AD7E8[] SDATA(D_001AD7E8);
extern unsigned char D_00189E20[];
typedef struct { char pad[0x24]; int sound; int volume; char pad2c[0x3C]; int busy; } SoundState;
extern SoundState D_001A63A8;
extern unsigned char D_00139568[];
extern unsigned char D_00239BA0[];
extern float func_00283CE0(int);
extern char *func_002FF300(int, int);

void func_002FF0D8(void)
{
    unsigned char *record;
    D_001B2310[0].count = D_001AD7F8;
    D_001B2310[0].rate = 1.0f / func_00283CE0(D_001B2310[0].count);
    qcopy(D_001B2310[0].from, D_00189E20 + 0x80);
    qcopy(D_001B2310[0].to, D_00189E20 + 0x90);
    D_001B2310[0].elapsed = 0;
    {
        SoundState *sound = &D_001A63A8;
        if (sound->busy == 0 && sound->sound == -1) {
            sound->volume = 0;
            sound->sound = 0xDB7;
        }
    }
    D_001AD7E4[0] = 1;
    D_001AD7E8[0] = 0;
    D_001B2310[0].flag1C = 0;
    D_001B2310[0].flag1D = 0;
    if (D_001B2310[0].item == 31) {
        record = D_00139568[31] * 0xE0 + D_00239BA0;
        D_001B2310[0].model = (unsigned char *)func_002FF300(*(int *)(record + 0x14), 1);
        D_001B2310[0].owned = 0;
    } else if (D_001B2310[0].item == 45) {
        record = D_00139568[45] * 0xE0 + D_00239BA0;
        D_001B2310[0].model = (unsigned char *)func_002FF300(*(int *)(record + 0x14), -1);
        D_001B2310[0].owned = 0;
    } else if (D_001B2310[0].item == 9) {
        D_001B2310[0].model = (unsigned char *)func_002FF300(601, 0);
        D_001B2310[0].owned = 0;
    } else {
        D_001B2310[0].owned = 1;
        record = D_00239BA0 + D_00139568[D_001B2310[0].item] * 0xE0;
        D_001B2310[0].model = *(unsigned char **)(D_00189E20 + *(int *)(record + 0xC) * 0x50 + 0x1220);
    }
}

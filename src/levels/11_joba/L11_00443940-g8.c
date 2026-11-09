/* func_L11_00443940: the help-prompt HUD lines (labels 0x49/0x48, then a pulsing colour
 * from func_00283D38, the 0x4b line when the selection is nonzero and the first available
 * 0x4a entry after it). Twin of func_L02_003FDDE8.
 * one/k3 are set-once label_y actives (k3 only in the 0x4b draw, which local-alloc keeps beside
 * the label copy); x3 is that draw's own x. The label_y dead-test helper, set-once constant
 * locals and func_00300A00's bank-preserving argument order (x before colour) are allowed by
 * owner rulings (2026-11-08/09). */
#include "common.h"

typedef struct {
    u8 pad[0x1a0];
    int field1a0;
} InputView;
typedef struct {
    u8 pad[4];
    u8 enabled;
    u8 rest[0xdb];
} MenuRecord;
extern u8 *D_L11_001A904C;
extern float D_L11_001B3E04;
extern int D_L11_001B30C8;
extern unsigned char D_00138180[];
extern unsigned char D_00139568[], D_001395B8[];
extern unsigned char D_L11_00279BA0[];
/* The class pointer table is addressed through gp. */
extern int *D_L11_001B14F8[] SDATA(D_L11_001B14F8);
extern void func_L00_0037B7B0(void);
extern int func_00336D50(u8 *, int);
extern void func_00300A00(char *, float, int, float, float, float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern int func_L11_0043E108(unsigned int);
extern int func_00288D58(void);
extern void func_002FC560(unsigned int, unsigned long long);
extern float D_L11_001B161C __attribute__((sda));
extern int D_L11_001B1620 __attribute__((sda));
extern int D_L11_001B1624 __attribute__((sda));
extern int D_L11_001B1628 __attribute__((sda));
extern int D_L11_001B162C __attribute__((sda));
extern int D_L11_001B1630 __attribute__((sda));
extern int D_L11_001B1634 __attribute__((sda));
extern unsigned int D_L11_001B1638 __attribute__((sda));
extern unsigned int D_L11_001B163C __attribute__((sda));
extern unsigned int D_L11_001B1644 __attribute__((sda));
extern unsigned int D_L11_001B1648 __attribute__((sda));

extern int D_L11_001B3E00;

/* label_y: dead-test HUD helper allowed by owner ruling (7 November 2026; precedent
   src/levels/15_gorn/L15_00431590-g8.c); `one` as active per the func_L01_002F1588 ruling. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L11_001B3E00;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

void func_L11_00443940(u8 *object, int enabled)
{
    u8 *state;
    int label, phase, i, one, k3, entry;
    unsigned int color, c;
    float x3, nv, x, fy, pulse, half, sc, z;
    if (D_L11_001A904C == 0) return;
    func_L00_0037B7B0();
    entry = 0x8710;
    state = *(u8 **)(object + 0x68);
    half = 0.5f;

    label = func_00336D50(D_L11_001A904C + entry, 0x49);
    x = (float)D_L11_001B1620;
    one = 1;
    fy = (float)label_y((void *)label, (float)D_L11_001B1624, D_L11_001B3E04, half, one);
    sc = 1.0f;
    z = 0.0f;
    func_00300A00((char *)label, x, D_L11_001B163C, fy, D_L11_001B161C, sc, z);
    label = func_00336D50(D_L11_001A904C + entry, 0x48);
    x = (float)D_L11_001B1620;
    fy = (float)label_y((void *)label, (float)D_L11_001B1624, D_L11_001B3E04, half, 1);
    func_00300A00((char *)label, x, D_L11_001B1638, fy, D_L11_001B161C, sc, z);
    phase = D_L11_001B30C8 % 50;
    if (phase >= 25) pulse = sc - (float)(phase - 25) * 0.04f;
    else pulse = (float)phase * 0.04f;
    color = func_00283D38(D_L11_001B1638, D_L11_001B163C, pulse);
    if (enabled) {
        if (*(short *)(state + 0x1e8) != 0) {
            label = func_00336D50(D_L11_001A904C + 0x8710, 0x4b);
            k3 = 1;
            x3 = (float)D_L11_001B1628;
            c = (((InputView *)D_00138180)->field1a0 & 0x8000) ? D_L11_001B1644 : color;
            fy = (float)label_y((void *)label, (float)D_L11_001B162C, D_L11_001B3E04, 0.5f, k3);
            func_00300A00((char *)label, x3, c, fy, D_L11_001B161C, 1.0f, 0.0f);
        }
        for (i = *(short *)(state + 0x1e8) + 1; i < 13; i++) {
            if (!D_001395B8[func_L11_0043E108(D_L11_001B14F8[i][2])]) continue;
            if (i >= 11 && !func_00288D58()) continue;
            if (i == 8) {
                MenuRecord *choice = (MenuRecord *)(D_L11_00279BA0 + D_00139568[0x1e] * 0xe0);
                if (!choice->enabled) continue;
            }
            label = func_00336D50(D_L11_001A904C + 0x8710, 0x4a);
            one = 1;
            c = (((InputView *)D_00138180)->field1a0 & 0x2000) ? D_L11_001B1648 : color;
            nv = (float)D_L11_001B1630;
            fy = (float)label_y((void *)label, (float)D_L11_001B1634, D_L11_001B3E04, 0.5f, one);
            func_00300A00((char *)label, nv, c, fy, D_L11_001B161C, 1.0f, 0.0f);
            break;
        }
    }
    func_002FC560(0x47, 0x5360b);
}

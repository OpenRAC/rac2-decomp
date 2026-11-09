/* func_L02_003FDDE8: the help-prompt HUD lines (labels 0x49/0x48, then a pulsing colour
 * from func_00283D38, the 0x4b line when the selection is nonzero and the first available
 * 0x4a entry after it). Twin of func_L11_00443940.
 * one/k3 are set-once label_y actives (k3 only in the 0x4b draw, which local-alloc keeps beside
 * the label copy); x3 is that draw's own x. The label_y dead-test helper, set-once constant
 * locals and func_00300A00's bank-preserving argument order (x before colour) are allowed by
 * owner rulings (2026-11-08/09). */
#include "common.h"

typedef struct {
    u8 pad[0x1a0];
    int buttons;
} HelpInput;
typedef struct {
    u8 pad[4];
    u8 available;
    u8 rest[0xdb];
} HelpEntry;

extern u8 *D_L02_001A904C;
extern float D_L02_001B3E04;
extern int D_L02_001B30C8;
extern HelpInput D_00138180;
extern u8 D_00139568[], D_001395B8[];
extern HelpEntry D_L02_00264A70[];
extern u8 *D_L02_001B1190[] SDATA(D_L02_001B1190);

extern void func_L00_0037B7B0(void);
extern int func_00336D50(u8 *, int);
extern void func_00300A00(char *, float, int, float, float, float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern int func_L02_003F9B70(int);
extern int func_00288D58(void);
extern void func_002FC560(unsigned int, unsigned long long);

extern float D_L02_001B1260 __attribute__((sda));
extern int D_L02_001B1264 __attribute__((sda));
extern int D_L02_001B1268 __attribute__((sda));
extern int D_L02_001B126C __attribute__((sda));
extern int D_L02_001B1270 __attribute__((sda));
extern int D_L02_001B1274 __attribute__((sda));
extern int D_L02_001B1278 __attribute__((sda));
extern unsigned int D_L02_001B127C __attribute__((sda));
extern unsigned int D_L02_001B1280 __attribute__((sda));
extern unsigned int D_L02_001B1288 __attribute__((sda));
extern unsigned int D_L02_001B128C __attribute__((sda));

extern int D_L02_001B3E00;

/* label_y: dead-test HUD helper allowed by owner ruling (7 November 2026; precedent
   src/levels/15_gorn/L15_00431590-g8.c); `one` as active per the func_L01_002F1588 ruling. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L02_001B3E00;
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

void func_L02_003FDDE8(u8 *object, int enabled)
{
    u8 *state;
    char *label;
    int phase, i, one, k3, entry;
    unsigned int color, c;
    float x3, nv, x, fy, pulse, half, sc, z;
    HelpEntry *r;

    if (D_L02_001A904C == 0) return;
    func_L00_0037B7B0();
    entry = 0x8710;
    state = *(u8 **)(object + 0x68);
    half = 0.5f;
    label = (char *)func_00336D50(D_L02_001A904C + entry, 0x49);
    x = (float)D_L02_001B1264;
    one = 1;
    fy = (float)label_y(label, (float)D_L02_001B1268, D_L02_001B3E04, half, one);
    sc = 1.0f;
    z = 0.0f;
    func_00300A00(label, x, D_L02_001B1280, fy, D_L02_001B1260, sc, z);
    label = (char *)func_00336D50(D_L02_001A904C + entry, 0x48);
    x = (float)D_L02_001B1264;
    fy = (float)label_y(label, (float)D_L02_001B1268, D_L02_001B3E04, half, 1);
    func_00300A00(label, x, D_L02_001B127C, fy, D_L02_001B1260, sc, z);
    phase = D_L02_001B30C8 % 50;
    if (phase >= 25) pulse = sc - (float)(phase - 25) * 0.04f;
    else pulse = (float)phase * 0.04f;
    color = func_00283D38(D_L02_001B127C, D_L02_001B1280, pulse);
    if (enabled) {
        if (*(short *)(state + 0x118) != 0) {
            label = (char *)func_00336D50(D_L02_001A904C + 0x8710, 0x4b);
            k3 = 1;
            x3 = (float)D_L02_001B126C;
            if (D_00138180.buttons & 0x8000) c = D_L02_001B1288; else c = color;
            fy = (float)label_y(label, (float)D_L02_001B1270, D_L02_001B3E04, 0.5f, k3);
            func_00300A00(label, x3, c, fy, D_L02_001B1260, 1.0f, 0.0f);
        }
        for (i = *(short *)(state + 0x118) + 1; i < 14; i++) {
            if (D_001395B8[func_L02_003F9B70(*(int *)(D_L02_001B1190[i] + 8))] == 0) continue;
            if (i >= 12 && !func_00288D58()) continue;
            if (i == 7) {
                r = &D_L02_00264A70[D_00139568[0x1e]];
                if (r->available == 0) continue;
            }
            if (i == 8) {
                r = &D_L02_00264A70[D_00139568[0x2a]];
                if (r->available == 0) continue;
            }
            label = (char *)func_00336D50(D_L02_001A904C + 0x8710, 0x4a);
            one = 1;
            c = (D_00138180.buttons & 0x2000) ? D_L02_001B128C : color;
            nv = (float)D_L02_001B1274;
            fy = (float)label_y(label, (float)D_L02_001B1278, D_L02_001B3E04, 0.5f, one);
            func_00300A00(label, nv, c, fy, D_L02_001B1260, 1.0f, 0.0f);
            break;
        }
    }
    func_002FC560(0x47, 0x5360b);
}

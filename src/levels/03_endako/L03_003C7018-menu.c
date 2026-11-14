/* func_L03_003C7018 (656 bytes, Endako): the two-line menu panel. Own unit:
 * -O2 -G0 -ffunction-sections -Wa,--r5900-la-addend=sn -frac2-sched2-barrier-hold
 * (config/cflags.txt). label_y/label_y2 are the dead-test rounding helpers allowed by owner
 * ruling (7 November 2026). In draw 2 the loop-note barrier (a cvt.s.w, latency 3) is still
 * pending when the argument loads issue; retail issues only top-priority insns until it
 * completes, which the switch models (docs/build/compiler-notes.md). Owner standard of
 * 12 November 2026; forced on everywhere the switch changes no other function.
 */
#include "common.h"

struct MenuCoordinate { float x, y; };
extern unsigned char *D_L03_001A904C __attribute__((sda));
extern float D_L03_001B014C SDATA(D_L03_001B014C);
extern float D_L03_001B0150 SDATA(D_L03_001B0150);
extern float D_L03_001B0154 SDATA(D_L03_001B0154);
extern float D_L03_001B0158 SDATA(D_L03_001B0158);
extern struct MenuCoordinate D_L03_001B0160[] SDATA(D_L03_001B0160);
extern int D_L03_001B0140 SDATA(D_L03_001B0140);
extern int D_L03_001B3280 __attribute__((sda));
extern float D_L03_001B3284 __attribute__((sda));
extern char D_L03_001B0190[], D_L03_001B0198[];
extern unsigned char D_001A7A7C[] __attribute__((sda));
extern int func_00336D50(unsigned char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern unsigned char *func_00288FB8(int);
extern int func_00115DA8(char *, char *, ...);
extern int func_00283CF0(float);
extern int func_0027FB40(int, int, unsigned long, unsigned char *, int);
extern int func_L00_00443DF8(char *);
extern int func_L00_00443E18(char *);

static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L03_001B3280;
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
static __inline__ int label_y2(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L03_001B3280;
    float scaled = value * scale + half;
    int result = (int)scaled;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = half;
    return result;
}

static __inline__ int screen_coord(int mode, float value, float offset, int one)
{
    float scaled = value * D_L03_001B3284 + 0.5f;

    if (mode == one)
        return (int)(scaled + offset);
    return (int)scaled;
}

int func_L03_003C7018(void)
{
    if (D_L03_001A904C) {
        int one;
        int i;

        {
            char *title;
            float row, x, c, d;

            do {
                title = (char *)func_00336D50(D_L03_001A904C + 0x8710, 0xc6);
                row = (float)label_y(title, D_L03_001B0150, D_L03_001B3284, 0.5f, 1);
                x = D_L03_001B014C;
                c = D_L03_001B0154;
                d = D_L03_001B0158;
            } while (0);
            func_00300A00(title, 0x60442d00, x, row, c, d, 0.0f);
        }
        {
            char *title;
            float row, x, c, d;

            do {
            do {
                title = (char *)func_00336D50(D_L03_001A904C + 0x8710, 0xc7);
                row = (float)label_y2(title, D_L03_001B0150, D_L03_001B3284, 0.5f, 1);
                x = D_L03_001B014C;
                c = D_L03_001B0154;
                d = D_L03_001B0158;
            } while (0);
            do {
                func_00300A00(title, 0x55f0c070, x, row, c, d, 0.0f);
                i = 0;
            } while (0);
            } while (0);
        }
        one = 1;
        {
            int keys[4] = {11599,12116,12769,12770};
            unsigned char buffer[128];
            unsigned char *buf;
            buf = buffer;
            do {
                int shift = 5;
                int x;
                unsigned char *label = func_00288FB8(keys[i]);
                if (i == one) {
                    func_00115DA8((char *)buf, D_L03_001B0190, label, D_L03_001B0140 + 1);
                    shift = -4;
                } else {
                    func_00115DA8((char *)buf, D_L03_001B0198, label);
                }
                x = func_00283CF0(D_L03_001B0160[i].x);
                func_0027FB40(x, func_00283CF0((float)screen_coord(D_L03_001B3280, D_L03_001B0160[i].y, (float)shift, one)), 0x80808080UL, buf, 0x80);
                i++;
            } while (i < 4);
        }
        if (D_001A7A7C[0]) {
            func_L00_00443DF8((char *)D_L03_001A904C + 0x36f28);
            func_L00_00443E18((char *)D_L03_001A904C + 0x36f28);
        }
    }
    return 1;
}

#include "common.h"

/* func_US2_00298AA8: new in USA v2.00, no v1.01 counterpart. On levels 8 and 19 it pulses a marker
 * on the map (an arrow with a shadow, or an icon) over every moby of the classes the level lists. */
typedef struct MapMarkerMoby {
    char pad_00[0x10];
    float x;
    float y;
    char pad_18[0x8];
    unsigned char state;
    char pad_21[0x89];
    short oClass;
    char pad_ac[0x54];
} MapMarkerMoby;

extern int D_001A79F0 MACRO_ADDR;
extern MapMarkerMoby *D_001B18D8 MACRO_ADDR;
extern MapMarkerMoby *D_001B18DC MACRO_ADDR;
extern int D_US2_001A9768[4] __attribute__((sda));
extern int D_US2_001A9778[4] __attribute__((sda));
extern int D_US2_001A9788 __attribute__((sda));
extern int D_US2_001A978C __attribute__((sda));
extern unsigned char D_US2_001A9790 __attribute__((sda));
extern unsigned char D_US2_001A9794 __attribute__((sda));
extern unsigned char D_US2_001A9798 __attribute__((sda));
extern int D_US2_001A979C __attribute__((sda));
extern int D_US2_001A97A0 __attribute__((sda));
extern s32 D_US2_001A97A4 __attribute__((sda));

/* The callers load all five arguments, though this body reads only the two pointers. */
extern int func_00297218(float x, float y, float *u, float *v, int level);
extern void func_00297FE8(float x, float y, float *u, float *v, int level);
extern int func_0028E588(int key, int index);
extern void func_0028F078(int icon, int x, int y, int w, int h, int alpha, unsigned int color);
extern void func_0028FAB8(int x0, int y0, int x1, int y1, u64 color, int flags);

void func_US2_00298AA8(float x0, float x1, float y0, float y1, float scale)
{
    float u;
    float v;
    int *table;
    int color;
    int i;
    int j;
    int y;
    int px;
    float size;
    int icon;
    MapMarkerMoby *m;

    switch (D_001A79F0) {
    case 8:
        table = D_US2_001A9768;
        color = D_US2_001A9788;
        break;
    case 19:
        table = D_US2_001A9778;
        color = D_US2_001A978C;
        break;
    default:
        return;
    }

    D_US2_001A9790 = D_US2_001A979C ? D_US2_001A9790 + D_US2_001A9794 : D_US2_001A9790 - D_US2_001A9798;
    if (D_US2_001A9790 < 0x60 || D_US2_001A9790 > 0xF0) {
        D_US2_001A979C ^= 1;
        if (D_US2_001A9790 > 0xF0) {
            D_US2_001A9790 = 0xF0;
        }
        if (D_US2_001A9790 < 0x30) {
            D_US2_001A9790 = 0x30;
        }
    }

    for (i = 0; table[i] != 0 && i < 10; i++) {
        for (m = D_001B18D8; m < D_001B18DC; m++) {
            if (m == 0 || m->oClass != table[i] || m->state == 0xFE || m->state == 0xFD) {
                continue;
            }
            if (func_00297218(m->x, m->y, &u, &v, D_001A79F0) == 0) {
                func_00297FE8(m->x, m->y, &u, &v, D_001A79F0);
            }
            u = x0 + u * (x1 - x0);
            v = y0 + v * (y1 - y0);
            if (D_001A79F0 == 8) {
                px = (int)u >> 4;
                y = ((int)v >> 4) - 8;
                for (j = 0; j < 3; j++, y++) {
                    func_0028FAB8(px - D_US2_001A97A0 - j + D_US2_001A97A4, y + D_US2_001A97A4,
                                  px + D_US2_001A97A0 + j + D_US2_001A97A4, y + D_US2_001A97A4,
                                  (D_US2_001A9790 << 23) | 0x80000000, 0);
                }
                for (j = 0; j < 5; j++, y++) {
                    func_0028FAB8(px - D_US2_001A97A0 + j + D_US2_001A97A4, y + D_US2_001A97A4,
                                  px + D_US2_001A97A0 - j + D_US2_001A97A4, y + D_US2_001A97A4,
                                  (D_US2_001A9790 << 23) | 0x80000000, 0);
                }
                y = ((int)v >> 4) - 8;
                for (j = 0; j < 3; j++, y++) {
                    func_0028FAB8(px - D_US2_001A97A0 - j, y, px + D_US2_001A97A0 + j, y,
                                  color | (D_US2_001A9790 << 23), 0);
                }
                for (j = 0; j < 5; j++, y++) {
                    func_0028FAB8(px - D_US2_001A97A0 + j, y, px + D_US2_001A97A0 - j, y,
                                  color | (D_US2_001A9790 << 23), 0);
                }
            } else {
                icon = func_0028E588(0xE99E, 0);
                size = scale * 128.0f;
                func_0028F078(icon, u, v, size + 24.0f, size + 24.0f, D_US2_001A9790, 0x80000000);
                func_0028F078(func_0028E588(0xE99E, 0), u, v, size, size, D_US2_001A9790, color);
            }
        }
    }
}

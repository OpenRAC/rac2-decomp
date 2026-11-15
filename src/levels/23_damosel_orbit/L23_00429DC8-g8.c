#include "include_asm.h"
#include "names.h"

/* func_L23_00429DC8 is a unit of its own: retail clears its start vector as plain C, with the
   zero materialised (`por $v0,$zero,$zero` ... `sq $v0,0($sp)`), which -frac2-zero-ti-por keeps,
   and copies it with the grouped quadword copy and its scheduling barrier (-frac2-qcopy
   -frac2-qcopy-barrier; config/cflags.txt). */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef int TI128 __attribute__((mode(TI)));

typedef union { TI128 q; float f[4]; } V4;

/* the globals it arms, and the list it fills */
extern s16 D_L23_001B1B94 __attribute__((sda));
extern s16 D_L23_001B1B96 __attribute__((sda));
extern s32 D_L23_001B1B98 __attribute__((sda));
extern s32 D_L23_001B3934[4] __attribute__((sda));
extern s32 D_L23_001B3938[4] __attribute__((sda));
extern s32 D_L23_001B3934_2[4] __attribute__((sda)); /* the same word as D_L23_001B3934 */
extern s32 D_L23_001B3980[16] __attribute__((sda));
extern float D_L23_002A7170[][4];
extern s32 D_L23_0025E8B0[];
typedef struct { s16 a; s16 b; s32 c; } Edge; /* 8 bytes; the array is walked through an s16 cast */
extern Edge D_L23_002A7A74[];
extern s32 D_L23_0025E9D0[];
extern void func_002A7750(void *, s32, s32);

/* arms the object once: clears the list, builds the 500/500/575 start position and the 16 slots
   (the count, spread over the list of used edges, scaled by sixteenths) */
/* Sets up the controller object the first time it runs. It places it, counts which links
   between points are in use, and fills a table of 16 steps. */
void func_L23_00429DC8(u8 *obj) {
    s32 *payload = *(s32 **)(obj + 0x68);
    s32 i, j, k, m, n, found;
    V4 v;

    if (obj[0x20] == 0) {
        D_L23_001B3934_2[0] = 0;
        D_L23_001B1B96 = -1;
        D_L23_001B1B94 = -1;
        D_L23_001B1B98 = 0;
        D_L23_001B3938[0] = 0;
        *(s16 *)(obj + 0x32) = 0x50;
        obj[0x30] = 0xFF;
        payload[0] = 0;
        payload[2] = 0;
        payload[1] = 0;
        v.q = 0;
        v.f[0] = 500.0f;
        v.f[1] = 500.0f;
        v.f[2] = 575.0f;
        *(TI128 *)(obj + 0x10) = v.q;
        SetMobyState(obj, 1, 0);
        for (i = 0; i < 0x48; i++) {
            float *p = D_L23_002A7170[i];

            if (0.0f < p[2]) {
                D_L23_0025E8B0[i] = 1;
                for (j = 0; j < 0x9C; j++) {
                    if (((s16 *)D_L23_002A7A74)[j * 4] == i || ((s16 *)D_L23_002A7A74)[j * 4 + 1] == i) {
                        n = D_L23_001B3934[0];
                        found = 0;
                        for (k = 0; k < n; k++) {
                            if (D_L23_0025E9D0[k] == j) {
                                found = 1;
                                break;
                            }
                        }
                        if (!found) {
                            D_L23_0025E9D0[D_L23_001B3934[0]] = j;
                            D_L23_001B3934_2[0] = D_L23_001B3934[0] + 1;
                        }
                    }
                }
            } else {
                D_L23_0025E8B0[i] = 0;
            }
        }
        {
            s32 count = D_L23_001B3934_2[0];

            for (m = 0; m < 16; m++) {
                D_L23_001B3980[m] = (m * count) / 16;
            }
        }
    }
}

#include "common.h"
typedef int s128 __attribute__((mode(TI)));

extern char D_00189E20[];
extern char D_00189EA0[];
extern u8 D_001A7B0C __attribute__((sda));
extern s32 func_L00_002AD868(void *, void *, void *, void *, void *, void *, void *, s32, s32);

/* Finds a nearby grind rail and records its contact point and rail parameters. */
void func_L00_002ADB40(void)
{
    struct { float contact[4]; float position[4]; s32 rail; s32 segment; float parameter; s32 kind; } fr __attribute__((aligned(16)));
    char *h;
    char *b;
    char *h2;
    s32 m;
    float gap;

    if (D_001A7B0C != 0) {
        h = D_00189E20;
        *(s32 *)(h + 0x63C) = 0;
        if (*(short *)(h + 0x1F4) == 0) {
            m = *(s32 *)(h + 0x229C);
            if (m == 2 || m == 0 || m == 1 || m == 6)
                goto call;
            m = *(s32 *)(h + 0x2294);
            if (m == 1)
                goto call;
            if ((unsigned)(m - 0x28) < 2 && (*(s32 *)(h + 0x640) != 0 || *(s32 *)(h + 0x694) != 0))
                goto call;
            if (*(s32 *)(h + 0x229C) == 4 && (*(u8 *)(h + 0x49E) != 0 || *(short *)(h + 0x1F6) != 0))
                goto call;
            return;
call:
            *(s128 *)fr.position = *(s128 *)D_00189EA0;
            if (nearest_rail_point(fr.position, &fr.rail, fr.contact, &fr.segment, &fr.parameter, &fr.kind, 0, 0, 0) != 0) {
                b = D_00189EA0 - 0x80;
                if (*(s32 *)(b + 0x2294) == 0x28 && *(s32 *)(b + 0x694) != 0 && fr.rail == *(s32 *)(b + 0x630))
                    return;
                h2 = D_00189E20;
                gap = *(float *)(h2 + 0x88) - fr.contact[2];
                if (gap > -0.5f && (gap < 0.57f || *(short *)(h2 + 0x1F6) != 0)) {
                    qcopy(h2 + 0x5D0, fr.contact);
                    *(s32 *)(h2 + 0x630) = fr.rail;
                    *(s32 *)(h2 + 0x634) = fr.segment;
                    *(float *)(h2 + 0x638) = fr.parameter;
                    *(s32 *)(h2 + 0x654) = fr.kind;
                    *(s32 *)(h2 + 0x63C) = 1;
                }
            }
        }
    }
}

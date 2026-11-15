#include "common.h"
typedef int s128 __attribute__((mode(TI)));

extern char D_00189E20[];
extern char D_00189EA0[];
extern u8 D_001A7B0C __attribute__((sda));
extern s32 func_L00_002AD868(void *, void *, void *, void *, void *, void *, void *, s32, s32);

/* Finds a nearby grind rail and records its contact point and rail parameters. */
void func_L00_002ADB40(void)
{
    struct { float contact[4]; float position[4]; s32 rail; s32 segment; float parameter; s32 kind; } probe __attribute__((aligned(16)));
    char *hero;
    char *heroBase;
    char *heroRefreshed;
    s32 modeValue;
    float gap;

    if (D_001A7B0C != 0) {
        hero = gHeroState;
        *(s32 *)(hero + 0x63C) = 0;
        if (*(short *)(hero + 0x1F4) == 0) {
            modeValue = *(s32 *)(hero + 0x229C);
            if (modeValue == 2 || modeValue == 0 || modeValue == 1 || modeValue == 6)
                goto call;
            modeValue = *(s32 *)(hero + 0x2294);
            if (modeValue == 1)
                goto call;
            if ((unsigned)(modeValue - 0x28) < 2 && (*(s32 *)(hero + 0x640) != 0 || *(s32 *)(hero + 0x694) != 0))
                goto call;
            if (*(s32 *)(hero + 0x229C) == 4 && (*(u8 *)(hero + 0x49E) != 0 || *(short *)(hero + 0x1F6) != 0))
                goto call;
            return;
call:
            *(s128 *)probe.position = *(s128 *)gHeroPosition;
            if (nearest_rail_point(probe.position, &probe.rail, probe.contact, &probe.segment, &probe.parameter, &probe.kind, 0, 0, 0) != 0) {
                heroBase = gHeroPosition - 0x80;
                if (*(s32 *)(heroBase + 0x2294) == 0x28 && *(s32 *)(heroBase + 0x694) != 0 && probe.rail == *(s32 *)(heroBase + 0x630))
                    return;
                heroRefreshed = gHeroState;
                gap = *(float *)(heroRefreshed + 0x88) - probe.contact[2];
                if (gap > -0.5f && (gap < 0.57f || *(short *)(heroRefreshed + 0x1F6) != 0)) {
                    qcopy(heroRefreshed + 0x5D0, probe.contact);
                    *(s32 *)(heroRefreshed + 0x630) = probe.rail;
                    *(s32 *)(heroRefreshed + 0x634) = probe.segment;
                    *(float *)(heroRefreshed + 0x638) = probe.parameter;
                    *(s32 *)(heroRefreshed + 0x654) = probe.kind;
                    *(s32 *)(heroRefreshed + 0x63C) = 1;
                }
            }
        }
    }
}

#include "common.h"
typedef int s128 __attribute__((mode(TI)));

extern char g_hero_state[];
extern char g_hero_position[];
extern u8 D_001A7B0C __attribute__((sda));
extern s32 nearest_rail_point(void *, void *, void *, void *, void *, void *, void *, s32, s32);

/* Finds a nearby grind rail and records its contact point and rail parameters. */
void FindGrindRail(void)
{
    struct { float contact[4]; float position[4]; s32 rail; s32 segment; float parameter; s32 kind; } probe __attribute__((aligned(16)));
    char *hero;
    char *hero_base;
    char *hero_refreshed;
    s32 mode_value;
    float gap;

    if (D_001A7B0C != 0) {
        hero = g_hero_state;
        *(s32 *)(hero + 0x63C) = 0;
        if (*(short *)(hero + 0x1F4) == 0) {
            mode_value = *(s32 *)(hero + 0x229C);
            if (mode_value == 2 || mode_value == 0 || mode_value == 1 || mode_value == 6)
                goto call;
            mode_value = *(s32 *)(hero + 0x2294);
            if (mode_value == 1)
                goto call;
            if ((unsigned)(mode_value - 0x28) < 2 && (*(s32 *)(hero + 0x640) != 0 || *(s32 *)(hero + 0x694) != 0))
                goto call;
            if (*(s32 *)(hero + 0x229C) == 4 && (*(u8 *)(hero + 0x49E) != 0 || *(short *)(hero + 0x1F6) != 0))
                goto call;
            return;
call:
            *(s128 *)probe.position = *(s128 *)g_hero_position;
            if (nearest_rail_point(probe.position, &probe.rail, probe.contact, &probe.segment, &probe.parameter, &probe.kind, 0, 0, 0) != 0) {
                hero_base = g_hero_position - 0x80;
                if (*(s32 *)(hero_base + 0x2294) == 0x28 && *(s32 *)(hero_base + 0x694) != 0 && probe.rail == *(s32 *)(hero_base + 0x630))
                    return;
                hero_refreshed = g_hero_state;
                gap = *(float *)(hero_refreshed + 0x88) - probe.contact[2];
                if (gap > -0.5f && (gap < 0.57f || *(short *)(hero_refreshed + 0x1F6) != 0)) {
                    qcopy(hero_refreshed + 0x5D0, probe.contact);
                    *(s32 *)(hero_refreshed + 0x630) = probe.rail;
                    *(s32 *)(hero_refreshed + 0x634) = probe.segment;
                    *(float *)(hero_refreshed + 0x638) = probe.parameter;
                    *(s32 *)(hero_refreshed + 0x654) = probe.kind;
                    *(s32 *)(hero_refreshed + 0x63C) = 1;
                }
            }
        }
    }
}

/* 28 October 2026: 900/916 bytes with -O2 -G8 -ffunction-sections.
 * Five compiles: shared-address nibble updates were 836 bytes;
 * branch-scoped addresses reach 900. Retail preserves the counter high
 * address in s2 across the proximity path; this source rebuilds it.
 * enabled is a real measured field reloaded after the counter test
 * even on paths without a call. Inlining/address grouping tie.
 * Extern returns checked against definitions or retail return banks.
 * No strict/local match. Reopen with pointer lifetime/CFG evidence.
 *
 * closer D, later: enabled needs no volatile; every read stays state->enabled, and cse threads the !enabled path to
 * the end of the case (retail's beqz a1,+0x8E), so the reload at the last test is only the block after the counter
 * path. Retail has no activate = 0 at all, a1 = 1 on every edge into the first activation, and sb a1,0xBC there, so
 * object[0xBC] = activate. The high half of D_0019B4A8 is PRE's copy in s2, which needs the threaded CFG. if/else
 * leaves, gotos and an inline flare_triggered() (916 bytes) do not thread as retail does: 127 to 134 words.
 */
#include "common.h"

extern float func_002A7940(void);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern float func_00282E80(void *, void *);
extern int func_002E5CF8(int, int, char *);
extern int D_001A79F0 __attribute__((sda));
extern unsigned char D_0019B2E8[];
extern unsigned char D_0019B4A8[];
extern unsigned char D_L09_0021E9F0[];
extern char *D_L09_001B0834;
extern char *D_L09_001B1648;
extern struct {
    char reserved00[0x33C];
    char *owner;
    char reserved340[0xE];
    short locked;
} D_00189E20;



/* Retail reloads enabled after the counter test even without a call. */
typedef struct { float angle; volatile int enabled; } FlareState;

void func_L09_0041A700(char *object)
{
    FlareState *state = *(FlareState **)(object + 0x68);
    float point[4] __attribute__((aligned(16)));
    int color;
    int activate;
    unsigned short index;
    unsigned char counter;
    char *target;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        state->angle = func_002A7940();
        *(unsigned char *)(object + 0x20) = 1;
        *(float *)(object + 0x18) -= 0.35f;
        break;
    case 1:
        state->angle = func_00283B98(state->angle, 0.10471977f);
        color = func_00283CF0((func_00283198(state->angle) * 4.0f - 3.0f) * 128.0f);
        if (color > 128) color = 128;
        else if (color < 32) color = 32;
        *(unsigned int *)(object + 0x78) = (color << 16) | (0x80000000 | (color << 8)) | color;
        activate = 0;
        if (D_00189E20.owner == object && !D_00189E20.locked) {
            activate = 1;
        } else {
            int selected = D_0019B2E8[D_001A79F0 * 16 + *(unsigned char *)(object + 0xB0)] & 0x80;
            int enabled = state->enabled;
            if (selected && !enabled) activate = 1;
            else if (enabled) {
                index = *(unsigned short *)(object + 0xB2);
                if (D_L09_0021E9F0[(short)index + 0x464]) {
                    activate = 1;
                } else {
                    counter = D_0019B4A8[D_001A79F0 * 1024 + ((short)index >> 1)];
                    if (index & 1) counter >>= 4;
                    if (counter & 7) activate = 1;
                }
            }
        }
        if (activate) {
            object[0xBC] = 1;
            object[0x20] = 2;
            *(unsigned int *)(object + 0x78) = 0x80208020;
            func_002E5CF8(0, 0, object);
            index = *(unsigned short *)(object + 0xB2);
            if (index & 1) {
                unsigned char *entry = &D_0019B4A8[D_001A79F0 * 1024 + ((short)index >> 1)];
                if (((*entry >> 4) & 7) != 7) *entry += 16;
            } else {
                unsigned char *entry = &D_0019B4A8[D_001A79F0 * 1024 + ((short)index >> 1)];
                if ((*entry & 7) != 7) *entry += 1;
            }
        }
        if (state->enabled) {
            target = D_L09_001B0834;
            if (!target) target = D_L09_001B1648;
            if (target) {
                qcopy(point, object + 0x10);
                point[2] += 0.35f;
                if (func_00282E80(point, target + 0x10) < 0.5f) {
                    index = *(unsigned short *)(object + 0xB2);
                    if (index & 1) {
                        unsigned char *entry = &D_0019B4A8[D_001A79F0 * 1024 + ((short)index >> 1)];
                        if (((*entry >> 4) & 7) != 7) *entry += 16;
                    } else {
                        unsigned char *entry = &D_0019B4A8[D_001A79F0 * 1024 + ((short)index >> 1)];
                        if ((*entry & 7) != 7) *entry += 1;
                    }
                    object[0xBC] = 1;
                    object[0x20] = 2;
                    *(unsigned int *)(object + 0x78) = 0x80208020;
                    func_002E5CF8(0, 0, object);
                }
            }
        }
        break;
    }
}

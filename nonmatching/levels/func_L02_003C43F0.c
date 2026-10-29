/* Retained platform-menu drawing,2026-10-28: best744/752B,0/2US.
 * Four bounded trials. Default736/frame60; no-split-addresses744/frame50;
 * narrow no-force-mem and broader no-gcse both tie744, rejected. Stop after
 * three identical outputs. Retail uses frame40 and reloads literal258F12;
 * C caches258 in an extra savedFP register, changing FP allocation/scheduling.
 * Required best profile -O2 -G0 -ffunction-sections -mno-split-addresses.
 * Real caller pairs3C32EC/3C3798/3C3AE0/3C3E8C register this target through
 * void draw-callback queue L00_002E6CF0, corroborated by its matched definition.
 * Registry lookup00336D50 actuals32return is cast towidgetpointer. Widget draw
 * actualvoid signature has twoGPR/fiveFP; fontdraw actualint has64-bit style.
 * No local buffer/extents invented: dynamic registry count at+18 and8B rows.
 */
#include "common.h"
extern s32 func_00336D50(u8 *, s32);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern void func_002FC560(unsigned int, u64);
extern s32 func_00288FB8(s32);
extern int func_0027FBD8(int, int, u64, u8 *, int);
extern u8 *D_001A904C NOT_SDA;
extern float D_L02_001B3E04 NOT_SDA;

/* Registered as a void draw callback by the four actual callers in3C26F0.
 * Registry lookup returns a32-bit target address; widget drawing takes two
 * GPRs and five floats. Font style remains64-bit through the canonical API.
 * Registry owner extent is open: header+8710 has count18 and dynamic8B rows. */
void func_L02_003C43F0(u8 *object)
{
    char *widget;
    u8 *text;
    int state;
    widget = (char *)func_00336D50(D_001A904C + 0x8710, 0x70);
    func_00300A00(widget, 0x60442D00, 258.0f, (float)(int)(D_L02_001B3E04 * 203.0f + 0.5f), 1.0f, 1.0f, 0.0f);
    widget = (char *)func_00336D50(D_001A904C + 0x8710, 0x6F);
    func_00300A00(widget, 0x60442D00, 258.0f, (float)(int)(D_L02_001B3E04 * 203.0f + 0.5f), 1.0f, 1.0f, 0.0f);
    widget = (char *)func_00336D50(D_001A904C + 0x8710, 0x71);
    func_00300A00(widget, 0x55F0C070, 258.0f, (float)(int)(D_L02_001B3E04 * 203.0f + 0.5f), 1.0f, 1.0f, 0.0f);
    widget = (char *)func_00336D50(D_001A904C + 0x8710, 0x72);
    func_00300A00(widget, 0x55F0C070, 258.0f, (float)(int)(D_L02_001B3E04 * 203.0f + 0.5f), 1.0f, 1.0f, 0.0f);
    func_002FC560(0x47, 0x5360BULL);
    state = object[0x20];
    if (state == 7) {
        text = (u8 *)func_00288FB8(0x2F5C);
        func_0027FBD8(254, (int)(D_L02_001B3E04 * 23.0f + 0.5f), 0x88FFFFFFULL, text, -1);
    } else if (state != 8 && state != 5) {
        text = (u8 *)func_00288FB8(0x2F5B);
        func_0027FBD8(262, (int)(D_L02_001B3E04 * 23.0f + 0.5f), 0x88FFFFFFULL, text, -1);
    }
    text = (u8 *)func_00288FB8(0x2F5A);
    func_0027FBD8(254, (int)(D_L02_001B3E04 * 373.0f + 0.5f), 0x88FFFFFFULL, text, -1);
}

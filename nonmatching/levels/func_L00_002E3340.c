/* 28 October 2026: 476/476 bytes, all27 US places differ only at
 * +0x1A0: compiler lui a1,0xFFFF; dsrl32 versus retail addiu
 * a1,zero,-1; dsrl32. Both yield the same64-bit 0xFFFFFFFF style.
 * Four checks. Retain the truthful unsigned-long64-bit style contract;
 * no narrowing workaround. MACRO_ADDR on the height word closes
 * the extra saved base/frame and makes all other instructions agree.
 * FontPrint accesses layout offsets0..0x17; 802E0 initializes all12
 * halfwords before each draw, including fields FontPrint mutates.
 * 798A0/2E36F8 return int; DE50/802E0/80190 return void from existing
 * C or retail. No local/strict match. Reopen only with an independent
 * assembler/oracle or source constant-class explanation.
 * Profile: default -O2 -G0 -ffunction-sections. */
#include "common.h"

typedef struct {
    int reserved00, firstKey;
    char reserved08[0xC];
    int origin;
    int reserved18, reserved1C, step, reserved24;
} TextGroup;
typedef struct {
    char reserved00[0x20];
    short group;
    char reserved22[0x384 - 0x22];
    int anchor;
} TextContextPrefix;

extern TextGroup D_L00_001BC588[];
extern char D_L00_001BC200[];
extern int D_001A7340 MACRO_ADDR;
extern int func_002798A0(int, int *, int *);
extern int func_L00_002E36F8(int);
extern void func_0027DE50(int, int, int, int, u64);
extern void func_002802E0(unsigned short *, int, int, int, int, int, int, int, int);
extern void func_00280190(unsigned short *, unsigned long, unsigned char *, int);

/* The layout constructor initializes all twelve halfwords consumed by FontPrint. */
void func_L00_002E3340(int row, float alpha)
{
    unsigned short layout[12];
    int group, index;
    unsigned char *text;
    TextContextPrefix *context;
    int origin;
    if (!func_002798A0(row, &group, &index)) return;
    text = (unsigned char *)func_L00_002E36F8(D_L00_001BC588[group].firstKey + index);
    if (!text) return;
    context = (TextContextPrefix *)D_L00_001BC200;
    origin = D_L00_001BC588[context->group].origin + row * D_L00_001BC588[context->group].step;
    func_0027DE50(origin + 2, origin + D_L00_001BC588[context->group].step - 2,
        0, D_001A7340, (u64)((int)(alpha * 96.0f) << 24));
    func_002802E0(layout, origin, origin + D_L00_001BC588[context->group].step, 0,
        D_001A7340, D_001A7340 / 2 + 2,
        origin + D_L00_001BC588[context->group].step / 2 + 1, context->anchor, 3);
    func_00280190(layout, 0x80000000UL, text, -1);
    func_002802E0(layout, origin, origin + D_L00_001BC588[context->group].step, 0,
        D_001A7340, D_001A7340 / 2,
        origin + D_L00_001BC588[context->group].step / 2, context->anchor, 3);
    func_00280190(layout, 0xFFFFFFFFUL, text, -1);
}

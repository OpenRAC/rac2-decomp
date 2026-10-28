/* Nonmatching USA592/608 bytes, 0/27 placements, frame50/40. Six bounded
 * checks: initial shared row/alpha locals596 frame50; separate loop scopes and
 * scalar macro address596 frame40; switch/independent view576 frame40;
 * direct second-mode owner fields592 frame50; opaque canonical owner and -g
 * tie the592-byte form. No flags retained. Remaining owner-base lifetimes,
 * dispatch/loop placement and FP temporary scheduling require source evidence.
 *
 * True contracts checked: FCB00 returns a packed signed64 texture descriptor
 * (current C definition); C540/C660/DDC0 void; 83CF0 signed32 fromfloat;
 * E3520/E2C30 void with the measured inputs and no stable return in retail;
 * E3340 void(int,float). The upload return is deliberately not narrowed/void.
 * The40-byte descriptor stride is shared with the independently reconstructed
 * E3340. The context prefix reaches373; its buffers remain opaque external
 * storage, passed at+10 for a512x416 upload. No local packet or vector allocation.
 * Current RAC1 debug-menu/text and capture-scrolling-text families inspected;
 * no equivalent donor body. Reopen on original context/descriptor-owner views.
 */
#include "common.h"

typedef struct {
    char reserved00[0x18];
    int style, count, step, duration;
} TextRenderGroup;
typedef struct {
    unsigned char *buffers[2];
    char reserved08[0x14];
    short bufferIndex, reserved1E, group, reserved22, active;
    char reserved26[2];
    int tick;
    char reserved2C[0x36C - 0x2C];
    int rowDelay, fadeDuration;
} TextRenderContextPrefix;
extern unsigned char D_L00_001BC200[];
extern TextRenderGroup D_L00_001BC588[];
extern int D_001A72DC MACRO_ADDR;
extern float D_001B18E0 MACRO_ADDR;
extern void func_0027C540(int);
/* The real upload helper returns its packed64-bit texture descriptor. */
extern long long func_002FCB00(int, int, int, int);
extern void func_L00_002E3520(void);
extern void func_L00_002E3340(int, float);
extern void func_L00_002E2C30(int, float);
extern void func_0027C660(void);
extern int func_00283CF0(float);
extern void func_0027DDC0(int, int, int, int);

void func_L00_002E2958(void)
{
    TextRenderContextPrefix *context = (TextRenderContextPrefix *)D_L00_001BC200;
    int style;
    if (!context->active)
        return;
    func_0027C540(0);
    func_002FCB00((int)(context->buffers[(short)(context->bufferIndex ^ 1)] + 0x10),
                 D_001A72DC, 512, 416);
    func_L00_002E3520();
    style = D_L00_001BC588[context->group].style;
    switch (style) {
    case 0: {
        int row;
        float alpha;
        for (row = 0; row < D_L00_001BC588[context->group].count; row++) {
            if (D_L00_001BC588[context->group].duration < context->tick * 2) {
                float remainder = 1.0f - (float)context->tick /
                    (float)D_L00_001BC588[context->group].duration;
                alpha = remainder + remainder;
            } else {
                alpha = 1.0f;
            }
            func_L00_002E3340(row, alpha);
        }
        break;
    }
    case 1:
    case 2: {
        int row, next;
        for (row = 0; row < D_L00_001BC588[((TextRenderContextPrefix *)D_L00_001BC200)->group].count; row = next) {
            next = row + 1;
            func_L00_002E2C30(row, 1.0f - ((float)((TextRenderContextPrefix *)D_L00_001BC200)->tick -
                (float)(D_L00_001BC588[((TextRenderContextPrefix *)D_L00_001BC200)->group].count - next) * (float)((TextRenderContextPrefix *)D_L00_001BC200)->rowDelay) /
                (float)((TextRenderContextPrefix *)D_L00_001BC200)->fadeDuration);
        }
        break;
    }
    }
    func_0027C660();
    func_0027DDC0(0, 0, 0, func_00283CF0(D_001B18E0 * 128.0f));
}

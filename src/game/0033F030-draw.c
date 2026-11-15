#include "names.h"
/* Draws the active menu, including eight widgets of each virtual-draw layout.
 * This unit disables GCSE to retain the two loops' separate cursor setup. */
extern int D_00138344[];
extern char *D_001A8CFC[] __attribute__((sda));
extern int func_002A9588(int, int, int, int, int);
extern int *func_00335E20(void *);
extern float *func_00335E18(void *);
extern void func_00336320(void *);
extern void func_00336A78(void *);
extern void func_00335E68(void *, int);
extern void func_00340638(void *);
extern void func_00340498(void *);
extern void func_0034E2E0(void *, int, int, int);
typedef struct {
    char reserved00[8];
    short adjustment;
    short reserved0A;
    void (*draw)(void *);
} DrawMethod;
/* Draws the radial menu with its eight item slots and eight icons, when the menu is open. */
void func_00340250(char *self)
{
    char *widget214, *widget2A8, *widget2F4, *recordCursor, *iconCursor, *cursorWidget, *recordMethodSlot, *iconMethodSlot;
    int i, j;
    float *pos;
    int *color;
    if (*(int *)(self+0xA58)) {
        if (D_00138344[0]&0xF000) PingPongBlendValues(0,0,1,1,1);
        widget214=self+0x214; widget2A8=self+0x2A8; widget2F4=self+0x2F4;
        color=GetFieldC(widget214);
        cursorWidget=self+0x5A0;
        *color=PingPongBlendValues(0x60442D00,0x70FFFEED,20,1,0);
        recordCursor=self+0x340;
        DrawScreenElementAtStoredPosition(self);
        recordMethodSlot=self+0x370;
        DrawScreenElementAtStoredPosition(self+0x4C);
        DrawScreenElementAtStoredPosition(self+0xE4);
        DrawScreenElementAtStoredPosition(self+0x130);
        DrawAlignedTextLabel(self+0x828);
        DrawAlignedTextLabel(self+0x8B8);
        DrawAlignedTextLabel(self+0x900);
        DrawAlignedTextLabel(self+0x948);
        DrawAlignedTextLabel(self+0x990);
        SetFlagValue(self+0x870,0);
        DrawRadialMenuInfoPanelPage2(self);
        DrawRadialMenuInfoPanelLeft(self);
        DrawScreenElementAtStoredPosition(widget214);DrawScreenElementAtStoredPosition(widget2A8);DrawScreenElementAtStoredPosition(widget2F4);
        pos=GetSecondField(widget2A8); *pos=-*pos;
        pos=GetSecondField(widget2F4); *pos=-*pos;
        DrawScreenElementAtStoredPosition(widget2A8);DrawScreenElementAtStoredPosition(widget2F4);
        pos=GetSecondField(widget2A8); *pos=-*pos;
        pos=GetSecondField(widget2F4); *pos=-*pos;
        for(i=7;i>=0;i--,recordCursor+=0x4C,recordMethodSlot+=0x4C) {
            DrawMethod *method=*(DrawMethod **)recordMethodSlot;
            method->draw(recordCursor+method->adjustment);
        }
        iconCursor=self+0x5EC;iconMethodSlot=self+0x61C;
        for(j=7;j>=0;j--,iconCursor+=0x3C,iconMethodSlot+=0x3C) {
            DrawMethod *method=*(DrawMethod **)iconMethodSlot;
            method->draw(iconCursor+method->adjustment);
        }
        DrawScreenElementAtStoredPosition(cursorWidget);
        *GetFieldC(cursorWidget)=0x80FFDE8D;
        LayoutRadialMenuItems(D_001A8CFC[0]+0x36F28,0xF3,0x2B,0x70);
    }
}

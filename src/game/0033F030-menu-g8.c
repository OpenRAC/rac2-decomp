#include "include_asm.h"
#include "names.h"

typedef struct { float x, y; } Pair;
typedef struct { int value; } MenuColor;
extern Pair D_001AE048[], D_001AE050[], D_001AE058[], D_001AE060[], D_001AE068[], D_001AE070[];
typedef struct { int value; char pad[20]; int id; } Item;
typedef struct { Item *items; } Items;
extern Items *D_001B18D4;
extern char *D_001A8CFC;
extern unsigned char D_00139568[];
extern int D_00139868[];
extern char D_00239BA0[];
extern struct { char pad[0x1C4]; int buttons; } D_00138180;
extern void *func_00115484(void *, int, unsigned int);
extern void func_00335E38(void *, float, float, float, float);
extern void func_00335E68(void *, int);
extern void func_00336920(void *, int, int);
extern char *func_0034E5B8(void *);
extern void func_00336F20(int, int *, int *, int *);
extern int *func_00335E20(void *);
extern void func_00336498(void *, int, int);
extern void func_00336B90(void *, int);
extern void func_00336B98(void *, int);
extern int func_002E5E58(int, int, void *);
extern void func_003409C8(void *, int);
extern void func_00340B70(void *, int);
extern unsigned int func_002A9588(unsigned int, unsigned int, int, int, int);
extern void func_003363C0(void *, float);
/* Updates the eight item rows, their colors and the current menu selection. */
int func_0033FB98(char *self, int buttons)
{
    Pair offset0, offsetE4, offset130, offset4C, offset828, offset900, offset8B8, offset948, offset990, offsetCursor;
    MenuColor firstColor, secondColor, textColor;
    int i;
    char *child;
    memset(&offset0,0,8);
    memset(&offsetE4,0,8);
    memset(&offset130,0,8);
    memset(&offset4C,0,8);
    offset828 = D_001AE048[0];
    offset900 = D_001AE050[0];
    offset8B8 = D_001AE058[0];
    offset948 = D_001AE060[0];
    offset990 = D_001AE068[0];
    SetFirstFloat4(self + 0x0, offset0.x + (*(Pair **)(self+0x80C))->x, offset0.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    SetFirstFloat4(self + 0x4C, offset4C.x + (*(Pair **)(self+0x80C))->x, offset4C.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    SetFirstFloat4(self + 0xE4, offsetE4.x + (*(Pair **)(self+0x80C))->x, offsetE4.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    SetFirstFloat4(self + 0x130, offset130.x + (*(Pair **)(self+0x80C))->x, offset130.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    SetFirstFloat4(self + 0x828, offset828.x + (*(Pair **)(self+0x80C))->x, offset828.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    SetFirstFloat4(self + 0x8B8, offset8B8.x + (*(Pair **)(self+0x80C))->x, offset8B8.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    SetFirstFloat4(self + 0x900, offset900.x + (*(Pair **)(self+0x80C))->x, offset900.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    SetFirstFloat4(self + 0x948, offset948.x + (*(Pair **)(self+0x80C))->x, offset948.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    SetFirstFloat4(self + 0x990, offset990.x + (*(Pair **)(self+0x80C))->x, offset990.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    offsetCursor=D_001AE070[0];
    SetFirstFloat4(self + 0x2A8, offsetCursor.x + (*(Pair **)(self+0x80C))->x, offsetCursor.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    SetFirstFloat4(self + 0x2F4, offsetCursor.x + (*(Pair **)(self+0x80C))->x, offsetCursor.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    SetFirstFloat4(self + 0x5A0, offsetCursor.x + (*(Pair **)(self+0x80C))->x, offsetCursor.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    if (gRadialMenuPages) {
        int resourceOffset;
        i=0;
        resourceOffset = 0x36F28;
        for (child = self + 0x5EC; i < 8; child += 0x3C, i++) {
            char *bar, *row;
            if (!gRadialMenuPages->items[i].value) SetFlagValue(child,0);
            else {
                SetFlagValue(child,1);
                SetWidgetValuePair(child,gRadialMenuPages->items[i].value,0);
            }
            bar=ReturnArgument_0034E5B8(D_001A8CFC+resourceOffset)+i*0x48;
            SetFlagValue(bar,0);
            firstColor.value = 0;
            secondColor.value = 0;
            textColor.value = 0;
            ChooseItemColors(gRadialMenuPages->items[i].id,&firstColor.value,&secondColor.value,&textColor.value);
            {
                int *primary = GetFieldC(child);
                *primary = (*primary & 0xFF000000) | (textColor.value & 0xFFFFFF);
            }
            bar=ReturnArgument_0034E5B8(D_001A8CFC+resourceOffset)+i*0x48;
            SetFlagValue(bar,1);
            SetFirstPair(bar,firstColor.value,secondColor.value);
            SetMeterMaximum(bar,100);
            SetMeterValue(bar,100);
            row=gWeaponTable_00239BA0+gItemSlotToRecord[gRadialMenuPages->items[i].id]*224;
            if (*(int *)row) {
                int active = (unsigned char)row[4] != 0;
                if (*(int *)(row+0x6C) || active) {
                    SetMeterMaximum(bar,*(int *)(row+0x6C));
                    {
                        int *secondary = GetFieldC(child);
                        *secondary = (*secondary & 0xFF000000) | (textColor.value & 0xFFFFFF);
                    }
                    if (*(int *)(gWeaponTable_00239BA0+gItemSlotToRecord[gRadialMenuPages->items[i].id]*224+0x6C)>0)
                        SetMeterValue(bar,D_00139868[gRadialMenuPages->items[i].id]>>5);
                }
            }
        }
    }
    if (buttons&4) {
        int v,lower;
        PlaySoundFromGlobalBank(3,0,0);
        lower=-1;
        v=*(int *)(self+0x7CC)-1;
        *(int *)(self+0x7CC)=v>lower?v:7;
    } else if (buttons&8) {
        int v;
        PlaySoundFromGlobalBank(3,0,0);
        v=*(int *)(self+0x7CC)+1;
        *(int *)(self+0x7CC)=v>7?0:v;
    } else {
        switch (*(int *)(self+0x81C)) {
        case 0: MoveRadialMenuGridSelection(self,buttons); break;
        case 1: MoveRadialMenuItemSelection(self,buttons); break;
        }
    }
    if (gPadState.buttons&12) PingPongBlendValues(0,0,1,0,1);
    {
        int *p=GetFieldC(self+0x5A0);
        *p=PingPongBlendValues(0x60442D00,0x70FFFEED,20,0,0);
    }
    SetFloatAt38(self+0x5A0,(float)*(int *)(self+0x7CC));
    return 0;
}

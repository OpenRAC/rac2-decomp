#include "include_asm.h"
#include "names.h"

extern char *func_00288FB8(int);
extern void func_00336A38(void *, char *);
extern void func_00115DA8(char *, const char *, ...);
extern void func_00336A30(void *, int);
extern void func_00336A78(void *);
extern int func_002B0DB8(void);
extern int func_002B0D60(void);
extern int func_002B0D70(void);
extern float *func_00335E10(void *);
extern void func_00335E38(void *, float, float, float, float);
extern void func_00335E68(void *, int);
extern void func_0028FC48(int, int, int, int, unsigned long, int);
extern char D_001ADBC8[], D_001ADF98[], D_001AE2F8[];
extern short D_001A7A1A;
extern int D_001A7A1C;
extern int D_001A79FC;
extern int D_001AE2F0 __attribute__((sda));
extern int D_001AE2E0 __attribute__((sda));
extern int D_001AE2E4;
extern int D_001AE2E8 __attribute__((sda));
extern int D_001AE2EC;

/* Updates the texts of the grid menu for the selected entry, such as counts and descriptions, and draws the cursor box. */
void func_00344938(char *menu)
{
    int sel = 0;
    float zero;

    if (*(int *)(menu + 0x448) == 3)
        sel = *(int *)(menu + 0x43C) + *(int *)(menu + 0x440) * 2;
    menu[0x410] = 0;
    menu[0x420] = 0;
    SetWidgetField40(menu + 0x2E0, GetLocalizedString(0xAD2));
    switch (sel) {
    case 0:
        SetWidgetField40(menu + 0x210, GetLocalizedString(0xAD2));
        zero = 0.0f;
        Sprintf(menu + 0x400, D_001ADBC8, GetLocalizedString(0x2DBB));
        SetWidgetField44(menu + 0x328, 0);
        DrawAlignedTextLabel(menu + 0x328);
        Sprintf(menu + 0x400, D_001ADF98, CountFilledSlotsInTable());
        SetFirstFloat4(menu + 0x328, GetFirstField(menu + 0x328)[0] + (float)D_001AE2F0,
                      GetFirstField(menu + 0x328)[1], zero, zero);
        SetWidgetField44(menu + 0x328, 2);
        DrawAlignedTextLabel(menu + 0x328);
        Sprintf(menu + 0x410, D_001ADBC8, GetLocalizedString(0x2DBC));
        SetWidgetField44(menu + 0x370, 0);
        DrawAlignedTextLabel(menu + 0x370);
        Sprintf(menu + 0x410, D_001ADF98, GetSavedBaselineCount());
        SetFirstFloat4(menu + 0x370, GetFirstField(menu + 0x370)[0] + (float)D_001AE2F0,
                      GetFirstField(menu + 0x370)[1], zero, zero);
        SetWidgetField44(menu + 0x370, 2);
        DrawAlignedTextLabel(menu + 0x370);
        Sprintf(menu + 0x420, D_001ADBC8, GetLocalizedString(0x2DBD));
        SetWidgetField44(menu + 0x3B8, 0);
        DrawAlignedTextLabel(menu + 0x3B8);
        Sprintf(menu + 0x420, D_001ADF98, CountItemsAboveBaseline());
        SetFirstFloat4(menu + 0x3B8, GetFirstField(menu + 0x3B8)[0] + (float)D_001AE2F0,
                      GetFirstField(menu + 0x3B8)[1], zero, zero);
        SetWidgetField44(menu + 0x3B8, 2);
        DrawAlignedTextLabel(menu + 0x3B8);
        break;
    case 1:
        Sprintf(menu + 0x400, D_001ADBC8, GetLocalizedString(0x2DBB));
        SetWidgetField44(menu + 0x328, 0);
        DrawAlignedTextLabel(menu + 0x328);
        Sprintf(menu + 0x400, D_001ADF98, D_001A7A1A);
        SetFirstFloat4(menu + 0x328, GetFirstField(menu + 0x328)[0] + (float)D_001AE2F0,
                      GetFirstField(menu + 0x328)[1] + 16.0f, 0.0f, 0.0f);
        SetWidgetField44(menu + 0x328, 2);
        DrawAlignedTextLabel(menu + 0x328);
        SetWidgetField40(menu + 0x2E0, GetLocalizedString(0xAD1));
        SetWidgetField40(menu + 0x210, GetLocalizedString(0xAD1));
        break;
    case 2:
        Sprintf(menu + 0x400, D_001ADBC8, GetLocalizedString(0x2DBB));
        SetWidgetField44(menu + 0x328, 0);
        DrawAlignedTextLabel(menu + 0x328);
        Sprintf(menu + 0x400, D_001ADF98, D_001A7A1C);
        SetFirstFloat4(menu + 0x328, GetFirstField(menu + 0x328)[0] + (float)D_001AE2F0,
                      GetFirstField(menu + 0x328)[1] + 16.0f, 0.0f, 0.0f);
        SetWidgetField44(menu + 0x328, 2);
        DrawAlignedTextLabel(menu + 0x328);
        SetWidgetField40(menu + 0x2E0, GetLocalizedString(0xAD0));
        SetWidgetField40(menu + 0x210, GetLocalizedString(0xAD0));
        break;
    case 3:
        Sprintf(menu + 0x400, D_001ADBC8, GetLocalizedString(0x2DBB));
        SetWidgetField44(menu + 0x328, 0);
        DrawAlignedTextLabel(menu + 0x328);
        Sprintf(menu + 0x400, D_001ADF98, D_001A79FC);
        SetFirstFloat4(menu + 0x328, GetFirstField(menu + 0x328)[0] + (float)D_001AE2F0,
                      GetFirstField(menu + 0x328)[1] + 16.0f, 0.0f, 0.0f);
        SetWidgetField44(menu + 0x328, 2);
        DrawAlignedTextLabel(menu + 0x328);
        Sprintf(menu + 0x400, D_001AE2F8, GetLocalizedString(0x2DBB), D_001A79FC);
        SetWidgetField40(menu + 0x2E0, GetLocalizedString(0xACF));
        SetWidgetField40(menu + 0x210, GetLocalizedString(0xACF));
        break;
    }
    DrawAlignedTextLabel(menu + 0x2E0);
    if (*(int *)(menu + 0x444) == sel) {
        SetFlagValue(menu + 0x210, 1);
        SetFirstFloat4(menu + 0x210, (*(float **)(menu + 0x430))[0] + -117.0f,
                      (*(float **)(menu + 0x430))[1] + 3.0f, 0.0f, 0.0f);
        DrawAlignedTextLabel(menu + 0x210);
    }
    if (sel == 0) {
        int x = (*(float **)(menu + 0x430))[0];
        int y = (*(float **)(menu + 0x430))[1];
        AppendScreenRectPacket(x + D_001AE2E0, y + D_001AE2E4, x + D_001AE2E8, y + D_001AE2EC,
                      0x55F0C070, 0);
    }
}

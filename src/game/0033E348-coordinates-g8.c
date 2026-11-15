#include "names.h"
/* The x offsets use small-data loads; incomplete SDA y declarations retain
 * the absolute macro loads without claiming an unmeasured array extent. */
extern void func_0033AE28(void *);
extern void func_0033B018(void *, float, float);
extern void func_00335E38(void *, float, float, float, float);
extern char *func_002DF1F8(char *, int);
extern char *func_00288FB8(int);
extern void func_00336A38(void *, void *);
extern void func_0033EC98(void *);
extern void func_002D6F38(int);
extern char D_001C4FA0[], D_001ADC88[];
extern int D_00258D70[];
extern float D_001ADF28 __attribute__((sda));
extern float D_001ADF2C[] __attribute__((sda));
extern float D_001ADF30 __attribute__((sda));
extern float D_001ADF34[] __attribute__((sda));
extern float D_001ADF38 __attribute__((sda));
extern float D_001ADF3C[] __attribute__((sda));
extern float D_001ADF40 __attribute__((sda));
extern float D_001ADF44[] __attribute__((sda));
extern float D_001ADF48 __attribute__((sda));
extern float D_001ADF4C[] __attribute__((sda));
extern float D_001ADF50 __attribute__((sda));
extern float D_001ADF54[] __attribute__((sda));
extern float D_001ADF58 __attribute__((sda));
extern float D_001ADF5C[] __attribute__((sda));
/* Updates the info panel: moves every part into place and shows the text for the selected item. */
int func_0033EA60(char *object, int flags)
{
    char *child = object + 8;
    char *label = object + 0x578;
    char *state;
    int text;
    float x, y;

    UpdateButtonPromptBar(child);
    SetMenuAnchorPosition(child, (*(float **)(object + 0x2A8))[0], (*(float **)(object + 0x2A8))[1]);
    x = D_001ADF28 + (*(float **)(object + 0x2A8))[0];
    y = D_001ADF2C[0] + (*(float **)(object + 0x2A8))[1];
    SetFirstFloat4(object + 0x2E8, x, y, 0.0f, 0.0f);
    x = D_001ADF30 + (*(float **)(object + 0x2A8))[0];
    y = D_001ADF34[0] + (*(float **)(object + 0x2A8))[1];
    SetFirstFloat4(object + 0x330, x, y, 0.0f, 0.0f);
    x = D_001ADF38 + (*(float **)(object + 0x2A8))[0];
    y = D_001ADF3C[0] + (*(float **)(object + 0x2A8))[1];
    SetFirstFloat4(object + 0x378, x, y, 0.0f, 0.0f);
    x = D_001ADF50 + (*(float **)(object + 0x2A8))[0];
    y = D_001ADF54[0] + (*(float **)(object + 0x2A8))[1];
    SetFirstFloat4(object + 0x2AC, x, y, 0.0f, 0.0f);
    x = D_001ADF58 + (*(float **)(object + 0x2A8))[0];
    y = D_001ADF5C[0] + (*(float **)(object + 0x2A8))[1];
    SetFirstFloat4(object + 0x3C0, x, y, 0.0f, 0.0f);
    x = D_001ADF48 + (*(float **)(object + 0x2A8))[0];
    y = D_001ADF4C[0] + (*(float **)(object + 0x2A8))[1];
    SetFirstFloat4(label, x, y, 0.0f, 0.0f);
    x = D_001ADF40 + (*(float **)(object + 0x2A8))[0];
    y = D_001ADF44[0] + (*(float **)(object + 0x2A8))[1];
    SetFirstFloat4(object + 0x530, x, y, 0.0f, 0.0f);
    state = gMapOverlayState;
    FormatLocationName(object + 0x5C0, *(int *)(state + 0x230));
    text = D_00258D70[*(int *)(state + 0x230) * 2 + 1];
    if (text >= 0)
        SetWidgetField40(label, GetLocalizedString(text));
    else
        SetWidgetField40(label, D_001ADC88);
    PlaceInfoPanelCounterTexts(object);
    DrawMapScreen(0);
    return (flags >> 6) & 1;
}

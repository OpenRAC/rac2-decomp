#include "names.h"
extern void func_0033B0A8(void *, float);
extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern void func_0033ABD8(void *, void *, void *);
extern int func_00288FB8(int);
extern void func_0033B050(void *, int, int, int);
extern void func_0033B030(void *, float, float, float, float, float, float);
extern void func_0033D5A0(void *, int);
extern int D_001ADE78[2] __attribute__((sda));
/* Sets up a menu page with a single on/off option. */
void func_0033D478(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ReturnSecondArgument(16, AllocPoolCell(argument));
        *(int **)(object + 0x2AC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2AC) = 255.0f;
    (*(float **)(object + 0x2AC))[1] = 195.0f;
    child = object + 8;
    InitButtonPromptBar(child, argument, D_001ADE78);
    text = GetLocalizedString(0x2D99);
    second = GetLocalizedString(0x2D4E);
    SetButtonPromptTexts(child, text, second, GetLocalizedString(0x2D4F));
    SetButtonPromptTextOffsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    SetButtonPromptSpacing(child, 0.3f);
    *(int *)(object + 0x2A8) = 0;
    UpdateSingleToggleOptionMenuA(object, 0);
}
extern void func_0033D868(void *, int);
extern int D_001ADE88[2] __attribute__((sda));
/* Sets up a menu page with two on/off options. */
void func_0033D740(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ReturnSecondArgument(16, AllocPoolCell(argument));
        *(int **)(object + 0x2AC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2AC) = 255.0f;
    (*(float **)(object + 0x2AC))[1] = 195.0f;
    child = object + 8;
    InitButtonPromptBar(child, argument, D_001ADE88);
    text = GetLocalizedString(0x2D61);
    second = GetLocalizedString(0x2D4E);
    SetButtonPromptTexts(child, text, second, GetLocalizedString(0x2D4F));
    SetButtonPromptTextOffsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    SetButtonPromptSpacing(child, 0.4f);
    *(int *)(object + 0x2A8) = 0;
    UpdateTwoToggleOptionMenuB(object, 0);
}
extern void func_0033DC30(void *, int);
extern int D_001ADE98[2] __attribute__((sda));
/* Sets up another menu page with a single on/off option. */
void func_0033DB08(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ReturnSecondArgument(16, AllocPoolCell(argument));
        *(int **)(object + 0x2AC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2AC) = 255.0f;
    (*(float **)(object + 0x2AC))[1] = 195.0f;
    child = object + 8;
    InitButtonPromptBar(child, argument, D_001ADE98);
    text = GetLocalizedString(0x2D61);
    second = GetLocalizedString(0x2D4E);
    SetButtonPromptTexts(child, text, second, GetLocalizedString(0x2D4F));
    SetButtonPromptTextOffsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    SetButtonPromptSpacing(child, 0.3f);
    *(int *)(object + 0x2A8) = 0;
    UpdateSingleToggleOptionMenuC(object, 0);
}

extern void func_0033DEE0(void *, int);
extern int D_001ADEA8[2] __attribute__((sda));
/* Sets up another menu page with a single on/off option. */
void func_0033DDB8(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ReturnSecondArgument(16, AllocPoolCell(argument));
        *(int **)(object + 0x2AC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2AC) = 255.0f;
    (*(float **)(object + 0x2AC))[1] = 195.0f;
    child = object + 8;
    InitButtonPromptBar(child, argument, D_001ADEA8);
    text = GetLocalizedString(0x2D61);
    second = GetLocalizedString(0x2D4E);
    SetButtonPromptTexts(child, text, second, GetLocalizedString(0x2D4F));
    SetButtonPromptTextOffsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    SetButtonPromptSpacing(child, 0.4f);
    *(int *)(object + 0x2A8) = 0;
    UpdateSingleToggleOptionMenuD(object, 0);
}

extern void func_0033E0D8(void *, int);
extern int D_001ADEB8[2] __attribute__((sda));
/* Sets up another menu page with a single on/off option. */
void func_0033DFB0(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ReturnSecondArgument(16, AllocPoolCell(argument));
        *(int **)(object + 0x2AC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2AC) = 255.0f;
    (*(float **)(object + 0x2AC))[1] = 195.0f;
    child = object + 8;
    InitButtonPromptBar(child, argument, D_001ADEB8);
    text = GetLocalizedString(0x2D61);
    second = GetLocalizedString(0x2D4E);
    SetButtonPromptTexts(child, text, second, GetLocalizedString(0x2D4F));
    SetButtonPromptTextOffsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    SetButtonPromptSpacing(child, 0.4f);
    *(int *)(object + 0x2A8) = 0;
    UpdateSingleToggleOptionMenuE(object, 0);
}

extern void func_0033E3A0(void *, int);
extern int D_001ADEC8[2] __attribute__((sda));
extern void func_00347EC8(void *, void *);
extern void func_003480D8(void *, int, int);
extern void func_003480E8(void *, int);
/* Sets up a menu page that shows a scrolling list. */
void func_0033E1B0(char *object, void *argument)
{
    int *allocation;
    char *child, *widget;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ReturnSecondArgument(16, AllocPoolCell(argument));
        *(int **)(object + 0x37C) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x37C) = 255.0f;
    (*(float **)(object + 0x37C))[1] = 195.0f;
    child = object + 8;
    widget = object + 0x2B0;
    InitButtonPromptBar(child, argument, D_001ADEC8);
    text = GetLocalizedString(0x2DA0);
    second = GetLocalizedString(0x2D75);
    SetButtonPromptTexts(child, text, second, GetLocalizedString(0x2D4F));
    SetButtonPromptTextOffsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    SetButtonPromptSpacing(child, 0.4f);
    *(int *)(object + 0x2A8) = 0;
    InitListMenu_00347EC8(widget, argument);
    SetMenuSettings(widget, -83, 32);
    SetMenuField0xB8(widget, 1);
    UpdateListMenuPage(object, 0);
}

extern void func_0033D028(void *, int);
extern int D_001ADE48[2] __attribute__((sda));
extern char D_001ADC88[];
extern void func_00336408(void *, int, int, void *, void *);
extern void func_00336CC8(void *, int);
extern void func_00336B90(void *, int);
extern void func_00336B98(void *, int);
extern void func_00336498(void *, int, int);
extern void func_003364B0(void *, int, int);
extern void func_00336CE0(void *, int);
extern void func_00336CC0(void *, int);
/* Sets up the audio options menu with its two volume sliders and title box. */
void func_0033CDC8(char *object, void *argument)
{
    int *allocation;
    char *child, *widget, *secondWidget;
    void *table;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ReturnSecondArgument(16, AllocPoolCell(argument));
        *(int **)(object + 0x33C) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x33C) = 255.0f;
    (*(float **)(object + 0x33C))[1] = 195.0f;
    child = object + 8;
    widget = object + 0x2AC;
    secondWidget = object + 0x2F4;
    InitButtonPromptBar(child, argument, D_001ADE48);
    text = GetLocalizedString(0x2D97);
    second = GetLocalizedString(0x2D4E);
    SetButtonPromptTexts(child, text, second, GetLocalizedString(0x2D4F));
    SetButtonPromptTextOffsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    SetButtonPromptSpacing(child, 0.67f);
    table = D_001ADC88;
    InitDerivedObjectB(widget, 150, 1, table, argument);
    SetWidgetPositionY(widget, 16);
    SetMeterMaximum(widget, 0x400);
    SetMeterValue(widget, 0);
    SetFirstPair(widget, 0x55F0C070, 0x55F0C070);
    SetSecondPair(widget, 0x60442D00, 0x60442D00);
    SetTextAlignment(widget, 0x20FFFFFF);
    SetWidgetField38(widget, 0);
    InitDerivedObjectB(secondWidget, 150, 1, table, argument);
    SetWidgetPositionY(secondWidget, 16);
    SetMeterMaximum(secondWidget, 0x400);
    SetMeterValue(secondWidget, 0);
    SetFirstPair(secondWidget, 0x55F0C070, 0x55F0C070);
    SetSecondPair(secondWidget, 0x60442D00, 0x60442D00);
    SetTextAlignment(secondWidget, 0x20FFFFFF);
    SetWidgetField38(secondWidget, 0);
    *(int *)(object + 0x2A8) = 0;
    UpdateAudioOptionsMenu(object, 0);
}

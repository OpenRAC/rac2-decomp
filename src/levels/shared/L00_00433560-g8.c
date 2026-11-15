#include "include_asm.h"
#include "names.h"

extern void func_0033ABD8(char *p, void *argument, void *table);
extern int func_00288FB8(int);
extern void func_0033B050(char *p, int a, int b, int c);
extern void func_0033B030(char *p, float a, float b, float c, float d, float e, float f);
extern void func_0033B0A8(char *p, float f);
extern int *func_00336DA8(int size, int count);
extern int func_00336E40(void *argument);

extern int func_L00_00433810(char *object, int flags);
extern int func_L00_00433A08(char *object, int flags);

extern int D_L00_001AE1E8[2] __attribute__((sda));
extern int D_L00_001AE1F8[2] __attribute__((sda));

/* Builds the labelled sub-view on the object: allocation record, two size floats, then the
   three localized strings, the box and the scale, finally the next layer down. */
void func_L00_004336E8(char *object, void *argument)
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
    InitButtonPromptBar(child, argument, D_L00_001AE1E8);
    text = GetLocalizedString(0x2D61);
    second = GetLocalizedString(0x2D4E);
    SetButtonPromptTexts(child, text, second, GetLocalizedString(0x2D4F));
    SetButtonPromptTextOffsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    SetButtonPromptSpacing(child, 0.4f);
    *(int *)(object + 0x2A8) = 0;
    UpdateTwoPartObjectFlagsB(object, 0);
}

/* Same construction as func_L00_004336E8 with its own label table and lower layer. */
/* Builds a second menu page the same way as the first one. */
void func_L00_004338E0(char *object, void *argument)
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
    InitButtonPromptBar(child, argument, D_L00_001AE1F8);
    text = GetLocalizedString(0x2D61);
    second = GetLocalizedString(0x2D4E);
    SetButtonPromptTexts(child, text, second, GetLocalizedString(0x2D4F));
    SetButtonPromptTextOffsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    SetButtonPromptSpacing(child, 0.4f);
    *(int *)(object + 0x2A8) = 0;
    UpdateTwoPartObjectFlagsC(object, 0);
}

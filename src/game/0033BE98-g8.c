#include "names.h"
extern void func_0033B0A8(void *, float);
extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern void func_0033ABD8(void *, void *, void *);
extern int func_00288FB8(int);
extern void func_0033B050(void *, int, int, int);
extern void func_0033B030(void *, float, float, float, float, float, float);
extern void func_0033C2D8(void *, int);
extern int D_001ADDE0[2] __attribute__((sda));
/* Sets up the on/off option menu: its button prompt bar, labels and position. */
void func_0033C1B0(char *menu, void *owner)
{
    int *allocation;
    char *prompt;
    int textA, textB;
    *(void **)menu = owner;
    if (owner) {
        allocation = ReturnSecondArgument(16, AllocPoolCell(owner));
        *(int **)(menu + 0x2AC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(menu + 0x2AC) = 255.0f;
    (*(float **)(menu + 0x2AC))[1] = 195.0f;
    prompt = menu + 8;
    InitButtonPromptBar(prompt, owner, D_001ADDE0);
    textA = GetLocalizedString(0x31E4);
    textB = GetLocalizedString(0x2D4E);
    SetButtonPromptTexts(prompt, textA, textB, GetLocalizedString(0x2D4F));
    SetButtonPromptTextOffsets(prompt, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    SetButtonPromptSpacing(prompt, 0.65f);
    *(int *)(menu + 0x2A8) = 0;
    UpdateOnOffOptionMenu(menu, 0);
}

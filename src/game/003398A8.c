#include "names.h"


extern int D_00138344[4];

extern int D_L04_001ADF14[4] __attribute__((sda));

extern int D_L04_001ADF10 __attribute__((sda));

extern int D_L04_001ADF18 __attribute__((sda));

extern void func_L00_00430948(char *, float, float);

extern void func_0033AE28(char *);

extern int func_002A9588_1(int, int, int, int, int);

extern void *func_00335E20(char *);

extern void func_00335E38_3(char *, float, float, float, float);

/* Moves the pop-up's box and label to follow its position and row, and updates the label colour. */
int func_003398A8(char *popup)
{
    char *box = popup + 8;
    char *label;
    void *colorSlot;
    float labelX;
    float labelY;

    StoreTwoFloatsThroughCell(box, ((float *)(*(int *)(popup + 756)))[0], ((float *)(*(int *)(popup + 756)))[1]);
    UpdateButtonPromptBar(box);
    if (D_00138344[0] & 0x5000)
        func_002A9588_1(0, 0, 1, 0, 1);
    label = popup + 680;
    colorSlot = GetFieldC(label);
    *(int *)colorSlot = func_002A9588_1(0x60442D00, 0x70FFFEED, 20, 0, 0);
    labelX = ((float *)(*(int *)(popup + 756)))[0] + (float)D_L04_001ADF10;
    labelY = ((float *)(*(int *)(popup + 756)))[1]
        + (float)(*(int *)(popup + 760) * D_L04_001ADF18);
    labelY = labelY + (float)D_L04_001ADF14[0];
    func_00335E38_3(label, labelX, labelY, 0.0f, 0.0f);
    return 0;
}

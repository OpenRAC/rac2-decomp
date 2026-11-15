#include "include_asm.h"
#include "names.h"

typedef struct { int ids[2]; } OptionPair;
typedef struct { int ids[3]; } OptionTriple;
extern OptionPair D_001ADE20 __attribute__((section(".data")));
extern OptionPair D_001ADDD0 __attribute__((section(".data")));
extern OptionTriple D_001ADE28 __attribute__((section(".data")));
extern char D_001ADDD8[];
extern int D_001ADE00 __attribute__((sda));
extern int D_001ADE04[] __attribute__((sda));
extern int D_001ADE08 __attribute__((sda));
extern int D_001ADE0C[] __attribute__((sda));
extern int D_001ADE10 __attribute__((sda));
extern int D_001ADE14[] __attribute__((sda));
extern int D_001ADE18 __attribute__((sda));
extern int D_001ADE1C[] __attribute__((sda));
extern int D_001A7BA4, D_001A7BA8, D_001A7BAC;
extern unsigned char D_001A7BB1;
extern void func_0033AF48(void *);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern int func_0027FB40(int, int, unsigned long, char *, int);


#ifndef RAC2_T_U8_FF4EB83C9
#define RAC2_T_U8_FF4EB83C9
typedef unsigned char u8_Ff4eb83c9;
#endif

#ifndef RAC2_T_S32_FF4EB83C9
#define RAC2_T_S32_FF4EB83C9
typedef int s32_Ff4eb83c9;
#endif

#ifndef RAC2_T_F32_FF4EB83C9
#define RAC2_T_F32_FF4EB83C9
typedef float f32_Ff4eb83c9;
#endif

/* Resident shared table reached through $gp (small-data symbol). */
extern f32_Ff4eb83c9 D_L04_001AE070[2] __attribute__((sda));

extern void *func_00336E40_3(void *);

extern void *func_00336DA8_3(s32_Ff4eb83c9, void *);

extern void func_0033ABD8_3(u8_Ff4eb83c9 *, void *, f32_Ff4eb83c9 *);

extern void *func_00288FB8_2(s32_Ff4eb83c9);

extern void func_0033B050_2(u8_Ff4eb83c9 *, void *, void *, void *);

extern void func_0033B030_3(u8_Ff4eb83c9 *, f32_Ff4eb83c9, f32_Ff4eb83c9, f32_Ff4eb83c9, f32_Ff4eb83c9, f32_Ff4eb83c9, f32_Ff4eb83c9);

extern void func_0033B0A8_2(u8_Ff4eb83c9 *, f32_Ff4eb83c9);

extern int func_0033C590(u8_Ff4eb83c9 *, s32_Ff4eb83c9);
extern void func_0033AE28(void *);
extern void func_0033B018(void *, float, float);
extern int func_002E5E58(int, int, void *);
extern void func_0027AB40(void);

/* Sets up the four-option menu: its button prompt bar, labels and position. */
void func_0033C468(u8_Ff4eb83c9 *self, void *arg) {
    u8_Ff4eb83c9 *prompt;
    void *textA, *textB, *textC;
    *(void **)self = arg;
    if (arg != 0) {
        void *owner = func_00336E40_3(arg);
        void *allocation = func_00336DA8_3(16, owner);
        *(void **)(self + 684) = allocation;
        ((s32_Ff4eb83c9 *)allocation)[1] = 0;
        ((s32_Ff4eb83c9 *)allocation)[2] = 0;
        ((s32_Ff4eb83c9 *)allocation)[3] = 0;
        ((s32_Ff4eb83c9 *)allocation)[0] = 0;
    }
    prompt = self + 8;
    ((f32_Ff4eb83c9 *)*(void **)(self + 684))[0] = 255.0f;
    ((f32_Ff4eb83c9 *)*(void **)(self + 684))[1] = 195.0f;
    func_0033ABD8_3(prompt, arg, D_L04_001AE070);
    textA = func_00288FB8_2(11672);
    textB = func_00288FB8_2(11598);
    textC = func_00288FB8_2(11599);
    func_0033B050_2(prompt, textA, textB, textC);
    func_0033B030_3(prompt, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_0033B0A8_2(prompt, 0.65f);
    *(s32_Ff4eb83c9 *)(self + 680) = 0;
    UpdateFourOptionMenuInput(self, 0);
}
int func_0033C590(u8_Ff4eb83c9 *a0, int a1)
{
    u8_Ff4eb83c9 *p = a0 + 8;
    unsigned int *sfx = (unsigned int *)0x1A7BA4;
    unsigned int *music = (unsigned int *)0x1A7BA8;
    int *mode = (int *)0x1A7BAC;
    unsigned char *toggle = (unsigned char *)0x1A7BB1;
    float *q;
    int v;

    UpdateButtonPromptBar(p);
    q = *(float **)(a0 + 0x2AC);
    SetMenuAnchorPosition(p, q[0], q[1]);
    if (a1 & 0x1000) {
        PlaySoundFromGlobalBank(3, 0, 0);
        v = *(int *)(a0 + 0x2A8);
        *(int *)(a0 + 0x2A8) = (v + 3) % 4;
    } else if (a1 & 0x4000) {
        PlaySoundFromGlobalBank(3, 0, 0);
        v = *(int *)(a0 + 0x2A8);
        *(int *)(a0 + 0x2A8) = (v + 1) % 4;
    } else if (a1 & 0x40) {
        PlaySoundFromGlobalBank(4, 0, 0);
        switch (*(int *)(a0 + 0x2A8)) {
        case 0:
            *sfx = *sfx < 1;
            break;
        case 1:
            *music = *music < 1;
            break;
        case 2:
            *mode = (*mode + 1) % 3;
            break;
        case 3:
            *toggle = *toggle < 1;
            UpdateViewContext();
            break;
        }
    }
    return (a1 >> 6) & 1;
}

/* Draws the four option lines (two on/off options, a three-way option and an on/off option) and highlights the selected one. */
void func_0033C738(char *object)
{
    char buffer[128];
    OptionPair onOffText;
    OptionTriple modeText;
    OptionPair toggleText;
    char *first, *second, *format;
    char *label2, *label3, *label4;
    int color;
    DrawButtonPromptBar(object + 8);
    onOffText = D_001ADE20;
    modeText = D_001ADE28;
    toggleText = D_001ADDD0;
    format = D_001ADDD8;
    color = *(int *)(object + 0x2A8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    first = GetLocalizedString(0x2DE2);
    second = GetLocalizedString(onOffText.ids[D_001A7BA4 != 0]);
    Sprintf(buffer, format, first, second);
    DrawTextCenteredMediumFont(D_001ADE00, D_001ADE04[0], color, buffer, -1);
    color = *(int *)(object + 0x2A8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label2 = GetLocalizedString(0x2DE1);
    second = GetLocalizedString(onOffText.ids[D_001A7BA8 != 0]);
    Sprintf(buffer, format, label2, second);
    DrawTextCenteredMediumFont(D_001ADE08, D_001ADE0C[0], color, buffer, -1);
    color = *(int *)(object + 0x2A8) == 2 ? (int)0x80D0D0D0 : 0x70808080;
    {
        int mode = D_001A7BAC;
        label3 = GetLocalizedString(0x2F18);
        second = GetLocalizedString(modeText.ids[mode]);
    }
    Sprintf(buffer, format, label3, second);
    DrawTextCenteredMediumFont(D_001ADE10, D_001ADE14[0], color, buffer, -1);
    color = *(int *)(object + 0x2A8) == 3 ? (int)0x80D0D0D0 : 0x70808080;
    label4 = GetLocalizedString(0x31E4);
    second = GetLocalizedString(toggleText.ids[D_001A7BB1 != 0]);
    Sprintf(buffer, format, label4, second);
    DrawTextCenteredMediumFont(D_001ADE18, D_001ADE1C[0], color, buffer, -1);
}

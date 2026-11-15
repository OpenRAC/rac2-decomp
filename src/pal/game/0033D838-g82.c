#include "include_asm.h"
#include "names.h"

typedef unsigned char u8_Ff4eb83c9;
typedef int s32_Ff4eb83c9;
extern int UpdateFourOptionMenuInput(u8_Ff4eb83c9 *, s32_Ff4eb83c9);
extern void func_PAL_0033CD50(void *);
extern void menu_set_anchor_pos(void *, float, float);
extern int snd_play_from_global_bank(int, int, void *);
extern void UpdateViewContext(void);

int func_PAL_0033E460(u8_Ff4eb83c9 *a0, int a1)
{
    u8_Ff4eb83c9 *p = a0 + 8;
    unsigned int *sfx = (unsigned int *)0x1A7C2C;
    unsigned int *music = (unsigned int *)0x1A7C30;
    int *mode = (int *)0x1A7C34;
    unsigned char *toggle = (unsigned char *)0x1A7C39;
    float *q;
    int v;

    func_PAL_0033CD50(p);
    q = *(float **)(a0 + 0x2DC);
    menu_set_anchor_pos(p, q[0], q[1]);
    if (a1 & 0x1000) {
        snd_play_from_global_bank(3, 0, 0);
        v = *(int *)(a0 + 0x2D8);
        *(int *)(a0 + 0x2D8) = (v + 3) % 4;
    } else if (a1 & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        v = *(int *)(a0 + 0x2D8);
        *(int *)(a0 + 0x2D8) = (v + 1) % 4;
    } else if (a1 & 0x40) {
        snd_play_from_global_bank(4, 0, 0);
        switch (*(int *)(a0 + 0x2D8)) {
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
extern void func_PAL_0033CE70(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern int text_draw_centered_medium(int, int, unsigned long, char *, int);

void func_PAL_0033E608(char *object)
{
    char buffer[128];
    OptionPair onoff;
    OptionTriple modes;
    OptionPair toggle;
    char *first, *second, *format;
    char *label2, *label3, *label4;
    int color;
    func_PAL_0033CE70(object + 8);
    onoff = D_001ADE20;
    modes = D_001ADE28;
    toggle = D_001ADDD0;
    format = D_001ADDD8;
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    first = GetLocalizedString(0xBF3);
    second = GetLocalizedString(onoff.ids[D_001A7BA4 != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_medium(D_001ADE00, D_001ADE04[0], color, buffer, -1);
    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label2 = GetLocalizedString(0xBF2);
    second = GetLocalizedString(onoff.ids[D_001A7BA8 != 0]);
    sprintf(buffer, format, label2, second);
    text_draw_centered_medium(D_001ADE08, D_001ADE0C[0], color, buffer, -1);
    color = *(int *)(object + 0x2D8) == 2 ? (int)0x80D0D0D0 : 0x70808080;
    {
        int mode = D_001A7BAC;
        label3 = GetLocalizedString(0xE3D);
        second = GetLocalizedString(modes.ids[mode]);
    }
    sprintf(buffer, format, label3, second);
    text_draw_centered_medium(D_001ADE10, D_001ADE14[0], color, buffer, -1);
    color = *(int *)(object + 0x2D8) == 3 ? (int)0x80D0D0D0 : 0x70808080;
    label4 = GetLocalizedString(0x10FC);
    second = GetLocalizedString(toggle.ids[D_001A7BB1 != 0]);
    sprintf(buffer, format, label4, second);
    text_draw_centered_medium(D_001ADE18, D_001ADE1C[0], color, buffer, -1);
}

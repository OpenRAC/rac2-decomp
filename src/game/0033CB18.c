#include "include_asm.h"
#include "names.h"
extern unsigned char D_001A7B96 __attribute__((sda));
typedef struct { int ids[2]; } SolTextPair;

extern SolTextPair D_L00_001AE1A8;
extern char D_L00_001AE1B0[];
extern void func_00336548(void *);
extern void func_0027FA10(int, int, unsigned long, char *, int);
extern int func_0027FB40(int, int, unsigned long, char *, int);

extern char D_L00_001AE118[];
extern int DrawOptionText(int, int, unsigned long, char *, int) __asm__("func_0027FAA8");
extern void func_0033AF48(void *);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);

extern void Fc558ca70_FUN_0033AE28(char *p);

extern void Fc558ca70_FUN_0033B018(char *p, float a, float b);

extern void Fc558ca70_FUN_002E5E58(int a, int b, int c);

extern volatile unsigned char Fc558ca70_D_001A7B95 __attribute__((sda));

extern volatile unsigned char Fc558ca70_D_001A7B94 __attribute__((sda));

extern void Ffb202470_FUN_0033AB50(char *p);

extern void F5979c03f_FUN_0033AE28 (char *object);

extern void F5979c03f_FUN_0033B018 (char *object, float x, float y);

extern int F5979c03f_FUN_002E5E58 (int a, int b, int c);

extern void Fb7feb893_FUN_0033AE28(char *p);

extern void Fb7feb893_FUN_0033B018(char *p, float a, float b);

extern void Fb7feb893_FUN_002E5E58(int a, int b, int c);

extern volatile unsigned char Fb7feb893_D_001A7BB2 __attribute__((sda));

extern volatile unsigned char Fb7feb893_D_001A7BB3 __attribute__((sda));

extern void Fb1bbe20c_FUN_0033AE28(char *p);

extern void Fb1bbe20c_FUN_0033B018(char *p, float x, float y);

extern int Fb1bbe20c_FUN_002E5E58(int a, int b, int c);

extern volatile unsigned char Fb1bbe20c_D_001A7BB2 __attribute__((sda));

void* func_0033E170(void* param_1);

extern void func_0033AB50(int);

extern unsigned long long func_00347EA0(unsigned long long);

extern int func_0033E348(int);

/* Handles input for the two-switch option menu: up/down moves the cursor and the confirm button flips the chosen switch. */
int func_0033CB18(char *object, int flags)
{
    char *child = object + 8;
    float *position;
    int selected;

    Fc558ca70_FUN_0033AE28(child);
    position = *(float **)(object + 684);
    Fc558ca70_FUN_0033B018(child, position[0], position[1]);
    if (flags & 0x1000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        selected = *(int *)(object + 680);
        *(int *)(object + 680) = (selected + 1) % 2;
    } else if (flags & 0x4000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        selected = *(int *)(object + 680);
        *(int *)(object + 680) = (selected + 1) % 2;
    } else if (flags & 0x40) {
        Fc558ca70_FUN_002E5E58(4, 0, 0);
        switch (*(int *)(object + 680)) {
        case 0:
            Fc558ca70_D_001A7B95 = Fc558ca70_D_001A7B95 == 0;
            break;
        case 1:
            Fc558ca70_D_001A7B94 = Fc558ca70_D_001A7B94 == 0;
            break;
        }
    }
    return (flags >> 6) & 1;
}

/* Cleans up the two-switch option menu. */
char *func_0033CD80(char *object)
{
    extern void func_003363D0(void *);
    DestroyButtonPromptBar((int)(object + 8));
    ConstructDerivedObjectB(object + 0x2AC);
    ConstructDerivedObjectB(object + 0x2F4);
    return object;
}




/* func_0033D028 uses small data in 0033D028-g8.c. */

/* Draws the audio options menu: the two volume sliders and the sound mode line. */
void func_0033D2C0(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *format, *first, *second;
    char *format2, *middle, *last;
    int color;
    DrawButtonPromptBar(object + 8);
    color = *(int *)(object + 0x2A8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = D_L00_001AE1A8;
    format = D_L00_001AE1B0;
    first = GetLocalizedString(0x2F0F);
    Sprintf(buffer, format, first);
    DrawTextRightAlignedMediumFont(0x100, 0x91, color, buffer, -1);
    DrawProgressBar(object + 0x2AC);
    color = *(int *)(object + 0x2A8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    middle = GetLocalizedString(0x2F10);
    Sprintf(buffer, format, middle);
    DrawTextRightAlignedMediumFont(0x100, 0xBE, color, buffer, -1);
    DrawProgressBar(object + 0x2F4);
    color = *(int *)(object + 0x2A8) == 2 ? (int)0x80D0D0D0 : 0x70808080;
    format2 = D_L00_001AE118;
    last = GetLocalizedString(0x2F11);
    second = GetLocalizedString(pair.ids[*(int *)0x001A7B98 != 0]);
    Sprintf(buffer, format2, last, second);
    DrawTextCenteredMediumFont(0x100, 0xE1, color, buffer, -1);
}

/* Cleans up the one-switch option menu. */
char *func_0033D440(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}




/* Handles input for a one-switch option menu: the confirm button flips the switch. */
int func_0033D5A0 (char *object, int flags)
{
  unsigned char *setting = &D_001A7B96;
  float *position;
  int discarded;

  F5979c03f_FUN_0033AE28 (object + 8);
  position = *(float **) (object + 684);
  F5979c03f_FUN_0033B018 (object + 8, position[0], position[1]);

  if ((flags & 0x40) && *(int *) (object + 680) == 0)
    {
      discarded = F5979c03f_FUN_002E5E58 (4, 0, 0);
      (void) discarded;
      *setting = (*setting < 1);
    }

  return (flags >> 6) & 1;
}


extern SolTextPair D_L00_001AE110;
extern char D_L00_001AE118[];
/* Resident byte at 0x001A7BB2 is shared by all programs. */
extern void func_0033AF48(void *);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern void func_0027FAA8(int, int, unsigned long, char *, int);

/* Draws the one-switch option line with its current on/off text. */
void func_0033D638(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    int color;
    DrawButtonPromptBar(object + 8);
    color = *(int *)(object + 0x2A8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = GetLocalizedString(0x2D99);
    second = GetLocalizedString(pair.ids[*(unsigned char *)0x001A7B96 != 0]);
    Sprintf(buffer, format, first, second);
    DrawTextCenteredSmallFont(0x100, 0xAA, color, buffer, -1);
}


/* Cleans up a one-switch option menu. */
char *func_0033D708(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}




/* Handles input for the second two-switch option menu: up/down moves the cursor and confirm flips a switch. */
int func_0033D868(char *object, int flags)
{
    char *child = object + 8;
    float *position;
    int selected;

    Fb7feb893_FUN_0033AE28(child);
    position = *(float **)(object + 684);
    Fb7feb893_FUN_0033B018(child, position[0], position[1]);
    if (flags & 0x1000) {
        Fb7feb893_FUN_002E5E58(3, 0, 0);
        selected = *(int *)(object + 680);
        *(int *)(object + 680) = (selected + 1) % 2;
    } else if (flags & 0x4000) {
        Fb7feb893_FUN_002E5E58(3, 0, 0);
        selected = *(int *)(object + 680);
        *(int *)(object + 680) = (selected + 1) % 2;
    } else if (flags & 0x40) {
        Fb7feb893_FUN_002E5E58(4, 0, 0);
        switch (*(int *)(object + 680)) {
        case 0:
            Fb7feb893_D_001A7BB2 = Fb7feb893_D_001A7BB2 == 0;
            break;
        case 1:
            Fb7feb893_D_001A7BB3 = Fb7feb893_D_001A7BB3 == 0;
            break;
        }
    }
    return (flags >> 6) & 1;
}


/* Cleans up the two-switch option menu. */
char *func_0033DAD0(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}




/* Handles input for a one-switch option menu: the confirm button flips the switch. */
int func_0033DC30(char *object, int flags)
{
    float *vec;

    Fb1bbe20c_FUN_0033AE28(object + 8);
    vec = *(float **)(object + 684);
    Fb1bbe20c_FUN_0033B018(object + 8, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 680) == 0) {
        int discarded = Fb1bbe20c_FUN_002E5E58(4, 0, 0);
        (void)discarded;
        Fb1bbe20c_D_001A7BB2 = (Fb1bbe20c_D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}


/* Draws the one-switch option line with its current on/off text. */
void func_0033DCC8(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    DrawButtonPromptBar(object + 8);
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = GetLocalizedString(0x2D9A);
    second = GetLocalizedString(pair.ids[*(unsigned char *)0x001A7BB2 != 0]);
    Sprintf(buffer, format, first, second);
    DrawTextCenteredSmallFont(0x100, 0xAA, 0x80F0F0F0UL, buffer, -1);
}



/* Cleans up a one-switch option menu. */
char *func_0033DD80(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}




/* Handles input for a one-switch option menu: the confirm button flips the switch. */
int func_0033DEE0(char *object, int flags)
{
    float *vec;

    Fb1bbe20c_FUN_0033AE28(object + 8);
    vec = *(float **)(object + 684);
    Fb1bbe20c_FUN_0033B018(object + 8, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 680) == 0) {
        int discarded = Fb1bbe20c_FUN_002E5E58(4, 0, 0);
        (void)discarded;
        Fb1bbe20c_D_001A7BB2 = (Fb1bbe20c_D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}

/* Cleans up a one-switch option menu. */
char *func_0033DF78(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}




/* Handles input for a one-switch option menu: the confirm button flips the switch. */
int func_0033E0D8(char *object, int flags)
{
    float *vec;

    Fb1bbe20c_FUN_0033AE28(object + 8);
    vec = *(float **)(object + 684);
    Fb1bbe20c_FUN_0033B018(object + 8, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 680) == 0) {
        int discarded = Fb1bbe20c_FUN_002E5E58(4, 0, 0);
        (void)discarded;
        Fb1bbe20c_D_001A7BB2 = (Fb1bbe20c_D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}

/* Cleans up a menu page that has a scrolling list. */
void* func_0033E170(void* object)
{
  DestroyButtonPromptBar((int)object + 8);
  PassThroughHandle((int)object + 0x2b0);
  return object;
}




/* Returns the list entry that is currently selected. */
int func_0033E310(int owner)
{
    int result;
    result = GetListSelectedIndex(owner);
    return *(int *)(owner + 0x378) + result * 0x14;
}

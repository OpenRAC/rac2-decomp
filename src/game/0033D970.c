#include "include_asm.h"
#include "names.h"
/* Draws the two-line option row: each line is the shared "%s: %s" format over a label and the
 * variant text picked by one of two resident flags; the line matching the current selection
 * takes the bright color. */
typedef struct { int ids[2]; } SolTextPair2;
extern SolTextPair2 D_L00_001AE110;
extern char D_L00_001AE118[];
extern unsigned char D_001A7BB3 __attribute__((sda));
extern unsigned char D_001A7BB2 __attribute__((sda));
extern void func_0033AF48(void *);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern int func_0027FAA8(int, int, unsigned long, char *, int);

void func_0033D970(char *object)
{
    char buffer[128];
    SolTextPair2 pair;
    char *first;
    char *label;
    char *second;
    char *format;
    int color;

    DrawButtonPromptBar(object + 8);
    color = *(int *)(object + 0x2A8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = GetLocalizedString(0x2D9A);
    second = GetLocalizedString(pair.ids[D_001A7BB2 != 0]);
    Sprintf(buffer, format, first, second);
    DrawTextCenteredSmallFont(0x100, 0x96, color, buffer, -1);

    color = *(int *)(object + 0x2A8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label = GetLocalizedString(0x31E3);
    second = GetLocalizedString(pair.ids[D_001A7BB3 != 0]);
    Sprintf(buffer, format, label, second);
    DrawTextCenteredSmallFont(0x100, 0xBE, color, buffer, -1);
}

/* Menu list draw: one text row per entry with selection colours, check boxes and an
   optional second line. Rows are reread through the list base each time; the
   check-box globals are macro-addressed. */
#include "common.h"
typedef struct { short fields[12]; } MenuTextRectangle;
extern char *D_001F2854;
extern char D_00263B50[], D_00264290[], D_00263EF0[];
extern unsigned char D_001A7A60[] MACRO_ADDR, D_001A7BB4 MACRO_ADDR;
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_0027C540(int);
extern void *func_00115484(void *, int, int);
extern unsigned long func_0027C878(int);
extern int func_00288FB8(int);
extern void func_0027F120(void), func_0027F110(void), func_0027C660(void);
extern void func_0027FC70(short *, unsigned long, int, int, unsigned long, char *);
extern void func_002D9CF8(int, int, int);
extern void func_0028FAB8(int, int, int, int, int, int);


int func_002D84B0(char *object)
{
    MenuTextRectangle rectangle, initial;
    short *row;
    int height = 12, texture = 1, lineHeight, spacing, top;
    int count, index, selected, enabled, text;
    int active = *(char **)(D_001F2854 + 0xE8) == object;
    char *font = D_00263B50;
    unsigned long textureWord;
    int colour;
    if (*(int *)(object + 0x30) & 4) { height = 14; font = D_00264290; texture = 3; }
    if (*(int *)(object + 0x30) & 8) { height = 11; font = D_00263EF0; texture = 2; }
    VU1_addGSregister(66, 68);
    lineHeight = height + 2;
    VU1_addGSregister(71, 0x2004B);
    SetupGifPaging(0);
    row = *(short **)(object + 0x34);
    count = 0;
    while (row[0]) { row += 6; count++; }
    if (*(int *)(object + 0x30) & 16) spacing = height + 3;
    else spacing = *(int *)(object + 0x24) / (count + 1);
    top = spacing - height / 2;
    memset(&initial, 0, 24);
    initial.fields[0] = 4;
    initial.fields[1] = *(int *)(object + 0x24) - 4;
    initial.fields[3] = *(int *)(object + 0x20) - 2;
    initial.fields[5] = top - *(int *)(object + 0x44);
    initial.fields[8] = lineHeight;
    rectangle = initial;
    textureWord = GetEffectTextureDescriptor(texture);
    for (index = 0; (*(short **)(object + 0x34))[index * 6]; index++) {
        selected = active && *(int *)(object + 0x40) == index;
        enabled = (*(short **)(object + 0x34))[index * 6 + 1] != 0;
        if (*(int *)(object + 0x30) & 2) colour = (int)0x80F0F0F0u;
        else if (selected) colour = enabled ? (int)0x8020FFFFu : (int)0x80006060u;
        else colour = enabled ? (int)0x80F0F0F0u : (int)0x80303030u;
        if (!(*(int *)(object + 0x30) & 0x10000) && selected && rectangle.fields[5] < 4)
            *(int *)(object + 0x44) -= 4;
        text = GetLocalizedString((*(short **)(object + 0x34))[index * 6]);
        rectangle.fields[4] = (*(int *)(object + 0x30) & 0xA00) ? 32 : 4;
        if (*(int *)(object + 0x30) & 0x400) {
            rectangle.fields[9] = 1;
            rectangle.fields[4] = *(int *)(object + 0x20) >> 1;
        }
        if (selected) func_0027F120();
        FontPrintWindow(rectangle.fields, colour, text, -1, textureWord, font);
        if (selected) func_0027F110();
        if (*(int *)(object + 0x30) & 0x200)
            DrawMenuCheckBox(15, rectangle.fields[5] + 9, D_001A7A60[index] != 0);
        if (*(int *)(object + 0x30) & 0x800)
            DrawMenuCheckBox(15, rectangle.fields[5] + 9, D_001A7BB4 == *(int *)(*(short **)(object + 0x34) + index * 6 + 2));
        rectangle.fields[5] += rectangle.fields[7];
        if ((*(short **)(object + 0x34))[index * 6 + 4]) {
            text = GetLocalizedString((*(short **)(object + 0x34))[index * 6 + 4]);
            rectangle.fields[4] = 20;
            if (*(int *)(object + 0x30) & 0x20) {
                int x, y;
                rectangle.fields[4] = *(int *)(object + 0x20) >> 1;
                x = rectangle.fields[2] + rectangle.fields[4];
                y = rectangle.fields[0] + rectangle.fields[5] + 2;
                func_0028FAB8(x - 8, y, x + 8, y, (colour & 0xFFFFFF) | 0x50000000, 0);
                rectangle.fields[5] += 6;
            }
            FontPrintWindow(rectangle.fields, colour, text, -1, textureWord, font);
            rectangle.fields[5] += spacing;
        }
        rectangle.fields[5] += rectangle.fields[7] + 2;
        if (!(*(int *)(object + 0x30) & 0x10000) && selected) {
            int bottom = rectangle.fields[5] + rectangle.fields[7];
            if (bottom > rectangle.fields[1]) {
                if (*(int *)(object + 0x30) & 0x8000)
                    *(int *)(object + 0x44) += bottom - rectangle.fields[1];
                else *(int *)(object + 0x44) += 4;
            }
        }
    }
    DoGifPaging();
    if (*(int *)(object + 0x30) & 0x8000) {
        *(int *)(object + 0x30) ^= 0x8000;
        return 1;
    }
    return 2;
}

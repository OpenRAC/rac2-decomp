#include "include_asm.h"
#include "names.h"

extern int func_0033E348(int);

extern int func_00348128(unsigned char *);

/* Qwen draft (branch qwen/autonomy, 4419d477), checked by tools/check.py */
void func_0033AF48(int);

extern void func_0033AB50_1(void *);

extern void func_L00_0042BFF8(void *);

extern void func_L00_0042C290(void *);

extern void func_L00_0042BAD0(void *);

/* Returns the index of the selected entry in the menu list. */
int func_0033E348(int owner)
{
    return GetMenuSelectedIndex((unsigned char *)(owner + 0x2b0));
}

/* Gives the menu list its entries and remembers where they are. */
void func_0033E368(unsigned char *owner, float *records)
{
    extern void func_00348068(unsigned char *, float *);
    SetMenuEntryTable(owner + 0x2B0, records);
    *(float **)(owner + 0x378) = records;
}

extern void func_0033AE28(char *);
extern void func_0033B018(char *, float, float);
extern char *func_00347F80(char *, int);
extern void func_003480F0(char *, float, float);

/* Handles input for the list menu page and keeps the list in place. */
int func_0033E3A0(char *object, int flags)
{
    char *first = object + 8;
    char *second;
    float *position;
    UpdateButtonPromptBar(first);
    second = object + 0x2B0;
    position = *(float **)(object + 0x37C);
    SetMenuAnchorPosition(first, position[0], position[1]);
    UpdateMenuListSelection(second, flags);
    SetMenuPosition(second, (*(float **)(object + 0x37C))[0], (*(float **)(object + 0x37C))[1]);
    return (flags >> 6) & 1;
}



extern void func_0033AB50(void *);
extern void *func_00336968(void *);

/* Cleans up a menu page that has a list. */
char *func_0033E480(char *object) {
    DestroyButtonPromptBar(object + 8);
    ConstructWidgetBase(object + 0x2B0);
    return object;
}




extern void func_0033AE28(char *p);
extern void func_0033B018(char *p, float x, float y);

/* Keeps the simple menu page in place and reports if confirm was pressed. */
int func_0033E5C0(char *object, int flags)
{
    char *p = object + 8;
    float *v;
    UpdateButtonPromptBar(p);
    v = *(float **)(object + 0x2A8);
    SetMenuAnchorPosition(p, v[0], v[1]);
    return (flags >> 6) & 1;
}

/* Draws the frame of a menu page. */
void func_0033E620(int object) {
  DrawButtonPromptBar(object + 8);
}

/* Calls twelve sub-object handlers in sequence, each with the object base plus a fixed byte offset (8, 684, 744, 816, 888, 960, 1040, 1112, 1184, 1256, 1328, 1400), then returns the object pointer. */
/* Cleans up a menu page made of a frame and eleven text parts. */
char *func_0033E640(char *object)
{
    func_0033AB50_1(object + 8);
    InitCameraObjectTableC(object + 684);
    InitCameraObjectTableD(object + 744);
    InitCameraObjectTableD(object + 816);
    InitCameraObjectTableD(object + 888);
    InitCameraObjectTableA(object + 960);
    InitCameraObjectTableD(object + 1040);
    InitCameraObjectTableD(object + 1112);
    InitCameraObjectTableD(object + 1184);
    InitCameraObjectTableD(object + 1256);
    InitCameraObjectTableD(object + 1328);
    InitCameraObjectTableD(object + 1400);
    return object;
}

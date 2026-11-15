#include "include_asm.h"
#include "names.h"

extern void func_00336320_6(char *);

extern void func_00336A78_7(char *);

extern void func_00341A48(char *);

extern void func_00341A68_1(char *);

extern void func_00341A88(char *);

typedef int s32;

typedef unsigned char u8;

extern void func_00348068(unsigned char *owner, float *records);

void func_00348138(int);

void func_00348138(int param_1);

/* Reads a word at +544 of the object; returns when it is zero, otherwise calls a repeated callee four times with the object and the objects at +152, +76 and +228, then one callee each with +464, the object, the object and the object. */
/* Draws the tabbed menu when it is turned on. */
void func_00341C20(char *self)
{
    if (*(int *)(self + 544) == 0)
        return;
    func_00336320_6(self);
    func_00336320_6(self + 152);
    func_00336320_6(self + 76);
    func_00336320_6(self + 228);
    func_00336A78_7(self + 464);
    DrawTabbedMenuPart(self);
    func_00341A68_1(self);
    DrawTabbedMenuIcons(self);
}

/* Sets up the three parts of a small list menu and returns it. */
char *func_00341C90(char *self) {
    extern void func_00347EA0(void *);
    extern void func_003361A8(char *);
    PassThroughHandle(self + 0x10);
    ConstructDerivedObjectA(self + 0xDC);
    ConstructDerivedObjectA(self + 0x128);
    return self;
}


/* Measured target: byte-identical across all 27 levels. */
/* Stores a value in the menu. */
void func_00341CD8(u8 *self, s32 value) { *(s32 *)(self + 0x8) = value; }




/* Returns which entry of the list is selected. */
extern s32 func_00341E90(char *);


extern s32 func_00348128(u8 *);

s32 func_00341E90(char *object) {
    return GetMenuSelectedIndex((u8 *)object + 0x10);
}

/* Gives the list its table of entries. */
void func_00341EB0(unsigned char *owner, float *records)
{
    SetMenuEntryTable(owner + 0x10, records);
    *(float **)(owner + 0xD8) = records;
}

extern char *func_00347F80(char *, int);
extern void func_003480F0(char *, float, float);

/* Sets the selected entry of the list and moves the list to the menu position. */
long func_00341EE8(char *object, int arg)
{
    char *child = object + 0x10;
    UpdateMenuListSelection(child, arg);
    SetMenuPosition(child, (*(float **)object)[0], (*(float **)object)[1]);
    return 0;
}


/* Sets up the parts of a list menu and returns it. */
char *func_003420C8(char *object) {
    extern void func_003361A8(char *);
    extern void func_003366D0(char *);
    extern void func_00347EA0(void *);
    ConstructDerivedObjectA(object);
    ConstructDerivedObjectA(object + 0x4C);
    ConstructDerivedObjectA(object + 0x98);
    ConstructDerivedObjectA(object + 0xE4);
    ConstructDerivedObjectC(object + 0x130);
    PassThroughHandle(object + 0x188);
    return object;
}

/* func_00342118 is in 00341C20-g8.c (it reaches small data through $gp). */

/* Gives the list its table of entries. */
void func_00342380(unsigned char *owner, float *records)
{
    *(float **)(owner + 0x250) = records;
    SetMenuEntryTable(owner + 0x188, records);
}

/* Measured target: byte-identical across all 27 levels. */
/* Turns the list on or off by storing a flag. */
void func_003423A8(u8 *self, s32 value) { *(s32 *)(self + 0x170) = value; }

/* multiplies the index by 20 and adds it to a base; byte-identical across all 27 levels. */
/* Returns the address of the selected entry in the list table. */
s32 func_003423B0(u8 *self) { return *(s32 *)(self + 0x250) + *(s32 *)(self + 0x16C) * 20; }



/* Does nothing. */
void func_00342420(void)
{
}





/* Draws the selection cursor, playing a sound if a direction button was pressed. */
void func_003425B8(char *object)
{
    extern int func_002A9588(unsigned int, unsigned int, int, int, int);
    extern int *func_00335E20(char *);
    extern void func_00336320(char *);
    extern int D_00138344;
    int *slot;
    if (D_00138344 & 0x5000)
        PingPongBlendValues(0, 0, 1, 0, 1);
    object += 0xE4;
    slot = GetFieldC(object);
    *slot = PingPongBlendValues(0x60442D00, 0x70FFFEED, 20, 0, 0);
    DrawScreenElementAtStoredPosition(object);
}

/* Draws the scrolling part of the list menu. */
void func_00342648(int object)
{
  DrawOptionListRows(object + 0x188);
  return;
}

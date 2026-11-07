#include "include_asm.h"

extern int D_L00_001A904C_1 __attribute__((sda));
extern int func_PAL_003405B0(int, int);

/* func_PAL_L00_0030F568, the PAL copy of func_L00_0030D718: the same C with its own offset and
 * handler. */
int func_PAL_L00_0030F568(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return func_PAL_003405B0(v + 0x3C898, a0);
    }
    return 0;
}

extern int D_L00_001A904C_2 __attribute__((sda));
extern void func_0033D970(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_PAL_L00_0030F5A8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033D970(value + 0x3D288);
}

extern int func_PAL_L00_004388F8(int, int);

/* func_PAL_L00_0030F5D8, the PAL copy of func_L00_0030D788: the same C with its own offset and
 * handler. */
int func_PAL_L00_0030F5D8(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return func_PAL_L00_004388F8(v + 0x3D288, a0);
    }
    return 0;
}

extern int func_PAL_0033E460(int, int);

/* func_PAL_L00_0030F618, the PAL copy of func_L00_0030D7C8: the same C with its own offset and
 * handler. */
int func_PAL_L00_0030F618(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_PAL_0033E460(value + 0x3D568, argument);
    return 0;
}

extern void func_0033C738(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_PAL_L00_0030F658(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033C738(value + 0x3D568);
}

extern int func_PAL_L00_00437BA8(int, int);

/* func_PAL_L00_0030F688, the PAL copy of func_L00_0030D838: the same C with its own offset and
 * handler. */
int func_PAL_L00_0030F688(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_PAL_L00_00437BA8(value + 0x3D848, argument);
    return 0;
}

extern void func_0033CC20(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_PAL_L00_0030F6C8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033CC20(value + 0x3D848);
}

extern int func_PAL_0033F470(int, int);

/* func_PAL_L00_0030F6F8, the PAL copy of func_L00_0030D8A8: the same C with its own offset and
 * handler. */
int func_PAL_L00_0030F6F8(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_PAL_0033F470(value + 0x3DE98, argument);
    return 0;
}

extern void func_0033D638(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_PAL_L00_0030F738(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033D638(value + 0x3DE98);
}

extern int func_PAL_0033DDC0(int, int);

/* func_PAL_L00_0030F768, the PAL copy of func_L00_0030D918: the same C with its own offset and
 * handler. */
int func_PAL_L00_0030F768(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_PAL_0033DDC0(value + 0x3E178, argument);
    return 0;
}

extern void func_0033C028(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_PAL_L00_0030F7A8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033C028(value + 0x3E178);
}

extern int func_PAL_0033E160(int, int);

/* func_PAL_L00_0030F7D8, the PAL copy of func_L00_0030D988: the same C with its own offset and
 * handler. */
int func_PAL_L00_0030F7D8(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_PAL_0033E160(value + 0x3E458, argument);
    return 0;
}

extern void func_0033C378(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_PAL_L00_0030F818(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033C378(value + 0x3E458);
}

extern int func_PAL_00340348(int, int);

/* func_PAL_L00_0030F848, the PAL copy of func_L00_0030D9F8: the same C with its own offset and
 * handler. */
int func_PAL_L00_0030F848(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_PAL_00340348(value + 0x3F4A0, argument);
    return 0;
}

void func_PAL_L00_0030F888(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033E428(value + 0x3F4A0);
}

extern int func_PAL_0033EEF8(int, int);

/* func_PAL_L00_0030F8B8, the PAL copy of func_L00_0030DA68: the same C with its own offset and
 * handler. */
int func_PAL_L00_0030F8B8(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_PAL_0033EEF8(value + 0x3DB28, argument);
    return 0;
}

void func_PAL_L00_0030F8F8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033D2C0(value + 0x3DB28);
}

extern int func_PAL_L00_00438CC0(int, int);

/* func_PAL_L00_0030F928, the PAL copy of func_L00_0030DAD8: the same C with its own offset and
 * handler. */
int func_PAL_L00_0030F928(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_PAL_L00_00438CC0(value + 0x3EC00, argument);
    return 0;
}

void func_PAL_L00_0030F968(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033DCC8(value + 0x3EC00);
}


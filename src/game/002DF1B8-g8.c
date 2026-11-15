#include "include_asm.h"
#include "names.h"

/* -G8 sibling for src/game/002DF1B8.c: the two argument words go out through
   $gp, so this body needs the small-data addressing mode. */

extern void func_002B49E0(int, int, int, int, int);

extern void func_00284E18(int, int, int);

extern int D_001ABD80 __attribute__((sda));
extern int D_001ABD84 __attribute__((sda));

extern int D_001B1608[] __attribute__((sda));
extern char *D_001B1B5C;
extern char *D_001B1B64;

extern char *D_001B22A8;
extern int D_001ABD88[2] __attribute__((sda));
extern char D_00261D10[];
extern void func_002E0C40(int, int);

/* func_002DF380 is here for the compiler, not for $gp: the SDK compiler of
   src/game/002DF1B8.c does not rotate the loop the way retail does. The first
   call returns a word the original keeps in $v0, which is what puts the base
   pointer in $v1. */
extern int func_002B4B70(int, int);

/* The globals this function reads are above the resident data: their addresses
   differ from program to program, so they have no address in their names. */
extern int ref_L00_002DF380_00[];
extern char *ref_L00_002DF380_01;
extern char *ref_L00_002DF380_02;

/* Shows every game object again by clearing the hidden mark on each one. */
void func_002DF380(void)
{
    char *start;
    char *end;
    char *p;

    EndSlotRequest(0, 0);
    SetBackgroundColor(ref_L00_002DF380_00[0x8F], ref_L00_002DF380_00[0x90], ref_L00_002DF380_00[0x91]);
    start = ref_L00_002DF380_02;
    end = ref_L00_002DF380_01;
    for (p = start; p < end; p += 0x100) {
        *(unsigned short *)(p + 0x34) &= 0xFF7F;
    }
}

/* Adds a shadow drawing step to the packet list and starts it. */
void func_002DF7A8(int pass, int tableIndex, int recordIndex)
{
    *(int *)(*(char *volatile *)&gDmaPacketCursor + 0x0) = 0x30000003;
    *(int *)(*(char *volatile *)&gDmaPacketCursor + 0x4) = (int)(D_00261D10 + recordIndex * 0x30);
    *(int *)(*(char *volatile *)&gDmaPacketCursor + 0x8) = 0x13000000;
    *(int *)(*(char *volatile *)&gDmaPacketCursor + 0xC) = 0x50000003;
    gDmaPacketCursor = *(char *volatile *)&gDmaPacketCursor + 0x10;
    DrawShadowPass(pass, D_001ABD88[tableIndex]);
}

/* Hides every game object by setting a hidden mark on each one, and remembers the two arguments. */
void func_002DF2E0(int firstArg, int secondArg)
{
    char *start;
    char *end;
    char *p;

    BeginSlotRequest(7, 1, 0, 0, 0);
    D_001ABD84 = secondArg;
    D_001ABD80 = firstArg;
    D_001B1608[0] = 0;
    SetBackgroundColor(0, 0, 0);
    start = D_001B1B5C;
    end = D_001B1B64;
    for (p = start; p < end; p += 0x100) {
        *(unsigned short *)(p + 0x34) |= 0x80;
    }
}

extern char *D_001B20B4;
extern int D_001B20BC __attribute__((section(".sdata")));
extern void *D_001A72D0 __attribute__((sda));
extern char D_001ABD90[];
extern int func_002E2988(void *);
extern void func_002FC748(void);
extern void func_0026FEB8(const char *, ...);

/* Links the two graphics packet lists together, checks how big the frame got, warns if it is too large and keeps the biggest size seen. */
void func_002E0F98(void)
{
    char *other = *(char *volatile *)&D_001B20B4;
    char *saved = *(char *volatile *)&gDmaPacketCursor;
    char *next;
    int size;
    gDmaPacketCursor = saved + 16;
    *(unsigned int *)other = 0x20000000;
    *(int *)(*(char *volatile *)&D_001B20B4 + 4) = (int)*(char *volatile *)&gDmaPacketCursor;
    *(int *)(*(char *volatile *)&D_001B20B4 + 8) = 0;
    *(int *)(*(char *volatile *)&D_001B20B4 + 12) = 0;
    size = BuildShrubTextureDma(D_001A72D0);
    AppendVu1DmaChainTable1();
    if (size > 0x400000)
        STUB_printf(D_001ABD90);
    if (*(volatile int *)&D_001B20BC < size)
        D_001B20BC = size;
    *(unsigned int *)(*(char *volatile *)&gDmaPacketCursor) = 0x20000000;
    next = *(char *volatile *)&D_001B20B4 + 16;
    *(int *)(*(char *volatile *)&gDmaPacketCursor + 4) = (int)next;
    *(int *)(*(char *volatile *)&gDmaPacketCursor + 8) = 0;
    *(int *)(*(char *volatile *)&gDmaPacketCursor + 12) = 0;
    *(char *volatile *)&gDmaPacketCursor = *(char *volatile *)&gDmaPacketCursor + 16;
    *(unsigned int *)saved = 0x20000000;
    *(int *)(saved + 4) = (int)*(char *volatile *)&gDmaPacketCursor;
    *(int *)(saved + 8) = 0;
    *(int *)(saved + 12) = 0;
}

extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern const char D_001AB998[];
extern const char D_001AB9F8[];
extern struct { int text; int pad; } D_00258D70[];

/* Builds the text for a location name into the buffer. Most locations get a prefix word first. */
char *func_002DF1F8(char *buf, int kind) {
    int flag;

    switch (kind) {
    case 2:
    case 5:
    case 10:
    case 23:
    case 24:
    case 25:
    case 26:
        flag = 0;
        break;
    default:
        flag = 1;
        break;
    }
    if (flag) {
        Sprintf(buf, D_001AB998, GetLocalizedString(0xB44), GetLocalizedString(D_00258D70[kind].text));
    } else {
        Sprintf(buf, D_001AB9F8, GetLocalizedString(D_00258D70[kind].text));
    }
    return buf;
}

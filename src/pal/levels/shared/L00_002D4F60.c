#include "include_asm.h"


extern char D_00189E20[];
extern int D_L00_001A8F00 __attribute__((sda));
extern void func_PAL_L00_002AFAE8(void);
extern void func_PAL_L00_002B0860(char *);
extern void func_PAL_L00_002D4F60(void);
typedef struct {
    unsigned char pad0[0x1270];
    void *f1270;
    void *f1274;
    unsigned char pad1[0x12C0 - 0x1278];
    void *f12C0;
    unsigned char pad2[0x1360 - 0x12C4];
    void *f1360;
    void *f1364;
    void *f1368;
} Base_2A;
typedef struct {
    unsigned char pad0[0x44];
    short count;
    unsigned char pad1[0x18C - 0x46];
    void *list[1];
} Rec_1BCAC0;
extern Rec_1BCAC0 D_L00_001BCAC0;

/* Set bit 0x800 on list objects of either supported kind, dispatch the level
   updates, then clear bit 0 on the six resident object slots. */
void func_PAL_L00_002D5150(char *arg0)
{
    int i;
    void *node;
    unsigned short v;

    if (D_L00_001A8F00 != 2 && D_L00_001A8F00 != 6)
        return;

    if (((Base_2A *)D_00189E20)->f12C0 == 0)
        func_PAL_L00_002AFAE8();

    for (i = 0; i < D_L00_001BCAC0.count; i++) {
        node = D_L00_001BCAC0.list[i];
        if (node != 0 && (*(short *)((char *)node + 0xAA) == 0x50A ||
                          *(short *)((char *)node + 0xAA) == 0xD54)) {
            v = *(unsigned short *)((char *)node + 0x34);
            *(unsigned short *)((char *)node + 0x34) = v | 0x800;
        }
    }

    func_L00_002AA178(arg0);
    func_PAL_L00_002B0860(arg0);
    func_PAL_L00_002D4F60();

    {
        void *node;
        Base_2A *state = (Base_2A *)D_00189E20;

        node = state->f12C0;
        if (node != 0) {
            v = *(unsigned short *)((char *)node + 0x34);
            *(unsigned short *)((char *)node + 0x34) = v & 0xFFFE;
        }
        node = state->f1270;
        if (node != 0) {
            v = *(unsigned short *)((char *)node + 0x34);
            *(unsigned short *)((char *)node + 0x34) = v & 0xFFFE;
        }
        node = state->f1274;
        if (node != 0) {
            v = *(unsigned short *)((char *)node + 0x34);
            *(unsigned short *)((char *)node + 0x34) = v & 0xFFFE;
        }
        node = state->f1360;
        if (node != 0) {
            v = *(unsigned short *)((char *)node + 0x34);
            *(unsigned short *)((char *)node + 0x34) = v & 0xFFFE;
        }
        node = state->f1364;
        if (node != 0) {
            v = *(unsigned short *)((char *)node + 0x34);
            *(unsigned short *)((char *)node + 0x34) = v & 0xFFFE;
        }
        node = state->f1368;
        if (node != 0) {
            v = *(unsigned short *)((char *)node + 0x34);
            *(unsigned short *)((char *)node + 0x34) = v & 0xFFFE;
        }
    }
}


extern char D_00189E20_4D98[];
extern char *func_0029EFD0(int);
extern void func_L00_002AA178(char *);
extern void func_L00_002B0968(char *);

/* One-shot spawn: arms the state word, and when the slot is free asks the allocator for a
   0x50A object, writes its flags, the packed constant at +0x38 and the level's tag, then runs
   the two level entry points on the argument. */
void func_PAL_L00_002D52C0(char *arg0) {
    char *base = D_00189E20_4D98;
    char *node;

    *(int *)(base + 0x12E8) = 0x2F;
    if (*(int *)(base + 0x12C0) == 0) {
        node = func_0029EFD0(0x50A);
        if (node != 0) {
            *(unsigned short *)(node + 0x32) = 0x20;
            *(unsigned short *)(node + 0x34) =
                *(unsigned short *)(node + 0x34) | 2;
            *(unsigned char *)(node + 0x31) = 1;
            *(unsigned long *)(node + 0x38) = 0x20202000000000UL;
            *(int *)(node + 0x64) = 0;
            if (*(unsigned char *)(*(int *)(node + 0x24) + 6) != 0)
                *(unsigned char *)(node + 0x63) = 0x10;
            *(unsigned short *)(node + 0x34) =
                *(unsigned short *)(node + 0x34) | 0x800;
            *(int *)(base + 0x12C0) = (int)node;
            *(int *)(base + 0x12E4) = 2;
        }
    }
    func_L00_002AA178(arg0);
    func_L00_002B0968(arg0);
}

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_002D5380);

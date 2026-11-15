#include "include_asm.h"
#include "names.h"

extern char *D_L00_001B24FC;
extern char *D_L00_001B2608;
extern int D_L00_001B2504;
extern int D_001A72D0 __attribute__((sda));
extern char D_L00_001AD3D0[];

extern void func_002F00A8(void);
extern int func_002F0218(int);
extern void gfx_append_vu1_preset_a(void);
extern void STUB_printf(const char *, ...);

/* Adds an empty marker to the render list, runs the main render passes, records how big the list got, and links the markers together. */
void gfx_build_render_list_markers(void)
{
    char *oldHead;
    char *oldTail;
    int chainSize;

    oldHead = D_L00_001B24FC;
    oldTail = D_L00_001B2608;
    D_L00_001B2608 = oldTail + 16;
    *(int *)(oldHead + 0) = 0x20000000;
    *(char **)(D_L00_001B24FC + 4) = D_L00_001B2608;
    *(int *)(D_L00_001B24FC + 8) = 0;
    *(int *)(D_L00_001B24FC + 12) = 0;
    func_002F00A8();
    chainSize = func_002F0218(D_001A72D0);
    gfx_append_vu1_preset_a();
    if (0x400000 < chainSize) {
        STUB_printf(D_L00_001AD3D0);
    }
    if (D_L00_001B2504 < chainSize) {
        D_L00_001B2504 = chainSize;
    }

    *(int *)(D_L00_001B2608 + 0) = 0x20000000;
    *(char **)(D_L00_001B2608 + 4) = D_L00_001B24FC + 16;
    *(int *)(D_L00_001B2608 + 8) = 0;
    *(int *)(D_L00_001B2608 + 12) = 0;
    D_L00_001B2608 = D_L00_001B2608 + 16;
    *(int *)(oldTail + 0) = 0x20000000;
    *(char **)(oldTail + 4) = D_L00_001B2608;
    *(int *)(oldTail + 8) = 0;
    *(int *)(oldTail + 12) = 0;
}

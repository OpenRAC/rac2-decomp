/* func_00294988 - 572 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_00294988 584B vs 572B (best so far 576B before merging dst/src).
   Structure and all calls match (twin of func_00294398/func_00294630 in the
   same file for the slot search, goto-first-element style). Left: allocation.
   Retail keeps only the hi part (lui 0x15) of D_00152CD0 in $s4 and re-adds
   0x2CD0 at each use after the calls (addiu v0,s4,0x2CD0), saving s0-s5; mine
   keeps the full address of D_00152CD0 in a saved reg (s0) so it saves s0-s6.
   Also: 'jal func_132858; nop; nop; jal func_132028; nop nop nop nop; bnez'
   wait loop has label nops (needs -g?) — not checked. Table2 gained named
   fields cur/slot/handle (same offsets). */

/* src/game/00291758.c. ALSO change struct Table2 at the top to: struct Table2 { char pad00[0x14]; short cur; short slot; char pad18[0x18]; int handle; s32 slots[4]; };  (same offsets). The block below replaces the INCLUDE-less stub `void func_00294988(void) {}`/marker. Uses Fee2b87d1_D_0014B540 / Fee2b87d1_D_00152CD0 from the same file. */
typedef struct { char pad[0x78]; void *f78; char pad7C[0x70 - 0x7C + 0x70]; } Node294988;
typedef struct { char pad[0x1C]; int kind; } Entry294988;

extern char D_00188660[0x16C0];
extern int D_001B22A0[] __attribute__((sda));
extern int D_001B22B0[] __attribute__((sda));
extern int D_001A7278[] __attribute__((sda));
extern int D_001A5200_unused;
extern char D_001AF370[];
extern char D_001A9B80;
extern void func_0026FEB8();
extern void func_002FC3C0(int);
extern void func_002945E8(void *, void *);
extern void func_0029CFB0(int, int, int);
extern void func_00132858(void *);
extern int func_00132028(void);
extern void *func_001326D8(int);
extern void func_00132828(void);
extern void func_002946C0(int, int, int);

void func_00294988(int id)
{
    int i = 0;
    int k;
    int dst;
    char *p;

    if (Fee2b87d1_D_0014B540.slots[0].w == id)
        goto found;
    while (++i < 48) {
        if (Fee2b87d1_D_0014B540.slots[i].w == id)
            break;
    }
found:
    if (i == 48)
        return;
    if (Fee2b87d1_D_00152CD0.cur == i)
        return;
    k = 0;
    Fee2b87d1_D_00152CD0.cur = i;
    if (Fee2b87d1_D_00152CD0.slots[0] == i)
        goto have;
    while (++k < 3) {
        if (Fee2b87d1_D_00152CD0.slots[k] == i)
            break;
    }
have:
    func_002FC3C0(1);
    if (k == 3) {
        k = 0;
        func_0026FEB8(D_001AF370, id);
        func_002945E8((void *)id, 0);
    }
    Fee2b87d1_D_00152CD0.slot = k;
    dst = (int)((char *)&Fee2b87d1_D_00152CD0 + 0x40 + k * 0xC800);
    if (dst <= 0xFFFFF) {
        int t = D_001B22A0[0] + D_001B22B0[0] - 0xC800;
        func_0029CFB0(t, dst, 0xC80);
        dst = t;
    }
    for (p = D_00188660; p < D_00188660 + 0x16C0; p += 0x70) {
        Entry294988 *e = *(Entry294988 **)(p + 0x78);
        if (e != 0 && e->kind == 4)
            *(void **)(p + 0x78) = &D_001A9B80;
    }
    if (Fee2b87d1_D_00152CD0.handle != 0) {
        do {
            func_00132858((void *)Fee2b87d1_D_00152CD0.handle);
        } while (func_00132028() != 0);
    }
    if (Fee2b87d1_D_0014B540.slots[i].rest[3] != 0) {
        void *h = func_001326D8(D_001A7278[0] + k * 0xC800);
        Fee2b87d1_D_00152CD0.handle = (int)h;
        *(void **)(D_00188660 + 0x17B0) = h;
    } else {
        Fee2b87d1_D_00152CD0.handle = 0;
    }
    func_00132828();
    func_002946C0(id, i, dst);
}

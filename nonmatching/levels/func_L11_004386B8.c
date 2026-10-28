/* func_L11_004386B8 - 452 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   SIZE MATCHES (452 B). Trick from func_L11_00439BF0 in the same file: a
   local `records = (char *)D_L11_001B359C` re-read (as a statement) after
   every call, so the base stays cached between the call-free statements as in
   retail; qcopy_nc (not qcopy) for the quad.
   Left (~60 diff lines, all register picks): retail keeps the base in $a0 and
   the scaled index in $a3 (`addu a0,a0,a3`), draft the opposite ($a3 base,
   $a0 index); retail uses idx+base order for stores and base+idx for call
   args (macros RECB/REC in the draft, no effect). Tried: first group with
   direct global read. */

/* in L11_00432628.c (needs #include "common.h"; D_L11_001B359C is the file sda int) */
extern void func_00282CF0(void *, void *, void *);
extern void func_00282C88(void *);

/* Rebuilds the three axis vectors of the rotor record from its saved basis. The record table is
   read again after every call. */
void func_L11_004386B8(char *p)
{
#define REC(o) ((char *)((*(int *)(*(char **)((o) + 0x68) + 0x358) << 8) + (int)records))
#define RECB(o) (records + (*(int *)(*(char **)((o) + 0x68) + 0x358) << 8))
    char *records;
    char *state = *(char **)(p + 0x68);

    records = (char *)D_L11_001B359C;
    qcopy_nc(REC(p) + 0x10, state + 0x1B0);
    func_00282CF0(RECB(p) + 0xC0, state + 0x1A0, state + 0x1B0);
    records = (char *)D_L11_001B359C;
    *(int *)(REC(p) + 0xCC) = 0;
    func_00282F20(RECB(p) + 0xC0, RECB(p) + 0xC0, 1.0f);
    records = (char *)D_L11_001B359C;
    func_00282C88(RECB(p) + 0xE0);
    records = (char *)D_L11_001B359C;
    *(float *)(REC(p) + 0xE8) = 1.0f;
    func_00282DD8(RECB(p) + 0xD0, RECB(p) + 0xE0, RECB(p) + 0xC0);
    records = (char *)D_L11_001B359C;
    *(int *)(REC(p) + 0xDC) = 0;
    func_00282F20(RECB(p) + 0xD0, RECB(p) + 0xD0, 1.0f);
    records = (char *)D_L11_001B359C;
    func_00282DD8(RECB(p) + 0xE0, RECB(p) + 0xC0, RECB(p) + 0xD0);
    records = (char *)D_L11_001B359C;
    *(int *)(REC(p) + 0xEC) = 0;
    func_00282F20(RECB(p) + 0xE0, RECB(p) + 0xE0, 1.0f);
    records = (char *)D_L11_001B359C;
    *(unsigned short *)(REC(p) + 0x34) |= 0x100;
#undef REC
#undef RECB
}

/* func_L11_00438460 - 596 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   SIZE MATCHES (596 B), ~73 diff lines, all register picks / operand order.
   Uses the `records = (char *)D_L11_001B359C;` re-read after every call trick
   (see func_L11_00439BF0 in the same file) and qcopy_nc. Same remaining issue
   as func_L11_004386B8: retail base in $a0 / index in $a1 ($a3 in the other),
   draft base in $a2; retail `addu v1,v1,s0` (state ptr + i*4) vs draft `addu
   v1,s0,v1`. */

/* in L11_00432628.c (needs #include "common.h"); same body as func_L11_004386B8 in a 10-rotor loop */
extern void func_00282CF0(void *, void *, void *);
extern void func_00282C88(void *);

/* For each of the ten rotors that is not flagged at 0x380, rebuilds its record's three axis vectors
   from the saved basis at 0x100 and 0x110. */
void func_L11_00438460(char *p)
{
#define REC(o, i) (records + (*(int *)((i) * 4 + *(char **)((o) + 0x68) + 0x330) << 8))
    char *records;
    char *state = *(char **)(p + 0x68);
    int i;

    for (i = 0; i < 10; i++) {
        if (*(unsigned char *)(state + 0x380 + i) != 0)
            continue;
        records = (char *)D_L11_001B359C;
        qcopy_nc(REC(p, i) + 0x10, state + 0x110 + i * 0x10);
        func_00282CF0(REC(p, i) + 0xC0, state + 0x100 + i * 0x10, state + 0x110 + i * 0x10);
        records = (char *)D_L11_001B359C;
        *(int *)(REC(p, i) + 0xCC) = 0;
        func_00282F20(REC(p, i) + 0xC0, REC(p, i) + 0xC0, 1.0f);
        records = (char *)D_L11_001B359C;
        func_00282C88(REC(p, i) + 0xE0);
        records = (char *)D_L11_001B359C;
        *(float *)(REC(p, i) + 0xE8) = 1.0f;
        func_00282DD8(REC(p, i) + 0xD0, REC(p, i) + 0xE0, REC(p, i) + 0xC0);
        records = (char *)D_L11_001B359C;
        *(int *)(REC(p, i) + 0xDC) = 0;
        func_00282F20(REC(p, i) + 0xD0, REC(p, i) + 0xD0, 1.0f);
        records = (char *)D_L11_001B359C;
        func_00282DD8(REC(p, i) + 0xE0, REC(p, i) + 0xC0, REC(p, i) + 0xD0);
        records = (char *)D_L11_001B359C;
        *(int *)(REC(p, i) + 0xEC) = 0;
        func_00282F20(REC(p, i) + 0xE0, REC(p, i) + 0xE0, 1.0f);
        records = (char *)D_L11_001B359C;
        *(unsigned short *)(REC(p, i) + 0x34) |= 0x100;
    }
#undef REC
}

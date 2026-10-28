/* functional: medium. Hand-written from the assembly. Retail builds the tag word for func_001286C8 as bitfields of an uninitialised 64-bit local (in $s4): its low 32 bits are always 0x0103400B and its upper 32 bits are whatever the caller left in $s4. func_001286C8 stores only the low word of that argument (sw $a1) and then reuses $a1, so the honest form passes the 32-bit word 0x0103400B and nothing of $s4. The fifth argument (in $t0) is the source of the first copy. The frame is zeroed because retail passes the buffer on with its unwritten gap bytes holding whatever was on the stack (0 in every captured call); zeroing makes that deterministic. */
extern void func_001153D4(void *, void *, int);
extern int func_001286C8(int, unsigned int, void *, void *);

int func_00128FD0(int a0, int a1, int a2, int a3, void *a4)
{
    int frame[0x38 / 4 + 8];
    char *base = (char *)frame;
    int *size = (int *)(base + 0x30);

    { int k; for (k = 0; k < 0x38 / 4 + 8; k++) frame[k] = 0; }
    *size = 0x28;
    ((int *)base)[1] = a3;
    func_001153D4(base + 8, a4, a3);
    ((int *)base)[0] = a1;
    func_001153D4(base + a3 + 8, (void *)a2, a1);
    return func_001286C8(a0, 0x0103400Bu, base + 0x30, base);
}

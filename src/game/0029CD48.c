/* A unit of its own: at the default -G0 the sda globals are one assembler operand, the retail's
   absolute lui + load through the destination register, or one $gp store in the delay slot of
   the branch. func_0029CD20 reads its global itself and ignores the argument, but the retail
   sets $a0 from D_001A7B90 before calling it: the load survives only as an argument of the call. */

extern char D_001BAEC0[];
extern int D_00138180[];
extern int D_001A79F0 __attribute__((sda));
extern int D_001A7B90[] __attribute__((sda));
extern char *D_001A8CFC __attribute__((sda));

extern void *func_00115484(void *, int, int); /* memset */
extern void func_0029CD20(int);
extern int *func_00336DA8(int, int);
extern char *func_0034E5C0(int *, int);
extern void func_0029C0D0(void);
extern void func_0029C108(void);
extern void func_0029C0D8(void);
extern void func_0029CD18(void);

/* The level object's callback table: the two slots at +0x734C and +0x7350. */
typedef struct { char pad[0x734C]; void *cb1; void *cb2; } SubBf;

/* Clears the 0x40000-byte buffer with 0xCD and zeroes the fields 104 to 111 of the D_00138180 block. */
void func_0029CD48(void)
{
    char *state = D_001BAEC0;
    char *obj;

    func_00115484(*(void **)(state + 0x80), 0xCD, 0x40000);
    D_00138180[104] = 0;
    D_00138180[105] = 0;
    D_00138180[106] = 0;
    D_00138180[107] = 0;
    D_00138180[108] = 0;
    D_00138180[109] = 0;
    D_00138180[110] = 0;
    D_00138180[111] = 0;
    D_00138180[112] = 0;
    D_00138180[113] = 0;
    D_00138180[114] = 0;
    D_00138180[115] = 0;
    func_0029CD20(D_001A7B90[0]);
    obj = func_0034E5C0(func_00336DA8(0x3F490, *(int *)(state + 0x80)), 0x40000);
    D_001A8CFC = obj;
    if (D_001A79F0 == 0x1F5) {
        ((SubBf *)(obj + 0x38000))->cb1 = func_0029C0D0;
        ((SubBf *)(obj + 0x38000))->cb2 = func_0029CD18;
    } else {
        ((SubBf *)(obj + 0x38000))->cb1 = func_0029C108;
        ((SubBf *)(obj + 0x38000))->cb2 = func_0029C0D8;
    }
}

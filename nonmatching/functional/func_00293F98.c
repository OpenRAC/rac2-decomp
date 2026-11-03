/* functional: high. Unchecked: every captured call waits on the disc past the gate's 40M-instruction budget (NOTHING COMPARED). Nothing differs from retail: same calls, arguments, stores and loop bound (read 0x293F98-0x29406C in full; the part loop is written as a top-tested for, retail tests the first count before the loop and the bound after the store, which runs the same iterations). */

/* Loads disc file `index` of the table of contents (D_0014B540: base at +0x3E24, sector/size pairs at +0x3E28)
 * into the buffer of the world state D_001B8840 (+0x70) with func_002B7B18; when `flag` is set it first calls
 * func_002B7CE0(0) and func_0027D330(flag). It stores the index at +0x30, calls func_002B7CE0(1), then for
 * each 8-byte part record of the buffer (offset, count; stop at a zero count, at most 70) stores
 * buffer + offset + 0x800 at +0x74 + 4 * i. */

extern char D_0014B540[];
extern char D_001B8840[];
extern int func_002B7B18(int, int, int);
extern short func_002B7CE0(int);
extern void func_0027D330(int);

void func_00293F98(int index, int flag)
{
    char *entry = D_0014B540 + (index << 3);
    int *rec;
    int i;

    func_002B7B18(*(int *)(D_001B8840 + 0x70),
                  *(int *)(entry + 0x3E28) + *(int *)(D_0014B540 + 0x3E24),
                  *(int *)(entry + 0x3E2C));
    if (flag != 0) {
        func_002B7CE0(0);
        func_0027D330(flag);
    }
    *(int *)(D_001B8840 + 0x30) = index;
    func_002B7CE0(1);
    rec = *(int **)(D_001B8840 + 0x70);
    for (i = 0; i < 70; i++, rec += 2) {
        if (rec[1] == 0)
            break;
        *(int *)(D_001B8840 + 0x74 + 4 * i) = *(int *)(D_001B8840 + 0x70) + (rec[0] + 0x800);
    }
}

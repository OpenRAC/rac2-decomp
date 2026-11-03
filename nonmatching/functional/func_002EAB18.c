/* functional: high. Unchecked: every captured call waits on the disc past the gate's 40M-instruction budget (NOTHING COMPARED). Read 0x2EAB18-0x2EB148 in full: same reads, writes and calls in the same order (stores in jal delay slots before their calls); the archive header is read through plain offsets and some header words are re-read where retail keeps them in registers (no store in between); the 64-bit GS words are unsigned long; func_0029D4D0 is declared as the port's host function (int addresses); 0x132828 is called by its port symbol func_00132828 (the catalogue row func_00132818). */
extern char D_00189E20[];          /* +0x2C0, +0x2C4 ints, +0x2C8 float, +0x2290 flag */
extern char D_00152C00[];          /* the load state: +0x1C count, +0x20 mode, +0x22 selection, +0x2E disc entry, +0x38 GS word */
extern char D_0014B540[];          /* the disc table: +0x3E24 base sector, +0x3E58 (sector, length) pairs */
extern char D_001BAEC0[];          /* load buffers: +0x18 header, +0x38 first class, +0x48 end, +0x70 UI class, +0x78 UI info */
extern char D_00188660[];          /* +0x17B4 sound state */
extern float D_001B15A0;
extern int D_001B22B0, D_001B15A4;
extern int D_001A72D0, D_001A72D4, D_001A72F4;
extern char D_001B1740[], D_001CE4E0[], D_001D1580[];
extern int D_001D0E00[];
extern char *D_001D0600[];      /* class data address, its texture type in the top nibble */
extern int D_001B1B4C, D_001B1B40;
extern unsigned long D_001C4DC0[];
extern char D_001A91E0[];
extern char *D_001CDB80[];
extern short D_001CE300[];
extern int D_001A7290;
extern short D_001A7A18;
extern char *D_001B1604;
extern char D_001C2B40[], D_001C2C40[], D_001C2740[];
extern int D_001ABEC0[];
extern char *D_001B1B5C, *D_001B159C, *D_001B1B60, *D_001B1B64, *D_001B1B6C, *D_001B1D90;
extern int D_001B1D98, D_001B1D94, D_001B1D9C, D_001B1B74, D_001B1DA0;
extern char D_001F1D40[];
extern int D_001B2130, D_001B2134, D_001B2138, D_001B213C, D_001B2140;

extern void func_00290B48(void);
extern void func_00282A60(void *, int, int);
extern void func_0027A9F0(void);
extern void func_0027AB40(void);
extern void func_002FC1D8(void);
extern int func_002B7C10(char *, int, int);
extern void func_0027D330(int);
extern int func_00133580(int);
extern void func_0011AEA0(int);
extern int func_0029D4D0(int source, int destination);
extern void func_00293000(char *, int, int, char *);
extern int func_00282A18(int);
extern void func_00291EC0(char *);
extern void func_00293890(char *, char *, char *, int);
extern void func_00292328(int);
extern void func_002934B8(char *, char *);
extern void func_00291DE0(char *, int);
extern void func_00291CA8(char *, char *, char *, int);
extern void func_00282A88(void *, int);
extern void func_00282B50(void *, void *, int);
extern void func_0029F0C8(char *, int);
extern void func_0027B7E0(void);
extern void func_002EA968(void);
extern void func_002EAAA8(char *, int *);
extern int func_00132828(void);       /* jal 0x132828; the catalogue names it func_00132818 */

#define HI(o) (*(int *)(h + (o)))

/* Loads a level's archive: reads it from disc into the load buffer, unpacks it, registers its
   textures, classes, mobys, the UI class, collision points and parts, lays out the moby and
   pool buffers after it, and sets up its five sound banks. */
void func_002EAB18(void)
{
    char *h;
    char *base;
    char *records;
    char *rec;
    char *p;
    char **out;
    int size;
    int i;
    int count;
    int index;

    *(float *)(D_00189E20 + 0x2C8) = -1.0f;
    *(short *)(D_00152C00 + 0x20) = 2;
    *(short *)(D_00152C00 + 0x22) = -1;
    D_001B15A0 = 1.0f;
    D_001B22B0 = 0x100000;
    *(int *)(D_00189E20 + 0x2290) = 0;
    *(int *)(D_00189E20 + 0x2C0) = 0;
    *(int *)(D_00189E20 + 0x2C4) = 0;
    D_001B15A4 = 0;
    func_00290B48();
    D_001A72D4 = D_001A72F4;
    D_001A72D0 = D_001A72F4;
    func_00282A60(D_001B1740, 0x87654321, 16);
    func_00282A60(D_001CE4E0, -1, 0x2000);
    func_00282A60(D_001D1580, -1, 0xF00);
    func_00282A60(D_001D0E00, 0, 0xF0);
    func_0027A9F0();
    func_0027AB40();
    func_002FC1D8();

    index = *(short *)(D_00152C00 + 0x2E) * 8;
    func_002B7C10(*(char **)(D_001BAEC0 + 0x18) + 0x400000,
                  *(int *)(D_0014B540 + 0x3E58 + index) + *(int *)(D_0014B540 + 0x3E24),
                  *(int *)(D_0014B540 + 0x3E5C + index));
    func_0027D330(6);
    func_00133580(0);
    func_0011AEA0(0);
    size = func_0029D4D0((int)(*(char **)(D_001BAEC0 + 0x18) + 0x400000), (int)*(char **)(D_001BAEC0 + 0x18));
    func_0011AEA0(0);

    h = *(char **)(D_001BAEC0 + 0x18);
    func_00293000(h + HI(0x00), HI(0x08), 0, h + HI(0x0C));
    base = h + HI(0x04);
    records = base + HI(0x30);
    rec = h + HI(0x1C);
    D_001B1B4C = HI(0x18);
    if (HI(0x18) > 0) {
        i = 0;
        out = D_001D0600;
        do {
            int type = func_00282A18(*(unsigned short *)(rec + 4));
            i++;
            *out = records + *(int *)rec + (type << 28);
            rec += 16;
            out++;
        } while (i < D_001B1B4C);
    }

    func_00291EC0(base + HI(0x48));
    rec = h + HI(0x14);
    D_001B1B40 = 0;
    for (i = 0; i < HI(0x10); i++, rec += 32) {
        char *object = *(int *)rec != 0 ? base + *(int *)rec : 0;
        if (*(int *)(rec + 8) != 0) {
            D_001C4DC0[1] = 0xFFA0000000E0UL;
            D_001C4DC0[0] = *(unsigned long *)(D_00152C00 + 0x38);
            D_001C4DC0[2] = 0x0040000400004000UL;
            func_00293890(object, 0, D_001A91E0, *(int *)(rec + 4));
            D_001D0E00[D_001B1B40 - 1] = (int)0xFFFC0000;
        } else {
            func_00293890(object, h + HI(0x1C), rec + 16, *(int *)(rec + 4));
        }
    }

    count = D_001B1B40;
    *(int *)(D_00152C00 + 0x1C) = count;
    D_001CDB80[count] = *(char **)(D_001BAEC0 + 0x70);
    D_001CE300[count] = 0xD54;
    D_001CE4E0[0xD54] = *(unsigned char *)(D_00152C00 + 0x1C);
    D_001B1B40 = count + 1;
    D_001D0E00[count] = (int)0xFFFC0000;
    *(char **)(D_001BAEC0 + 0x38) = D_001CDB80[0];
    if (D_001A7290 != D_001A7A18)
        func_00292328(D_001A7A18);
    func_002934B8(D_001CDB80[0], *(char **)(D_001BAEC0 + 0x78));
    D_001D0E00[0] = (int)0xFFFC0000;
    D_001B1604 = base + HI(0x38);
    func_00291DE0(h + HI(0x2C), HI(0x28));
    func_00291CA8(h + HI(0x3C), base + HI(0x34), h + HI(0x24), HI(0x20));

    p = *(char **)(D_001BAEC0 + 0x18) + size;
    *(char **)(D_001BAEC0 + 0x48) = p;
    func_00282A88(D_001C2B40, 0x100);
    func_00282A88(D_001C2C40, 0x180);
    func_00282A88(D_001C2740, 0x400);
    func_00282B50(D_001C2740, D_001ABEC0, 0x40);
    D_001B1B5C = p;
    func_00282A60(p, 0, 0x4000);
    p += 0x4000;
    {
        char *first = D_001B1B5C;
        D_001B159C = first;
        func_0029F0C8(first, 0);
        first[0x20] = (char)0xFD;     /* retail keeps the pre-call value */
    }
    D_001B1B60 = D_001B159C + 0x100;
    D_001B1B60[0x20] = (char)0xFF;
    D_001B1B6C = p;
    p += 0x2000;
    D_001B1D98 = -1;
    D_001B1D90 = p;
    D_001B1B64 = D_001B1B60 + 0x3F00;
    D_001B1D94 = 0;
    D_001B1D9C = 0;
    func_00282A88(D_001F1D40, 0x200);
    func_0027B7E0();
    D_001B1B74 = 0x3C0;
    D_001B1DA0 = 0x1F4000;
    func_002EA968();
    *(unsigned int *)(D_00188660 + 0x17B4) = 0xFFFFFFFFu;

    *(int *)(base + HI(0x74) + 0x18 + 0x2C) = 0xC000;
    *(int *)(base + HI(0x74) + 0x18 + 0x28) = 0xC000;
    *(int *)(base + HI(0x70) + 0x18 + 0x2C) = 0xC000;
    *(int *)(base + HI(0x70) + 0x18 + 0x28) = 0xC000;
    *(int *)(base + HI(0x6C) + 0x18 + 0x2C) = 0xC000;
    *(int *)(base + HI(0x6C) + 0x18 + 0x28) = 0xC000;
    *(int *)(base + HI(0x68) + 0x18 + 0x2C) = 0xC000;
    *(int *)(base + HI(0x68) + 0x18 + 0x28) = 0xC000;
    *(int *)(base + HI(0x64) + 0x18 + 0x2C) = 0xC000;
    *(int *)(base + HI(0x64) + 0x18 + 0x28) = 0xC000;
    func_0011AEA0(0);
    func_002EAAA8(base + HI(0x74), &D_001B2140);
    func_002EAAA8(base + HI(0x6C), &D_001B2138);
    func_002EAAA8(base + HI(0x70), &D_001B213C);
    func_002EAAA8(base + HI(0x68), &D_001B2134);
    func_002EAAA8(base + HI(0x64), &D_001B2130);
    func_00132828();
}

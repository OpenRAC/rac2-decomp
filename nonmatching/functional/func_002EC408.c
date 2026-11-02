/* functional: high. Unchecked: the level change loads from disc and loops until the level is up, never returning within the gate's 40M-instruction budget (NOTHING COMPARED). Read 0x2EC408-0x2ECB6C in full against this C: same reads, writes and calls with the same arguments in the same order; retail reads D_001A79F0 only when D_001B1680 is not 22 and loads the light words before storing them (plain reads, no behaviour change); globals retail reaches through $gp are named by their address; func_00132828, func_001336D0 and func_00133710 are named by their jal addresses, the port's symbols (the catalogue rows are func_00132818, func_001336C0, func_00133700). */
extern char D_00139780[];          /* +0x00, +0x08: flag words */
extern int D_0013977C;
extern int D_00139810;
extern int D_00139814;
extern unsigned char D_001395E3;
extern char D_001393E0[];          /* +24 short, +348, +356, +380 ints */
extern char D_00152C00[];          /* +44, +46 shorts */
extern int D_00189E00[6];          /* handles: 0x188660 + 0x17A0 as retail forms it */
extern char D_001A63A8[];          /* +7 byte flag */
extern int D_001A7280;
extern int D_001A7284;
extern unsigned int D_001A7424;    /* also stored through gp-0x7BCC */
extern int D_001A79F0;             /* also gp-0x7600 */
extern unsigned char D_001A7BE8[]; /* also gp-0x7408 */
extern unsigned char D_001A7BD2, D_001A7BD3;
extern int D_001A8BB0;
extern int D_001ABEB0;             /* gp-0x3140 */
extern int D_001ABF0C;             /* gp-0x30E4 */
extern char D_001AC1E0[];
extern int D_001B1598;             /* also gp+0x25A8 */
extern unsigned char D_001B1640, D_001B1641, D_001B1642;
extern float D_001B1644, D_001B1648, D_001B164C, D_001B1650;
extern int D_001B1680;             /* also gp+0x2690 */
extern int D_001B16AC;
extern int D_001B2138;
extern int D_001B2140;
extern char *D_001B2148;
extern char D_001B8840[];          /* +84: the equipment piece */
extern char *D_001B8894;
extern char D_001B9040[];
extern char D_001BADC0[];
extern char D_001BAF80[];          /* +16 flag word */
extern char D_001C5540[];
extern int D_00214920[];
extern char D_00240450[];

extern void func_00282A60(void *, int, int);
extern void func_0029FAE0(void);
extern void func_0011AEA0(int);
extern void func_00133710(int, int, int, int, int);
extern void func_00133230(void);
extern int func_00132028(void);
extern void func_002E5FE0(void);
extern void func_002B7170(void);
extern void func_00132858(int);
extern void func_00132828(void);
extern void func_0026FEB8(const char *, ...);
extern void func_00284E18(int, int, int);
extern void func_00298F00(void);
extern void func_00298178(void);
extern void func_001336D0(void (*)(int));
extern void func_002B7CE0(int);
extern void func_0027D330(int);
extern int func_002939D0(void);
extern int func_00133580(int);
extern void func_002FCDA8(void);
extern void func_002EAB18(void);
extern void func_00133AA0(int index, void *buffer);
extern char *func_0029EFD0(int);
extern void func_002E6178(int);
extern void func_002ED260(void *);
extern void func_002FC280(void);
extern void func_002FC220(void);
extern void func_00284FC0(void);
extern void func_00285338(void);
extern void func_00284EA8(void);
extern void func_002B9000(void);
extern int func_002E9268(void);
extern void func_002EA8E8(void);
extern void func_002FC3C0(int);
extern int func_001261F0(int);
extern int func_00293A60(void);

void func_002EC408(void)
{
    int next;
    int cur;
    int i;
    int done;
    int started;
    char *v;

    func_00282A60(D_001BADC0, -1, 128);
    D_001A8BB0 = 6;
    next = D_001B1680;
    *(short *)(D_00152C00 + 44) = 0;
    *(short *)(D_00152C00 + 46) = 0;
    cur = D_001A79F0;
    if (next == 22 || cur == 22 || next == 23 || cur == 23)
        *(short *)(D_00152C00 + 46) = 1;
    else if (next == 26 || cur == 26)
        *(short *)(D_00152C00 + 46) = 2;

    if (D_001B1680 == 14 && D_001395E3 == 0)
        *(short *)(D_00152C00 + 46) = 3;

    if (D_001A7BE8[0] != 0 && D_001B1680 != 0 && !(D_00139810 & 0x200))
        D_001ABEB0 = 169;
    else if (D_001A7BE8[1] != 0 && D_001B1680 != 1 && !(D_0013977C & 0x800000))
        D_001ABEB0 = 23;
    else if (D_001A7BE8[5] != 0 && D_001B1680 != 5 && !(D_00139810 & 0x800))
        D_001ABEB0 = 171;
    else if (D_001A7BE8[8] != 0 && D_001B1680 != 8 && !(D_00139814 & 0x2000))
        D_001ABEB0 = 173;
    else if ((D_001A7BD2 != 0 || D_001A7BD3 != 0) && !(*(int *)D_00139780 & 0x4000000))
        D_001ABEB0 = 26;
    else if (D_001B1680 == 13 && !(*(int *)D_00139780 & 0x8000000))
        D_001ABEB0 = 27;
    else if (D_001A7BE8[16] != 0 && D_001B1680 != 16 && !(D_00139814 & 0x8000))
        D_001ABEB0 = 175;

    *(unsigned int *)(D_001BAF80 + 16) |= 0x80000000u;
    func_0029FAE0();
    func_0011AEA0(0);
    func_00133710(2, 0, 0, 0, 0);
    func_00133230();
    func_00132028();
    func_002E5FE0();
    func_002B7170();
    D_001A63A8[7] = 1;
    for (i = 0; i < 6; i++) {
        if (D_00189E00[i] != 0) {
            func_00132858(D_00189E00[i]);
            func_00132828();
            func_0026FEB8(D_001AC1E0, D_00189E00[i]);
            D_001B16AC = 0;
            D_00189E00[i] = 0;
        }
    }

    *(int *)(D_001B9040 + 568) = 16;
    *(int *)(D_001B9040 + 560) = 0;
    *(int *)(D_001B9040 + 564) = 0;
    *(int *)(D_001B9040 + 536) = 0;
    D_001B1640 = *(unsigned char *)(D_001B9040 + 560);
    D_001B1641 = *(unsigned char *)(D_001B9040 + 564);
    D_001B1642 = *(unsigned char *)(D_001B9040 + 568);
    D_001B1644 = *(float *)(D_001B9040 + 536);
    D_001B1648 = 524288.0f;
    D_001B164C = 255.0f;
    D_001B1650 = 128.0f;
    *(float *)(D_001B9040 + 540) = 524288.0f;
    *(float *)(D_001B9040 + 552) = 255.0f;
    *(float *)(D_001B9040 + 556) = 128.0f;
    func_00284E18(0, 0, 0);

    cur = D_001A79F0;
    if (D_001B1680 < 0) {
        while (!(*(int *)(D_001393E0 + 348) < 3 && *(int *)(D_001393E0 + 356) < 0)) {
            func_00298F00();
            func_00298178();
        }
        if (*(int *)(D_001393E0 + 380) != 0)
            *(int *)(D_001393E0 + 380) = 0;
        if (*(short *)(D_001393E0 + 24) >= 0)
            *(short *)(D_001393E0 + 24) = -1;
        D_001A7424 = D_001A7424 & ~0x200u;
        func_001336D0(0);
        D_001A63A8[7] = 0;
        func_002B7CE0(1);
        while (func_00132028() != 0)
            ;
        D_001A63A8[7] = 1;
        func_0027D330(6);
        D_001A79F0 = D_001B1680;
        func_002939D0();
        func_00133580(0);
        D_001A63A8[7] = 0;
        func_002FCDA8();
        return;
    }

    if ((unsigned int)cur < 19u && (cur != 0 || (*(int *)(D_00139780 + 8) & 2)) && cur < 28)
        D_001A7BE8[cur] = 2;

    {
        unsigned int w = *(unsigned int *)(D_001BAF80 + 16);
        D_001A79F0 = D_001B1680;
        D_001A7280 = 0;
        *(unsigned int *)(D_001BAF80 + 16) = w | 0x80000000u;
        D_001A7284 = 1;
    }
    started = 0;
    func_002EAB18();
    func_00133AA0(D_001A79F0, D_001C5540);

    {
        short kind = *(short *)(D_00152C00 + 46);
        int id = -1;
        if (kind == 3)
            id = 4930;
        else if (kind == 1)
            id = 4748;
        else if (kind == 2)
            id = 4749;
        if (id >= 0) {
            v = func_0029EFD0(id);
            D_001B2148 = v;
            *(unsigned short *)(D_001B8894 + 52) |= 1;
        } else {
            int *p = D_00214920;
            while (*p != 0) {
                *p = 0;
                p++;
            }
            func_002E6178(*(int *)(D_001B8840 + 84));
        }
    }
    func_002ED260(D_00240450);

    do {
        func_002FC280();
        func_002FC220();
        func_00284FC0();
        func_00285338();
        func_00284EA8();
        func_002B9000();
        done = func_002E9268();
        func_002EA8E8();
        func_00298F00();
        func_00298178();
        func_002FC3C0(1);
        func_001261F0(0);
        D_001B1598 = D_001B1598 + 1;
        if (D_001ABEB0 == 0 && started == 0)
            started = func_00293A60();
    } while (done == 0);

    D_001ABF0C = 0;
    if (started == 0) {
        do {
            func_0011AEA0(0);
            func_001261F0(0);
            func_00298F00();
            func_00298178();
        } while (func_00293A60() == 0);
    }
    while (!(*(int *)(D_001393E0 + 348) == 2 && *(int *)(D_001393E0 + 356) < 0)) {
        func_0011AEA0(0);
        func_001261F0(0);
        func_00298F00();
        func_00298178();
    }

    if (D_001B2138 != 0)
        func_00132858(D_001B2138);
    if (D_001B2140 != 0)
        func_00132858(D_001B2140);
    while (func_00132028() != 0)
        ;
    func_00132828();
    func_001336D0(0);
    func_00133580(0);
    func_00133580(0);
    D_001A63A8[7] = 0;
    func_002FCDA8();
}

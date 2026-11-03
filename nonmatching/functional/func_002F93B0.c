/* functional: high. Written from the assembly (the near miss's control flow kept): same reads, calls and stores in the same order; the shop state is plain offsets from D_0021F240 instead of a padded struct and a volatile field. */
extern char D_0021F240[];          /* the shop: +0x28 moby, +0x50 mode, +0x6C scroll, +0x78 sound handle,
                                      +0x80 selected, +0x84 busy, +0x88 animated, +0x90 animation,
                                      +0x140 rows of 0x18 (id, kind, ...), +0x740 row count */
extern char D_00138180[];          /* the pad: +0x1C4 pressed buttons */
extern int D_001B223C, D_001B2240, D_001B2244;
extern int D_001A79F8;             /* bolts */
extern int D_00139688[];
extern char D_00239BA0[];          /* 0xE0-byte item records: +0x88 price, +0x8E limit */
extern unsigned char D_00139568[];
extern int func_002E5CF8(int index, int flags, char *object);
extern void func_0028B6C8(int, int);
extern int func_002F6510(void);
extern void func_002F9198(void);

#define S_I(o) (*(int *)(D_0021F240 + (o)))
#define PRESSED (*(int *)(D_00138180 + 0x1C4))

/* The shop's list input: down/up (or their auto-repeat counters) move the selection by one row
   and scroll 56 pixels, the confirm button buys an affordable item (or plays the refusal), and
   the back button leaves through func_002F9198. Nothing while a purchase is busy. */
void func_002F93B0(void)
{
    int moved;
    int id;
    char *record;

    if (S_I(0x84) != 0)
        return;

    if ((PRESSED & 0x2000) || (D_001B2240 >= 16 && D_001B2240 % 10 == 1)) {
        if (S_I(0x6C) < 57) {
            moved = 0;
            if (S_I(0x80) < S_I(0x740) - 1) {
                S_I(0x80) = S_I(0x80) + 1;
                moved = 1;
            }
            if (moved) {
                if (S_I(0x88) != 0)
                    S_I(0x90) = (S_I(0x50) != 2) ? 1 : 3;
                S_I(0x6C) = S_I(0x6C) + 56;
                func_002E5CF8(1, 17, *(char **)(D_0021F240 + 0x28));
                if (S_I(0x78) != -1 && S_I(0x50) == 0)
                    func_0028B6C8(S_I(0x78), 0);
                S_I(0x78) = -1;
            }
        }
    }

    if ((PRESSED & 0x8000) || (D_001B223C >= 16 && D_001B223C % 10 == 1)) {
        if (!(S_I(0x6C) < -56)) {
            moved = 0;
            if (S_I(0x80) > 0) {
                S_I(0x80) = S_I(0x80) - 1;
                moved = 1;
            }
            if (moved) {
                if (S_I(0x88) != 0)
                    S_I(0x90) = (S_I(0x50) != 2) ? 1 : 3;
                S_I(0x6C) = S_I(0x6C) - 56;
                func_002E5CF8(1, 17, *(char **)(D_0021F240 + 0x28));
                if (S_I(0x78) != -1 && S_I(0x50) == 0)
                    func_0028B6C8(S_I(0x78), 0);
                S_I(0x78) = -1;
            }
        }
    }

    if ((PRESSED & 0x40) && !(D_001B2244 & 0x40)) {
        if (S_I(0x50) == 3 && S_I(0x144 + S_I(0x80) * 12) == 0)
            goto finish;
        if (S_I(0x50) == 0) {
            if (S_I(0x144 + S_I(0x80) * 24) == 0 && !(D_001A79F8 < func_002F6510()))
                goto activate;
            if (S_I(0x144 + S_I(0x80) * 24) != 1)
                goto rejected;
            id = S_I(0x140 + S_I(0x80) * 24);
            record = D_00239BA0 + D_00139568[id] * 224;
            if (!(D_00139688[id] < *(unsigned short *)(record + 0x8E)))
                goto rejected;
            if (D_001A79F8 < *(unsigned short *)(record + 0x88))
                goto rejected;
        }
activate:
        if (S_I(0x88) != 0)
            S_I(0x90) = 1;
        S_I(0x84) = 1;
        func_002E5CF8(0, 17, *(char **)(D_0021F240 + 0x28));
        goto finish;
rejected:
        func_002E5CF8(2, 17, *(char **)(D_0021F240 + 0x28));
    }
finish:
    if (PRESSED & 0x10)
        func_002F9198();
}

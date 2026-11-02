/* functional: medium. Near-miss C: same reads, writes and calls in retail order; only register allocation and scheduling differ. */
typedef struct {
    int mode;
    char pad04[0x10];
    int arg;
    char pad18[4];
    int pending;
    char pad20[0x100];
    int counter;
    char pad124[0x34];
    int timer;
    char pad15C[8];
    int step;
    int clear;
} PauseState;

typedef struct {
    char pad[0x15C];
    int level;
    char pad160[4];
    int delta;
} PauseInput;

extern char D_001F2840[];
extern PauseInput D_001393E0;
extern int D_001A7424;
extern int D_001B1684;
extern short D_0018A000[];
extern int D_001B18A8;
extern void func_002DDEC8(void);
extern int func_002B49E0(int, int, int, int, void *);
extern void func_002CAA58(void);
extern void func_002CAA88(void);
extern void func_002CAAA0(void);
extern void func_002CAB00(void);
extern void func_002CADB0(void);
extern void func_002E4AC8(void);
extern void func_002B6658(void);
extern void func_002CA5D0(void);

void func_002CA8A8(void)
{
    PauseState *S = (PauseState *)D_001F2840;

    S->counter = S->counter > 0x7CFF ? 0x7D00 : S->counter + 1;
    S->clear = 0;
    if (S->timer != 0)
        S->timer--;
    if (D_001393E0.level >= 3 || D_001393E0.delta >= 0)
        ((PauseState *)D_001F2840)->step = 0;
    else
        S->step++;
    func_002DDEC8();
    if ((D_001A7424 & 1) && ((PauseState *)D_001F2840)->mode == 4 && D_001B1684 >= 8) {
        if (func_002B49E0(4, 1, 1, ((PauseState *)D_001F2840)->arg, 0) == 0)
            return;
    }
    switch (((PauseState *)D_001F2840)->mode) {
    case 1:
        func_002CAA58();
        break;
    case 2:
        func_002CAA88();
        break;
    case 3:
        func_002CAAA0();
        break;
    case 4:
        func_002CAB00();
        break;
    case 5:
        func_002CADB0();
        func_002E4AC8();
        D_0018A000[0] = 10;
        D_001B18A8 = 0;
        return;
    }
    func_002B6658();
    func_002E4AC8();
    if (((PauseState *)D_001F2840)->pending != 0)
        func_002CA5D0();
}

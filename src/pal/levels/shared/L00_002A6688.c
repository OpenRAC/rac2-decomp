#include "include_asm.h"

#include "common.h"
extern unsigned char D_00189E20[];
extern unsigned char D_00189EA0[];
extern int D_L00_001A8F00 MACRO_ADDR;
extern void func_PAL_L00_002A6468(void);
extern void func_PAL_L00_002D29E8(void);
extern void func_PAL_L00_002B3608(void);
extern void func_L00_002ACA08(void);
extern int func_PAL_L00_002ACE70(void *, void *, void *);
extern void func_L00_002ADB40(void);
extern void func_L00_002ADD30(void);
extern void func_PAL_L00_002CB7A0(void);
extern void func_L00_002D2E68(void);
extern void func_L00_002D3068(void);
extern void func_L00_002AE0C8(void);
extern void func_PAL_L00_002B9C20(void);
extern void func_PAL_L00_002AC088(void);
extern void func_PAL_L00_002AB0C0(void);
extern void func_PAL_L00_002AB308(void);
extern void func_PAL_L00_002ABA88(void);
extern void func_PAL_L00_002AB830(void);
extern void func_PAL_L00_002A53A8(void);
extern void func_PAL_L00_002A56D0(void);
extern void func_PAL_L00_002B7688(void);
extern void func_L00_002A5368(void);
extern void func_L00_002A9460(void);
extern void func_L00_002AA178(int);
extern void func_PAL_L00_002B2018(void);
extern void func_PAL_L00_002B2230(void);
extern void func_PAL_L00_002B20F8(void);
extern void func_L00_002AFBC0(void);
extern int func_L00_002D6418(void);
extern void func_L00_002A7958(void);
extern void func_L00_002A7748(void);
extern void func_PAL_L00_002A6688(void);
extern void func_PAL_L00_002D6408(void);
extern void func_PAL_L00_002A62B0(void);
extern void func_PAL_L00_002D5680(void);
extern int func_L00_002A7000(void);
extern void func_L00_003080D0(void *);
extern int func_002A677C(void *);
extern void func_PAL_L00_002A7390(void);
extern void func_L00_002A9760(void);

/* Run the frame's ordered resident-player updates while its control mode is active. */
void func_PAL_L00_002A6CB8(void) {
    unsigned char *player = D_00189E20;
    unsigned char *hero;
    *(short *)(player + 0x2162) = 0;
    *(short *)(player + 0x2160) = 0;
    if (player[0x22B4]) { func_PAL_L00_002A6468(); return; }
    func_PAL_L00_002D29E8();
    func_PAL_L00_002B3608();
    func_L00_002ACA08();
    func_PAL_L00_002ACE70(player + 0x80, player + 0x90, player + 0x550);
    func_L00_002ADB40();
    func_L00_002ADD30();
    func_PAL_L00_002CB7A0();
    if (D_L00_001A8F00 == 2 || D_L00_001A8F00 == 6) {
        if (player[0x22B5]) func_L00_002D2E68();
        else func_L00_002D3068();
        return;
    }
    func_L00_002AE0C8();
    if (player[0x22B4]) return;
    func_PAL_L00_002B9C20();
    func_PAL_L00_002AC088();
    func_PAL_L00_002AB0C0();
    func_PAL_L00_002AB308();
    func_PAL_L00_002ABA88();
    func_PAL_L00_002AB830();
    func_PAL_L00_002A53A8();
    func_PAL_L00_002A56D0();
    func_PAL_L00_002B7688();
    func_L00_002A5368();
    func_L00_002A9460();
    func_L00_002AA178(0);
    func_PAL_L00_002B2018();
    func_PAL_L00_002B2230();
    func_PAL_L00_002B20F8();
    func_L00_002AFBC0();
    if (player[0x22B5] || func_L00_002D6418()) func_L00_002D2E68();
    else func_L00_002D3068();
    func_L00_002A7958();
    func_L00_002A7748();
    func_PAL_L00_002A6688();
    func_PAL_L00_002D6408();
    func_PAL_L00_002A62B0();
    func_PAL_L00_002D5680();
    hero = D_00189E20;
    if ((*(int *)(hero + 0x229C) != 0x16 && *(int *)(hero + 0x229C) != 0x1F && *(int *)(hero + 0x2294) != 0x31) || func_L00_002A7000())
        func_L00_003080D0(D_00189EA0);
    { unsigned char *base = D_00189E20; func_002A677C(*(void **)(base + 0x2290)); }
    func_PAL_L00_002A7390();
    func_L00_002A9760();
}


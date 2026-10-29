/* Nonmatching resource-loader reconstruction, 2026-10-28. No C coverage credit.
 * Four US checks, 0/28, retained672/700B with -O2 -G0
 * -ffunction-sections. The mode-formal correction and a partial state view
 * plus narrow unsplit edges remain672B. Broad -fno-gcse is worse668B
 * with frame0x20 and is rejected. Frame0x30 matches but the extra retained global high
 * half, bit-table scheduling, global scalar loads, poll padding and the
 * poll scheduling still differs. Reopen with independent global high-half
 * or poll-loop source evidence.
 *
 * Independent sceGsSyncV(u32 mode) interface evidence resolved the ignored
 * 32-bit mode argument. Canonical001261F0.c now has int(int unused_mode),
 * checked byte exact in US/US2/PAL. The retail graph011 body ignores mode;
 * calls here now truthfully pass zero. Interface witness only, no HLE code:
 * https://github.com/open-goal/jak-project/blob/master/game/graphics/sceGraphicsInterface.h
 * Actual002B7CE0 returns signed halfword stream+4 on all paths, so its
 * ignored result is int, not old externs' void. 002EF010 actual definition
 * returns unsigned long (64-bit ABI); selected explicitly uses signed low32.
 * 002EB158 and002B6D28 actual definitions return int. 002ED058/002EB598
 * mutate state and return void. 00282A60 fills32-bit words for the supplied
 * byte length. Its raw-only void-return hypothesis remains provisional;
 * it is not assumed to be libc memset or to return the destination.
 * Every cleared region extent is the actual argument:0x230,0x1D0 and six
 * 0x40 clears. Globals stay incomplete; no artificial allocation bounds,
 * volatile state fields, aliases, register pins or synthetic accesses.
 */

#include "common.h"
extern unsigned int D_00139768[];
extern unsigned char D_0018B020[], D_001B8840[];
extern unsigned char D_001B1450[], D_001B1390[], D_001B2980[], D_001B13D0[], D_001B1410[];
extern unsigned char D_001A63A8[];
extern unsigned int D_001BAF2C __attribute__((sda));
extern float D_001B15A0[] __attribute__((sda));
extern int D_001A8BB0[] __attribute__((sda));
extern int D_001B15A8[] __attribute__((sda));
extern int D_001B15AC[] __attribute__((sda));
extern float D_001A8C74[] __attribute__((sda));
extern int D_001A8C78[] __attribute__((sda));
extern int D_001B15A4[] SDATA(D_001B15A4);
extern unsigned long func_002EF010(int);
extern void func_00282A60(void *, unsigned int, int);
extern void func_0027D330(int);
extern int func_002B7CE0(int);
extern int func_002EB158(int);
extern void func_002EB598(void), func_002ED058(void), func_002E4AC8(void);
extern int func_001261F0(int), func_002B6D28(void);

void func_002EB7E8(int resource)
{
    int selected;
    unsigned char *state;
    unsigned char *stream;
    int field;
    if ((unsigned int)resource < 177)
        D_00139768[(unsigned int)resource >> 2] |= 1U << (resource & 31);
    selected = (int)func_002EF010(resource);
    if (selected < 0) return;
    func_00282A60(D_0018B020, 0, 0x230);
    state = D_001B8840;
    func_00282A60(state, 0, 0x1D0);
    func_00282A60(D_001B1450, 0, 0x40);
    func_00282A60(D_001B1390, 0, 0x40);
    func_00282A60(D_001B2980, 0, 0x40);
    func_00282A60(D_001B2980 + 0x40, 0, 0x40);
    func_00282A60(D_001B13D0, 0, 0x40);
    func_00282A60(D_001B1410, 0, 0x40);
    stream = D_001A63A8;
    *(unsigned int *)(state + 0x70) = D_001BAF2C - 0x100000;
    *(int *)(state + 0x30) = selected;
    *(unsigned int *)(state + 0x6C) = D_001BAF2C - 0x80000;
    D_001B15A0[0] = 1.0f;
    D_001A8BB0[0] = 2;
    D_001B15A8[0] = 1;
    D_001B15AC[0] = 52;
    D_001A8C74[0] = 1.0f;
    D_001A8C78[0] = 0;
    *(int *)(state + 0x34) = 0;
    *(int *)(state + 0x3C) = 0;
    D_001B15A4[0] = 0;
    if (*(short *)(stream + 4)) {
        func_0027D330(6);
        func_002B7CE0(1);
        func_002EB158(0);
    } else {
        func_002EB158(0);
        func_0027D330(6);
    }
    if (*(short *)(stream + 4)) func_002B7CE0(1);
    func_002EB598();
    func_002ED058();
    *(int *)(stream + 0x28) = 0;
    *(int *)(stream + 0x24) = *(int *)(D_001B8840 + 0x30) + 4000;
    while (*(short *)(stream + 0x72) != 3 || *(short *)(stream + 0x6C) >= 6000) {
        func_002E4AC8();
        func_001261F0(0);
    }
    state = D_001B8840;
    *(short *)(state + 0x48) = -3;
    func_002B6D28();
    func_002EB158(1);
    field = 0;
    if (*(short *)(state + 0x48) < 0) {
        do {
            func_001261F0(0);
            field--;
        } while (*(short *)(state + 0x48) < field);
    }
}

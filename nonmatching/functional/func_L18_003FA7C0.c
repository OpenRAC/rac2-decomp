/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Current nonmatching reconstruction; game compiler, -O2 -G0 -ffunction-sections.
   us: 18_damosel: 260 bytes, expected 288; func_L18_003FA7C0: 0 of 3 places match (src/levels/shared/L18_003FA7C0.c).
   us2: 18_damosel: 260 bytes, expected 288; func_L18_003FA7C0: 0 of 3 places match (src/levels/shared/L18_003FA7C0.c).
   pal: 18_damosel: 260 bytes, expected 288; func_L18_003FA7C0: 0 of 3 places match (src/levels/shared/L18_003FA7C0.c).
   The inner group limit and object base are snapshotted separately after the outer validity test, matching the retail lifetimes. Remaining differences concern loop/base construction and register allocation. Reopen with a natural source expression tree for the two group-walk checks.
   Historical screening comments below predate this measured C reconstruction. */
/* func_L18_003FA7C0 - 288 bytes, 3 place(s), level 18_damosel, retail at
   0x003fa7c0. Screened with tools/w10_screen.py: 0 call(s) [-]; data
   addresses materialised [0x200000, 0x1b0000, 0x1b0000, 0x1b0000]; float
   constants [-]; $gp-relative small data: no   saves: -; callee-saved
   registers saved [-]; words plain C cannot emit [-]. Head: addiu $sp, $sp,
   -0x10 ; lui $v0, 0x20 ; sd $s0, 0x0($sp) ; addiu $t9, $v0, -0x4CE0 ; lui
   $t7, 0x1B ; lw $t7, 0x2838($t7). Not matched in this wave: the body is
   straight-line code whose register allocation and the materialisation of
   its constant addresses have to be reproduced word for word. What would
   unblock it: the exact source expression tree, so this cc1 picks the same
   registers in the same order. */

typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern u16 *D_L18_001FB320[];
extern s32 D_L18_001B2838;
extern char *D_L18_001B281C;

/* Disables collision and marks every object in each of the eight linked groups. */
void func_L18_003FA7C0(char *self) {
    s32 *groups = (s32 *)(*(char **)(self + 0x68) + 0x60);
    s32 limit = D_L18_001B2838;
    s32 i;
    u16 *ids;
    char *object;
    for (i = 0; i < 8; i++) {
        s32 innerLimit;
        char *base;
        ids = D_L18_001FB320[groups[i]];
        if ((groups[i] & 255) == 255 || groups[i] > limit || !ids) continue;
        innerLimit = D_L18_001B2838;
        base = D_L18_001B281C;
        while ((s16)ids[-1] >= 0 || ids == D_L18_001FB320[groups[i]]) {
            object = base + ((*ids & 0x7FFF) << 8);
            if (!object) break;
            *(s32 *)(object + 0x98) = 0;
            *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) & 0xEFFF) | 0x43;
            ids++;
            if ((groups[i] & 255) == 255 || groups[i] > innerLimit || !ids) break;
        }
    }
}

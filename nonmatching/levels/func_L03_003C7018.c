/* 6 November 2026, round 2: new best C below; default -G0 profile, 656/656 bytes, 0/1 USA,
 * 92 diff lines (the previous form gave 102). Plain call arguments with literal 0.5f/0.0f
 * put half in $f20 before the first call as retail does; a group around the second text
 * call keeps the loop set-up (i, the constant 1, the coordinate pointers) after that call;
 * an unconditional (float)shift fixes the loop registers (i s3, shift s1, keys s2, buffer s4).
 * Left: half/zero swapped ($f21/$f20) once the group is in; in both text calls retail does
 * the whole row conversion before loading any other argument, here sched interleaves them;
 * retail's .y pointer is %hi/%lo(D_001B0164) where this forms base+4; loop increments sit
 * between mfc1 and mtc1. Measured, none closer: group around both calls or the first only
 * (668 bytes, extra $f22), group around the loop's row block (660), a `half` variable,
 * -ffast-math, -fno-schedule-insns, -fno-schedule-insns2 (652).
 */
/* Retained bounded near miss, 2026-10-28: default profile656/656 bytes.
 * Five forms: named half constant removes duplicated FPR and restores0xf0
 * frame; explicit row/zero/adjustment lifetimes and -fno-regmove tie the
 * remaining scheduling. -fno-schedule-insns and -fno-gcse reach652 bytes and
 * are not retained. First difference+0x4c is swapped persistenthalf/zero FPRs,
 * followed by independent argument setup hoisted across coordinate conversion.
 * Reopen with a measured genuine constant lifetime/scheduling witness.
 * Getter keeps its actual integer stored-address return; text drawing takes
 * an explicit pointer cast. Printer returnsint and is variadic. Font renderer
 * style is64-bit unsignedlong, and both ending wrappers returnint.
 * The actual local formatting capacity is128 bytes; its initialized text is
 * terminated by the verified sprintf-style helper before font consumption.
 * Four key words16 bytes and four coordinate pairs32 bytes are complete.
 */
#include "common.h"

struct MenuCoordinate { float x, y; };
extern unsigned char *D_L03_001A904C __attribute__((sda));
extern float D_L03_001B014C SDATA(D_L03_001B014C);
extern float D_L03_001B0150 SDATA(D_L03_001B0150);
extern float D_L03_001B0154 SDATA(D_L03_001B0154);
extern float D_L03_001B0158 SDATA(D_L03_001B0158);
extern struct MenuCoordinate D_L03_001B0160[];
extern struct MenuCoordinate D_L03_001B0160_gp[] SDATA(D_L03_001B0160);
extern int D_L03_001B0140 SDATA(D_L03_001B0140);
extern int D_L03_001B3280 __attribute__((sda));
extern float D_L03_001B3284 __attribute__((sda));
extern char D_L03_001B0190[], D_L03_001B0198[];
extern unsigned char D_001A7A7C[] __attribute__((sda));
extern int func_00336D50(unsigned char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern unsigned char *func_00288FB8(int);
extern int func_00115DA8(char *, char *, ...);
extern int func_00283CF0(float);
extern int func_0027FB40(int, int, unsigned long, unsigned char *, int);
extern int func_L00_00443DF8(char *);
extern int func_L00_00443E18(char *);

int func_L03_003C7018(void)
{
    if (D_L03_001A904C) {
        func_00300A00((char *)func_00336D50(D_L03_001A904C + 0x8710, 0xc6), 0x60442d00, D_L03_001B014C,
            (float)(int)(D_L03_001B0150 * D_L03_001B3284 + 0.5f), D_L03_001B0154, D_L03_001B0158, 0.0f);
        do {
            func_00300A00((char *)func_00336D50(D_L03_001A904C + 0x8710, 0xc7), 0x55f0c070, D_L03_001B014C,
                (float)(int)(D_L03_001B0150 * D_L03_001B3284 + 0.5f), D_L03_001B0154, D_L03_001B0158, 0.0f);
        } while (0);
        {
            int keys[4] = {11599,12116,12769,12770};
            unsigned char buffer[128];
            int i;
            for (i = 0; i < 4; i++) {
                int shift = 5;
                int x;
                float y;
                unsigned char *label = func_00288FB8(keys[i]);
                if (i == 1) {
                    func_00115DA8((char *)buffer, D_L03_001B0190, label, D_L03_001B0140 + 1);
                    shift = -4;
                } else {
                    func_00115DA8((char *)buffer, D_L03_001B0198, label);
                }
                x = func_00283CF0(D_L03_001B0160_gp[i].x);
                {
                    float adjustment = (float)shift;
                    y = D_L03_001B0160[i].y * D_L03_001B3284 + 0.5f;
                    if (D_L03_001B3280 == 1)
                        y += adjustment;
                }
                func_0027FB40(x, func_00283CF0((float)(int)y), 0x80808080UL, buffer, 0x80);
            }
        }
        if (D_001A7A7C[0]) {
            func_L00_00443DF8((char *)D_L03_001A904C + 0x36f28);
            func_L00_00443E18((char *)D_L03_001A904C + 0x36f28);
        }
    }
    return 1;
}


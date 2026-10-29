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

/* Four genuine text identifiers, one128-byte formatting buffer and four
 * coordinate pairs. The text formatter writes through its ordinary char
 * interface; no shortened object or scheduling-only volatile is used. */
int func_L03_003C7018(void)
{
    if (D_L03_001A904C) {
        int text;
        float half = 0.5f, row, zero;
        text = func_00336D50(D_L03_001A904C + 0x8710, 0xc6);
        row = (float)(int)(D_L03_001B0150 * D_L03_001B3284 + half);
        zero = 0.0f;
        func_00300A00((char *)text, 0x60442d00, D_L03_001B014C, row,
            D_L03_001B0154, D_L03_001B0158, zero);
        text = func_00336D50(D_L03_001A904C + 0x8710, 0xc7);
        row = (float)(int)(D_L03_001B0150 * D_L03_001B3284 + half);
        func_00300A00((char *)text, 0x55f0c070, D_L03_001B014C, row,
            D_L03_001B0154, D_L03_001B0158, zero);
        {
            int keys[4] = {11599,12116,12769,12770};
            unsigned char buffer[128];
            int i;
            for (i = 0; i < 4; ++i) {
                int shift = 5, x, y;
                unsigned char *label = func_00288FB8(keys[i]);
                if (i == 1) {
                    func_00115DA8((char *)buffer, D_L03_001B0190, label, D_L03_001B0140+1);
                    shift = -4;
                } else func_00115DA8((char *)buffer, D_L03_001B0198, label);
                x = func_00283CF0(D_L03_001B0160_gp[i].x);
                {
                    row = D_L03_001B0160[i].y * D_L03_001B3284 + half;
                    {
                        float adjustment = (float)shift;
                        if (D_L03_001B3280 == 1) row += adjustment;
                    }
                    y = func_00283CF0((float)(int)row);
                }
                func_0027FB40(x, y, 0x80808080UL, buffer, 0x80);
            }
        }
        if (D_001A7A7C[0]) {
            func_L00_00443DF8((char *)D_L03_001A904C + 0x36f28);
            func_L00_00443E18((char *)D_L03_001A904C + 0x36f28);
        }
    }
    return 1;
}

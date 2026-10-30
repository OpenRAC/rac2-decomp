/* Complete C reconstruction; not linked and no matching credit.
 * 2026-10-30, game -O2 -G8 -ffunction-sections:
 * 1064/1064 bytes, USA v1.01 0/1; USA v2.00 and PAL identities absent.
 * The full 128-byte formatting buffer gives the retail 0xD0 frame. FP constant
 * roles, 0x8710/one saved roles, text pointer lifetime and outgoing argument
 * scheduling differ. Two contract/source trials. Reopen with independent constant
 * lifetime and text-helper scheduling evidence, not narrowed color parameters.
 * Colors remain 64-bit; the seven-argument wrapper forwards that width and the
 * text pointer to its deep consumer. Its current int-only source declaration is
 * incomplete for a native ABI and must be audited before native use. The lookup
 * returns its real 32-bit address word; func_0027F5B8 has the real void contract.
 */
#include "common.h"

extern int D_001A7340;
extern char *D_L05_001A904C;
extern float D_L05_001B2D84;
extern int D_L05_001B2D80;
extern int D_L05_001B3578;
extern int D_L05_001B13EC __attribute__((sda));
extern int D_L05_001B1350[] SDATA(D_L05_001B1350);
extern int D_L05_001B13F8[][3] SDATA(D_L05_001B13F8);
extern u8 D_001A7A0A;
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00336D50(void *, int);
extern void func_00300968(void *, int, float, float, float, float);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, char *, ...);
extern int func_001157AC(char *);
extern int func_0027FB40(int, int, u64, char *, int);
extern void func_L05_00303000(int, int, int, int, u64, char *, int);
extern void func_0027F5B8(int, int, u64, char *, int);

int func_L05_00420360(void)
{
    char text[128];
    float center = func_00283CE0(D_001A7340) * 0.5f;
    char *label;
    int x;
    int y;
    int mission;
    int previous;
    int rank;
    int reward;
    float row;

    if (D_L05_001A904C == 0)
        return 1;
    func_00300968((void *)func_00336D50(D_L05_001A904C + 0x8710, 0x45),
                  0x60442D00, center,
                  (float)(int)(D_L05_001B2D84 * 200.0f + 0.5f), 1.0f, 0.0f);
    func_00300968((void *)func_00336D50(D_L05_001A904C + 0x8710, 0x44),
                  0x55F0C070, center,
                  (float)(int)(D_L05_001B2D84 * 200.0f + 0.5f), 1.0f, 0.0f);
    func_00115DA8(text, func_00288FB8(0x2F72), D_L05_001B13EC + 1);
    label = func_00288FB8(0x2F93);
    x = func_00283CF0(center);
    row = D_L05_001B2D84 * 46.0f + 0.5f;
    if (D_L05_001B2D80 == 1)
        y = (int)(row - 2.0f);
    else
        y = (int)row;
    func_0027FB40(x, y, 0x80F0F0F0ULL, label, func_001157AC(label));
    label = func_00288FB8(0x31CB);
    y = (int)(D_L05_001B2D84 * 131.0f + 0.5f);
    func_L05_00303000(117, y, 280, 400, 0x80F0F0F0ULL,
                     label, func_001157AC(label));
    mission = D_L05_001B3578;
    previous = D_L05_001B1350[mission] - 1;
    rank = previous < 3 ? previous : 2;
    reward = D_L05_001B13F8[mission][rank];
    if (D_001A7A0A != 0)
        reward *= 10;
    if (reward == 0)
        func_00115DA8(text, func_00288FB8(0x11F5));
    else
        func_00115DA8(text, func_00288FB8(0x2FC6), reward);
    y = (int)(D_L05_001B2D84 * 210.0f + 0.5f);
    func_L05_00303000(117, y, 280, 400, 0x80F0F0F0ULL,
                     text, func_001157AC(text));
    row = D_L05_001B2D84 * 294.0f + 0.5f;
    if (D_L05_001B2D80 == 1)
        y = (int)(row + 3.0f);
    else
        y = (int)row;
    func_0027F5B8(117, y, 0x80F0F0F0ULL, func_00288FB8(0x31CC), -1);
    row = D_L05_001B2D84 * 294.0f + 0.5f;
    if (D_L05_001B2D80 == 1)
        y = (int)(row + 3.0f);
    else
        y = (int)row;
    func_0027F5B8(274, y, 0x80F0F0F0ULL, func_00288FB8(0x31CD), -1);
    return 1;
}

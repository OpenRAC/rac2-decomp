#include "include_asm.h"

struct pos {
    float x;
    float y;
};
extern char D_001ADBC8[];
extern char D_001ADF98[];
extern int D_001ADF80 __attribute__((sda));
extern int D_001ADF84;
extern int D_001ADF88 __attribute__((sda));
extern int D_001ADF8C;
extern int D_001ADF90 __attribute__((sda));
extern const char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern void func_00336A30(char *, int);
extern void func_PAL_00338770(char *);
extern int func_002B0DB8(void);
extern int func_002B0D60(void);
extern int func_002B0D70(void);
extern float *func_00335E10(char *);
extern void func_00335E38(char *, float, float, float, float);
extern void func_0028FC48(int, int, int, int, unsigned long, int);

/* formats three message strings (0x2DBB to 0x2DBD) and a count each into buffers at +0x600/+0x618/+0x630,
   places the text objects at +0x410/+0x458/+0x4A0 from the position pointer at +0x2A8, then draws one box;
   func_0028FC48 takes its colour as unsigned long (as in 002D5E98-g8.c): with an int the argument setup
   is scheduled differently from retail */
void func_PAL_00340D78(char *self)
{
    float zero = 0.0f;

    func_00115DA8(self + 0x6C0, D_001ADBC8, func_00288FB8(0xBCC));
    func_00336A30(self + 0x470, 0);
    func_PAL_00338770(self + 0x470);
    func_00115DA8(self + 0x6C0, D_001ADF98, func_002B0DB8());
    func_00335E38(self + 0x470, func_00335E10(self + 0x470)[0] + (float)D_001ADF90,
                  func_00335E10(self + 0x470)[1], zero, zero);
    func_00336A30(self + 0x470, 2);
    func_PAL_00338770(self + 0x470);

    func_00115DA8(self + 0x6D8, D_001ADBC8, func_00288FB8(0xBCD));
    func_00336A30(self + 0x4C8, 0);
    func_PAL_00338770(self + 0x4C8);
    func_00115DA8(self + 0x6D8, D_001ADF98, func_002B0D60());
    func_00335E38(self + 0x4C8, func_00335E10(self + 0x4C8)[0] + (float)D_001ADF90,
                  func_00335E10(self + 0x4C8)[1], zero, zero);
    func_00336A30(self + 0x4C8, 2);
    func_PAL_00338770(self + 0x4C8);

    func_00115DA8(self + 0x6F0, D_001ADBC8, func_00288FB8(0xBCE));
    func_00336A30(self + 0x520, 0);
    func_PAL_00338770(self + 0x520);
    func_00115DA8(self + 0x6F0, D_001ADF98, func_002B0D70());
    func_00335E38(self + 0x520, func_00335E10(self + 0x520)[0] + (float)D_001ADF90,
                  func_00335E10(self + 0x520)[1], zero, zero);
    func_00336A30(self + 0x520, 2);
    func_PAL_00338770(self + 0x520);

    func_PAL_00338770(self + 0x578);
    {
        struct pos *pos = *(struct pos **)(self + 0x2D8);

        func_0028FC48((int)pos->x + D_001ADF80, (int)pos->y + D_001ADF84, (int)pos->x + D_001ADF88,
                      (int)pos->y + D_001ADF8C, 0x55F0C070UL, 0);
    }
}

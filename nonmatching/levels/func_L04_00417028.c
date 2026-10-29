/* Retained timer HUD, 2026-10-28: best720/736B,0/2US.
 * Three bounded trials: default712; truthful absolute UI-scale view with
 * -mno-split-addresses720; narrow no-cse-follow-jumps ties720, rejected.
 * Retail retains a saved format pointer across message lookup; C rematerializes
 * the address and changes FP conversion scheduling. No forced registers.
 * Format lookup returns an s32 target address (actual RC2 definition), sprintf
 * returns int and is variadic, strlen returns32-bit length, draw returns int
 * and takes a genuine64-bit style word0x80F0F0F0.
 * Real interface finding: existing matched0029B658 C omits four FP arguments
 * transparently forwarded by its60B retail wrapper. Callee003384C0 saves/uses
 * F12..F15 at+2C/+34/+3C/+44; parent notified for canonical definition repair.
 * Caller uses two64B stack strings; formatting is unbounded as in retail.
 * No larger bounds or safety of arbitrary external localized strings claimed.
 */
#include "common.h"
extern s32 func_00288FB8(s32);
extern int func_00115DA8(char *, const char *, ...);
extern unsigned int func_001157AC(const char *);
extern void func_0027EB88(int, int, int, int, int, int);
/* The wrapper forwards F12..F15 unchanged to003384C0, whose prologue saves
 * all four parameters. Existing two-int wrapper source needs that same full
 * interface before this caller could be credited. */
extern void func_0029B658(int, int, float, float, float, float);
extern int func_0027FBD8(int, int, u64, u8 *, int);
extern int D_L04_001A8FE4;
extern int D_L04_001B0920_gp SDATA(D_L04_001B0920);
extern const char D_L04_001B0B20[], D_L04_001B0B38[];
extern float D_L04_001B2D44 NOT_SDA;
extern int D_001A7340;

/* Two real64-byte stack strings, matching the retail formatting buffers.
 * Message lookup returns a32-bit target address; the font style is genuinely
 * 64-bit, matching the canonical draw definition rather than a fake int. */
void func_L04_00417028(void)
{
    char output[64], label[64];
    char *message;
    const char *format;
    int ticks;
    func_00115DA8(label, (const char *)func_00288FB8(0x2F82), D_L04_001A8FE4);
    if ((D_L04_001B0920_gp / 60) % 60 < 10) {
        format = D_L04_001B0B20;
        message = (char *)func_00288FB8(0x2F83);
        ticks = D_L04_001B0920_gp;
        func_00115DA8(output, format, label, message,
            ticks / 216000, (ticks / 3600) % 60, (ticks / 60) % 60, (ticks / 6) % 10);
    } else {
        format = D_L04_001B0B38;
        message = (char *)func_00288FB8(0x2F83);
        ticks = D_L04_001B0920_gp;
        func_00115DA8(output, format, label, message,
            ticks / 216000, (ticks / 3600) % 60, (ticks / 60) % 60, (ticks / 6) % 10);
    }
    func_0027EB88((int)(D_L04_001B2D44 * 112.0f + 0.5f),
        (int)(D_L04_001B2D44 * 142.0f + 0.5f), 50, D_001A7340 - 50, 96, 0x60442D00);
    func_0029B658(96, 0x55F0C070,
        (float)(int)(D_L04_001B2D44 * 112.0f + 0.5f),
        (float)(int)(D_L04_001B2D44 * 142.0f + 0.5f), 50.0f, (float)(D_001A7340 - 50));
    func_0027FBD8(D_001A7340 / 2, (int)(D_L04_001B2D44 * 118.0f + 0.5f),
        0x80F0F0F0ULL, (u8 *)output, func_001157AC(output));
}

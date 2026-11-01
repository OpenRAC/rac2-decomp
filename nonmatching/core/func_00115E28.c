/* from src/core/00115200.c, in place of its INCLUDE_ASM line. The catalogue's 64-byte row
   func_00115E28 is two functions: newlib's abort (16 bytes) and, at 0x00115E38, its
   __assert (48 bytes), which four jals reach (docs/LEVELS.md). With this C in src/ the boot
   links byte-identical, but the build reports "func_00115E28: 16 bytes, expected 64" and
   tests/check_repository.py rejects func_00115E38, which is in no catalogue. It can go back
   into src/ once the row is split into 16 and 48 bytes. */
#include "include_asm.h"

extern void *D_00133E74;

/* The exit thunk (src/core/00131780.c): it never returns, so neither function below has
   an epilogue. */
extern void func_00131CA8(int status) __attribute__((noreturn));
/* fiprintf */
extern void func_00115CF0(void *stream, const char *fmt, ...);
/* "assertion \"%s\" failed: file \"%s\", line %d\n" */
extern char D_0013A370[];

void func_00115E28(void) __attribute__((noreturn));

/* newlib's abort. The catalogue's 64-byte row also holds func_00115E38 (docs/LEVELS.md). */
void func_00115E28(void)
{
    func_00131CA8(1);
}

/* newlib's __assert: prints to the runtime record's stderr (+0xC) and aborts. */
void func_00115E38(const char *file, int line, const char *expr)
{
    func_00115CF0(*(void **)((char *)D_00133E74 + 0xC), D_0013A370, expr, file, line);
    func_00115E28();
}

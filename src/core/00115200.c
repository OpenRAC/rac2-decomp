#include "include_asm.h"

extern void *D_00133E74;

extern void *D_0013A308;

/* Returns the address of errno: the current reentrancy block pointer D_00133E74. */
void *func_00115200(void)
{
    return D_00133E74;
}

/* Returns the address of the pointer variable D_0013A308. */
void **func_00115210(void)
{
    return &D_0013A308;
}


ASM_FUNC("asm/core", func_00115250);

ASM_FUNC("asm/core", func_00115340);

ASM_FUNC("asm/core", func_001153D4);

ASM_FUNC("asm/core", func_00115484);

ASM_FUNC("asm/core", func_00115544);

ASM_FUNC("asm/core", func_00115690);

ASM_FUNC("asm/core", func_001157AC);

/* Newlib's original r5900/strncmp.S, Cygnus Solutions (1999), from the
 * public SSXModding/ps2-ee-toolchain snapshot b595ded. Its complete MMI
 * body assembles byte-identically in all three releases; it is not C. */
ASM_FUNC("asm/core", func_001158F4);

ASM_FUNC("asm/core", func_00115AC0);


extern void func_00131CA8(int status) __attribute__((noreturn));
extern void func_00115CF0(void *stream, const char *format, ...);
extern char D_0013A370[];

/* Newlib abort and its separately entered assertion reporter. */
void func_00115E28(void) __attribute__((noreturn));

/* Newlib abort: leaves the program through func_00131CA8 with status 1. */
void func_00115E28(void)
{
    func_00131CA8(1);
}

/* Newlib assertion failure reporter: prints the failed expression with file and line through
   func_00115CF0, then aborts. */
void func_00115E38(const char *file, int line, const char *expression)
{
    func_00115CF0(*(void **)((char *)D_00133E74 + 0xC),
                  D_0013A370, expression, file, line);
    func_00115E28();
}


extern int D_001341E0;

extern int D_001341E4;

extern int D_00134DB8;

extern int func_0011AB10(void);

extern void func_0011AC60(int arg0);

/* Recursive lock acquire: if the current id from func_0011AB10 is not the owner D_001341E0,
   waits on semaphore D_00134DB8 and becomes owner; always raises the depth D_001341E4. */
int func_00116300(void) {
    int id = func_0011AB10();

    if (D_001341E0 != id) {
        func_0011AC60(D_00134DB8);
        D_001341E0 = id;
        return ++D_001341E4;
    }
    return ++D_001341E4;
}

/* Stores value in the word at offset 0x58 of the current reentrancy block D_00133E74. */
void func_001163A0(unsigned int value)
{
    *(unsigned int *)((unsigned char *)D_00133E74 + 0x58) = value;
}

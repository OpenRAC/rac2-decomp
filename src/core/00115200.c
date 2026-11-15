#include "include_asm.h"
#include "names.h"

extern void *D_00133E74;

extern void *D_0013A308;

/* Returns the pointer to the record the C library uses to keep its own state. */
void *libc_get_state_record(void)
{
    return D_00133E74;
}

/* Returns the address of a fixed block of C library data. */
void **libc_get_data_block(void)
{
    return &D_0013A308;
}


/* Searches memory for the first byte that matches a value. */
ASM_FUNC("asm/core", func_00115250);

/* Compares two blocks of memory and says which one is bigger, or if they match. */
ASM_FUNC("asm/core", func_00115340);

/* Copies a block of memory from one place to another. */
ASM_FUNC("asm/core", func_001153D4);

/* Fills a block of memory with one byte value. */
ASM_FUNC("asm/core", func_00115484);

/* Compares two text strings and says which one comes first, or if they match. */
ASM_FUNC("asm/core", func_00115544);

/* Copies a text string, including its ending zero, to another place. */
ASM_FUNC("asm/core", func_00115690);

/* Counts how many characters are in a text string. */
ASM_FUNC("asm/core", func_001157AC);

/* Newlib's original r5900/strncmp.S, Cygnus Solutions (1999), from the
 * public SSXModding/ps2-ee-toolchain snapshot b595ded. Its complete MMI
 * body assembles byte-identically in all three releases; it is not C. */
/* Compares the first few characters of two text strings. */
ASM_FUNC("asm/core", func_001158F4);

/* Copies up to a set number of characters of a text string and pads with zeros. */
ASM_FUNC("asm/core", func_00115AC0);


extern void exit_ignoring_status(int status) __attribute__((noreturn));
extern void func_00115CF0(void *stream, const char *format, ...);
extern char D_0013A370[];

/* Newlib abort and its separately entered assertion reporter. */
void func_00115E28(void) __attribute__((noreturn));

/* Stops the program by exiting with an error code. */
void func_00115E28(void)
{
    exit_ignoring_status(1);
}

/* Prints a failed-check message with the file, line and test text, then stops the program. */
void assert_fail_abort(const char *file, int line, const char *expression)
{
    func_00115CF0(*(void **)((char *)D_00133E74 + 0xC),
                  D_0013A370, expression, file, line);
    func_00115E28();
}


extern int D_001341E0;

extern int D_001341E4;

extern int D_00134DB8;

extern int GetThreadId(void);

extern void WaitSema(int arg0);

/* Takes the memory lock. If another thread holds it, this waits; the same thread can take it again. */
int malloc_lock_acquire(void) {
    int id = GetThreadId();

    if (D_001341E0 != id) {
        WaitSema(D_00134DB8);
        D_001341E0 = id;
        return ++D_001341E4;
    }
    return ++D_001341E4;
}

/* Sets the starting number for the random number generator. */
void func_001163A0(unsigned int value)
{
    *(unsigned int *)((unsigned char *)D_00133E74 + 0x58) = value;
}

#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void func_L02_003D1ED0(char *, TI128 *);
extern void func_002A7A00(char *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_L02_0032D5F8(char *, int, char *, char *, int, int, float *, void *, void *, float);
extern void func_0029F338(char *);
extern char D_L02_001A8F20[] __attribute__((sda));

/* When the actor is drawn and still holds its sub-object, builds a vector from 0.1 and 1/6,
   offsets it by the vector at D_L02_001A8F20 and passes both to func_PAL_L02_0032D5F8 with the
   sub-object's +0x10 and +0xF0 records; then releases the sub-object in every case. The
   caller's quadword is copied to the stack (as retail does) and not read again. */
void func_PAL_L02_003D5F20(char *self, TI128 *pos) {
    char *state = *(char **)(self + 0x68);
    float copy[4];
    float vec[4];

    *(TI128 *)copy = *pos;
    if (*(unsigned char *)(self + 0x31) != 0 && *(char **)(state + 0x2E4) != 0) {
        func_002A7A00((char *)vec, 0.120000005f, 0.20000002f);
        func_00282CC0(vec, vec, D_L02_001A8F20);
        func_PAL_L02_0032D5F8(self, 0x9D8, *(char **)(state + 0x2E4) + 0x10, *(char **)(state + 0x2E4) + 0xF0,
                    0, 0, vec, D_L02_001A8F20, D_L02_001A8F20, 0.004f);
    }
    func_0029F338(*(char **)(state + 0x2E4));
    *(char **)(state + 0x2E4) = 0;
}


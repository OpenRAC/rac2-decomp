#include "include_asm.h"
#include "names.h"

extern int D_001AA3B4 __attribute__((sda));
extern void func_002A8860(void *, int);
extern int func_00282978(void *);
extern void func_002B9180(void *);

/* Updates the colour of a particle and removes it when its timer runs out. */
void func_002C5020(char *object)
{
    DecrementTopByte(object + 4, D_001AA3B4);
    if (FastDecTimer(object + 0xA))
        KillParticle(object);
}

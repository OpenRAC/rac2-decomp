#include "include_asm.h"
#include "names.h"

extern unsigned char D_L00_001B26B4[];
extern int func_00282948(void *p);

/* Advances the resident fade timer by one step. */
void func_L00_0037E640(void)
{
    FastFloatHelperD(D_L00_001B26B4);
}

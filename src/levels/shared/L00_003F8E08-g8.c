#include "include_asm.h"

/* Functions whose retail body reaches level data through $gp (small data area). */
extern void func_2EE5B0(void *, void *, void *);
extern void func_2EE108(void *, void *, void *);

extern int D_L00_001B0BE0 __attribute__((sda));

/* Turns a fixed offset by the moby's facing and moves it to the moby's position, giving a
   point in the world. */
void func_L00_003FE280(char *sourceMoby, char *worldPoint)
{
    func_2EE5B0(worldPoint, &D_L00_001B0BE0, sourceMoby + 0xC0);
    func_2EE108(worldPoint, worldPoint, sourceMoby + 0x10);
}

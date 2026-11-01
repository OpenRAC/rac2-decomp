#include "include_asm.h"

#include "common.h"
extern int func_002ED688(void *);
extern int func_002A77E0(int);
extern int func_002E5CF8(int, int, char *);
extern void func_L05_00379FA0(float, float, float, void *, int, int, int, float, int, int, int);

/* Kills the object: the type at 0x20 picks the effect, and the hit state at 0x268
   ends up at 0x19. */
void func_PAL_L10_0041DF98(void *a0)
{
    void *s0 = a0;
    void *s1 = *(void **)((char *)s0 + 0x68);
    void *v0 = func_002ED688(s0);

    if (v0 == 0)
        return;
    if (*(int *)((char *)v0 + 0x120) == 0)
        return;
    if (*(int *)((char *)s1 + 0x268) != 0)
        return;
    if (*(unsigned char *)((char *)s0 + 0x20) == 2) {
        func_L05_00379FA0(0.9f, 13.0f, 4.5f, s0, 0x60000080, 0, 1, 1.0f, 0, -1, 0);
    } else if (*(unsigned char *)((char *)s0 + 0x20) == 1) {
        if (func_002A77E0(2) != 0)
            func_L05_00379FA0(0.6f, 5.0f, 1.0f, s0, 0x60800000, 1, 0, 1.0f, 0, -1, 0);
        else
            func_L05_00379FA0(0.6f, 5.0f, 1.0f, s0, 0x60800080, 1, 0, 1.0f, 0, -1, 0);
    }
    if (func_002A77E0(3) == 0)
        func_002E5CF8(0, 0, s0);
    *(int *)((char *)s1 + 0x268) = 0x15;
}

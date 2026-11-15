#include "include_asm.h"
#include "names.h"

typedef int V4_Fb6552688 __attribute__((mode(TI)));
extern int func_002ED688(unsigned char *owner);
extern unsigned int func_002EE6A8(unsigned char *owner);
extern void func_002EE988(char *);

/* Copies the 16-byte vector at `src` to offset 0x60 of the owner's object, then runs func_002EE988 unless the
   state is 2 or 0xC. The destination is formed after the null test (in the branch's delay slot): formed before it,
   the `daddu $s0,$a0` of the prologue lands behind the second save instead of between the first two. */
/* Sets the follower's push vector and clamps its movement, except while it is in state 2 or 12. */
void func_002EE920(unsigned char *owner, V4_Fb6552688 *src)
{
    char *object;
    unsigned int state;

    object = (char *)GetMobyMotionData(owner);
    if (object == 0)
        return;
    *(V4_Fb6552688 *)(object + 0x60) = *src;
    state = GetFollowerState(owner);
    if (state == 2)
        return;
    if (state == 0xC)
        return;
    ClampFollowerPushVector((char *)owner);
}

#include "include_asm.h"
#include "names.h"

typedef int V4_Fb6552688 __attribute__((mode(TI)));
extern int moby_get_motion_data(unsigned char *owner);
extern unsigned int follower_get_state(unsigned char *owner);
extern void follower_clamp_push_vector(char *);

/* Copies the 16-byte vector at `src` to offset 0x60 of the owner's object, then runs func_002EE988 unless the
   state is 2 or 0xC. The destination is formed after the null test (in the branch's delay slot): formed before it,
   the `daddu $s0,$a0` of the prologue lands behind the second save instead of between the first two. */
/* Sets the follower's push vector and clamps its movement, except while it is in state 2 or 12. */
void follower_set_push_vector(unsigned char *owner, V4_Fb6552688 *src)
{
    char *object;
    unsigned int state;

    object = (char *)moby_get_motion_data(owner);
    if (object == 0)
        return;
    *(V4_Fb6552688 *)(object + 0x60) = *src;
    state = follower_get_state(owner);
    if (state == 2)
        return;
    if (state == 0xC)
        return;
    follower_clamp_push_vector((char *)owner);
}

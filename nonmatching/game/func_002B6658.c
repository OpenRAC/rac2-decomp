/* Tier: opus (task v2121).  Best: 144/148 bytes, 0/28 places (check.py via
   cdiff.py, this checkout's compiler, -G8 sibling src/game/002B6120-g8.c).

   func_002B6658, boot 0x002B6658, catalogue size 148 (0x94).  Placing it needs
   the -G8 sibling (the head store is `sw $v0,0x2B78($gp)`) and removing the
   INCLUDE_ASM marker from src/game/002B6120.c.

   Now right in this draft:
   - the head store comes from $v0: a separate `head` local for the call
     result (t = head) gives the store its own short pseudo in $v0;
   - `beqz $v1 / nop` before the callback: declaring `flags` (0x34) volatile
     stops reorg stealing the target's `lhu` into a `beql` slot.  NOT
     JUSTIFIED YET: retail rereads flags only after calls, which plain code also
     does, so this volatile has no evidence and would not land as is.  Without
     it the branch is `beql $v0,$zero / lhu $v0,0x34($s0)` (still 144 bytes).

   Still different (retail on the right):
     lw   $v0,0x64($s0)  (x2)        | lw   $v1,0x64($s0)  (x2)
     jalr $v0 / daddu $a0,$s0 (slot) | daddu $a0,$s0 / jalr $v1 / nop
   Reorg's backward scan (fill_simple_delay_slots, calls first) always moves
   `move $a0,$s0` into the jalr slot here; retail's empty slot needs something
   zero-length between the move and the call (an UNSPEC_VOLATILE/asm, a label)
   or a volatile resource on the call, and a callback in $v1 means $v0 conflicts
   with the pointer pseudo during its life.  Neither found.
   Tried with the same bytes: callback returning int (call_value) or void,
   varargs `(Node *, ...)`, unprototyped `()`, the pointer in a local `fn`.
   The level copies (level 0: f_0032D068, and the inlined walker at the end of
   f_0032CF60 = boot 0x002B6550) show the same beqz/nop/move/jalr/nop shape, so
   the quirk comes from this loop body, probably a shared inline walker.
   Older wordings (while/continue, if/else, for(;;) with goto) are in git
   history of this file.
*/

#include "include_asm.h"

typedef struct Node Node;

struct Node {
    unsigned char pad0[0x20];
    signed char flag20;
    unsigned char pad21[7];
    Node *next;
    unsigned char pad2c[8];
    volatile unsigned short flags;
    unsigned char pad36[0x2E];
    int (*vfunc)(Node *);
};

extern Node *func_002A08A0(void);
extern void func_002A05A8(Node *);
extern void func_002A0F48(Node *);
extern Node *ref_L00_002B6658_00 __attribute__((sda));

void func_002B6658(void)
{
    Node *head = func_002A08A0();
    Node *t;

    ref_L00_002B6658_00 = head;
    for (t = head; t != 0; t = t->next) {
        if (t->flag20 < 0)
            continue;
        if ((t->flags & 0x40) == 0)
            func_002A05A8(t);
        if (t->vfunc != 0)
            t->vfunc(t);
        if ((t->flags & 4) == 0)
            func_002A0F48(t);
    }
}

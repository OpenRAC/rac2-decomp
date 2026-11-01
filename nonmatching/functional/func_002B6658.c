/* functional: high. Walks the node list the same way (skip negative flag, draw, call the node's own function, update) and records the head; the branch forms differ. */
/* Current-master USA v1.01 replay: 152 bytes against 148 and 0/28 placements.
   The loop's shape and frame are right, but the compiler picks different
   branch forms and registers.

   func_002B6658, boot 0x002B6658, catalogue size 148 (0x94).

   The retail bytes are

       002b6664  jal   func_2A08A0
       002b666c  daddu $s0,$v0,$zero
       002b6670  beqz  $s0,...
       002b6674  sw    $v0,0x2B78($gp)      <- the global, in small data
       002b6678  lb    $v0,0x20($s0)
       002b667c  nop
       002b6680  bltzl $v0,...              <- likely form
       002b6684  lw    $s0,0x28($s0)        <- the advance, in the delay slot
       ...                                    (the body)
       002b66a4  beqz  $v1,...              <- plain form
       002b66c0  bnel  $v0,$zero,...        <- likely form
       002b66d4  bnel  $s0,$zero,...

   This C compiles to 152 bytes, four more than the retail.  The differences
   are the branch-likely bits (our `bltz`/`beql`/`bnez` against the retail's
   `bltzl`/`beqz`/`bnel`), the register the global is stored from (our $s0
   against the retail's $v0), the register the vtable pointer lives in (our
   $v0 against the retail's $v1), and the advance that the retail keeps in
   the delay slot of the flag test while ours emits it after a `nop`.

   The global is at 0x001B1B68 (gp 0x001AEFF0 + 0x2B78) and lives in the
   small-data section, so this function needs the -G8 sibling
   `002B6120-g8.c`; at -G0 the compiler emits `sw $s0,0x0($gp)` and the
   assembler expands the reference to a lui/addiu pair instead.

   Tried: `while` with `continue`, `while` with `if/else`, `for(;;)` with the
   `if (...) goto body;` recipe from docs/COMPILER-NOTES.md, a goto to the
   loop condition, and a local copy of the flag byte.  The frame, the load
   count and the body shape are right in every spelling; the likely bits and
   the register allocation are not.
*/

typedef struct Node Node;

struct Node {
    unsigned char pad0[0x20];
    signed char flag20;
    unsigned char pad21[7];
    Node *next;
    unsigned char pad2c[8];
    unsigned short flags;
    unsigned char pad36[0x2E];
    void (*vfunc)(Node *);
};

extern Node *func_002A08A0(void);
extern void func_002A05A8(Node *);
extern void func_002A0F48(Node *);
extern Node *D_001B1B68 __attribute__((sda));

void func_002B6658(void)
{
    Node *t = func_002A08A0();

    D_001B1B68 = t;
    for (; t != 0; t = t->next) {
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
